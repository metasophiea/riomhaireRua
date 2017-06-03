// std::string syntaxCheck_import(std::string code){return "";}

// std::string syntaxCheck(std::vector<std::string> program){
//     std::string syntaxCheckResult = ""; std::string temp;
//     std::string syntaxErrorOpener;

//     for(unsigned a = 0; a < program.size(); a++){
//         syntaxErrorOpener = "syntax error on line: " + std::to_string(a) +  "\n\"" + program[a] + "\"\n";

//         //test compiler directives
//             switch(program[a][0]){
//                 case '/':
//                     /*check for second slash*/ if(program[a][1] != '/'){ return syntaxErrorOpener + "second slash missing"; }
//                 break;
//                 case ':':
//                     /*check for second colonlash*/ if(program[a][1] != ':'){ return syntaxErrorOpener + "second colon missing"; } 
//                     /*check that tag name is valid*/ 
//                         temp = program[a];
//                         temp.erase(0,2);
//                         std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
//                         if      (   temp.compare("nop")         ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("goto")        ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("ifbitflow")   ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("clear")       ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("flip")        ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("inc")         ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("lshift")      ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("copy")        ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("nand")        ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.compare("add")         ){ return syntaxErrorOpener + ""; }
//                         else if (   temp.find(" ")              ){ return syntaxErrorOpener + "can't use space in tag"; }
//                 break;
//                 case '#': temp = syntaxCheck_import(program[a]); if(!temp.empty()){std::cout << temp << std::endl;} break;
//             }


//     }


//     return syntaxCheckResult;
// }