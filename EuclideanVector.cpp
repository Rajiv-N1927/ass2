#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "EuclideanVector.h"

int main(int argc, char ** argv) {
  EuclideanVector vec1 { 1, 2, 3 };
  EuclideanVector vec2 { 1, 3, 7 };
  EuclideanVector vec4 { 2, 3, 1 };
  //vec1 += vec2;
  EuclideanVector vec3;
  vec3 = vec1 - (vec2 + vec4);
  vec3.printVec();

  return 0;
}
