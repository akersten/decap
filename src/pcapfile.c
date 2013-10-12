#include <stdio.h>
#include <stdlib.h>

#include "pcapfile.h"

void printPacketHeader(pcap_packet_header* header) {
    printf("--- PACKET ---\n");
    printf("Seconds: %d\n", header->ts_sec);
    printf("Microsec: %d\n", header->ts_usec);
    printf("Incl_len: %d\n", header->incl_len);
    printf("Orig_len: %d\n", header->orig_len);

}

void printFileHeader(pcap_header* header) {
    printf("=== FILE HEADER ===\n");
    printf("Magic number: %x\n", header->magic_number);
    printf("Major version: %d\n", header->version_major);
    printf("Minor version: %d\n", header->version_minor);
    printf("Timezone offset: %d\n", header->thiszone);
    printf("Sigfigs: %d\n", header->sigfigs);
    printf("Max packet count: %d\n", header->snaplen);
    printf("Network type: %d\n", header->network);
}

void printFile(pcap_file* header) {
    printf("=== FILE ===\n");
    printf("Descriptor: %d\n", header->fd);
    printf("Bytes reversed?: %d\n", header->bytesNeedFlipping);
    printf("Nano resolution: %d\n", header->nanoResolution);
    printf("Fixed size: %d\n", header->fixedSize);
}