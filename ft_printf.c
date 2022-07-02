#include "ft_printf.h"

t_lit	ft_init(t_lit listflags) //flag initialize เพราะเป็นการผ่าน argument ประเภท structureเข้ามาประเภท functionเลยเป็น t_lst
{
	listflags.minus = 0; // no minus
	listflags.zero = 0; // no zero
	listflags.point = 0; // no point
	listflags.width = 0; // no width
	listflags.precision = -1;  // have precision
	return (listflags);
}

t_lit	ft_cut_star(t_lit listflags, va_list argv)
{
	if (listflags.point == 1)
		listflags.precision = va_arg(argv, int);
	else if (listflags.width < 1)
	{
		listflags.width = va_arg(argv, int);
		if (listflags.width < 0)
		{
			listflags.width *= (-1);
			listflags.minus = 1;
		}
	}
	return (listflags);
}

t_lit		ft_cut_flags(const char *flag, t_lit listflags, va_list argv) // function screen flag ทั้ง string 
{
	int i;

	i = 0;
	while (flag[i] && ft_check_flag(flag[i])) // check flag[i] ไม่ใช่ null และ เป็น -, *, digit, .
	{
		if (flag[i] == '-') // screen minus flag
			listflags.minus = 1; // ถ้าใช่ set minus flag เป็น 1
		else if (flag[i] == '0' && listflags.width < 1 && 
				listflags.point == 0)//ถ้าไม่มี precision และ width < 0 และ flag รอบนั้นๆเป็น 0
			listflags.zero = 1; //ถ้าใช่ set flag zero = 1
		else if (ft_isdigit(flag[i]) && listflags.point == 0) // เป็นตัวเลขหรือเปล่า และ flag. เป็น 0 no precision
			listflags.width = (listflags.width * 10) + (flag[i] - 48); // แปลงค่า parameter 0 ของ width เป็น int เพราะ flag width ต้องมีค่าเปนตัวเลข
		else if (flag[i] == '.') // ถ้า flag . ถูกเจอ
		{
			listflags.point = 1; 
			listflags.precision = 0; // check precision
		}
		else if (ft_isdigit(flag[i]) && listflags.point == 1) // มีทั้งตัวเลขและจุด คือ เป็น digit ก็ใช้ convert atoi
			listflags.precision = (listflags.precision * 10) + (flag[i] - 48); // atoi
		else if (flag[i] == '*')
			listflags = ft_cut_star(listflags, argv);
		i++;
	}
	return (listflags); // update ทั้ง listflags ว่ามีตัวไหนบ้าง
}

int		ft_printf(const char *str, ...) // *str คือชี้ string ฝั่งซ้ายของ printf function, ... คือ การ detect %letter ซึ่งจะdetectเจอกี่ครั้งไม่รู้
{
	int		i;
	int		count;
	va_list	argv; // ชื่อ list variable (หรือจะเรียก argument parameters ก็ได้)
	t_lit	listflags; // ประกาศ object ของ structure var t_lst ซึ่งมี 5 variable list flag อยู่ข้างใน

	i = 0;
	count = 0;	
	va_start(argv, str); // start of variadic function, เป็น patter 1st va_listที่ประกาศ 2nd arg = last requiured argument ที่จะ pass เข้า function (str)
	while (str[i] != '\0') // run จนชน null terminator 
	{				// variadic เป็นการใช้ macroเข้าร่วม start end, ซึ่งกรณีนี้ input เข้ามาเป็น str  แต่ไม่รู้จำนวน สามารถใช้ va_arg(argv, type) ร่วมด้วยได้
		count += (str[i] == '%') ? 0 : 1; // ถ้า str[i] เป็น % count = count + 0, แต่ถ้า ไม่ใช่ % count = count + 1		
		if (str[i] == '%' && str[i + 1] != '\0') // ถ้า format specifier ถูก detect เข้า if statement,
		{
			listflags = ft_init(listflags); // update object listflags ผ่านfunction ft_init
			listflags = ft_cut_flags(&str[++i], listflags, argv); // update object listflags ผ่านfunction  ft_cut_flags
			while (ft_check_flag(str[i]))
				i++;
			count += ft_print_spec(str[i], listflags, argv);
		}
		else // ถ้าเป็น string ทั่วไป ไม่เจอ% พิมปกติได้เลย
			ft_putchar_fd(str[i], 1); 
		i += (str[i] == '\0') ? 0 : 1;
	}
	va_end(argv);
	return (count);
}
