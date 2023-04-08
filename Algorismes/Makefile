TARGET: SA program program_localSearch

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: SA.cc SA.hh program.cc Greedy.hh program_localSearch.cc LocalSearch.hh difussionGraph.hh 
OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
