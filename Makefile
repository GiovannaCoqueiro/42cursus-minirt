######################### NAMES ###############################
NAME			=		miniRT

######################### PATHS ###############################
HEADER_PATH		=		includes/
LIBFT_PATH		=		libft/
OBJECTS_PATH	=		objects/
SOURCES_PATH	=		sources/
VPATH			=		$(SOURCES_PATH) \
						# $(addprefix $(SOURCES_PATH),	matrices)

######################### MLX #################################
MLX_H			=		$(addprefix $(HEADER_PATH), mlx/)
MLX				=		$(addprefix $(MLX_H), libmlx42.a)

######################### LIBFT ###############################
LIBFT_H			=		$(addprefix $(LIBFT_PATH), $(HEADER_PATH))
LIBFT			=		$(addprefix $(LIBFT_PATH), libft.a)

######################### SOURCES #############################
MATRICES		=		comparison_matrices.c \
						create_matrix.c \
						determinant.c \
						operations_matrices.c \
						rotation_matrices_objects.c \
						transformations_matrices_objects.c \
						transformations_matrices.c
PARSER			=		parser.c \
						set_data.c \
						validate_data.c \
						validate_elements.c \
						validate_numbers.c \
						validate_objects.c
RAY_CASTING		=		discriminant.c \
						intersection_ray_object.c \
						intersections.c \
						list_utils.c \
						normal_reflecting.c \
						ray_utils.c
RENDER			=		lightning.c \
						render.c
TUPLES			=		color_operations.c \
						comparison.c \
						create.c \
						operations.c \
						vector_operations.c
UTILS			=		error.c \
						free.c
SOURCES			=		main.c \

######################### OBJECTS #############################
OBJECTS			=		$(patsubst %.c, $(OBJECTS_PATH)%.o, $(SOURCES))

######################### COMMANDS ############################
CC				=		cc
RM				=		rm -rf

######################### FLAGS ###############################
C_FLAGS			=		-Wall -Werror -Wextra -O3 -I$(HEADER_PATH) -I$(HEADER_B_PATH) -I$(LIBFT_H)
FLAGS			=		-lm -ldl -lglfw -pthread
LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft
FLAGS_EXTRA		=		-g3 -O3 -MP
FLAGS_MLX		=		-I$(MLX_H)

######################### RECIPES #############################
all:					$(LIBFT) $(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH) --no-print-directory

$(OBJECTS_PATH)%.o:		%.c $(HEADER_PATH)minirt.h
						@mkdir -p $(dir $@)
						@$(CC) $(FLAGS_EXTRA) $(C_FLAGS) -c $< -o $@ $(FLAGS_MLX)

$(NAME):				$(OBJECTS)
						@$(CC) -g3 $(C_FLAGS) $(OBJECTS) $(MLX) $(FLAGS_MLX) $(FLAGS) $(LIBFT_FLAGS) -o $@

# v:						all
# 						@valgrind --leak-check=full --show-leak-kinds=all \
# 							--suppressions=./supression.sup ./miniRT $(SCENE)

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean --no-print-directory

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean --no-print-directory

re:						fclean all

.PHONY:					all bonus clean fclean re