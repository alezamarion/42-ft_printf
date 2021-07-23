/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:29:59 by azamario          #+#    #+#             */
/*   Updated: 2021/07/23 12:32:29 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.c"

void		print_c(char c, int *len, t_flags fl)
{
	if (fl.minus == 0 && fl.width == 0)
	{
		ft_putchar_len(c, len);	
	}
	else if (fl.minus == 0 && fl. width > 0)
	{
		while (fl.width-- > 1)
		{
			write(1, " ", 1);
			len++;
		}
		ft_putchar_len(c, len);
	}
	else if (fl.minus == 1)
	{
		ft_putchar_len(c, len);
		while (fl.width-- > 1)
		{
			write(1, " ", 1);
			len++;
		}
	}
}
