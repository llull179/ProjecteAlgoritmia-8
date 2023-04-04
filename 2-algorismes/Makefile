TARGET: program

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: program.cc difussionGraph.hh Greedy.hh

OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
