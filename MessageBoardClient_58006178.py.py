import sys
import socket
from socket import *

# Several established variables for client side.
BUFFER_SIZE = 4096
TIMEOUT = 5  # Timeout for server response in seconds

def create_socket():
    s = socket(AF_INET, SOCK_STREAM)
    s.settimeout(TIMEOUT)
    return s

s = create_socket()
serverResponse = ""

# Receiving client input such as IP Address and server port.
def getClient():
    global serverIp, serverPort
    print("Please initialize your connection to the server: ")
    try:
        serverIp = input("Input the IP Address: ")
        serverPort = int(input("Input the server port: "))
    except KeyboardInterrupt:
        print("Keyboard Interrupt Detected (CTRL+C) during input, please run again!")
        sys.exit()
    ConnectToServer()

# Establishing connection to the server, has some error checking.
def ConnectToServer():
    global serverIp, serverPort, s 
    while True:
        try:
            s.connect((serverIp, serverPort))
            s.setsockopt(IPPROTO_TCP, TCP_NODELAY, 1)
        except (ValueError, TimeoutError, OSError, OverflowError):
            print("Connection Failed, Please try again.")
            getClient()
            return True
        else:
            print("Connection Successful! Start Inputting Messages: ")
            return False

#Function to send data with error handling
def safe_send(data):
    try:
        s.send(data.encode())
    except Exception:
        print("Warning: Unable to send message to server.")

#Function to receive data with error handling
def safe_recv():
    try:
        return s.recv(BUFFER_SIZE).decode()
    except Exception:
        print("Warning: No response from server.")
        return None

# POST function
def post():
    safe_send('POST')
    while True:
        new_msg = input("client: ")
        if new_msg == '#':
            break
        safe_send(new_msg)
    safe_send('#')
    serverResponse = safe_recv()
    print("server:", serverResponse)
# GET function
def get():
    safe_send('GET')
    while True:
        serverResponse = safe_recv()
        if serverResponse is None or serverResponse == '#':
            print("server:", serverResponse)
            break
        print("server:", serverResponse)
    

# DELETE function
def delete():
    safe_send('DELETE')
    while True:
        deleted = input("client: ")
        if deleted == "#":
            break
        else:
            safe_send(deleted)
    safe_send('#')
    serverResponse = safe_recv()
    if serverResponse:
        print("server:", serverResponse)

# Program control of client side
def start():
    while True:
        command = input("client: ")
        if command == "POST":
            post()
        elif command == "GET":
            get()
        elif command == "DELETE":
            delete()
        elif command == "QUIT":
            safe_send('QUIT')
            serverResponse = safe_recv()
            if serverResponse:
                print("server:", serverResponse)
            return
        else:
            safe_send(command)
            serverResponse = safe_recv()
            if serverResponse:
                print("server:", serverResponse)

# Rundown of connection within client side
getClient()
try: 
    start()
    s.close()
except KeyboardInterrupt:
    print("Keyboard Interrupt Detected (CTRL+C), restart connection please!")
    safe_send('QUIT')
    s.close()