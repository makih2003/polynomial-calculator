#include <iostream>
#include <cmath>
#include "Poly.h"

using namespace std;

Poly::Poly(){
  poly = nullptr;
  var = 'x';
}


Poly::Poly(int coeff, int pow){
  if(coeff == 0) poly = nullptr;
  else{
    poly = new Node{coeff, pow, nullptr};
    var = 'x';
  } 
}


void Poly::setVar(char c){
  var = c;
}


char Poly::getVar(){
  return var;
}


Poly operator +(const Poly& p1, const Poly& p2){
  Poly sumPoly;
  sumPoly.setVar(p1.var);
  sumPoly.poly = Poly::addPolynomials(p1.poly, p2.poly);
  return sumPoly;
}


Poly operator-(const Poly& p1, const Poly& p2){
  Poly subtrPoly;
  subtrPoly.setVar(p1.var);
  subtrPoly.poly = Poly::subtractPolynomials(p1.poly, p2.poly);
  return subtrPoly;
}


Poly::Node* Poly::subtractPolynomials(const Node* poly1, const Node* poly2){
  if(!poly1 && !poly2) return nullptr;
  if(!poly1) return multiplyPolynomial(poly2, -1);
  if(!poly2) return deepCopyPoly(poly1);

  Node* p2 = multiplyPolynomial(poly2, -1);
  Node* head = addPolynomials(poly1, p2);
  return head;
}


Poly operator*(const Poly& p, int i){
  Poly multplyPoly;
  multplyPoly.setVar(p.var);
  multplyPoly.poly = Poly::multiplyPolynomial(p.poly, i);
  return multplyPoly;
}


Poly::Node* Poly::multiplyPolynomial(const Node* poly, int i){
  if(!poly) return nullptr;

  Node* dummyH = new Node;
  Node* curr = dummyH;

  while(poly){
    int newCoeff = poly->coeff * i;
    if(newCoeff != 0){
      curr->next = new Node{newCoeff, poly->power, nullptr};
      curr = curr->next;
    }
    poly = poly->next;
  }

  if(curr == dummyH){ // polynomial == 0
    delete dummyH;
    return nullptr;
  }

  curr = dummyH->next;
  delete dummyH;
  return curr;
}


Poly::Node* Poly::addPolynomials(const Node* poly1, const Node* poly2) {
    if(!poly1 && !poly2) return nullptr;
    
    Node* dummyH = new Node;
    Node* curr = dummyH;

    while(poly1 && poly2){
      if(poly1->power > poly2->power){
        curr->next = new Node{poly1->coeff, poly1->power, nullptr};
        poly1 = poly1->next;
        curr = curr->next;
      }else if(poly1->power < poly2->power){
        curr->next = new Node{poly2->coeff, poly2->power, nullptr};
        poly2 = poly2->next;
        curr = curr->next;
      }else{ // poly1->power == poly2->power
        int sumOfCoeff = poly1->coeff + poly2->coeff;
        
        if(sumOfCoeff != 0){
          curr->next = new Node{sumOfCoeff, poly1->power, nullptr};
          curr = curr->next;
        }
        poly1 = poly1->next;
        poly2 = poly2->next;
      }
    }

    while(poly1){
      curr->next = new Node{poly1->coeff, poly1->power, nullptr};
      poly1 = poly1->next;
      curr = curr->next;
    }

    while(poly2){
      curr->next = new Node{poly2->coeff, poly2->power, nullptr};
      poly2 = poly2->next;
      curr = curr->next;
    }

    if(curr == dummyH){ // polynomial == 0
      delete dummyH;
      return nullptr;
    }

    curr = dummyH->next;
    delete dummyH;
    return curr;
}


int Poly::evaluate(int x) const{
  Node* head = poly;
  if(!head) return 0;

  int answer = 0;
  while(head){
    double sumOfTerm = head->coeff * pow(x, head->power);
    answer += sumOfTerm;
    head = head->next;
  }
  return answer;
}


Poly Poly::derivative(){
  Poly derivPoly;
  derivPoly.setVar(var);
  derivPoly.poly = Poly::derivative(poly);
  return derivPoly;
}


Poly::Node* Poly::derivative(const Node* poly){
  if(!poly) return nullptr;
    
  Node* dummyH = new Node;
  Node* curr = dummyH;

  while(poly){
    if(poly->power != 0){
      int newCoeff = poly->coeff * poly->power;
      int newPow = poly->power - 1;

      if(newCoeff != 0){
        curr->next = new Node{newCoeff, newPow, nullptr};
        curr = curr->next;
      }
    }
    poly = poly->next;
  }

  if(curr == dummyH){ // polynomial == 0
    delete dummyH;
    return nullptr;
  }

  curr = dummyH->next;
  delete dummyH;
  return curr;
}


void Poly::insert(int c, int p){
  poly = Poly::insert(c, p, poly);
}


Poly::Node* Poly::insert(int c, int p, Node* head){
  if(head == nullptr || p > head->power){
    return new Node{c, p, head};
  }else if(p == head->power){
    head->coeff += c;
  }else{
    head->next = insert(c, p, head->next);
  }
  return head;
}


istream& operator>>(istream& in, Poly& poly){
  int nmbTerm;
  in >> nmbTerm;

   for (int i = 0; i < nmbTerm; i++) {
      int coeff, pow;
      in >> coeff >> pow;

      if(coeff != 0){
        poly.insert(coeff, pow); 
      }
   }
   return in;
}


ostream& operator<<(std::ostream& out, const Poly& p){
  if(p.poly == nullptr) out << "0";
  else Poly::displayPoly(p.poly, p.var, out);
  return out;
}


void Poly::displayPoly(Node* head, char v, std::ostream& out){
  bool isFirstNode = true;
  while(head != nullptr){
    int coeff = head->coeff;
    int pow = head->power;

    if(!isFirstNode && coeff > 0){
      out << " + ";
    }else if(coeff < 0){
      out << " - ";
      coeff *= -1;
    }

    if(coeff != 1 || pow == 0){
      out << coeff;
    }

    if(pow != 0){
      out << v;
    }

    if(pow != 1 && pow != 0){
      out << "^" << pow;
    }
    head = head->next;
    isFirstNode = false;
  }
}


Poly::Node* Poly::deepCopyPoly(const Node* head) {
    if (!head) return nullptr;

    Node* duplicateHead = new Node{head->coeff, head->power, nullptr};
    Node* current = duplicateHead;
    Node* original = head->next;

    while (original) {
      current->next = new Node{original->coeff, original->power, nullptr};
      current = current->next;
      original = original->next;
    }

    return duplicateHead;
}


Poly::Node* Poly::deletePoly(Node *head){
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    return head;
}


Poly::Poly(const Poly& other){
  poly = deepCopyPoly(other.poly);
  var = other.var;
}


Poly& Poly::operator = (const Poly& other){
  if(this != &other){
      poly = deletePoly(poly);
      poly = deepCopyPoly(other.poly);
      var = other.var;
   }

   return *this;
}


Poly::~Poly(){
  poly = deletePoly(poly);
}


Poly::Poly(Poly&& other){
  poly = other.poly;
  var = other.var;
  other.poly = nullptr;
  other.var = 'x';
}


Poly& Poly::operator=(Poly&& other){
  if(this != &other){
    poly = deletePoly(poly);
    poly = other.poly;
    var = other.var;
    other.poly = nullptr;
    other.var = 'x';
  }
  return *this;
}