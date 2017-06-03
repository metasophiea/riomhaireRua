#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

#include "syntaxChecker.cpp"

int main(int argumentCount, char *arguments[]){    
    std::string inputFileName, outputFileName;

    //input checking and collection
        switch(argumentCount){
            case 0: case 1:  std::cout << "compiler failed to start - elements missing from argument" << std::endl; return 1; break;
            case 2: inputFileName = arguments[1]; break;
            case 3: default: inputFileName = arguments[1]; outputFileName = arguments[2]; break;
        }

    //load in program
        std::vector<std::string> program;
        std::ifstream inputFile(inputFileName); std::string line;
        while(getline( inputFile, line )){ program.push_back(line); }


    //// globals: maxProgramLength, memorySize
    //check for imports and do imports
        //remove import command
        //find file (stop if can't be found)
        //paste text in from where this import was
    //check for comments and blank lines; and remove
        //look for slash
        //no second slash -> stop
    //tags
        //sequentially
            //find tag
            //remove tag
            //add tag name to list with corrisponding line number
            //if line number is larger than maxProgramLength -> stop
    //check if resulting code is too long; if so stop
    //convert to byte code
        //unknown command -> stop
        //command references file beyond memorySize -> stop
        //replace goto:X tags with line numbers (in HEX) from tag list

    return 0;
}