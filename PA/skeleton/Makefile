CPPFLAGS = -std=c++11 -g -fsanitize=address -fsanitize=undefined
OBJECTS = course_database.o course.o main.o student_database.o student.o swap_list.o system.o wait_list.o

all: pa1

pa1: $(OBJECTS)
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clean:
	rm  -f  *.o *.exe