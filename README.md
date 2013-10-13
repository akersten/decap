# decap

Library for extracting packet data from packet captures in the pcap format.

## Usage
1. Open a file descriptor to a pcap file (`open` syscall, not `fopen`).
2. Initialize a `pcap_file` struct
3. Invoke `load` on it (this allocates space in memory for the header and
reads it in as well). Be sure to `unload` this when you're done with it.
4. Use the following functions to interact with the file. See the comments in
`decap.h` for more information.

* `readPacket` reads the header and payload of a packet - this could be any
kind of protocol, the size of these are contained in their respective header.
In my experiments, they've been pretty consistent (MTU-sized) but that will
depend on the protocol. You'll need to pass it a `pcap_packet` handle, which
you'll then need to invoke `unloadPacket` on when you're done with it.
* `more` determines whether this file has more packets to read. Non-zero for
true, zero if EOF.