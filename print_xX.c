/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:17:05 by azamario          #+#    #+#             */
/*   Updated: 2021/07/24 21:41:52 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_xX(t_flags fl, va_list args, int *len, const char c)
{
	int	size;

	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), c);
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
			fl.width--, len++;
		}
		ft_putstr_len(fl.strNum, len);
	}
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

char	*ft_int_to_hex_pxX(unsigned long int n, const char c)
{
	int		len;
	char	*result;
	int		temp;

	len = ft_len_hex(n);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (0);
	result[len--] = '\0';
	while (len >= 0)
	{
		temp = 0;
		temp = n % 16;
		if (temp < 10)
			result[len--] = temp + 48;
		else
		{
			if (c == 'x' || c == 'p')
				result[len--] = temp + 87;
			else
				result[len--] = temp + 55;
		}
		n = n / 16;
	}
	return (result);
}
