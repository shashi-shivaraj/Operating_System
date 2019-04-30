CXX = gcc

# Warnings frequently signal eventual errors:
CXXFLAGS = -g -W -Wall

LDFLAGS =

OBJS = \
	fscheck.o 
	
EXEC = fscheck

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) -I ./

fscheck.o: fscheck.c

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
