/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:24:14 by azamario          #+#    #+#             */
/*   Updated: 2021/07/21 22:17:35 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "stdlib.h"
# include "string.h"
# define CONVERSIONS	"cspdiuxX%"
# define FLAGS			"-0.0123456789"
# define ALL_FLAGS		"-0.0123456789cspdiuxX%"
# define NUMBERS		"0123456789"


typedef struct t_flags
{
	int		minus;
	int		zero;
	int		width;
	int		dot;
	int		precision;
	char	type;
	char	*strNum;
}	t_flags;

int		ft_printf(const char *format, ...);
void	ft_putchar_len(char c, int *len);
int		ft_strchr(char *s, char c);
size_t	ft_strlen(const char *s);
void	ft_putstr(char *s);
void	ft_putchar(char c);
void	ft_putnbr(int n);
char	*ft_itoa(int n);
void	ft_putstr_len(char *s, int *len);
void	print_s(char *c, int *len, t_flags fl);
void	print_i_d(t_flags fl, va_list args, int *len);
void	print_u(t_flags fl, va_list args, int *len);
char	*ft_uitoa(unsigned int n);
int		ft_ulen(unsigned int num);
void	print_c(char c, int *len, t_flags fl);
void	print_p(t_flags fl, va_list args, int *len);
char	*ft_int_to_hex_pxX(unsigned long int n, t_flags fl);
void	ft_putstr_len_p(char *s, int *len);
int		ft_len_hex(unsigned long int x);
void	print_x(t_flags fl, va_list args, int *len);
void	print_X(t_flags fl, va_list args, int *len);
void	print_pct(int *len);
void	print_s_space_print(char *c, int *len, t_flags fl);
void	print_s_space_cut(char *c, int *len, t_flags fl);
void	print_s_space_cut_right(char *c, int *len, t_flags fl);
void	print_s_space_cut_left(char *c, int *len, t_flags fl);

void 	print_s_space(t_flags fl, int size, int *len);
void 	print_s_zero(t_flags fl, int size, int *len);


t_flags	ft_clean_flags(void);

#endif
