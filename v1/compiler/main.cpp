#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
//#include <algorithm>
//#include <regex>

#include "importHandler.cpp"
#include "commentHandler.cpp"
#include "tagHandler.cpp"

int main(int argumentCount, char *arguments[]){    
    std::string inputFileName, outputFileName, inputFileFolder;

    //input checking and collection
        switch(argumentCount){
            case 0: case 1:  std::cout << "compiler failed to start - elements missing from argument" << std::endl; return 1; break;
            case 2: inputFileName = arguments[1]; inputFileFolder = importHandler_extractFolderAddress(arguments[1]); break;
            case 3: default: inputFileName = arguments[1]; outputFileName = arguments[2]; inputFileFolder = importHandler_extractFolderAddress(arguments[1]); break;
        }

    //load in program
        std::vector<std::string> program;
        std::ifstream inputFile(inputFileName); std::string line;
        while(getline( inputFile, line )){ program.push_back(line); }


    //// globals: maxProgramLength, memorySize
    unsigned int maxProgramLength = 256;

    //check for imports and do imports
        //find file (stop if can't be found)
        //paste text in from where this import was
        //remove import command
    program = importHandler(program,inputFileFolder); if(program.empty()){
        std::cout << "compilation failed - import issue" << std::endl;
        return 1;
    }

    //check for comments and blank lines; and remove
        //look for slash
        //no second slash -> stop
    program = commentHandler(program); if(program.empty()){
        std::cout << "compilation failed - comment issue" << std::endl;
        return 1;
    }

    //tags
        //find tag
        //add tag name to list with corrisponding line number
        //remove tag
        //if line number is larger than maxProgramLength -> stop
        //go through code again, replace goto:X tags with line numbers (in HEX) from tag list
    program = tagHandler(program); if(program.empty()){
        std::cout << "compilation failed - tagging issue" << std::endl;
        return 1;
    }  

    //check if resulting code is too long; if so stop
    if( program.size() >= maxProgramLength ){
        std::cout << "compilation failed - program too long" << std::endl;
        std::cout << program.size() << "/" << maxProgramLength << std::endl;
        return 1;
    }
    //convert to byte code
        //unknown command -> stop
        //adjust hex number to suit architecture
        //command references file beyond memorySize -> stop

    std::cout << std::endl << " -result- " << std::endl;
    for(unsigned int a = 0; a < program.size(); a++){
        std::cout << program[a] << std::endl;
    }

    return 0;
}