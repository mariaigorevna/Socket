FROM debian
RUN apt update
RUN apt install g++ python3 python -y
RUN apt install  nano -y
RUN apt install libpcap-dev libssl-dev -y
COPY ./Client.py /home/masha/Client.py
COPY ./Server.py /home/masha/Server.py
COPY ./SocketClient.cpp /home/masha/SocketClient.cpp
COPY ./SocketServer.cpp /home/masha/SocketServer.cpp
ENTRYPOINT /bin/bash
