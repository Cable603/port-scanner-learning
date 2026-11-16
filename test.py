import socket

"""
Creating a socket
- Allocates memory(Its an object, duh)
- Creates internal socket DS
- Assigns it a file descriptor(Linux/macOS) or socket handle(Windows)
- Returns reference

Doesn't actually open a connection yet, it just makes an object
"""
client = socket.socket(
    socket.AF_INET,     #IPv4
    socket.SOCK_STREAM  #TCP
)

client.settimeout(2)    #Sets time in seconds for wait before stopping connection attempts

print(client)

"""
Connecting to a host
- How DNS works in the process
- What the OS does
- TCP handshake(For SOCK_STREAM)
- Connection failure
"""

try: 
    """
    To use IP address instead, use IPAdress.parse("0.0.0.0")
    python -> socket -> kernel -> DNS lookup -> routing table -> network card -> internet -> host
    Connect essentially assigns the interface to use, which ip we are going to, and what ephemeral port we use as source ip
    """
    client.connect(("google.com", 80))  #First parameter is host, second is port
    print("Success")
except Exception as error:
    print(error)
    
"""
connect_ex() does same thing but returns numbers instead of raising errors
0 means success
anything else is an error
"""
result = client.connect_ex(("youtube.com", 443))  #First parameter is host, second is port
if result == 0:
    print("Success")
else: 
    print("Failed")

client.close() #Closes the socket, does not delete variable



"""
Simple port scanner script
"""
host = "google.com"

for port in range(20,21):

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.settimeout(1)

    result = client.connect_ex((host, port))

    if result == 0:
        print(f"Port {port} is OPEN")
    else:
        print(f"Port {port} is CLOSED")

    client.close()
    

"""
Sending and recieving data

TCP doesn't understand anything but bytes, network is in hexadecimal
text1 = "Hello":str
text2 = b"Hello":bytes

The process of changing a value to bytes is encoding, usually in UTF-8
Decoding is the opposite, use encode() and decode() function
"""

client = socket.socket(
    socket.AF_INET,
    socket.SOCK_STREAM
)
client.settimeout(2)
result = client.connect_ex(("google.com", 443))
if result != 0:
    print("Failed")
else:
    client.send(b"Hello")   #send() does not guarantee all bytes are trasmitted in one call
    client.sendall(b"Hello again")  #Repeatedly calls send internally until all accepted or error

    client.recv(1024)   #1024 is the maximum to read, prevents all in one
    response = b""
    while True:
        chunk = client.recv(1024)
        if chunk == b"":
            break
        response += chunk


"""
Building a TCP Server
- bind(), listen(), accept()
- Servers are different from clients
- Only one process can bind to a port(Usually)
- Client server communication

0.0.0.0 means "Listen on every network interface"
"""

server = socket.socket(
    socket.AF_INET,
    socket.SOCK_STREAM
)
server.bind(("0.0.0.0", 5000))  #"This socket owns port 5000" Nothing has started yet
client_socket, address = server.accept()    #Does nothing until client connects




