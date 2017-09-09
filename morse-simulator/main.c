#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>
#include <time.h>



void sleep_ms(int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}


int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char message[1000], *server_reply;
	float z = 0.0;
	int i = 0;


	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 4000 );


	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	printf("Connected\n");



	while (1) {


		while(z<10.0)
		{
			i++;

			sprintf(message, "id%d quad.teleport translate [0, 0, %7.3f]\r\n", i, z);
			z+=0.001;


			if( send(socket_desc , message , strlen(message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}

			sleep_ms(100);
		}

	}
	return 0;
}
