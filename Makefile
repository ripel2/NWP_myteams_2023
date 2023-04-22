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
COMMANDS		=   $(SERVER_FOLDER)/commands
COMMANDS_TOOLS	=   $(SERVER_FOLDER)/commands/commands_tools
ADD_FUNCTION	=   $(SERVER_FOLDER)/handle_database/add_functions
GET_FUNCTION	=   $(SERVER_FOLDER)/handle_database/get_functions
OTHER_FUNCTION 	=   $(SERVER_FOLDER)/handle_database/other_functions
SAVE_FUNCTION   =   $(SERVER_FOLDER)/save
READ_FUNCTION   =   $(SERVER_FOLDER)/read

SERVER_NAME	=   myteams_server
CLIENT_NAME	=   myteams_cli

SERVER_MAIN	=	$(SERVER_FOLDER)/main.c
CLIENT_MAIN	=	$(CLIENT_FOLDER)/main.c

SERVER_MAIN_OBJ	=	$(SERVER_MAIN:.c=.o)
CLIENT_MAIN_OBJ	=	$(CLIENT_MAIN:.c=.o)

SHARED_SRC	=	$(SHARED_FOLDER)/print_help.c	\
				$(SHARED_FOLDER)/port_handler.c \
				$(SHARED_FOLDER)/ip_handler.c	\
				$(SHARED_FOLDER)/fixed_array_split.c	\
				$(SHARED_FOLDER)/str_to_time.c

SERVER_SRC	=	$(ADD_FUNCTION)/add_user_to_struct.c				\
				$(GET_FUNCTION)/get_user_from_struct.c				\
				$(OTHER_FUNCTION)/generate_uuid.c					\
				$(OTHER_FUNCTION)/init_data.c						\
				$(ADD_FUNCTION)/add_team_to_struct.c				\
				$(GET_FUNCTION)/get_team_from_struct.c				\
				${ADD_FUNCTION}/add_channel_to_struct.c				\
				${GET_FUNCTION}/get_channel_from_struct.c			\
				$(ADD_FUNCTION)/add_thread_to_struct.c				\
				$(GET_FUNCTION)/get_thread_from_struct.c			\
				$(ADD_FUNCTION)/add_reply_to_struct.c				\
				$(GET_FUNCTION)/get_reply_from_struct.c				\
				$(ADD_FUNCTION)/add_discussion_to_struct.c			\
				$(GET_FUNCTION)/get_discussion_from_struct.c		\
				$(ADD_FUNCTION)/add_message_to_struct.c				\
				$(ADD_FUNCTION)/add_user_to_team.c					\
				$(OTHER_FUNCTION)/remove_user_from_team.c			\
				$(OTHER_FUNCTION)/is_channel_in_team.c				\
				$(OTHER_FUNCTION)/is_thread_in_channel.c			\
				$(SERVER_FOLDER)/server_loop.c						\
				$(SERVER_FOLDER)/handle_client_commands.c			\
				$(COMMANDS)/create_command.c						\
				$(COMMANDS)/help_command.c							\
				$(COMMANDS)/info_command.c							\
				$(COMMANDS)/list_command.c							\
				$(COMMANDS)/login_command.c							\
				$(COMMANDS)/logout_command.c						\
				$(COMMANDS)/messages_command.c						\
				$(COMMANDS)/send_command.c							\
				$(COMMANDS)/subscribe_command.c						\
				$(COMMANDS)/subscribed_command.c					\
				$(COMMANDS)/unsubscribe_command.c					\
				$(COMMANDS)/use_command.c							\
				$(COMMANDS)/user_command.c							\
				$(COMMANDS)/users_command.c							\
				$(COMMANDS_TOOLS)/is_user_logged_in.c				\
				$(COMMANDS_TOOLS)/remove_bad_char.c					\
				$(COMMANDS_TOOLS)/get_user_logged_in.c				\
				$(COMMANDS_TOOLS)/get_user_from_struct_by_fd.c 		\
				$(COMMANDS_TOOLS)/send_event_to_user.c				\
				$(COMMANDS_TOOLS)/is_a_uuid.c						\
				$(COMMANDS_TOOLS)/count_nb_messages.c				\
				$(SAVE_FUNCTION)/write_in_to_file.c					\
				$(SERVER_FOLDER)/open_file.c						\
				$(SAVE_FUNCTION)/write_users.c						\
				$(SAVE_FUNCTION)/write_teams_uuids.c				\
				$(SAVE_FUNCTION)/write_personal_discussion.c		\
				$(SAVE_FUNCTION)/write_teams.c						\
				$(SAVE_FUNCTION)/write_channels.c					\
				$(SAVE_FUNCTION)/write_threads.c					\
				$(SAVE_FUNCTION)/write_replies.c					\
				$(READ_FUNCTION)/read_users.c						\
				$(READ_FUNCTION)/read_channels.c					\
				$(READ_FUNCTION)/read_threads.c						\
				$(READ_FUNCTION)/read_replies.c						\
				$(READ_FUNCTION)/read_teams.c						\
				$(READ_FUNCTION)/read_personal_discussion.c			\
				$(READ_FUNCTION)/load_struct_from_file.c			\
				$(READ_FUNCTION)/read_messages.c

