/*
 * Simple echo server
 * C program to demonstrate socket programming in finding ip address and port
 * number of connected client on Server Side
 */

#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void)
{
        int sfd;
        int acc;
        int ret = EXIT_FAILURE;

        sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd < 0) {
                perror("Error in server creating\n");
                return ret;
        }

        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
                perror("Unable to setsockopt\n");
                goto error;
        }

        printf("Server Created\n");

        {
                struct sockaddr_in my_addr;

                my_addr.sin_family = AF_INET;
                my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
                my_addr.sin_port = htons(12000);

                if (bind(sfd, (struct sockaddr*) &my_addr, sizeof(my_addr))) {
                        perror("Unable to bind\n");
                        goto error;
                }
        }

        printf("Binded Correctly\n");

        if (listen(sfd, 0)) {
                perror("Unable to listen\n");
                goto error;
        }

        while (ret != EXIT_SUCCESS) {
                printf("Listening ...\n");

                {
                        struct sockaddr_in peer_addr;
                        char ip[INET_ADDRSTRLEN] = {0};
                        socklen_t addr_size = sizeof(struct sockaddr_in);

                        acc = accept(sfd, (struct sockaddr *)&peer_addr, &addr_size);
                        if (acc < 0) {
                                perror("Unable to accept, retrying ...\n");
                                goto error;
                        }

                        printf("Connection established\n");
                        if (!inet_ntop(AF_INET, &(peer_addr.sin_addr), ip,
                                                INET_ADDRSTRLEN)) {
                                perror("inet_ntop error, retrying ...\n");
                                goto error;
                        }

                        // "ntohs(peer_addr.sin_port)" function is
                        // for finding port number of client
                        printf("Connection established with IP : %s and PORT : %d\n",
                                        ip, ntohs(peer_addr.sin_port));
                }

                while (1) {
                        char buf[32] = {0};

                        printf("\n--- Send 'quit' to end session, 'exit' to end everything ---\n");

                        if (recv(acc, buf, sizeof(buf), 0) < 1) {
                                perror("Unable to receive - Client disconnected\n");
                                break;
                        }
                        printf("Client sent: %s\n", buf);

                        if (send(acc, buf, sizeof(buf), 0) < 0) {
                                perror("Unable to send, retrying ...\n");
                                continue;
                        }

                        if (!strcmp(buf, "exit")) {
                                ret = EXIT_SUCCESS;
                                break;
                        }

                        if (!strcmp(buf, "quit"))
                                break;
                }
                close(acc);
        }

error:
        if (sfd > 0)
                close(sfd);

        return ret;
}
