CXX = gcc

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -W -Wall -Wextra -pedantic -O0

OBJS = \
	./src/main.o

EXEC = run

# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# $@ - targets ;  $^ - dependencies of target

%.o: %.cpp # pattern for target (object file) : dependencies (source code)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
