#!/usr/bin/env python
# -*- coding: utf-8 -*-
import socket



sock = socket.socket()
sock.bind(('', 8000))
sock.listen(1)
conn, addr = sock.accept()

print ('Connected: ', addr)
while True:
    data = conn.recv(1024)
    if not data:
        break
    conn.send(data.upper())
conn.close()
