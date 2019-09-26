import socket
import threading
import select

def client(args): 
    conn = args["conn"]
    port = args["port"]
    client_table = args["client_table"]
    recive_Data = args["onRecive"]
    while True:
        ready = select.select([conn], [conn], [], 0.1)
        if ready[0]:
            data = conn.recv(1024).decode()
            if(len(data) == 0):
                print("[INFO]    Disconnected")
                conn.close()
                del client_table[port]
                break
            if(data):
                # print("[RECIVED] "+data)
                recive_Data((data,port))
        if ready[1]:
            if(not client_table[port] == None):
                conn.send(client_table[port].encode())

class Server:

    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.client_table = {}
                    
    def onRecive(self, handeler):
        self.reciveData = handeler
    
    def start(self):
        soc = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        soc.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        soc.bind((self.ip,self.port))
        print("[INFO]    Starting server ..")
        print("[INFO]    listening to "+str(self.ip)+":"+str(self.port))
        soc.listen(1)

        while(True):
            conn, addr = soc.accept()
            args = {}
            args["client_table"] = self.client_table
            args["port"] = str(addr[1])
            args["conn"] = conn
            args["onRecive"] = self.reciveData
            self.client_table[str(addr[1])] = None
            print("[INFO]    Client Connected")
            threading.Thread(target=client,args=[args]).start()

    def send_Data(self, port, data):
        self.client_table[port] = data

