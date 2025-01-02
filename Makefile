CXX = g++
CXXFLAGS = -std=c++20 -O2

TARGET = julia_hsv
SRC = julia_hsv.cpp
FRAMES = ./frames/frame_*.ppm
VIDEO = fractal_julia.mp4

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

frames: $(TARGET)
	./$(TARGET)

video: frames
	ffmpeg -framerate 30 -i ./frames/frame_%04d.ppm -c:v libx264 -pix_fmt yuv420p $(VIDEO)

gif:
	ffmpeg -i $(VIDEO) -vf "fps=15,scale=800:-1:flags=lanczos" -c:v pam -f image2pipe - | convert -delay 6 -loop 0 - fractal_julia.gif

clean:
	rm -f $(TARGET) $(FRAMES) $(VIDEO)

.PHONY: all frames video clean