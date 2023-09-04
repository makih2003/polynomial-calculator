#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include <sstream>
#include <iostream>

#include "Poly.h"

using namespace std;

/***********************************************************************
 To compile this file, run the following flag on terminal.
 g++ -pedantic -Wall -Wextra -std=c++17 -o unittest unittest_poly.cpp Poly.cpp
************************************************************************/


TEST_CASE("working with zero poly") {
   Poly zeroP;
   Poly p(2, 4);
   SUBCASE("default constructor") {
      Poly zeroP;
      stringstream result;
      result << zeroP;
      CHECK( result.str() == "0" );
   }
   SUBCASE("constructor with inputs") {
      stringstream result;
      result << p;
      CHECK( result.str() == "2x^4" );
   }
   SUBCASE("zero poly + zero poly") {
      stringstream result;
      result << (zeroP + zeroP);
      CHECK( result.str() == "0" );
   }
   SUBCASE("add zero poly") {
      stringstream result;
      result << (p + zeroP);
      CHECK( result.str() == "2x^4" );
   }
   SUBCASE("add 1 term to zero poly") {
      stringstream result;
      result << (zeroP + p);
      CHECK( result.str() == "2x^4" );
   }
   SUBCASE("subtract zero poly") {
      stringstream result;
      result << (p - zeroP);
      CHECK( result.str() == "2x^4" );
      stringstream result2;
      result2 << (zeroP - zeroP);
      CHECK( result2.str() == "0" );

   }
   SUBCASE("subtract from zero poly") {
      stringstream result;
      result << (zeroP - p);
      CHECK( result.str() == " - 2x^4" );
   }
   SUBCASE("evaluate zero poly") {
      stringstream result;
      result << zeroP.evaluate(5);
      CHECK( result.str() == "0" );
   }
   SUBCASE("differentiate zero poly") {
      stringstream result;
      result << zeroP.derivative();
      CHECK( result.str() == "0" );
   }
}

TEST_CASE("operation on 1 term"){
  Poly p1;
  Poly p2;
  stringstream ss_in1("1 -1 2");
  ss_in1 >> p1;
  stringstream ss_in2("1 5 6");
  ss_in2 >> p2;
  SUBCASE("output"){
    stringstream result;
    result << p1;
    CHECK( result.str() == " - x^2" );
  }
  SUBCASE("output"){
    stringstream result;
    result << p2;
    CHECK( result.str() == "5x^6" );
  }
  SUBCASE("addition"){
    stringstream result;
    result << (p1 + p2);
    CHECK( result.str() == "5x^6 - x^2" );
  }
  SUBCASE("subtraction"){
    stringstream result;
    result << (p1 - p2);
    CHECK( result.str() == " - 5x^6 - x^2" );
  }
  SUBCASE("evaluate poly of 1 term") {
      stringstream result;
      result << p1.evaluate(5);
      CHECK( result.str() == "-25" );
   }
   SUBCASE("evaluate poly of 1 term with negative nbr") {
      stringstream result;
      result << p1.evaluate(-2);
      CHECK( result.str() == "-4" );
   }
   SUBCASE("evaluate poly of 1 term with 0") {
      stringstream result;
      result << p1.evaluate(0);
      CHECK( result.str() == "0" );
   }
   SUBCASE("differentiate") {
      stringstream result;
      result << p1.derivative();
      CHECK( result.str() == " - 2x" );
   }
   SUBCASE("differentiate") {
      stringstream result;
      result << p2.derivative();
      CHECK( result.str() == "30x^5" );
   }
}

