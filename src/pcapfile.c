#include <stdio.h>
#include <stdlib.h>

#include "pcapfile.h"

int isPrintable(char c) {
    return (c >= 32) && (c <= 126);
}
void printPacketHeader(pcap_packet_header* header) {
    printf("--- PACKET ---\n");
    printf("Seconds: %d\n", header->ts_sec);
    printf("Microsec: %d\n", header->ts_usec);
    printf("Incl_len: %d\n", header->incl_len);
    printf("Orig_len: %d\n", header->orig_len);

}

void printPacketData(pcap_packet_data* data) {
    printf("--- PACKET DATA ---\n");
    printf("Size: %d\n", data->size);
    printf("Data (ASCII):\n");
    printf("\t");
    int i = 0;
    for (i = 0; i < data->size; i++) {
        if (isPrintable(data->data[i])) {
        printf("%c", data->data[i]);
        }else {
            printf(".");
        }
        if ((i > 99) && (i % 100 == 0)) {
            printf("\n");
        }
    }
    printf("\n");
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