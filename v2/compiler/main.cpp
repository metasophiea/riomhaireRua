#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "errorHandler.h"

#include "importHandler.cpp"
#include "commentHandler.cpp"
#include "tagHandler.cpp"
#include "conversionHandler.cpp"
#include "compiler.cpp"

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

    //compile
        //// globals: maxProgramLength, memorySize, byteSize
        unsigned int maxProgramLength = 65536;
        unsigned int memorySize = 256;
        unsigned int byteSize = 8;

        program = compiler(program,maxProgramLength,memorySize,byteSize,inputFileFolder); if(program.empty()){ return 0; }

    //print program
        //look to see if output file name has been provided; if so; use that name and place it back in the folder
        //if not; take the original name, attach '.rua' and place it back in the folder
        if(outputFileName.length() != 0){ outputFileName = inputFileFolder + outputFileName;  }
        else{ outputFileName = inputFileName + ".rua"; }

        //printing
        FILE* output = fopen((outputFileName).c_str(), "w");
        for(unsigned int a = 0; a < program.size(); a++){
            for(unsigned int b = 0; b < program[a].length(); b++){ fprintf(output, "%c", program[a][b]); }
            if( a < program.size()-1 ){ fprintf(output, "%c", '\n'); }
        }

    return 0;
}