# decap

Library for extracting packet offsets and file information from packet captures
in the pcap format (not pcap-ng).

## Usage
1. Open a file descriptor to a pcap file
2. Allocate a `pcap_file` from `pcapfile.h`
3. Initialize it via `load` in `decap.c` (this allocates a space for the header
and initializes it as well).

The `pcap_file` struct will keep track of the current read position in the
capture file, so you can continuously check if there are more packets available
and read the next one. The following functions are available in `decap.c`:

* `readPacket`
* `debugAll` reads the entire capture, printing out information about the file
and every packet header encountered.