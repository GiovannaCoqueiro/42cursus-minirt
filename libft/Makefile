NAME = libft.a
PATH_INCLUDE = ./includes
CCFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_toupper.c ft_tolower.c ft_atoi.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strnstr.c ft_strlcpy.c ft_strdup.c ft_calloc.c ft_strlcat.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_striteri.c \
	ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_atod.c ft_iswhitespace.c

OBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
	ft_strlen.o ft_toupper.o ft_tolower.o ft_atoi.o ft_memset.o ft_bzero.o \
	ft_memcpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_strchr.o ft_strrchr.o \
	ft_strncmp.o ft_strnstr.o ft_strlcpy.o ft_strdup.o ft_calloc.o ft_strlcat.o \
	ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_itoa.o ft_striteri.o \
	ft_strmapi.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_atod.o ft_iswhitespace.o

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	cc $(GCCFLAGS) -I $(PATH_INCLUDE) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all







