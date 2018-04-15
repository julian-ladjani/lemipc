CC = gcc -g

RM = rm -f

CFLAGS += -I./include -Wall -Wextra
LDFLAGS = -lpthread -lncurses -lm

NAME = lemipc

SRCS 	= 	src/main.c	\
			src/ai.c	\
			src/initializer.c	\
			src/controller.c	\
			src/display.c		\
			src/display_score.c		\
			src/team.c	\
			src/player.c	\
			src/ai_dead.c	\
			src/ai_algo.c	\
			src/ai_distance.c	\

OBJDIR = obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

NB_SRCS := $(words $(SRCS))
COMPILATION_INDEX := 1

$(OBJDIR)/%.o : %.c
	@if [ "$(CC)" != "gcc" ] && [ "$(COMPILATION_INDEX)" = "1" ]; then printf "%b" "\033[1;31mWarning Debug Flag\033[0m\n";fi
	@printf "%b" "\033[1;32m[$(COMPILATION_INDEX)/$(NB_SRCS)]\033[0m "
	@printf "%b" "\033[0;32mBuilding C object $@\033[0m\n"
	@$(eval COMPILATION_INDEX=$(shell echo $$(($(COMPILATION_INDEX)+1))))
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "%b" "\033[1;32mLinking C executable $(NAME)\033[0m\n"
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(LDFLAGS)
clean:
	@printf "%b" "\033[0;32mRemove C objects\033[0m\n"
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)

fclean: clean
	@printf "%b" "\033[0;32mRemove C executable\033[0m\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

