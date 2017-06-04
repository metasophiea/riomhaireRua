//goes through program looking for comments and blank lines to remove
std::vector<std::string> commentHandler(std::vector<std::string> program){
    unsigned int lineCount = 0;

    //loop through the code looking for / symbols and blank lines
    for(unsigned int a = 0; a < program.size(); a++){
        if(program[a][0] == '/'){
            if(program[a][1] != '/'){ std::cout << "lone comment slash: " << std::endl << lineCount << " | "<< program[a] << std::endl; return std::vector<std::string>(); }
            program.erase(program.begin()+a); a--;
        }
        else if( program[a].length() == 0){ program.erase(program.begin()+a); a--; }
        lineCount++;
    }

    return program;
}