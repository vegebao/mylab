#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t mod(uint64_t, uint64_t);

void test(uint64_t a, uint64_t m) {
  #define U64 "%" PRIu64
  printf(U64 " mod " U64 " = " U64 "\n", a, m, mod(a,m));
}

int main() {
  test(15498, 36);//<2^32;<2^32
  test(4294156248, 61);//<2^32;<2^32
  test(4294217854, 4216548765);//<2^32  <2^32
  test(4697541238,36);
  test(4954871392,4743219764);
  test(1657321984571359486, 1498732168495214568);
  test(1469813579846285412, 45);
}