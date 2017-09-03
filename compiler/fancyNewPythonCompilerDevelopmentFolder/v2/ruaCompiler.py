def gatherTextFromFile(fileName):
    text = []
    try:
        file_obj = open(fileName)
    except FileNotFoundError:
        # these errors are handled elsewhere
        pass
    else:
        for line in file_obj:
            line = line.replace("\n","").rstrip().lstrip() # little bit of cleaning
            text.append(line)
        file_obj.close()
    return text








def cleanCode(code):
    outputCode = []
    for line in code:
        if len(line) != 0:
            outputCode.append(line)

    return outputCode








def errorHandler(type, offendingLine="", isTest=False):
    errorString = ""
    if offendingLine == "":
        errorString = type
    else:
        bail = False
        for file in errorHandler.files:
            file_obj = open(file)

            for index,line in enumerate(file_obj):
                line = line.replace("\n","")
                if line == offendingLine:
                    errorString = type + " : \"" + file + "\" : " + str(index) + " : " + offendingLine
                    bail = True
                    break

                if bail:
                    break

            file_obj.close()

    if isTest:
        return errorString
    else:
        print(errorString)
        exit()

errorHandler.files = []



