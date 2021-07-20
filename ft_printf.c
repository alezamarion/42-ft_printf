/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/20 16:46:03 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_types(int *len, va_list args, t_flags fl)
{
	if (fl.type == 'c')
		print_c(va_arg(args, int), len, fl);
	if (fl.type == 's')
		print_s(va_arg(args, char *), len);
	if (fl.type == 'i' || fl.type == 'd')
		print_i_d(fl, args, len);
	if (fl.type == 'u')
		print_u(fl, args, len);
	if (fl.type == 'p')
		print_p(fl, args, len);
	if (fl.type == 'x')
		print_x(fl, args, len);
	if (fl.type == 'X')
		print_X(fl, args, len);
	if (fl.type == '%')
		print_pct(len);
}

static void	get_types(const char *format, int *i, int *len, va_list args, t_flags fl)
{

	if (ft_strchr(CONVERSIONS, format[*i]))
	{
		fl.type = format[(*i)++];
		handle_types(len, args, fl);
	}
}

t_flags	get_flag_width_precision(const char *format, t_flags fl, int *i)
{
	if (format[*i] == '-')
	{
		fl.minus = 1;
		fl.zero = 0;
	}
	if (format[*i] == '0' && fl.minus == 0 && fl.width == 0)
		fl.zero = 1;
	if (format[*i] == '.')
		fl.dot = 1;
	if (ft_strchr(NUMBERS, format[*i]))
	{
		if (fl.dot == 1)
		{
			fl.precision = (fl.precision * 10) + (format[*i] - '0');
		}
		else
		{
			fl.width = (fl.width * 10) + (format[*i] - '0');
		}
	}	
	return (fl);
}


int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;
	t_flags fl;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_putchar_len(format[i++], &len);
		else
		{
			i++;
			fl = ft_clean_flags();
			while(format[i] && ft_strchr(FLAGS, format[i]))
			{
				fl = get_flag_width_precision(format, fl, &i);
				i++, len++;
			}
			get_types(format, &i, &len, args, fl);
			if (len == -1)
				return (-1);
		}
	}
	va_end(args);
	return (len);
}

int main (void)
{
	printf("\n   caso 1 printf: %c\n", 'C');
	ft_printf("caso 1 ft_printf: %c\n", 'C');

	printf("\n   caso2  printf: %10c\n", 'C');
	ft_printf("caso 2 ft_printf: %10c\n", 'C');

	printf("\n   caso 3 printf: %-10c\n", 'C');
	ft_printf("caso 3 ft_printf: %-10c\n", 'C');

    /*
	char c = 'u';
	char *s = "Vila 26 bombando";
    int in = 42;
    int dec = 42;
    unsigned int ui = -3000;
    int hexa = 300000000;

    printf("\n   printf -> char: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n", c, s, in, dec, ui);
    ft_printf("ft_printf -> char: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n\n", c, s, in, dec, ui);

    printf("\n   printf -> pointer: %p, hexa 'x': %x, hexa 'X': %X,  %%\n", &s, hexa, hexa);
    ft_printf("ft_printf -> pointer: %p, hexa 'x': %x, hexa 'X': %X,  %%\n\n", &s, hexa, hexa);
	*/
    return (0);
}
