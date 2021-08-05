/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:07:45 by azamario          #+#    #+#             */
/*   Updated: 2021/08/05 15:42:00 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_i_d(t_flags fl, va_list args, int *len) 
{
	int number;
	int size;

	size = 0;
	number = va_arg(args, int);
	if (number == 0 && fl.dot == 1 && fl.precision == 0)
	{
		fl.strNum = ft_itoa(number);
		size = (int)ft_strlen(fl.strNum);
		print_zero_corner_case(fl, len, size);
		free(fl.strNum);
	}
	else if (number >= 0)
		print_id_positive(fl, number, len);
	else
	{
		number *= -1;
		print_id_negative(fl, number, len);
	}	
}

void	print_id_positive(t_flags fl, int number, int *len)
{
	int size;

	fl.strNum = ft_itoa(number);
	size = (int)ft_strlen(fl.strNum);
	if (size == 0 && fl.dot == 1 && fl.precision == 0)
		print_zero_corner_case(fl, len, size);
    if ((fl.width == 0 || fl.width <= size) && (fl.precision  > size))
  	{
		while (fl.precision - size > 0)
		{
			write(1, "0", 1);
			fl.precision--, (*len)++;
		}
		ft_putstr_len(fl.strNum, len);
	}
    else if (fl.width > size && (fl.precision == 0 || fl.precision <= size))   
    {
        if (fl.minus == 1)
        {
 	    	ft_putstr_len(fl.strNum, len);
   		   	while (fl.width - size > 0)
		    {
		  		write(1, " ", 1);
		    	fl.width--, (*len)++;
	    	}
        }
		else if (fl.zero == 0 || (fl.zero == 1 && fl.dot == 1))
		{ 	       					
   	  		while (fl.width - size > 0)
	    	{
		   		write(1, " ", 1);
		    	fl.width--, (*len)++;
	    	}
	    	ft_putstr_len(fl.strNum, len);
     	}
      	else
		{
	    	while (fl.width - size > 0)
	    	{
		    	write(1, "0", 1);
		    	fl.width--, (*len)++;
	    	}
	   		ft_putstr_len(fl.strNum, len);      
		}
	}
    else if (fl.width > size && fl.precision > size)
    {
		int i;

		i = 0;
		if (fl.minus == 1)
		{
			if (fl.width == fl.precision)
			{
 	  			while (fl.precision - size > 0)
 				{
				    write(1, "0", 1);
				    fl.precision--, (*len)++;
				}
				ft_putstr_len(fl.strNum, len);
			}
			else if (fl.width > fl.precision)
			{
 	  			while (fl.precision - size > 0)
 				{
				    write(1, "0", 1);
				    fl.precision--, (*len)++, i++;
				}
				ft_putstr_len(fl.strNum, len);
 				while (fl.width - (fl.precision + i) > 0)
				{
					write(1, " ", 1);
					fl.width--, (*len)++;
				}
			}
			else
			{
 	  			while (fl.precision - size > 0)
 				{
				    write(1, "0", 1);
				    fl.precision--, (*len)++;
				}
				ft_putstr_len(fl.strNum, len);
			}
		}
		else
		{
 			while (fl.width - fl.precision > 0)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
  			while (fl.precision - size > 0)
			{
			    write(1, "0", 1);
			    fl.precision--, (*len)++;
	    	}
	    	ft_putstr_len(fl.strNum, len);
		}
    }
	else
		ft_putstr_len(fl.strNum, len);

    free(fl.strNum);
}

void	print_id_negative(t_flags fl, int number, int *len)
{
	int size;
	if (number == -2147483648)
		fl.strNum = "2147483648";
	else
		fl.strNum = ft_itoa(number);
	size = (int)ft_strlen(fl.strNum) + 1;
	if (fl.width <= size && fl.precision < size)
	{
		ft_putchar_len('-', len);
		ft_putstr_len(fl.strNum, len);
	}
	else if (fl.precision > size -1 && fl.width < size)
	{
		ft_putchar_len('-', len);
		while (fl.precision - (size - 1) > 0)
		{
			write(1, "0", 1);
			fl.precision--, (*len)++;
		}
		ft_putstr_len(fl.strNum, len);
	}
	else if ((fl.width > size || fl.width == 0) && (fl.precision == 0 || fl.precision > size) && fl.zero == 1)
	{
		if (fl.width > fl.precision && fl.dot == 1)
		{
			while (fl.width - (fl.precision + 1) > 0)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
			ft_putchar_len('-', len);
			while (fl.precision - (size - 1) > 0)
			{
				write(1, "0", 1);
				fl.precision--, (*len)++;
			}
			ft_putstr_len(fl.strNum, len);
		}
		else if (fl.width == fl.precision && fl.dot == 1)
		{
			ft_putchar_len('-', len);
			while (fl.width - (size - 1) > 0)
			{
				write(1, "0", 1);
				fl.width--, (*len)++;
			}
			ft_putstr_len(fl.strNum, len);
		}
		else if (fl.width < fl.precision && fl.dot == 1)
		{
			ft_putchar_len('-', len);
			while (fl.precision - (size - 1) > 0)
			{
				write(1, "0", 1);
				fl.precision--, (*len)++;
			}
			ft_putstr_len(fl.strNum, len);
		}
		else
		{
			ft_putchar_len('-', len);
			print_i_d_zero(fl, size, len);
			ft_putstr_len(fl.strNum, len);
		}
	}
	else if ((fl.width > size && fl.precision != 0) && fl.precision <= size )
	{
		if (fl.minus == 1 && fl.precision < size)
		{
			ft_putchar_len('-', len);
			ft_putstr_len(fl.strNum, len);
			while (fl.width - size > 0)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
		}
		else if (fl.minus == 1 && fl.precision == size)
		{
			ft_putchar_len('-', len);
			while (fl.precision > size - 1)
			{
				write(1, "0", 1);
				fl.precision--, (*len)++;
			}
			ft_putstr_len(fl.strNum, len);
			while (fl.width - size > 1)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
		}
		else if (fl.minus == 1 && fl.precision >= size)
		{
			ft_putchar_len('-', len);
			while (fl.precision > size - 1)
			{
				write(1, "0", 1);
				fl.precision--, (*len)++;
			}
			ft_putstr_len(fl.strNum, len);
			while (fl.width - (size - 1) > 0)
			{
				write(1, " ", 1);
				fl.width--, (*len)++;
			}
		}
		else
		{
			print_space(fl, size, len);
			ft_putchar_len('-', len);
			ft_putstr_len(fl.strNum, len);
		}
	}
	else if (fl.minus == 1 && fl.precision == 0 && fl.width > size)
	{
		ft_putchar_len('-', len);
		ft_putstr_len(fl.strNum, len);
		print_space(fl, size, len);
	}
	else if (fl.minus == 0 && fl.width > size && fl.dot == 0)
	{
		print_space(fl, size, len);		
		ft_putchar_len('-', len);
		ft_putstr_len(fl.strNum, len);
	}
	else if (fl.width == fl.precision)
	{
		ft_putchar_len('-', len);
		while (fl.width - (size - 1) > 0)
		{
			write(1, "0", 1);
			fl.width--, (*len)++;
		}
		ft_putstr_len(fl.strNum, len);
	}
	if (number != -2147483648)
		free(fl.strNum);
}

void	print_space(t_flags fl, int size, int *len)
{
	if (fl.precision > 0 && fl.width > size)
	{
		while (fl.width - size > 0)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
	}
	else if (fl.precision > 0)
	{
		while (fl.precision - size > 0)
		{
			write(1, "0", 1);
			fl.precision--, (*len)++;
		}
	}
	else
	{
		while (fl.width - size > 0)
		{
			write(1, " ", 1);
			fl.width--, (*len)++;
		}
	}
}

void	print_i_d_zero(t_flags fl, int size, int *len)
{
	if (fl.precision > 0)
	{
		while (fl.precision - size > 0)
		{
			write(1, "0", 1);
			fl.precision--, (*len)++;
		}
	}
	else
	{		
		while (fl.width - size > 0)
		{
			write(1, "0", 1);
			fl.width--, (*len)++;
		}
	}
}
