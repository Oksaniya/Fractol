NAME = FRACTOL

CC = gcc
FLAG = -glldb -g3
INC = -I ./inc -I ./SDL ./my_stdlib
LIB = ./SDL/SDL.a ./my_stdlib/my_stdlib.a
LIBDIR = ./SDL ./my_stdlib

all: obj
	make -C $(LIBDIR)
	$(CC) obj/main.o \
	obj/fcact.o \
	 -o fcact -glldb -fsanitize=address -g3 $(LIB)
	@echo "\033[0;32mFactorial compiled : \033[0m\033[31m$(NAME)\033[0m"	

obj:
	mkdir obj
	$(CC) $(FLAG) -c src/main.c -o obj/main.o $(INC)
	$(CC) $(FLAG) -c src/fcact.c -o obj/fcact.o $(INC)

clean:
	rm -fr obj/*.o
	rm -fr obj

fclean: clean
	rm -fr $(NAME)

re: fclean all

run: re
	./$(NAME) ./Example1.txt

debug: re
	lldb -- ./$(NAME)