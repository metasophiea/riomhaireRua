struct languageDescription{
    int commandLength;
    int maxProgramLength;
    int worktopSize;
    int byteSize;

    std::vector<std::string> commands;
    std::vector< std::vector<std::string> > commandDetails;
    // tag, bit, byte, long
};

languageDescription loadDescription(unsigned int languageNumber){
    languageDescription rua;
    std::vector<std::string> temp;

    switch(languageNumber){
        case 1: //rua.1
            rua.commandLength    = 5;
            rua.maxProgramLength = 256;
            rua.worktopSize      = 256;
            rua.byteSize         = 2; //hex digit count

            rua.commands.push_back("nop");
                temp = std::vector<std::string>();
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("goto");
                temp = std::vector<std::string>();
                temp.push_back("tag");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("ifbitflow");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("bit");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("clear");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("flip");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("inc");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("lrotate");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("copy");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("nand");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("add");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
        break;
        case 2: //rua.2
            rua.commandLength    = 5;
            rua.maxProgramLength = 65536;
            rua.worktopSize      = 256;
            rua.byteSize         = 2; //hex digit count
            
            rua.commands.push_back("nop");
                temp = std::vector<std::string>();
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("goto");
                temp = std::vector<std::string>();
                temp.push_back("tag");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("ifbitflow");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("bit");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("ifbitskip");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("bit");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("clear");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("set");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("flip");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("inc");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("dec");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("lrotate");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("rrotate");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("copy");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("nand");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("add");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
        break;
        case 3: //rua.3
            rua.commandLength    = 6;
            rua.maxProgramLength = 65536;
            rua.worktopSize      = 256;
            rua.byteSize         = 2; //hex digit count

            rua.commands.push_back("nop");
                temp = std::vector<std::string>();
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("goto");
                temp = std::vector<std::string>();
                temp.push_back("tag");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("ifbitflow");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("bit");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("ifbitskip");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("bit");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("wait");
                temp = std::vector<std::string>();
                temp.push_back("long");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("clear");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("set");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("neg");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("flip");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("inc");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("dec");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("lrotate");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("rrotate");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("copy");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("and");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("nand");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("or");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("nor");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("xor");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("add");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
            rua.commands.push_back("sub");
                temp = std::vector<std::string>();
                temp.push_back("byte");
                temp.push_back("byte");
                rua.commandDetails.push_back(temp);
        break;
    }

    // std::cout << "language selected: " << languageNumber << std::endl;
    // std::cout << "- instructions -" << std::endl;
    // for(unsigned int a = 0; a < rua.commands.size(); a++){
    //     std::cout << UINTtoHEX(a) << " | " << rua.commands[a] << std::endl;
    //     std::cout << "\t";
    //     for(unsigned int b = 0; b < rua.commandDetails[a].size(); b++){
    //         std::cout << rua.commandDetails[a][b] << " ";
    //     }std::cout << std::endl;
    // }

    return rua;
}



