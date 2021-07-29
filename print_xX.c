/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:17:05 by azamario          #+#    #+#             */
/*   Updated: 2021/07/29 18:28:20 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    print_xX(t_flags fl, va_list args, int *len, const char c)
{
    int    size;
		fl.ulli = va_arg(args, unsigned int);		
    if (c == 'X')
        fl.strNum = ft_ullitoa_base(fl.ulli, HEXAUPP);
    else if (c == 'x')
        fl.strNum = ft_ullitoa_base(fl.ulli, HEXALOW);
    size = (int)ft_strlen(fl.strNum);
    if (fl.minus == 0 && fl.width > size)
        print_xX_right_aligned(fl, len, size);
    else if (fl.minus == 1 && fl.width > size)
    {
        ft_putstr_len(fl.strNum, len);
        print_space(fl, size, len);
    }
    else
        ft_putstr_len(fl.strNum, len);
    free(fl.strNum);
}

int	return_hex_len(int num) //quem chama?
{
	int len;

	len  = 0;
	while (num)
	{
		num = num / 16;
		len++;
	}
	return (len);	
}

void	print_xX_right_aligned(t_flags fl, int *len, int size)
{
	if (fl.zero == 0)
	{
		print_space(fl, size, len);
		ft_putstr_len(fl.strNum, len);
	}
	if (fl.zero == 1)
	{
		while (fl.width - size > 0)
		{
			write(1, "0", 1);
			fl.width--, (*len)++;
		}
		ft_putstr_len(fl.strNum, len);
	}
}

int	ft_len_hex(unsigned long int x) //quem chama?
{
	int	len;

	len = 0;
	while (x)
	{
		x = x / 16;
		len++;
	}
	return (len);
}

char        *ft_ullitoa_base(unsigned long long int n, char *base)
{
    char                 	   *a;
    unsigned long long int 	   nbr;
    size_t                 	   size;
    int                        b_len;

    b_len = ft_strlen(base);
    nbr = n;
    size = 1;
    while (n /= b_len)
        size++;
    if (!(a = (char *)malloc(size + 1)))
        return (0);
    a[size--] = '\0';
    while (nbr > 0)
    {
        a[size--] = base[nbr % b_len];
        nbr /= b_len;
    }
    if (size == 0 && a[1] == '\0')
        a[0] = '0';
    return (a);
}
