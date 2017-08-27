std::vector<std::string> compiler(std::vector<std::string> program, languageDescription rua, std::string inputFileFolder){
    //set up error handler
        errorHandler errorHandler;
        errorHandler.importMainProgram(program);
 
    //check for imports and do imports
        //find file (stop if can't be found)
        //paste text in from where this import was
        //remove import command
    program = importHandler(program,inputFileFolder,errorHandler); 
    if(program.empty()){
        std::cout << "compilation failed - import issue" << std::endl;
        return std::vector<std::string>();
    }

    //check for comments, tabs/spacing and blank lines; and remove
        //look for slash
        //no second slash -> stop
    program = commentHandler(program,errorHandler); 
    if(program.empty()){
        std::cout << "compilation failed - comment issue" << std::endl;
        return std::vector<std::string>();
    }

    //tags
        //find tag
        //add tag name to list with corresponding line number
        //remove tag
        //if line number is larger than maxProgramLength -> stop
        //go through code again, replace goto:X tags with line numbers (in apropiate number format) from tag list
    switch(rua.numberMode){
        case 0: program = tagHandler_dec(program,rua,errorHandler); break;
        case 1: program = tagHandler_hex(program,rua,errorHandler); break;
    }
    if(program.empty()){
        std::cout << "compilation failed - tagging issue" << std::endl;
        return std::vector<std::string>();
    }  

    //check if resulting code is too long; if so stop
    if( program.size() >= rua.maxProgramLength ){
        std::cout << "compilation failed - program too long" << std::endl;
        std::cout << program.size() << "/" << rua.maxProgramLength << std::endl;
        return std::vector<std::string>();
    }

    //convert to byte code
        //unknown command -> stop
        //adjust numbers to suit architecture
        //command references byte beyond memorySize -> stop
    switch(rua.numberMode){
        case 0: program = conversionHandler_dec(program,rua,errorHandler); break;
        case 1: program = conversionHandler_hex(program,rua,errorHandler); break;
    }
    if(program.empty()){
        std::cout << "compilation failed - conversion issue" << std::endl;
        return std::vector<std::string>();
    }

    return program;
}