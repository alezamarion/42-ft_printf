/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/08/02 20:51:19 by azamario         ###   ########.fr       */
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
	else if (format[*i] == '0' && fl.minus == 0 && fl.width == 0 && fl.dot == 0)
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
			ft_putchar_len(format[i++], &len);
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
			if (len == -1)
				return (-1);
		}
	}
	va_end(args);
	return (len);
}


/*
int main (void)
{
	printf("\n\n");
   printf("%.0xis a big number", 0);
	printf("\n");
   printf("the number is %.x", 0);
 	printf("\n");
    printf("%x%.5x%.0x%.x%.9x", 5, 55, 2, 0, 42);

	printf("\n\n");
 
   ft_printf("%.0xis a big number", 0);
	printf("\n");
   ft_printf("the number is %.x", 0);
 	printf("\n");
    ft_printf("%x%.5x%.0x%.x%.9x", 5, 55, 2, 0, 42);

	printf("\n\n");


}
*/


/*
int main (void)
{

   printf("%.0u", 0);
   printf("%.u", 0); 

	printf("\n\n");

   ft_printf("%.0u", 0);
   ft_printf("%.u", 0); 


  	printf("%.0uis a big number", (unsigned int)-1);
		printf("\n");
   	printf("the number is %.u", (unsigned int)-1);
		printf("\n");
	printf("%u%.5u%.0u%.u%.9u", 5, 55, 2, 0, 42);

		printf("\n\n");
 
  	ft_printf("%.0uis a big number", (unsigned int)-1);
 		printf("\n");
   	ft_printf("the number is %.u", (unsigned int)-1);
		printf("\n");
   	ft_printf("%u%.5u%.0u%.u%.9u", 5, 55, 2, 0, 42);
	printf("\n\n");

}

*/

/*
int main (void)
{
	printf("\n\n");
 
   printf("%.0u", 0);
 	printf("\n");
   printf("%.u", 0);
	printf("\n");
   printf("%.0uis a big number", 0);
 	printf("\n");
   printf("%u%.5u%.0u%.u%.9u", 5, 55, 2, 0, 42);

	printf("\n\n");

   ft_printf("%.0u", 0);
 	printf("\n");
   ft_printf("%.u", 0);
	printf("\n");
   ft_printf("%.0uis a big number", 0);
 	printf("\n");
   ft_printf("%u%.5u%.0u%.u%.9u", 5, 55, 2, 0, 42);

	printf("\n\n");

} 
*/
/*
int main(void)
{
	int len1, len2;
	len1 = printf("%-1d", 0);
	printf("\n");
	len2 = ft_printf("%-1d", 0);
	printf("printf: %i, ft_: %i", len1, len2);
}
*/
/*
int main (void)
{
	printf("\n");
 												printf("%10d", 42);
 	printf("\n"); 
//    printf("%20d", -42000);
// 	printf("\n");
												printf("wait for it... %50d", 42);
	printf("\n");
   												printf("%30d", 2147483647);
 	printf("\n");
//    printf("%12d", (int)-2147483648);
//  	printf("\n");
//    printf("%12d, %20d, %2d, %42d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%12d, %d, %2d, %42d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%14d%20d%2d%d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%20d is how many tests are going to be made", 8000);
// 	printf("\n");


	printf("\n");
 												ft_printf("%10d", 42);
 	printf("\n"); 
//    printf("%20d", -42000);
// 	printf("\n");
												ft_printf("wait for it... %50d", 42);
	printf("\n");
   												ft_printf("%30d", 2147483647);
 	printf("\n");
//    printf("%12d", (int)-2147483648);
//  	printf("\n");
//    printf("%12d, %20d, %2d, %42d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%12d, %d, %2d, %42d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%14d%20d%2d%d", (int)-2147483648, 3, 30, -1);
// 	printf("\n");
//    printf("%20d is how many tests are going to be made", 8000);
// 	printf("\n");

}
*/





/*
int main (void)
{
	char *str = NULL;
	int len1, len2;
	printf("\n\n");
	   len1 = printf("%7s", str);
	   	printf("\n");
	   len2 = ft_printf("%7s", str);
	  printf("printf len %i, ft_ len: %i", len1, len2);
}
*/

