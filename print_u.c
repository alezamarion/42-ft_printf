/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:11:44 by azamario          #+#    #+#             */
/*   Updated: 2021/08/06 14:26:16 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_u(t_flags fl, va_list args, int *len)
{
	int	size;
	unsigned int number;
	int count;

	count = 0;
	number = va_arg(args, unsigned int);
	fl.strNum = ft_uitoa(number);
	size = (int)ft_strlen(fl.strNum);
	if (number == 0 && fl.dot == 1 && fl.precision == 0)
		print_zero_corner_cases(fl, size, len);
	else if (fl.zero == 1 && fl.width > size && fl.precision == 0)
		print_zero_string_u(fl, len, size);
	else if (fl.width > size && fl.precision <= size)
		print_space_string_u(fl, len, size);
	else if (fl.precision > size)
		print_corner_cases_u(fl, size, len, &count);
	else
		ft_putstr_len(fl.strNum, len);
	free(fl.strNum);
}

void	print_zero_corner_cases(t_flags fl, int size, int *len)
{
	int count;

	count = 0;
	if (fl.width > fl.precision)
		print_corner_cases_width_precision_u(fl, len, &count);
	else if (fl.precision > fl. width)
			print_precision_zero_u(fl, len);
	else if (fl.width > size)
		print_width_bigger_than_size_u(fl, len);
	else if (fl.precision > size)
	{
		while (fl.precision > 1)
		{		
			write(1, "0", 1);
			fl.precision--, (*len)++;		
		}
		ft_putstr_len(fl.strNum, len);
	}	
	else
		write(1, " ", 0);
}


void	print_space_string_u(t_flags fl, int *len, int size)
{
	if (fl.minus == 1)
	{
		ft_putstr_len(fl.strNum, len);
		print_space(fl, size, len);
	}
	else
	{
		print_space(fl, size, len);
		ft_putstr_len(fl.strNum, len);
	}
}

void	print_zero_string_u(t_flags fl, int *len, int size)
{	
	if (fl.minus == 0)
	{
		while (fl.width - size > 0)
		{
			write(1, "0", 1);
			fl.width--, (*len)++;
		}
		ft_putstr_len(fl.strNum, len);
	}
	else if (fl.minus == 1)
	{
		ft_putstr_len(fl.strNum, len);
		print_space(fl, size, len);
	}
}

int	ft_ulen(unsigned int num)
{
	size_t	len;

	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*result;

	len = ft_ulen(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (0);
	result[len] = '\0';
	len--;
	while (len >= 0)
	{
		result[len] = '0' + (n % 10);
		n = n / 10;
		len--;
	}
	return (result);
}

void	print_zero_precision_u(t_flags fl, int size, int *len)
{
	while (fl.precision - size > 0)
	{
		write(1, "0", 1);
		fl.precision--, (*len)++;
	}
	ft_putstr_len(fl.strNum, len);

}

void	print_corner_cases_u(t_flags fl, int size, int *len, int *count)
{
	if (fl.width > size && fl.minus == 1)
	{
		print_zero_precision_u(fl, size, len);
		while (fl.width - (fl.precision + *count) > 0)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
	}
	else if (fl.minus == 0 && fl.width > fl.precision)
	{
		while (fl.width - fl.precision > 0)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
		print_zero_precision_u(fl, size, len);
	}
	else
		print_zero_precision_u(fl, size, len);
}

void	print_width_space_u(t_flags fl, int *len)
{
	while (fl.width > 1)
	{
		write(1, " ", 1);
		fl.width--, (*len)++;		
	}
}

void	print_precision_zero_u(t_flags fl, int *len)
{
	while (fl.precision > 0)
	{
		write(1, "0", 1);
		fl.precision--, (*len)++;	
	}	
}

void	print_corner_cases_width_precision_u(t_flags fl, int *len, int *count)\
{
	if (fl.minus == 1)
	{
		while (fl.precision > 0)
		{
			write(1, "0", 1);
			fl.precision--, (*len)++, count++;
		}
		while (fl.width - (fl.precision + *count) > 0)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
	}
	else if (fl.minus == 0)
	{
		while (fl.width > fl.precision)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
		print_precision_zero_u(fl, len);
	}
}

void	print_width_bigger_than_size_u(t_flags fl, int *len)
{
	if (fl.dot == 1)
		print_width_space_u(fl, len);
	else if (fl.zero == 0 || fl.minus == 1)
	{
		print_width_space_u(fl, len);
		ft_putstr_len(fl.strNum, len);
	}
	else
	{
		while (fl.width > 1)
		{
			write(1, "0", 1);
			fl.width--, (*len)++;		
		}
		ft_putstr_len(fl.strNum, len);
	}
}