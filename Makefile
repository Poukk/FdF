#------------------ Config -----------------#
NAME    := fdf
SRCS    := \
src/main.c              \
src/debug.c		\
src/parser/map_parser.c \
src/parser/map_size.c   \
src/error/cleanup.c     \
src/draw/color.c        \
src/draw/helpers.c      \
src/draw/line.c         \

#---------------- Variables ----------------#
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast

LIB_DIR := ./lib
LIBMLX  := $(LIB_DIR)/MLX42
LIBFT   := $(LIB_DIR)/Libft

HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

OBJ_DIR := obj
OBJS    := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

#----------------- Targets ----------------#
all: check_submodules libmlx libft $(NAME)

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT)

libmlx:
	@if [ ! -f "$(LIBMLX)/build/libmlx42.a" ]; then \
		cmake $(LIBMLX) -Wno-dev -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "MLX42 is already built"; \
	fi

check_submodules:
	@if git submodule status | grep -q '^-'; then \
		echo "Initializing missing submodules..."; \
		git submodule update --init --recursive; \
	fi

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) --no-print-directory -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT) fclean

re: clean all

.PHONY: all clean fclean re libmlx libft
