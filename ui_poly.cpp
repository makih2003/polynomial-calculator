#include "Poly.h"

#include <iostream>
#include <string>

using namespace std;

/***********************************************************************
 To compile this file, run the following flag on terminal.
 g++ -pedantic -Wall -Wextra -std=c++17 -o uiPoly ui_poly.cpp Poly.cpp
************************************************************************/


// display options 
// (addition, subtraction, multiplying by a number, evaluate with a number, derivative, set a new variable, display polynomials, quit the program)
void displayMenu();

// display initial instructions
void displayInstruction();

// clearing the inout buffer
void clearInputStream(istream &in);

// read a new polynomial and store it in p
// num is the number of polynomial (ex: "1st", "2nd")
bool readInput(Poly& p, string num);

// print polynomials p1 and p2
void printInput(Poly& p1, Poly& p2);

// read 2 polynomials and store them in p1 and p2
// it keeps reading until valid inputs are giving
void readInput(Poly& p1, Poly& p2);

// process the chosen option
// precondition::
//    op = a number user chose
//    p1 = 1st polynomial
//    p2 = 2nd polynomial
// postcondition::
//    result = polynomial that contains the result of operation
void process(int op, Poly& p1, Poly& p2, Poly& result);

// print result
// postcondition::
//    op: operation (ex: +, -)
//    p1 = 1st polynomial
//    p2 = 2nd polynomial
// postcondition::
//    result = polynomial that contains the result of operation
void printResult(string op, Poly& p1, Poly& p2, Poly& result);

// print result
// postcondition::
//    op: operation (ex: +, -)
//    p = polynomial
//    c = a number to multiply by p
// postcondition::
//    result = polynomial that contains the result of operation
void printResult(string op, Poly& p, int c, Poly& result);

// print result
// postcondition::
//    p = polynomial
//    x = a number to evaluate p
//    fg = "f" or "g"
// postcondition::
//    answer = the result after evaluating f with x
void printResult(Poly& p, int x, int answer, string fg);

// print result of derivative
// postcondition::
//    p = polynomial
//    fg = "f" or "g"
void printResult(Poly& p, Poly& result, string fg);

// read a number to multiply by the polynomial
bool readConstantNumber(int& c);

// read a new variable to set
char readVariable();


void displayInstruction(){
  cout << "Please read the following instructions:" << endl << endl;
  cout << "Example 1) To input \"6x^4 - 7x^2 + 10\", please type: \n3\n6 4\n-7 2\n10 0"<< endl;
  cout << "The first \"3\" referes to the nubmer of the terms in the polynomial." << endl << endl;
  cout << "Example 2) To input \"x^6 + 2x^2 + 1 - 9x^-4 - 10x^-6\", please type: \n5\n1 6\n2 2\n1 0\n-9 -4 \n-10 -6"<< endl;
  cout << "The first \"5\" refers to the nubmer of the terms in the polynomial." << endl << endl;
  cout << "The polynomial will always be in descending order by the number of powers regardless of how you type. Please note that the number of the terms in the polynomial must be typed first as in the above examples shown." << endl << endl;
}


void clearInputStream(istream &in){
   in.clear();
   in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}


bool readInput(Poly& p, string num){
  cout << "Enter " << num << " polynomial" << endl;
  bool isRead = true;
  if(!(cin >> p)){
    cout << "ERROR in Reading" << endl;
    isRead = false;
  }
  clearInputStream(cin);
  return isRead;
}


void readInput(Poly& p1, Poly& p2){
    bool isRead = readInput(p1, "1st");
    while(!isRead){
      isRead = readInput(p1,"1st");
    }
    isRead = readInput(p2, "2nd");
    while(!isRead){
      isRead = readInput(p2,"2nd");
    }
}


void printInput(Poly& p1, Poly& p2){
  cout << "f(" << p1.getVar() << "): " << p1 << endl;
  cout << "g(" << p2.getVar() << "): " << p2 << endl;
}


