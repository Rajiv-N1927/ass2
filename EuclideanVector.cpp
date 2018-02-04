#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "EuclideanVector.h"

int main(int argc, char ** argv) {
  EuclideanVector vec1 { 1, 6, 3 };
  EuclideanVector vec2 { 1, 3, 7 };
  EuclideanVector vec3 { 2, 3, 1 };

  std::cout << vec2 << std::endl;
  return 0;
}
