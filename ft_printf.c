/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:00 by azamario          #+#    #+#             */
/*   Updated: 2021/07/13 23:21:55 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void handle_types(int *len, va_list args, t_flags fl)
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
    // write(1, &print_c, 1);
    // if (fl.type == 'x')
    //    print_c  = va_arg(args, char *);
    // write(1, &print_c, 1);
    // if (fl.type == 'X')
    //    print_c  = va_arg(args, char *);
    // write(1, &print_c, 1);
    // if (fl.type == '%')
    //    print_c  = va_arg(args, char *);
    // write(1, &print_c, 1);
}

static void get_specs(const char *format, int  *i, int *len, va_list args) {
    t_flags fl;
    if (ft_strchr_01(CONVERSIONS, format[*i]))
    {
         fl.type = format[(*i)++];
         handle_types(len, args, fl);
    }    
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int len;
    int i;

    va_start(args, format);
    len = 0;
    i = 0;
    while (format[i] != '\0')
    {
        if (format[i] != '%')
            ft_putchar_len(format[i++], &len); // tamanho = hello %-s, name // 7
        else
        {
            i++;
            get_specs(format, &i, &len, args);
            if (len == -1)
				return (-1); // %[flags][width][.precision][size]type -> "hello" "    hello"
        }
    }
    va_end(args);
    return(len);
}

int main (void)
{
    //char c = 'u';
    char *s = "Vila 26 bombando";
    char *t = "Será que o pointer tá bacana?";
    //int in = 42;
    //int dec = 42;
    //unsigned int ui = -300;

    //ft_printf("\nchar: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n\n", c, s, in, dec, ui);
    //printf("\nchar: %c, string: %s, int: %i, decimal: %d, unsigned: %u\n\n", c, s, in, dec, ui);
    printf("   printf: %p\n", &s);
    ft_printf("ft_printf: %p\n", &s);

    printf("   printf: %p\n", &t);
    ft_printf("ft_printf: %p\n", &t);

    return (0);
}
