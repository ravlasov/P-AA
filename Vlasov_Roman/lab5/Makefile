CC = g++
OBJ = main.o

all: hello

hello: $(OBJ)
	$(CC) $(OBJ) pattern_search_tree.h -o lr5
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@
clean:
	rm lr5
	rm *.o

