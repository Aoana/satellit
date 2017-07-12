CFLAGS = -Wall -pedantic -Werror -g
LFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm -lconfig -lcunit
PROG = utest
PROG_TARGET = $(addprefix $(GB_GIT)/, $(PROG))
CXX = gcc
MD := mkdir

TDIR = $(GB_WS)/unittest
INCLUDES = -I$(GB_GIT)/src/generic -I. 
SOURCES = $(wildcard *.c)
OBJS = $(addprefix $(TDIR)/, $(SOURCES:.c=.o))

ifdef DEBUG
CFLAGS  += -DDEBUG
endif

# top-level rule to create the program.
all: $(TDIR) $(PROG)

$(TDIR):
	$(MD) -p $(TDIR)

# Compiling
$(OBJS): $(TDIR)/%.o: ./%.c
	$(CXX) -c $(INCLUDES) $(CFLAGS) $< -o $@

# Linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG_TARGET) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(OBJS) $(PROG_TARGET)