CLIENT_SRC	=	$(CLIENT_FOLDER)/client_init.c	\
				$(CLIENT_FOLDER)/client_loop.c	\
				$(CLIENT_FOLDER)/client_read.c	\
				$(CLIENT_FOLDER)/client_printf.c	\
				$(CLIENT_FOLDER)/client_events.c	\
				$(CLIENT_FOLDER)/commands/handler.c	\
				$(CLIENT_FOLDER)/commands/help_command.c	\
				$(CLIENT_FOLDER)/commands/login_command.c	\
				$(CLIENT_FOLDER)/commands/logout_command.c	\
				$(CLIENT_FOLDER)/commands/users_command.c	\
				$(CLIENT_FOLDER)/commands/user_command.c	\
				$(CLIENT_FOLDER)/commands/use_command.c	\
				$(CLIENT_FOLDER)/commands/send_command.c	\
				$(CLIENT_FOLDER)/commands/create_command.c	\
				$(CLIENT_FOLDER)/commands/subscribe_command.c	\
				$(CLIENT_FOLDER)/commands/unsubscribe_command.c	\
				$(CLIENT_FOLDER)/commands/messages_command.c	\
				$(CLIENT_FOLDER)/commands/info_command.c

SHARED_OBJ	=	$(SHARED_SRC:.c=.o)
SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)

TESTS_SRC	=	tests/add_functions/add_team_to_struct/basic_tests.c		\
				tests/add_functions/add_channel_to_struct/basic_tests.c 	\
				tests/add_functions/add_user_to_struct/basic_tests.c		\
				tests/add_functions/add_thread_to_struct/basic_tests.c		\
				tests/add_functions/add_reply_to_struct/basic_tests.c		\
				tests/add_functions/add_discussion_to_struct/basic_tests.c	\
				tests/add_functions/add_message_to_struct/basic_tests.c		\
				tests/add_functions/add_user_to_team/basic_tests.c			\
				tests/get_functions/get_channel_from_struct/basic_tests.c	\
				tests/get_functions/get_team_from_struct/basic_tests.c		\
				tests/get_functions/get_user_from_struct/basic_tests.c		\
				tests/get_functions/get_thread_from_struct/basic_tests.c	\
				tests/get_functions/get_reply_from_struct/basic_tests.c		\
				tests/get_functions/get_discussion_from_struct/basic_tests.c\
				tests/other_functions/remove_user_from_team/basic_tests.c	\
				tests/other_functions/is_channel_in_team/basic_tests.c		\
				tests/other_functions/is_thread_in_channel/basic_tests.c	\
				tests/client_functions/tests_buffer_managment.c	\
				tests/client_functions/tests_client_printf.c	\
				tests/client_functions/tests_client_events.c	\
				tests/save/open_file.c										\
				tests/save/write.c											\
				tests/save/read.c											\
				tests/other_functions/split_array.c

