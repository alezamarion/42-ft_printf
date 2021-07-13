/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:23:34 by azamario          #+#    #+#             */
/*   Updated: 2021/07/12 13:13:06 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h> 
#include <stdarg.h>						

char *convert(unsigned int num, int base) 					//Converte integer para octal, hex, etc.
{ 
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 
	
	ptr = &buffer[49]; 
	*ptr = '\0'; 
	
	do 
	{ 
		*--ptr = Representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	
	return(ptr); 
}


void Myprintf(char* format,...) 						//printf function
{ 
	char *traverse; 
	unsigned int i; 
	char *s; 
	
	//Module 1: Initializing Myprintf's arguments 
	va_list arg; 
	va_start(arg, format); 
	
	for(traverse = format; *traverse != '\0'; traverse++)  //primeiro ele imprime tudo até o %, depois avança para depois da %
	{ 
		while( *traverse != '%' ) 
		{ 
			putchar(*traverse);
			traverse++; 
		} 

		traverse++; 
		
		//Module 2: Fetching and executing arguments -> aqui o cara lida com as formatações, alguns dos casos que a gente tem que lidar
		switch(*traverse) 
		{ 
			case 'c' : i = va_arg(arg,int);			//Fetch char argument
						putchar(i);
						break; 
						
			case 'd' : i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
						if(i < 0) 
						{ 
							i = -i;
							putchar('-'); 
						} 
						puts(convert(i,10));
						break; 
						
			case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
						puts(convert(i,8));
						break; 
						
			case 's': s = va_arg(arg,char *); 		//Fetch string
						puts(s); 
						break; 
						
			case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
						puts(convert(i,16));
						break; 
		}	
	} 
	
	//Module 3: Closing argument list to necessary clean-up
	va_end(arg); 
} 


int main() 
{ 
	Myprintf(" WWW.FIRMCODES.COM \n %d", 9); 
	
	return 0;
} 
*/


#include <stdarg.h>
#include <unistd.h>

#define FLAGS "-0.*0123456789"

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (c % 256))
		s++;
	if (*s == (c % 256))
		return ((char *)s);
	return (0);
}

typedef struct	flag
{
	int	align;
	int zero;
	int dot;
	int star;
}				flag;

//flag check_flags();

//int join_flags_types_and_print();


int ft_printf(const char *format, ...)
{
    va_list arguments;
    int     num_printed_char;
	flag flags;
    num_printed_char = 0;
    va_start(arguments, format);
    while (*format)
    {
        if (*format != '%')
        {
            ft_putchar(*format);
            num_printed_char++;
            format++;
        }
        while(*format == '%')/*
            *format++;
            while(*format && ft_strchr(FLAGS, *format))
            	flags = check_flags();
			num_printed_char = num_printed_char + join_flags_types_and_print(); */
    } 
    va_end(arguments);
    return(num_printed_char);
}

int main(void)
{
    ft_printf("Hello World!");
}

//trabalhar só com os tipos
