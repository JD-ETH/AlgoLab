#include<stdio.h>

void do_case() {

    // read number of bits
    int n;
    scanf("%i", &n);

    // init
    int count = 0, evens = 0, odds = 0;

    // run for all bits
    for(; n; n--) {

        // read bit
        int b;
        scanf("%i", &b);

        // adjust evens and odds
        if(b) {
            int tmp;
            tmp = odds;
            odds = evens+1;
            evens = tmp;
        }
        else {
            evens++;
        }

        // add evens to total
        count += evens;
    }

    // output result
    printf("%i\n", count);
}

int main() {

    // read number of cases
    int t;
    scanf("%i", &t);

    // run all cases
    for(; t; t--) {
        do_case();
    }

    return 0;
}
