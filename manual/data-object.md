---
layout: doc
title: Data Object
order: 78
description: BKData is a general container for audio frames. It is used to hold waveform phases and sample frames.
---

`BKData` is a general container for audio frames. It is used to hold [waveform](../waveforms/) phases and [sample](../playing-samples/) frames. Its content can be loaded from WAVE files or raw audio data.

A data object can be attached to multiple tracks.

## Attributes

<dl>

<dt><var>BK_SAMPLE_PITCH</var></dt>
<dd>

<p>Sets the object's pitch.</p>
<p>This attribute is used to <em>tune</em> the sample. It should be tuned to <code>BK_C_4</code> to represent the correct note.</p>
<p>When a sample is attached to a track, the data object's <code>BK_SAMPLE_PITCH</code> attribute overwrites the one of the track, so this attribute has to be set before.</p>

{% highlight c %}
// Tune sample
BKSetAttr (& data, BK_SAMPLE_PITCH, -0.257 * BK_FINT20_UNIT);
{% endhighlight %}
</dd>

<dt><var>BK_NUM_FRAMES</var> (read-only)</dt>
<dd>

<p>The number of frames per channel.</p>

{% highlight c %}
BKInt numFrames;

// Get number of frames
BKGetAttr (& data, BK_NUM_FRAMES, & numFrames);
{% endhighlight %}
</dd>

<dt><var>BK_NUM_CHANNELS</var> (read-only)</dt>
<dd>

<p>The number of channel.</p>

{% highlight c %}
BKInt numChannels;

// Get number of channels
BKGetAttr (& data, BK_NUM_CHANNELS, & numChannels);
{% endhighlight %}
</dd>

</dl>
