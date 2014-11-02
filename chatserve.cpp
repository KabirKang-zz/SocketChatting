#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int checkArg(int, char **);
void createSocket(int);
void bindSocket();
void listenSocket();
void acceptConn();

struct sockaddr_in servaddr;
int listenfd, connfd;
char* servName = "Kabir";


int main(int argc, char ** argv)
{
  int commence; // Here we check if we have a port number to work with
  int portNum;  

if((commence = checkArg(argc, argv))==1)
    {
      return 1;
    }
 portNum = atoi(argv[1]);
  createSocket(portNum);
  bindSocket();
  listenSocket();
  acceptConn();

  return 0;
}

int checkArg(int argc, char** argv)
{
  if(argc!=2)
    {
      cerr << "This program requires 1 argument, the port number." << endl;
      return 1;
    }
  return 0;
}

void createSocket(int portNum)
{
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, '0', sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(portNum); 
}

void bindSocket()
{
  bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
}

void listenSocket()
{
  listen(listenfd, 10); 
}

void acceptConn()
{
  while(1)
    {
      connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

      send(connfd,servName,strlen(servName),0);
      //char* message="This is a message to send\n\r";
      char message[81];
      char recMessage[81];
      std::cin >> message;      
      //cin >> message;
      send(connfd,message,strlen(message),0); 
      recv(connfd,recMessage,80,0);
      std::cout << recMessage << endl;

      close(connfd);
      sleep(1);
    }
}
