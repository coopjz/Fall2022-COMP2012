CPPFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -g -fsanitize=address
OBJECTS = main.o system.o

all: lab2

lab2: $(OBJECTS)
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clean:
	rm  -f  *.o *.exe
