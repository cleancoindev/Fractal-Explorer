OBJECTS=GLMath.o float3.o double3.o mat4.o dmat4.o Quaternion.o Shaders.o OpenGL.o
OUT=test

make: main.cpp $(OBJECTS)
	g++ -o $(OUT) -std=c++11 -O2 main.cpp $(OBJECTS) -lGLEW -lGLU -lglut -lGL -lSOIL

clean:
	rm *.o
	rm $(OUT)

OpenGL.o: OpenGL.cpp
	g++ -c -o OpenGL.o --std=c++11 -O2 OpenGL.cpp

GLMath.o: GLMath.cpp
	g++ -c -o GLMath.o --std=c++11 -O2 GLMath.cpp

float3.o: float3.cpp
	g++ -c -o float3.o --std=c++11 -O2 float3.cpp

double3.o: double3.cpp
	g++ -c -o double3.o --std=c++11 -O2 double3.cpp

mat4.o: mat4.cpp
	g++ -c -o mat4.o --std=c++11 -O2 mat4.cpp

dmat4.o: dmat4.cpp
	g++ -c -o dmat4.o --std=c++11 -O2 dmat4.cpp

Quaternion.o: Quaternion.cpp
	g++ -c -o Quaternion.o --std=c++11 -O2 Quaternion.cpp

Shaders.o: Shaders.cpp
	g++ -c -o Shaders.o --std=c++11 -O2 Shaders.cpp
