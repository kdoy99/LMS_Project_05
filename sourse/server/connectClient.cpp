#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "client.cpp"

using namespace std;

#define BUF_SIZE 1000000
void error_handling(string message);

int main(int argc, char *argv[])
{
    Member_Information MI[100]; 
    Book_Information BI[100];   
    int m_idx = 0, mt_idx = 0;   // 인덱스 초기화
    char login_ID[20];

	int sock;
	pid_t pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;
	if(argc!=3) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
    sock=socket(PF_INET, SOCK_STREAM, 0);   
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
    {
        error_handling("connect() error!");
    }

    // login(MI, BI, &m_idx, &mt_idx, login_ID);
    
    while (1)
    {
        fputs("책 제목 검색(종료하려면 q): ", stdout);
        fgets(buf, BUF_SIZE, stdin);

        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            break;
        }
        write(sock, buf, BUF_SIZE); // 문자열
        
        
        read(sock, buf, BUF_SIZE);
        printf("Message from server : %s\n", buf);
    }
    
    close(sock);
    return 0;
}

void error_handling(string message)
{
	cout << message << endl;
    exit(1);
}