std::vector<std::string> tagHandler_hex(std::vector<std::string> program, languageDescription rua, errorHandler errorHandler){
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

std::vector<std::string> tagHandler_dec(std::vector<std::string> program, languageDescription rua, errorHandler errorHandler){
    std::unordered_map <std::string, unsigned int> tagMap;
    std::string tempString;
    std::vector<std::string> tempVector;
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

    //go through code looking for taggable commands, replacing tags with the proper number
    for(unsigned int a = 0; a < program.size(); a++){
        tempVector = splitString(program[a],':');

        //detect if command is on the list of commands that use tags
        for(unsigned int b = 0; b < rua.tagableCommands.size(); b++){ if( tempVector[0].compare(rua.tagableCommands[b]) == 0 ){
            //extract tag
                tempString = tempVector[rua.tagableCommandArgumentPosition[b]+1];
            //check if tag is on tag list
                if(tagMap.find(tempString) == tagMap.end()){ errorHandler.reportError("unknown tag",program[a]); return std::vector<std::string>(); }
            //replace tag with the actual location number
                tempVector[rua.tagableCommandArgumentPosition[b]+1] = std::to_string(tagMap[tempString]);
            //put the vector back together and push
                program[a] = combineVector(tempVector,":");

        } }
    }

    return program;
}