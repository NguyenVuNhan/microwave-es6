TARGET 				= microwave_test

CC 					= g++
CFLAGS 				= -Wall $(INCL) -DTESTING
LDFLAGS 			= -lpthread

MODULES 			= displayControl states utils microwave
SRC_DIR     		= $(addprefix ../src/,$(MODULES))
SRC_DIR				+= ../test
SRC_DIR				+= ../test/stub
BUILD_DIR   		= $(addprefix ../build/,$(MODULES))
BUILD_DIR   		+= ../build
BUILD_DIR   		+= ../build/stub
BIN_DIR     		= ../bin

SRC 				= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ_TMP				= $(patsubst ../src/%.cpp,../build/%.o,$(SRC))
OBJ 				+= $(patsubst ../test/%.cpp,../build/%.o,$(OBJ_TMP))
INCL 				= $(addprefix -I,$(SRC_DIR))
INCL				+= -I../test/include
GTEST_OBJS 			= ./build/lib/libgtest.a \
					  ./build/lib/libgtest_main.a \
					  ./build/lib/libgmock.a \
					  ./build/lib/libgmock_main.a

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp Makefile
	$(CC) -c $(CFLAGS) $$< -o $$@
endef

.PHONY: all clean checkdirs $(TARGET)

all: checkdirs $(TARGET)
	./$(BIN_DIR)/$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(GTEST_OBJS) $(LDFLAGS) -o $(BIN_DIR)/$@

checkdirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

tmp:
	@echo $(OBJ)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
