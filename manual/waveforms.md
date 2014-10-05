---
layout: doc
title: Waveforms
order: 30
---

Waveforms consist of a certain number of *phases*. Each phase is a value in the range from `-BK_MAX_VOLUME` to `+BK_MAX_VOLUME`. When playing a note, the waveform and with it its phases are scaled, so that the note is in the right pitch. Tracks have some predefined waveforms which are typical for old soundchips.

## Square

`BK_SQUARE` has 16 phases. The duty cycle attribute `BK_DUTY_CYCLE` defines the length of the wave peak. By default, this value is 4, which accords to a duty cycle of 25%. The value can range between 1 and 15:

{% highlight text %}
    +-----+
    |12.5%|
0 - +     +-----------------------------------------+

    +-----------+
    |    25%    |
0 - +           +-----------------------------------+

    +-----------------------+
    |         50%           |
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

## Triangle

`BK_TRIANGLE` has 32 phases and is the only waveform which is not affected by the volume by default. It is either 0 or at its maximum for values greater than 0. This is because volume changes of triangle-like or sine-like waveforms do not sound very good.

{% highlight text %}
              __
            _|  |_
          _|      |_
        _|          |_
      _|              |_
    _|                  |_
  _|                      |_
_|__________________________|_______________________________
                               |_                        _|
                                 |_                    _|
                                   |_                _|
                                     |_            _|
                                       |_        _|
                                         |_    _|
                                           |__|
{% endhighlight %}

The waveform is shifted to the left by 8 phases which is to use negative amplitudes as well to reduce potential overflows when mixing tracks.

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

To enable the volume attribute's normal behaviour anyway, the `BK_TRIANGLE_IGNORES_VOLUME` attribute can be set to 0:

{% highlight c %}
// Enable normal volume behaviour
BKTrackSetAttr (& track, BK_TRIANGLE_IGNORES_VOLUME, 0);
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-triangle.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-triangle.mp3" | prepend: site.baseurl }}">Triangle Wave</a></div>
	</div>
</div>

## Noise

Noise is a square wave whose phase amplitudes are randomly either 0 or at their full volume. This is controlled by a 16 bit random generator, which means that the noise pattern is repeated after 65536 phases. This can be heard on high notes.

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

## Sawtooth

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-sawtooth.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-sawtooth.mp3" | prepend: site.baseurl }}">Sawtooth Wave</a></div>
	</div>
</div>

## Sine

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-sine.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-sine.mp3" | prepend: site.baseurl }}">Sine Wave</a></div>
	</div>
</div>

## Custom waveforms

There is the possibility to define custom waveforms. The following example waveform sounds like the vocal "A":

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

It has 13 phases which, for simplification, have a resolution of 4 steps. Waveforms can have an arbitary number of phases, but an absurd high number could create unwanted effects. Numbers around 8 and 64 are optimal.

The number of phases doesn't affect the pitch. However, the waveform itself could contain overtones which would increase the pitch.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/waveforms/waveform-a.mp3" | prepend: site.baseurl }}" class="button">
			Waveform "A"
		</a>
		<div class="label"><a href="{{ "/assets/sound/waveforms/waveform-a.mp3" | prepend: site.baseurl }}">Waveform "A"</a></div>
	</div>
</div>

Waveform phases are wrapped into `BKData` objects. These objects can then be set to multiple tracks as `BK_WAVEFORM` pointer attributes.

*Like all `BKData` objects, they must exist as long as some tracks are using them. The example below declares it on the stack which is only for demonstration. Declare it globally or wrap it into another object which exists outside of the stack.*

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

`BKDataNormalize` is used to expand the phases to their maximum values between `BK_MAX_VOLUME` and `-BK_MAX_VOLUME`, respectively. Otherwise, the waveform is not audible or the volume range can't be used completely.

Of course, the phases could already be defined with the maximum values, but in this case it's more readable.

## Unsetting waveforms

A waveform can't be unset from a track, instead it has to be set to another one. This could be another custom waveform or a default one:

{% highlight c %}
// Set a default waveform again
BKTrackSetAttr (& track, BK_WAVEFORM, BK_TRIANGLE);
{% endhighlight %}
