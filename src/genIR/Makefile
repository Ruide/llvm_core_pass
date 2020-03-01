LLVM_CONFIG?=llvm-config
#  --enable-curses=no --enable-terminfo=no


ifdef SILENT
QUIET:=@
endif

SRC_DIR?=$(PWD)
#-Wl,--start-group -L/lib/x86_64-linux-gnu -ltinfo -Wl,--end-group
LDFLAGS += -pthread $(shell $(LLVM_CONFIG) --ldflags) $(shell $(LLVM_CONFIG) --system-libs) -L/home/osboxes/Desktop/llvm/build/lib
COMMON_FLAGS = -Wall -Wextra -g
CXXFLAGS += $(COMMON_FLAGS) $(shell ($(LLVM_CONFIG) --cxxflags))
CPPFLAGS += $(shell ($(LLVM_CONFIG) --cppflags)) -I$(SRC_DIR)

GENIR=genIR
GENIR_OBJECTS=genIR.o

default: $(GENIR)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(GENIR) : $(GENIR_OBJECTS)
	@echo Linking $@
	/usr/lib/gcc/x86_64-linux-gnu/5/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper -plugin-opt=-fresolution=/tmp/ccAgUUkP.res -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lpthread -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro -o genIR /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o -L/home/osboxes/Desktop/llvm/build/lib -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. -lrt -ldl -lz genIR.o -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMCore -lLLVMSupport -lstdc++ -lm -lgcc_s -lgcc -lpthread -ltinfo -ldl -lc -lgcc_s -lgcc /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o

#$(QUIET)$(CXX) -v -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `llvm-config --libs bitwriter core support`


#/usr/lib/gcc/x86_64-linux-gnu/5/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu /lib64/ld-linux-x86-64.so.2 hello.o -o helloworld /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. -L/home/osboxes/Desktop/llvm/build/lib -lrt -ldl -lz -lLLVMBitReader -lLLVMCore -lLLVMSupport -lstdc++ -lm -lgcc_s -lgcc -ldl -ltinfo -lpthread -lc -lgcc_s -lgcc /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o -lLLVMSupport
# Note that after the linker has looked at a library, it won't look at it again. Even if it exports symbols that may be needed by some later library. The only time where a linker goes back to rescan objects it has already seen happens within a single library - as mentioned above, once an object from some library is taken into the link, all other objects in the same library will be rescanned. Flags passed to the linker can tweak this process - again, we'll see some examples later.



clean:
	$(QUIET)rm -f $(GENIR) $(GENIR_OBJECTS)

# /usr/lib/gcc/x86_64-linux-gnu/5/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/5/liblto_plugin.so --sysroot=/ 
# --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 
# -z relro -o helloworld /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o 
# /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o 
# -L/usr/lib/llvm-3.8/lib -L/usr/lib/gcc/x86_64-linux-gnu/5 -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu 
# -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu 
# -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. -lrt {delete: -ldl -ltinfo -lpthread} -lz hello.o -lLLVMBitReader 
# -lLLVMCore -lLLVMSupport -lstdc++ -lm -lgcc_s -lgcc <!need to be here: -ldl -ltinfo -lpthread!> -lc -lgcc_s -lgcc 
# /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o
