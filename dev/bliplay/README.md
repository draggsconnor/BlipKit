bliplay
=======

This program was build to play more complex sound files to test the BlipKit
library. It reads a CSV like file format. Some examples are located in
`examples`.

Building and running
--------------------

You have to build the library in the base directory first. Then execute the
following command to build `bliplay`:

	blipkit/dev/bliplay$ make bliplay

Now you can play the examples:

	blipkit/dev/bliplay$ ./bliplay -p examples/generic-boss-appears.blip

Options
-------

The play speed can be adjusted with the options `s`:

	blipkit/dev/bliplay$ ./bliplay -s 32 -p examples/generic-boss-appears.blip

More TODO...

File format
-----------

TODO
