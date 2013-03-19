# We accept cpp and c source files
SRC_CXXEXT=.cpp
SRC_CEXT=.c

# Specify nane of source and object directories
SRC_DIR=src/
OBJ_DIR=obj/

# Name of the engine's static library
BINARIES=lxgine.a

# OS specifics
ifeq "$(shell uname)" "Darwin"
	# Mac specifics
	LIBPATH+=-L"/System/Library/Frameworks/OpenGL.framework/Libraries" -L$(OBJ_DIR)
	CFLAGS+=-I/usr/X11R6/include -I/usr/local/include -I$(SRC_DIR)
	LDFLAGS+=-framework GLUT -framework OpenGL -framework Cocoa
else
	# Windows specifics (no linux, easier this way)
	LIBPATH+=-L"C:\MinGW\freeglut\lib" -L$(OBJ_DIR)
	CFLAGS+=-I"C:\MinGW\freeglut\include" -I$(SRC_DIR)
	LDFLAGS+=-lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows
endif

# Retrieve all source and object file names, for all extensions
SRC_CXX = $(wildcard $(SRC_DIR)*$(SRC_CXXEXT))
SRC_C = $(wildcard $(SRC_DIR)*$(SRC_CEXT))
OBJ_CXX = $(addprefix $(OBJ_DIR),$(notdir $(SRC_CXX:$(SRC_CXXEXT)=.o)))
OBJ_C = $(addprefix $(OBJ_DIR),$(notdir $(SRC_C:$(SRC_CEXT)=.o)))

all: $(BINARIES)

clean:
	-rm *.o $(OBJ_DIR)*.o $(BINARIES) 

$(BINARIES): $(OBJ_CXX) $(OBJ_C)
	ar rvs $@ $^

# Build cpp source files
$(OBJ_DIR)%.o: $(SRC_DIR)%$(SRC_CXXEXT)
	g++ -c -o $@ $< $(CFLAGS)

# Build c source files
$(OBJ_DIR)%.o: $(SRC_DIR)%$(SRC_CEXT)
	gcc -c -o $@ $< $(CFLAGS)
