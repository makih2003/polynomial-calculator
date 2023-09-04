#ifndef POLY_H
#define POLY_H

#include <iostream>

class Poly {

  public:
    // Constructor of Poly
    // Initialize polynomial with nullptr
    Poly();

    // Constructor of Poly
    // Initialize polynomial with the givin coeff and power
    Poly(int coeff, int pow);

    // set new character as a variable
    void setVar(char c);

    // return var of poly
    char getVar();

    // add two polynomials and return the result
    // the result is a new polynomial object
    friend Poly operator+(const Poly& p1, const Poly& p2);

    // subtract two polynomials and return the result
    // the result is a new polynomial object
    friend Poly operator-(const Poly& p1, const Poly& p2);

    // multiply two polynomials and return the result
    // the result is a new polynomial object
    friend Poly operator*(const Poly& p, int i);

    // evaluate the polynomial with the value x
    int evaluate(int x) const;

    // differentiate the polynomial and return the result
    // the result is a new polynomial object
    Poly derivative();

    // overloaded output operator
    // output the polynomial in the format easy to read
    friend std::ostream& operator<<(std::ostream&, const Poly& p);

    // overload input operator
    // first, read the number of terms user will enter (n)
    // then, read the pairs of coefficient and power n times
    friend std::istream& operator>>(std::istream&, Poly& p);

    void insert(int c, int p);

    // overloaded assignment, copy constructor, destructor
    // copy constructor
    Poly(const Poly&);

    // overloaded assignment operator
    Poly& operator = (const Poly&);

    // destructor
    ~Poly();

    // move constructor
    Poly(Poly&& other);

    // move assignment operator
    Poly& operator=(Poly&& other);


  private:
    struct Node {
      int coeff;
      int power;
      struct Node* next;
  };

  struct Node* poly;
  char var;

  static Node* insert(int c, int p, Node* head);
  static void displayPoly(Node* head, char v, std::ostream&);
  static Node* deepCopyPoly(const Node* head);
  static Node* deletePoly(Node *head);
  static Node* addPolynomials(const Node* poly1, const Node* poly2);
  static Node* subtractPolynomials(const Node* poly1, const Node* poly2);
  static Node* multiplyPolynomial(const Node* poly, int i);
  static Node* derivative(const Node* poly);
};


#endif