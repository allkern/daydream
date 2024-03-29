#include <stdint.h>
#include <stdio.h>

int main() {
    uint32_t virt = 0x7fffffff;
    uint32_t phys = virt & 0x1fffffff;

    int p   = (virt & 0x80000000) != 0;
    int alt = (virt & 0x40000000) != 0;
    int nc  = (virt & 0x20000000) != 0;

    printf("virt=%08x -> phys=%08x p=%u alt=%u nc=%u\n",
        virt,
        phys,
        p,
        alt,
        nc
    );

    return 0;
}