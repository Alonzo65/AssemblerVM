#include <iostream>
#include <string>
#include "Assembler.h"
#include "VM.h"
using namespace std;

int main(int argc, char* argv[]) {
	string fileName;

	if (argc == 1) {
		cout << "Please enter a .bin or .asm file\n";
		return 0;
	}

	fileName = argv[1];
	if (fileName.find(".asm") != string::npos) {
		//run the assembler
		runAssembler(fileName);
	}
	else if (fileName.find(".bin") != string::npos) {
		//run VM
		runVM(fileName);
	}
	else {
		//throw an error saying file is not a .bin or .asm file
		cout << "file is not a .bin or .asm" << endl; 
		return 0;
	}


}