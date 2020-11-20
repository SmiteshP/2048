BUILDDIR= build
SOURCEDIR= src
SOURCES= $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS= $(patsubst $(SOURCEDIR)/%, $(BUILDDIR)/%, $(patsubst %.cpp, %.o, $(SOURCES)))
BINARY= 2048
CXXFLAGS = -std=c++17

.PHONY: all release debug run clean

all: release

release: CXXFLAGS += -O2
release: build $(BINARY)

debug: CXXFLAGS += -g -Wall -Wshadow -fsanitize=address -fsanitize=undefined
debug: build $(BINARY)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

format:
	clang-format -i -style=file src/*.cpp src/*.hpp

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BINARY) $^

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

run: $(BINARY)
	@(./$(BINARY))

clean:
	rm -f $(BUILDDIR)/* $(BINARY)
