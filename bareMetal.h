#ifndef _INCL_GUARD_bareMetal
#define _INCL_GUARD_bareMetal

class bareMetal{
    private:
        unsigned int bitCount;

    public:
        virtual std::string UINTtoHEX(unsigned int UINT);
        virtual unsigned int HEXtoUINT(std::string HEX);
        virtual std::string BINtoHEX(std::string BIN);
        virtual std::string HEXtoBIN(std::string HEX);
        virtual unsigned int BINtoUINT(std::string BIN);
        virtual std::string UINTtoBIN(unsigned int UINT);

        virtual std::string localSizeHex(std::string HEX);
        virtual std::string localSizeBIN(std::string BIN);
        virtual int checkForComplyingLength(std::string HEX);

        virtual unsigned int getBitCount();

    public:
        bareMetal(unsigned int bitCount);
        virtual ~bareMetal();
};

#endif