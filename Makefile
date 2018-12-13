PUSH_SWAP_NAME		=	push_swap

CHECKER_NAME		=	checker

MINILIBX			=	libmlx.a

CC					=	clang

FLAGS				=	-O3 -Wall -Werror -Wextra -Wshadow
MLX_FLAGS			=	-framework OpenGL -framework AppKit -Ofast -O3

PUSH_SWAP_SRC		=	main.c	get_stack_a.c	sort_for_few_unsorted.c \
						print_out.c		push_half_of_unsorted_in_b.c \
						find_and_push_numbers.c		try_to_sort.c	push_in.c \
						push_swap_rotate.c	main_sorting_function.c

PUSH_SWAP_INC		=	push_swap.h

CHECKER_SRC			=	main.c	read_numbers.c	get_instructions.c \
						push_swap.c		push.c	key_hooks.c \
						visualization.c		draw.c

CHECKER_INC			=	checker.h

PUSH_SWAP_OBJ		=	$(addprefix $(PUSH_SWAP_OBJ_DIR), $(PUSH_SWAP_SRC:.c=.o))
CHECKER_OBJ			=	$(addprefix $(CHECKER_OBJ_DIR), $(CHECKER_SRC:.c=.o))

PUSH_SWAP_HEADER	=	$(addprefix $(PUSH_SWAP_SRC_DIR), $(PUSH_SWAP_INC))
CHECKER_HEADER		=	$(addprefix $(CHECKER_SRC_DIR), $(CHECKER_INC))

MINILIBX_LIB		=	$(addprefix $(MINILIBX_DIR), $(MINILIBX))

PUSH_SWAP_SRC_DIR	=	push_swap_src/
PUSH_SWAP_OBJ_DIR	=	push_swap_obj/

CHECKER_SRC_DIR		=	checker_src/
CHECKER_OBJ_DIR		=	checker_obj/

MINILIBX_DIR		=	minilibx_macos/

all: $(MINILIBX) $(PUSH_SWAP_NAME) $(CHECKER_NAME)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

push_swap_obj:
	mkdir -p $(PUSH_SWAP_OBJ_DIR)

$(PUSH_SWAP_OBJ_DIR)%.o: $(PUSH_SWAP_SRC_DIR)%.c $(PUSH_SWAP_HEADER) | push_swap_obj
	$(CC) $(FLAGS) -c $< -o $@

$(PUSH_SWAP_NAME): $(PUSH_SWAP_OBJ)
	$(CC) $(FLAGS) $(PUSH_SWAP_OBJ) -o $(PUSH_SWAP_NAME)


checker_obj:
	mkdir -p $(CHECKER_OBJ_DIR)

$(CHECKER_OBJ_DIR)%.o: $(CHECKER_SRC_DIR)%.c $(CHECKER_HEADER) | checker_obj
	$(CC) $(FLAGS) -c $< -o $@

$(CHECKER_NAME): $(CHECKER_OBJ)
	$(CC) $(FLAGS) $(MLX_FLAGS) $(MINILIBX_LIB) $(CHECKER_OBJ) -o $(CHECKER_NAME)


clean:
	rm -rf $(PUSH_SWAP_OBJ_DIR) $(CHECKER_OBJ_DIR)

fclean: clean 
	rm -f $(PUSH_SWAP_NAME) $(CHECKER_NAME)
	make clean -C $(MINILIBX_DIR)

re: fclean all
