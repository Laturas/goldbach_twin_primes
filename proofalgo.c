#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;
typedef unsigned long long u64;
typedef long int i32;
typedef long long i64;

typedef enum bool {
    false,
    true,
} bool;

bool is_active(unsigned char* list, u64 in) {
    if ((list[in / 8]) & (1 << (in & 7))) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    FILE* out = fopen("exceptions.txt", "w");
    FILE* in = fopen("twin_prime_list.txt", "r");
    unsigned char* big_bitfield = calloc(1000000000, sizeof(char)); // 1,000,000,000 bytes -> 8 billion numbers : 1GB
    i64* twins = calloc(50000000, sizeof(i64)); // 80,000,000 bytes, 80Mb
    if (!twins) {printf("Out of memory :(\n"); return 0;}

    int current_index = 2;
    
    u32 location;
    int _ = fscanf(in, "%lu", &location);
    _ = fscanf(in, "%lu", &location);
    _ = fscanf(in, "%lu", &location); // duplicate 5 >:(
    twins[0] = 3;
    twins[1] = 5;
    while (location < 50000000) {
        int _ = fscanf(in, "%lu", &location);
        twins[current_index++] = location;
    }
    fseek(in,0,SEEK_SET);
    while (location < 8000000000) {
        int _ = fscanf(in, "%lu", &location);
        //printf("\r%lu", location);
        big_bitfield[location / 8] |= 1 << (location & 7);
    }
    fclose(in);
    printf("Successfully read in file!\n"); fflush(stdout);

    unsigned short suppressed_printing = 0;

    for (i64 i = 2; i < 8000000000; i += 2) { // i = num being tested
        if (!(suppressed_printing++)) {printf("\rTesting: %lli", i);}
        if (is_active(big_bitfield, i - 1)) {i += 20;}
        i64 remainder = 0;
        for (i64 twindex = 0; twindex < 50000000; twindex++) {
            remainder = i - twins[twindex];
            if (remainder < 0) {
                printf("Exception: %lli\n", i);
                fprintf(out, "Exception: %lli\n", i); fflush(stdout); break;
            }
            if (is_active(big_bitfield, remainder)) {
                break;
            }
            if (twindex + 1 == 50000000) {fprintf(out, "Exception: %lli\n", i); fflush(stdout); break;}
        }
    }
    printf("\nDone\n");
}
