.ONESHELL:

CORE_CC := gcc
CORE_CFLAGS += -Ofast -ffast-math
CORE_SOURCES := $(wildcard src/*.c)
CORE_SOURCES += $(wildcard src/holly/*.c)

NEON_CC := c++
NEON_CFLAGS := 
PLATFORM := $(shell uname -s)

ifeq ($(PLATFORM),Darwin)
	CFLAGS += -mmacosx-version-min=10.9 -Wno-newline-eof
endif

VERSION_TAG := $(shell git describe --always --tags --abbrev=0)
COMMIT_HASH := $(shell git rev-parse --short HEAD)
OS_INFO := $(shell uname -rmo)

bin/daydream frontend/main.cpp:
	mkdir -p bin

	c++ frontend/*.cpp -o daydream -I"frontend" `sdl2-config --cflags --libs`

core:
	mkdir -p build
	cd build

	$(CORE_CC) -c $(CORE_SOURCES) \
		-I"../src/" \
		-DOS_INFO="$(OS_INFO)" \
		-DREP_VERSION="$(VERSION_TAG)" \
		-DREP_COMMIT_HASH="$(COMMIT_HASH)" \
		$(CORE_CFLAGS)

	cd ..

deps:
	git clone https://github.com/ocornut/imgui

	mkdir -p build

	c++ -c \
		../imgui/*.cpp \
		../imgui/backends/imgui_impl_sdl2.cpp \
		../imgui/backends/imgui_impl_sdlrenderer2.cpp \
		-I"../imgui/" \
		-I"../imgui/backends/" \
		`sdl2-config --cflags --libs`

	cd ..

clean:
	rm -rf "bin"