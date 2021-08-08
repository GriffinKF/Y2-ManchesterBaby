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
#include <iomanip>
#include <string>

#include "../utilities.h"

using namespace std;

class Simulator
{

    // the memory addresses
    vector<string> store;

    // stores the calculations
    int accumulator = 0;

    int storeSize = 16;

    // control instruction
    int CI = 0;

    // program instruction
    string PI;
public:
    Simulator();

    Simulator(int);


    // Store functions
    int insert(string, int);
    int reset();
    string retrieveFunction(int);
    string retrieveAddress(int, bool);
    int returnValue(int);

    string getInstruction() { return PI; }

    vector<string> getStore()
    {
        vector<string> store1 = store;

        return store1;
    }
    void incCI() { CI++; }

    int getCI()
    {
        return CI;
    }

    string getPI()
    {
        return PI;
    }

    int setCI(int input);
    int setPI(string input);

    int getAcc()
    {
        return accumulator;
    }

    int setAcc(int);

    int LDN(string);
    int SUB(int);
    int MLT(int); // multiplcation - accumulator * content of store address
    int DIV(int); // division - accumulator / content of store address
    int MOD(int); // modulo - accumulator % content of store address
    int POW(int); // exponent - accumulator ^ content of store address
    int INC(); // increment - accumulator + 1
    int DEC(); // decrement - accumulator - 1

    void printStore(); // prints the store
    void printBinaryStore();
    int findLongestCell(); // finds the longest string size in the store for formatting
};

/*
* Constructor of Simulator
* Sets store size to 16
*/
Simulator::Simulator()
{
    CI = 0;
    store.resize(16);
}

/*
* Constructor of Simulator
* @param int Sets store size to input
*/
Simulator::Simulator(int input)
{
    CI = 0;
    store.resize(input);
}

/*
* Retrieves the function of the store at index
* @param int index of line to use
* @return string Value of the function
*/
string Simulator::retrieveFunction(int index)
{ 
    string temp ="";
    if (store.at(index).length() > 0) {
        temp += to_string(toDecimal(store.at(index).substr(13,16)));
    } else {
        temp = "";
    }
    return temp; 
}

/*
* Retrieves the address of the store at index
* @param int index of line to use
* @return string Value of the address
*/
string Simulator::retrieveAddress(int index, bool isVar)
{
    // checks if the address exists in store
    if (index > int(store.size())) {
        return "Error when collecting data from store";
    }

    string temp = "";

    if (isVar) {
        string value = store.at(index);
        temp += to_string(toDecimal(value.substr(0,31)));
    } else {
        temp += to_string(toDecimal(store.at(index).substr(0,5)));
    }

    return temp; 
}

/*
* Retrieves the value of the store at address
* @param int address to access
* @return int returns the value at address 
*/
int Simulator::returnValue(int address)
{
    return toDecimal(store.at(address));
}

/*
* Modifies the value into store
* @param string input binary value to insert into store
* @param int address to store binary value at
* @return int validity of modfication
*/
int Simulator::insert(string value, int address)
{
    // checks if the address exists in store
    if (address > int(store.size())) {
        cout << "Not in range" << endl;
        return 1;
    }
    
    // setting value at inputted address
    store.at(address) = value;
    return 0;
}

/*
* Modifies the value of CI
* @param int new value of CI
* @return int the validity of inserting the new CI
*/
int Simulator::setCI(int newCI)
{
    // checks validity of CI
    if (newCI < 0) {
        return 1;
    }

    cout << "Setting CI to: " << newCI << endl
         << endl;

    // setting CI
    CI = newCI;

    // returning validity
    return 0;
}


/*
* Sets the value of the accumulator
* @param int new value of Accumulator
* @return int the validity of modifying the accumulator
*/
int Simulator::setAcc(int newAcc)
{
    cout << "Setting Acc to: " << newAcc << endl
         << endl;

    // setting new value of accumulator
    accumulator = newAcc;
    return 0;
}

/*
* Modifies the value of PI
* @param string line of binary to retrieve new PI
* @return int the validity of changing PI
*/
int Simulator::setPI(string input)
{
    cout << endl;
    cout << "Setting PI to: " << input << endl
         << endl;
    PI = "";
    PI += input;
    return 0;
}

/*
* Sets the accumulator to the negation of the value of input
* @param string binary of new value
* @return int the validity of modifying the value of accumulator
*/
int Simulator::LDN(string input)
{
    // multiplies the new value by -1 and assigns to accumulator
    setAcc((returnValue(stoi(input)) * -1));
    return 0;
}

