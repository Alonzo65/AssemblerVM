#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H
#include <iostream>
#include <string>
#include <initializer_list>
#include <algorithm>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <unordered_map>
#include <tuple>
using namespace std;

class syntaxHelper {
public:
	tuple<int, int, int> binaryVals;	
	int instruction = 0;
	string oper1;	//this will hold the parsed string of operand1 without commas or whitespace 
	string errMsg;	//used to hold error messages 
	int op1 = 0;
	int op2 = 0;
	syntaxHelper() {}	

	//checkToks will check for syntax and return a tuple of the int values of the opcode, operand1, and operand2
	tuple<int,int,int>* checkToks(string opcode, string operand1, string operand2, unordered_map<string, int>& symbolTabl) {
		//check if the opcode given is a valid instruction
		if (opcodes.count(opcode) == 0) {
			//throw an exception/error code saying that this opcode is not a valid instruction
			errMsg = opcode + " is not a valid instruction.";
			throw invalid_argument(errMsg);
		}
		
		//set instruction to the int value of the opcode found in the opcodes map
		instruction = opcodes.at(opcode);

		//run the specific instructions code to check for proper syntax
		if (instruction == 1) {	//JMP
			//remove any white space
			oper1 = operand1.substr(0, operand1.find(" "));
			//check to see if oper1(operand1) is a label that lies in the symbolTable
			if (symbolTabl.count(oper1) > 0) {
				binaryVals = make_tuple(instruction, symbolTabl.at(oper1), op2);
			}
			else {
				//throw an exception saying that the operand1 provided is not a label 
				errMsg = "Operand 1 for " + opcode + " is not a label.";
				throw invalid_argument(errMsg);
			}
		}
		else if (isIn(instruction, { 7, 13, 15, 16, 17 })) {	//MOV, ADD, SUB, MUL, DIV
			//check for comma and white space
			if (operand1.find(", ") == string::npos) {
				//throw an exception message saying that there needs to be a comma and white space seperating operand 1 and 2
				errMsg = "Syntax error: There needs to be a comma and white space seperating operand 1 and operand 2.";
				throw invalid_argument(errMsg);
			}

			oper1 = operand1.substr(0, operand1.find(","));
			//check if oper1 and operand2 are both registers
			if (registers.count(oper1) > 0 && registers.count(operand2) > 0) {
				binaryVals = make_tuple(instruction, registers.at(oper1), registers.at(operand2));
			}
			else {
				//throw an exception message saying that <instruction> requires that both operands be registers
				errMsg = opcode + " instruction requires that operand 1 be a register and operand 2 be a register.";
				throw invalid_argument(errMsg);
			}
		}
		else if (isIn(instruction, {10, 12})) {	//LDR, LDB
			//check to see if there is a comma and white space seperating operand 1 and operand 2
			if (operand1.find(", ") == string::npos) {
				//throw an exception message saying that there needs to be a comma and white space seperating operand 1 and 2
				errMsg = "Syntax error: There needs to be a comma and white space seperating operand 1 and operand 2.";
				throw invalid_argument(errMsg);
			}

			//set oper1 to operand1, but without any commas
			oper1 = operand1.substr(0, operand1.find(","));

			//check if oper1 is a register and operand2 is a label
			if (registers.count(oper1) > 0 && symbolTabl.count(operand2) > 0) {
				//set binaryVals to a new tuple of the int values of instruction, oper1, and operand2
				binaryVals = make_tuple(instruction, registers.at(oper1), symbolTabl.at(operand2));
			}
			else {
				//throw an exception message saying that <instruction> requires that operand1 be a register and operand 2 has to be a label
				errMsg = opcode + " instruction requires that operand 1 be a register and operand 2 be a label.";
				throw invalid_argument(errMsg);
			}
		}
		else {
			//only thing left is TRP since we already checked earlier if opcode exists in the opcode table
			//get rid of any white space in operand1
			oper1 = operand1.substr(0, operand1.find(" "));
			//check if user provided a label, register, or nothing for operand 1 for the TRP instruction
			if (registers.count(oper1) > 0 || symbolTabl.count(oper1) > 0 || oper1 == "") {
				//the given operand 1 must be a decimal number
				errMsg = opcode + " requires a decimal number for operand 1.";
				throw invalid_argument(errMsg);
			}
				binaryVals = make_tuple(instruction, stoi(oper1), op2);	
		}
		//set instruction and operands back to 0
		instruction = 0;
		op1 = 0;
		op2 = 0;
		return &binaryVals;
}

	

private:
	//function to check if instruction lies in a set of opcode values given
	bool isIn(const int& instr, initializer_list<int> checkList) {
		return(find(begin(checkList), end(checkList), instr) != end(checkList));
	}
	//we will check against our map of opcodes to see if the opcode/instruction given exists
	//if not then throw an error, if it does exist then return its int value
	unordered_map<string, int> opcodes = {
		{"JMP", 1},
		{"MOV", 7},
		{"LDR", 10},
		{"LDB", 12},
		{"ADD", 13},
		{"SUB", 15},
		{"MUL", 16},
		{"DIV", 17},
		{"TRP", 21}	
	};
	
	unordered_map<string, int> registers = {
		{"R0", 0},
		{"R1", 1},
		{"R2", 2},
		{"R3", 3},
		{"R4", 4},
		{"R5", 5},
		{"R6", 6},
		{"R7", 7},
		{"R8", 8},
		{"R9", 9},
		{"R10", 10},
		{"R11", 11},
		{"R12", 12},
		{"R13", 13},
		{"R14", 14},
		{"R15", 15},
		{"PC", 16}
	};
};


#endif