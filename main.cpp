#include "SyntaxChecker.h"

int main(int argc, char **argv){

  SyntaxChecker newChecker;

  //check for command line argument
  //take in a file from COMMAND LINE input

  if(argc > 1){
    // set the file name equal to the arg
    string inputFileName = argv[1];
    cout << "Input file name taken in by command line input." << endl;
    bool keepPrompting = true;
    while (keepPrompting){
      // check the syntax of the file
      int isValid = newChecker.checkSyntax(inputFileName);
      if (isValid == 1){
        // not valid
        keepPrompting = false;
      } else {
        // syntax is valid, prompt the user if they want to check another file
        char userInput = 'n';
        cout << "Would you like to check another file? (answer y or n)" << endl;
        char answer;
        cin >> answer;
        if(answer != 'y'){
          cout << "Thanks!" << endl;
          keepPrompting = false;
        }else{
          cout << "What is the name of the file you want to check?" << endl;
          cin >> inputFileName;
        }
      }

    }

  } else{
    cout << "Error: you did not enter the name of the file to read." << endl;
  }
  return 0;
}
