#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "utilities.cpp"
#include "languageDescripion.cpp"
#include "errorHandler.h"

#include "importHandler.cpp"
#include "commentHandler.cpp"
#include "tagHandler.cpp"
#include "conversionHandler.cpp"
#include "compiler.cpp"

int main(int argumentCount, char *arguments[]){
    std::string inputFileName, outputFileName, inputFileFolder;

    //check that inputs are present
        //input arguments: exe, code file, output file name
        if( argumentCount != 3 ){ std::cout << "compiler failed to start - elements missing from argument" << std::endl; return 1; }
        inputFileName = arguments[1]; inputFileFolder = importHandler_extractFolderAddress(arguments[1]);
        outputFileName = arguments[2]; 
        
    //load in description
        languageDescription rua = loadDescription(4);

    //load in program
        std::vector<std::string> program;
        std::ifstream inputFile(inputFileName); std::string line;
        while(getline( inputFile, line )){ program.push_back(line); }

    //compile
        program = compiler(program,rua,inputFileFolder); if(program.empty()){ return 0; }

    //print program
        //look to see if output file name has been provided; if so; use that name and place it back in the folder
        //if not; take the original name, attach '.rr' and place it back in the folder
        if(outputFileName.length() != 0){ outputFileName = inputFileFolder + outputFileName;  }
        else{ outputFileName = inputFileName + ".rr"; }

        //printing
        FILE* output = fopen((outputFileName).c_str(), "w");
        for(unsigned int a = 0; a < program.size(); a++){
            for(unsigned int b = 0; b < program[a].length(); b++){ fprintf(output, "%c", program[a][b]); }
            if( a < program.size()-1 ){ fprintf(output, "%c", '\n'); }
        }

    return 0;
}