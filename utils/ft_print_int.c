#include "../ft_printf.h"

int		check_width_int(t_lit list_flags, int size, int num)
{
	int	count;

	count = 0;
	if (list_flags.zero) // no precision
	{
		if (num < 0)
		{
			write(1, "-", 1);
			count++;
		}
		count += ft_add_space('0', list_flags.width - size); // 
	}
	else if (list_flags.precision >= size) // มี precision 
	{
		if (num < 0)
			count += ft_add_space(' ', list_flags.width -
					list_flags.precision - 1); // -1 คือ position minus sign 
		else
			count += ft_add_space(' ', list_flags.width - list_flags.precision); //กรณีเป็น +
	}
	else
		count += ft_add_space(' ', list_flags.width - size); // ปริ้งช่องว่างตาม width, case ปกติ
	return (count);
}

int		check_precision_int(t_lit list_flags, int size, int num)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	if (num < 0 && list_flags.precision < size && !list_flags.zero) //
	{
		write(1, "-", 1);
		return (1);
	}
	if (list_flags.precision > 0)
	{
		if (num < 0)
		{
			write(1, "-", 1);
			count++;
			i--;
		}
		while (i++ < list_flags.precision - size) // -1 < (4-3) 4 123 >> 0123
		{
			write(1, "0", 1);
			count++;
		}
	}
	return (count);
}

int		check_minus_int(t_lit list_flags, int size, char *str, int num) // function นี้เปลี่ยนแต่ค่า str
{
	int	count;

	count = 0;
	if (num < 0)
		str++; // shift position to next (ignore - sign) then check flag.minus from line 66
	if (list_flags.minus)
	{
		count += check_precision_int(list_flags, size, num); // print 0 = (precision - width)
		count += ft_putstr_fd(str, 1);
		count += check_width_int(list_flags, size, num);
	}
	else if (!list_flags.minus)
	{
		count += check_width_int(list_flags, size, num);
		count += check_precision_int(list_flags, size, num);
		count += ft_putstr_fd(str, 1);
	}
	return (count);
}

int		ft_print_int(t_lit list_flags, va_list argv)
{
	int		num;
	char	*str;
	int		size;
	int		count;

	num = va_arg(argv, int); 
	str = ft_itoa(num);
	size = ft_strlen(str);
	count = 0;
	if (list_flags.zero && (list_flags.minus || list_flags.precision >= 0)) // 
		list_flags.zero = 0;
	if (list_flags.precision == 0 && *str == '0') // ค่าvar เป็น char 0 รึเปล่า, >> print ช่องว่างก่อน input integer
	{
		count += ft_add_space(' ', list_flags.width);
		return (count);
	}
	count += check_minus_int(list_flags, size, str, num);
	free(str);
	return (count);
}
