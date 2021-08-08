/*
Ramsay Sewell - 170012517
Brandon Clark - 180009209
Taha Kashaf - 180020889
Elisaveta Peeva - 180012881
Preslav Chonev - 180007405
AC21009
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
* Converts binary to decimal and handles negative numbers when last bit is 1
* @return int the decimal value of binary
*/
int toDecimal(string binary)
{
    int total = 0;

    if (binary[0] == '0') {
        total = 0;
    } else {
        total += 1;
    }

    for (int i = 1; i < int(binary.length()) - 1; i++)
    {
        if (binary[i] == '1')
        {
            total += pow(2, i);
        }
    }

    // if the last bit is 1 then the total will be negated
    if (binary.size() == 31) {
        if (binary.back() == '1') {
            total *= -1;
        }
    }

    return total;
}

string toBinary(int decimal) {
    int binaryArr[32] = {0};
    string binary = "";

    bool negative = false;
    if (decimal < 0) {
        negative = true;
        decimal = decimal * -1;
    }

    for(int i=0; decimal>0; i++)    
    {    
        binaryArr[i]=decimal%2;    
        decimal = decimal/2;  
    }

    for (int i = 0; i < 30; i++) {
        binary += to_string(binaryArr[i]);
    }

    if (negative) {
        binary += '1';
    } else {
        binary += '0';
    }

    cout << endl;


    return binary;
}

/*
* Gets input from user for menu
* @return int the validated integer value from the user
*/
int getIntInput()
{

    //init input variable
    string input = "";
    bool isInt = false;

    do
    {
        cin >> input; //Gets input from user

        int inputLength = input.length();

        // Goes through the string by input to make sure each character is a digit and not a char
        for (int i = 0; i < inputLength; i++)
        {

            if (!isdigit(input[i])) // Check for digit
            {
                cout << "INVALID INPUT - PLEASE ENTER A VALID NUMBER" << endl;
                break;
            }
            else
            {
                isInt = true;
            }
        }

    } while (!isInt);

    // cout << typeid(input).name() << endl;

    return atoi(input.c_str()); //Converts input to integer and returns it
}

#endif