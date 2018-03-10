import ui
import socket
import time

def sw1(s):
	tx.sendto(bytes('1', 'utf-8'), (HOST, PORT))

def sw2(s):
	tx.sendto(bytes('2', 'utf-8'), (HOST, PORT))

def sw3(s):
	tx.sendto(bytes('3', 'utf-8'), (HOST, PORT))

def all(s):
	v['button1'].background_color = on
	v['button2'].background_color = off
	v['button3'].background_color = off
	
v = ui.load_view()
v.present('sheet')

HOST, PORT = '192.168.4.1', 7000
rx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
time.sleep(1)
rx.bind(('', 9000))
tx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

on= '#a4ff77'
off = '#b0b0b0'

all('')

while True:
	d1 = str(rx.recv(32), 'utf-8')
	d2 = d1.split('/')
	mode = d2[0]								#mode
	temp = d2[1]								#temperatura
	hume = d2[2]								#humedad
	
	if mode == 'd': 						# sensor data
		v['textfield1'].text = temp
		v['textfield2'].text = hume
		
	if mode == 't': 						# time data
		sw = d2[1]
		all('')
		v['button1'].background_color = off
		if sw == '1':
			v['button1'].background_color = on
		if sw == '2':
			v['button2'].background_color = on
		if sw == '3':
			v['button3'].background_color = on
