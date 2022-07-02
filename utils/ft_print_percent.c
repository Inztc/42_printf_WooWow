#include "../ft_printf.h"

int		ft_print_percent(t_lit list_flags)
{
	int count;

	count = 0;
	if (list_flags.minus) // minus is left allign, : (no minus)___a,(minus) a___   "%4s", cat :cat_ , _cat (no minus)
	{
		ft_putchar_fd('%', 1);
		count += ft_add_space(' ', list_flags.width - 1);
	}
	else if (!list_flags.minus)
	{
		if (list_flags.zero) // %04
			count += ft_add_space('0', list_flags.width - 1);
		else
			count += ft_add_space(' ', list_flags.width - 1);
		ft_putchar_fd('%', 1);
	}
	return (count + 1);
}
