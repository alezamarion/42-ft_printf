/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/29 18:28:52 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_types(const char c, int *len, va_list args, t_flags fl)
{
	if (c == 'c')
		print_c(va_arg(args, int), len, fl);
	if (c == 's')
		print_s(va_arg(args, char *), len, fl);
	if (c == 'i' || c == 'd')
		print_i_d(fl, args, len);
	if (c == 'u')
		print_u(fl, args, len);
	if (c == 'p')
		print_p(fl, args, len, c);
	if (c == 'x' || c == 'X')
		print_xX(fl, args, len, c);
	if (c == '%')
		ft_putstr_len("%", len);
	if (ft_strchr(TYPES, c) == 0)
		(*len) = -1;
	return (*len);
}

t_flags	get_flag_width_precision(const char *format, t_flags fl, int *i)
{
	if (format[*i] == '-')
		fl.minus = 1;
	else if (format[*i] == '0' && fl.minus == 0 && fl.width == 0)
		fl.zero = 1;
	else if (format[*i] == '.')
	{
		fl.dot = 1;
	}
	else if (ft_strchr(NUMBERS, format[*i]))
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
			ft_putchar_len(format[i++], &len);   // espaço len1 + c len2 + espaço len3 + espaço len4
		else
		{ 	
			i++;
			fl = ft_clean_flags ();
			while (format[i] && ft_strchr(FLAGS, format[i]))
			{
				fl = get_flag_width_precision(format, fl, &i);
				i++;
			}
			handle_types(format[i++], &len, args, fl);
			if (len == -1)								//<- appinha
				return (-1);							// <- appinha
		}
	}
	va_end(args);
	return (len);
}


//int main (void)
//{


	//categoria -s
	// printf("\n\n");
	// int len1, len2;
	// len1 = printf(" %-1s %-2s ", "", "-");
	// len2 = printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	// printf("\nlen   printf: %i %i\n", len1, len2);

	// int len11, len22;
	// len11 = ft_printf(" %-1s %-2s ", "", "-");
	// len22 = ft_printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	// printf("\nlen ft_printf: %i %i\n\n\n\n", len11, len22);

	//categoria -p
/*  printf("\n\n");
	int len3, len4;
	len3 = printf(" %-4p ", 17);
	len4 = printf(" %-9p %-10p ", LONG_MIN, LONG_MAX);
	printf("\nlen   printf: %i %i\n", len3, len4);

	int len33, len44;
	len33 = ft_printf(" %-4p ", 17);
	len44 = ft_printf(" %-9p %-10p ", LONG_MIN, LONG_MAX);
	printf("\nlen ft_printf: %i %i\n\n\n\n", len33, len44);

*/

//	printf("\n\n");
//int len4;
//	int len1, len2, len3, len4;
//	len1 = printf(" %04d ", 9);
//	len2 = printf(" %03d ", 15);
//	len3 = printf(" %04d ", 16);
//	len4 = printf(" %05d ", 17);
//	printf("\nlen   printf %i\n", len4);

//	printf("\nlen   printf %i %i %i %i\n", len1, len2, len3, len4);
//	printf("\n\n");
//int len44;
//	int len11, len22, len33, len44;
//	len11 = ft_printf(" %04d ", 9);
//	len22 = ft_printf(" %03d ", 15);
//	len33 = ft_printf(" %04d ", 16);
//	len44 = ft_printf(" %05d ", 17);
//	printf("\nlen   printf %i\n", len44);

//	printf("\nlen ft_printf %i %i %i %i\n\n\n", len11, len22, len33, len44);

//	return (0);
//}



/*
//int len2;
	int len1, len2, len3, len4, len5, len6, len7, len8, len9;
	len1 = printf("%-1c", '0');
	len2 = printf(" %-2c ", '0');	//	0 + espaço
	len3 = printf(" %-3c", '0' - 256);
	len4 = printf("%-4c ", '0' + 256);
	len5 = printf(" %-1c %-2c %-3c ", '0', 0, '1');
	len6 = printf(" %-1c %-2c %-3c ", ' ', ' ', ' ');
	len7 = printf(" %-1c %-2c %-3c ", '1', '2', '3');
	len8 = printf(" %-1c %-2c %-3c ", '2', '1', 0);
	len9 = printf(" %-1c %-2c %-3c ", 0, '1', '2');
//	printf("  printf len %i", len2);
	printf("\n\nlen    printf: %i %i %i %i %i %i %i %i", len1, len2, len3, len4, len5, len6, len7, len8);

	printf("\n\n");
//int len22;	
	int len11, len22, len33, len44, len55, len66, len77, len88, len99;
	len11 = ft_printf("%-1c", '0');
	len22 = ft_printf(" %-2c ", '0');
	len33 = ft_printf(" %-3c", '0' - 256);
	len44 = ft_printf("%-4c ", '0' + 256);
	len55 = ft_printf(" %-1c %-2c %-3c ", '0', 0, '1');
	len66 = ft_printf(" %-1c %-2c %-3c ", ' ', ' ', ' ');
	len77 = ft_printf(" %-1c %-2c %-3c ", '1', '2', '3');
	len88 = ft_printf(" %-1c %-2c %-3c ", '2', '1', 0);
	len99 = printf(" %-1c %-2c %-3c ", 0, '1', '2');
	//printf("ft_printf len %i\n\n\n", len22);
	printf("\n\nlen ft_printf: %i %i %i %i %i %i %i %i\n\n\n\n\n\n\n", len11, len22, len33, len44, len55, len66, len77, len88);
*/

