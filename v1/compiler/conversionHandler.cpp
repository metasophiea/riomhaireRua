std::string localSizeHex(std::string HEX, unsigned int byteSize){
    if(HEX.length() == byteSize/4){return HEX;}
    else if( HEX.length() < byteSize/4 ){
        for(unsigned int a = HEX.length(); a < byteSize/4; a++){ HEX = "0" + HEX; }
        return HEX;
    }
    else{
        std::string returnHEX;
        for(unsigned int a = 0; a < byteSize/4; a++){ returnHEX += HEX[ HEX.length()-a-1  ]; }
        return returnHEX;
    }
}

bool testForHexNumber(std::string number){
    for(unsigned int a = 0; a < number.length(); a++){
		switch(number[a]){
			case '0': 			break;
			case '1': 			break;
			case '2': 			break;
			case '3': 			break;
			case '4': 			break;
			case '5': 			break;
			case '6': 			break;
			case '7': 			break;
			case '8': 			break;
			case '9': 			break;
			case 'a': case 'A': break;
			case 'b': case 'B': break;
			case 'c': case 'C': break;
			case 'd': case 'D': break;
			case 'e': case 'E': break;
			case 'f': case 'F': break;
            default: return false; break;
		}
    }
    return true;
}

std::vector<std::string> splitString(std::string line){
    std::vector<std::string> output; std::string temp;

    for(unsigned int a = 0; a < line.length(); a++){
        if(line[a] == ':'){ 
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            output.push_back(temp); 
            temp = ""; }
        else{ temp += line[a]; }
    }

    output.push_back(temp);
    return output;
}

std::vector<std::string> conversionHandler(std::vector<std::string> program, unsigned int byteSize, errorHandler errorHandler){
    std::vector<std::string> thisCommand, result; 
    std::string temp;

    for(unsigned int a = 0; a < program.size(); a++){
        thisCommand = splitString(program[a]);
        if( thisCommand.size() > 3 ){ errorHandler.reportError("unknown command",program[a]); return std::vector<std::string>(); }
        if( thisCommand.size() > 1 ){ if( !testForHexNumber(thisCommand[1]) ){ errorHandler.reportError("unknown command",program[a]); return std::vector<std::string>(); } }
        if( thisCommand.size() > 2 ){ if( !testForHexNumber(thisCommand[2]) ){ errorHandler.reportError("unknown command",program[a]); return std::vector<std::string>(); } }

        if(     thisCommand[0].find("nop") != std::string::npos         ){ temp = "00000"; }
        else if(thisCommand[0].find("goto") != std::string::npos        ){ temp = "1" + localSizeHex(thisCommand[1],byteSize) + "00"; }
        else if(thisCommand[0].find("ifbitflow") != std::string::npos   ){ temp = "2" + localSizeHex(thisCommand[1],byteSize) + localSizeHex(thisCommand[2],byteSize);}
        else if(thisCommand[0].find("clear") != std::string::npos       ){ temp = "3" + localSizeHex(thisCommand[1],byteSize) + "00"; }
        else if(thisCommand[0].find("flip") != std::string::npos        ){ temp = "4" + localSizeHex(thisCommand[1],byteSize) + "00"; }
        else if(thisCommand[0].find("inc") != std::string::npos         ){ temp = "5" + localSizeHex(thisCommand[1],byteSize) + "00"; }
        else if(thisCommand[0].find("lshift") != std::string::npos      ){ temp = "6" + localSizeHex(thisCommand[1],byteSize) + "00"; }
        else if(thisCommand[0].find("copy") != std::string::npos        ){ temp = "7" + localSizeHex(thisCommand[1],byteSize) + localSizeHex(thisCommand[2],byteSize);}
        else if(thisCommand[0].find("nand") != std::string::npos        ){ temp = "8" + localSizeHex(thisCommand[1],byteSize) + localSizeHex(thisCommand[2],byteSize);}
        else if(thisCommand[0].find("add") != std::string::npos         ){ temp = "9" + localSizeHex(thisCommand[1],byteSize) + localSizeHex(thisCommand[2],byteSize);}
        else{ errorHandler.reportError("unknown command",program[a]); return std::vector<std::string>(); }

        result.push_back(temp);
    }

    return result;
}