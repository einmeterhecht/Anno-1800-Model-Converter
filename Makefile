CXX      ?= g++
WINDRES  ?= windres
PYTHON   ?= python3
CXXFLAGS ?= -O2
CXXFLAGS += -std=c++17 -mf16c -IRDM-Converter/include -IConsole-Application/include \
            -Ithird-party/spdlog/include

SRC := $(wildcard RDM-Converter/src/*.cpp) Console-Application/src/Console-Application.cpp

ifeq ($(OS),Windows_NT)
  WIN := 1
endif
ifneq ($(findstring mingw,$(CXX)),)
  WIN := 1
endif

ifdef WIN
  BUILD   := build/windows
  BIN     := $(BUILD)/rdm-converter.exe
  LDFLAGS += -static
  LDLIBS  += -lshell32 -luser32
  RES     := $(BUILD)/Console-Application.res.o
else
  BUILD := build/linux
  BIN   := $(BUILD)/rdm-converter
endif

OBJ := $(SRC:%.cpp=$(BUILD)/%.o)

all: $(BIN)

$(BIN): $(OBJ) $(RES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(RES): Console-Application/Console-Application.rc
	@mkdir -p $(dir $@)
	$(WINDRES) -IConsole-Application -IConsole-Application/include $< -o $@

windows:
	$(MAKE) CXX=x86_64-w64-mingw32-g++ WINDRES=x86_64-w64-mingw32-windres

clean:
	rm -rf build

-include $(OBJ:.o=.d)
.PHONY: all windows clean
