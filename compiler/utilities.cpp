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

std::string localSizeHex(std::string HEX, unsigned int byteSize){
    if(HEX.length() == byteSize){return HEX;}
    else if( HEX.length() < byteSize ){
        for(unsigned int a = HEX.length(); a < byteSize; a++){ HEX = "0" + HEX; }
        return HEX;
    }
    else{
        std::string returnHEX;
        for(unsigned int a = 0; a < byteSize; a++){ returnHEX += HEX[ HEX.length()-a-1  ]; }
        return returnHEX;
    }
}

std::vector<std::string> splitString(std::string line, char split){
    std::vector<std::string> output; std::string temp;

    for(unsigned int a = 0; a < line.length(); a++){
        if(line[a] == split){ 
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            output.push_back(temp); 
            temp = ""; }
        else{ temp += line[a]; }
    }

    output.push_back(temp);
    return output;
}