#ifndef MINI_DEBUGGER_HPP
#define MINI_DEBUGGER_HPP


#include <utility>
#include <string>
#include <linux/types.h>
#include <unordered_map>
#include "breakpiont.hpp"

using namespace std;

namespace minidebugger {
    class debugger {
    public:
        debugger() = default;
        debugger (string prog_name, pid_t pid)
        : m_prog_name{move(prog_name)}, m_pid(pid) {set_base_addr();}

        void run();
        void handle_command(const string& line);
        void continue_execution();
        intptr_t set_breakpoint_at_address(intptr_t addr);
        void set_base_addr();
        void dump_registers();
        void step_over_breakpoint();
        void wait_for_single();
        void get_maps();
        void delete_breakpiont_at_address(intptr_t addr);


        uint64_t get_pc();
        void set_pc(uint64_t pc);
        uint64_t read_memory(uint64_t address);
        void write_memory(uint64_t address, uint64_t value); 
        string m_prog_name;
        pid_t m_pid;
        unordered_map<intptr_t, breakpoint> m_breakpoints;
        intptr_t m_base_addr;
    };
}

#endif