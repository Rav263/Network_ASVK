FROM ubuntu


RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y make
RUN apt-get install -y git

RUN git clone -b docker_test https://github.com/RAV263/Network_ASVK

WORKDIR Network_ASVK
RUN git pull
COPY client.txt ./
RUN cat client.txt


RUN chmod +x make_client.sh
RUN ./make_client.sh

CMD ["./client.out", "<", "client.txt"]

