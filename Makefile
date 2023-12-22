CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = life

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET)
