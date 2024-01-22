CC = clang
CFLAGS = -v -I/opt/homebrew/include -I./include -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lc++ -std=c++20
TARGET = main
SOURCE = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/*%.cpp, dist/%.o, $(SOURCE))

.PHONY: build debug run dev clean

build: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o dist/$(TARGET)

debug: CFLAGS += -g
debug: build

dist/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./dist/$(TARGET)

dev: build run

clean:
	rm -f dist/*.o dist/$(TARGET)