CC = g++
OBJ = main.o

all: hello

hello: $(OBJ)
	$(CC) $(OBJ)  -o lr4
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@
clean:
	rm lr4
	rm *.o

