/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/21 21:49:39 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_types(int *len, va_list args, t_flags fl)
{
	if (fl.type == 'c')
		print_c(va_arg(args, int), len, fl);
	if (fl.type == 's')
		print_s(va_arg(args, char *), len, fl);
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
	// TESTES DE INT E D
/*
	// TESTES SEM FLAG - //
	printf("CASOS COM ZERO ANTES DO WIDTH E SEM FLAG '-'\n");
	printf("CASOS COM ZERO ANTES DO WIDTH E SEM FLAG '-'\n");
	//1
	printf("casos de impressão normal:\n");
	printf("%0i\n", 123456);
	ft_printf("%0i\n", 123456);

	printf("%0.3i\n", 123456);
	ft_printf("%0.3i\n", 123456);

	printf("%0.6i\n", 123456);
	ft_printf("%0.6i\n", 123456);

	printf("%3i\n", 123456);
	ft_printf("%3i\n", 123456);

	printf("%03.3i\n", 123456);
	ft_printf("%03.3i\n", 123456);

	printf("%03.6i\n", 123456);
	ft_printf("%03.6i\n", 123456);

	printf("%06i\n", 123456);
	ft_printf("%06i\n", 123456);

	printf("%06.3i\n", 123456);
	ft_printf("%06.3i\n", 123456);

	printf("%06.6i\n", 123456);
	ft_printf("%06.6i\n", 123456);
	
	//2
	printf("casos precisão-size: imprime zeros + imprime string\n");
	printf("%0.10i\n", 123456);
	ft_printf("%0.10i\n", 123456);

	printf("%03.10i\n", 123456);
	ft_printf("%03.10i\n", 123456);

	printf("%03.10i\n", 123456);
	ft_printf("%03.10i\n", 123456);

	printf("%06.10i\n", 123456);
	ft_printf("%06.10i\n", 123456);
	
	//3
	printf("casos precisão-size: imprime espaços + imprime string\n");
	printf("%010.3i\n", 123456); 
	ft_printf("%010.3i\n", 123456);

	printf("%010.6i\n", 123456);
	ft_printf("%010.6i\n", 123456);
	

	printf("CASOS SEM O ZERO ANTES DO WIDTH E SEM FLAG '-'\n");
	//1
	printf("casos de impressão normal:\n");
	printf("%i\n", 123456);
	ft_printf("%i\n", 123456);

	printf("%.3i\n", 123456);
	ft_printf("%.3i\n", 123456);

	printf("%.6i\n", 123456);
	ft_printf("%.6i\n", 123456);

	printf("%3i\n", 123456);
	ft_printf("%3i\n", 123456);

	printf("%3.3i\n", 123456);
	ft_printf("%3.3i\n", 123456);

	printf("%3.6i\n", 123456);
	ft_printf("%3.6i\n", 123456);

	printf("%6i\n", 123456);
	ft_printf("%6i\n", 123456);

	printf("%6.3i\n", 123456);
	ft_printf("%6.3i\n", 123456);

	printf("%6.6i\n", 123456);
	ft_printf("%6.6i\n", 123456);
	
	//2
	printf("casos precisão-size: imprime zeros + imprime string\n");	
	printf("%.10i\n", 123456);
	ft_printf("%.10i\n", 123456);

	printf("%3.10i\n", 123456);
	ft_printf("%3.10i\n", 123456);

	printf("%3.10i\n", 123456);
	ft_printf("%3.10i\n", 123456);

	printf("%6.10i\n", 123456);
	ft_printf("%6.10i\n", 123456);
	
	//3
	printf("casos precisão-size: imprime espaços + imprime string\n");

	printf("%10.3i\n", 123456); 
	ft_printf("%10.3i\n", 123456);

	printf("%10.6i\n", 123456);
	ft_printf("%10.6i\n", 123456);

*/
//////////

/*
	// TESTES COM FLAG - //
	printf("CASOS COM ZERO ANTES DO WIDTH E COM FLAG '-'\n");
	printf("CASOS COM ZERO ANTES DO WIDTH E COM FLAG '-'\n");
	printf("CASOS COM ZERO ANTES DO WIDTH E COM FLAG '-'\n");

	//1
	printf("casos de impressão normal:\n");
	printf("%-0i\n", 123456);
	ft_printf("%-0i\n", 123456);

	printf("%-0.3i\n", 123456);
	ft_printf("%-0.3i\n", 123456);

	printf("%-0.6i\n", 123456);
	ft_printf("%-0.6i\n", 123456);

	printf("%-3i\n", 123456);
	ft_printf("%-3i\n", 123456);

	printf("%-03.3i\n", 123456);
	ft_printf("%-03.3i\n", 123456);

	printf("%-03.6i\n", 123456);
	ft_printf("%-03.6i\n", 123456);

	printf("%-06i\n", 123456);
	ft_printf("%-06i\n", 123456);

	printf("%-06.3i\n", 123456);
	ft_printf("%-06.3i\n", 123456);

	printf("%-06.6i\n", 123456);
	ft_printf("%-06.6i\n", 123456);
	
	//2
	printf("casos precisão-size: imprime zeros + imprime string\n");
	printf("%-0.10i\n", 123456);
	ft_printf("%-0.10i\n", 123456);

	printf("%-03.10i\n", 123456);
	ft_printf("%-03.10i\n", 123456);

	printf("%-03.10i\n", 123456);
	ft_printf("%-03.10i\n", 123456);

	printf("%-06.10i\n", 123456);
	ft_printf("%-06.10i\n", 123456);
	
	//3
	printf("casos precisão-size: imprime espaços + imprime string\n");
	printf("%-010.3i\n", 123456); 
	ft_printf("%-010.3i\n", 123456);

	printf("%-010.6i\n", 123456);
	ft_printf("%-010.6i\n", 123456);
	

	printf("CASOS SEM O ZERO ANTES DO WIDTH E COM FLAG '-'\n");
	//1
	printf("casos de impressão normal:\n");
	printf("%-i\n", 123456);
	ft_printf("%-i\n", 123456);

	printf("%-.3i\n", 123456);
	ft_printf("%-.3i\n", 123456);

	printf("%-.6i\n", 123456);
	ft_printf("%-.6i\n", 123456);

	printf("%-3i\n", 123456);
	ft_printf("%-3i\n", 123456);

	printf("%-3.3i\n", 123456);
	ft_printf("%-3.3i\n", 123456);

	printf("%-3.6i\n", 123456);
	ft_printf("%-3.6i\n", 123456);

	printf("%-6i\n", 123456);
	ft_printf("%-6i\n", 123456);

	printf("%-6.3i\n", 123456);
	ft_printf("%-6.3i\n", 123456);

	printf("%-6.6i\n", 123456);
	ft_printf("%-6.6i\n", 123456);
	
	//2
	printf("casos precisão-size: imprime zeros + imprime string\n");	
	printf("%-.10i\n", 123456);
	ft_printf("%-.10i\n", 123456);

	printf("%-3.10i\n", 123456);
	ft_printf("%-3.10i\n", 123456);

	printf("%-3.10i\n", 123456);
	ft_printf("%-3.10i\n", 123456);

	printf("%-6.10i\n", 123456);
	ft_printf("%-6.10i\n", 123456);
	
	//3
	printf("casos precisão-size: imprime espaços + imprime string\n");

	printf("%-10.3i\n", 123456); 
	ft_printf("%-10.3i\n", 123456);

	printf("%-10.6i\n", 123456);
	ft_printf("%-10.6i\n", 123456);
	
*/
	
	//TESTES DE STRING
	printf("\nimpressão sem flags:\n\n");

	printf("%s\n", "Vila 26");
	ft_printf("%s\n", "Vila 26");

	printf("\nsem a flag '-':\n\n");

	printf("%10s\n", "Vila 26");
	ft_printf("%10s\n", "Vila 26");

	printf("%.4s\n", "Vila 26");
	ft_printf("%.4s\n", "Vila 26");

	printf("%10.4s\n", "Vila 26");
	ft_printf("%10.4s\n", "Vila 26");

	printf("%4.10s\n", "Vila 26");
	ft_printf("%4.10s\n", "Vila 26");

	printf("\ncom a flag '-':\n\n");
	
	printf("%-10s\n", "Vila 26");
	ft_printf("%-10s\n", "Vila 26");

	printf("%-.4s\n", "Vila 26");
	ft_printf("%-.4s\n", "Vila 26");

	printf("%-10.4s\n", "Vila 26");
	ft_printf("%-10.4s\n", "Vila 26");

	printf("%-4.10s\n", "Vila 26");
	ft_printf("%-4.10s\n", "Vila 26");
	

	/*
	TESTES DE CHAR
	printf("\n   caso 1 printf: %c\n", 'C');
	ft_printf("caso 1 ft_printf: %c\n", 'C');

	printf("\n   caso2  printf: %10c\n", 'C');
	ft_printf("caso 2 ft_printf: %10c\n", 'C');

	printf("\n   caso 3 printf: %-10c\n", 'C');
	ft_printf("caso 3 ft_printf: %-10c\n", 'C');
	*/

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
