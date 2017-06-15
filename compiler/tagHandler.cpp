std::vector<std::string> tagHandler(std::vector<std::string> program, errorHandler errorHandler){
    std::unordered_map <std::string, unsigned int> tagMap;
    std::string tempString;
    unsigned int lineCount = 0;

    //go through code and populate unordered_map
    for(unsigned int a = 0; a < program.size(); a++){
        if(program[a][0] == ':'){
            //check if there are two colons and no spaces
                if(program[a][1] != ':'){ errorHandler.reportError("lone tag colon",program[a]); return std::vector<std::string>(); }
                if( program[a].find(' ') != std::string::npos ){ errorHandler.reportError("no spaces allowed in tags",program[a]); return std::vector<std::string>(); }
            //check if tag already exists
                tempString = program[a]; tempString.erase(0,2);
                if(tagMap.find(tempString) != tagMap.end()){ errorHandler.reportError("duplicate tag",program[a],true); return std::vector<std::string>(); }
            //add tag to map
                tagMap[tempString] = a;
            //erase tag from code
                program.erase(program.begin()+a); a--;
        }
        lineCount++;
    }

    //go through code, replaceing goto tags
    for(unsigned int a = 0; a < program.size(); a++){
        if( program[a].find("goto") != std::string::npos ){
            //clean off 'goto:' bit, and see if this tag is on the list. If not; complain
                tempString = program[a]; tempString.erase(0,5);
                if(tagMap.find(tempString) == tagMap.end()){ errorHandler.reportError("unknown tag",program[a]); return std::vector<std::string>(); }
            //rewrite tag with actual line value in Hex
                program[a] = "goto:" + UINTtoHEX(tagMap[tempString]);
        }
    }

    return program;
}