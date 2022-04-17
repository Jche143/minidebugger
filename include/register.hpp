#ifndef MINI_DEBUGGER_REGISTERS_HPP
#define MINI_DEBUGGER_REGISTERS_HPP

#include <sys/user.h>
#include <algorithm>
#include <iostream>
#include <sys/ptrace.h>
#include <sys/uio.h>

using namespace std;

namespace minidebugger{
    //枚举寄存器
    enum class reg{
        rax, rbx, rcx, rdx,
        rdi, rsi, rbp, rsp,
        r8,  r9,  r10, r11,
        r12, r13, r14, r15,
        rip, eflags,    cs,
        orig_rax, fs_base,
        gs_base,
        fs, gs, ss, ds, es    
    };

    //常量27个
    constexpr size_t n_registers = 27;

    //结构体存储寄存器信息
    struct reg_descriptor {
        reg r;
        int dwarf;
        string name;
    };

    //列出对应寄存器信息
    const array<reg_descriptor, n_registers> g_register_descriptors {{
        {reg::r15, 15, "r15"},
        {reg::r14, 14, "r14"},
        {reg::r13, 13, "r13"},
        {reg::r12, 12, "r12"},
        {reg::rbp, 6, "rbp"},
        {reg::rbx, 3, "rbx"},
        {reg::r11, 11, "r11"},
        {reg::r10, 10, "r10"},
        {reg::rax, 0, "rax"},
        {reg::rcx, 2, "rcx"},
        {reg::rdx, 1, "rdx"},
        {reg::rsi, 4, "rsi"},
        {reg::rdi, 5, "rdi"},
        {reg::orig_rax, -1, "orig_rax"},
        {reg::rip, -1, "rip"},
        {reg::cs, 51, "cs"},
        {reg::eflags, 49, "eflags"},
        {reg::rsp, 7, "rsp"},
        {reg::ss, 52, "ss"},
        {reg::fs_base, 58, "fs_base"},
        {reg::gs_base, 59, "gs_base"},
        {reg::ds, 53, "ds"},
        {reg::es, 50, "es"},
        {reg::fs, 54, "fs"},
        {reg::gs, 55, "gs"}
    }};

    //获取寄存器值
    uint64_t get_register_value(pid_t pid, reg r){
        user_regs_struct regs;
        ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
        // auto it = find_if(begin(g_register_descriptors), end(g_register_descriptors),
        // [r](auto&& rd) { return rd.r == r; });
        // return *(reinterpret_cast<uint64_t*>(&regs) + (it - begin(g_register_descriptors)));
        uint64_t ret = 0;
        switch(r){
            case reg::rax:
                ret = regs.rax;
                break;
            case reg::rbx:
                ret = regs.rbx;
                break;
            case reg::rcx:
                ret = regs.rcx;
                break;
            case reg::rdx:
                ret = regs.rdx;
                break;
            case reg::rdi:
                ret = regs.rdi;
                break;
            case reg::rsi:
                ret = regs.rsi;
                break;
            case reg::rbp:
                ret = regs.rbp;
                break;
            case reg::rsp:
                ret = regs.rsp;
                break;
            case reg::r8:
                ret = regs.r8;
                break;
            case reg::r9:
                ret = regs.r9;
                break;
            case reg::r10:
                ret = regs.r10;
                break;
            case reg::r11:
                ret = regs.r11;
                break;
            case reg::r12:
                ret = regs.r12;
                break;
            case reg::r13:
                ret = regs.r13;
                break;
            case reg::r14:
                ret = regs.r14;
                break;
            case reg::r15:
                ret = regs.r15;
                break;
            case reg::rip:
                ret = regs.rip;
                break;
            case reg::eflags:
                ret = regs.eflags;
                break;
            case reg::cs:
                ret = regs.cs;
                break;
            case reg::fs:
                ret = regs.fs;
                break;
            case reg::gs:
                ret = regs.gs;
                break;
            case reg::es:
                ret = regs.es;
                break;
            case reg::ds:
                ret = regs.ds;
                break;
            case reg::ss:
                ret = regs.ss;
                break;
            case reg::orig_rax:
                ret = regs.orig_rax;
                break;
            case reg::fs_base:
                ret = regs.fs_base;
                break;
            default:
                break;
        }
        return ret;
    }

