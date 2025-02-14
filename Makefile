VERSION = 1.0
CXX = g++

LIBS = -lSDL2 -lSDL2_image

SRC = key_sun.cpp
TARGET = key_sun

mouse_sun: $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(LIBS)

clean :
	rm $(TARGET)

install: mouse_sun