TESTS_OBJ	=	$(TESTS_SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Wshadow -Wpedantic -Werror
CFLAGS	+=	-I./include -I./libs/mynet/include -I./libs/myteams
CFLAGS	+=	-luuid -L./libs/mynet -lmynetserver
CFLAGS	+=	-L./libs/myteams -lmyteams
CFLAGS	+=	-I./libs/myteams
GCC	=	gcc

SERVER_LIB	=	./libs/mynet/libmynetserver.a

%.o: %.c
	@printf $(TEAL)"[+] Compiling $@ "$(DEFAULT)"\n"
	@$(GCC) $(CFLAGS) -c $< -o $@ && \
	printf $(GREEN)"[+] Compiled $@ "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $@ "$(DEFAULT)"\n"

all:	$(SERVER_NAME) $(CLIENT_NAME) $(SERVER_LIB)

$(SERVER_LIB):
	@printf $(TEAL)"[+] Compiling $(SERVER_LIB) "$(DEFAULT)"\n"
	@make -C ./libs/mynet/ && \
	printf $(GREEN)"[+] Compiled $(SERVER_LIB) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling $(SERVER_LIB) "$(DEFAULT)"\n"

$(SERVER_NAME):	$(SERVER_LIB) $(SERVER_MAIN_OBJ) $(SERVER_OBJ) $(SHARED_OBJ)
	@printf $(TEAL)"[+] Creating $(SERVER_NAME) "$(DEFAULT)"\n"
	@gcc -o $(SERVER_NAME) $(SERVER_MAIN_OBJ) $(SERVER_OBJ) \
	$(SHARED_OBJ) ${CFLAGS} && \
	printf $(GREEN)"[+] Created $(SERVER_NAME) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed creating $(SERVER_NAME) "$(DEFAULT)"\n"

$(CLIENT_NAME):	$(CLIENT_MAIN_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ)
	@printf $(TEAL)"[+] Creating $(CLIENT_NAME) "$(DEFAULT)"\n"
	@gcc -o $(CLIENT_NAME) $(CLIENT_MAIN_OBJ) $(CLIENT_OBJ) \
	$(SHARED_OBJ) ${CFLAGS} && \
	printf $(GREEN)"[+] Created $(CLIENT_NAME) "$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed creating $(CLIENT_NAME) "$(DEFAULT)"\n"

clean:
	@printf $(TEAL)"[+] Cleaning myteams"$(DEFAULT)"\n"
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SHARED_OBJ) \
	$(SERVER_MAIN_OBJ) $(CLIENT_MAIN_OBJ) && \
	find . -name "*.gcno" -delete && \
	find . -name "*.gcda" -delete && \
	find . -name "*.o" -delete && \
	rm -f "unit_tests" && \
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
	$(TESTS_OBJ) -L./libs/mynet -lmynetserver && \
	printf $(GREEN)"[+] Compiled tests"$(DEFAULT)"\n" || \
	printf $(RED)"[-] Failed compiling tests"$(DEFAULT)"\n"
	@printf $(TEAL)"[+] Running tests"$(DEFAULT)"\n"
	@./unit_tests && \
	printf $(GREEN)"[+] Tests passed"$(DEFAULT)"\n" || \
	(printf $(RED)"[-] Tests failed"$(DEFAULT)"\n" && exit 1)

debug:	CFLAGS += -g
debug:	re
	@printf $(MAGENTA)"[+] Compiled with debug mode"$(DEFAULT)"\n"

.PHONY: all clean fclean re debug
