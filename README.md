![band](doc/band.png)

`band` is a c++ media-library.

## Dependencies

* `libtool`: Combining static libraries when building.

## Building

* `make` in the 'band' dierctory builds `band` into a static-library.
* `make` in the 'example' directory builds all the examples.

## Running

* `cmd/file-to-code/file-to-code` runs a tool which generates a header and
  source file from a normal file.
* `example/bin/simple` runs the simple-example.

## Linking

* Provide the path to the combiled 'band'-directory as an include-path and the
  compiled static-library as a linked-library. Additionally, `dl`, `X11`, and
  `pthread` should be linked. These aren't a dependency for all platforms so
  they are left to the consumer to link. An example can be seen in the
  'Makefile' in the 'example' folder.
