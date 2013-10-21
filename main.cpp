#include "parser.h"
#include "sourceline.h"
#include <iostream>

int main() {
   Parser parser(std::cin,std::cout);
   parser.parse();
}
