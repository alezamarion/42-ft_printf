# Printf42
This is a printf function recoded, with limited specifiers and flags. Because putnbr and putstr arenโt enough!

## Use:

๐ง project:<br/>
```
42Libft $ make
```
๐ฟ Clean Obj files:<br/>
```
42Libft $ make clean
```
๐ฟ ๐ฟ Clean All (obj files + binary):<br/>
```
42Libft $ make fclean
```
๐ฟ ๐ฟ ๐ง Clean All + build:<br/>
```
42Libft $ make re
```

<br/>See Makefile<br/>
<h2><b>Logic</b></h2>

Basically, this printf works on demand. It goes through the string and, at each step, prints the character found. (Like a char machine gun - the char found is printed and counted).
If printf finds the formatting character <b>'%'</b>, it stores the formatting instructions (the flags) in a structure to later format the output according to the stored flags.

Below, a ft_printf's logic:
<br>

![ft_print.png](info/ft_printf.png)
<br>

