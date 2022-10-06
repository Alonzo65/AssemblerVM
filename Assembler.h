#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <stdexcept>
#include <regex>
#include <unordered_map>
#include "syntaxChecker.h"	
using namespace std;
#include <tuple>
#include <sstream>

//can turn this into a class, but is it necessary? it would condense the code and make it nicer

void runAssembler(string fileN) {

		tuple<int, int, int>* binValues;
		string parseLine;
		string instruction;
		string operand1;
		string operand2;
		string fileName;
		int charRep;
		int pc = 0;
		int offset = 4;
		int lineNum = 0;
		unordered_map<string, int> symbolTable = {};
		syntaxHelper syntaxCheck;
		unordered_map<string, int> directives = {
			{".INT", 4},	//4bytes
			{".BYT", 1}		//1byte
		};


		
		//open out .asm file
		ifstream asmFile(fileN, ios::in);
		fileName = fileN;
		fileName = fileName.substr(0, fileName.find(".asm"));
		fileName.append(".bin");

		//create binary output file
		ofstream binFile(fileName, ios::out | ios::binary);


		regex commentNL("^\\s*\\;");
		regex label("^(\\w*)(\\S?)\\s*(\.?\\w*)");	//match any words and capture any letters that are invalid
		regex chkBegLabel("^[^\\s\\w]"); //check the beginning of the the label for any invalid characters

		bool firstInstr = true;


		//check if file was opened correctly
		if (!asmFile.is_open()) {
			cout << "Error in opening the file" << endl;
			//using exit to exit the program
			exit(0);
		}

		smatch labelVal;

		//Pass 1
		while (!asmFile.eof()) {
			getline(asmFile, parseLine);
			lineNum++;
			regex_search(parseLine, labelVal, label);
			try {
				if (regex_search(parseLine, commentNL) || parseLine.size() == 0) {	//skip the line since its a comment or empty line
				}
				else if (labelVal[1] != "" || directives.count(labelVal[3]) > 0) {

					//check if an invalid character was used in the label name
					if (labelVal[2] != "") {
						//throw an exception message saying that an invalid character was used for the label
						throw invalid_argument("Labels may only contain alpha-numeric and underscore characters");
					}

					//check if label is a directive
					if (directives.count(labelVal[3]) > 0 && labelVal[1] != "") {
						if (directives.at(labelVal[3]) == 1) {
							//directive is a .BYT so increment offset by 1
							symbolTable.insert({ labelVal[1], offset });
							offset++;
						}
						else {
							//directive is a .INT so increment offset by 4
							symbolTable.insert({ labelVal[1], offset });
							offset += 4;
						}
					}
					else if (directives.count(labelVal[3]) > 0) {
						//no label given, so we just increment by the correct offset and dont insert it into our symbol table
						if (directives.at(labelVal[3]) == 1) {
							//directive is a .BYT so increment offset by 1
							
							offset++;
						}
						else {
							//directive is a .INT so increment offset by 4
							
							offset += 4;
						}
					}
					else {
						//label holds an instruction so we need to offset by 12
						symbolTable.insert({ labelVal[1], offset });
						offset += 12;
					}
				}
				else {
					//check if nonlabel character appeared at the beginning of the label, if there even exists a label in the line
					if (regex_search(parseLine, chkBegLabel)) {
						//throw exception: incorrect characters used for label.
						throw invalid_argument("Labels may only contain alpha-numeric and underscore characters");
					}

					//there is no label but line holds an instruction
					if (firstInstr == true) {	//this is the first time we have detected an instruction
						pc = offset;
						//change firstInstr to false so we dont override the pc after its set
						firstInstr = false;
					}

					offset += 12;
				}
			}
			catch (const invalid_argument& z) {
				cout << "Line Number " << lineNum << ": " << z.what() << endl;
				exit(0);
			}
		}

		offset = 0;
		//clear the eof bit and reset it to the beginning 
		asmFile.clear();
		asmFile.seekg(0, ios::beg);
		//set lineNum back to zero 
		lineNum = 0;
		//write pc to bin file
		binFile.write((char*)&pc, sizeof(int));	//write four bytes to the bin file
		//increment offset by four 
		offset += 4;

		smatch tokens;
		smatch labelToks;
		//lineParser will parse a line from .asm file to its proper tokens
		regex lineParser("^\\w*\\s*(\.?\\w*)?\\s*[#']?(\\w*\,?\\s*)?\'?[#']?(-?\\w*)");
		//labelParser will parse the tokens for labels
		regex labelParser("^\\w*\\s*(\.?\\w*)?\\s*(#{1}(-?\\w*))?('{1}(\\S?\\w*\\s?\\S?)?'{1})?");
		//pass2
		while (!asmFile.eof()) {
			getline(asmFile, parseLine);
			lineNum++;
			try {
				if (regex_search(parseLine, commentNL) || parseLine.size() == 0) {	//skip the line since its a comment or empty line
				}
				else if (regex_search(parseLine, tokens, lineParser)) {

					if (directives.count(tokens[1]) > 0 && regex_search(parseLine, labelToks, labelParser)) {
						//labelToks will hold the right possible arguments allowed for a directive 
						//checked if tokens[1] is a directive



						if (directives.at(labelToks[1]) == 4) {
							//directive is a .INT
							//set operand 1 to the decimal value capturing group labelToks[2]

							operand1 = labelToks[3];
							//parse out the #
							//operand1 = operand1.substr(0, operand1.find("#"));
							if (operand1 == "") {
								//nothing was given for operand 1 so we set charRep to be 0 which is what will be written to file
								charRep = 0;
							}
							else {
								//if decimal numbers were provided for operand 1 then set charRep to the decimal value obtained from stoi(operand1)
								charRep = stoi(operand1);
							}
							//write to binFile 4 bytes for allocation of .INT directive, then increment offset by 4
							binFile.write((char*)&charRep, sizeof(int));
							offset += 4;
						}
						else {
							//since we already checked to see that token[1] is a directive then we know its a .BYT
							//set operand 1 to the byte capturing group labelToks[3]
							operand1 = labelToks[5];

							charRep = int(operand1[0]);

							//check if only one byte was provided
							if (operand1.size() > 1) {
								//check for special character
								if (operand1 == "\\n") {
									charRep = 10;
								}
								else if (operand1 == "\\t") {
									charRep = 8;
								}
								else {
									//throw an exception saying that .byt only allocates one byte, you provided more than one byte to store
									throw invalid_argument("Provided more than one byte to store, .BYT only allocates space for one byte");
								}


							}
							else {
								//set charRep to the int value of the byte value provided
								charRep = int(operand1[0]);
							}
							binFile.write((char*)&charRep, sizeof(char));	//write to binFile size of char which is 1 byte, then increment offset by 1
							offset++;
						}
					}
					else {
						//line is an instruction
						try {
							//checkToks() will validate syntax and pass back the the int representation of opcode, operand1, and operand2
							binValues = syntaxCheck.checkToks(tokens[1], tokens[2], tokens[3], symbolTable);
						}
						catch (const invalid_argument& y) {
							//checkToks() throws any errors this catch statement will capture it and provide helpful feedback to user
							cout << "Line Number " << lineNum << ": " << y.what() << endl;
							exit(0);
						}

						//write to file 4 bytes three times, each token/value of binValues takes up 4 bytes
						binFile.write((char*)&get<0>(*binValues), sizeof(int)); //write opcode to binFile
						binFile.write((char*)&get<1>(*binValues), sizeof(int));	//write operand1 to binFile
						binFile.write((char*)&get<2>(*binValues), sizeof(int));	//write operand2 to binFile
						offset += 12;	//increment offset by 12
					}
				}
				else {
					//if program reaches here then there was an error in parsing the string
					throw logic_error("Error occured when parsing a line from the .asm file");
				}
			}
			catch (const invalid_argument& x) {
				cout << "Line Number " << lineNum << ": " << x.what() << endl;
				exit(0);
			}
		}
		//reset the eof() bit
		asmFile.clear();
		//close the bin file
		binFile.close();
}



#endif
