TARGET: program_SA program_Greedy program_localSearch

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: program_SA.cc SA.hh program_Greedy.cc Greedy.hh program_localSearch.cc LocalSearch.hh difussionGraph.hh 
OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	-rm program_SA program_Greedy program_localSearch output*
