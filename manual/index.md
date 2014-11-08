---
layout: doc
title: Manual
order: 10
description: This is an overview of the library's concept and its basic objects.
---

This is an overview of the library's concept and its basic objects. Objects can be declared and initialized statically, or allocated. Statically declared objecs can be wrapped into other structs to reduce memory allocations.

*Although the objects in the example snippets are declared in a function-like context, they should be declared globally or wrapped inside other objects, so they exist further when a function returns.*

- [Context Object](#context-object)
- [Track Objects](#track-objects)
- [Attributes](#attributes)
- [Playing a Note](#playing-a-note)
- [Disposing Objects](#disposing-objects)

## Context Object

[BKContext](context/) is the base object. The number of needed channels is defined at initialization (usually 2 for stereo). The sample rate should match the one which is used to output the audio, otherwise speed and pitch will not match.

{% highlight c %}
// The context object
BKContext ctx;

// Initialize a context object with 2 channels (stereo)
// and a sample rate of 44100 Hz
BKContextInit (& ctx, 2, 44100);
{% endhighlight %}

## Track Objects

[BKTrack](tracks/) objects render the audio data, this may be a [waveform](waveforms/) or a [sample](playing-samples/). A waveform type has to be given at initialization which can be changed afterwards, though. Each track generates it own layer of audio data and does not interfere with other tracks.

{% highlight c %}
// The track object
BKTrack track;

// Initialize a track object with a square wave
BKTrackInit (& track, BK_SQUARE);
{% endhighlight %}

In order to include a track into the rendering chain, it has to be attached to a context. Each context may have an arbitrary number of tracks attached to it.

{% highlight c %}
// Attach track to context
BKTrackAttach (& track, & ctx);
{% endhighlight %}

## Attributes

*Attributes* control the behaviour of objects. They can be single integers or pointers, which can either be other objects or structs. The following functions set or retreive these attributes.

The functions can be used for all objects, although not every object implements all attributes. If an object does not support an attribute or its value in invalid, an error code is returned.

<dl>
<dt><var>BKInt <strong>BKSetAttr</strong> (void * object, BKEnum attr, BKInt value)</var></dt>
<dd>

<p>Sets an integer attribute.</p>

{% highlight c %}
BKInt value = 8;

BKSetAttr (& track, BK_DUTY_CYCLE, value);
{% endhighlight %}
</dd>

<dt><var>BKInt <strong>BKGetAttr</strong> (void const * object, BKEnum attr, BKInt * outValue)</var></dt>
<dd>
<p>Retreives an integer attribute.</p>

{% highlight c %}
BKInt value;

BKGetAttr (& track, BK_DUTY_CYCLE, & value);
{% endhighlight %}
</dd>

<dt><var>BKInt <strong>BKSetPtr</strong> (void * object, BKEnum attr, void * ptr)</var></dt>
<dd>
<p>Sets a pointer or struct attribute.</p>

{% highlight c %}
// An object declared elsewhere
BKInstrument * instrument = ...;

BKSetPtr (& track, BK_INSTRUMENT, instrument, 0);
{% endhighlight %}

{% highlight c %}
BKInt range [2] = {15000, 28000};

BKSetPtr (& track, BK_SAMPLE_RANGE, range, sizeof (range));
{% endhighlight %}
</dd>

<dt><var>BKInt <strong>BKGetPtr</strong> (void const * object, BKEnum attr, void * outPtr)</var></dt>
<dd>
<p>Retreives a pointer or struct attribute.</p>

{% highlight c %}
BKInstrument * instrument;

BKGetPtr (& track, BK_INSTRUMENT, & instrument, 0);
{% endhighlight %}

{% highlight c %}
BKInt range [2];

BKGetPtr (& track, BK_SAMPLE_RANGE, range, sizeof (range));
{% endhighlight %}
</dd>

</dl>

- [Track attributes](tracks/#attributes)
- [Context attributes](context/#attributes)
- [Data attributes](data/#attributes)

## Disposing Objects

When an object is not used anymore, is should be disposed to free its resources. There is a general dispose function `BKDispose` which can be used on all objects.

When disposing, the objects are detached from the objects which they are attached to.

{% highlight c %}
BKTrack track;

// Initialize object
BKTrackInit (& track, BK_SQUARE);

...

BKDispose (& track);
{% endhighlight %}

{% highlight c %}
BKTrack * track;

// Allocate and initialize object
BKTrackAlloc (& track, BK_SQUARE);

...

BKDispose (track);
{% endhighlight %}
