.PHONY: asset

FLAGS = -g -Werror -Wall -Wextra -O2 -std=c++17 -fstack-protector -I .. -I../lib/raylib-2.6.0/src

SRCS =
SRCS += asset/font/helvetica.font.cc
SRCS += control.cc
SRCS += control/border.cc
SRCS += control/fps.cc
SRCS += control/image.cc
SRCS += control/label.cc
SRCS += control/rectangle.cc
SRCS += control/texture.cc
SRCS += interface.cc
SRCS += interface/raylib_interface.cc
SRCS += scope.cc
OBJS = $(subst .cc,.o,$(SRCS))
DEPS = $(subst .cc,.d,$(SRCS))

HEADERS =
HEADERS += all.h
HEADERS += asset/font/helvetica.font.h
HEADERS += control.h
HEADERS += control/all.h
HEADERS += control/anchor.h
HEADERS += control/border.h
HEADERS += control/button.h
HEADERS += control/fixed_panel.h
HEADERS += control/fps.h
HEADERS += control/image.h
HEADERS += control/label.h
HEADERS += control/padded_panel.h
HEADERS += control/rectangle.h
HEADERS += control/separator.h
HEADERS += control/stack_panel.h
HEADERS += control/texture.h
HEADERS += interface.h
HEADERS += interface/raylib_interface.h
HEADERS += interface/base_interface_decorator.h
HEADERS += interface/debug_interface_decorator.h
HEADERS += interface/section_interface_decorator.h
HEADERS += scope.h

VERSION = v2.0.0-dev

all: asset lib $(OBJS)
	mkdir -p bin
	mkdir -p bin/band
	cp --parents $(HEADERS) bin/band
	ar rvs bin/libband-no-raylib-$(VERSION).a $(OBJS)
	./combine-libs $(VERSION)

asset:
	../cmd/file-to-code/file-to-code .. band/asset/font/helvetica.ttf band/asset/font/helvetica.font Helvetica band::asset::font

lib:
	$(MAKE) -C ../lib

# This has a special override since the stb dependency has tons of unused
# functions.
interface/raylib_interface.o: interface/raylib_interface.cc
	g++ -MMD -MP -c -Wno-unused-function $(FLAGS) $< -o $@

%.o: %.cc
	g++ -MMD -MP -c $(FLAGS) $< -o $@

clean:
	rm -rf bin $(OBJS) $(DEPS)

-include $(DEPS)
