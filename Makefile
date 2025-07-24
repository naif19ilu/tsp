objs = main.o cxa.o
flags = -Wall -Wextra -Wpedantic
final = tsp

$(final): $(objs)
	cc	-o $(final) $(objs)
%.o: %.c
	cc	-c $< $(flags)
clean:
	rm	-rf $(objs) $(final) && clear
