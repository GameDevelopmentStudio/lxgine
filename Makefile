# We accept cpp and c source files
SRC_CXXEXT=.cpp
SRC_CEXT=.c

# Specify nane of source and object directories
# All subdirectories must be organized in directories under these names
SRC_DIR=src/
OBJ_DIR=obj/

# Subdirectories
# We only use the external engine for now
ENGINE_DIR=engine/
ENGINE_SRC_DIR=$(ENGINE_DIR)$(SRC_DIR)
ENGINE_OBJ_DIR=$(ENGINE_DIR)$(OBJ_DIR)

# Wrap all source and object directories in one variable
SRC_DIRS=$(ENGINE_SRC_DIR) $(SRC_DIR)
OBJ_DIRS=$(ENGINE_OBJ_DIR) $(OBJ_DIR)

# String that matches every possible obj file (except main.o)
OBJ_PATTERN=$(foreach dir,$(OBJ_DIRS),$(dir)$($(OBJ_DIR))%.o)

# OS specifics
ifeq "$(shell uname)" "Darwin"
	# Mac specifics
	LIBPATH+=-L"/System/Library/Frameworks/OpenGL.framework/Libraries" $(addprefix -L,$(OBJ_DIRS))
	CFLAGS+=-I/usr/X11R6/include -I/usr/include -I/usr/local/include $(addprefix -I,$(SRC_DIRS))
	LDFLAGS+=-lglew -framework GLUT -framework OpenGL -framework Cocoa
	BINARIES=test.osx
else
	# Windows specifics (no linux, easier this way)
	LIBPATH+=-L"C:\MinGW\lib" $(addprefix -L,$(OBJ_DIRS))
	CFLAGS+=-I"C:\MinGW\include" $(addprefix -I,$(SRC_DIRS))
	LDFLAGS+=-lglew32 -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows
	BINARIES=test.exe
endif

# Functions to retrieve source and object files
# 
# Given a file extension, returnns all files with that extension within the
# sources directory
getsrcswithext=$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*$(1)))
# Given a list of source files, returns a list with the names of their 
# correspondent object files
getobjsfromsrcs=$(foreach item,$(1:$(2)=.o),$(subst $(SRC_DIR),$(OBJ_DIR),$(item)))
# Given a list of object files and the file extension, returns a list with
# the names of their correspondent source files
getsrcsfrombjswithext=$(foreach item,$(1:.o=$(2)),$(subst $(OBJ_DIR),$(SRC_DIR),$(item)))

# Retrieve all source and object files
SRC_CXX=$(call getsrcswithext,$(SRC_CXXEXT))
SRC_C=$(call getsrcswithext,$(SRC_CEXT))
OBJ_CXX=$(call getobjsfromsrcs,$(SRC_CXX),$(SRC_CXXEXT))
OBJ_C=$(call getobjsfromsrcs,$(SRC_C),$(SRC_CEXT))

# Engine is also a directory, so we need to add it as a .PHONY target if
# we want to build it, otherwise it will find the directory name and consider
# it as already built
.PHONY: engine

all: game

game: $(BINARIES)

# Currently unused. It will be used for engine's static compiling as a library
engine:
	make -C $(ENGINE_DIR)

clean:
	-rm *.o $(OBJ_DIR)*.o $(ENGINE_OBJ_DIR)*.o $(BINARIES)

# Final step: build main.o into game executable
$(BINARIES): main.o $(OBJ_CXX) $(OBJ_C)
	g++ -o $@ $^ $(LIBPATH) $(LDFLAGS)

# Build main.cpp
%.o: %.cpp
	g++ -c -o $@ $^ $(CFLAGS)

# Build all cpp source files in any subdirectory
$(OBJ_PATTERN): $(call getsrcsfrombjswithext,$(@),$(SRC_CXXEXT))
	g++ -c -o $@ $(call getsrcsfrombjswithext,$(@),$(SRC_CXXEXT)) $(CFLAGS)

# Build all c source files in any subdirectory
$(OBJ_PATTERN): $(call getsrcsfrombjswithext,$(@),$(SRC_CEXT))
	gcc -c -o $@ $(call getsrcsfrombjswithext,$(@),$(SRC_CEXT)) $(CFLAGS)
