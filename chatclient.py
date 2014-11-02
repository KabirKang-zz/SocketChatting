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

portNum = 30020

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
sock.connect(("127.0.0.1",portNum)) 

def client():
    # set up handlers
    signalfy()

    # Receive and send prompt
    messages = msgIn(sock)

    for msg in messages:
	    print msg

    sendMsg = raw_input(messages[0])
    sock.send(sendMsg)	    
    sock.close()

# Summary: signal handler
def handleSigs(signum, frame):
	sys.exit()

# Summary: Returns messages
def msgIn(s):
	messages = s.recv(4096) #recommended buff size
	messages = messages.split('\n')
	return messages

def signalfy():
    signal.signal(signal.SIGQUIT, handleSigs)
    signal.signal(signal.SIGHUP, handleSigs)
    signal.signal(signal.SIGINT, handleSigs)


if __name__ == '__main__':
    client()
