#ifndef _INCL_GUARD_metal
#define _INCL_GUARD_metal

class metal{
    private:
        unsigned int bitSize;

    public:
        metal(unsigned int bitSize);
        virtual ~metal();

        virtual unsigned int getBitSize();

        virtual std::string UINTtoHEX(unsigned int UINT);
        virtual unsigned int HEXtoUINT(std::string HEX);
        virtual std::string resizeHex(std::string HEX, unsigned int byteSize);
};

#endif