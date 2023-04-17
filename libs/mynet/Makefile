##
## EPITECH PROJECT, 2023
## mynet
## File description:
## Makefile for the mynet library
##

DEFAULT	=	"\033[00m"
RED		=	"\033[1;31m"
GREEN	=	"\033[1;32m"
BLUE	=	"\033[1;34m"
MAGENTA	=	"\033[1;35m"
TEAL	=	"\033[1;36m"

SERVER_NAME	=   libmynetserver.a

SERVER_FOLDER	=	./server

SERVER_SRC	=	$(SERVER_FOLDER)/server_client.c	\
				$(SERVER_FOLDER)/server_destroy.c	\
				$(SERVER_FOLDER)/server_init.c	\
				$(SERVER_FOLDER)/server_read.c	\
				$(SERVER_FOLDER)/server_write.c	\
				$(SERVER_FOLDER)/server_step.c	\
				$(SERVER_FOLDER)/server_line_list.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Wshadow -Wpedantic -Werror
CFLAGS	+=	-I./include
GCC	=	gcc

%.o: %.c
	@printf $(TEAL)"[+] Compiling $@ "$(DEFAULT)"\n"
	@$(GCC) $(CFLAGS) -c $< -o $@ && \
	printf $(GREEN)"[+] Compiled $@ "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $@ "$(DEFAULT)"\n"

all:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):	$(SERVER_OBJ)
	@printf $(TEAL)"[+] Creating $(SERVER_NAME) "$(DEFAULT)"\n"
	@ar rc $(SERVER_NAME) $(SERVER_OBJ) && \
	printf $(GREEN)"[+] Created $(SERVER_NAME) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed creating $(SERVER_NAME) "$(DEFAULT)"\n"

clean:
	@printf $(TEAL)"[+] Cleaning mynet"$(DEFAULT)"\n"
	@rm -f $(SERVER_OBJ) && \
	printf $(GREEN)"[+] Cleaned mynet"$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed cleaning mynet"$(DEFAULT)"\n"

fclean:	clean
	@printf $(TEAL)"[+] Deleting mynet library binaries "$(DEFAULT)"\n"
	@rm -f $(SERVER_NAME) $(CLIENT_NAME) && \
	printf $(GREEN)"[+] Deleted mynet library binaries "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed deleting mynet library binaries "$(DEFAULT)"\n"

re:	fclean all

debug:	CFLAGS += -g
debug:	re
	@printf $(MAGENTA)"[+] Compiled with debug mode"$(DEFAULT)"\n"

.PHONY: all clean fclean re debug
