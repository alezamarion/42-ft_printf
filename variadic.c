/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:54:24 by azamario          #+#    #+#             */
/*   Updated: 2021/07/02 13:59:10 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
variaric funcion reduces code, it's a single function that processes variable number of arguments
We typically use variadic function when we don’t know the total number of arguments that will be used for a function
Basically one single function could potentially have n number of arguments

example:
int add(int args, ...); stdarg.h
first param = fixed number of arguments, second param = the variable number of arguments

add(3, 1, 2, 3) = 6
add(6, 20, 20, 20, 10, 20, 10) = 100

Important steps:
1 - include stdarg.h to get necessary things to implement variadic functons
2 - define function prototipe:
    first argument: fixed parameter
    second argument: elipses (...) -> indicates to the compiler that function accepts variable number of arguments
3 - define a va_list variable
4 - begin and end argument list with va_start and va_end (va = variable): macros that recognize where argument list starts and ends

Code below:
a - first param = fixed number of arguments, second param = the variable number of arguments
b - type va_list is used for argument pointer variables, it points to first optional argument
c - va_start: this macro initializes the argument pointer variable ap to point to the first of the optional arguments of the current function
    You access the optional arguments by successive calls to va_arg. The first call to va_arg gives you the first optional argument, 
    the next call gives you the second, and so on.
d - The va_arg macro returns the value of the next optional argument, and modifies the value of ap to point to the subsequent argument. 
    Thus, successive uses of va_arg return successive optional arguments.
e - This ends the use of ap. After a va_end call, further va_arg calls with the same ap may not work. You should invoke va_end 
    before returning from the function in which va_start was invoked with the same ap argument.
f - after final of argument list, we have our return

libc manual: variadic functions
https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html
*/


#include <stdarg.h>
#include <stdio.h>

int add(int args, ...)              //a
{             
    va_list ap;                     //b
    
    va_start(ap, args);             //c
  
    int i = 0;
    int sum = 0;

    for (i = 0; i < args; i++)
        sum += va_arg(ap, int);     //d 
                                        
    va_end(ap);                     //e
    return (sum);                   //f 
}

int main(void)
{
    printf("Add1 = %i\n", add(3, 1, 2, 3));
    printf("Add2 = %i\n", add(6, 20, 20, 20, 10, 10, 20));

    return (0);
}

/*
Output:
Add1 = 6
Add2 = 100
*/

/*
More explanations from https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html

Sometimes it is necessary to parse the list of parameters more than once or one wants to remember a certain position in the parameter list. 
To do this, one will have to make a copy of the current value of the argument. But va_list is an opaque type and one cannot necessarily 
assign the value of one variable of type va_list to another variable of the same type.

Macro: void va_copy (va_list dest, va_list src)
Macro: void __va_copy (va_list dest, va_list src)

The va_copy macro allows copying of objects of type va_list even if this is not an integral type. The argument pointer in dest is initialized 
to point to the same argument as the pointer in src.

va_copy was added in ISO C99. When building for strict conformance to ISO C90 (‘gcc -std=c90’), it is not available. 
GCC provides __va_copy, as an extension, in any standards mode; before GCC 3.0, it was the only macro for this functionality.

These macros are no longer provided by the GNU C Library, but rather by the compiler.

If you want to use va_copy and be portable to pre-C99 systems, you should always be prepared for the possibility that this macro 
will not be available. On architectures where a simple assignment is invalid, hopefully va_copy will be available, so one should always 
write something like this if concerned about pre-C99 portability:

{
  va_list ap, save;
  …
#ifdef va_copy
  va_copy (save, ap);
#else
  save = ap;
#endif
  …
}
*/