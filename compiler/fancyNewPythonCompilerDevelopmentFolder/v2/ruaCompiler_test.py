import unittest, os
from ruaCompiler import *

class gatherTextFromFile_test(unittest.TestCase):
    testText = ["Hello there","hello again","","1234567890"]
    textFileName = "ruaCompiler_test_testFile"

    def setUp(self):
        file_obj = open(self.textFileName, "w")
        for line in self.testText:
            file_obj.write(line)
            file_obj.write("\n")
        file_obj.close()

    def tearDown(self):
        os.remove(self.textFileName)

    def testGathering(self):
        self.assertEqual(gatherTextFromFile(self.textFileName), self.testText)








class cleanCode_test(unittest.TestCase):

    def testCleaning(self):
        self.assertEqual( cleanCode(["Hello there","hello again","1234567890"]) , ["Hello there","hello again","1234567890"])
        self.assertEqual( cleanCode(["Hello there","hello again","","1234567890"]) , ["Hello there","hello again","1234567890"])








class errorHandler_test(unittest.TestCase):
    testText = ["Hello there","hello again","","1234567890"]
    textFileName = "./ruaCompiler_test_testFile"

    def setUp(self):
        file_obj = open(self.textFileName, "w")
        for line in self.testText:
            file_obj.write(line)
            file_obj.write("\n")
        file_obj.close()

        errorHandler.files.append(self.textFileName)

    def tearDown(self):
        os.remove(self.textFileName)
        errorHandler.files.remove(self.textFileName)

    def testErrorFinding(self):
        self.assertEqual( errorHandler("Standard Error","Hello there",True) , "Standard Error : \"./ruaCompiler_test_testFile\" : 0 : Hello there" )
        self.assertEqual( errorHandler("Standard Error","1234567890",True) , "Standard Error : \"./ruaCompiler_test_testFile\" : 3 : 1234567890" )
        self.assertEqual( errorHandler("Standard Error","",True) , "Standard Error" )
        
        









if __name__ == "__main__": 
    unittest.main()