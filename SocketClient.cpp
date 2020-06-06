#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/un.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int sockfd, servlen, n;
    struct sockaddr_un serv_addr;
    char buffer[82];

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Error creating socket\n";
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        std::cerr << "Error connecting to server";
        exit(EXIT_FAILURE);
    }

    std::cout << "Enter your message:\n";
    bzero(buffer, 82);
    fgets(buffer, 80, stdin);
    write(sockfd, buffer, strlen(buffer));
    n = read(sockfd, buffer, 80);
    std::cout << "Return message:\n";
    write(1, buffer, n);
    close(sockfd);
    return 0;
}