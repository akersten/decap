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

/**
 * Assert equality.
 * 
 * @param a Value a.
 * @param b Value b.
 * @return a == b
 */
int assertE(int a, int b) {
    return a == b;
}

/**
 * Assert inequality.
 * 
 * @param a Value a.
 * @param b Value b.
 * @return a != b
 */
int assertNE(int a, int b) {
    return a != b;
}

/*
 * The poor-man's test suite.
 */
int passCount = 0;
int failCount = 0;

/**
 * Records a test as a pass or failure and prints out the corresponding message.
 * Increments passCount or failCount.
 * 
 * @param name The name of the test.
 * @param passed Whether the test passed or not.
 */
void test(char* name, int passed) {
    printf("[%s]\t%s\n", passed ? "PASS" : "FAIL", name);
    if (passed)
        passCount++;
    else
        failCount++;
}

/**
 * Prints the summary of the executed tests.
 */
void summarize() {
    if (!failCount) {
        printf("\nALL TESTS PASSED\n");
    } else {
        printf("Failed %d tests\n", failCount);
    }
}

/**
 * Just test some elementary features of decap. Makes sure nothing breaks when 
 * doing routine operations, enforces assumptions about type lengths, and
 * exemplifies the usage of the library.
 */
int main(int argc, char** argv) {
    printf("decap %s %s\nRunning tests...\n", __TIME__, __DATE__);


    test("Size of off_t must be > 4",
            assertE(sizeof (off_t) > (size_t) 4, 1));
    test("Size of size_t must be > 4",
            assertE(sizeof (size_t) > (size_t) 4, 1));
    test("Size of uint32_t is 4", assertE(sizeof (uint32_t), 4));
    test("Size of uint16_t is 2", assertE(sizeof (uint16_t), 2));
    test("Size of uint8_t is 1", assertE(sizeof (uint8_t), 1));

    int fd = open("nocommit/test.pcap", O_RDONLY);
    test("File open: test.pcap", assertNE(fd, -1));

    pcap_file pf;

    if (fd > 0) {
        int loadRet;

        loadRet = load(fd, &pf, 0);
        test("Read test file in expand mode", assertNE(loadRet, 0));
        test("Read test file test.pcap",
                assertNE(debug_printPackets(&pf), 0));
        test("Unload expand mode", assertNE(unload(&pf), 0));

        loadRet = load(fd, &pf, 1);
        test("Read test file in fixed size mode", assertNE(loadRet, 0));
        test("Read test file test.pcap",
                assertNE(debug_printPackets(&pf), 0));
        test("Unload fixed size mode", assertNE(unload(&pf), 0));

    } else {
        printf("io err: %s\n", strerror(errno));
    }



    if (fd > 0) {
        close(fd);
    }

    summarize();

    return (EXIT_SUCCESS);
}