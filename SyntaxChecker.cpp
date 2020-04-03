#include "SyntaxChecker.h"
#include "GenStack.hpp"
#include <iostream>
#include <fstream>

SyntaxChecker::SyntaxChecker(){

}

//return 1 if errors/ dont want to read another file
//return 0 if no errors/ want to read another file
int SyntaxChecker::checkSyntax(string fileName){
  ifstream inFS;
  string currentLine;
  int lineNumber = 0;
  GenStack<char> *myStack = new GenStack<char>(100);

  //read from the file
  inFS.open(fileName);

  //indicate that the file has been opened
  if(inFS.is_open()){
    cout << "File has been opened" << endl;
  }

  //loop through each line in the file
  while(getline(inFS, currentLine)){
    lineNumber++;
    for(int i = 0; i < currentLine.length(); ++i){
      char currentChar = currentLine[i];

      //if a character in the line is an opening bracket/brace/parenthesis, add it to the stack
      if((currentChar == '{') || (currentChar == '[') || (currentChar == '(')){
        myStack->push(currentChar);
      }

      //if a character in the line is an ending bracket/brace/parenthesis, compare it to the top of the stack
      //if the character does not have a matching beginning bracket/brace/parenthesis at the top of the stack, return error
      if(currentChar == '}'){
        if(myStack->peek() != '{'){
          cout << "ERROR: expected { before line " << lineNumber << endl;
          return 1;
        }
        else{
          myStack->pop();
        }
      }
      else if(currentChar == ']'){
        if(myStack->peek() != '['){
          cout << "ERROR: expected [ before line " << lineNumber << endl;
          return 1;
        }
        else{
          myStack->pop();
        }
      }
      else if(currentChar == ')'){
        if(myStack->peek() != '('){
          cout << "ERROR: expected ( before line " << lineNumber << endl;
          return 1;
        }
        else{
          myStack->pop();
        }
      }
    }
  }

  //if we have reached this point, there are no errors
  //if at the end of the file, there still exists open braces in the stack, then return an error
  if(!myStack->isEmpty()){

    //check for specific types of open brackets
    if(myStack->peek() == '{'){
      cout << "ERROR: Reached end of file, missing }" << endl;
      return 1;
    }
    else if(myStack->peek() == '['){
      cout << "ERROR: Reached end of file, missing ]" << endl;
      return 1;
    }
    else if(myStack->peek() == '('){
      cout << "ERROR: Reached end of file, missing )" << endl;
      return 1;
    }
  }

  //no errors in the file
  else{
    cout << "No syntax errors in the file!" << endl;
    return 0;
  }
}
