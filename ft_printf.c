/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/18 12:01:16 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_types(int *len, va_list args, t_flags fl)
{
	if (fl.type == 'c')
		print_c(va_arg(args, int), len);
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

static void	get_types_and_print(const char *format, int *i, int *len, va_list args)
{
	t_flags	fl;

	if (ft_strchr(CONVERSIONS, format[*i]))
	{
		fl.type = format[(*i)++];
		handle_types(len, args, fl);
	}
}


static void	get_flag_width_precision(const char *format, int *i, int *len);
{
	t_flags fl;

	if (*format == '-')
		fl.minus = 1;
	if (*format == )

}


int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

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
			while(format[i] && ft_strchr(FLAGS, format[i]))
				get_flag_width_precision(format, &i, &len);
			get_types_and_print(format, &i, &len, args);
			if (len == -1)
				return (-1);
		}
	}
	va_end(args);
	return (len);
}

int main (void)
{
    char c = 'u';
    char *s = "Vila 26 bombando";
    int in = 42;
    int dec = 42;
    unsigned int ui = -300;
    int hexa = 30000000;


    printf("\n   printf -> char: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n", c, s, in, dec, ui);
    ft_printf("ft_printf -> char: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n\n", c, s, in, dec, ui);

    printf("\n   printf -> pointer: %p, hexa 'x': %x, hexa 'X': %X,  %%\n", &s, hexa, hexa);
    ft_printf("ft_printf -> pointer: %p, hexa 'x': %x, hexa 'X': %X,  %%\n\n", &s, hexa, hexa);
   
    return (0);
}
