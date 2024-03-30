.ONESHELL:

CORE_CC := gcc
CORE_CFLAGS += -Ofast -ffast-math
CORE_SOURCES := $(wildcard src/*.c)
CORE_SOURCES += $(wildcard src/holly/*.c)

IMGUI_CC := c++
IMGUI_CFLAGS := -I"../imgui/" -I"../imgui/backends/"
IMGUI_CFLAGS += `sdl2-config --cflags --libs`
IMGUI_SOURCES := $(wildcard imgui/*.cpp)
IMGUI_SOURCES += imgui/backends/imgui_impl_sdl2.cpp
IMGUI_SOURCES += imgui/backends/imgui_impl_sdlrenderer2.cpp

NEON_CC := c++
NEON_CFLAGS := -I"frontend" -I"src" -I"imgui" -I"imgui/backends"
NEON_CFLAGS += `sdl2-config --cflags --libs`
NEON_SOURCES := $(wildcard frontend/*.cpp)
NEON_SOURCES += $(wildcard build/*.o)

PLATFORM := $(shell uname -s)

ifeq ($(PLATFORM),Darwin)
	CFLAGS += -mmacosx-version-min=10.9 -Wno-newline-eof
endif

VERSION_TAG := $(shell git describe --always --tags --abbrev=0)
COMMIT_HASH := $(shell git rev-parse --short HEAD)
OS_INFO := $(shell uname -rmo)

bin/daydream frontend/main.cpp:
	mkdir -p bin

	$(NEON_CC) $(NEON_SOURCES) \
		-o bin/daydream $(NEON_CFLAGS)

core:
	mkdir -p build
	cd build

	$(CORE_CC) -c \
		$(addprefix ../, $(CORE_SOURCES)) \
		-I"../src/" \
		-DOS_INFO="$(OS_INFO)" \
		-DREP_VERSION="$(VERSION_TAG)" \
		-DREP_COMMIT_HASH="$(COMMIT_HASH)" \
		$(CORE_CFLAGS)

	cd ..

deps:
	git clone https://github.com/ocornut/imgui

	mkdir -p build
	cd build

	$(IMGUI_CC) -c \
		$(addprefix ../, $(IMGUI_SOURCES)) \
		$(IMGUI_CFLAGS)

	cd ..

clean:
	rm -rf "bin"
	rm -rf "build"