---
layout: doc
title: Playing Samples
order: 70
description: A samples can be loaded from a WAVE file or from raw audio data and can contain 1 or more channels.
---

A sample replaces the waveform of a track and is played when a note is set in the corresponding pitch. It can be loaded from a WAVE file or from raw audio data and can contain 1 or more channels. If it contains more than 1 channel, the number of channels must match the context's number of channels, or else it cannot be set to a track and is ignored.

Samples are loaded into the general audio data container [`BKData`](../data/) and can be set to multiple track.

{% highlight c %}
// Data object to hold the frames
BKData data;

// Open WAVE file
FILE * file = fopen ("pika.wav", "rb");

// Initialize sample object with audio data from file
BKDataInitAndLoadWAVE (& data, file);

// Set sample to track
BKSetPtr (& track, BK_SAMPLE, & data);

// Play sample in original pitch
BKSetAttr (& track, BK_NOTE, BK_C_4 * BK_FINT20_UNIT);

// Play sample 1 octave higher
BKSetAttr (& track, BK_NOTE, BK_C_5 * BK_FINT20_UNIT);
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/samples/pika.mp3" | prepend: site.baseurl }}" class="button">
			Pika
		</a>
		<div class="label"><a href="{{ "/assets/sound/samples/pika.mp3" | prepend: site.baseurl }}">Pika</a></div>
	</div>
</div>

## Normalizing

The function `BKDataNormalize` expands the amplitudes of the sample frames to their maximum value relatively to the highest absolute amplitude. This can be used to increase the volume of a sample to the maximum possible value.

{% highlight c %}
// Normalize sample frames
BKDataNormalize (& data);
{% endhighlight %}

## Pitch

The sample rate of samples is ignored when playing them. This means, if a sample has a higher sample rate than the context, it would be played too slow. However, the `BKData` object has an attribute `BK_SAMPLE_PITCH` which can be used to *tune* the sample. The sample should be tuned to `BK_C_4` to represent the correct note.

When a sample is set to a track, the sample's attribute `BK_SAMPLE_PITCH` is copied to it, so the attribute has to be set before setting the sample.

{% highlight c %}
// Tune sample
BKSetAttr (& data, BK_SAMPLE_PITCH, -0.257 * BK_FINT20_UNIT);
{% endhighlight %}
