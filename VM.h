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
#include <utility>
#include <memory>
using namespace std;
//have to copy the whole .bin file into memory maybe read in file size and allocate that much in memory and copy it over? 
//if im gonna be changing the values in the array i should make a copy of it?? how do i know which ones are .int and which are .byts
 

//make pc read only, which instructions do we need to check this for?
void runVM(string fileN) {
	int opcode = 0;
	int operand1 = 0;
	int operand2 = 0;
	char* dataSegment;	//pointer to our copied bin file in memory
	//hold the range of directive values
	pair<int, int> directiveSegment;
	
	
	//R0-R15 general use pc will be R16 so in total 17 elements in register array
	long long r[21] = {};	//have to make r[16] which is the pc read only
	//registers can now have SL:17, SB:18, SP:19, FP:20(we will just use a general use register to act as the PFP)
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

	//allocate memory equal to the size of the .bin file
	char* dataPtr;	//have to set this back to dataSegment after using it to get the address
	//i dont think we need dataPtr
	dataSegment = (char*)malloc(maxPc);
	binF.read(&dataSegment[0], maxPc);
	dataPtr = dataSegment;
	//dataPtr += 4;
	//long long testers;
	//cout << long long(dataPtr) << dataPtr << endl;
	//testers = long long(dataSegment);
	//dataPtr = reinterpret_cast<char*>(testers);
	//cout << testers << endl;
	//cout << int(* dataPtr);
	
	//cout << &dataSegment << endl << dataSegment << endl;
	//cout << (*dataSegment) << endl;
	//cout << &dataPtr;
	//cout << *(dataSegment + 4);
	//cout << *dataSegment;
	//testing
	//cout << int(dataSegment[0]);
	//dataSegment[0] = 10;
	//*dataPtr = 10;
	//cout << int(dataSegment[0]);
	//cout << *(int*)(dataSegment+1);

	//reset file
	binF.clear();
	binF.seekg(0, ios::beg);

	//might place this in a function called fetch
	binF.read(byte, 3 * sizeof(int)); // 12 bytes read
	r[16] = int(byte[0]);	//might need to change this to read 4 bytes instead of just one
	binF.seekg(r[16], ios::beg);	//set pointer of file stream to main instruction
	
	//will be used in LDA to check if label is a directive
	directiveSegment = make_pair(4, r[16]);


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
			case 2:	//JMR
				r[16] = r[operand1];
				binF.seekg(r[16], ios::beg);
				break;
			case 3:	//BNZ
				if (r[operand1] != 0) {
					r[16] = operand2;
					binF.seekg(r[16], ios::beg);
				}
				
				break;
			case 4:	//BGT
				if (r[operand1] > 0) {
					r[16] = operand2;
					binF.seekg(r[16], ios::beg);
				}
				
				break;
			case 5:	//BLT
				if (r[operand1] < 0) {
					r[16] = operand2;
					binF.seekg(r[16], ios::beg);
				}
				
				break;
			case 6:	//BRZ
				if (r[operand1] == 0) {
					r[16] = operand2;
					binF.seekg(r[16], ios::beg);
				}
				
				break;
			case 7:	//mov allowed to change pc
				r[operand1] = r[operand2];
				//come back and alter in case it changes pc i will need to jump to it i think
				break;
			case 8:	//LDA only work if label is to a directive
				if (directiveSegment.first <= operand2 && operand2 < directiveSegment.second) {
					r[operand1] = long long(dataSegment + operand2);
				}
				
				break;
			case 9:	//STR //since it gives the offset we can just access it directly in our dataSegment
				dataSegment[operand2] = int(r[operand1]);
				
				break;
			case 10:	//ldr
				//changed this to read in 4 bytes from the label instead of just one like ldb
				binF.seekg(operand2, ios::beg);
				binF.read(byte, sizeof(int));
				r[operand1] = *(int*)(byte);
				binF.seekg(r[16], ios::beg);
				break;
			case 11:	//STB //since it gives the offset we can just access it directly in our dataSegment
				dataSegment[operand2] = char(r[operand1]);

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
			case 14:	//ADI
				if (operand1 == 16) {
					throw invalid_argument("Instruction ADD cannot modify the contents of the PC");
				}
				r[operand1] = r[operand1] + operand2;
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
			case 20:	//CMP
				if (r[operand1] == r[operand2]) {
					r[operand1] = 0;
				}
				else if (r[operand1] > r[operand2]) {
					r[operand1] = 1;
				}
				else {//RD<RS this is the last case so we dont need to check
					r[operand1] = -1;
				}

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
			case 22:	//STR
				dataPtr = reinterpret_cast<char*>(r[operand2]);
				*dataPtr = int(r[operand1]);

				break;
			case 23:	//LDR
				dataPtr = reinterpret_cast<char*>(r[operand2]);
				
				r[operand1] = *(int*)(dataPtr);
				break;
			case 24:	//STB
				dataPtr = reinterpret_cast<char*>(r[operand2]);
				*dataPtr = char(r[operand1]);

				break;
			case 25:	//LDB
				dataPtr = reinterpret_cast<char*>(r[operand2]);

				r[operand1] = *(dataPtr);	//is already a char* so dereferencing it returns a byte of size char

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
		//also check if there is a stack overflow or underflow.
		if (r[19] > r[18]) {
			cout << "Error: stack underflow detected: SP > SB" << endl;
			exit(0);
		}
		else if(r[19] < r[17]) {
			cout << "Error: stack overflow detected: SP < SL" << endl;
			exit(0);
		}
		if (r[16] > maxPc) {
			cout << "Error, pc is out of bounds and in the data segment: pc > maxPc" << endl;
			exit(0);
		}
		else if (r[16] < minPc) {
			cout << "Error, pc is out of bounds and is outside of the code segment: pc < minPc" << endl;
			exit(0);
		}

	}



}

#endif