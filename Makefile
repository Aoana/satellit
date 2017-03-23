CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image
PROG = duckspond
PROG_TARGET = $(addprefix $(WORKSPACE)/, $(PROG))
CXX = gcc
MD := mkdir
SOURCEDIR = src

DIRS = graphics
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
$(info $$SOURCES is $(SOURCES))
OBJS = $(subst $(SOURCEDIR), $(WORKSPACE), $(SOURCES:.c=.o))
$(info $$OBJS is $(OBJS))
	

# top-level rule to create the program.
all: $(PROG)

# Compiling graphics.
%.o: $(SOURCES)
	$(CXX) $(CFLAGS) -c -s $< 

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS) $(PROG_TARGET)

