#include <stdio.h>
#include <stdlib.h>

int assertE(int a, int b) {
    return a == b;
}

int assertNE(int a, int b) {
    return a != b;
}

int passCount = 0;
int failCount = 0;

int test(char* name, int passed) {  
    printf("[%s]\t%s\n", passed ? "PASS" : "FAIL", name);
    if (passed)
        passCount++;
    else
        failCount++;
}

void summarize() {
    if (!failCount) {
        printf("\nALL TESTS PASSED\n");
    } else {
        printf("Failed %d tests\n", failCount);
    }
}

int main(int argc, char** argv) {
    printf("decap %s\nRunning tests...\n", __TIME__);
    
    
    test("Size of off_t must be > 4",
            assertE(sizeof(off_t) > (size_t) 4, 1));
    
    summarize();
    
    return (EXIT_SUCCESS);
}