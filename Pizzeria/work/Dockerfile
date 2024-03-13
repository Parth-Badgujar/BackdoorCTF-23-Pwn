FROM ubuntu:22.04
RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd \
 && rm -rf /var/lib/apt/lists/*
RUN useradd hacker
RUN mkdir /pwn
RUN echo "You've been blocked by our server,try again, and report if this repeats." > /etc/banner_fail
COPY ./ctf.xinetd /etc/xinetd.d/pwn
COPY ./start.sh /start.sh
COPY ./setup.sh /setup.sh
COPY ./chal /pwn/
COPY ./ld-linux-x86-64.so.2 /pwn/
COPY ./libc.so.6 /pwn/
COPY ./flag.txt /pwn/flag.txt
RUN chown -R root:hacker /pwn && chmod -R 750 /pwn
RUN chmod +x /setup.sh
RUN chown root:hacker /start.sh && chmod 750 /start.sh

CMD ["/setup.sh"]

EXPOSE 10078
