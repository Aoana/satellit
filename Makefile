CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image
PROG = duckspond
PROG_TARGET = $(addprefix $(WORKSPACE)/, $(PROG))
CXX = gcc
MD := mkdir
SOURCEDIR = src

DIRS = generic graphics logic person
TDIRS = $(foreach dir, $(DIRS), $(addprefix $(WORKSPACE)/, $(dir)))
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJS = $(subst $(SOURCEDIR), $(WORKSPACE), $(SOURCES:.c=.o))
	
# top-level rule to create the program.
all: $(TDIRS) $(PROG)

$(TDIRS):
	$(MD) -p $(TDIRS)

# Compiling 
$(OBJS): $(WORKSPACE)/%.o: $(SOURCEDIR)/%.c
	$(CXX) -c $(INCLUDES) $(CFLAGS) $< -o $@

# Linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS) $(PROG_TARGET)

