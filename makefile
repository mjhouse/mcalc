CPP=g++
C=gcc

CPPFLAGS=`pkg-config gtkmm-3.0 --cflags --libs` -std=c++11 -ldl -g

TARGET = bin/mcalc
OUTDIR = bin
BLDDIR = obj
SRCDIR = src
INCDIR = inc

INC = -I$(INCDIR)

# copy glade file to output
$(shell cp res/*.glade bin/)
$(shell cp res/*.css bin/)
$(shell cp res/*.db bin/)

# find all source files in src
SOURCES  := $(shell find src/ -type f -name '*.cpp')
CSOURCES := $(shell find src/ -type f -name '*.c')

# assembles each source file into a BLDIR/*.o filename
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(BLDDIR)/%.o)
COBJECTS := $(CSOURCES:$(SRCDIR)/%.c=$(BLDDIR)/%.o)

# ----------------------------------------------------------------------
# DON'T EDIT BELOW THIS LINE
# ----------------------------------------------------------------------
all: link

# link executable
link: $(OBJECTS) $(COBJECTS)
	$(CPP) $(OBJECTS) $(COBJECTS) -o $(TARGET) $(CPPFLAGS)

# build all .o files from .cpp source
obj/%.o: src/%.cpp
	$(CPP) $(INC) -c $< -o $@ $(CPPFLAGS)

# build all .o files from .c source
obj/%.o: src/%.c
	$(C) $(INC) -c $< -o $@

clean:
	rm $(BLDDIR)/*.o; rm $(OUTDIR)/*;
