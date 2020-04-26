FROM ubuntu

RUN apt-get update && apt-get install -y \
	python3-pip \
	wget

RUN pip3 install googletrans

RUN wget http://kindlegen.s3.amazonaws.com/kindlegen_linux_2.6_i386_v2_9.tar.gz -O /tmp/kindlegen_linux_2.6_i386_v2_9.tar.gz
RUN tar -xzf /tmp/kindlegen_linux_2.6_i386_v2_9.tar.gz -C /tmp
RUN mv /tmp/kindlegen /usr/bin
RUN rm -r /tmp/*

COPY . .

ENTRYPOINT ["/bin/bash","./run.sh"]
