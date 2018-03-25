CC = gcc -g

RM = rm -f

CFLAGS += -I./include -Wall -Wextra
LDFLAGS = -lpthread -lncurses

NAME = lemipc

SRCS 	= 	src/main.c	\
			src/ai.c	\
			src/cleanup.c	\
			src/initializer.c	\
			src/controller.c	\
			src/display.c		\

OBJDIR = obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

NB_SRCS := $(words $(SRCS))
COMPILATION_INDEX := 1

$(OBJDIR)/%.o : %.c
	@if [ "$(CC)" != "gcc" ] && [ "$(COMPILATION_INDEX)" = "1" ]; then printf "%b" "\e[1;31mWarning Debug Flag\e[0m\n";fi
	@printf "%b" "\e[1;32m[$(COMPILATION_INDEX)/$(NB_SRCS)]\e[0m "
	@printf "%b" "\e[0;32mBuilding C object $@\e[0m\n"
	@$(eval COMPILATION_INDEX=$(shell echo $$(($(COMPILATION_INDEX)+1))))
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "%b" "\e[1;32mLinking C executable $(NAME)\e[0m\n"
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(LDFLAGS)
clean:
	@printf "%b" "\e[0;32mRemove C objects\e[0m\n"
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)

fclean: clean
	@printf "%b" "\e[0;32mRemove C executable\e[0m\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

