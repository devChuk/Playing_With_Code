import socket 

address = '' #this will make bind set host to the address of the machine 
port = 4200
queued = 5
size = 1024
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #creates socket object
server.bind((address,port))
server.listen(queued) 
while 1:
    client, address = server.accept() 
    message = client.recv(size) 
    if message: 
        client.send(message) 
    client.close()