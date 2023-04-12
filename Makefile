##
## EPITECH PROJECT, 2023
## myteams
## File description:
## Makefile for the myteams project
##

DEFAULT	=	"\033[00m"
RED		=	"\033[1;31m"
GREEN	=	"\033[1;32m"
BLUE	=	"\033[1;34m"
MAGENTA	=	"\033[1;35m"
TEAL	=	"\033[1;36m"

SHARED_FOLDER	=	./src/shared
SERVER_FOLDER	=	./src/server
CLIENT_FOLDER	=	./src/client

SERVER_NAME	=   myteams_server
CLIENT_NAME	=   myteams_cli

SERVER_MAIN	=	$(SERVER_FOLDER)/main.c
CLIENT_MAIN	=	$(CLIENT_FOLDER)/main.c

SERVER_MAIN_OBJ	=	$(SERVER_MAIN:.c=.o)
CLIENT_MAIN_OBJ	=	$(CLIENT_MAIN:.c=.o)

SHARED_SRC	=	$(SHARED_FOLDER)/print_help.c	\
				$(SHARED_FOLDER)/port_handler.c \
        $(SHARED_FOLDER)/loader/load_functions.c

SERVER_SRC	=	$(SERVER_FOLDER)/handle_database/add_functions/add_user_to_struct.c 		\
				$(SERVER_FOLDER)/handle_database/get_functions/get_user_from_struct.c
CLIENT_SRC	=

SHARED_OBJ	=	$(SHARED_SRC:.c=.o)
SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)

TESTS_SRC	=	tests/load_functions_tests/basic_tests.c 			 \
				tests/add_functions/add_user_to_struct/basic_tests.c \
				tests/get_functions/get_user_from_struct/basic_tests.c
TESTS_OBJ	=	$(TESTS_SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Wshadow -Wpedantic -Werror
CFLAGS	+=	-I./include -I./libs/mynet/include
CFLAGS	+=	-ldl -g
GCC	=	gcc

SERVER_LIB	=	./libs/mynet/libmynetserver.a
CLIENT_LIB	=	./libs/mynet/libmynetclient.a

%.o: %.c
	@printf $(TEAL)"[+] Compiling $@ "$(DEFAULT)"\n"
	@$(GCC) $(CFLAGS) -c $< -o $@ && \
	printf $(GREEN)"[+] Compiled $@ "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $@ "$(DEFAULT)"\n"

all:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_LIB):
	@printf $(TEAL)"[+] Compiling $(SERVER_LIB) "$(DEFAULT)"\n"
	@make -C ./libs/mynet/ && \
	printf $(GREEN)"[+] Compiled $(SERVER_LIB) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $(SERVER_LIB) "$(DEFAULT)"\n"

$(CLIENT_LIB):
	@printf $(TEAL)"[+] Compiling $(CLIENT_LIB) "$(DEFAULT)"\n"
	@make -C ./libs/mynet/ && \
	printf $(GREEN)"[+] Compiled $(CLIENT_LIB) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $(CLIENT_LIB) "$(DEFAULT)"\n"

$(SERVER_NAME):	$(SERVER_LIB) $(SERVER_MAIN_OBJ) $(SERVER_OBJ) $(SHARED_OBJ)
	@printf $(TEAL)"[+] Creating $(SERVER_NAME) "$(DEFAULT)"\n"
	@gcc -o $(SERVER_NAME) $(SERVER_MAIN_OBJ) $(SERVER_OBJ) \
	$(SHARED_OBJ) ${CFLAGS} && \
	printf $(GREEN)"[+] Created $(SERVER_NAME) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed creating $(SERVER_NAME) "$(DEFAULT)"\n"

$(CLIENT_NAME):	$(CLIENT_LIB) $(CLIENT_MAIN_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ)
	@printf $(TEAL)"[+] Creating $(CLIENT_NAME) "$(DEFAULT)"\n"
	@gcc -o $(CLIENT_NAME) $(CLIENT_MAIN_OBJ) $(CLIENT_OBJ) \
	$(SHARED_OBJ) ${CFLAGS} && \
	printf $(GREEN)"[+] Created $(CLIENT_NAME) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed creating $(CLIENT_NAME) "$(DEFAULT)"\n"

clean:
	@printf $(TEAL)"[+] Cleaning myteams"$(DEFAULT)"\n"
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ) \
	$(SERVER_MAIN_OBJ) $(CLIENT_MAIN_OBJ) && \
	printf $(GREEN)"[+] Cleaned myteams"$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed cleaning myteams"$(DEFAULT)"\n"

fclean:	clean
	@printf $(TEAL)"[+] Deleting myteams binaries "$(DEFAULT)"\n"
	@rm -f $(SERVER_NAME) $(CLIENT_NAME) && \
	printf $(GREEN)"[+] Deleted myteams binaries "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed deleting myteams binaries "$(DEFAULT)"\n"

re:	fclean all

tests_run:	CFLAGS += --coverage -fprofile-arcs -ftest-coverage
tests_run:	CFLAGS += -lcriterion
tests_run:	$(SERVER_LIB) $(CLIENT_LIB)
tests_run:	$(SERVER_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ)
tests_run:	$(TESTS_OBJ)
	@printf $(TEAL)"[+] Compiling tests"$(DEFAULT)"\n"
	@$(GCC) $(CFLAGS) -o unit_tests $(SERVER_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ) \
	$(TESTS_OBJ) && \
	printf $(GREEN)"[+] Compiled tests"$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling tests"$(DEFAULT)"\n"
	@printf $(TEAL)"[+] Running tests"$(DEFAULT)"\n"
	@./unit_tests && \
	printf $(GREEN)"[+] Tests passed"$(DEFAULT)"\n" || \
	printf $(RED)"[-] Tests failed"$(DEFAULT)"\n"

debug:	CFLAGS += -g
debug:	re
	@printf $(MAGENTA)"[+] Compiled with debug mode"$(DEFAULT)"\n"

.PHONY: all clean fclean re debug
