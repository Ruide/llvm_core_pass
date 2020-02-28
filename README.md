# llvm_core_pass

tweaked several things to make it work
1. mb.get().get() to get object (. for object, -> for pointer. ->xxx <=> *object.xxx)
2. g++ -v can show linkder command
3. linker order. the ones being resolved need to put ahead (solved undefined ref -ltinfo -lpthread)
4. -pthread instead of -lpthread (set Macro def)
5. -L/home/osboxes/Desktop/llvm/build/lib instead of /usr/lib/llvm-3.8 (solved undefined ref cl::ParseComm...)