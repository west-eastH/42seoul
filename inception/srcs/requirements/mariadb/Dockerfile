FROM alpine:3.19

RUN apk update && apk add --no-cache mariadb mariadb-client mariadb-server-utils dumb-init

COPY ./conf/my.cnf /etc/my.cnf

COPY ./tools/run-mariadb.sh /usr/local/bin/run-mariadb.sh
RUN chmod +x /usr/local/bin/run-mariadb.sh

ENTRYPOINT ["/usr/bin/dumb-init", "--"]
CMD ["/usr/local/bin/run-mariadb.sh"]
