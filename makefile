#build an executable named hello from hello.c
all : hello.c
	gcc -g -Wall -o hello hello.c
clean:
	$(RM) hello
