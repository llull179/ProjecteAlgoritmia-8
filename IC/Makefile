TARGET: program

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: program.cc IC_difussionGraph.hh

OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
