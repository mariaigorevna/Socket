#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket

sock = socket.socket()
sock.connect(('localhost', 8000))
sock.send("Hello, SERVER".encode())

data = sock.recv(1024)
print('Data from server:\n', data)
sock.close
