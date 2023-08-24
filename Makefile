CC = c++ -std=c++23 -o

example: 
	$(CC) example example.cpp

clean:
	rm example
