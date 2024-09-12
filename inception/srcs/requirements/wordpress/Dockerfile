FROM alpine:3.19

RUN apk update && apk add --upgrade \
    php \
    php-fpm \
    php82-mysqli \
    php82-mysqlnd \
    php82-phar \
    php82-mbstring \
    php82-iconv \
    dumb-init \
    mariadb-client

RUN mkdir -p /var/www/wordpress
WORKDIR /var/www/wordpress

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp && \
    wp core download --locale=ko_KR

COPY ./tools/run-wordpress.sh /usr/local/bin/run-wordpress.sh
RUN chmod +x /usr/local/bin/run-wordpress.sh

RUN sed -i "s/listen = 127.0.0.1:9000/listen = wordpress:9000/" /etc/php82/php-fpm.d/www.conf

ENTRYPOINT ["/usr/bin/dumb-init", "--", "/usr/local/bin/run-wordpress.sh"]
CMD ["php-fpm82", "--nodaemonize"]
