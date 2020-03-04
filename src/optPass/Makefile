LLVM_CONFIG?=llvm-config

ifdef SILENT
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS += -pthread $(shell $(LLVM_CONFIG) --ldflags) $(shell $(LLVM_CONFIG) --system-libs) -L/home/osboxes/Desktop/llvm/build/lib
COMMON_FLAGS = -Wall -Wextra -g
CXXFLAGS += $(COMMON_FLAGS) $(shell ($(LLVM_CONFIG) --cxxflags))
CPPFLAGS += $(shell ($(LLVM_CONFIG) --cppflags)) -I$(SRC_DIR)


ifeq ($(shell uname), Darwin)
LOADABLE_MODULE_OPTIONS=-bundle -undefined dynamic_lookup
else
#-shared create a shared library. -Wl,-o1 asks the GNU linker ld to optimize symbol table
LOADABLE_MODULE_OPTIONS=-shared -Wl,-O1
endif



# GENIR=genIR
# GENIR_OBJECTS=genIR.o

FNARGPASS=fnarg.so
FNARGPASS_OBJECTS=FnArgCnt.o

default: $(FNARGPASS)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(FNARGPASS) : $(FNARGPASS_OBJECTS)
	@echo Linking $@
	$(QUIET)$(CXX) -o $@ $(LOADABLE_MODULE_OPTIONS) $(CXXFLAGS) $^ $(LDFLAGS)

clean:
	$(QUIET)rm -f $(FNARGPASS) $(FNARGPASS_OBJECTS)

run:
	opt -load=./fnarg.so -fnargcnt < ../../test/fact.bc > /dev/null
# > /dev/null is for stderr. 
