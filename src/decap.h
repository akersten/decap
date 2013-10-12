#ifndef DECAP_H
#define	DECAP_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pcapfile.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Reads header information about a pcap file. Also does basic verification
     * of the file (checking magic number, etc.) This will allocate space for
     * a `pcap_header` struct as well. Be sure to unload the file when finished.
     * 
     * @param fd An open file descriptor to a pcap file.
     * @param pcapFile Fill-in target.
     * @param fixedSize If this file is not expected to grow in size. This will
     * speed up operations like more() since we can record the file size at the
     * initial opening instead of seeking to the end every time. Set to 0 if
     * this file is live (being appended to), otherwise set to non-zero.
     * @return Non-zero if success (no errors reading and seems like a valid
     * file), zero otherwise.
     */
    int load(int fd, pcap_file* pcapFile, int fixedSize);
    
    /**
     * Deallocates any memory used by the referenced pcap_file struct. Not
     * responsible for closing the file handle (just like load isn't resposible
     * for opening a file handle).
     * 
     * @param pcapFile The pcap file to unload.
     * @return Should always be non-zero.
     */
    int unload(pcap_file* pcapFile);
    
    
    int readPacket(pcap_file* pcapFile, pcap_packet_header* packetHeader, 
            pcap_packet_data* packetData);
    
    /**
     * Whether there's another packet available from this stream without hitting
     * EOF.
     * @param pcapFile The pcap_file handle.
     * @return Non-zero if packet available, zero otherwise.
     */
    int more(pcap_file* pcapFile);
    
    /**
     * Finds every packet header in the pcap file and prints it.
     * 
     * @param pcapFile The file to enumerate.
     * @return Non-zero on success.
     */
    int debugAll(pcap_file* pcapFile);
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DECAP_H */

