---
layout: doc
title: Instruments
order: 50
---

Instruments create envelopes over certain track attributes when a note is playing. Each envelope has thee phases: an *attack phase* which is played when the note is set, a *sustain phase* which is repeated after the attack phase has finished and as long as the note is set, and a *release phase* which will be played when the note is released.

{% highlight text %}
+--------+-----------------+---------+
| Attack | <-- Sustain --> | Release |
+--------+-----------------+---------+
{% endhighlight %}

The attack phase is only triggered when the note was not set before, so changing the note without releasing it first will not trigger the attack phase again. Instead, the sustain phase keeps repeating. The note, [arpeggio sequences](../arpeggio/) and all [effects](../effects/) will continue playing until each release phase of each envelope has finished.

Not all phases have to be defined, here are some meaningful combinations:

All phases: the behaviour is like in the description above.

{% highlight text %}
+--------+-----------------+---------+
| Attack | <-- Sustain --> | Release |
+--------+-----------------+---------+
{% endhighlight %}

No attack phase: the sustain phase is repeated right after a note is set.

{% highlight text %}
+-----------------+---------+
| <-- Sustain --> | Release |
+-----------------+---------+
{% endhighlight %}

No release phase: the note will stop immediately after its release.

{% highlight text %}
+--------+-----------------+
| Attack | <-- Sustain --> |
+--------+-----------------+
{% endhighlight %}

Sustain phase only: the sustain phase is repeated right after a note is set and stops immediately after its release.

{% highlight text %}
+-----------------+
| <-- Sustain --> |
+-----------------+
{% endhighlight %}

Attack phase only: the attack phase is played first then its last value is hold as long as the note is set.

{% highlight text %}
+--------+
| Attack |
+--------+
{% endhighlight %}

An envelope (further also called *sequence*) is simply an arrays of integers (*steps*) whose value ranges are dependant of the envelope type. The phase lengths are defined by the start and length of the sustain phase.

{% highlight c %}
BKInt volume [12] = {
	0.25 * BK_MAX_VOLUME, 0.5 * BK_MAX_VOLUME, 0.75 * BK_MAX_VOLUME, 1.0 * BK_MAX_VOLUME,
	1.0 * BK_MAX_VOLUME, 0.7 * BK_MAX_VOLUME, 0.5 * BK_MAX_VOLUME,
	0.8 * BK_MAX_VOLUME, 0.6 * BK_MAX_VOLUME, 0.4 * BK_MAX_VOLUME, 0.2 * BK_MAX_VOLUME, 0,
};

BKInt pitch [4] = {
	12 * BK_FINT20_UNIT, 12 * BK_FINT20_UNIT,
	0,
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

This initializes an instrument object with a volume and pitch sequence and sets it as track instrument. Instruments can be set to multiple tracks, and sequences can even be updated when an instrument is set to a track. `BKInstrumentSetSequence` sets or updates the values for the specified sequence type.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-volume.mp3" | prepend: site.baseurl }}" class="button">
			Volume Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-volume.mp3" | prepend: site.baseurl }}">Volume Envelope</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-arpeggio.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-arpeggio.mp3" | prepend: site.baseurl }}">Arpeggio Envelope</a></div>
	</div>
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/instruments/instrument-volume-arpeggio.mp3" | prepend: site.baseurl }}" class="button">
			Volume and Arpeggio Envelope
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/instrument-volume-arpeggio.mp3" | prepend: site.baseurl }}">Volume and Arpeggio Envelope</a></div>
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

The sequence phases are defined with the last 3 arguments of `BKInstrumentSetSequence`. `length` defines the number of values of the complete sequence. `sustainOffset` defines the start offset at which the sustain phase begins and `sustainLength` its length. The part after `sustainOffset` + `sustainLength` is the release part. It is allowed to have no length, which simply means that the sequence has no release phase. When the sustain phase has no length and its offset is equal to the length, the sequence has only an attack phase. Of course, the sustain phase can also cover the whole sequence and repeat it.

The following sequence types are defined:

<dl>
	<dt><var>BK_SEQUENCE_VOLUME</var></dt>
	<dd>Volume sequence. Multiplies the volume by its current value.</dd>
	<dt><var>BK_SEQUENCE_PANNING</var></dt>
	<dd>Panning sequence. Sets the panning of the track relative to its current value.</dd>
	<dt><var>BK_SEQUENCE_PITCH</var></dt>
	<dd>Arpggio sequence. Sets the pitch of the note relative to its current value.</dd>
	<dt><var>BK_SEQUENCE_DUTY_CYCLE</var></dt>
	<dd>Duty cycle sequence. Sets the duty cycle of the square wave, whereas it has no effect on other waveforms. Values of 0 do not change the current duty cycle.</dd>
</dl>

[Examples]

## Speed

Each sequence step is played for 4 ticks by default. This can be changed with the attribute `BK_INSTRUMENT_DIVIDER`:

{% highlight c %}
// Every step is now played for 8 ticks
BKTrackSetAttr (& track, BK_INSTRUMENT_DIVIDER, 8);
{% endhighlight %}

## Extended envelopes

There is another type of envelope which has a variable step size and whose values are interpolated between the steps. It is not affected by the `BK_INSTRUMENT_DIVIDER` attribute.

{% highlight c %}
BKSequencePhase volume [] = {
	{10, 1 * BK_MAX_VOLUME},
	{20, 0.5 * BK_MAX_VOLUME},
	{4,  0.6 * BK_MAX_VOLUME},
	{25, 0.01 * BK_FINT20_UNIT},
	{15, 1 * BK_MAX_VOLUME},
	{30, 0},
};

BKSequencePhase pitch [] = {
	{0, -12 * BK_FINT20_UNIT},
	{24, 0},
	{12, -0.3 * BK_FINT20_UNIT},
	{12, 0.3 * BK_FINT20_UNIT},
	{30, 0},
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