/*
int main (void)
{
printf("\n\n");

	char *null_str = NULL;
	int len1, len2, len3, len4, len5, len6;
   len1 = printf("%1s", "a");
   len2 = printf("%3s", "-42");
   len3 = printf("%6s", null_str);
	printf("len    printf: %i %i %i", len1, len2, len3);
printf("\n\n");

   len4 = ft_printf("%1s", "a");
   len5 = ft_printf("%3s", "-42");
   len6 = ft_printf("%6s", null_str);
	printf("len ft_printf: %i %i %i", len4, len5, len6);


printf("\n\n");

}
*/
/*
int main (void)
{
	//TESTES DO PAULO ERRADOS: x e X

	int len1, len3, len5, len7;
	printf("\n\n");
	len1 = printf("%01.0x", 0);
//	len2 = printf("%03.0x", 0);
	len3 = printf("%042.2X", 42000);
//	len4 = printf("%0014.2X%020X%0002.X%000.5X", -1, 3, 30, -1);
	printf("len    printf: %i %i", len1, len3);
	printf("\n\n");

	len5 = ft_printf("%01.0x", 0);
//	len6 = ft_printf("%03.0x", 0);
	len7 = ft_printf("%042.2X", 42000);
//	len8 = ft_printf("%0014.2X%020X%0002.X%000.5X", -1, 3, 30, -1);
	printf("len ft_printf: %i %i", len5, len7);

	printf("\n\n");


}
*/
/*
int main(void)
{
	//	PAULO: TESTES MANDATÓRIOS ASSINALADOS COMO ERRADOS QUE ESTÃO CERTOS

	   printf("\n");
	int len1, len2, len3,len4, len5, len6;
	len1 = printf("%u", 0);
		printf("\n"); 
  	len2 = printf("%u to the power of %u is %u", 2, 32, (unsigned int)4294967295);
		printf("\n");
	len3 = printf("%u%u%u%u", (unsigned int)429896724, 0, 32, (unsigned int)4294967295);
		printf("\n");
	printf("len  printf: %i %i %i", len1, len2, len3);
		printf("\n");
   
   printf("\n");
   	len4 = ft_printf("%u", 0);
		printf("\n");
  	len5 = ft_printf("%u to the power of %u is %u", 2, 32, (unsigned int)4294967295);
 		printf("\n");
  	len6 = ft_printf("%u%u%u%u", (unsigned int)429896724, 0, 32, (unsigned int)4294967295);
		printf("\n");
	printf("len ft_printf: %i %i %i", len4, len5, len6);
	   printf("\n\n");

   return (0);
}
*/

/*
int main (void)
{
	//	s:

		printf("\n\n");
	int len1, len2, len11, len22;
	len1 = printf(" %-1s %-2s ", "", "-");
	len2 = printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	printf("\nlen printf: %i %i", len1, len2);
		printf("\n\n");
//	int len11, len22;
	len11 = ft_printf(" %-1s %-2s ", "", "-");
	len22 = ft_printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	printf("\nlen ft_printf: %i %i", len11, len22);
		printf("\n\n");

	return (0);
}

*/

/*
int main (void)
{
	//	d e i:
	printf("--------------------------------------------\n\n");

	int len1, len2, len3, len4, len5;
	len1 = printf(" %.2d ", -1);
	len2 = printf(" %.3d ", -11);
	len3 = printf(" %.4d ", -14);
	len4 = printf(" %.3d ", -99);
	len5 = printf(" %.4d ", -101);
	printf("\nlen printf: %i %i %i %i %i", len1, len2, len3, len4, len5);
	
	printf("\n\n");

	int len11, len22, len33, len44, len55;
	len11 = ft_printf(" %.2d ", -1);
	len22 = ft_printf(" %.3d ", -11);
	len33 = ft_printf(" %.4d ", -14);
	len44 = ft_printf(" %.3d ", -99);
	len55 = ft_printf(" %.4d ", -101);
	printf("\nlen printf: %i %i %i %i %i", len11, len22, len33, len44, len55);

	return (0);
}
*/
/*

	int len1, len2;
	len1 = printf(" %.10x ", LONG_MAX);
//	len2 = printf(" %.11x ", LONG_MIN);	
	printf("\nlen printf: %i",len1);
	printf("\n\n");			

	int len4, len5;
	len4 = ft_printf(" %.10x ", LONG_MAX);
	//len5 = ft_printf(" %.11x ", LONG_MIN);
	printf("\nlen ft_printf: %i",len4);
	printf("\n\n");			

*/
	//	categoria -
	//	erros em s, d e i:


	// len5 = printf(" %-9d ", INT_MAX);
	// len6 = printf(" %-10d ", INT_MIN);
	// len7 = printf(" %-11d ", LONG_MAX);
	// len8 = printf(" %-12d ", LONG_MIN);
	// len9 = printf(" %-13d ", UINT_MAX);
	// len10 = printf(" %-14d ", ULONG_MAX);