/*
* Subtracts the inputted value from the current accumulator value
* @param int value to subtract from accumulator
* @return int the validity of modifying the accumulator
*/
int Simulator::SUB(int input)
{
    accumulator -= returnValue(input);
    return 0;
}

/*
* Multiplies the accumulator by the inputted value
* @param int value to multiply the accumulator by
* @return int the validity of modifying the accumulator
*/
int Simulator::MLT(int input)
{
    cout << "Multiplying Accumulator: " << accumulator << " by " << returnValue(input) << endl;

    int temp = accumulator;
    for (int i = 0; i < returnValue(input)-1; i++)
    {
        accumulator +=temp;
    }

    return 0;
}

/*
* Divides the accumulator by the inputted value
* @param int value to divide the accumulator by
* @return the validity of modifying the accumulator
*/
int Simulator::DIV(int input)
{
    cout << "Dividing Accumulator: " << accumulator << " by " << returnValue(input) << endl;
    accumulator = int(round(accumulator/ returnValue(input))); 
    return 0;
}

/*
* Modulos the accumulator by the inputted value
* @param int value to modulo the accumulator by
* @return int the validity of modifying the accumulator
*/
int Simulator::MOD(int input)
{
    cout << "Finding modulo " << returnValue(input) << " of Accumulator: " << accumulator << endl;
    
    int mod = returnValue(input);
    int temp = accumulator;
    if (temp < 0)
    {
        temp = temp * -1;
    }
    while ((temp - mod) > 0)
    {
        temp = temp - mod;
    }
    accumulator = temp;

    return 0;
}

/*
* Finds the value of the accumulator to the power of the inputted value
* @param int value of exponent to raise the accumulator by
* @return int the validity of modifying the accumulator
*/
int Simulator::POW(int input)
{
    cout << "Finding Accumulator: " << accumulator << " to the power of "  << returnValue(input)  << endl;
    if (accumulator < 0) {
        accumulator *= -1;
    }
    int mantissa = accumulator;
    int exponent = returnValue(input);
    cout << "This is the mantissa " << mantissa << "&" << exponent << endl;
    for (int i = 0; i < exponent-1; i++)
    {
        mantissa = mantissa * accumulator;
        cout << "H: " << mantissa << endl;
    }

    accumulator = mantissa;
    
    return 0;
}

/*
* Increments the accumulator by 1
* @return int the validity of incrementing the accumulator
*/
int Simulator::INC()
{
    accumulator++;
    return 0;
}

/*
* Decrementing the accumulator by 1
* @return int the validity of decrementing the accumulator
*/
int Simulator::DEC()
{
    accumulator--;
    return 0;
}

/*
* Finds the longest cell in the store to set the width of each cell, for formatting purposes
* @return int the length of the longest cell
*/
int Simulator::findLongestCell()
{
    // initialises length to 4
    int length = 4;

    for (int i = 0; i < int(store.size()); i++) {
        int current = int(store.at(i).length());
        // checks if current is longer than the existing longest cell
        if (current > length) {
            length = current;
        } 
    }

    return length;
}

/*
* Prints the current store in decimal format
*/
void Simulator::printStore()
{
    cout << endl;
    cout << "\033[4;36mStore\033[0m\n";
    int longest = findLongestCell();
    bool isVar = false;
    for (int i = 0; i < int(store.size()); i++)
    {
        
        if ((i % 4) == 0 && i > 0)
        {
            cout << endl << endl;
        }
        if (store.at(i) != "")
        {
            if (isVar) {
                cout << std::left << "\033[42;30m" << setw(longest) << toDecimal(store.at(i)) << "\033[0m";
            } else {
                cout << std::left << "\033[42;30m" << setw(longest) << retrieveFunction(i) + ":" + retrieveAddress(i, false) <<  "\033[0m";
            }
        }
        else
        {
            cout << std::left << "\033[4;40;30m" << setw(longest) << "." << "\033[0m";
        }
        cout << "  ";
        if (retrieveFunction(i) == "7") {
            isVar = true;
        }
    }

    cout << endl << endl;;
}

/*
* Prints the current store in binary format
*/
void Simulator::printBinaryStore()
{
    bool isVar = false;
    for (int i = 0; i < int(store.size()); i++)
    {
        if (store.at(i) != "")
        {
            cout << i << " == " << retrieveAddress(i, isVar) << endl;
        } else
        {
           cout << i << " == NULL" << endl;
        }
            if (retrieveFunction(i).compare("7") == 0) {
                isVar = true;
            }
     }
}