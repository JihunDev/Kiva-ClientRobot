#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_BUFFER_SIZE_	10000

void error_handling(char *message);

int main(void)
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[MAX_BUFFER_SIZE_];
	char sendMessage[] = "hihihi";
	int str_len;
	int j;
	FILE *out;
	
	sock = socket(PF_INET, SOCK_STREAM,0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("40.74.134.0");
	serv_addr.sin_port = htons(5000);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");

	else
		printf("Connection Success\n");

	str_len = read(sock, message, sizeof(message) -1);
	write(sock, sendMessage, sizeof(sendMessage) -1);
	if(str_len == -1)
		error_handling("accept() error");
	message[str_len] = 0;
        while(1)
	{
	 printf("message from server : %s \n", message);
	 memset(message, 0, MAX_BUFFER_SIZE_);
	 for(j = 0 ; j < 1000000000 ; j++);

 	}
	out = fopen("json_data.txt","wt+");
	fputs(message,out);
	fclose(out);
//	input();
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
