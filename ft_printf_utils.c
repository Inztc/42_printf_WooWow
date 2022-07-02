#include "ft_printf.h"

int		ft_check_flag(char flag) //
{
	return (flag == '-' || ft_isdigit(flag) || flag == '.' || flag == '*'); // เช็คว่า flag เป็นอันใดอันหนึ่ง
}

int		ft_check_digit(unsigned long long number , int size) //should be check digit (แต่ที่ return มันจะขาดไป 1 digit)
{
	int	count;

	count = 0; // จำนวนครั้งที่หาร = digit
	while (number > 0) 
	{
		number /= size; // size น่าจะเป็น จำนวนของฐานเช่น binary size = 2, hex size =16
		count++;
	}
	return (count); // return count = digit, จบ loop count +1 แต่ไปหลุดบรรทัด while
}
	
int		ft_add_space(char c, int width) // print fill ให้เต็ม width (' ', หรือ อื่นๆ)
{
	int i;

	i = -1;
	while (++i < width)
		ft_putchar_fd(c, 1); // putchar ตัวนี้เราใช้ print ' ', หรือ flag ตัวอื่นที่นอกเหนือกว่านี้
	return (i); // จำนวน space ที่ต้องเติม
}

int		ft_print_other_flag(char flag, t_lit list_flags)
{
	int count;

	count = 1;
	if (list_flags.minus)
	{
		ft_putchar_fd(flag, 1);
		if (list_flags.width) //ex. width = 5
			count += ft_add_space(' ', list_flags.width - 1); //print text หมดให้ print ' '
	}
	else if (!list_flags.minus)
	{
		if (list_flags.width)
			count += ft_add_space(' ', list_flags.width - 1);
		ft_putchar_fd(flag, 1);
	}
	return (count);
}

int		ft_print_spec(char flag, t_lit list_flags, va_list argv)
{
	int count;

	count = 0;
	if (flag == 'c')
		count = ft_print_char(list_flags, argv);
	else if (flag == 's')
		count = ft_print_str(list_flags, argv);
	else if (flag == 'p')
		count = ft_print_ptr(list_flags, argv);
	else if (flag == 'd' || flag == 'i')
		count = ft_print_int(list_flags, argv);
	else if (flag == 'u')
		count = ft_print_unsigned(list_flags, argv);
	else if (flag == 'x')
		count = ft_print_hex("0123456789abcdef", list_flags, argv);
	else if (flag == 'X')
		count = ft_print_hex("0123456789ABCDEF", list_flags, argv);
	else if (flag == '%')
		count = ft_print_percent(list_flags);
	else
		count = ft_print_other_flag(flag, list_flags); //เขียนดักไว้ ไม่มี function รองรับ >> แทนด้วย return(0);
	return (count);
}
