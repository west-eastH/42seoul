#!/bin/sh

while ! mysqladmin ping -u $MYSQL_USER -p$MYSQL_PASSWORD -h "$WP_DB_HOST" --silent; do
    sleep 1
done

while [ ! -f /var/www/wordpress/wp-config.php ]; do
    wp config create --dbhost="$WP_DB_HOST" --dbname="$WP_DB_NAME" --dbuser="$MYSQL_USER" --dbpass="$MYSQL_PASSWORD" --path=/var/www/wordpress --locale=ko_KR
    sleep 1
done

while ! wp db check --path=/var/www/wordpress; do
    sleep 1
done

while ! wp core is-installed --path=/var/www/wordpress; do
    wp core install --url="$WP_URL" --title="dongseo Website" --admin_user="$WP_ADMIN" --admin_password="$WP_ADMIN_PASSWORD" --admin_email="$WP_ADMIN_EMAIL" --path=/var/www/wordpress
    sleep 1
done

while ! wp user get dongseo; do
    wp user create "$WP_USER" "$WP_USER_EMAIL" --user_pass="$WP_USER_PASSWORD" --role=author --path=/var/www/wordpress
    sleep 1
done

exec php-fpm82 --nodaemonize
