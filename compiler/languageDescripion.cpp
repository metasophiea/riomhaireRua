struct languageDescription{
    int commandLength;
    int maxProgramLength;
    int worktopSize;
    int byteSize;   //hex digit count
    int numberMode; //0 - dec, 1 - hex

    std::vector<std::string> commands;
    std::vector<std::string> tagableCommands;
    std::vector< std::vector<std::string> > commandDetails;
    // tag, bit, byte, long
};

languageDescription loadDescription(unsigned int languageNumber){
    languageDescription rua;
    std::vector<std::string> commandDetails_tempVector;
    std::vector<std::string> commandDetails_splitVector;

    switch(languageNumber){
        case 1: //rua.1
            rua.commandLength    = 5;
            rua.maxProgramLength = 256;
            rua.worktopSize      = 256;
            rua.byteSize         = 2;
            rua.numberMode       = 1;

            rua.commands.push_back("nop");
                commandDetails_tempVector = std::vector<std::string>();
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("goto");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("tag");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("ifbitflow");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("bit");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("clear");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("flip");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("inc");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("lrotate");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("copy");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("nand");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("add");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
        break;
        case 2: //rua.2
            rua.commandLength    = 5;
            rua.maxProgramLength = 65536;
            rua.worktopSize      = 256;
            rua.byteSize         = 2;
            rua.numberMode       = 1;
            
            rua.commands.push_back("nop");
                commandDetails_tempVector = std::vector<std::string>();
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("goto");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("tag");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("ifbitflow");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("bit");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("ifbitskip");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("bit");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("clear");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("set");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("flip");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("inc");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("dec");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("lrotate");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("rrotate");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("copy");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("nand");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("add");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
        break;
        case 3: //rua.3
            rua.commandLength    = 6;
            rua.maxProgramLength = 65536;
            rua.worktopSize      = 256;
            rua.byteSize         = 2;
            rua.numberMode       = 1;

            rua.commands.push_back("nop");
                commandDetails_tempVector = std::vector<std::string>();
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("goto");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("tag");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("ifbitflow");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("bit");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("ifbitskip");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("bit");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("wait");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("long");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("clear");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("set");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("neg");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("flip");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("inc");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("dec");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("lrotate");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("rrotate");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("copy");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("and");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("nand");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("or");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("nor");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("xor");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("add");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
            rua.commands.push_back("sub");
                commandDetails_tempVector = std::vector<std::string>();
                commandDetails_tempVector.push_back("byte");
                commandDetails_tempVector.push_back("byte");
                rua.commandDetails.push_back(commandDetails_tempVector);
        break;
        case 4: //rua.4
            rua.maxProgramLength = 65536;
            rua.worktopSize      = 256;
            rua.numberMode       = 0;

            std::string desc[] = {
                "nop",
                "goto:location",
                "wait:time",
                "ifBitSet:byte:bit:location",
                "ifResultZero:location",
                "ifResultOverflow:location",
                "ifResultUnderflow:location",
                "ifResultNegative:location",
                "ifSAMmode:location",
                "setBit:byte:bit:value",
                "clear:byte",
                "flip:byte",
                "lRotate:byte",
                "rRotate:byte",
                "copy:byte:destinationByte",
                "and:byte:byte:destinationByte",
                "nand:byte:byte:destinationByte",
                "or:byte:byte:destinationByte",
                "nor:byte:byte:destinationByte",
                "xor:byte:byte:destinationByte",
                "mode:value",
                "convert:byte:inputMode:outputMode",
                "set:byte:value",
                "inc:byte",
                "dec:byte",
                "neg:byte",
                "add:byte:byte:destinationByte",
                "sub:byte:byte:destinationByte"
            };

            for(unsigned int a = 0; a < sizeof(desc)/sizeof(*desc); a++){
                //split up line
                    commandDetails_splitVector = splitString(desc[a],':');
                //add lead command to commands list
                    rua.commands.push_back(commandDetails_splitVector[0]);
                //add command details to commandDetails
                    commandDetails_tempVector = std::vector<std::string>();
                    for(unsigned int b = 1; b < commandDetails_splitVector.size(); b++){ 
                        commandDetails_tempVector.push_back( commandDetails_splitVector[b] );
                    }
                    rua.commandDetails.push_back(commandDetails_tempVector);

                //determine if command is tagAble, and add to the tagableCommands list if it is
                    if( std::find( commandDetails_tempVector.begin(), commandDetails_tempVector.end(), "location" ) != commandDetails_tempVector.end() ){
                        tagableCommands.push_back( commandDetails_splitVector[0] );
                    }

            }

        break;
    }

    // std::cout << "language selected: " << languageNumber << std::endl;
    // std::cout << "- instructions -" << std::endl;
    // for(unsigned int a = 0; a < rua.commands.size(); a++){
    //     if( languageNumber < 4){ std::cout << UINTtoHEX(a) << " | " << rua.commands[a] << std::endl; }
    //     else{ std::cout << a << " | " << rua.commands[a] << std::endl; }
    //     std::cout << "\t";
    //     for(unsigned int b = 0; b < rua.commandDetails[a].size(); b++){ std::cout << rua.commandDetails[a][b] << " "; }
    //     std::cout << std::endl;
    // }

    return rua;
}



