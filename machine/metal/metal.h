#ifndef _INCL_GUARD_metal
#define _INCL_GUARD_metal

class metal{
    private:
        bool debugMode;
        unsigned int bitSize;
        unsigned int maxPossibleValue_abs;
        unsigned int maxPossibleValue_sam;

    public:
        //construction/destruction
            metal(unsigned int bitSize);
            virtual ~metal();

        //getters
            virtual unsigned int getBitSize();
            virtual unsigned int getMaxPossibleValue(int mode);

        //converters
            virtual std::string UINTtoANYTHING(unsigned int UINT, char outputChars[], unsigned int outputCharsLength);
            virtual unsigned int ANYTHINGtoUINT(std::string ANYTHING, char outputChars[], unsigned int outputCharsLength);

            virtual std::string UINTtoHEX(unsigned int UINT);
            virtual std::string UINTtoHEX_systemSize(unsigned int UINT);
            virtual unsigned int HEXtoUINT(std::string HEX);
            virtual std::string UINTtoBIN(unsigned int UINT);
            virtual std::string UINTtoBIN_systemSize(unsigned int UINT);
            virtual unsigned int BINtoUINT(std::string BIN);
            virtual std::string UINTtoDEC(unsigned int UINT);
            virtual std::string UINTtoDEC_systemSize(unsigned int UINT);
            virtual unsigned int DECtoUINT(std::string DEC);

        //adjusters/getters
            virtual bool getBitFromUINT(unsigned int UINT, unsigned int bit);
            virtual std::string adjustBIN(std::string BIN, unsigned int bit, bool value);
            virtual unsigned int bitAdjustUINT_systemSize(unsigned int UINT, unsigned int bit, bool value);
            virtual std::string resize(std::string val, unsigned int byteSize);

        //printers and debug
            virtual void printMemory();
            virtual void debug(bool onOff);
};

#endif