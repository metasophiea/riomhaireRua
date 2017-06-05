//goes through program looking for comments and blank lines to remove
std::vector<std::string> commentHandler(std::vector<std::string> program, errorHandler errorHandler){
    unsigned int lineCount = 0; size_t temp;

    //loop through the code looking for / symbols and blank lines
    for(unsigned int a = 0; a < program.size(); a++){
        // std::cout << " - pass - " << std::endl;
        // for(unsigned int b = 0; b < program.size(); b++){
        //     std::cout << program[b] << std::endl;
        // }

        //check for comment
            temp = program[a].find("/");
            if( temp != std::string::npos ){
                if( program[a][temp+1] == '/' ){ program[a].erase(program[a].begin()+temp, program[a].end()); }
                else{ errorHandler.reportError("lone comment slash",program[a]); return std::vector<std::string>(); }
            }

        //removal of spaces and tabs
            temp = program[a].find(" ");
            while(temp != std::string::npos){
                program[a].erase(program[a].begin()+temp); 
                temp = program[a].find(" ");
            }

        //check for empty line
            if( program[a].length() == 0 ){ program.erase(program.begin()+a); a--; }

    }

    return program;
}