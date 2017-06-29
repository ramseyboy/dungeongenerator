#include "random.h"
#include <stdlib.h>

int generate(int lower, int upper) {
  return lower + rand() / (RAND_MAX / (upper - lower + 1) + 1);
}
