TARGET: SA

COMPILER: g++

FLAGS: -std=c++11 -Wall -Wextra

SRCS: SA.cc SA.hh difussionGraph.hh 
OBJS: $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
