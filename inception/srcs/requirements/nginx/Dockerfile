FROM alpine:3.19

RUN apk update && apk add nginx openssl dumb-init

RUN mkdir -p /etc/nginx/ssl && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=inception/CN=dongseo.42.fr"

COPY ./conf/default.conf /etc/nginx/http.d/default.conf

ENTRYPOINT ["/usr/bin/dumb-init", "--"]
CMD ["nginx", "-g", "daemon off;"]
