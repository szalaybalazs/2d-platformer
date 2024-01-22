CC = clang
CFLAGS = -v -I/opt/homebrew/include -I./include -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lc++ -std=c++20
TARGET = main
SRCDIR = src
OBJDIR = dist
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
HEADERS = $(wildcard $(SRCDIR)/*.hpp)

.PHONY: build debug run dev clean

build: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(OBJDIR)/$(TARGET)

debug: CFLAGS += -g
debug: build

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(OBJDIR)/$(TARGET)

dev: build run

clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/$(TARGET)
