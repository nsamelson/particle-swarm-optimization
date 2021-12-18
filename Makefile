# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall

# The build target 
TARGET = build /app

#NEW
app: build/main.o build/ball.o build/Particles.o build/Perlin.o
	$(CC) $(CFLAGS) -o app build/main.o build/ball.o build/Particles.o build/Perlin.o -lraylib

build/main.o: main.cpp #Ball.h
	$(CC) $(CFLAGS) -c -o build/main.o main.cpp

build/ball.o: src/Ball.cpp src/Ball.h
	$(CC) -c -o build/ball.o src/Ball.cpp 

build/Particles.o: src/Particles.cpp src/Particles.h
	$(CC) -c -o build/Particles.o src/Particles.cpp 

build/Perlin.o: src/Perlin.cpp src/Perlin.h
	$(CC) -c -o build/Perlin.o src/Perlin.cpp

clean:
	rm -f *.o

mrproper: clean
	rm -f app