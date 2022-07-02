#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct		s_lst  //name of structure = s_lst
{
	int	minus;
	int	zero;
	int	point;
	int	width;
	int	precision;
}					t_lit; // structure variable type t_lst ซึ่งสามารถประกาศ object แยกทีหลังได้เช่น object a มีvar minus, zero, point, object b เช่รกัน

int					ft_printf(const char *str, ...);
int					ft_check_flag(char flag);
int					ft_add_space(char c, int width); // add fill space  
int					ft_print_spec(char flag, t_lit list_flags, va_list argv); //print value type (specifier)
int					ft_check_digit(unsigned long long number, int size); //check digit , total index 
int					ft_print_char(t_lit list_flags, va_list argv); // print char
int					ft_print_str(t_lit list_flags, va_list argv);  // print str
int					ft_print_ptr(t_lit list_flags, va_list argv);  // print pointer
int					ft_print_int(t_lit list_flags, va_list argv);  // print int
int					ft_print_unsigned(t_lit list_flags, va_list argv); // print positive num
char				*ft_convert_pointer(char *array_hex, unsigned long long number);
int					ft_print_hex(char *array_hex, t_lit list_flags, va_list argv);
int					ft_print_percent(t_lit list_flags);

#endif
