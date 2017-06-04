//looks at import code and works out where the file is in reality
std::string importHandler_extractFolderAddress(std::string mainFileAddress){
    while( mainFileAddress.length() > 0 && mainFileAddress[mainFileAddress.length()-1] != '/' ){ mainFileAddress.erase(mainFileAddress.length()-1,1); }
    return mainFileAddress;
}

//correct "fileName.rr" codes to actual file addresses
std::string importHandler_parseFileAddress(std::string fileName, std::string inputFileFolder){
    fileName.erase(0,1);
    if(fileName[0] == '.' || fileName[0] == '/'){ return fileName; }
    return inputFileFolder + fileName;
}

//check for file
bool importHandler_doesFileExist(std::string fileName){
    std::ifstream inputFile(fileName);
    return inputFile.good();
}

//get file, and return a vector of the code therein
std::vector<std::string> importHandler_getFile(std::string fileName){
    std::vector<std::string> importProgram;
    std::ifstream inputFile(fileName); std::string line;
    while(getline( inputFile, line )){ importProgram.push_back(line); }
    return importProgram;
}

//go through file, looking for import commands. When found; get the file and paste the code in place. Do so in a recursive manor
std::vector<std::string> importHandler(std::vector<std::string> program, std::string inputFileFolder, std::vector<std::string> importedFiles = std::vector<std::string>()){
    std::vector<std::string> tempVector; std::string tempString;
    unsigned int lineCount = 0;

    //loop through the code looking for # symbols
    for(unsigned int a = 0; a < program.size(); a++){
        if(program[a][0] == '#'){
            //parse file to have correct address
                tempString = importHandler_parseFileAddress(program[a],inputFileFolder);
            //check if file exists, if so import it. If not; complain and return empty vector
                if(!importHandler_doesFileExist(tempString)){ std::cout << "import file not found: " << std::endl << lineCount << " | "<< program[a] << std::endl; return std::vector<std::string>(); }
                tempVector = importHandler_getFile(tempString);
            //add file name to list of files already imported
                tempString = program[a]; 
                tempString.erase(0,1);
                importedFiles.push_back(tempString);
            //go through this file in a recursive manor to look for import code
                tempVector = importHandler(tempVector,inputFileFolder,importedFiles); if(tempVector.empty()){ std::cout << "error within imported file related to line " << lineCount << " in the file \"" << tempString << "\"" << std::endl; return std::vector<std::string>(); }
            //paste imported code into file
                std::vector<std::string>::iterator it = program.begin();
                program.insert(it+a+1, tempVector.begin(), tempVector.end());
            //remove import code
                program.erase(program.begin()+a); a--;
        }

        lineCount++;
    }

    return program;
}