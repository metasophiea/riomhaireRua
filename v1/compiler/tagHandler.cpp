std::string UINTtoHEX(unsigned int UINT){
	if(UINT == 0){ return "0";}

	std::string hexArray[] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
    std::string HEX = "";

    //find biggest pow
        unsigned int biggestPow = 0;
        while( biggestPow < 100 ){
            if( (unsigned int)(UINT/pow(16,(biggestPow))) == 0 ){break;} 
            biggestPow++;
        }
        
    //do conversion
        do{
            biggestPow--;
            HEX += hexArray[ (unsigned int)(UINT/pow(16,biggestPow)) ]; 
            UINT = UINT - (unsigned int)(UINT/pow(16,biggestPow)) * pow(16,biggestPow);
        }while( biggestPow != 0 && UINT > 0 );

    //add in remaining zeros
        while(biggestPow > 0){ biggestPow--; HEX += "0"; }

    return HEX;
}

std::vector<std::string> tagHandler(std::vector<std::string> program){
    std::unordered_map <std::string, unsigned int> tagMap;
    std::string tempString;
    unsigned int lineCount = 0;

    //go through code and populate unordered_map
    for(unsigned int a = 0; a < program.size(); a++){
        if(program[a][0] == ':'){
            //check if there are two colons and no spaces
                if(program[a][1] != ':'){ std::cout << "lone tag colon: " << std::endl << lineCount << " | "<< program[a] << std::endl; return std::vector<std::string>(); }
                if( program[a].find(' ') != std::string::npos ){ std::cout << "no spaces in tags: " << std::endl << lineCount << " | "<< program[a] << std::endl; return std::vector<std::string>(); }
            //check if tag already exists
                tempString = program[a]; tempString.erase(0,2);
                if(tagMap.find(tempString) != tagMap.end()){ std::cout << "duplicate tag: " << std::endl << lineCount-1 << " | "<< program[a] << std::endl; return std::vector<std::string>(); }
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
                if(tagMap.find(tempString) == tagMap.end()){ std::cout << "unknown tag: " << std::endl << program[a] << std::endl; return std::vector<std::string>(); }
            //rewrite tag with actual line value in Hex
                program[a] = "goto:" + UINTtoHEX(tagMap[tempString]);
        }
    }

    return program;
}