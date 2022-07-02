CC = gcc
NAME = libftprintf.a
MAKE = make
FLAGS = -Wall -Wextra -Werror
SRCS =	./ft_printf.c ./ft_printf_utils.c ./utils/ft_print_char.c ./utils/ft_print_str.c ./utils/ft_print_ptr.c ./utils/ft_print_int.c ./utils/ft_print_unsigned.c ./utils/ft_print_hex.c ./utils/ft_print_percent.c
HEAD = ft_printf.h
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(HEAD) 
	@cd libft && $(MAKE) bonus
	@cp libft/libft.a $(NAME)
	@ar -rcs $(NAME) $(OBJS)
	@echo "libftprintf.a initiated"

%.o: %.c
	@$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)
	

clean :
	@rm -f $(OBJS)
	@$(MAKE) clean -C ./libft
	

fclean : clean
	@rm -f $(NAME)
	@rm -f libft.a
	@$(MAKE) fclean -C ./libft
	

re : fclean all

.PHONY: all re fclean clean
