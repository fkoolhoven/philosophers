NAME 			= 	philo
CC 				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror
RM				= 	rm -f
OBJ_DIR 		= 	objects
OBJ_FILES		= 	$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
SRC_DIR 		= 	sources
SRC_FILES 		= 	main.c \
					input_validation.c \
					initialize_data.c \
					time.c \
					manage_threads.c \
					dining.c \
					philo_states.c \
					utils.c

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