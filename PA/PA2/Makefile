CPPFLAGS = -std=c++11 -g 
SRCS = main.cpp animal.cpp board.cpp entity.cpp helper.cpp grass.cpp sheep.cpp wolf.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: PA2.exe

PA2.exe: $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f *.o *.exe *.d
#	del *.o *.exe *.d
zip:
	zip PA2.zip grass.cpp animal.cpp sheep.cpp wolf.cpp
# On Windows, use: del *.o *.exe *.d
# On Linux or MacOS, use: rm -f *.o *.exe *.d

.PRECIOUS: $(OBJS)