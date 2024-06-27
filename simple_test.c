#include <assert.h>
#include <stddef.h>

long load_long(long *p) {
    long res;
    asm volatile(".insn i 0b0001011, 0b011, %0, 0(%1)"
                    : "=r"(res)
                    : "r"(p));
    return res;
}

void store_long(long *p, long val) {
    asm volatile(".insn s 0b0101011, 0b011, %0, 0(%1)"
                    :
                    : "r"(val), "r"(p));
}

int main() {
    long a = 0x12345678;
    assert(load_long(&a) == 0x12345678);
    store_long(&a, 0x87654321);
    store_long(NULL, 0);
    assert(a == 0x87654321);
    assert(load_long(NULL) == 0);
    return 0;
}
