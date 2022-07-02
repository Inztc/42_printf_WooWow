#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;


size_t				ft_strlen(const char *str);
int					ft_isdigit(int ch);
char				*ft_strdup(const char *str);
char				*ft_itoa(int n);
void				ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
char				*ft_utoa(unsigned int n);

#endif
