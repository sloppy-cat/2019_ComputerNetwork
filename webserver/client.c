#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE sizeof(struct sockaddr_in)
int main()
{
        int sockfd;
        char send_c, recv_c;

        struct sockaddr_in server = {AF_INET, 3578, INADDR_ANY};

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("fail to call socket()\n");
        exit(1);
        }

        if(connect(sockfd, (struct sockaddr *)&server, SIZE) == -1) {
        printf("fail to call connect()\n");
        exit(1);
        }

 

        recv_c = '\n';
        while(1) {
        if(recv_c == '\n')
        printf("Input a message (enter 'Q' : quit server connection) \n");
	send_c = getchar();
	if (send_c == 'Q'){
		close(sockfd);
		exit(1);
	}
        send(sockfd, &send_c, 1, 0);

        if(recv(sockfd, &recv_c, 1, 0) > 0)
        printf("%c", recv_c);

        else{
        printf("server has no reply\n");
        close(sockfd);
        exit(1);
                }
        }
}
