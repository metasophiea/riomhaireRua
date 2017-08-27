# Rua compiler | Python Edition
import sys

def errorHandler(type,program,line):
    for l in program:
        if line in l:
            break


    sys.exit( type + " error with on line: " + str(program.index(l)+1) + " -> \"" + line + "\"")



# setup jobs
    # check that inputs are present
        # input arguments: exe, code file, output file name
    # load in description
    # load in program
rawProgram = []
workingProgram = []
file_obj = open("countFromZeroToNine.rua")
for line in file_obj:
    rawProgram.append(line)
    line = line.replace("\n","").rstrip().lstrip() # little bit of cleaning
    if len(line) != 0:
        workingProgram.append(line)
file_obj.close()

# compile jobs
    # check for imports and do imports
    #     find file (stop if can't be found)
    #     paste text in from where this import was
    #     remove import command

    # check for comments, tabs/spacing and blank lines; and remove
    #     look for slash
    #     no second slash -> stop
for line in workingProgram:
    index = line.find("/")
    if index != -1:
        if line[index+1] != "/":
            errorHandler("Comment",rawProgram,line)
        else:
            workingProgram.remove(line)

    # tags
    #     find tag
    #     add tag name to list with corresponding line number
    #     remove tag
    #     if line number is larger than maxProgramLength -> stop
    #     go through code again, replace goto:X tags with line numbers (in apropiate number format) from tag list

    # check if resulting code is too long; if so stop

    # convert to byte code

# aftermath jobs
    # look to see if output file name has been provided; if so; use that name and place it back in the folder if not; take the original name, attach '.rr' and place it back in the folder
    # printing