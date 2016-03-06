---
layout: doc
title: Context Object
order: 80
description: BKContext is the base object and contains the channel sound buffers.
---

`BKContext` is the base object and contains the channel sound buffers. The context is also responsible for running the attached [clocks](../clocks-and-dividers/).

{% highlight c %}
// The context object
BKContext ctx;

// Initialize context object
BKContextInit (& ctx, 2, 44100);

// Work with the context
...

// Dispose context object when not used anymore
// Track which are still attached are detached now and resources are freed
BKDispose (& ctx);
{% endhighlight %}

This initializes a `BKContent` object with 2 channels (stereo) and a sample rate of 44100 Hz. The maximum number of channels is `BK_MAX_CHANNELS` (8). The sample rate can range between `BK_MIN_SAMPLE_RATE` (16000) and `BK_MAX_SAMPLE_RATE` (96000). Lower or higher values are clamped.

## Attributes

The following list contains attributes which can be set with with `BKContextSetAttr` or read with `BKContextGetAttr`. Some attributes use a more complex data type and can be set with `BKContextSetPtr` or read with `BKContextGetPtr`.

<dl>
<dt><var>BK_SAMPLE_RATE</var> (read-only)</dt>
<dd>

<p>Data type: <var>BKInt</var></p>

<p>The sample rate on which basis the note frequencies are calculated. This attribute is read-only and can only be set at initialization.</p>

{% highlight c %}
BKInt sampleRate;

// Read sample rate
BKGetAttr (& ctx, BK_SAMPLE_RATE, & sampleRate);

// sampleRate has the value 44100
{% endhighlight %}

</dd>
<dt><var>BK_NUM_CHANNELS</var> (read-only)</dt>
<dd>

<p>Data type: <var>BKInt</var></p>

<p>Number of channels in which the sound data is rendered. Attributes and track effects which affect panning have only an effect when this number is exactly 2 (stereo). This attribute is read-only and can only be set at initialization.</p>

{% highlight c %}
BKInt numChannels;

// Read number of channels
BKGetAttr (& ctx, BK_NUM_CHANNELS, & numChannels);

// numChannels has the value 2
{% endhighlight %}

</dd>

<dt><var>BK_CLOCK_PERIOD</var></dt>
<dd>

<p>Data type: <var>BKTime</var></p>

<p>The master clock's tick period. This is a <a href="../clocks-and-dividers/">BKTime</a> struct. The default value is a 1/240th second (240 Hz). Use this attribute if a finer time granularity is required.</p>

{% highlight c %}
// Make time value
BKTime time = BKTimeFromSeconds (& ctx, 1.0 / 240.0);

// Set period of the master clock
BKSetPtr (& ctx, BK_CLOCK_PERIOD, & time, sizeof (time));

// Get period of the master clock
BKGetPtr (& ctx, BK_CLOCK_PERIOD, & time, sizeof (time));
{% endhighlight %}

</dd>
<dt><var>BK_TIME</var> (read-only)</dt>
<dd>

<p>Data type: <var>BKTime</var></p>

<p>This is the current absolute number of frames generated since initialization or the last reset of the context.</p>

{% highlight c %}
BKTime time;

// Get absolute time
BKGetPtr (& ctx, BK_TIME, & time, sizeof (time));
{% endhighlight %}

</dd>
</dl>

## Functions <span class="header-file">(<a href="https://github.com/detomon/BlipKit/blob/master/src/BKContext.h"><var>BKContext.h</var></a>)</span>

### BKContextInit

	BKInt BKContextInit (BKContext * ctx, BKInt numChannels, BKInt sampleRate)

Initializes a context object `ctx` with `numChannel` channels and a sample rate of `sampleRate`. Returns `0` on success.

Possible return errors:

`BK_ALLOCATION_ERROR` if memory allocation failed.

### BKContextAlloc

	BKInt BKContextAlloc (BKContext ** outCtx, BKInt numChannels, BKInt sampleRate)

Allocate and initializes a context object `ctx` with `numChannel` channels and a sample rate of `sampleRate`. Returns `0` on success.

Possible return errors:

`BK_ALLOCATION_ERROR` if memory allocation failed.