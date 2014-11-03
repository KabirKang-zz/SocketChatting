# Kabir Kang
# C372
# kangk@onid.oregonstate.edu
# 10/28/14
# Assignment 1
# File: chatclient.py
# Summary: Chats with chatserve.cpp. First it creates a connection with listening server, and then it can begin interchange. Client messages first, then server.

# General imports
import getopt
import os
import sys
import signal

#Program specific imports
import socket 

def client():
    checkArgs();
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((sys.argv[1],int(sys.argv[2])))    
# set up handlers
    signalfy()
    name = getName(sock)
    var = 1
    while var == 1:
        # Receive and send prompt
	msgOut(sock)

	message = msgIn(sock)
	if message == "\quit":
		print "The server has quit communication.\n"
		sys.exit()
	else:
		print name + "> " + message
    sock.close()
# This function receives the name of the server.                
def getName(s):
    name = s.recv(4096)
    return name


# Summary: signal handler
def handleSigs(signum, frame):
    sys.exit()

def checkArgs():
    if len(sys.argv) != 3:
        print "You must use the following syntax: python chatclient.py <host> <port>"
        sys.exit()

# Summary: Returns messages
def msgIn(s):
	message = str(s.recv(4096)) #recommended buff size
	return message
# Summary: This function sends messages.
def msgOut(s):
	sendMsg = raw_input("Client> ")
	s.send(sendMsg)
	if sendMsg == "\quit":
		s.close
		sys.exit()
# This function sets up signal handlers.
def signalfy():
    signal.signal(signal.SIGQUIT, handleSigs)
    signal.signal(signal.SIGHUP, handleSigs)
    signal.signal(signal.SIGINT, handleSigs)


if __name__ == '__main__':
    client()
