#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s && fd)
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	return (i);
}
