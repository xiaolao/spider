FROM ubuntu:latest

ENV TZ=Asia/Shanghai

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update -y && apt-get install -y git && apt-get install -y build-essential && \
    apt-get install -y libcurl4-gnutls-dev && apt-get install -y libuv1-dev && \
    apt-get install -y libxml2-dev && apt-get install -y libpcre3 libpcre3-dev && \
    echo "Asia/Shanghai" > /etc/timezone && DEBIAN_FRONTEND=noninteractive dpkg --configure -a \
    && DEBIAN_FRONTEND=noninteractive apt-get -yq install dh-autoreconf && \
    cd /root && git clone git://github.com/bbcarchdev/liburi.git && cd /root/liburi && \
    git submodule update --init --recursive && autoreconf -i && ./configure --prefix=/usr && \
    make && make install

ADD core /root/core

RUN cd /root/core && make && make install

ADD sample /root/demo

WORKDIR /root/demo

RUN gcc -o test main.c -lcspider -I /usr/include/libxml2

CMD ["/bin/bash", "./test"]