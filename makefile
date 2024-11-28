#compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -I$(shell brew --prefix nlohmann-json)/include
LDFLAGS = -lcurl

#exec name
TARGET = weatherApp

#source files
SRCS = main.cpp CommandLineInterfaceDriver.cpp WeatherController.cpp HTTPSController.cpp

#compiled source files
OBJS = $(SRCS:.cpp=.o)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

#compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean up
clean:
	rm -f $(OBJS) $(TARGET)
