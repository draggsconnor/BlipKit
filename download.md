---
layout: doc
title: Download and Building
order: 3
description: Build instructions and download page for the BlipKit library. Licensed under the MIT license.
---

	$ git clone https://github.com/detomon/BlipKit.git

[https://github.com/detomon/BlipKit](https://github.com/detomon/BlipKit)

## Building the Library

First execute `autogen.sh` in the base directory to generate the build system:

	blipkit$ sh ./autogen.sh

Next execute `configure` in the base directory:

	blipkit$ ./configure

Then execute `make` to build `libblipkit.a` in the `src` directory:

	blipkit$ make

Optionally, you may want to execute `sudo make install` to install the library
and headers on your system:

	blipkit$ sudo make install

## Building and Running Examples

All examples use SDL (<http://www.libsdl.org>) to output sound, so you have to
install it first. Execute `make examplename` to build an example in the
`examples` directory.

	blipkit/examples$ make tone
	blipkit/examples$ make divider
	blipkit/examples$ make stereo
	blipkit/examples$ make scratch
	blipkit/examples$ make waveform
	blipkit/examples$ make envelope

Finally, run examples like this:

	blipkit/examples$ ./tone

## License

This library is distributed under the MIT license. See `LICENSE` in the source directory.
