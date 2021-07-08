
/*

PRINTF = "print formatted"

A função:
pega a entrada (o que foi colocado na função) + argumentos opcionais se existirem
e produz uma sequência formatada de caracteres como output

a entrada pode conter zero ou mais diretivas:
 
    - zero diretivas --> simplesmente imprime o que foi fornecido
    Exemplo: printf("Hello World") --> output é: Hello World

    - outras diretivas: especificações de conversão que descrevem como formatar o que foi colocado na função
    especificações de conversão:
    % [flags] [width] [. precision] [size] type

Cada campo da especificação de conversão é um caractere ou um número que significa uma opção de formato particular 

O campo "type" é obrigatório e especifica o tipo de conversão a ser aplicado a um argumento - ex: para integer (%i) ou char (%c) 

Os campos opcionais "flags", "width", "precision", "size" controlam aspectos de formato adicionais, como espaços ou zeros à esquerda,
justificação e precisão exibida. 

Para esta tarefa:
"It will manage the following conversions: cspdiuxX%"
Temos que gerenciar as seguintes conversões:
    c - Character:      specifies a single-byte character (char)
    s - String:         specifies a single-byte or multi-byte character string; (char*)
    p - Pointer:    	Display the argument as an address in hexadecimal digits
    d - Integer:        Signed decimal integer
    i - Integer:    	Signed decimal integer
    u - Integer:    	Unsigned decimal integer
    x - Integer:    	Unsigned hexadecimal integer; uses "abcdef"
    X - Integer:    	Unsigned hexadecimal integer; uses "ABCDEF"
    %                   A '%' is written. No argument is converted. The complete conversion specification is '%%'.

Para esta tarefa:
"It will manage any combination of the following flags: ’-0.*’ and minimum fieldwidth with all conversions"                     
Temos que gerenciar os seguintes sinalizadores:
    - (alinhar)         Alinha o resultado à esquerda dentro da largura de campo fornecida. O padrão é alinhamento à direita.
    0 (preenchimento)   Quando a opção 'largura' é especificada, zeros precedem os tipos numéricos. O padrão adiciona espaços
                        Por exemplo, printf ("%4i", 3) produz:   3, enquanto printf ("%04i", 3) produz: 0003
                        Padrão: sem preenchimento.
    . (precisão)        Consiste em um ponto (.) seguido por um número inteiro decimal não negativo que, dependendo do tipo de conversão,
                        especifica o número de caracteres da string, o número de casas decimais ou o número de dígitos a serem impressos.
                        Ao contrário da especificação de largura, a especificação de precisão pode causar corte do valor de saída ou arredondamento 
                        do valor de um float.
                        Como os valores de precisão afetam os tipos da nossa tarefa:
                        c - Char: sem efeito
                        s - String: especifica o número máximo de caracteres a serem impressos. Os caracteres com excesso de precisão não são impressos. 
                            Padrão: os caracteres são impressos até que um caractere nulo seja encontrado.
                        p - Ponteiro: ? acho que não tem efeito sobre ponteiro
                        d, i, u, x, X - Inteiro: A precisão especifica o número mínimo de dígitos a serem impressos.
                                        Se o número de dígitos a serem impressos pela função for menor que a precisão,
                                        o valor de saída é preenchido à esquerda com zeros.
                                        O valor não é cortado quando o número de dígitos
                                        excede a precisão. Padrão: a precisão é 1
    * (asterisco)       Pode substituir especificações de sinalizadores
                        Por exemplo, printf("%*d", 5, 10) resultará na impressão de:     10, com uma largura total de 5 caracteres.
                        É a mesma coisa que escrever: printf("%5d", 10)
                        Por exemplo, printf("%.*s", 3, "abcdef") resultará na impressão de: abc.
                        É a mesma coisa que escrever: printf("%.3s", "abcdef");

*/

/*
Esse exemplo abaixo é de um protótipo que funciona, e como é mais simples, pode servir de base pra gente estudar.
Nessa função, o cara lida com a primeira parte da nossa tarefa: a conversão para char, decimal ou integer, string, etc

http://www.firmcodes.com/write-printf-function-c/

dá um  "gcc notas_printf.c" e depois executa pra dar uma olhada
*/


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

