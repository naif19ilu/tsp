objs = main.o cxa.o fatal.o lexer.o
flags = -Wall -Wextra -Wpedantic
final = tsp

$(final): $(objs)
	cc	-o $(final) $(objs)
%.o: %.c
	cc	-c $< $(flags)
clean:
	rm	-rf $(objs) $(final) && clear
