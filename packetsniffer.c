#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>

int main() {

    int sockfd;

    unsigned char buffer[65536];

    sockfd = socket(
        AF_PACKET,
        SOCK_RAW,
        htons(ETH_P_ALL)
    );

    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    printf("Listening for packets...\n");

    while (1) {

        int packet_size =
            recvfrom(
                sockfd,
                buffer,
                sizeof(buffer),
                0,
                NULL,
                NULL
            );

        if (packet_size < 0) {
            perror("recvfrom");
            break;
        }

        printf("Packet received: %d bytes\n",
               packet_size);
    }

    close(sockfd);

    return 0;
}
