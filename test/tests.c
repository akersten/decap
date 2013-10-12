#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <string.h>

#include "../src/decap.h"


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
    printf("decap %s %s\nRunning tests...\n", __TIME__, __DATE__);
    
    
    test("Size of off_t must be > 4",
            assertE(sizeof(off_t) > (size_t) 4, 1));
    test("Size of size_t must be > 4",
            assertE(sizeof(size_t) > (size_t) 4, 1));
    test("Size of uint32_t is 4", assertE(sizeof(uint32_t), 4));
    test("Size of uint16_t is 2", assertE(sizeof(uint16_t), 2));
    test("Size of uint8_t is 1", assertE(sizeof(uint8_t), 1));
    
    /*char buf[128];
    getcwd(buf, sizeof(buf));
    printf("Working dir: %s\n", buf);*/
    int fd = open("nocommit/test.pcap", O_RDONLY);
    test("File open: test.pcap", assertNE(fd, -1));
    
    pcap_file pf;
    
    if (fd > 0) {
        int lret = load(fd, &pf, 0);
        test ("Loaded file", assertNE(lret, 0));
    test("Read test file test.pcap",
            assertNE(debugAll(&pf), 0));
    } else {
        printf("io err: %s\n", strerror(errno));
    }
    
    if (fd > 0) {
        close(fd);
    }
    
    summarize();
    
    return (EXIT_SUCCESS);
}