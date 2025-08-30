CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = motorbike_rental_new
SOURCES = main.cpp ui.cpp auth.cpp booking.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
