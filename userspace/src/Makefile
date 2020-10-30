TARGET 		= microwave

CC 			= g++
CCarm 		= /usr/local/xtools/arm-unknown-linux-uclibcgnueabi/bin/arm-linux-g++
CFLAGS 		= -Wall $(INCL)
LDFLAGS 	= -lstdc++ -pthread

MODULES 	= displayControl states utils hardware microwave
SRC_DIR     = $(addprefix ../src/,$(MODULES))
SRC_DIR     += ../src
BUILD_DIR   = $(addprefix ../build/,$(MODULES))
BUILD_DIR   += ../build
BIN_DIR     = ../bin

SRC 		= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ 		= $(patsubst ../src/%.cpp,../build/%.o,$(SRC))
INCL 		= $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp Makefile
	$(CC$(ARCH)) -c $(CFLAGS) $$< -o $$@
endef

.PHONY: all clean checkdirs $(TARGET)

all: checkdirs $(TARGET)

$(TARGET): $(OBJ)
	$(CC$(ARCH)) $(OBJ) $(LDFLAGS) -o $(BIN_DIR)/$@

checkdirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

# clean
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

