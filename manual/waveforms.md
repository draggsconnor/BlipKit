---
layout: doc
title: Waveforms
order: 30
description: Waveforms consist of a certain number of *hases (amplitude steps). Tracks have predefined waveforms which are typical for old sound chips.
---

Waveforms consist of a certain number of *phases* (amplitude steps). Each phase is a value in the range from `-BK_MAX_VOLUME` to `+BK_MAX_VOLUME`. When playing a note, the waveform and with it its phases are scaled so that they are in the correct pitch. Tracks have predefined waveforms which are typical for old sound chips.

- [Square Wave](#square-wave)
- [Triangle Wave](#triangle-wave)
- [Noise](#noise)
- [Sawtooth Wave](#sawtooth-wave)
- [Sine Wave](#sine-wave)
- [Custom Waveforms](#custom-waveforms)

## Square Wave

`BK_SQUARE` has 16 phases. The duty cycle attribute `BK_DUTY_CYCLE` defines the length of the wave peak. This value is 4 by default, which accords to a duty cycle of 25%. The value can range from 1 to 15:

{% highlight text %}
    +-----+
    |12.5%|  duty cycle: 2
0 - +     +-----------------------------------------+

    +-----------+
    |    25%    |  duty cycle: 4
0 - +           +-----------------------------------+

    +-----------------------+
    |         50%           |  duty cycle: 8
0 - +                       +-----------------------+

    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
{% endhighlight %}

{% highlight c %}
// Set square wave
BKTrackSetAttr (& track, BK_WAVEFORM, BK_SQUARE);

// Set duty cycle to 50%
BKTrackSetAttr (& track, BK_DUTY_CYCLE, 8);
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-square-2.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-square-2.mp3" | prepend: site.baseurl }}">Square Wave 12.5%</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-square-4.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-square-4.mp3" | prepend: site.baseurl }}">Square Wave 25%</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-square-8.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-square-8.mp3" | prepend: site.baseurl }}">Square Wave 50%</a></div>
	</div>
</div>

## Triangle Wave

`BK_TRIANGLE` has 32 phases and is the only waveform which is not affected by the volume. It is either 0 or at its maximum for values greater than 0. This is because some sound chips also had no volume setting for triangle waves.

{% highlight text %}
                __
              _|  |_
            _|      |_
          _|          |_
        _|              |_
      _|                  |_
    _|                      |_
0 _|__________________________|_______________________________
                                 |_                        _|
                                   |_                    _|
                                     |_                _|
                                       |_            _|
                                         |_        _|
                                           |_    _|
                                             |__|
{% endhighlight %}

The waveform is shifted to the left by 8 phases. This is done to use negative amplitudes as well to reduce potential amplitude overflows when mixing the tracks.

{% highlight c %}
// Set triangle wave
BKTrackSetAttr (& track, BK_WAVEFORM, BK_TRIANGLE);

// Volume is still at its maximum
BKTrackSetAttr (& track, BK_VOLUME, 0.5 * BK_MAX_VOLUME);

// Track is muted
BKTrackSetAttr (& track, BK_VOLUME, 0);

// Master volume does still work
BKTrackSetAttr (& track, BK_MASTER_VOLUME, 0.3 * BK_MAX_VOLUME);
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-triangle.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-triangle.mp3" | prepend: site.baseurl }}">Triangle Wave</a></div>
	</div>
</div>

To enable the volume attribute's normal behaviour anyway, the attribute `BK_TRIANGLE_IGNORES_VOLUME` can be set to 0:

{% highlight c %}
// Enable normal volume behaviour
BKTrackSetAttr (& track, BK_TRIANGLE_IGNORES_VOLUME, 0);
{% endhighlight %}

## Noise

Noise is a square wave whose phase amplitudes are randomly either 0 or at their maximum volume. This is controlled by a 16 bit random generator, which means that the noise pattern is repeated after 65536 phases. This can be heard on high notes.

*Interestingly, the random pattern contains a part which could be identified as a ghost voice.* 👻

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-noise.mp3" | prepend: site.baseurl }}" class="button">
			Noise Test
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-noise.mp3" | prepend: site.baseurl }}">Noise Test</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-noise-ghost.mp3" | prepend: site.baseurl }}" class="button">
			Ghost Voice
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-noise-ghost.mp3" | prepend: site.baseurl }}">Ghost Voice</a></div>
	</div>
</div>

## Sawtooth Wave

`BK_SAWTOOTH` has 7 phases.

TODO

{% highlight text %}
    ____
   |    |____
   |         |____
   |              |____
   |                   |____
   |                        |____
0 -|_____________________________|____
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-sawtooth.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-sawtooth.mp3" | prepend: site.baseurl }}">Sawtooth Wave</a></div>
	</div>
</div>

## Sine Wave

`BK_SINE` has 32 phases.

TODO

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-sine.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-sine.mp3" | prepend: site.baseurl }}">Sine Wave</a></div>
	</div>
</div>

## Custom Waveforms

Custom waveforms can have an arbitary number of phases, but an absurd high number could create unwanted effects. Numbers around 8 and 32 are optimal. The number of phases does not affect the pitch. However, the waveform itself could contain overtones which would increase the pitch.

The following is an example waveform that sounds like the vocal "A". It has 13 phases and, for simplification, its amplitude has only a resolution of 4 positive and negative values.

{% highlight text %}
+4 |    ||             || ||    ||    ||
+3 |    ||       ||    || || || ||    ||
+2 |    ||    || ||    || || || ||    ||
+1 |    ||    || ||    || || || ||    ||
 0 ++--+--+--+--+--+--+--+--+--+--+--+--+--+
-1 | ||
-2 |
-3 |
-4 |
   ++--+--+--+--+--+--+--+--+--+--+--+--+--+
      0  1  2  3  4  5  6  7  8  9 10 11 12
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-a.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-a.mp3" | prepend: site.baseurl }}">Waveform "A"</a></div>
	</div>
</div>

Custom waveforms are wrapped into `BKData` objects. These objects can then be set to multiple tracks as `BK_WAVEFORM` pointer attributes.

*Like all `BKData` objects, they must exist as long as some tracks are using them. In the code below the declaration is on the stack only for demonstration. They should be declared globally or wrapped into other objects which exist outside of the stack.*

{% highlight c %}
BKInt numPhases = 13;

// Waveform phases
BKFrame phases [numPhases] = {
	-1, +4, 0, +2, +3, 0, +4, +4, +3, +4, 0, +4, 0,
};

// Data object used to store waveform
// Do not define this object on the stack like here!
// Make it global or wrap it into another object
BKData waveform;

// Initialize data object and copy waveform phases
BKDataInitWithFrames (& waveform, phases, numPhases, 1, 1);

// Normalize phases to maximum amplitude
BKDataNormalize (& waveform);

// Set data object as waveform
BKTrackSetPtr (& track, BK_WAVEFORM, & waveform);
{% endhighlight %}

`BKDataNormalize` is used to expand the amplitudes to their maximum values of `BK_MAX_VOLUME` and `-BK_MAX_VOLUME`, respectively. Otherwise the waveform is not audible or the volume range cannot be used completely.

Of course, the phases could already be declared with their maximum amplitudes; this is only for readability.

## Unsetting Waveforms

A waveform cannot be unset from a track, instead it has to be set to another one. This could be another custom waveform or a default one:

{% highlight c %}
// Set a default waveform again
BKTrackSetAttr (& track, BK_WAVEFORM, BK_TRIANGLE);
{% endhighlight %}
