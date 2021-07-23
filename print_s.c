/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:05:51 by azamario          #+#    #+#             */
/*   Updated: 2021/07/23 15:32:42 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_s(char *c, int *len, t_flags fl)
{
	int size;

	size = (int)ft_strlen(c);
	if ((fl.precision == 0 && fl.width == 0) || (fl.precision >= size && fl.width <= size))
		ft_putstr_len(c, len); 
	else if (fl.precision < size && (fl.width == 0 || fl.width < size))
		while (fl.precision > 0)
		{
			write(1, &*c, 1);
			fl.precision--, len++, c++;				
		}
	else if ((fl.precision == 0 || fl.precision >= size) && fl.width > size ) //imprime espaços + string
		print_s_space_print(c, len, fl);
	else if (fl.precision < size && fl.width >= size) //imprime espaços + corta string
		print_s_space_cut(c, len, fl);
}

void	print_s_space_print(char *c, int *len, t_flags fl)
{
	int size;

	size = (int)ft_strlen(c);
	if (fl.minus == 0)
	{
		while (fl.width > size)
		{
			write(1, " ", 1);
			fl.width--, len++;
		}
		ft_putstr_len(c, len);
	}
	else
	{
		ft_putstr_len(c, len);
		while (fl.width > size)
		{
			write(1, " ", 1);
			fl.width--, len++;
		}
	}
}

void	print_s_space_cut(char *c, int *len, t_flags fl)
{
	int size;

	size = (int)ft_strlen(c);
	if(fl.minus == 0)
		print_s_space_cut_right(c, len, fl);
	else
		print_s_space_cut_left(c, len, fl);
}

void	print_s_space_cut_right(char *c, int *len, t_flags fl)
{
	while (fl.width - fl.precision > 0)
	{
		write(1, " ", 1);
		fl.width--, len++;
	}
	while (fl.precision > 0)
	{
		write(1, &*c, 1);
		fl.precision--, len++, c++;				
	}
}

void	print_s_space_cut_left(char *c, int *len, t_flags fl)
{
	while (fl.precision > 0)
	{
		write(1, &*c, 1);
		fl.precision--, len++, c++;				
	}
	while (fl.width - fl.precision > 0)
	{
		write(1, " ", 1);
		fl.width--, len++;
	}
}
