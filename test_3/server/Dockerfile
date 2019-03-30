FROM ubuntu


RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y make
RUN apt-get install -y git

RUN git clone -b docker_test https://github.com/RAV263/Network_ASVK

WORKDIR Network_ASVK
RUN git pull

COPY server.txt ./

RUN ./make_server.sh

CMD ["./server.out", "<", "server.txt"]

