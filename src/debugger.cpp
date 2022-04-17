#include <iostream>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/personality.h>
#include <sstream>
#include <sys/procfs.h>
#include <iomanip>

#include "../include/debugger.hpp"
#include "../include/linenoise.h"
#include "../include/register.hpp"

using namespace minidebugger;
using namespace std;

//行命令分隔
vector<string> split(const string &s, char delimiter){
    vector<string> out{};
    stringstream ss {s};
    string item;

    while(getline(ss, item, delimiter)){
        out.push_back(item);
    }
    return out;
}

//of以s为前缀
bool is_prefix(const string& s, const string& of){
    if(s.size() > of.size()){
        return false;
    }
    return equal(s.begin(), s.end(), of.begin());
}

void debugger::continue_execution(){
    step_over_breakpoint();
    ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);
    //继续进程
    wait_for_single();
}

void debugger::handle_command(const string& line){
    auto args = split(line, ' ');
    auto command = args[0];
    
    //继续（c）
    if (is_prefix(command, "continue")){
        continue_execution();
    }

    //添加断点（b）
    else if(is_prefix(command, "break")){
        string addr (args[1], 2); //假设用户输入了0xADDRESS
        set_breakpoint_at_address(stol(addr, 0, 16));
    }

    //删除断点（delete）
    else if(is_prefix(command, "delete")){
        string addr (args[1], 2);
        delete_breakpiont_at_address(stol(addr, 0, 16));
    }

    //退出（quit）
    else if(is_prefix(command, "quit")){
        exit(0);
    }

    //读写寄存器（register）
    else if(is_prefix(command, "register")){

        if (is_prefix(args[1], "read")){
            // cout << get_register_value(m_pid, reg::rip) << endl;
            cout << args[2] << " : " << get_register_value(m_pid, get_register_from_name(args[2])) << endl; 
        }
        else if(is_prefix(args[1], "write")){
            string val {args[3], 2}; //假定0xval
            set_register_value(m_pid, get_register_from_name(args[2]), stol(val, 0, 16));
        }
    }

    //打印内存映射（vmmap）
    else if(is_prefix(command,"vmmap")){
        get_maps();
    }

    // //单步运行（n）
    // else if(is_prefix(command, "n")){
    //     ptrace(PTRACE_SINGLESTEP, m_pid, nullptr, nullptr);
    // }

    //读写内存（memory）
    else if(is_prefix(command, "memory")){
        string addr {args[2], 2}; //address 0xadrress

        if (is_prefix(args[1], "read")) {
            cout << hex << read_memory(stol(addr, 0, 16)) << endl;
        }
        else if(is_prefix(args[1], "write")){
            string val {args[3], 2}; //0xval
            write_memory(stol(addr, 0, 16), stol(val, 0, 16));
        }
    }
    else {
        cerr << "Unknow command\n";
    }

}

void debugger::run() {
    int wait_status;
    auto options = 0;
    //等待进程状态变化，暂停。被追踪的程序启动完成，会收到 SIGTRAP 信号，暂停。
    waitpid(m_pid, &wait_status, options);

    char* line = nullptr;
    while((line = linenoise("minidebugger> ")) != nullptr){
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }

}

//打印程序映射
void debugger::get_maps()
{
    string filename = "/proc/";
    string pid_str = to_string(m_pid);
    filename += pid_str + "/maps";
    FILE* maps = fopen(filename.c_str(), "r");
    if(!maps){
        cout << "fail to open the file" << endl;
        return;
    }
    size_t len = 0;
    ssize_t read;
    char* line = NULL;
    printf("address                   pm   offset   io    inode                      information\n");
    while(read = getline(&line, &len, maps) != -1){
        printf("%s",line);
    }
    fclose(maps);
}

void debugger::set_base_addr()
{
    string pid_str = to_string(m_pid);
    string filename = "/proc";
    filename += "/" + pid_str + "/maps";
    FILE* maps = fopen(filename.c_str(), "r");
    if(!maps)
    {
        cout << "Failed to open file " << " " << filename.c_str() << endl;
        return;
    }
    fscanf(maps, "%lx", &m_base_addr);
    // cout << m_base_addr << endl;
    fclose(maps);
}

uint64_t debugger::get_pc() {
    return get_register_value(m_pid, reg::rip);
}

void debugger::set_pc(uint64_t pc){
    set_register_value(m_pid, reg::rip, pc);
}

void debugger::wait_for_single(){
    int wait_status;
    auto options = 0;
    waitpid(m_pid, &wait_status, options);
}

void debugger::step_over_breakpoint(){
    auto possible_breakpoint_location = get_pc() - 1;

    if(m_breakpoints.count(possible_breakpoint_location)){
    auto& bp = m_breakpoints[possible_breakpoint_location];

    if(bp.is_enabled()){
        auto previous_instruction_address = possible_breakpoint_location;
        set_pc(previous_instruction_address);

        bp.disable();
        ptrace(PTRACE_SINGLESTEP, m_pid, nullptr, nullptr);
        wait_for_single();
        bp.enable();
    }
    }
}


intptr_t debugger::set_breakpoint_at_address(intptr_t addr){
    cout << "base addr: " << hex << (m_base_addr) << endl;
    addr = addr + m_base_addr;
    cout << "set breakpoint at address 0x" << hex << addr << endl;
    breakpoint bp (m_pid, addr);
    bp.enable(); 
    //添加断点
    m_breakpoints[addr] = bp;
    return addr;
}

void debugger::delete_breakpiont_at_address(intptr_t addr){
    addr += m_base_addr;
    if(m_breakpoints.count(addr)){

        auto &bp = m_breakpoints[addr];

        if(bp.is_enabled()){
            bp.disable();
            cout << "success delete the breakpoint at 0x" << hex << addr << endl;
        }else{
            cout << "there is no breakpoint at 0x" << hex << addr << endl;
        }
    }
}

void execute_debugee(const string& prog_name){
    //允许父进程对其跟踪
    if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0){
        cerr << "Error in ptrace\n";
        return;
    }
    execl(prog_name.c_str(), prog_name.c_str(), nullptr);
}

void debugger::dump_registers(){
    for (const auto& rd : g_register_descriptors){
        cout << rd.name << "0x"
            << setfill('0') << setw(16) << hex << get_register_value(m_pid, rd.r) << endl;
    }
}

uint64_t debugger::read_memory(uint64_t address){
    return ptrace(PTRACE_PEEKDATA, m_pid, address, nullptr);
}

void debugger::write_memory(uint64_t address, uint64_t value){
    ptrace(PTRACE_POKEDATA, m_pid, address, value);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "Program name not specified";
        return -1;
    }

    auto prog = argv[1];

    auto pid = fork();

    if(pid == 0){
        //子进程,执行被跟踪程序
        // personality(ADDR_NO_RANDOMIZE);
        // execl(prog, prog, nullptr);
        execute_debugee(prog);
    }
    else if (pid >= 1){
        //父进程返回子进程的id
        cout << "Started debugging process " << pid << '\n';
        debugger dbg{prog, pid};
        dbg.run();
    }
}