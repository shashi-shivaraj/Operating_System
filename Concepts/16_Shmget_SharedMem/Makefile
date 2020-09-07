CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -std=c++11 -W -Wall -Weffc++ -Wextra -O0

READ_OBJS = \
       ./src/shared_mem.o\
	   ./src/readshmem.o

WRITE_OBJS = \
       ./src/shared_mem.o\
	   ./src/writeshmem.o

READ_EXEC = read
WRITE_EXEC = write

all: read write

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I ./inc

read: $(READ_OBJS)
	$(CXX) $(CXXFLAGS) -o $(READ_EXEC) $(READ_OBJS) $(LDFLAGS)

shared_mem.o: shared_mem.cpp
readshmem.o: readshmem.cpp

write: $(WRITE_OBJS)
	$(CXX) $(CXXFLAGS) -o $(WRITE_EXEC) $(WRITE_OBJS) $(LDFLAGS)

shared_mem.o: shared_mem.cpp
readshmem.o: readshmem.cpp  

clean:
	rm -rf $(READ_OBJS)
	rm -rf $(READ_EXEC)
	rm -rf $(WRITE_OBJS)
	rm -rf $(WRITE_EXEC)