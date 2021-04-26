
import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 8728        # The port used by the server

def communicate_with_server():
    try:
        s.connect((HOST, PORT))
    except Exception as e:
        print("* Connection failed.")
        exit(1)

    print("* Connection succeeded \n")

	json_dict = {"username" : 'user1', "password" : '123', "Email" : '123@123'}
	string_json = json.dumps(json_dict)
	str_send = chr(1) + string_json

	sock.send(str_send.encode())


	data = sock.recv(1024)
	print(data)

	input()

	sock.close()



def main():
	communicate_with_server()

if __name__ == "__main__":
	main()