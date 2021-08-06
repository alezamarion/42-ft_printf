/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:17:05 by azamario          #+#    #+#             */
/*   Updated: 2021/08/06 19:04:23 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_xX(t_flags fl, va_list args, int *len, const char c)
{
	int	size;

	fl.ulli = va_arg(args, unsigned int);
	if (c == 'X')
		fl.strNum = ft_ullitoa_base(fl.ulli, HEXAUPP);
	else if (c == 'x')
		fl.strNum = ft_ullitoa_base(fl.ulli, HEXALOW);
	size = (int)ft_strlen(fl.strNum);
	if (fl.ulli == 0 && fl.dot == 1 && fl.precision == 0)
		print_zero_corner_cases(fl, size, len);
	else if ((fl.width == 0 || fl.width <= size)
		&& (fl.precision == 0 || fl.precision <= size))
		ft_putstr_len(fl.strNum, len);
	else if ((fl.width == 0 || fl.width <= size) && (fl.precision > size))
		print_precision_zero_i_d(fl, size, len);
	else if (fl.width > size && (fl.precision == 0 || fl.precision <= size))
		print_regular_cases_xX(fl, size, len);
	else if (fl.width > size && fl.precision > size)
		print_corner_cases_xX(fl, size, len);
	free(fl.strNum);
}

int	ft_len_hex(unsigned long int x)
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

char	*ft_ullitoa_base(unsigned long long int n, char *base)
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
	a = (char *)malloc(size + 1);
    if (!a)
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

void	print_corner_cases_xX(t_flags fl, int size, int *len)
{
	int	i;

	i = 0;
	if (fl.minus == 1)
	{
		if (fl.width == fl.precision)
			print_precision_zero_i_d(fl, size, len);
		else if (fl.width > fl.precision)
		{
			print_precision_zero_i_d(fl, size, len);
			while (fl.width - (fl.precision + i) > 0)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
		}
		else
			print_precision_zero_i_d(fl, size, len);
	}
	else
	{
		print_simple_space_width_precision_i_d(fl, len);
		print_precision_zero_i_d(fl, size, len);
	}
}

void	print_regular_cases_xX(t_flags fl, int size, int *len)
{	
	if (fl.minus == 1)
	{
		ft_putstr_len(fl.strNum, len);
		print_simple_space_i_d(fl, size, len);
	}
	else if (fl.zero == 0 || (fl.zero == 1 && fl.dot == 1))
	{
		print_simple_space_i_d(fl, size, len);
		ft_putstr_len(fl.strNum, len);
	}
	else
	{
		print_simple_zero_xX(fl, size, len);
		ft_putstr_len(fl.strNum, len);
	}
}
