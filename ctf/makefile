CXX = clang++
CXXFLAGS = -Wall -Wextra -g
TARGET = getPrimes

all: $(TARGET)

$(TARGET): getPrimes.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) getPrimes.cpp

clean:
	rm -f $(TARGET)