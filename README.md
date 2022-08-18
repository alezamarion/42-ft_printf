# Printf42
This is a printf function recoded, with limited specifiers and flags. Because putnbr and putstr aren’t enough!

Basically, this printf works on demand. It goes through the string and, at each step, prints the character found. (Like a char machine gun - the char found is printed and counted).
If printf finds the formatting character <b>'%'</b>, it stores the formatting instructions (the flags) in a structure to later format the output according to the stored flags.

Below, a ft_printf's logic:
<br>

![ft_print.png](info/ft_printf.png)
<br>

ft_printf42 é um projeto para recodificar o printf em C da libc. Ele irá gerenciar as seguintes conversões: cspdiuxX% !
Gerenciar qualquer combinação dos seguintes sinalizadores: '-0.' e largura mínima do campocom todas as conversões.
Gerenciar todos os seguintes sinalizadores: '# +' (sim, um deles é um espaço).
Entregando os arquivos: * .c, * / *. c, * .h, * / *. h, Makefile.

ft_printf42 is a project to recode printf in C from libc.  It will manage the following conversions: cspdiuxX% !  Handle any combination of the following flags: '-0.'  and minimum field width with all conversions.  Manage all of the following flags: '#+' (yes, one of them is a space).  Delivering the files: * .c, * / *.  c, * .h, * / *.  h, Makefile. <br/>

## Badge

<img src="ft_printf.png">

## SKills

 - Rigor
 - Algorithms & AI

 ## My grade

 <img src="score printf.png"> 

## Use:

🚧 project:
```
ft_printf42 $ make bonus
```
Compile your main with the library:
```
clang main.c libftprintf.a
```
:shower: Clean Obj files:<br/>
```
$ make clean
```
:shower: :shower: Clean All (obj files + binary):<br/>
```
$ make fclean
```
:shower: :shower: 🚧 Clean All + build:<br/>
```
$ make re
```
<br/>See Makefile<br/>

### Made with: <br/>

### Alexandre Zamarion
<div style="display: inline_block">
 <a href="https://github.com/alezamarion" target="_blank"><img align="center" alt="Github_Jorge" height="30" width="30" src="https://cdn-icons-png.flaticon.com/128/1051/1051275.png" target="_blank"></a>
 <a href="https://www.linkedin.com/in/alexandre-zamarion-cepeda-a3766323a/" target="_blank"><img align="center"src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white" target="_blank"></a> 
</div>

### Jorge Alves
<div style="display: inline_block">
 <a href="https://github.com/jorgeedualves/jorgeedualves" target="_blank"><img align="center" alt="Github_Jorge" height="30" width="30" src="https://cdn-icons-png.flaticon.com/128/1051/1051275.png" target="_blank"></a>
 <a href="https://www.linkedin.com/in/jorge-eduardo-alves-094b4331/" target="_blank"><img align="center"src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white" target="_blank"></a> 
</div>

### Alfredo Neto
<div style="display: inline_block">
 <a href="https://github.com/Alfredo-Neto" target="_blank"><img align="center" alt="Github_Jorge" height="30" width="30" src="https://cdn-icons-png.flaticon.com/128/1051/1051275.png" target="_blank"></a>
 <a href="https://www.linkedin.com/in/alfredo-neto-a2515814b/" target="_blank"><img align="center"src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white" target="_blank"></a> 
</div>
