CC = g++
OBJ = main.o

all: hello

hello: $(OBJ)
	$(CC) $(OBJ) graph.h  -o lr3
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@
clean:
	rm lr3
	rm *.o

