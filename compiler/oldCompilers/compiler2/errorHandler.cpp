#include <iostream>
#include <fstream>
#include <vector>

#include "errorHandler.h"

errorHandler::errorHandler(){}
errorHandler::~errorHandler(){}

std::vector<std::string> errorHandler::mainProgram = std::vector<std::string>();
std::vector<std::string> errorHandler::includedFiles = std::vector<std::string>();

void errorHandler::importMainProgram(std::vector<std::string> program){ for(unsigned int a = 0; a < program.size(); a++){ mainProgram.push_back(program[a]); } }
void errorHandler::addFile(std::string fileAddress){ includedFiles.push_back(fileAddress); }
void errorHandler::reportError(std::string errorMessage, std::string offendingLine, bool multiSearch){
    std::cout << " -- error -- " << std::endl;
    std::cout << errorMessage << std::endl;
    printLineAndFileName(offendingLine,multiSearch);
    std::cout << "\"" << offendingLine << "\""  << std::endl;
    std::cout << std::endl;
}

std::vector<std::string> errorHandler::getFile(std::string fileName){
    std::vector<std::string> importProgram;
    std::ifstream inputFile(fileName); std::string line;
    while(getline( inputFile, line )){ importProgram.push_back(line); }
    return importProgram;
}

void errorHandler::printLineAndFileName(std::string line, bool multiSearch){
    std::string temp = "";

    //search through main program
        for(unsigned int a = 0; a < mainProgram.size(); a++){
            if( mainProgram[a].find(line) != std::string::npos ){
                std::cout << "line: " + std::to_string(a) + " of file: " + "main program"  << std::endl;
                if(!multiSearch){return;}
            }
        }

    //search through imported files
        std::vector<std::string> tempFile;
        for(unsigned int a = 0; a < includedFiles.size(); a++){
            tempFile = getFile(includedFiles[a]);
            for(unsigned int a = 0; a < tempFile.size(); a++){
                if( tempFile[a].find(line) != std::string::npos ){
                    std::cout << "line: " + std::to_string(a) + " of file: " << includedFiles[a] << std::endl;
                    if(!multiSearch){return;}
                }
            }
        }

}