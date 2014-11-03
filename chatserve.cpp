/*
Name: Kabir Kang
Course: CS 372
Email: kangk@onid.oregonstate.edu
Date: 10/26/14
Assignment 1
File: chatserve.cpp
Summary: Manages connection and chats with chatclient.py; please compile with g++ chatserve.cpp -o chatserve
*/
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
void receiveMessage(int);
void sendMessage(int);
void clearMessages();


struct sockaddr_in servaddr;
int listenfd, connfd;
int closeFlag = 0;
char servName[6] = "Kabir";
char recMessage[81];
char message[81];


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
      closeFlag = 0;
      connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
      std::cout << "Client has connected. Awaiting message... " << endl;
      send(connfd,servName,strlen(servName),0);

	  while(closeFlag==0)
	{
	  clearMessages();
	  
	  receiveMessage(connfd);
	  
	  sendMessage(connfd);
	  

      if(closeFlag==1)
	{
	  close(connfd);
	}
	}

    }
}

void receiveMessage(int connfd)
{
	recv(connfd, recMessage, 80, 0);
	if (strcmp(recMessage, "\\quit") == 0)
	{
		std::cout << "Client has disconnected." << endl;
		closeFlag = 1;
	}
}

void sendMessage(int connfd)
{
	if (closeFlag == 0)
	{
		std::cout << "Client> " << recMessage << endl;
		std::cout << servName << "> ";
		std::cin.getline(message, 81);

	}
	if (strcmp(message, "\\quit") == 0)
	{
		std::cout << "You have chosen to close this connection..." << endl;
		closeFlag = 1;
	}


	send(connfd, message, strlen(message), 0);
}

void clearMessages()
{
	memset(&message[0], 0, sizeof(message));
	memset(&recMessage[0], 0, sizeof(recMessage));
}
