#!/bin/sh

mkdir -p /run/mysqld /var/lib/mysql
chown -R mysql:mysql /run/mysqld /var/lib/mysql
chmod -R 755 /run/mysqld /var/lib/mysql

rm -f /run/mysqld/mysqld.sock

if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --skip-test-db
fi

mysqld --skip-grant-tables &

while ! mysqladmin ping --silent; do
    sleep 1
done

mysql -u root<<EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%' WITH GRANT OPTION;
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
FLUSH PRIVILEGES;
EOF

killall mysqld

exec mysqld
