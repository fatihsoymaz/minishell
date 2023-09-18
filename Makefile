#                                 _             _    _   
#              _         _       ( )           (_ ) (_ ) 
#    ___ ___  (_)  ___  (_)  ___ | |__     __   | |  | | 
#  /' _ ` _ `\| |/' _ `\| |/',__)|  _ `\ /'__`\ | |  | | 
#  | ( ) ( ) || || ( ) || |\__, \| | | |(  ___/ | |  | | 
#  (_) (_) (_)(_)(_) (_)(_)(____/(_) (_)`\____)(___)(___)

RED			=	\033[0;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[0;34m
CYAN		=	\033[1;36m
RESET		=	\033[0m

SUBDIR 				=	executor parser tokenize lst env builtin redirect tools include
SRCS				=	$(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))
NAME				=	minishell
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra -g #-fsanitize=address
RM					=	rm -f
READLINE			=	-lreadline
OBJS_DIR			=	objs/
PROJECT_H			=	./include/minishell.h
OBJS 				=	$(SRCS:c=o)
OBJECTS_PREFIXED	= 	$(addprefix $(OBJS_DIR), $(OBJS))
LIBFT				= ./libft




LINKERS		= -lft -L $(LIBFT) $(READLINE) -L ./lib/lib/readline/lib

INCLUDES	= -I. -I ./lib/lib/readline/include


$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)executor $(OBJS_DIR)parser $(OBJS_DIR)tokenize $(OBJS_DIR)lst $(OBJS_DIR)env $(OBJS_DIR)builtin $(OBJS_DIR)redirect $(OBJS_DIR)tools $(OBJS_DIR)include
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 
	@printf	"\033[2K\r📶${RED}[DERLENİYOR! / COMPILING!]${RESET}"

$(NAME): $(OBJECTS_PREFIXED) makerun
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJECTS_PREFIXED) $(INCLUDES) $(LINKERS)
	@echo "\n✅ ${GREEN}Executable ${NAME} created and ready for use!${BLUE} -- >${RED} $(NAME) ${BLUE}< --${RESET}"

all:	${NAME}

makerun:
	@make -C ./libft
	@make -C ./lib

clean:
	@make clean -C ./libft
	@rm -rf $(OBJS_DIR)
	@echo "🧽 $(GREEN)Minishell Clean: ${RED}Removed all the \".o\" files${RESET}"

fclean:	clean
	@make fclean -C ./libft 
	@rm -f $(NAME) 
	@echo "🧽 $(GREEN)Minishell Fclean: ${RED}Removed the executables${RESET}"

re:	fclean all

.PHONY:		all clean fclean re