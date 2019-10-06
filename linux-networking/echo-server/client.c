/*
 * C program to demonstrate socket programming as well as explicitly assigning
 * a port number on Client Side
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

void clear_stdin(void)
{
        if (fseek(stdin,0,SEEK_END))
                fprintf(stderr, "%s: fseek failed\n", __func__);
}

int main(int argc, char **argv)
{
        int cfd;
        int ret = EXIT_FAILURE;

        cfd = socket(AF_INET, SOCK_STREAM, 0);
        if (cfd < 0) {
                perror("Error in client creating\n");
                return ret;
        }

        if (setsockopt(cfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
                perror("Unable to setsockopt\n");
                goto error;
        }

        printf("Client created\n");

        {
                struct sockaddr_in my_addr;

                my_addr.sin_family = AF_INET;
                my_addr.sin_port = htons(12000);
                my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


                if (connect(cfd, (struct sockaddr *)&my_addr, sizeof(my_addr))) {
                        perror("Error in Connection\n");
                        goto error;
                }
        }

        printf("Client connected to ECHO server\n");
        while (ret != EXIT_SUCCESS) {
                char buf[32] = {0};

                printf("\n--- Send end to end session, exit to end everything ---\n");

                clear_stdin();
                printf("Enter your message: ");
                if (!fgets(buf, sizeof(buf), stdin)) {
                        perror("Unable to get input from user, retrying ...\n");
                        continue;
                }
                buf[strlen(buf) - 1] = '\0';

                if (send(cfd, buf, sizeof(buf), 0) < 0) {
                        perror("Unable to send, retrying ...\n");
                        goto error;
                }

                if (recv(cfd, buf, sizeof(buf), 0) <= 0) {
                        perror("Unable to receive, retrying ...\n");
                        goto error;
                }
                printf("Server replied: %s\n", buf);

                if (!strcmp(buf, "exit") || !strcmp(buf, "end"))
                        ret = EXIT_SUCCESS;
        }

error:
        if (cfd > 0)
                close(cfd);

        return ret;
}

