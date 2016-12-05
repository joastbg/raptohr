# Define the compiler options
# Define the compiler options
CXXFLAGS  = -pipe -O2 -Wall -W -ansi #-pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast -pthread -msse4.1 
CC = g++

# Define what to do when make is executed without arguments.
all: raptohr
	g++ -o raptohr options.o runner.o raptohr.o 

raptohr: raptohr.o options.o runner.o

# Define the rules for the object files.
raptohr.o: raptohr.cc
	$(CXX) -c raptohr.cc $(CXXFLAGS)
		
runner.o: runner.cc
	$(CXX) -c runner.cc $(CXXFLAGS) 
		
options.o: options.cc
	$(CXX) -c options.cc $(CXXFLAGS) 
		
clean:
	rm -rf *o raptohr
				
run:
	./raptohr						
runa:
	./raptohr --conf raptohr.conf