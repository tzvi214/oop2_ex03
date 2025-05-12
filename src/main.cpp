#include "FunctionCalculator.h"

#include <string>
#include <iostream>
#include "SquareMatrix.h"

int main()
{
   SquareMatrix<int> sq(2, 2); // Specify template argument explicitly
   SquareMatrix<int> s(5);    // Specify template argument explicitly
   std::cout << "the d-tor(,) \n" << sq << "the d-tor() \n" << s;

   FunctionCalculator(std::cin, std::cout).run();
}
