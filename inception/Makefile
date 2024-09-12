all: up

up:
	sudo mkdir -p /home/dongseo/data/wordpress
	sudo mkdir -p /home/dongseo/data/mariadb
	sudo chown -R dongseo:dongseo /home/dongseo/data/wordpress
	sudo chown -R dongseo:dongseo /home/dongseo/data/mariadb
	@echo "127.0.0.1 dongseo.42.fr" | sudo tee -a /etc/hosts
	docker-compose -f srcs/docker-compose.yml up --build -d

clean:
	docker-compose -f srcs/docker-compose.yml down
	sudo sed -i '/127.0.0.1 dongseo.42.fr/d' /etc/hosts

fclean:
	docker-compose -f srcs/docker-compose.yml down
	sudo rm -rf /home/dongseo/data
	sudo sed -i '/127.0.0.1 dongseo.42.fr/d' /etc/hosts

re: clean up

.PHONY : all clean fclean re
