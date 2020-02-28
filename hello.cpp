#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/Error.h"
//#include "llvm/Support/system_error.h"
#include <iostream>

using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

int main(int argc, char** argv){
	cl::ParseCommandLineOptions(argc, argv, "hello world llvm\n");
	// bool ParseCommandLineOptions(int argc, const char *const *argv,
	//                              const char *Overview = nullptr,
    //	                            bool IgnoreErrors = false);
	LLVMContext context;
	ErrorOr<std::unique_ptr<MemoryBuffer>> mb = MemoryBuffer::getFile(FileName);
	// ErrorOr< std::unique_ptr< MemoryBuffer > > MemoryBuffer::getFile	(	const Twine & 	Filename,
	// int64_t 	FileSize = -1,
	// bool 	RequiresNullTerminator = true,
	// bool 	IsVolatile = false )	
	ErrorOr<std::unique_ptr<Module>> m = parseBitcodeFile(mb.get().get()->getMemBufferRef(), context);
	// ErrorOr<std::unique_ptr<Module>> parseBitcodeFile(MemoryBufferRef Buffer,
    //                                                   LLVMContext &Context);

	if (bool(m) == false){
		std::cerr << "Error reading Bitcode: " << mb.getError() << std::endl;
		return -1;
	}
	raw_os_ostream O(std::cout);
	for (Module::const_iterator i = m.get().get()->getFunctionList().begin(), e = m.get().get()->getFunctionList().end(); i!=e; i++){
	if (!i->isDeclaration()){
		O << i->getName() << " has " << i->size() << " basic block(s) .\n";
		}
	}
	return 0;
}
