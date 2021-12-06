CC=gcc
CFLAGS=-Wall -Werror -Wextra
SRCS:=add_node.c \
	copy_node.c \
	create_node.c \
	delete_node.c \
	destruct_avl.c \
	replace_node.c \
	rotate_avl.c \
	search_node.c
OBJS_DIR=obj
OBJS=$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS_DIR=dep
DEPS=$(addprefix $(DEPS_DIR)/, $(SRCS:.c=.d))
NAME=libavl.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.c
	@if ! [ -d $(OBJS_DIR) ]; then \
		mkdir -p $(OBJS_DIR);\
	fi;
	@if ! [ -d $(DEPS_DIR) ]; then \
		mkdir -p $(DEPS_DIR);\
	fi;
	$(CC) $(CFLAGS) -c -MMD -MP -o $@ $<
	@mv $(OBJS_DIR)/*.d $(DEPS_DIR)/

clean :
	rm -fR $(OBJS_DIR) $(DEPS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re