NAME = FRACTOL

CC = clang
FLAG = -glldb -g3
INC = -I ./inc -I ./my_stdlib/header
LIB = ./my_stdlib/my_stdlib.a
LIBDIR = ./my_stdlib
FRAMEWORK_PATH = -F/Library/Frameworks
FRAMEWORK = -framework SDL2

all: obj
	make -C $(LIBDIR)
	$(CC) $(FLAG) obj/main.o \
	obj/render.o \
	obj/init.o \
	obj/mandelbrot.o \
	 -o $(NAME) -glldb -fsanitize=address -g3 $(LIB) $(FRAMEWORK_PATH) $(FRAMEWORK)
	@echo "\033[0;32mFactorial compiled : \033[0m\033[31m$(NAME)\033[0m"	

obj:
	mkdir obj
	$(CC) $(FLAG) -c src/main.c -o obj/main.o $(INC) $(FRAMEWORK_PATH)
	$(CC) $(FLAG) -c src/render.c -o obj/render.o $(INC) $(FRAMEWORK_PATH)
	$(CC) $(FLAG) -c src/init.c -o obj/init.o $(INC) $(FRAMEWORK_PATH)
	$(CC) $(FLAG) -c src/mandelbrot.c -o obj/mandelbrot.o $(INC) $(FRAMEWORK_PATH)

clean:
	rm -fr obj/*.o
	rm -fr obj

fclean: clean
	rm -fr $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: re
	lldb -- ./$(NAME)