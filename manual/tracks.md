---
layout: doc
title: Tracks
order: 15
description: Tracks play waveforms or samples, but can only play one note at once.
---

Tracks play [waveforms](../waveforms/) or [samples](../samples/), but can only play one *note* at once. The attribute `BK_MASTER_VOLUME` defines the volume at which the audio data is written into the audio buffers. It is 0 after initialization and has to be set explicitly. `BK_VOLUME` is used to set the loudness of *notes* and is at its maximum after initialization. Actually, the two values are interchangable, as they are multiplied by each other which would give the same result.

Tracks generate their own layer of audio data and do not interfere with each other.

{% highlight c %}
// The track object
BKTrack track;

// Initialize a track object with a square wave
BKTrackInit (& track, BK_SQUARE);

// Set master volume to 20%
BKTrackSetAttr (& track, BK_MASTER_VOLUME, 0.2 * BK_MAX_VOLUME);

// Set volume to 50%
// The final volume is 10%
BKTrackSetAttr (& track, BK_VOLUME, 0.5 * BK_MAX_VOLUME);
{% endhighlight %}

## Generating Audio Data

In order to include a track into the rendering chain, it has to be attached to a context. Each context may have an arbitrary number of tracks attached to it.

{% highlight c %}
// Attach track to context
BKTrackAttach (& track, & ctx);
{% endhighlight %}

## Playing Notes

The note is set with the attribute `BK_NOTE`.

{% highlight c %}
// Set note C of octave 3
BKTrackSetAttr (& track, BK_NOTE, BK_C_3 * BK_FINT20_UNIT);
{% endhighlight %}

The constants `BK_C_0` to `BK_C_8` are values between 0 and 96 and used for readability. Of course, their equivalent integer values can be used as well.

To unset the note, it can either be set to `BK_NOTE_RELEASE` or `BK_NOTE_MUTE`. The latter has a different behaviour when using [instruments](../instruments/); it does not play the envelopes' release parts and mutes the note immediately.

The release constants `BK_NOTE_RELEASE` and `BK_NOTE_MUTE` must **not** be multiplied by `BK_FINT20_UNIT`.

{% highlight c %}
// Release note
BKTrackSetAttr (& track, BK_NOTE, BK_NOTE_RELEASE);
{% endhighlight %}

## Attributes

