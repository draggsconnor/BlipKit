---
layout: doc
full_title: BlipKit
order: 0
hide_comments: True
---

BlipKit is a C library for creating the beautiful sound of old [sound chips](http://en.wikipedia.org/wiki/Chiptune).

* Generate [waveforms](manual/waveforms/): square, triangle, noise, sawtooth, sine and custom waveforms
* Use an unlimited number of individual [tracks](manual/generating-sound/)
* Use stereo output or up to 8 channels
* Define [instruments](manual/instruments/) to create envelopes and other interesting effects
* Use [effects](manual/effects/): portamento, tremolo, vibrato and some more
* Load multi-channel [samples](manual/samples/) and play them at different pitches

<p class="buttons">
	<strong><a href="examples/" class="button">Examples</a></strong>
	<strong><a href="manual/" class="button">Read manual</a></strong>
	<a href="download/" class="button">Download</a>
</p>

## Basic Example

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/basic/square-wave-with-tremolo.mp3" | prepend: site.baseurl }}" class="button">
			Square Wave with Tremolo
		</a>
		<div class="label"><a href="{{ "/assets/sound/basic/square-wave-with-tremolo.mp3" | prepend: site.baseurl }}">Square Wave with Tremolo</a></div>
	</div>
</div>

This code demonstrates the basic steps to generate audio data of a [square wave](manual/waveforms/#square-wave) in the note *A* with enabled [tremolo effect](manual/effects/#tremolo):

{% highlight c %}
// Context object
BKContext ctx;

// Initialize context with 2 channels (stereo)
// and a sample rate of 44100 Hz
BKContextInit (& ctx, 2, 44100);

// Track object to generate the waveform
BKTrack track;

// Initialize track with square wave
// By default, the square wave has a duty cycle of 12.5%
BKTrackInit (& track, BK_SQUARE);

// Set mix and note volume
BKSetAttr (& track, BK_MASTER_VOLUME, 0.15 * BK_MAX_VOLUME);
BKSetAttr (& track, BK_VOLUME,        1.0 * BK_MAX_VOLUME);

// Set note A in octave 3
BKSetAttr (& track, BK_NOTE, BK_A_3 * BK_FINT20_UNIT);

// Enable tremolo effect
BKInt tremolo [2] = {20, 0.66 * BK_MAX_VOLUME};
BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo, sizeof (tremolo));

// Attach track to context
BKTrackAttach (& track, & ctx);

// Define audio data buffer
// As there are 2 channels used, the buffer actually must be
// two times the size than number of frames are requested
BKFrame frames [512 * 2];

// Generate 512 frames, e.g., as they would be requested by an audio output function
// Subsequent calls to this function generate the next requested number of frames
BKContextGenerate (& ctx, frames, 512);

// The channels are interlaced into the buffer in the form: LRLR...
// Which means that the first frame of the left channel is at frames[0],
// the first frame of the right channel at frames[1] and so on
{% endhighlight %}

- [Read manual](manual/)
- [More examples](examples/)
- [Download BlipKit](download/)
