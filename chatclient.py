# Kabir Kang
# C372
# kangk@onid.oregonstate.edu
# 10/28/14
# Assignment 1
# File: chatclient.py
# Summary: Chats with chatserve.cpp

# General imports
import getopt # necessary for -k
import os
import sys
import signal

#Program specific imports
# parse returns a document from input
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
        sendMsg = raw_input("Client> ")
        sock.send(sendMsg)

        if sendMsg == "\quit":
            sock.close
            sys.exit()

        message = msgIn(sock)
        if message == "\quit":
            print "The server has quit communication.\n"
            sys.exit()
        else:
            print name + "> " + message
    sock.close()

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

def signalfy():
    signal.signal(signal.SIGQUIT, handleSigs)
    signal.signal(signal.SIGHUP, handleSigs)
    signal.signal(signal.SIGINT, handleSigs)


if __name__ == '__main__':
    client()
