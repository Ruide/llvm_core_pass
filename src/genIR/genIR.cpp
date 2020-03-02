#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Debug.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Type.h"


using namespace llvm;

Module *makeLLVMModule(){
	LLVMContext context; 
	Module *mod = new Module("sum.ll", context);
	mod -> setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
	// mod->setDataLayout("e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80-128:128-n8:16:32:64-S128");
	mod -> setTargetTriple("x86_64-unknown-linux-gnu");
	// mod->setTargetTriple("x86_64-apple-macosx10.7.0");


	Value *int32_a;
	Value *int32_b;
	//define i32 @main(i32 %argc, i8 **%argv)
	Function *funcSum = cast<Function>(mod->
	getOrInsertFunction("sum", IntegerType::getInt32Ty(mod->getContext()),
	                    IntegerType::getInt32Ty(mod->getContext()),
	                    IntegerType::getInt32Ty(mod->getContext()), NULL));
	{
		Function::arg_iterator args = funcSum->arg_begin();
		int32_a = &*args++;
		int32_a->setName("a");
		int32_b = &*args++;
		int32_b->setName("b");
	}

	// SmallVector<Type*, 2> FuncTyArgs;
	// FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	// FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	// FunctionType *FuncTy = FunctionType::get(
	// 	/*Results*/ IntegerType::get(mod->getContext(), 32),
	// 	/*Params*/  FuncTyArgs, /*isVarArg=*/ false);

	// Function *funcSum = Function::Create(
	// 	/*Type=*/ FuncTy,
	// 	/*Linkage=*/ GlobalValue::ExternalLinkage,
	// 	/*Name=*/ "sum", mod);
	// funcSum -> setCallingConv(CallingConv::C);

	// Function::arg_iterator args = funcSum->arg_begin();
	// Value *int32_a = &(*args);
	// args++;
	// int32_a->setName("a");
	// Value *int32_b = &(*args);
	// args++;
	// int32_b->setName("b");

	BasicBlock *labelEntry = BasicBlock::Create(mod->getContext(), "entry", funcSum, 0);

	// Block entry (label_entry)
	AllocaInst *ptrA = new AllocaInst(IntegerType::get(mod->getContext(),32), "a.addr", labelEntry);
	ptrA->setAlignment(4);
	AllocaInst *ptrB = new AllocaInst(IntegerType::get(mod->getContext(),32), "b.addr", labelEntry);
	ptrB->setAlignment(4);

	StoreInst *st0 = new StoreInst(int32_a, ptrA, false, labelEntry);
	st0-> setAlignment(4);
	StoreInst *st1 = new StoreInst(int32_b, ptrB, false, labelEntry);
	st1-> setAlignment(4);

	LoadInst *ld0 = new LoadInst(ptrA, "", false, labelEntry);
	ld0-> setAlignment(4);
	LoadInst *ld1 = new LoadInst(ptrB, "", false, labelEntry);
	ld1-> setAlignment(4);
	BinaryOperator *addRes = BinaryOperator::Create(Instruction::Add, ld0, ld1, "add", labelEntry);
	ReturnInst::Create(mod->getContext(), addRes, labelEntry);

	return mod;
}




int main(){
	Module *Mod = makeLLVMModule();
	outs() << "created module\n";

	// Mod->dump();

	// raw_ostream *os;
	// raw_ostream *out = &outs();
	// verifyModule(*Mod,  out);
	if (verifyModule(*Mod)) {
		errs() << "Error: module failed verification.  This shouldn't happen.\n";
		abort();
	}
	// outs();
	
	// bool verifyModule(const Module &M, raw_ostream *OS = nullptr,
	//                  bool *BrokenDebugInfo = nullptr);
	outs() << "verified module\n";

	// Mod->dump();
	//Get the output stream
	raw_ostream *out = &outs();
	std::error_code EC;

	out = new raw_fd_ostream("./sum.bc", EC, sys::fs::F_None);
	
	// OwningPtr
	// std::unique_ptr<tool_output_file> Out(new tool_output_file("./sum.bc", EC, sys::fs::F_None));
	//   tool_output_file(StringRef Filename, std::error_code &EC,
    //               sys::fs::OpenFlags Flags);

  	// tool_output_file(StringRef Filename, int FD);
	// outs() << "outputed file\n";

	// if(error_code){
	// 	errs() << '\n';
	// 	return -1;
	// }

	// outs() << "checked error_code\n";

	// tool_output_file.os()
	// raw_fd_ostream& llvm::tool_output_file::os
	// Return the contained raw_fd_ostream.

	// Mod->dump();

	// WriteBitcodeToFile(Mod, Out->os());
	outs() << *Mod;
	WriteBitcodeToFile(Mod, *out);
    // WriteBitcodeToFile(Mod.get(), *out);
	//   void WriteBitcodeToFile(const Module *M, raw_ostream &Out,
                          // bool ShouldPreserveUseListOrder = false,
                          // const ModuleSummaryIndex *Index = nullptr,
                          // bool GenerateHash = false);


	outs() << "writed Bitcode\n";

	//Clean up
	if (out != &outs())
		delete out;

	// Out->keep(); // Declare success
	return 0;
}
