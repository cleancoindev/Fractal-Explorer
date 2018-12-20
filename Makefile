OBJECTS=GLMath.o float3.o double3.o mat4.o dmat4.o Quaternion.o Shaders.o OpenGL.o
OUT=test
CC=g++
STATIC=

make: main.cpp $(OBJECTS)
	$(CC) $(STATIC) -o $(OUT) -std=c++11 -O2 main.cpp $(OBJECTS) -lGLEW -lGLU -lSOIL -lglut -lGL

clean:
	rm *.o $(OUT)

OpenGL.o: OpenGL.cpp
	$(CC) -c -o OpenGL.o --std=c++11 -O2 OpenGL.cpp

GLMath.o: GLMath.cpp
	$(CC) -c -o GLMath.o --std=c++11 -O2 GLMath.cpp

float3.o: float3.cpp
	$(CC) -c -o float3.o --std=c++11 -O2 float3.cpp

double3.o: double3.cpp
	$(CC) -c -o double3.o --std=c++11 -O2 double3.cpp

mat4.o: mat4.cpp
	$(CC) -c -o mat4.o --std=c++11 -O2 mat4.cpp

dmat4.o: dmat4.cpp
	$(CC) -c -o dmat4.o --std=c++11 -O2 dmat4.cpp

Quaternion.o: Quaternion.cpp
	$(CC) -c -o Quaternion.o --std=c++11 -O2 Quaternion.cpp

Shaders.o: Shaders.cpp
	$(CC) -c -o Shaders.o --std=c++11 -O2 Shaders.cpp
