---
layout: doc
title: Instruments
order: 50
description: Instruments create envelopes over certain track attributes. An envelope changes its corresponding track attribute stepwise relatively to the current attribute value while the note is playing.
---

Instruments create envelopes over certain track attributes. An envelope changes its corresponding track attribute stepwise relatively to the current attribute value while the note is playing. (An exception is the *duty cycle* envelope, which sets absolute values).

Each envelope has 3 *phases*, where each phase has a certain number of *steps*. The *attack phase* is played when the note is set, the *sustain phase* is played after the attack phase and repeated while the note is set, and the *release phase* is be played when the note is released.

{% highlight text %}
+--------+-----------------+---------+
| Attack | <-- Sustain --> | Release |
+--------+-----------------+---------+
{% endhighlight %}

The attack phase is only triggered the first time the note is set, so changing the note without releasing it first will not trigger the attack phase again. Instead the sustain phase keeps repeating and a possibly set [portamento effect](../effects/#portamento-note-slide) can be used.

The note, [arpeggio notes](../arpeggio/) and all [effects](../effects/) will continue playing until all release phases of each envelope are finished. If an envelope has no release phase or is shorter than others in the same instrument, its last value is kept until all envelopes are finished.

- [Envelope Phases](#envelope-phases)
- [Setting Envelopes](#setting-envelopes)
- [Step Size](#step-size)
- [Extended Envelopes](#extended-envelopes)
- [ADSR Envelopes](#adsr-envelopes)

## Envelope Phases

What follows are combinations of envelope phases and their behaviour:

**All phases:** the attack phase is played, after that the sustain phase is repeated. The release phase is played when unsetting the note.

{% highlight text %}
+--------+-----------------+---------+
| Attack | <-- Sustain --> | Release |
+--------+-----------------+---------+
{% endhighlight %}

**No attack phase**: the sustain phase is repeated right after a note is set. The release phase is played when unsetting the note

{% highlight text %}
+-----------------+---------+
| <-- Sustain --> | Release |
+-----------------+---------+
{% endhighlight %}

**No release phase:** the attack phase is played, after that the sustain phase is repeated. The note will be muted immediately after its release.

{% highlight text %}
+--------+-----------------+
| Attack | <-- Sustain --> |
+--------+-----------------+
{% endhighlight %}

**Sustain phase only:** the sustain phase is repeated right after a note is set and will mute it immediately after its release.

{% highlight text %}
+-----------------+
| <-- Sustain --> |
+-----------------+
{% endhighlight %}

**Attack phase only:** the attack phase is played first then its last value is kept as long as the note is set.

{% highlight text %}
+--------+
| Attack |
+--------+
{% endhighlight %}

## Setting Envelopes

An envelope is simply an arrays of integers (*steps*) whose value ranges depend on the envelope type. The phase lengths are defined by the start and length of the *sustain phase*.

{% highlight c %}
BKInt volume [12] = {
	// attack
	0.25 * BK_MAX_VOLUME, 0.5 * BK_MAX_VOLUME,
	0.75 * BK_MAX_VOLUME, 1.0 * BK_MAX_VOLUME,
	// sustain
	1.0 * BK_MAX_VOLUME, 0.7 * BK_MAX_VOLUME,
	0.5 * BK_MAX_VOLUME,
	// release
	0.8 * BK_MAX_VOLUME, 0.6 * BK_MAX_VOLUME,
	0.4 * BK_MAX_VOLUME, 0.2 * BK_MAX_VOLUME,
	0,
};

BKInt pitch [4] = {
	// attack
	12 * BK_FINT20_UNIT, 12 * BK_FINT20_UNIT,
	// sustain
	0,
	// release
	-12 * BK_FINT20_UNIT,
};

// Instrument object
BKInstrument instrument;

// Initialize instrument
BKInstrumentInit (& instrument);

// Set volume sequence
BKInstrumentSetSequence (& instrument, BK_SEQUENCE_VOLUME, volume, 13, 4, 3);

// Set pitch sequence
BKInstrumentSetSequence (& instrument, BK_SEQUENCE_PITCH, pitch, 4, 2, 1);

// Set track instrument
BKTrackSetPtr (& track, BK_INSTRUMENT, & instrument);
{% endhighlight %}

This initializes an instrument object with a volume and pitch envelope and sets it to a track. Instruments can be set to multiple tracks, and envelopes can even be updated while the instrument is set to a track. `BKInstrumentSetSequence` sets or updates these values for the specified envelope.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-volume.mp3" | prepend: site.baseurl }}" class="button">
			Volume Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-volume.mp3" | prepend: site.baseurl }}">Volume Envelope</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-pitch.mp3" | prepend: site.baseurl }}" class="button">
			Pitch Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-pitch.mp3" | prepend: site.baseurl }}">Pitch Envelope</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-volume-pitch.mp3" | prepend: site.baseurl }}" class="button">
			Volume and Pitch Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-volume-pitch.mp3" | prepend: site.baseurl }}">Volume and Pitch Envelope</a></div>
	</div>
</div>

{% highlight c %}
BKInt BKInstrumentSetSequence (
	BKInstrument * instr,
	BKEnum         sequence,
	BKInt const  * values,
	BKUInt         length,
	BKInt          sustainOffset,
	BKInt          sustainLength
)
{% endhighlight %}

The offsets are defined with the last 3 arguments of `BKInstrumentSetSequence`. `length` defines the number of steps of the complete envelope. `sustainOffset` defines the start offset at which the *sustain phase* begins and `sustainLength` its length. The part after `sustainOffset` + `sustainLength` is the *release phase*. It is allowed to have no length, which simply means that the envelope has none. When the *sustain phase* has no length and its offset is equal to the length, the envelope has only an *attack phase*.

The following envelope types are defined:

<dl>
	<dt><var>BK_SEQUENCE_VOLUME</var></dt>
	<dd>Volume envelope. Multiplies the volume by its current value.</dd>
	<dt><var>BK_SEQUENCE_PANNING</var></dt>
	<dd>Panning envelope. Sets the panning relative to its current value.</dd>
	<dt><var>BK_SEQUENCE_PITCH</var></dt>
	<dd>Arpeggio envelope. Sets the note pitch relative to its current value.</dd>
	<dt><var>BK_SEQUENCE_DUTY_CYCLE</var></dt>
	<dd>Duty cycle envelope. Sets the square wave's duty cycle, whereas it has no effect on other waveforms. Values of 0 do not change the current duty cycle, which allows to change it only at specific parts of the envelope.</dd>
</dl>

[Examples]

## Step Size

Each envelope step is played for 4 ticks by default. This can be changed with the attribute `BK_INSTRUMENT_DIVIDER`:

{% highlight c %}
// Each step is now played for 8 ticks
BKTrackSetAttr (& track, BK_INSTRUMENT_DIVIDER, 8);
{% endhighlight %}

## Extended Envelopes

There is another type of envelope which has a variable step size and whose values are interpolated between the steps. Instead of single integer values, this envelopes consist of `BKSequencePhase` structs which have a *step* and *value* field. The *step* field defines the number of [ticks](../clocks-and-dividers/) in which the track attribute should slide to the next *value*. `BKInstrumentSetEnvelope` is used to set these envelopes.

`BK_INSTRUMENT_DIVIDER` has no effect on this envelope type.

{% highlight c %}
BKSequencePhase volume [6] = {
	// attack
	{10, 1 * BK_MAX_VOLUME},
	{20, 0.5 * BK_MAX_VOLUME},
	// sustain
	{4,  0.6 * BK_MAX_VOLUME},
	{25, 0.01 * BK_FINT20_UNIT},
	// release
	{15, 1 * BK_MAX_VOLUME},
	{30, 0},
};

BKSequencePhase pitch [4] = {
	// attack
	{0, -12 * BK_FINT20_UNIT},
	{24, 0},
	// sustain
	{12, 0.3 * BK_FINT20_UNIT},
	// release
	{40, -0.6 * BK_FINT20_UNIT},
};

BKInstrumentSetEnvelope (& instrument, BK_SEQUENCE_PITCH, volume, 6, 2, 2);

BKInstrumentSetEnvelope (& instrument, BK_SEQUENCE_PITCH, pitch, 4, 2, 1);
{% endhighlight %}

{% highlight c %}
BKInt BKInstrumentSetEnvelope (
	BKInstrument          * instr,
	BKEnum                  sequence,
	BKSequencePhase const * phases,
	BKUInt                  length,
	BKInt                   sustainOffset,
	BKInt                   sustainLength
)
{% endhighlight %}

## ADSR Envelopes

...

{% highlight c %}
BKInt BKInstrumentSetEnvelopeADSR (
	BKInstrument * instr,
	BKUInt         attack,
	BKUInt         decay,
	BKInt          sustain,
	BKUInt         release
)
{% endhighlight %}

...

{% highlight c %}
BKSequencePhase volume [4] = {
	{attack, BK_MAX_VOLUME},
	{decay, sustain},
	{240, sustain},
	{release, 0},
};
{% endhighlight %}
