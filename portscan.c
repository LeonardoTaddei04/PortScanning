#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <IP>\n", argv[0]);
        return 1;
    }

    char *target_ip = argv[1];
    int port;

    for (port = 1; port <= 1024; port++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("socket");
            return 1;
        }

        struct sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(target_ip);

        if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("Porta %d aperta\n", port);
        }

        close(sock);
    }

    return 0;
}
