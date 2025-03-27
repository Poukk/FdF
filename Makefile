#------------------ Config -----------------#
NAME    := FdF
SRCS    := \
src/main.c \

#---------------- Variables ----------------#
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast

LIB_DIR := ./lib
LIBMLX  := $(LIB_DIR)/MLX42
LIBFT   := $(LIB_DIR)/Libft

HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

OBJS    := ${SRCS:.c=.o}

#----------------- Targets ----------------#
all: submodules libmlx libft $(NAME)

submodules:
	@git submodule update --init --recursive --jobs 4

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT)

libmlx:
	@if [ ! -f "$(LIBMLX)/build/libmlx42.a" ]; then \
		cmake $(LIBMLX) -Wno-dev -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "MLX42 is already built"; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) --no-print-directory -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft, submodules
