# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ========================================== 

# Test suite list #
TESTS = absTest controllerTest tcsTest datalogTest aebTest speedometerTest laneControlTest eaebTest accTest
# # # # # # # # # #

C_COMPILER=gcc
SRC_DIR=../src
UNITY_DIR=unity
UNITY_SRC=$(UNITY_DIR)/unity.c
RUNNER_GEN=$(UNITY_DIR)/generate_test_runner.rb
TARGET_FILES = $(patsubst %,%$(TARGET_EXTENSION),$(TESTS))

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.out
else
	TARGET_EXTENSION=.out
endif
INC_DIRS=-I$(SRC_DIR) -I$(UNITY_DIR)
SYMBOLS=-DTEST

ifeq ($(OSTYPE),cygwin)
        CLEANUP = rm -f build/*.o ; rm -f *$(TARGET_EXTENSION) ; mkdir -p build
else ifeq ($(OS),Windows_NT)
        CLEANUP = rm -f build/*.o ; rm -f *$(TARGET_EXTENSION) ; mkdir -p build
else
	CLEANUP = rm -f build/*.o ; rm -f *$(TARGET_EXTENSION)
endif

all: clean $(TARGET_FILES)
	$(patsubst %,./% && ,$(filter-out $(lastword $(TARGET_FILES)),$(TARGET_FILES)))./$(lastword $(TARGET_FILES))

clean:
	$(CLEANUP)
	
absTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) absTest/absTest.c
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/abs.c $(SRC_DIR)/controller.h $(SRC_DIR)/speedometer.h -o $@

controllerTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) controllerTest/controllerTest.c 
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/controller.c $(SRC_DIR)/nxt_interface.h -o $@
	
tcsTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) tcsTest/tcsTest.c 
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/tcs.c $(SRC_DIR)/nxt_interface.h $(SRC_DIR)/speedometer.h -o $@

aebTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) aebTest/aebTest.c 
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/aeb.c $(SRC_DIR)/nxt_interface.h -o $@

datalogTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) datalogTest/datalogTest.c 
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/datalog.c $(SRC_DIR)/nxt_interface.h $(SRC_DIR)/controller.h -o $@

speedometerTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) speedometerTest/speedometerTest.c 
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/speedometer.c $(SRC_DIR)/nxt_interface.h $(SRC_DIR)/controller.h -o $@

laneControlTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) laneControlTest/laneControlTest.c
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/laneControl.c $(SRC_DIR)/controller.h $(SRC_DIR)/nxt_interface.h -o $@

eaebTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) eaebTest/eaebTest.c
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/eaeb.c $(SRC_DIR)/nxt_interface.h $(SRC_DIR)/abs.h $(SRC_DIR)/controller.h $(SRC_DIR)/aeb.h -o $@

accTest$(TARGET_EXTENSION):
	ruby $(RUNNER_GEN) accTest/accTest.c
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(UNITY_SRC) $(wildcard $*/*.c) \
	$(SRC_DIR)/acc.c $(SRC_DIR)/nxt_interface.h $(SRC_DIR)/abs.h $(SRC_DIR)/edc.h $(SRC_DIR)/speedometer.h $(SRC_DIR)/constants.h -o $@
