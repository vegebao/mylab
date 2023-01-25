#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  asm(
    "lea (%1,%2,1), %0"
    :"=r"(a)
    :"0"(a),"r"(b)
  );
  return a;
}

int asm_popcnt(uint64_t x) {
  /*for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }*/
  int s=0,i=0;
  asm(
    "L1:\n\t"
    "mov %rdx, %rdi\n\t"
    "shr %ecx, %rdi\n\t"
    "and $1, %rdi\n\t"
    "add %edi, %eax\n\t"
    "add $1, %ecx\n\t"
    "cmp $32, %ecx\n\t"
    "jne L1\n\t"
    :"=a"(s)
    :"c"(i),"d"(x)
    :"rdi"
  );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
