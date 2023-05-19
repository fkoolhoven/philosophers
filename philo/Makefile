NAME 			= 	philo
CC 				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror #-fsanitize=address -g3
RM				= 	rm -f
OBJ_DIR 		= 	objects
OBJ_FILES		= 	$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
SRC_DIR 		= 	sources
SRC_FILES 		= 	main.c \
					input_validation.c \
					initialize_data.c \
					initialize_threads.c \
					time_utils.c \
					dining_threads.c \
					philo_states.c \
					log_messages.c \
					monitor_dining.c \
					general_utils.c \
					clean_up.c \
					error_messages.c

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re