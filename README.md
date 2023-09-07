# polynomial-calculator
Polynomial calculator users can interact on the console. Users can do multiple operations after entering two polynomials, such as addition, subtraction, and differentiation. A linked list is used as its data structure. Big five (copy constructor, copy assignment, destructor, move constructor, move assignment) is also implemented. The unit test is conducted with doctest framework.

## How to run the program
• To run the <em>main program (ui_poly.cpp)</em>, please run the following flag on terminal.
<br>
```bash
g++ -pedantic -Wall -Wextra -std=c++17 -o uiPoly ui_poly.cpp Poly.cpp
```

• To run the unit test file (unittest_poly.cpp), please run the following flag on the terminal.
<br>
```bash
g++ -pedantic -Wall -Wextra -std=c++17 -o unittest unittest_poly.cpp Poly.cpp
```

## File Structure
### Poly.h
Header file contains Poly class definition

### Poly.cpp
The implementation file of Poly class
