#include "../ft_printf.h"

char	*ft_convert_pointer(char *array_hex, unsigned long long number)
{
	int		size_hex; // 
	int		count_num; //หารได้กี่รอบ
	char	*str; // convert hex to string

	size_hex = ft_strlen(array_hex); // นับความยาว array hex (OAD8 = size = 4)
	count_num = ft_check_digit(number, size_hex); // return count = digit
	if (!(str = (char *)malloc(sizeof(char) * (count_num + 1)))) // +1 เพราะ hex เป็น array (+ null terminate)
		return (NULL);
	str[count_num] = '\0'; // str index สุดท้ายไม่ใช่ null terminator
	while (--count_num) // ex. 3
	{
		str[count_num] = array_hex[number % size_hex]; // count 3: xxx
		number /= size_hex;
	}
	if (count_num == 0)
		str[count_num] = array_hex[number % size_hex];
	return (str);
}

int		check_minus_ptr(t_lit list_flags, int size, char *str)
{
	int	count;

	count = 0;
	if (list_flags.minus)
	{
		count += ft_putstr_fd("0x", 1);
		count += ft_putstr_fd(str, 1);
		count += ft_add_space(' ', list_flags.width - (size + 2));
	}
	else if (!list_flags.minus)
	{
		count += ft_add_space(' ', list_flags.width - (size + 2));
		count += ft_putstr_fd("0x", 1);
		count += ft_putstr_fd(str, 1);
	}
	return (count);
}

int		ft_print_ptr(t_lit list_flags, va_list argv)
{
	char				*str;
	int					size;
	int					count;
	unsigned long long	num;

	num = va_arg(argv, unsigned long long); // va_arg เก็บค่า argv ที่ cap = long long unsigned
	if (!num) // 
		str = (list_flags.precision == 0) ? ft_strdup("") : ft_strdup("0");
	else
		str = ft_convert_pointer("0123456789abcdef", num);
	size = ft_strlen(str);
	count = 0;
	count += check_minus_ptr(list_flags, size, str);
	free(str);
	return (count);
}
