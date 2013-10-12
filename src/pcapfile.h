#ifndef PCAPFILE_H
#define	PCAPFILE_H

#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif

    /*
     * A lot of this is documented in the Wireshark development pages.
     * http://wiki.wireshark.org/Development/LibpcapFileFormat
     */

    struct pcap_header {
        uint32_t magic_number; /* magic number */
        uint16_t version_major; /* major version number */
        uint16_t version_minor; /* minor version number */
        uint32_t thiszone; /* GMT to local correction */
        uint32_t sigfigs; /* accuracy of timestamps */
        uint32_t snaplen; /* max length of captured packets, in octets */
        uint32_t network; /* data link type */
    };


#ifdef	__cplusplus
}
#endif

#endif	/* PCAPFILE_H */

