CFLAGS = -Wall -pedantic -Werror -g
LFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm -lconfig
PROG = gravbounce
PROG_TARGET = $(addprefix $(GB_GIT)/, $(PROG))
CXX = gcc
MD := mkdir
SOURCEDIR = src

DIRS = generic graphics logic objects controls audio main
TDIRS = $(foreach dir, $(DIRS), $(addprefix $(GB_WS)/, $(dir)))
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJS = $(subst $(SOURCEDIR), $(GB_WS), $(SOURCES:.c=.o))
	
# top-level rule to create the program.
all: $(TDIRS) $(PROG)

$(TDIRS):
	$(MD) -p $(TDIRS)

# Compiling 
$(OBJS): $(GB_WS)/%.o: $(SOURCEDIR)/%.c
	$(CXX) -c $(INCLUDES) $(CFLAGS) $< -o $@

# Linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS) $(PROG_TARGET)

