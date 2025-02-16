VERSION = 1.0
CXX = g++

LIBS = -lSDL2 -lSDL2_image

SRC = key-sun.cpp
TARGET = key-sun

key-sun: $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(LIBS)

clean :
	rm $(TARGET)

install: key-sun