    //设置寄存器值
    void set_register_value(pid_t pid, reg r, uint64_t value) {
        user_regs_struct regs;
        ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
        // auto it = find_if(begin(g_register_descriptors), end(g_register_descriptors),
        // [r](auto&& rd) { return rd.r == r; });

        // *(reinterpret_cast<uint64_t*>(&regs) + (it - begin(g_register_descriptors))) = value;

        switch(r){
            case reg::rax:
                regs.rax = value;
                break;
            case reg::rbx:
                regs.rbx = value;
                break;
            case reg::rcx:
                regs.rcx = value;
                break;
            case reg::rdx:
                regs.rdx = value;
                break;
            case reg::rdi:
                regs.rdi = value;
                break;
            case reg::rsi:
                regs.rsi = value;
                break;
            case reg::rbp:
                regs.rbp = value;
                break;
            case reg::rsp:
                regs.rsp = value;
                break;
            case reg::r8:
                regs.r8 = value;
                break;
            case reg::r9:
                regs.r9 = value;
                break;
            case reg::r10:
                regs.r10 = value;
                break;
            case reg::r11:
                regs.r11 = value;
                break;
            case reg::r12:
                regs.r12 = value;
                break;
            case reg::r13:
                regs.r13 = value;
                break;
            case reg::r14:
                regs.r14 = value;
                break;
            case reg::r15:
                regs.r15 = value;
                break;
            case reg::rip:
                regs.rip = value;
                break;
            case reg::eflags:
                regs.eflags = value;
                break;
            case reg::cs:
                regs.cs = value;
                break;
            case reg::fs:
                regs.fs = value;
                break;
            case reg::gs:
                regs.gs = value;
                break;
            case reg::es:
                regs.es = value;
                break;
            case reg::ds:
                regs.ds = value;
                break;
            case reg::ss:
                regs.ss = value;
                break;
            case reg::orig_rax:
                regs.orig_rax = value;
                break;
            case reg::fs_base:
                regs.fs_base = value;
                break;
            default:
                break;
        }
        ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
    }

    //通过寄存器号查找
    uint64_t get_register_value_from_dwarf_register (pid_t pid, unsigned regum){
        auto it = find_if(begin(g_register_descriptors), end(g_register_descriptors),
                [regum](auto&& rd) { return rd.dwarf == regum;}
        );
        if (it == end(g_register_descriptors)) {
            throw out_of_range{"Unknow dwarf register"};
        }
        return get_register_value(pid, it->r);
    }

    //获取寄存器name
    string get_register_name(reg r){
        // auto it = find_if(begin(g_register_descriptors), end(g_register_descriptors),
        //             [r](auto&& rd) { return rd.r == r; });
        // return it->name;
        string ret = "";
        switch(r){
            case reg::rax:
                ret = "rax";
                break;
            case reg::rbx:
                ret = "rbx";
                break;
            case reg::rcx:
                ret = "rcx";
                break;
            case reg::rdx:
                ret = "rdx";
                break;
            case reg::rdi:
                ret = "rdi";
                break;
            case reg::rsi:
                ret = "rsi";
                break;
            case reg::rbp:
                ret = "rbp";
                break;
            case reg::rsp:
                ret = "rsp";
                break;
            case reg::r8:
                ret = "r8";
                break;
            case reg::r9:
                ret = "r9";
                break;
            case reg::r10:
                ret = "r10";
                break;
            case reg::r11:
                ret = "r11";
                break;
            case reg::r12:
                ret = "r12";
                break;
            case reg::r13:
                ret = "r13";
                break;
            case reg::r14:
                ret = "r14";
                break;
            case reg::r15:
                ret = "r15";
                break;
            case reg::rip:
                ret = "rip";
                break;
            case reg::eflags:
                ret = "eflags";
                break;
            case reg::cs:
                ret = "cs";
                break;
            case reg::fs:
                ret = "fs";
                break;
            case reg::gs:
                ret = "gs";
                break;
            case reg::es:
                ret = "es";
                break;
            case reg::ds:
                ret = "ds";
                break;
            case reg::ss:
                ret = "ss";
                break;
            case reg::orig_rax:
                ret = "orig_rax";
                break;
            case reg::fs_base:
                ret = "fs_base";
                break;
            default:
                break;
        }
        return ret;
    }

    //通过name获取寄存器
    reg get_register_from_name(const string& name){
        auto it = find_if(begin(g_register_descriptors), end(g_register_descriptors),
                    [name](auto&& rd) { return rd.name == name; });
            return it->r;
    }
}

#endif