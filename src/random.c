#include "random.h"
#include <stdlib.h>

int generate(int lower, int upper) {
  int r;
  const unsigned int range = 1 + upper - lower;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  /* Create equal size buckets all in a row, then fire randomly towards
    * the buckets until you land in one of them. All buckets are equally
    * likely. If you land off the end of the line of buckets, try again. */
  do {
    r = rand();
  } while (r >= limit);

  return lower + (r / buckets);
}
