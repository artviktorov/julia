CXX = g++
CXXFLAGS = -std=c++20 -Wall

TARGET = build
SRC = julia_hsv.cpp
OUTPUT_IMG = img.ppm

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) && open $(OUTPUT_IMG)

clean:
	rm -f $(TARGET) $(OUTPUT_IMG)

rebuild: clean all
