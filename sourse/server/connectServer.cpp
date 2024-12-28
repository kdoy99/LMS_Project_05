#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "connectDB.cpp"

using namespace std;

#define BUF_SIZE 1000000
void error_handling(string message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
    Database db;
    string user_input;

    pid_t pid;
    struct sigaction act;
	socklen_t adr_sz;
    char input[BUF_SIZE];
    string output;
    int* len = new int;
	int str_len, state;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD, &act, 0);
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	

    while (1)
    {
        adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
        if(clnt_sock==-1)
			continue;
		else
			printf("new client connected...\n");
        pid=fork();
        if (pid==-1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid==0)
        {
            close(serv_sock);
            read(clnt_sock, input, BUF_SIZE);
            *len = strlen(input);
            cout << "len: " << *len << endl;
            cout << "input: " << input << endl;
            user_input = input;
            cout << "user_input: " << user_input << endl;
            if (user_input == "카푸")
            {
                cout << "일치!" << endl;
            }
            
            db.openDB(input);

            output = db.searchResult + "-------------------------------\n" + input + "검색 결과입니다.\n" + "총 " + to_string(db.resultCount) + "건\n";
            write(clnt_sock, output.c_str(), BUF_SIZE);
            close(clnt_sock);
            puts("client disconnected...\n");
            return 0;
        }
        else
        {
            close(clnt_sock);
        }
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid=waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d \n", pid);
}
void error_handling(string message)
{
	cout << message << endl;
	exit(1);
}