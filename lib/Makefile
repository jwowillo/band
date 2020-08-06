all: raylib

raylib: raylib-2.6.0
	$(MAKE) -C raylib-2.6.0/src PLATFORM=PLATFORM_DESKTOP

raylib-2.6.0:
	unzip raylib-2.6.0.zip -d .

clean:
	rm -rf raylib-2.6.0
