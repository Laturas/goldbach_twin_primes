#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;
typedef unsigned long long u64;

typedef enum bool {
    false,
    true,
} bool;

bool is_active(unsigned char* list, u32 in) {
    if ((list[in / 8]) & (1 << (in & 7))) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    FILE* out = fopen("sums.txt", "w");
    FILE* in = fopen("twin_prime_list.txt", "r");
    unsigned char* big_bitfield = calloc(600000000, sizeof(char));
    u32* twins = calloc(24968224, sizeof(u32));
    if (!twins) {printf("Out of memory :(\n"); return 0;}

    int current_index = 2;
    
    u32 location;
    int _ = fscanf(in, "%lu", &location);
    _ = fscanf(in, "%lu", &location);
    _ = fscanf(in, "%lu", &location); // duplicate 5 >:(
    twins[0] = 3;
    twins[1] = 5;
    while (location < 4000000000) {
        int _ = fscanf(in, "%lu", &location);
        twins[current_index++] = location;
        //printf("\r%lu", location);
        //big_bitfield[location / 8] |= 1 << (location & 7);
    }
    fclose(in);
    printf("Successfully read in file!\n"); fflush(stdout);
    unsigned char shutup = 0;
    for (int i = 0; i < 5000; i++) {
        u32 j = i;
        u64 value;
        while ((value = twins[i] + twins[j]) < 4000000000) {
            if (!(is_active(big_bitfield, value))) {
                fprintf(out, "%llu:%lu\n", value, twins[i]);
            }
            big_bitfield[value / 8] |= 1 << (value & 7);
            j++;
        }
        if (!(shutup++)) {
            printf("%lu\n", twins[i]); fflush(stdout);
        }
    }
    printf("Reading bitfield\n"); fflush(stdout);
    for (u32 i = 0; i < 4000000000; i += 2) {
        if (!is_active(big_bitfield,i)) {
            printf("Exception found: %lu\n", i);
        }
    }
}
