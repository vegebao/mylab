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
    "cmp %%rax, %%rdi\n\t"
    "jb L4\n\t"
    "L2:\n\t"
    "movb (%%rcx,%%rdi,1), %%dl\n\t"
    "cmp %%rbx, %%rcx\n\t"
    "je R\n\t"
    "movb %%dl, (%%rcx,%%rax,1)\n\t"
    "add $1, %%rcx\n\t"
    "jmp L2\n\t"
    "L4:\n\t"
    "cmp $0, %%rbx\n\t"
    "je R\n\t"
    "movb -1(%%rbx,%%rdi,1), %%dl\n\t"
    "movb %%dl, -1(%%rbx,%%rax,1)\n\t"
    "sub $1, %%rbx\n\t"
    "jmp L4\n\t"
    "R:\n\t"
    :"=a"(dest)
    :"a"(dest),"c"(i),"b"(n),"D"(src)
    :"dl"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  int s=0;
  asm_jmp_buf *t=&env;
  asm(
    "movl %%ebx, (%%rdx)\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 4(%%rdx)\n\t"
    "movl %%ecx, 8(%%rdx)\n\t"
    "shr $32, %%rcx\n\t"
    "movl %%ecx, 12(%%rdx)\n\t"
    "movl %%edx, 16(%%rdx)\n\t"
    "mov %%rdx, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 20(%%rdx)\n\t"
    "movl %%esp, 24(%%rdx)\n\t"
    "mov %%rsp, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 28(%%rdx)\n\t"
    "movl %%ebp, 32(%%rdx)\n\t"
    "mov %%rbp, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 36(%%rdx)\n\t"
    "movl %%esi, 40(%%rdx)\n\t"
    "mov %%rsi, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 44(%%rdx)\n\t"
    "movl %%edi, 48(%%rdx)\n\t"
    "mov %%rdi, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 52(%%rdx)\n\t"
    "movl %%eip, 56(%%rdx)\n\t"
    "mov %%rip, %%rbx\n\t"
    "shr $32, %%rbx\n\t"
    "movl %%ebx, 60(%%rdx)\n\t"
    :"=a"(s)
    :"a"(s),"d"(t)
  );
  return s;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  asm_jmp_buf *t=&env;
  asm(
    "movq (%%rdx), %%rbx\n\t"
    "movq 8(%%rdx), %%rcx\n\t"
    "movq 16(%%rdx), %%rdx\n\t"
    "movq 24(%%rdx), %%rsp\n\t"
    "movq 32(%%rdx), %%rbp\n\t"
    "movq 40(%%rdx), %%rsi\n\t"
    "movq 48(%%rdx), %%rdi\n\t"
    "movq 56(%%rdx), %%rip\n\t"
    :"=a"(val)
    :"a"(val),"d"(t)
  );
}
