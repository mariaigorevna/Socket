#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/un.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, servlen,n;
    socklen_t clilen;
    struct sockaddr_un cli_addr, serv_addr;
    char buf[80];
	
/* получаем свой сокет-дескриптор: */
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Error creating socket\n";
        exit(EXIT_FAILURE);  //Макрос EXIT_FAILURE используется для возвращения ОС кода о неудачном завершении программы
    }
   
/* создаем адрес, c которым будут связываться клиенты */   
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
	
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        std::cerr << "Error binding socket\n";
        exit(EXIT_FAILURE); //Макрос EXIT_FAILURE используется для возвращения ОС кода о неудачном завершении программы
    }

/* слушаем запросы на сокет */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

/* связываемся с клиентом через неименованный сокет с 	дескриптором d1:*/
    newsockfd = accept(sockfd, (struct sockaddr *)& cli_addr, &clilen);
    if (newsockfd < 0)
    {
        std::cerr << "Error accepting socket\n";
        exit(EXIT_FAILURE);
    }

    n = read(newsockfd, buf, 80);
    std::cout << "A connection has been established\n";
    write(1, buf, n);
    write(newsockfd, "I got your message\n", 19);
	
/* завершаем сеанс работы */
    close(newsockfd);
    close(sockfd);
    return 0;
}