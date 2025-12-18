GREEN = \033[0;92m

NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes


DFLAGS = -MMD -MP \
		-I include \


SRCDIR = src
OBJDIR = obj


SRCS = $(addprefix $(SRCDIR)/,\
		main.c \
		parsing.c \
		utils.c \
)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
		mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_A) $(C_VEC_A)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN) Compiled!$(DEF_COLOR)"

valgrind:
		$(VALGRIND) ./philo

clean:
		rm -rf $(OBJDIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind
.SECONDARY:$(OBJS)
-include $(DEPS)