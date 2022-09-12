# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall -std=c++17 -pthread 
LFLAGS = -lstdc++fs
 
# The build target 
TARGET = test_timer
OBJECTS = App.o test_timer.o #clear.o
BUILD = build
PROJECT_OUTPUT = $(BUILD)/$(TARGET)

.PHONY: run
run: clean all
	./build/test_timer

all: $(OBJECTS) $(BUILD) 
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(PROJECT_OUTPUT)
	# g++ -std=c++17 -lstdc++fs test_timer.cpp -lstdc++fs  -o test_timer

# $(OBJECTS): %.o: %.cpp
$(OBJECTS): App.cpp  test_timer.cpp
	# $(CC) $(CFLAGS) -c clear.cpp -o clear.o
	$(CC) $(CFLAGS) -c App.cpp -o App.o
	$(CC) $(CFLAGS) -c test_timer.cpp -o test_timer.o


clean:
	$(RM) -rf $(BUILD) $(OBJECTS) 

$(BUILD):
	mkdir build