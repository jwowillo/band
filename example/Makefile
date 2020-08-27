FLAGS = -g -Werror -Wall -Wextra -O2 -std=c++17 -fstack-protector -I ../band/bin -I ..

all: simple control

simple: asset band icon.image.o
	mkdir -p bin
	g++ $(FLAGS) simple.cc -L ../band/bin icon.image.o -l band-v2.0.0-dev -l dl -l X11 -l pthread -o bin/simple

control: asset band icon.image.o
	mkdir -p bin
	g++ $(FLAGS) control.cc -L ../band/bin icon.image.o -l band-v2.0.0-dev -l dl -l X11 -l pthread -o bin/control

asset:
	../cmd/file-to-code/file-to-code .. doc/band.png example/icon.image Icon ''

icon.image.o: icon.image.cc
	g++ -MMD -MP -c $(FLAGS) $< -o $@

band:
	$(MAKE) -C ../band

clean:
	$(MAKE) -C ../band clean
