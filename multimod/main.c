#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t mod(uint64_t, uint64_t);

void test(uint64_t a, uint64_t m) {
  #define U64 "%" PRIu64
  printf(U64 " mod " U64 " = " U64 "\n", a, m, mod(a,m));
}

int main() {
  test(15498, 36);
  test(4294156248, 61);
  test(4294217854, 4216548765);
}