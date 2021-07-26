/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:07:45 by azamario          #+#    #+#             */
/*   Updated: 2021/07/24 22:35:47 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_i_d(t_flags fl, va_list args, int *len)
{
	int	size;

	fl.strNum = ft_itoa(va_arg(args, int));
	size = (int)ft_strlen(fl.strNum);
	if (fl.width <= size && fl.precision <= size)
		ft_putstr_len(fl.strNum, len);
	if (fl.precision > size)
	{
		print_i_d_zero(fl, size, len);
		ft_putstr_len(fl.strNum, len);
	}
	if (fl.width > size && fl.precision <= size)
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
	free(fl.strNum);	
}

void	print_space(t_flags fl, int size, int *len)
{
	while (fl.width - size > 0)
	{
		write(1, " ", 1);
		fl.width--, len++;
	}
}

void	print_i_d_zero(t_flags fl, int size, int *len)
{
	while (fl.precision - size > 0)
	{
		write(1, "0", 1);
		fl.precision--, len++;
	}
}
