CC=gcc
CFLAGS=-Wall -Wextra -Werror #-g -fsanitize=thread

NAME:=philo_bonus
SRC_DIR:=src
SRC_FILES:=main.c \
	philo_life_bonus.c \
	philo_init_bonus.c \
	start_philo_behavior.c \
	ft_sem_sys_bonus.c \
	ft_ato_num.c \
	ft_free_dbl_ptr.c \
	ft_itoa.c \
	ft_isdigit.c \
	ft_msleep_until_time.c \
	ft_print_error.c \
	ft_strlen.c \
	get_mtime.c

UTILS_DIR:=utils

NAME:=$(NAME)

OBJS_DIR:=obj
OBJS:=$(addprefix $(OBJS_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

DEPS_DIR:=dep
DEPS:=$(addprefix $(DEPS_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

vpath %.c $(SRC_DIR):$(SRC_DIR)/$(UTILS_DIR)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) $(DEPS_DIR)

#$(OBJS): $(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/$(UTILS_DIR)/%.c
$(OBJS_DIR)/%.o: %.c
	gcc $(CFLAGS) -I./include -MMD -MP -c -o $@ $<
	@mv $(OBJS_DIR)/*.d $(DEPS_DIR)/

-include $(DEPS)

clean:
	rm -fR $(OBJS_DIR) $(DEPS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
