
#include <stdio.h>

void    function(str)
{
    printf("%p\n", &str);
    function(str);
}

int     main(void)
{

    char *str = "Hello World";
    printf("%p\n", &str);
    function(*str);
    
    return 0;
}