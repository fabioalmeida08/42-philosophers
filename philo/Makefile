NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -MP -I ./includes
DIR_DUP = mkdir -p $(@D)

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

SRCS_DIR = src
OBJS_DIR = objs

SRCS := main.c \
				utils.c \
				validation.c \
				clean_utils.c \
				setup.c \
				simulation.c \
				routines.c \
				monitor.c \

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)🛠️ Finished compiling $(NAME) objects$(RESET)"
	@echo "$(GREEN)🚀 $@ was created$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)🧹 $(NAME) objects removed$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)💥 $(NAME) deleted$(RESET)"

re: fclean all
	@echo "$(BLUE)🔄 $(NAME) rebuild$(RESET)"

debug: CFLAGS += -g -O0
debug: re
	@echo "$(BLUE)🐞 Starting GDB...$(RESET)"
	@gdbtui ./$(NAME) 
.PHONY: all clean fclan re
