/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/23 19:25:33 by azamario         ###   ########.fr       */
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
	if (fl.type == 'x' || fl.type == 'X')
		print_xX(fl, args, len);
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
		fl.minus = 1;
	if (format[*i] == '0' && fl.minus == 0 && fl.width == 0)
		fl.zero = 1;
	if (format[*i] == '.')
		fl.dot = 1;
	if (ft_strchr(NUMBERS, format[*i]))
	{
		if (fl.dot == 1)
			fl.precision = (fl.precision * 10) + (format[*i] - '0');
		else
			fl.width = (fl.width * 10) + (format[*i] - '0');
	}	
	return (fl);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;
	t_flags	fl;

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
			fl = ft_clean_flags ();
			while (format[i] && ft_strchr(FLAGS, format[i]))
			{
				fl = get_flag_width_precision(format, fl, &i);
				i++, len++;
			}
			get_types(format, &i, &len, args, fl);
		}
	}
	va_end(args);
	return (len);
}


int main (void)
{
	// TESTES DE x E X
	printf("----------TESTES DE x SEM FLAG - E SEM OPÇÃO 0--------\n");
	printf("%x\n", 123456789);
	ft_printf("%x\n", 123456789);

	printf("%15x\n", 123456789); 
	ft_printf("%15x\n", 123456789); //vai até 15 de width sem crashar <-------------------------

	printf("%3X\n", 123456789);
	ft_printf("%3X\n", 123456789);

	printf("%7X\n", 123456789);
	ft_printf("%7X\n", 123456789);

	printf("----------TESTES DE x COM FLAG - E SEM OPÇÃO 0--------\n");
	printf("%-x\n", 123456789);
	ft_printf("%-x\n", 123456789);

	printf("%-20x\n", 123456789);
	ft_printf("%-20x\n", 123456789);

	printf("%-3x\n", 123456789);
	ft_printf("%-3x\n", 123456789);

	printf("%7x\n", 123456789);
	ft_printf("%7x\n", 123456789);


	printf("----------TESTES DE x SEM FLAG - E COM  OPÇÃO 0--------\n");
	printf("%0x\n", 123456789);
	ft_printf("%0x\n", 123456789);

	printf("%015x\n", 123456789);
	ft_printf("%015x\n", 123456789);

	printf("%03x\n", 123456789);
	ft_printf("%03x\n", 123456789);

	printf("%07x\n", 123456789);
	ft_printf("%07x\n", 123456789);

/*	printf("----------TESTES DE x COM FLAG - E COM OPÇÃO 0--------\n");
	printf("%-0x\n", 123456789);
	ft_printf("%-0x\n", 123456789);

	printf("%-015x\n", 123456789);
	ft_printf("%-015x\n", 123456789);

	printf("%-03x\n", 123456789);
	ft_printf("%-03x\n", 123456789);

	printf("%-07x\n", 123456789);
	ft_printf("%-07x\n", 123456789);
*/


	// TESTES DE PONTEIRO
    //char    *string = "Hello";
/*	printf("----------TESTES DE PONTEIRO SEM FLAG - E SEM OPÇÃO 0--------\n");
    printf("%p\n", &string);
   	ft_printf("%p\n", &string);

    printf("%20p\n", &string);
   	ft_printf("%20p\n", &string);

    printf("%3p\n", &string);
   	ft_printf("%3p\n", &string);

    printf("%14p\n", &string);
   	ft_printf("%14p\n", &string);

	printf("----------TESTES DE PONTEIRO COM FLAG - E SEM OPÇÃO 0--------\n");
    printf("%-p\n", &string);
   	ft_printf("%-p\n", &string);

    printf("%-20p\n", &string);
   	ft_printf("%-20p\n", &string);

    printf("%-3p\n", &string);
   	ft_printf("%-3p\n", &string);

    printf("%-14p\n", &string);
   	ft_printf("%-14p\n", &string);
*/
/*
	printf("----------TESTES DE PONTEIRO SEM FLAG - E COM OPÇÃO 0--------\n");
	printf("%0p\n", &string);
   	ft_printf("%0p\n", &string);

	printf("%020p\n", &string);
   	ft_printf("%020p\n", &string);

	printf("%03p\n", &string);
   	ft_printf("%03p\n", &string);

	printf("%014p\n", &string);
   	ft_printf("%014p\n", &string);

	printf("----------TESTES DE PONTEIRO COM FLAG - E COM OPÇÃO 0--------\n");
	printf("%-0p\n", &string);
   	ft_printf("%-0p\n", &string);

	printf("%-020p\n", &string);
   	ft_printf("%-020p\n", &string);

	printf("%-03p\n", &string);
   	ft_printf("%-03p\n", &string);

	printf("%-014p\n", &string);
   	ft_printf("%-014p\n", &string);
*/


	//TESTES DE UNSIGNED INT
/*
	printf("TESTES PARA FLAG ZERO COM O ZERO ANTES DO WIDTH\n");

	printf("%u\n", 123456789);
	ft_printf("%u\n", 123456789);

	printf("%0u\n", 123456789);
	ft_printf("%0u\n", 123456789);

	printf("%0.3u\n", 123456789);
	ft_printf("%0.3u\n", 123456789);

	printf("%0.9u\n", 123456789);
	ft_printf("%0.9u\n", 123456789);

	printf("%0.14u\n", 123456789);
	ft_printf("%0.14u\n", 123456789);

	printf("%014u\n", 123456789);
	ft_printf("%014u\n", 123456789);

	printf("%014.3u\n", 123456789);
	ft_printf("%014.3u\n", 123456789);

	printf("%014.9u\n", 123456789);
	ft_printf("%014.9u\n", 123456789);

	printf("%014.14u\n", 123456789);
	ft_printf("%014.14u\n", 123456789);

	printf("%09u\n", 123456789);
	ft_printf("%09u\n", 123456789);

	printf("%09.3u\n", 123456789);
	ft_printf("%09.3u\n", 123456789);

	printf("%09.9u\n", 123456789);
	ft_printf("%09.9u\n", 123456789);

	printf("%09.14u\n", 123456789);
	ft_printf("%09.14u\n", 123456789);
 
	printf(".............................................\n\n\n\n");
	printf("TESTES PARA FLAG ZERO SEM O ZERO ANTES DO WIDTH\n");
	printf("%u\n", 123456789);
	ft_printf("%u\n", 123456789);

	printf("%.3u\n", 123456789);
	ft_printf("%.3u\n", 123456789);

	printf("%.9u\n", 123456789);
	ft_printf("%.9u\n", 123456789);

	printf("%.14u\n", 123456789);
	ft_printf("%.14u\n", 123456789);

	printf("%14u\n", 123456789);
	ft_printf("%14u\n", 123456789);

	printf("%14.3u\n", 123456789);
	ft_printf("%14.3u\n", 123456789);

	printf("%14.9u\n", 123456789);
	ft_printf("%14.9u\n", 123456789);

	printf("%14.14u\n", 123456789);
	ft_printf("%14.14u\n", 123456789);

	printf("%9u\n", 123456789);
	ft_printf("%9u\n", 123456789);

	printf("%9.3u\n", 123456789);
	ft_printf("%9.3u\n", 123456789);

	printf("%9.9u\n", 123456789);
	ft_printf("%9.9u\n", 123456789);

	printf("%9.14u\n", 123456789);
	ft_printf("%9.14u\n", 123456789);
*/
/*
	printf("TESTES PARA FLAG - COM O ZERO ANTES DO WIDTH\n");

	printf("%-u\n", 123456789);
	ft_printf("%-u\n", 123456789);

	printf("%-0u\n", 123456789);
	ft_printf("%-0u\n", 123456789);

	printf("%-0.3u\n", 123456789);
	ft_printf("%-0.3u\n", 123456789);

	printf("%-0.9u\n", 123456789);
	ft_printf("%-0.9u\n", 123456789);

	printf("%-0.14u\n", 123456789);
	ft_printf("%-0.14u\n", 123456789);

	printf("%-014u\n", 123456789);
	ft_printf("%-014u\n", 123456789);

	printf("%-014.3u\n", 123456789);
	ft_printf("%-014.3u\n", 123456789);

	printf("%-014.9u\n", 123456789);
	ft_printf("%-014.9u\n", 123456789);

	printf("%-014.14u\n", 123456789);
	ft_printf("%-014.14u\n", 123456789);

	printf("%-09u\n", 123456789);
	ft_printf("%-09u\n", 123456789);

	printf("%-09.3u\n", 123456789);
	ft_printf("%-09.3u\n", 123456789);

	printf("%-09.9u\n", 123456789);
	ft_printf("%-09.9u\n", 123456789);

	printf("%-09.14u\n", 123456789);
	ft_printf("%-09.14u\n", 123456789);
*/
/*
	printf(".............................................\n\n\n\n");
	printf("TESTES PARA FLAG - SEM O ZERO ANTES DO WIDTH\n");
	printf("%-u\n", 123456789);
	ft_printf("%-u\n", 123456789);

	printf("%-.3u\n", 123456789);
	ft_printf("%-.3u\n", 123456789);

	printf("%-.9u\n", 123456789);
	ft_printf("%-.9u\n", 123456789);

	printf("%-.14u\n", 123456789);
	ft_printf("%-.14u\n", 123456789);

	printf("%-14u\n", 123456789);
	ft_printf("%-14u\n", 123456789);

	printf("%-14.3u\n", 123456789);
	ft_printf("%-14.3u\n", 123456789);

	printf("%-14.9u\n", 123456789);
	ft_printf("%-14.9u\n", 123456789);

	printf("%-14.14u\n", 123456789);
	ft_printf("%-14.14u\n", 123456789);

	printf("%-9u\n", 123456789);
	ft_printf("%-9u\n", 123456789);

	printf("%-9.3u\n", 123456789);
	ft_printf("%-9.3u\n", 123456789);

	printf("%-9.9u\n", 123456789);
	ft_printf("%-9.9u\n", 123456789);

	printf("%-9.14u\n", 123456789);
	ft_printf("%-9.14u\n", 123456789);
*/

/*

	// TESTES DE INT E D

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
*/	
/*
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

/*	
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
*/	

	
/*	//TESTES DE CHAR
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
