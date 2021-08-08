/*
Ramsay Sewell - 170012517
Brandon Clark - 180009209
Taha Kashaf - 180020889
Elisaveta Peeva - 180012881
Preslav Chonev - 180007405
AC21009
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include "fetch/simulator.cpp"
#include "assembler/assembler.cpp"
#include "utilities.h"

using namespace std;

void displayMenu();

int main()
{
    // initialising variables for menu
    cSimulator cSim;
    string input;
    int result = 6; 
    int parseOut;

    while (true)
    {
        displayMenu(); // display the menu

        result = getIntInput(); // store input from keyboard inside variable

        switch (result)
        {
        case 1:
            cout << "Option 1 selected" << endl; // Runs simulator using "BabyTest1-MC.txt"
            cSim = cSimulator();
            if (cSim.run() == 1)
            {
                cout << "File cannot be found, try again..." << endl;
            }
            break;
        case 2:
            cout << "Option 2 selected" << endl << endl; // Runs simulator using user selected file
            cout << "To include files, place in the fetch folder" << endl;
            cout << "Example files included: " << endl;
            cout << "Addition.txt -- Adds two numbers together" << endl;
            cout << "Subtraction.txt -- Subtracts one number from another" << endl;
            cout << "Additional.txt -- Displays the use of aditional instructions" << endl << endl;

            cout << "Input a filename:";
            cin >> input;
            cout << endl;
            cSim = cSimulator(input);
            if (cSim.run() == 1)
            {
                cout << "File cannot be found, try again..." << endl;
            }
            break;
        case 3:
            cout << "Option 3 selected" << endl; // Compiles "Atest_file.txt" from assembly language into machine code
            parseOut = parse("assembler/Atest_file.txt");
            if (parseOut == 1)
            {
                cout << "An error occured with the code." << endl;
            };     
            break;
        case 4:
            cout << "Option 4 selected" << endl << endl; // Compiles user selected file from assembly language into machine code
             cout << "To include files, place in the assembler folder" << endl;
            cout << "Example files included: " << endl;
            cout << "Atest_file.txt -- Adds two numbers together" << endl;
            cout << "Atest_file2.txt -- Subtracts one number from another" << endl << endl;;
            cout << "Input a filename:";
            cin >> input;
            cout << endl;
             parseOut =  parse("assembler/"+input);
            if (parseOut == 1)
            {
                cout << "An error occured with the code." << endl;
            };
            break;
        case 5:
            cout << "Option 5 selected" << endl; // Exits program
            exit(0);
            break;
        default:
            cout << "Invalid input. Try again" << endl;
            break;
        }
    }
}

/*
* Prints the menu options
*/
void displayMenu()
{
    // print the instructions
    cout << "Please select an option ('basic' refers to default program) " << endl;
    cout << "1. Simulate a basic program using machine code" << endl;
    cout << "2. Simulate another program using machine code" << endl;
    cout << "3. Compile basic program from assembly code" << endl;
    cout << "4. Compile another program from assembly code" << endl;
    cout << "5. Exit Program" << endl;
}