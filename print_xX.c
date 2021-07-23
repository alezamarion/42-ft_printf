/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:17:05 by azamario          #+#    #+#             */
/*   Updated: 2021/07/23 15:22:18 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_x(t_flags fl, va_list args, int *len)
{
	int size;																						
																									
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	size = (int)ft_strlen(fl.strNum);																
	if (fl.minus == 0 && fl.width > size)
	{
		if (fl.zero == 0)
		{
			print_s_space(fl, size, len);		
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
	else if (fl.minus == 1 && fl.width > size)
	{
		ft_putstr_len(fl.strNum, len);		
			print_s_space(fl, size, len);		
	}
	else
		ft_putstr_len(fl.strNum, len);		
}

void	print_X(t_flags fl, va_list args, int *len)
{
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	ft_putstr_len(fl.strNum, len);
}