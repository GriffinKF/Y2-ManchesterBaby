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
#include <string>

// including classes and utility methods
#include "simulator.h"
#include "../utilities.h"

using namespace std;

class cSimulator
{
public:

    // initialising filename
    string fileName = "";

    cSimulator()
    {
        // default binary file
        fileName = "fetch/Addition.txt";
    };

    cSimulator(string input)
    {
        // creating new simulator using the inputted file path
        fileName = "fetch/";
        fileName += input;
    };

    /*
    * sets the filename for the simulator
    * @param string inputted filename
    * @return int validity of setting the filename
    */
    int setFileName(string input)
    {
        // resetting the filename for the simulator
        fileName = input;

        return 0;
    }

    /*
    * Sets the store size of the simulator
    * @param int new size of store
    * @return int inputted new store size
    */
    int setStoreSize(int fileSize)
    {
        int input = 16;
        cout << "Enter a number above 16: ";
        input = getIntInput();

        // makes sure that filesize is greater than or equal to 16
        if (input < fileSize)
        {
            cout << "Input less than number of lines in file, adjusting memory to accommodate for file. ";
            input = fileSize + 1;
        }

        if (input < 16)
        {
            cout << endl
                 << "Less than 16, setting to default of 16";
            input = 16;
        }
        cout << endl;
        return input;
    }

    /*
    * Runs the simulator
    * @return int validity of running code
    */
    int run()
    {

        // initialises variables for reading lines
        ifstream lineReader;
        string line;
        int no_Lines = 0;
        vector<string> lines;

        // Reads each line into a vector to then be processed further
        cout << "This is the file: " << fileName << endl;
        lineReader.open(fileName);
        if (lineReader.is_open())
        {

            while (getline(lineReader, line))
            {
                lines.push_back(line);
                no_Lines++;
            }
        }
        else
        {
            lineReader.close();
            return 1;
        }

        lineReader.close();

        // loops through each lines checking if line contains non-digit characters
        for (int i = 0; i < int(lines.size()); i++)
        {
            for (int j = 0; j < int(lines.at(i).length() - 1); j++)
            {
                if (lines.at(i)[j] != '0' && lines.at(i)[j] != '1' && lines.at(i)[j] != '\n')
                {
                    cout << "Error at line " << i << ", character " << j << ". Character " << lines.at(i)[j] << " not valid." << endl;
                    return 1;
                }
            }
        }


        // new Simulator instance
        Simulator *sim = new Simulator(setStoreSize(no_Lines));

        // goes through each line, checking if the line contains an instruction or a variable
        for (int i = 0; i < int(lines.size()); i++)
        {

           sim->insert(lines.at(i),i);
        }

        // initialises the function
        int function = 8;

        while (function != 7)
        {
            // Increments the Control Instruction
            sim->incCI();
      
            // Sets the program instruction to the instruction and address
            sim->setPI(sim->retrieveFunction(sim->getCI()));
            
            // Outputs the current CI, PI and ACC.
            cout << "\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n";

            cout << "\033[37mAcc: " << sim->getAcc() << "\033[0m";
            cout << "   \033[32mPI: " << sim->getPI() << "\033[0m";
            cout << "   \033[33mCI: " << sim->getCI() << "\033[0m\n\n";

            // Prints the store
            sim->printStore();

            cout << "\n\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n";

            // Sets the instruction to function, for example 1
            function = stoi(sim->getInstruction());

            // Checks what the function is, and the different cases
            switch (function)
            {
            case 0:
                cout << "JMP-ing CI to " << sim->retrieveAddress(sim->getCI(),false) << "." << endl;
               sim->setCI(stoi(sim->retrieveAddress(sim->getCI(),false)));
                break;
            case 1:
                cout << "JRP-ing by setting the address: " << sim->retrieveAddress(sim->getCI(),false) 
                << " to value " << sim->getAcc() << endl;
                if(sim->insert(to_string(sim->getAcc()), stoi(sim->retrieveAddress(sim->getCI(), false)))) {
                    exit(1);
                }
                break;
            case 2:
                cout << "LDN-ing setting the Accumulator to the value at address " << sim->retrieveAddress(sim->getCI(), false) << "." << endl;
                if (sim->LDN(sim->retrieveAddress(sim->getCI(), false))) {
                    exit(1);
                }
                break;
            case 3:
                cout << "Storing the accumulator in position " << sim->retrieveAddress(sim->getCI(),false) << "." << endl;
                if(sim->insert(toBinary(sim->getAcc()), stoi(sim->retrieveAddress(sim->getCI(), false)))) {
                    exit(1);
                }
                break;
            case 4:
                cout << "Subtracting Accumulator(" << sim->getAcc() << ") by " << sim->retrieveAddress(sim->getCI(), false) << "." << endl;
                if(sim->SUB(stoi(sim->retrieveAddress(sim->getCI(), false)))) {
                    exit(1);
                }
                break;
            case 5:
                cout << "Subtracting Accumulator(" << sim->getAcc() << ") by " << sim->retrieveAddress(sim->getCI(), false) << "." << endl;
                if(sim->SUB(stoi(sim->retrieveAddress(sim->getCI(), false)))) {
                    exit(1);
                }
                break;
            case 6:
                cout << "Checking if accumulator is negative... ";
                // checks if accumulator is negative and increments
                if (sim->getAcc() < 0)
                {
                    cout << "Incrementing accumulator by 1" << endl;
                    sim->incCI();
                }
                cout << "No need to incrememnt accumulator by 1" << endl;
                break;
            case 7:
                cout << "\033[1;32m"
                     << "Program has completed successfully."
                     << "\033[0m\n";
                sim->printStore();
                break;
             case 8:
                cout << "Multiplying accumulator(" << sim->getAcc() << ") by " << sim->retrieveAddress(sim->getCI(), false)  << "." << endl;
                // Multiplcation - accumulator * content of store address
                sim->MLT(stoi(sim->retrieveAddress(sim->getCI(), false)));
                break;
            case 9:
                cout << "Dividing accumulator(" << sim->getAcc() << ") by " << sim->retrieveAddress(sim->getCI(), false) << "." << endl;
                // Division - accumulator / content of store address
                 sim->DIV(stoi(sim->retrieveAddress(sim->getCI(), false)));
                break;
            case 10: 
                cout << "Getting mod " << sim->retrieveAddress(sim->getCI(), false) << " of accumulator(" << sim->getAcc() << ")."  << endl;
                // Modulo - accumulator % content of store address
                sim->MOD(stoi(sim->retrieveAddress(sim->getCI(), false)));
                break;
            case 11: 
                cout << "Finding accumulator(" << sim->getAcc() << ") to the power of " << sim->retrieveAddress(sim->getCI(), false) << endl;
                // Exponent - accumulator ^ content of store address
                sim->POW(stoi(sim->retrieveAddress(sim->getCI(), false)));
                break;
            case 12:
                cout << "Incrementing accumulator" <<endl;
                // Increment - accumulator + 1
                sim->INC();
                break;
            case 13:
                cout << "Decrementing accumulator" << endl;
                // Decrement - accumulator -1
                sim->DEC();
                break;
            default:
                cout << "\033[1;31m" << "Program has NOT completed successfully." << "\033[0m\n";
                return 1;
                break; 
            }
            
            string key;
            cout << "Press any key and Enter/Return to continue:  ";
            cin >> key;
            cout << endl;
            cin.clear();


        } 
    return 0;
}
};