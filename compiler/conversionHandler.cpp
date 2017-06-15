std::vector<std::string> conversionHandler(std::vector<std::string> program, languageDescription rua, errorHandler errorHandler){
    std::vector<std::string> thisCommand, result; 
    std::string temp;

    for(unsigned int a = 0; a < program.size(); a++){
        thisCommand = splitString(program[a],':');

        for(unsigned int b = 0; b < rua.commands.size(); b++){
            if( thisCommand[0].compare(rua.commands[b]) == 0 ){//legal command, push to result
                //get command number
                    temp = localSizeHex( UINTtoHEX(b), UINTtoHEX(rua.commands.size()).length() );

                //write in arguments
                    for(unsigned int c = 0; c < rua.commandDetails[b].size(); c++){
                        if(      rua.commandDetails[b][c].compare("tag")  == 0 ){ temp += localSizeHex(thisCommand[c+1],UINTtoHEX(rua.maxProgramLength-1).length()); }
                        else if( rua.commandDetails[b][c].compare("bit")  == 0 ){ temp += localSizeHex(thisCommand[c+1],rua.byteSize);   }
                        else if( rua.commandDetails[b][c].compare("byte") == 0 ){ temp += localSizeHex(thisCommand[c+1],rua.byteSize);   }
                        else if( rua.commandDetails[b][c].compare("long") == 0 ){ temp += localSizeHex(thisCommand[c+1], (rua.commandLength - temp.length()) ); }
                    }

                //expand command to regular size
                    while(temp.length() < rua.commandLength){ temp += "0"; }

                //push
                    result.push_back(temp);
                    break;
            }
            if( b+1 == rua.commands.size() ){ errorHandler.reportError("unknown command",program[a]); return std::vector<std::string>(); }
        }

    }

    return result;
}