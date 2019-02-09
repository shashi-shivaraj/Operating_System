CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -std=c++11 -W -Wall -Weffc++ -Wextra -O0

OBJS = \
	virtual_address.o
EXEC = run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

virtual_address.o: virtual_address.cpp

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
