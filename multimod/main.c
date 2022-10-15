#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t mod_add(uint64_t, uint64_t, uint64_t);
uint64_t mod(uint64_t, uint64_t);

void test(uint64_t a,uint64_t b ,uint64_t m) {
  #define U64 "%" PRIu64
  printf(U64 " + " U64 " mod "  U64 " = " U64 "\n", a,b ,m , mod_add(a, b, m));
}

int main() {
 
  
  
  test(15498,15498, 36);//<2^32;<2^32    shoubld be 0
  test(4294156248, 149875642,61);//<2^32;<2^32   should be 49
  test(4294217854, 2187945658,4216548765);//<2^32  <2^32  should be 2265614747
  test(4697541238, 49875462135,36);
  test(4954871392,4743219764, 4265487912);
  test(-1ULL,-1ULL,-2ULL);
}