/*	printf("\nlen printf: %i %i %i %i", len1, len2, len3, len4);

		printf("\n\n");

	int len11, len22, len33, len44;
	len11 = ft_printf(" %-1d ", 0);
	len22 = ft_printf(" %-2d ", -1);
	len33 = ft_printf(" %-2d ", 11);
	len44 = ft_printf(" %-4d ", -14);
*///	len55 = ft_printf(" %-9d ", INT_MAX);
//	len66 = ft_printf(" %-10d ", INT_MIN);
//	len77 = ft_printf(" %-11d ", LONG_MAX);
	// len88 = ft_printf(" %-12d ", LONG_MIN);
	// len99 = ft_printf(" %-13d ", UINT_MAX);
	// len1010 = ft_printf(" %-14d ", ULONG_MAX);
//	printf("\nlen ft_printf: %i %i %i %i", len11, len22, len33, len44);
//		printf("\n\n");

//-----------------------------------------------------------------------------------------------------------------//

	//	categoria .
	//	erros em s, d, i, x e X:

	//	. s:
/*	int len1, len2;
	len1 = printf(" %.s ", "-");
	len2 = ft_printf(" %.s ", "-");
		printf("\n");
	printf("len printf: %i, len ft_printf: %i", len1, len2);
		printf("\n\n");
*/
/*
	//	. d e i:
		printf("\n\n");
	int len1, len2, len3, len4, len5, len6, len7, len8, len9, len10, len11, len12;
	len1 = printf(" %.2d ", -1);
	len2 = printf(" %.2d ", 1);
	len3 = printf(" %.4d ", 15);
	len4 = printf(" %.4d ", -14);
	len5 = printf(" %.3d ", -99);
	len6 = printf(" %.4d ", -101);
	len7 = printf(" %.10d ", LONG_MAX);
	len8 = printf(" %.11d ", LONG_MIN);
	len9 = printf(" %.12d ", UINT_MAX);
	len10 = printf(" %.13d ", ULONG_MAX);
	len11 = printf(" %.14d ", 9223372036854775807LL);
		printf("\n\n");
	len12 = printf(" %.8d %.9d %.10d %.11d %.12d %.13d %.14d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\nlen printf: %i %i %i %i %i %i %i %i %i %i %i %i", len1, len2, len3, len4, len5, len6, len7, len8, len9, len10, len11, len12);

	printf("\n\n");
	
	int len13, len14, len15, len16, len17, len18, len19, len20, len21, len22, len23, len24;
	len13 = ft_printf(" %.2d ", -1);
	len14 = ft_printf(" %.2d ", 1);
	len15 = ft_printf(" %.4d ", 15);
	len16 = ft_printf(" %.4d ", -14);
	len17 = ft_printf(" %.3d ", -99);
	len18 = ft_printf(" %.4d ", -101);
	len19 = ft_printf(" %.10d ", LONG_MAX);
	len20 = ft_printf(" %.11d ", LONG_MIN);
	len21 = ft_printf(" %.12d ", UINT_MAX);
	len22 = ft_printf(" %.13d ", ULONG_MAX);
	len23 = ft_printf(" %.14d ", 9223372036854775807LL);
		printf("\n\n");
	len24 = ft_printf(" %.8d %.9d %.10d %.11d %.12d %.13d %.14d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\nlen ft_printf: %i %i %i %i %i %i %i %i %i %i %i %i", len13, len14, len15, len16, len17, len18, len19, len20, len21, len22, len23, len24);
		printf("\n\n");
*/
/*
	//	. x e X:
	int len1, len2, len3, len4, len5, len6, len7, len8, len9, len10, len11;
	len1 = printf(" %.2x ", 1);
	len2 = printf(" %.1x ", 9);
	len3 = printf(" %.6x ", 17);
	len4 = printf(" %.3x ", 101);
	len5 = printf(" %.9x ", INT_MIN);
	len6 = printf(" %.10x ", LONG_MAX);
	len7 = printf(" %.11x ", LONG_MIN);
	len8 = printf(" %.12x ", UINT_MAX);
	len9 = printf(" %.13x ", ULONG_MAX);
	len10 = printf(" %.14x ", 9223372036854775807LL);
		printf("\n\n");
	len11 = printf(" %.8x %.9x %.10x %.11x %.12x %.13x %.14x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\n\nlen printf: %i %i %i %i %i %i %i %i %i %i %i", len1, len2, len3, len4, len5, len6, len7, len8, len9, len10, len11);

		printf("\n\n");

	int len13, len14, len15, len16, len17, len18, len19, len20, len21, len22, len23;
	len13 = ft_printf(" %.2x ", 1);
	len14 = ft_printf(" %.1x ", 9);
	len15 = ft_printf(" %.6x ", 17);
	len16 = ft_printf(" %.3x ", 101);
	len17 = ft_printf(" %.9x ", INT_MIN);
	len18 = ft_printf(" %.10x ", LONG_MAX);
	len19 = ft_printf(" %.11x ", LONG_MIN);
	len20 = ft_printf(" %.12x ", UINT_MAX);
	len21 = ft_printf(" %.13x ", ULONG_MAX);
	len22 = ft_printf(" %.14x ", 9223372036854775807LL);
		printf("\n\n");
	len23 = ft_printf(" %.8x %.9x %.10x %.11x %.12x %.13x %.14x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\n\nlen ft_printf: %i %i %i %i %i %i %i %i %i %i %i", len13, len14, len15, len16, len17, len18, len19, len20, len21, len22, len23);

*/
//	return (0);
//}

