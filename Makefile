CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image
PROG = duckspond
PROG_TARGET = $(addprefix $(WORKSPACE)/, $(PROG))
CXX = gcc
MD := mkdir
SOURCEDIR = src

DIRS = graphics
TDIRS = $(foreach dir, $(DIRS), $(addprefix $(WORKSPACE)/, $(dir)))
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJS = $(subst $(SOURCEDIR), $(WORKSPACE), $(SOURCES:.c=.o))
$(info $$OBJS is $(OBJS))
	
# top-level rule to create the program.
all: $(PROG)

$(TDIRS):
	$(MD) -p $(TDIRS)

# Compiling graphics.
%.o: $(SOURCES) $(TDIRS)
	$(CXX) $(CFLAGS) -c -s $< -o $@

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS) $(PROG_TARGET)

