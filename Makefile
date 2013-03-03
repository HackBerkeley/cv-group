CXX = clang++
LDFLAGS = -lm -lopencv_highgui -lopencv_core -lopencv_imgproc
CXXFLAGS = -I/usr/include/opencv2 -I/usr/include/eigen3 -Wall -Wextra

TARGETS = calc

all: $(TARGETS)

calc: calc.cc

clean:
	rm -f $(TARGETS)
