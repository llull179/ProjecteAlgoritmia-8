TARGET: program program_localSeach

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: program.cc program_localSeach.cc difussionGraph.hh Greedy.hh LocalSearch.hh

OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
