#include <stdio.h>
#include <gmp.h>

typedef unsigned long long u64;

int main(int argc, char* argv[]) {
    FILE* out = fopen("twin_prime_list.txt", "w");
    mpz_t val;
    mpz_t val_p2;
    mpz_init_set_ui(val, 1);
    mpz_init_set_ui(val_p2, 3);

    // 10,000,000,000,000
    for (u64 i = 3; i < 4200000000; i += 2) {
        mpz_add_ui(val, val, 2);
        mpz_add_ui(val_p2, val_p2, 2);

        int res = mpz_probab_prime_p(val, 1); // 5 reps is fine.
        if (res == 2) {
            if (mpz_probab_prime_p(val_p2, 1) == 2) {
                fprintf(out, "%llu\n%llu\n", i, i+2);
            }
        }
        else {
            if (res == 1) {
                printf("End of guaranteed primality testing at i = %llu\n", i);
                return 0;
            }
        }
    }
}