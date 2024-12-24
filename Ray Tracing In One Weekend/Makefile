CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -Ofast
EXEC = raytracing
OBJECTS = main.o vec3.o ray.o hittable_list.o sphere.o interval.o camera.o lambertian.o metal.o dielectric.o
DEPENDS = ${OBJECTS:.o=.d}

.PHONY: all clean

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS} ${TEST_OBJECTS} ${DEPENDS} ${EXEC} ${TEST_EXEC}