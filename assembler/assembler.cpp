/*
Ramsay Sewell - 170012517
Brandon Clark - 180009209
Taha Kashaf - 180020889
Elisaveta Peeva - 180012881
Preslav Chonev - 180007405
AC21009
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <bits/stdc++.h>

using namespace std;

int globalEnd = 0;
int startFound = 0;

//This method is mostly validation of the .txt file. Checks for certain things like the start and end statements, and performs the very important function of globally saving what line 'END' appears on, as this is critical for other functions.
bool lables(vector<vector<string> > vect, int checkFor){
    if (checkFor == 1){
    	cout << endl;
    	cout << "Currently searching for the START statement in the assembly code." << endl;
        int inputsDotSize = vect.size();
        for (int i = 0; i < inputsDotSize; i++){
            int lineSize = vect[i].size();
            for (int j = 0; j < lineSize ; j++){
                if (vect[i][j] == "START:"){
                	cout << "Successfully found the START statement in the assembly code." << endl;
                	startFound = i;
                    return true;
                }
            }
        }
        cout << "Did not find the START statement" << endl;
        return false;

    } else if (checkFor == 2){
    	cout << endl;
    	cout << "Currently searching for the END statement in the assembly code." << endl;
        int inputsDotSize = vect.size();
        for (int i = 0; i < inputsDotSize; i++){
            int lineSize = vect[i].size();
            for (int j = 0; j < lineSize ; j++){
                if (vect[i][j] == "END:"){
                	cout << "Successfully found the END statement in the assembly code." << endl;
                    globalEnd = i;
                	return true;
                }
            }
        }
        cout << "Did not find the END statement" << endl;
        return false;

    } else if (checkFor == 3){
    	cout << endl;
    	cout << "Currently searching for the | VAR 0 | statement in the assembly code." << endl;
    	if (startFound != 0){
    		int lineSize = vect[startFound-1].size();
    		for (int k = 0; k < lineSize;k++){
    			if (vect[startFound-1][k] == "VAR"){
    				if (k != 0){
    					if (vect[startFound-1][k-1] == "0"){
    						cout << "Successfully found the | VAR 0 | statement in the assembly code." << endl;
    						return true;
    					}	
    				} else {
    					cout << "Did not detect the | VAR 0 | statement line in the assembly code." << endl;
    					return false;
    				}
    			}
    		}
    	}
    }
	cout << "Did not detect the | VAR 0 | statement line in the assembly code" << endl;
    return false;
}

//This method is used to convert the actual `instructions' to there relevant machine code output - this includes extra codes that we have implemented and defined.
string command(string command) {
	string codes[14] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP", "MLT", "DIV", "MOD", "POW", "INC", "DEC"};
	string codesMachine[14] = {"0000000000000000000", "1000000000000000000", "0100000000000000000", "1100000000000000000", "0010000000000000000", "1010000000000000000", "0110000000000000000", "00000000000001110000000000000000", "0001000000000000000", "1001000000000000000", "0101000000000000000", "1101000000000000000", "0011000000000000000", "1011000000000000000"};
	for (int i = 0; i < 8; i++) {
		//cout << codes[i] << endl;
		if (command == codes[i]) {
			return codesMachine[i];
		}
	}
	cout << "Incorrect Assembly Language Input, Terminating Compiler" << endl;
	return "error";
}

//This is a simple method that converts a decimal passed too it, into binary. The binary is in big-endian format, with it's length defined by the passed "bit length."
string decToBin(string dec, int bitLength){
	
	int stringSize = dec.size();
	string returnMe;
	
	for (int i = 0; i < stringSize; i++) {
		if (isdigit(dec[i]) != 0) {
			continue;
		} else {
			// returnMe = "00000000000000000000000000000000";
			// cout << "Invalid Variable: " << dec << " | Storing 0 instead." << endl;
			cout << "Invalid Variable: " << dec << " | Compiling terminate, incorrect variable type (expected an integer)." << endl;
			return "error";
		}
	}

	int intDec = stoi(dec);

	while(intDec != 0) {
		returnMe = (intDec%2 == 0 ?"0":"1") + returnMe;
		intDec /= 2;
	}

	reverse(returnMe.begin(), returnMe.end());
	
	int returnMeDotSize = returnMe.size();
	while (returnMeDotSize != bitLength) {
		returnMe = returnMe + "0";
		returnMeDotSize = returnMe.size();
	}
	
	// cout << returnMe << endl;
	return returnMe;
}

//This method takes the lines of actual 'Assembly Instructions' (the stuff between start and end) and processes them to the relevant machine code output. 
string lineConvert(vector<vector<string>> vect, vector<string> cLine) {
	int vectSize = vect.size();
	string finalString;
	string comBinary;

	if (cLine.size() > 2) {
		if(cLine[2] != "START:") {
			cout << "Incorrect Assembly Language Input (Too many intructions on one line)" << endl;
			return "error";
		}
	}

	for(int i = globalEnd+1; i < vectSize; i++) {
		size_t pos = vect[i][2].find(cLine[0]);
		if (pos != string::npos){

			string temping = cLine[0] + ":";
			// cout << vect[i][2] << endl;
			// cout << temping << endl;
			if (vect[i][2] == temping){
			} else {
				return "error";
			}

			// cout << i << endl;
			cout << "Calculating the correct memory address to which the first variable is being assigned." << endl;
			finalString = decToBin(to_string(i), 13);
			break;
		} else if (cLine[0] == "STP") {
			cout << endl;
			cout << "The assembler has detected a STP instruction in the assembly code. All intructions compliled correctly. (First pass completed)" << endl;
			return "00000000000001110000000000000000";
		} else if (i == vectSize - 1) {
			cout << "Incorrect Assembly Language Input" << endl;
			return "error";
		}
		cout << endl;
	}

	for(int i = globalEnd+1; i < vectSize; i++) {
		if (cLine[1] == "STP") {
			cout << endl;
			cout << "The assembler has detected a STP instruction in the assembly code. All intructions compliled correctly. (First pass completed)" << endl;
			return "00000000000001110000000000000000";
		} else {
			// cout << cLine[1] << endl;
			cout << "The assemblar is processing the instruction sets given in the assembly code." << endl;
			comBinary = command(cLine[1]);
			if (comBinary != "error") {
				// SDASSADSADSADSA
				finalString = finalString + comBinary;
				cout << "No errors detected in the assembly code - line succesfully compiled.";
				return finalString;
			} else {
				cout << endl;
				return "error";
			}
		}
		cout << endl;
	}

	return "error";
}

//The parsing method serves two functions. It opens a user defined file and then "parses" the assembly language in the file. Parsing meaning finding key statements such as start and end, VAR 0, and the variable definitions. It pases parsed string lines into the other methods to be processed.
int parse(string fileName){
    
    vector <vector<string> > inputs;
    ifstream lineReader;
    string line;
    string subsStr;
    string delimiter = " ";
    size_t pos = 0;
    bool comment;
    lineReader.open(fileName);
    if (lineReader.is_open()){
        while (getline(lineReader, line)){
            comment = false;
            vector <string> temp;

            while ((pos = line.find(delimiter)) != string::npos){
                subsStr = line.substr(0,pos);
                if (subsStr == ";"){
                    comment = true;
                }

                if (comment != true){
                    if ( subsStr != ""){
                        // cout << subsStr << "-";
                        temp.insert(temp.begin(),subsStr);
                    }    
                } 
                line.erase(0, pos + delimiter.length());
            }
            
            if (comment == true){
            	// cout << "GOOD" << endl;
            	if (temp.empty()){
            		// cout << "BAD" << endl;
            		continue;
            	}
                inputs.push_back(temp);
                // cout << endl;
                continue;
            } else {
                // cout << line << endl;
                temp.insert(temp.begin(),line);
                inputs.push_back(temp);
            }
        }
    } else {
		lineReader.close();
		return 1;
	}

    int inputsDotSize = inputs.size();
    cout << "How the assembler sees the assembly language code from the .txt file (Comments removed)." << endl;
    cout << endl;
    cout << "==================================" << endl;
    for (int i = 0; i < inputsDotSize; i++){
    	int lineSize = inputs[i].size();
    	for (int j = 0; j < lineSize ; j++){
    	// cout << inputs[i][j] << " - ";
    		cout << inputs[i][j] << " ";
			// cout << int(inputs[i][j][0]);
    	}
    	cout << endl;
    }
    cout << "==================================" << endl;
 
    ofstream myfile;
    myfile.open("assembler/machineCode.txt");

    if (lables(inputs, 1) && lables(inputs, 2) && lables(inputs, 3)){
    	// cout << "PROCEED" << endl;
    	myfile << "00000000000000000000000000000000" << endl;
    } else {
    	return 1;
    }

    cout << endl;
    cout << endl;


    // Writing to a file
    
    if( ! myfile ) {
    	cerr << "Error opening file for output" << endl;
    }
    
    for(int i = 1; i < globalEnd + 1; i++) {
    	string tempString = lineConvert(inputs, inputs[i]);
    	if (tempString == "error") {
    		cout << "An error was detected at an earlier stage of compiling, assembler will not continue" << endl;
    		cout << endl;
    		return 1;
    	}
    	// cout << tempString << endl;
    	myfile << tempString << endl;
    	cout << endl;

    }
    for(int n = globalEnd + 1; n < inputsDotSize; n++) {
    	//inputs[n][0] needs validating.
		if (inputs[n].size() < 2){
			cout << "Error detected with the assembly code (Incorrect format of the assembly file)." << endl;
			return 1;
		}
    	if (inputs[n][1] != "VAR"){
    		cout << "The assembly code is not declaring variables correctly. Terminating Compiler." << endl;
    		cout << endl;
    		return 1;
    	}
    	string tempString2 = decToBin(inputs[n][0], 32); 
    	if (tempString2 == "error"){
    		cout << "An error was detected at an earlier stage of compiling, assembler will not continue" << endl;
    		cout << endl;
    		return 1;
    	}
    	cout << "No errors detected in compiling the variable statement." << endl;

    	// cout << tempString2<< endl;
    	myfile << tempString2 << endl;
    }
    cout << endl;
    cout << "No errors detected in compiling any of the variable statements (Second Pass Completed)." << endl;
    cout << endl;
    cout << "=======================================" << endl;
    cout << "Full Compilation Completed Successfully" << endl;
    cout << "=======================================" << endl;
    myfile.close();



    return 0;

}