void displayMenu(){
  cout << "\n";
  cout << "------------------- Choose an Option -------------------" << endl;
  cout << "(1) f + g" << endl;
  cout << "(2) f - g" << endl;
  cout << "(3) g - f" << endl;
  cout << "(4) f * c (constant number)" << endl;
  cout << "(5) g * c (constant number)" << endl;
  cout << "(6) evaluate f with a constant number \"x\"" << endl;
  cout << "(7) evaluate g with a constant number \"x\"" << endl;
  cout << "(8) differentiate f" << endl;
  cout << "(9) differentiate g" << endl;
  cout << "(10) set a variable (default variable is x) " << endl;
  cout << "(11) display the polynomials" << endl;
  cout << "(12) quit the program" << endl;
}


void printResult(string op, Poly& p1, Poly& p2, Poly& result){
  cout << " ( "<< p1 << " ) " << op << " ( " << p2 << " )" << endl;
  cout << " = " << result << endl; 
}


void printResult(string op, Poly& p, int c, Poly& result){
  cout << " ( "<< p << " ) " << op << " " << c << endl;
  cout << " = " << result << endl; 
}


void printResult(Poly& p, int x, int answer, string fg){
  cout << fg << " = " << p << endl;
  cout << fg << "(" << x << ")" << " = " << answer << endl;
}


void printResult(Poly& p, Poly& result, string fg){
  string deriv;
  if(fg == "f") deriv = "df/d";
  else deriv = "dg/d";
  cout << fg << " = " << p << endl;
  cout << deriv << p.getVar() << " " << result << endl;
}


bool readConstantNumber(int&  c){
  cout << "Enter a number: ";
  bool isRead = true;
  if(!(cin >> c)){
    cout << "Invalid input";
    isRead = false;
  }
  clearInputStream(cin);
  return isRead;
}


void process(int op, Poly& p1, Poly& p2, Poly& result){
  switch (op){
  case 1:
    result = (p1 + p2);
    printResult("+", p1, p2, result);
    break;
  case 2:
    result = (p1 - p2);
    printResult("-", p1, p2, result);
    break;
  case 3:
    result = (p2 - p1);
    printResult("-", p2, p1, result);
    break;
  case 4:
    int c;
    bool isRead;
    isRead = readConstantNumber(c);
    if(isRead){
      result = (p1 * c);
      printResult("*", p1, c, result);
    }
    break;
  case 5:
    isRead = readConstantNumber(c);
    if(isRead){
      result = (p2 * c);
      printResult("*", p2, c, result);
    }
    break;
  case 6:
    int x, answer;
    isRead = readConstantNumber(x);
    if(isRead){
      answer = p1.evaluate(x);
      printResult(p1, x, answer, "f");
    }
    break;
  case 7:
    isRead = readConstantNumber(x);
    if(isRead){
      answer = p2.evaluate(x);
      printResult(p2, x, answer, "g");
    }
    break;
  case 8:
    result = p1.derivative();
    printResult(p1, result, "f");
    break;
  case 9:
    result = p2.derivative();
    printResult(p2, result, "g");
    break;
  case 10:
    char v;
    v = readVariable();
    p1.setVar(v);
    p2.setVar(v);
    result.setVar(v);
    break;
  case 11:
    printInput(p1, p2);
    break;
  }
}

char readVariable(){
  cout << "Enter a single character: ";
  char c;
  if(!(cin >> c)){
    cout << "Invalid input";
  }
  clearInputStream(cin);
  return c;
}

int main(){
  displayInstruction();
  Poly p1;
  Poly p2;
  readInput(p1, p2);
  printInput(p1, p2);
  displayMenu();

  int chosenOp = 0;
  Poly result;
  do {
    if(!(cin >> chosenOp)){
      cout << "Invalid input" << endl;
      clearInputStream(cin);
    }
    process(chosenOp, p1, p2, result);
    if(chosenOp != 12){
      cout << "\nEnter another option" << endl;
    }
  } while(chosenOp != 12);
  return 0;
}