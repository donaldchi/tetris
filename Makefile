#!/bin/bash

CXX=g++ -std=c++11 -O3   
#CXX=g++ 
CFLAGS=  -O3 -Wall 
LDFLAGS= -lm -Wall 
ALL=tetrist
OBJ1= main_tetrist.o 
OBJ2= Tetrist.o

# all: $(ALL)
	# mv $(ALL).exe bin/

tetrist : obj/$(OBJ1) obj/$(OBJ2)
	$(CXX) -o $@ $^ $(LDFLAGS)

.HONY: install

# install: all
	# mv $(ALL).exe ../bin
	# mv *.o ../obj

##########################################
# Generic rules
##########################################

obj/%.o: src/%.cpp src/%.h
	$(CXX) -o $@ -c $< $(CFLAGS)

obj/%.o: src/%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(ALL) bin/* obj/*
