/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 09:32:51 by azamario          #+#    #+#             */
/*   Updated: 2021/08/07 09:57:50 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_for_plus_and_space_i_d(t_flags fl, int *len)
{
	if (fl.plus == 1)
		ft_putchar_len('+', len);
	else if (fl.space == 1 && fl.plus == 0)
		ft_putchar_len(' ', len);
}

void	basic_output_check_hash_xX(t_flags fl, int *len, const char c)
{
	if (fl.hash == 1 && c == 'X' && fl.ulli != 0)
	{
		ft_putstr_len("0X", len);
		ft_putstr_len(fl.strNum, len);
	}
	else if (fl.hash == 1 && c == 'x' && fl.ulli != 0)
	{
		ft_putstr_len("0x", len);
		ft_putstr_len(fl.strNum, len);
	}
	else
		ft_putstr_len(fl.strNum, len);
}