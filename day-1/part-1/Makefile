all:		trebuchet trebuchet.c
		@echo "Compiling: trebuchet.c"
		@gcc -Wall -Werror -Wextra -fsanitize=address -g3 trebuchet.c -o trebuchet

clean:
		@rm -rf trebuchet

fclean:		clean

re:			fclean all