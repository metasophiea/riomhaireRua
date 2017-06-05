#ifndef _INCL_GUARD_errorHandler
#define _INCL_GUARD_errorHandler

class errorHandler{
    private:
        static std::vector<std::string> mainProgram;
        static std::vector<std::string> includedFiles;
        void printLineAndFileName(std::string line, bool multiSearch = false);
        std::vector<std::string> getFile(std::string fileName);

    public:
        virtual void importMainProgram(std::vector<std::string> program);
        virtual void addFile(std::string fileAddress);
        virtual void reportError(std::string errorMessage, std::string offendingLine, bool multiSearch = false);

    public:
        errorHandler();
        virtual ~errorHandler();
};

#endif