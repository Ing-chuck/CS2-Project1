

####### Compiler, tools and options

CXX           = g++
CXXFLAGS      = -std=gnu++11 -Wall
DEL_FILE      = rm -f

####### Files

SOURCES       = main.cpp \
		troop.cpp \
		point.cpp 
OBJECTS       = main.o \
		troop.o \
		point.o

TARGET        = main

####### Build rules

$(TARGET):  $(OBJECTS)  
	$(CXX) -o $(TARGET) $(OBJECTS) 

clean: 
	$(DEL_FILE) $(OBJECTS)

####### Compile

main.o: main.cpp troop.h point.h
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp

troop.o: troop.cpp troop.h point.h
	$(CXX) -c $(CXXFLAGS) -o troop.o troop.cpp

point.o: point.cpp point.h
	$(CXX) -c $(CXXFLAGS) -o point.o point.cpp

