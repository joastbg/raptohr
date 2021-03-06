# Define the compiler options
# Define the compiler options
CXXFLAGS  = -pipe -O3 -funroll-all-loops -Wall -W -ansi -std=gnu++11 -std=gnu++1y
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast -pthread -msse4.1 -lcrypto
CC  = g++

# Define what to do when make is executed without arguments.
all: raptohr
	g++ $(CXXFLAGS) -o raptohr options.o runner.o sha1.o complex.o matrix.o signal.o misc.o raptohr.o 

raptohr: raptohr.o options.o runner.o sha1.o complex.o matrix.o signal.o misc.o

# Define the rules for the object files.
raptohr.o: raptohr.cc
	$(CXX) -c raptohr.cc
		
runner.o: runner.cc
	$(CXX) -c runner.cc
		
options.o: options.cc
	$(CXX) -c options.cc
	
sha1.o: sha1.cc
	$(CXX) -c sha1.cc
	
complex.o: complex.cc
	$(CXX) -c complex.cc
	
matrix.o: matrix.cc
	$(CXX) -c matrix.cc

signal.o: signal.cc
	$(CXX) -c signal.cc

misc.o: misc.cc
	$(CXX) -c misc.cc
		
clean:
	rm -rf *o raptohr
				
run:
	./raptohr						
runa:
	./raptohr --conf raptohr.conf