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

using namespace llvm;

Module *makeLLVMModule(){
	LLVMContext context; 
	Module *mod = new Module("sum.ll", context);
	mod -> setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
	// mod -> setDataLayout("e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-
	// 	i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-
	// 	v128:128:128-a0:0:64-s0:64:64-f80-128:128-
	// 	n8:16:32:64-S128");
	mod -> setTargetTriple("x86_64-unknown-linux-gnu");

	SmallVector<Type*, 2> FuncTyArgs;
	FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
	FunctionType *FuncTy = FunctionType::get(
		/*Results*/ IntegerType::get(mod->getContext(), 32),
		/*Params*/  FuncTyArgs, /*isVarArg=*/ false);

	Function *funcSum = Function::Create(
		/*Type=*/ FuncTy,
		/*Linkage=*/ GlobalValue::ExternalLinkage,
		/*Name=*/ "sum", mod);
	funcSum -> setCallingConv(CallingConv::C);

	Function::arg_iterator args = funcSum->arg_begin();
	Value *int32_a = &(*args);
	args++;
	int32_a->setName("a");
	Value *int32_b = &(*args);
	args++;
	int32_b->setName("b");

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
	LLVMContext context; 
	outs() << "created context\n";

	Module *Mod = makeLLVMModule();
	outs() << "created module\n";

	Mod->dump();


	raw_ostream *os;
	verifyModule(*Mod,  os);
	os->flush();
	// bool verifyModule(const Module &M, raw_ostream *OS = nullptr,
	//                  bool *BrokenDebugInfo = nullptr);
	outs() << "verified module\n";


	std::error_code error_code;
	// OwningPtr
	std::unique_ptr<tool_output_file> Out(new tool_output_file("./sum.bc", error_code, sys::fs::F_None));
	//   tool_output_file(StringRef Filename, std::error_code &EC,
    //               sys::fs::OpenFlags Flags);

  	// tool_output_file(StringRef Filename, int FD);
	outs() << "outputed file\n";

	if(error_code){
		errs() << '\n';
		return -1;
	}

	outs() << "checked error_code\n";

	// tool_output_file.os()
	// raw_fd_ostream& llvm::tool_output_file::os
	// Return the contained raw_fd_ostream.

	Mod->dump();

	WriteBitcodeToFile(Mod, Out->os());
	//   void WriteBitcodeToFile(const Module *M, raw_ostream &Out,
                          // bool ShouldPreserveUseListOrder = false,
                          // const ModuleSummaryIndex *Index = nullptr,
                          // bool GenerateHash = false);


	outs() << "writed Bitcode\n";

	Out->keep(); // Declare success
	return 0;
}