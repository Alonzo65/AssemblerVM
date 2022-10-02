#ifndef VM_H
#define VM_H
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

//make pc read only, which instructions do we need to check this for?
void runVM(string fileN) {
	int opcode = 0;
	int operand1 = 0;
	int operand2 = 0;

	//R0-R15 general use pc will be R16 so in total 17 elements in register array
	int r[17] = {};	//have to make r[16] which is the pc read only
	char readB;//used to hold a byte when reading in from cin
	char byte[3 * sizeof(int)] = {}; //12 bytes, array is initialized to zero for all registers



	ifstream binF(fileN, ios::in | ios::binary);

	//check if file was open
	if (!binF.is_open()) {
		cout << "Error in opening the file" << endl;
		exit(0);
	}

	//set limits of min pc and max pc
	auto minPc = binF.tellg();
	binF.seekg(0, ios::end);
	auto maxPc = binF.tellg();
	binF.seekg(0, ios::beg);

	//might place this in a function called fetch
	binF.read(byte, 3 * sizeof(int)); // 12 bytes read
	r[16] = int(byte[0]);	//might need to change this to read 4 bytes instead of just one
	binF.seekg(r[16], ios::beg);	//set pointer of file stream to main instruction



	while (binF.tellg() != maxPc) {
		//fetch
		binF.read(byte, 3 * sizeof(int));
		//increment
		r[16] += 12;	//12 bytes we read each time 

		//decode
		opcode = *(int*)(byte);
		operand1 = *(int*)(byte + 4);
		operand2 = *(int*)(byte + 8);

		//execute
		try
		{
			switch (opcode) {
			case 1:	//jmp allowed to change pc
				//instruction
				r[16] = operand1;
				binF.seekg(r[16], ios::beg);
				break;
			case 7:	//mov allowed to change pc
				r[operand1] = r[operand2];
				//come back and alter in case it changes pc i will need to jump to it i think
				break;
			case 10:	//ldr
				//changed this to read in 4 bytes from the label instead of just one like ldb
				binF.seekg(operand2, ios::beg);
				binF.read(byte, sizeof(int));
				r[operand1] = *(int*)(byte);
				binF.seekg(r[16], ios::beg);
				break;
			case 12:	//ldb
				binF.seekg(operand2, ios::beg);
				r[operand1] = binF.peek();
				binF.seekg(r[16], ios::beg);
				break;
			case 13:	//add
				if (operand1 == 16) {
					throw invalid_argument("Instruction ADD cannot modify the contents of the PC");
				}
				r[operand1] = r[operand1] + r[operand2];
				break;
			case 15:	//sub
				if (operand1 == 16) {
					throw invalid_argument("Instruction SUB cannot modify the contents of the PC");
				}
				r[operand1] = r[operand1] - r[operand2];
				break;
			case 16:	//mul
				if (operand1 == 16) {
					throw invalid_argument("Instruction MUL cannot modify the contents of the PC");
				}
				r[operand1] = r[operand1] * r[operand2];
				break;
			case 17:	//div
				if (operand1 == 16) {
					throw invalid_argument("Instruction DIV cannot modify the contents of the PC");
				}
				r[operand1] = r[operand1] / r[operand2];
				break;
			case 21:	//trp check operand 1 for what kind of trap it is
				switch (operand1) {
				case 0:
					exit(0); //if this doesnt work we can use exit()
					break;
				case 1:
					cout << r[3];
					break;
				case 2:
					cin >> r[3];
					break;
				case 3:
					cout << char(r[3]);
					break;
				case 4:
					//will require to take a whole string(while loop of getchar() and store it in a char array) but only return the first one of it and move the pointer when trp3 is called
					// 
					//cin >> readB;//its gonna do implicit conversion if input is a char reading byte not int 
					r[3] = int(getchar());
					break;

				}
				break;
			default:
				cout << "Exited incorrectly on pc: " << r[16] << endl;
				exit(0);
			}
		}
		catch (const invalid_argument& z)
		{
			cout << "Error occured at pc: " << r[16] << " Error Message: " << z.what() << endl;

		}

		//check if pc is out of bounds
		if (r[16] > maxPc) {
			cout << "error, pc is out of bounds and in the data segment: pc > maxPc" << endl;
			exit(0);
		}
		else if (r[16] < minPc) {
			cout << "error, pc is out of bounds and is outside of the code segment: pc < minPc" << endl;
			exit(0);
		}

	}



}

#endif