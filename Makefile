CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image
OBJS   = init.o input.o main.o graphics.o
OBJS_TARGET := $(addprefix $(WORKSPACE)/, $(OBJS))
PROG = duckspond
PROG_TARGET = $(addprefix $(WORKSPACE)/, $(PROG))
CXX = gcc

# top-level rule to create the program.
all: $(PROG)

# Compiling graphics.
%.o: src/graphics/%.c src/graphics/%.h src/graphics/defs.h
	$(CXX) $(CFLAGS) -c -s $< -o $(WORKSPACE)/$@

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS_TARGET) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS_TARGET) $(PROG_TARGET)

