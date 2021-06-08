
import socket
import json

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 8728        # The port used by the server

def communicate_with_server():
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		try:
			s.connect((HOST, PORT))
		except Exception as e:
			print("* Connection failed.")
			exit()

		print("* Connection succeeded \n")
		"""
		# Signup
		json_dict = {"username": 'user1', "password": '1234', "mail": 'user1@gmail.com'}
		code = 10 # signup
		s.sendall(generate_buffer(code, json_dict))

		reply = s.recv(1024).decode()
		print(reply)
		
		
		# Signup
		json_dict = {"username": 'user2', "password": '1234', "mail": 'user2@gmail.com'}
		code = 10 # signup
		s.sendall(generate_buffer(code, json_dict))

		reply = s.recv(1024).decode()
		print(reply)
		"""
		
		#login
		json_dict = {"username": 'user1', "password": '1234'}
		code = 11 # login
		s.sendall(generate_buffer(code, json_dict))

		reply = s.recv(1024).decode()
		print(reply)

		#login
		json_dict = {"username": 'user1', "password": '1234'}
		code = 15 # login
		s.sendall(generate_buffer(code, json_dict))

		reply = s.recv(1024).decode()
		print(reply)
		
def generate_buffer(code: int, msg: dict):
    to_send = bytearray()

    to_send.append(code) # appending message code
    json_msg = json.dumps(msg)

    for x in [hex(len(json_msg) >> i & 0xff) for i in (24,16,8,0)][::-1]: # appending data length
        to_send.append(int(x, 16))

    for x in str(json_msg): # appending json message
        to_send.append(ord(x))

    print("Packet to send: ", to_send, end="")
    return to_send


def main():
	communicate_with_server()

if __name__ == "__main__":
	main()