//-----------------------------------------------------------------------------------------------------------------//



	/*
	int len1, len2, len3, len4;
	len1 = printf(" %-1d ", 0);
	len2 = printf(" %-2d ", -1);
	len3 = printf(" %-2d ", 11);
	len4 = printf(" %-3d ", -11);
	printf("\nlen   printf: %i %i %i %i\n", len1, len2, len3, len4);

	printf("\n");

	int len11, len22, len33, len44;
	len11 = ft_printf(" %-1d ", 0);
	len22 = ft_printf(" %-2d ", -1);
	len33 = ft_printf(" %-2d ", 11);
	len44 = ft_printf(" %-3d ", -11);
	printf("\nlen ft_printf: %i %i %i %i\n", len11, len22, len33, len44);


		printf(" %.s ", "-");
		printf("\n-----------\n");
		ft_printf(" %.s ", "-");





	// TEST(51, print(" %-9d ", INT_MAX));
	// TEST(52, print(" %-10d ", INT_MIN));
	// TEST(53, print(" %-11d ", LONG_MAX));
	// TEST(54, print(" %-12d ", LONG_MIN));
	// TEST(55, print(" %-13d ", UINT_MAX));
	// TEST(56, print(" %-14d ", ULONG_MAX));



//	printf("\n\n");
//int len3;
	//int len1, len2, len3;
	//len1 = printf(" %04d ", 9);
	//len2 = printf(" %05d ", -15);
//	len3 = printf(" %012d ", INT_MIN);
//	printf("\nlen   printf %i \n", len3);
	
//	printf("\n\n");
//int len33;
//	int len11, len22, len33;
//	len11 = ft_printf(" %04d ", 9);
//	len22= ft_printf(" %05d ", -15);
//	len33 = ft_printf(" %012d ", INT_MIN);
//	printf("\nlen ft_printf %i\n\n\n", len33);
*/
/*
	//categoria -s
	printf("\n\n");
	int len1;
	len1 = printf(" %-1s %-2s ", "", "-");
//	len2 = printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	printf("\nlen   printf: %i \n", len1);

	int len11;
	len11 = ft_printf(" %-1s %-2s ", "", "-");
//	len22 = ft_printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", "");
	printf("\nlen ft_printf: %i \n\n\n\n", len11);

*/	//categoria -p

// 	return (0);
// }



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
