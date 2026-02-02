# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Target executable
TARGET = qcode

# Source and object files
SRCS = main.cpp QuantumState.cpp
OBJDIR = build
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Default rule
all: $(TARGET)

# Linking step (executable stays in current directory)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation step (object files go into build/)
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule (only removes object files)
clean:
	rm -rf $(OBJDIR)

# Distclean rule (removes objects + executable)
distclean: clean
	rm -f $(TARGET)
