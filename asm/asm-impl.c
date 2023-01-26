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
  int s=0;
  int i=0;
  asm(
    "L1:\n\t"
    "mov %%rdx, %%rdi\n\t"
    "shr %%ecx, %%rdi\n\t"
    "and $1, %%rdi\n\t"
    "add %%edi, %%eax\n\t"
    "add $1, %%ecx\n\t"
    "cmp $64, %%ecx\n\t"
    "jne L1\n\t"
    :"=a"(s)
    :"a"(s),"c"(i),"d"(x)
    :"rdi"
  );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  int i=0;
  asm(
    "cmp %%rax, %%rdx\n\t"
    "ja L4:\n\t"
    "L2:\n\t"
    "movb (%%rcx,%%rdi,1), %%dl\n\t"
    "cmp %%rbx, %%rcx\n\t"
    "je R\n\t"
    "cmp $0, %%dl\n\t"
    "je L3\n\t"
    "movb %%dl, (%%rcx,%%rax,1)\n\t"
    "add $1, %%rcx\n\t"
    "jmp L2\n\t"
    "L3:\n\t"
    "movb $0, (%%rcx,%%rax,1)\n\t"
    "add $1, %%rcx\n\t"
    "cmp %%rcx, %%rbx\n\t"
    "jne L3\n\t"
    "jmp R\n\t"
    "L4:\n\t"
    "cmp $0, %%rbx\n\t"
    "je R\n\t"
    "movb $-1(%%rbx,%%rdi,$1), %%dl\n\t"
    "movb %%dl, $-1(%%rbx,%%rax,$1)\n\t"
    "sub $1, %%rbx\n\t"
    "R:\n\t"
    :"=a"(dest)
    :"a"(dest),"c"(i),"b"(n),"D"(src)
    :"dl"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
