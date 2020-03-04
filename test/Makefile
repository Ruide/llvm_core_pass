all:
	clang -c -emit-llvm fact.cpp -o fact.bc
	llvm-dis fact.bc
clean:
	rm *.bc *.ll 
