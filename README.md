# minidebugger
参考https://blog.tartanllama.xyz/writing-a-linux-debugger-setup/
实现以下功能：
1.(c)continue to run
2.(b 0xxxx) set breakpoint at address
3.(delete 0xxxxx) delete breakpoint at address
4.(quit) exit the debugger
5.(register) read and write the register
example: register read rip / register write rip 
6.(memory) read and write the memory at address
example: memory read 0xxxxx / memory write 0xxxx 
7.(vmmap) print the maps
and more functions tobe added