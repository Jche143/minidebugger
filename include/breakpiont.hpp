#ifndef MINI_DEBUGGER_BREAKPOINT_HPP
#define MINI_DEBUGGER_BREAKPOINT_HPP

#include <sys/ptrace.h>
#include <cstdint>
#include <iostream>

using namespace std;

namespace minidebugger{
    class breakpoint{
        public:
            breakpoint() = default;
            breakpoint(pid_t pid, intptr_t addr) : m_pid{pid}, m_addr{addr}, m_enabled{false}, m_saved_data{} {}
            void enable() {
                // cout << "enable breakpoint: " << m_addr << endl;

                //获取当前地址数据
                auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);

                //cout << "orgin data: " << hex << data << endl;

                //保存最低8字节数据
                m_saved_data = static_cast<uint8_t>(data & 0xff);

                //cout << "save data: " << m_saved_data << endl;

                uint64_t int3 = 0xcc;

                //设置低8字节为0xcc
                uint64_t data_with_int3 = ((data & ~0xff) | int3);

                //cout << "repalced_data:" << hex << replaced_data << endl;
                
                //设置新数据
                ptrace(PTRACE_POKEDATA, m_pid, m_addr, data_with_int3);

                m_enabled = true;

            }

            void disable(){

                //将低8位数据还原
                auto data = ptrace(PTRACE_PEEKDATA, m_pid, m_addr, nullptr);

                //cout << "saved data: " << hex << m_saved_data << endl;

                //待还原数据
                auto restored_data = ((data & ~0xff) | m_saved_data);

                //设置数据
                ptrace(PTRACE_POKEDATA, m_pid, m_addr, restored_data);

                m_enabled = false;
            }

            auto is_enabled() const -> bool {
                return m_enabled;
            }

            auto get_address() const -> intptr_t {
                return m_addr;
            }
        private:
            pid_t m_pid;
            intptr_t m_addr;
            bool m_enabled;
            uint8_t m_saved_data; //保存被breakpoint占用前的数据
    };
}

#endif