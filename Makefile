vpath %.c sources

NAME = miniRT

CC = cc
FLAGS = -lm $(LIBFT)/libft.a
CFLAGS = -Wall -Wextra -Werror -I$(LIBS) -O3 -g3
XFLAGS = -lmlx -lX11 -lXext

LIBFT = ./libft
LIBS = ./includes
OBJ_DIR = build/
COLOR_DIR = color/
FINISH_DIR = finish/
INIT_DIR = init_utils/
INTER_DIR = intersections/
MATRIX_DIR = matrix/
PARSER_DIR = parser/
RENDER_DIR = render/
TUPLES_DIR = tuples/

RM = rm -f
FILES = main.c \
		$(COLOR_DIR)color.c \
		$(FINISH_DIR)error.c \
		$(FINISH_DIR)free.c \
		$(FINISH_DIR)free2.c \
		$(INIT_DIR)init.c \
		$(INTER_DIR)camera.c \
		$(INTER_DIR)list.c \
		$(INTER_DIR)ray.c \
		$(INTER_DIR)scene.c \
		$(INTER_DIR)get_normal_vector.c \
		$(INTER_DIR)sphere.c \
		$(INTER_DIR)plane.c \
		$(INTER_DIR)cylinder.c \
		$(INTER_DIR)cylinder_cap.c \
		$(MATRIX_DIR)create_matrix.c \
		$(MATRIX_DIR)determinant.c \
		$(MATRIX_DIR)operations_matrix.c \
		$(MATRIX_DIR)transformation_rotation.c \
		$(MATRIX_DIR)transformations.c \
		$(MATRIX_DIR)verify_matrix.c \
		$(PARSER_DIR)parser.c \
		$(PARSER_DIR)seters.c \
		$(PARSER_DIR)verify_camera_and_lights.c \
		$(PARSER_DIR)verify_data.c \
		$(PARSER_DIR)verify_numbers.c \
		$(PARSER_DIR)verify_objects.c \
		$(RENDER_DIR)get_color.c \
		$(RENDER_DIR)render.c \
		$(TUPLES_DIR)are_equals.c \
		$(TUPLES_DIR)create_tuples.c \
		$(TUPLES_DIR)operations_tuples.c \
		$(TUPLES_DIR)operations_vector.c
		
OBJS = $(FILES:.c=.o)

all: mkdir_obj $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

mkdir_obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(COLOR_DIR)
	@mkdir -p $(OBJ_DIR)$(FINISH_DIR)
	@mkdir -p $(OBJ_DIR)$(INIT_DIR)
	@mkdir -p $(OBJ_DIR)$(INTER_DIR)
	@mkdir -p $(OBJ_DIR)$(MATRIX_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSER_DIR)
	@mkdir -p $(OBJ_DIR)$(RENDER_DIR)
	@mkdir -p $(OBJ_DIR)$(TUPLES_DIR)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	@make -C $(LIBFT) --silent
	@$(CC) $(addprefix $(OBJ_DIR), $(OBJS)) $(FLAGS) -o $(NAME) $(XFLAGS)
	@echo "\033[0;32mSUCCESS!\033[0m"

val: all
	valgrind --quiet --leak-check=full --show-leak-kinds=all ./$(NAME) scenes/composition.rt

clean:
	@make clean -C $(LIBFT) --silent
	@$(RM) $(addprefix $(OBJ_DIR), $(OBJS))
	@echo "\033[0;36mBUILD DIRECTORY CLEAN!\033[0m"

fclean: clean
	@make fclean -C $(LIBFT) --silent
	@$(RM) $(NAME)
	@echo "\033[0;31mBINARY DESTROYED!\033[0m"

re: fclean all

.PHONY: all clean fclean re