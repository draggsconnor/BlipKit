---
layout: doc
title: Manual
order: 5
---

BlipKit is a C library for simulating old sound chips. It generates waveforms like square and triangle waves on different tracks with multiple channels. The library itself is not able to output audio, it only creates the audio data which then can be used otherwise. (e.g. played with [SDL](sdl))

A track generates a single waveform or renders a sample, but can only play one note at a time. There are attributes which control their behavior. This includes waveform, note, volume, panning, duty cycle for square waves and some more.

There are some [effects][effect] which “animate“ track attributes. For example, sliding to a new note in a certain amount of time. [Instruments][instruments] can be used to create envelopes for different attributes. It is also possible to create [custom waveforms][custom waveforms] and playing [samples][samples].

[sdl]: http://www.libsdl.org
[effect]: manual/effects/
[instruments]: manual/instruments/
[custom waveforms]: manual/waveforms/
[samples]: manual/samples/
