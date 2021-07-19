NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

NAME = philo
NAME_BONUS = philo_bonus

OBJDIR = ./obj/
OBJDIR_BONUS = ./obj/bonus/
HEADERDIR = ./includes/

SRCDIR = ./srcs/philo/
SRCS = main.c forks.c threads.c
OBJ = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
HEADER = $(addprefix $(HEADERDIR), philo.h)

SRC_BONUS_DIR = ./srcs/philo_bonus/
SRCS_BONUS = main.c check_args.c messages.c tools.c processes.c
OBJ_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_BONUS:.c=.o))
HEADER_BONUS = $(addprefix $(HEADERDIR), bonus.h)

SRC_UTILS_DIR = ./srcs/utils/
SRCS_UTILS = ft_isdigit.c ft_putstr_fd.c ft_atoi.c get_time.c  ft_usleep.c\
	 error_handler.c ft_putendl_fd.c tools.c
OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(OBJ_UTILS) $(HEADER) $(HEADER_UTILS)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_UTILS) -o $@
	@echo "$(PURPLE) $(NAME) has been created $(NONE)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJDIR_BONUS) $(OBJ_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $@
	@echo "$(PURPLE) $(NAME_BONUS) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_BONUS):
	mkdir -p $(OBJDIR_BONUS)

############################
##   philo compilation    ##
############################

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) $(HEADER_UTILS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for philo has been created $(NONE)"

############################
##   utils compilation    ##
############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for utils has been created $(NONE)"

#################################
##   philo bonus compilation   ##
#################################

$(OBJ_BONUS): $(OBJDIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(HEADER_BONUS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for philo_bonus has been created $(NONE)"

clean:
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED) $(NAME) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re bonus
