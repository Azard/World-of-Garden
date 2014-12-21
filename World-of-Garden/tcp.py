from socket import *
import win32api
import win32con

host = '192.168.137.1'
port = 8081
bufsiz = 1024
 

tcpSerSock = socket(AF_INET, SOCK_STREAM)
#tcpSerSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
tcpSerSock.bind((host, port))
tcpSerSock.listen(5)

 
while True:

	print 'waiting for connection...'
	tcpCliSock, addr = tcpSerSock.accept()
	print '...connected from:', addr
 
	while True:
		data = tcpCliSock.recv(bufsiz)
		print data
		if not data:
			break
		if data == "0000010001":
			win32api.keybd_event(67,0,0,0)
		if data == "0000020001":
			win32api.keybd_event(67,0,win32con.KEYEVENTF_KEYUP,0)
		if data == "0000010002":
			win32api.keybd_event(37,0,0,0)
		if data == "0000020002":
			win32api.keybd_event(37,0,win32con.KEYEVENTF_KEYUP,0)
		if data == "0000010003":
			win32api.keybd_event(38,0,0,0)
		if data == "0000020003":
			win32api.keybd_event(38,0,win32con.KEYEVENTF_KEYUP,0)
		if data == "0000010004":
			win32api.keybd_event(39,0,0,0)
		if data == "0000020004":
			win32api.keybd_event(39,0,win32con.KEYEVENTF_KEYUP,0)	

	tcpCliSock.close()
tcpSerSock.close()