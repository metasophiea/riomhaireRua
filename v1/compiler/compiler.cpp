std::vector<std::string> compiler(std::vector<std::string> program, unsigned int maxProgramLength, unsigned int memorySize, unsigned int byteSize, std::string inputFileFolder){
    //set up error handler
        errorHandler errorHandler;
        errorHandler.importMainProgram(program);
 
    //check for imports and do imports
        //find file (stop if can't be found)
        //paste text in from where this import was
        //remove import command
    program = importHandler(program,inputFileFolder,errorHandler); if(program.empty()){
        std::cout << "compilation failed - import issue" << std::endl;
        return std::vector<std::string>();
    }

    //check for comments, tabs/spacing and blank lines; and remove
        //look for slash
        //no second slash -> stop
    program = commentHandler(program,errorHandler); if(program.empty()){
        std::cout << "compilation failed - comment issue" << std::endl;
        return std::vector<std::string>();
    }

    //tags
        //find tag
        //add tag name to list with corrisponding line number
        //remove tag
        //if line number is larger than maxProgramLength -> stop
        //go through code again, replace goto:X tags with line numbers (in HEX) from tag list
    program = tagHandler(program,errorHandler); if(program.empty()){
        std::cout << "compilation failed - tagging issue" << std::endl;
        return std::vector<std::string>();
    }  

    //check if resulting code is too long; if so stop
    if( program.size() >= maxProgramLength ){
        std::cout << "compilation failed - program too long" << std::endl;
        std::cout << program.size() << "/" << maxProgramLength << std::endl;
        return std::vector<std::string>();
    }

    //convert to byte code
        //unknown command -> stop
        //adjust hex number to suit architecture
        //command references file beyond memorySize -> stop
    program = conversionHandler(program,byteSize,errorHandler); if(program.empty()){
        std::cout << "compilation failed - conversion issue" << std::endl;
        return std::vector<std::string>();
    }

    return program;
}