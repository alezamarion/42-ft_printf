/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:14:31 by azamario          #+#    #+#             */
/*   Updated: 2021/07/23 15:22:10 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_p(t_flags fl, va_list args, int *len)
{
	int size;																						
																									
	fl.strNum = ft_int_to_hex_pxX(va_arg(args, unsigned long int), fl);
	size = (int)ft_strlen(fl.strNum);																
	size = size + 2;
	if (fl.zero == 0 && fl.width > size)
	{
		if(fl.minus == 0)
		{
			print_s_space(fl, size, len);		
			ft_putstr_len_p(fl.strNum, len);
		}
		else if (fl.minus == 1)
		{
			ft_putstr_len_p(fl.strNum, len);
			print_s_space(fl, size, len);		
		}
	}
	else if (fl.zero == 1 && fl.width > size)
	{
		if (fl.minus == 0)
		{
			write(1, "0x", 2);
			while (fl.width - size > 0)
			{
				write(1, "0", 1);
				fl.width--, len++;
			}
			ft_putstr_len(fl.strNum, len);
		}
		else if (fl.minus == 1)
		{
			ft_putstr_len_p(fl.strNum, len);
			print_s_space(fl, size, len);		
		}
	}
	else
		ft_putstr_len_p(fl.strNum, len);
}