TEST_CASE("operation on multiple terms"){
  Poly p1;
  Poly p2;
  stringstream ss_in1("3 -2 3 8 4 1 6");
  ss_in1 >> p1;
  stringstream ss_in2("6 7 5 -16 4 -1 6 8 2 20 0 11 1");
  ss_in2 >> p2;
  SUBCASE("output"){
    stringstream result;
    result << p1;
    CHECK( result.str() == "x^6 + 8x^4 - 2x^3" );
  }
  SUBCASE("output"){
    stringstream result;
    result << p2;
    CHECK( result.str() == " - x^6 + 7x^5 - 16x^4 + 8x^2 + 11x + 20" );
  }
  SUBCASE("addition"){
    stringstream result;
    result << (p1 + p2);
    CHECK( result.str() == "7x^5 - 8x^4 - 2x^3 + 8x^2 + 11x + 20" );
  }
  SUBCASE("subtraction the second poly is longer"){
    stringstream result;
    result << (p1 - p2);
    CHECK( result.str() == "2x^6 - 7x^5 + 24x^4 - 2x^3 - 8x^2 - 11x - 20" );
  }
  SUBCASE("subtraction the first poly is longer"){
    stringstream result;
    result << (p2 - p1);
    CHECK( result.str() == " - 2x^6 + 7x^5 - 24x^4 + 2x^3 + 8x^2 + 11x + 20" );
  }
  SUBCASE("multiply by 3"){
    stringstream result;
    result << (p1 * 3);
    CHECK( result.str() == "3x^6 + 24x^4 - 6x^3" );
  }
  SUBCASE("multiply by -1"){
    stringstream result;
    result << (p1 * -1);
    CHECK( result.str() == " - x^6 - 8x^4 + 2x^3" );
  }
  SUBCASE("multiply by 0"){
    stringstream result;
    result << (p1 * 0);
    CHECK( result.str() == "0" );
  }
  SUBCASE("evaluate with 0") {
      stringstream result;
      result << p2.evaluate(0);
      CHECK( result.str() == "20" );
  }
  SUBCASE("evaluate with positive number") {
      stringstream result;
      result << p2.evaluate(3);
      CHECK( result.str() == "-199" );
  }
  SUBCASE("evaluate with negative number") {
      stringstream result;
      result << p2.evaluate(-10);
      CHECK( result.str() == "-1859290" );
  }
  SUBCASE("differentiate") {
      stringstream result;
      result << p1.derivative();
      CHECK( result.str() == "6x^5 + 32x^3 - 6x^2" );

      stringstream result2;
      result2 << p2.derivative();
      CHECK( result2.str() == " - 6x^5 + 35x^4 - 64x^3 + 16x + 11" );
  }
  Poly p3;
  stringstream ss_in3("4 10 0 1 -3 1 -5 2 2");
  ss_in3 >> p3;
  SUBCASE("differentiate negative power") {
      stringstream result;
      result << p3.derivative();
      CHECK( result.str() == "4x - 3x^-4 - 5x^-6" );
  }
}

TEST_CASE("copy constructor test"){
  SUBCASE("zero poly"){
    Poly p;
    Poly copiedP = p;
    stringstream ss_p;
    ss_p << p;
    stringstream ss_copied;
    ss_copied << copiedP;
    CHECK( ss_p.str() == ss_copied.str() );
  }
  SUBCASE("poly with 3 terms"){
    Poly p;
    stringstream ss_in("3 6 4 2 7 0 1");
    ss_in >> p;
    
    Poly copiedP = p;
    stringstream ss_copied;
    ss_copied << copiedP;

    stringstream ss_original;
    ss_original << p;
    
    CHECK( ss_original.str() == ss_copied.str() );

    // check if deep-copy is properly done
    copiedP.insert(2, 5);
    stringstream ss_copied_modified;
    ss_copied_modified << copiedP;
    stringstream ss_org_modified;
    ss_org_modified << p;
    CHECK( ss_org_modified.str() != ss_copied_modified.str() );
  }
}

TEST_CASE("overloaded assignment operator"){
  SUBCASE("zero poly"){
    Poly p1(2, -4);
    Poly p2;
    p1 = p2;
    stringstream ss_p;
    ss_p << p1;
    stringstream ss_copied;
    ss_copied << p2;
    CHECK( ss_p.str() == ss_copied.str() );
  }
  SUBCASE("multiple poly with modifying"){
    Poly p1;
    Poly p2(5, 4);

    p1 = p2;
    stringstream ss_p1;
    ss_p1 << p1;
    stringstream ss_p2;
    ss_p2 << p2;
    CHECK( ss_p1.str() == ss_p2.str() );

    // check if deep-copy is properly done
    p1.insert(5, 5);
    stringstream ss_copied_modified;
    ss_copied_modified << p1;
    stringstream ss_org_modified;
    ss_org_modified << p2;
    CHECK( ss_org_modified.str() != ss_copied_modified.str() );
  }
}

TEST_CASE("destructor test"){
  SUBCASE("out of scope"){
    {
      Poly p(2, 6);
    }

    Poly p;
    stringstream ss_p;
    ss_p << p;
    CHECK( ss_p.str() == "0" );
  }
  SUBCASE("using delete keyword"){
    Poly* p = new Poly;
    p->insert(2, 5);
    p->insert(4, 3);
    delete p;
  }
}