/*	int len1 = printf(" %-2c ", '0');
	printf("\nlen printf %i\n", len1);

	int len2 = printf(" %-3c \n", '0' - 256);
	printf("len prinf %i\n", len2);

	printf("\nft_printf: \n");
	int lena = ft_printf(" %-2c ", '0');
	printf("\nlen ft_printf %i\n", lena);

	int lenb = printf(" %-3c \n", '0' - 256);
	printf("len ft_printf %i\n", lenb);
*/
/*
	printf("--------------------2\n");
	printf(" %-s \n", "-");
	printf(" %-1s %-2s \n", "", "-");
	printf("\nft_printf: \n");
	ft_printf(" %-s \n", "-");
	ft_printf(" %-1s %-2s \n", "", "-");

	printf("--------------------3\n");
	printf(" %-4p \n", 17);
	printf(" %-9p %-10p \n", LONG_MIN, LONG_MAX);	
	printf("\nft_printf: \n");
	ft_printf(" %-4p \n", 17);
	ft_printf(" %-9p %-10p \n", LONG_MIN, LONG_MAX);	


	printf("--------------------4\n");
	printf(" %-1d \n", 99);
	printf(" %-2d \n", 100);
	printf(" %-3d \n", 101);
	printf(" %-1d \n", -9);
	printf("\nft_printf: \n");
	ft_printf(" %-1d \n", 99);
	ft_printf(" %-2d \n", 100);
	ft_printf(" %-3d \n", 101);
	ft_printf(" %-1d \n", -9);

	printf("--------------------5\n");
	printf(" %-3i \n", 101);
	printf(" %-1i \n", -9);
	printf("\nft_printf: \n");
	ft_printf(" %-3i \n", 101);
	ft_printf(" %-1i \n", -9);

	printf("--------------------6\n");
	printf(" %-11i \n", LONG_MAX);
	printf(" %-12i \n", LONG_MIN);
	printf("\nft_printf: \n");
	ft_printf(" %-11i \n", LONG_MAX);
	ft_printf(" %-12i \n", LONG_MIN);

	printf("--------------------7\n");
	printf(" %-3u \n", 101);
	printf(" %-1u \n", -9);
	printf("\nft_printf: \n");
	ft_printf(" %-3u \n", 101);
	ft_printf(" %-1u \n", -9);
*/
//    return (0);
//}

/*
	int len = ft_printf("%p\n", -1);
	ft_printf("\n%i", len);
    int len = ft_printf("%s", NULL);
    printf("\n%i\n", len); 
*/
/*	printf("casos precisão-size: imprime zeros + imprime string\n");	
	printf("%.5i---------------\n", 42);
	ft_printf("%.5i\n", 42);
*/
/*	ft_printf(" %p \n", -1);
	ft_printf(" %p \n", 1);
	ft_printf(" %p \n", 15);
	ft_printf(" %p \n", 16);
	ft_printf(" %p \n", 17);

ft_printf("Bla %.2ii bla %.5isbla bla %.ix bla %.i", 127, 42, 1023, 0);
*/
//Bla 127i bla 00042sbla bla 1023x bla % appinha

//Bla 127i bla 42sbla bla 3ff bla %      nosso  


//	return (0);
//}


/*
int main(void)
{
	printf(" %p \n", 1);
	printf(" %p \n", 15);

	ft_printf(" %p \n", 1);
	ft_printf(" %p \n", 15);
*/
/*
	ft_printf(" %p ", -1);  

	//printf("%s\n", );
    //ft_printf(NULL);
   //ft_printf("%s", NULL);

}
*/


/*
void print_sizes(int printf_len, int ft_printf_len)
{
    if (printf_len != ft_printf_len)
        printf("Diff KO: diferent sizes. Expected %i, but got %i\n", printf_len, ft_printf_len);
    else
        printf("Diff OK: equal sizes. Expected %i, got %i\n", printf_len, ft_printf_len);
}
*/

//int main (void)
//{

  //  ft_printf("%x", 0);
/*
    int printf_len = printf("%s\n", "Vila 26");
    int ft_printf_len = ft_printf("%s\n", "Vila 26");
    print_sizes(printf_len, ft_printf_len);
*/
/*	
	int len = printf("%s","Hello\n");
    printf("%i\n", len);

	int len1 = ft_printf("%s","Hello\n");
    ft_printf("%i\n", len1);

	int len2 = printf("%s","Hello Vila 26\n");
    printf("%i\n", len2);

	int len3 = ft_printf("%s", "Hello Vila 26\n");
    ft_printf("%i\n\n\n\n", len3);
*/	
/*	// TESTES DE x E X
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
*/
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
/*	// TESTES DE PONTEIRO
	char    *string = "Hello";
	printf("----------TESTES DE PONTEIRO SEM FLAG - E SEM OPÇÃO 0--------\n");
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

/*	printf(".............................................\n\n\n\n");
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


	// TESTES DE INT E D

	// TESTES SEM FLAG - //
/*	printf("CASOS COM ZERO ANTES DO WIDTH E SEM FLAG '-'\n");
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

	
	//TESTES DE STRING
/*	printf("\nimpressão sem flags:\n\n");

	int len;
	len = printf("Vila 26");
	printf("printf len: %i\n", len);
	
	len = 0;
	len = ft_printf("Vila 26");
	ft_printf("ft_printf len: %i\n", len);
*/
/*
	printf("\nsem a flag '-':\n\n");

	printf("%s\n", "Vila 26");
	ft_printf("%s\n", "Vila 26");

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
/*	
	//TESTES DE CHAR
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
