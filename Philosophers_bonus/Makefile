
### COMPILATION ###
CC      = gcc
FLAGS  = -Wall -Wextra -Werror -pthread

### EXECUTABLE ###
NAME_BONUS = philo_bonus

### INCLUDES ###
OBJ_PATH_BONUS  = objs
HEADER_BONUS = includes
SRC_PATH_BONUS  = src

### SOURCE FILES ###
SOURCES_BONUS =    	main.c \
					philo_bonus.c \
					init_bonus.c \
					utils_bonus.c \

### OBJECTS ###

SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS)/,$(SOURCES_BONUS))
OBJS_BONUS = $(addprefix $(OBJ_PATH_BONUS)/,$(SOURCES_BONUS:.c=.o))


### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: $(NAME_BONUS)

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(OBJ_PATH_BONUS)/*.o

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_PATH_BONUS)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

bonus: $(NAME_BONUS)
	
$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH_BONUS)/%.o: $(SRC_PATH_BONUS)/%.c $(HEADER_BONUS)/philosophers_bonus.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

norminette:
	@norminette

re: fclean
	@$(MAKE) all

.PHONY: re fclean clean norminette bonus