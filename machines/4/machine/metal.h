#ifndef _INCL_GUARD_metal
#define _INCL_GUARD_metal

class metal{
    private:
        unsigned int bitSize;
        unsigned int maxPossibleValue;

    public:
        //construction/destruction
            metal(unsigned int bitSize);
            virtual ~metal();

        //getters
            virtual unsigned int getBitSize();
            virtual unsigned int getMaxPossibleValue();

        //converters
            virtual std::string UINTtoHEX(unsigned int UINT);
            virtual std::string UINTtoHEX_systemSize(unsigned int UINT);
            virtual unsigned int HEXtoUINT(std::string HEX);
            virtual std::string UINTtoBIN(unsigned int UINT);
            virtual std::string UINTtoBIN_systemSize(unsigned int UINT);
            virtual unsigned int BINtoUINT(std::string BIN);
            virtual unsigned int BINtoUINT(bool BIN[]);

        //adjusters/getters
            virtual bool getBitFromUINT(unsigned int UINT, unsigned int bit);
            virtual std::string adjustBIN(std::string BIN, unsigned int bit, bool value);
            virtual std::string resize(std::string val, unsigned int byteSize);
};

#endif