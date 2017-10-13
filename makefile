CC=g++
CPPFLAGS=`pkg-config gtkmm-3.0 --cflags --libs` -std=c++11

TARGET = bin/mcalc
OUTDIR = bin
BLDDIR = obj
SRCDIR = src
INCDIR = inc

INC = -I$(INCDIR)

# copy glade file to output
$(shell cp res/*.glade bin/)
$(shell cp res/*.css bin/)

# find all source files in src
SOURCES := $(shell find src/ -type f -name '*.cpp')

# assembles each source file into a BLDIR/*.o filename
OBJECTS := $(SOURCES:src/%.cpp=$(BLDDIR)/%.o)

# ----------------------------------------------------------------------
# DON'T EDIT BELOW THIS LINE
# ----------------------------------------------------------------------
all: link

# link executable
link: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CPPFLAGS)

# build all .o files
obj/%.o: src/%.c*
	$(CC) $(INC) -c $< -o $@ $(CPPFLAGS)

clean:
	rm $(BLDDIR)/*.o; rm $(TARGET);
