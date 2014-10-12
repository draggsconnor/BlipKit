---
layout: doc
title: Arpeggio Notes
order: 60
---

- [Note Length](#note-length)
- [Pitch Shifting](#pitch-shifting)

Arpeggio notes are used to play multiple notes fast and repeatedly after each other. As they are only played for a short time, this gives the impression of multiple notes playing at the same time. This makes it a good way to play chords for example, as the notes are played relatively to the track note. They can be used independently of [pitch envelopes](../instruments).

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/arpeggio/arpeggio-minor.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Minor
		</a>
		<div class="label"><a href="{{ "/assets/sound/arpeggio/arpeggio-minor.mp3" | prepend: site.baseurl }}">Arpeggio Minor</a></div>
	</div>
</div>

{% highlight c %}
BKInt arpeggio [4] = {3, 0, -5 * BK_FINT20_UNIT, 3 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}

This defines an array with 3 arpeggio notes in which the first element defines the number of notes. The first note is the base note itself (0 halftones away from the track note), the second is 5 halftones below and the third is 3 haltones above the base note. The note values are [fixed-point numbers](../fixed-point-numbers/) which makes it possible to define fractional notes.

Arpeggio notes are disabled with a NULL pointer or by setting the number of notes to 0.

## Note Length

Each note is played for 4 ticks by default. This can be changed with the attribute `BK_ARPEGGIO_DIVIDER`. This plays each note for 12 ticks:

{% highlight c %}
BKTrackSetAttr (& track, BK_ARPEGGIO_DIVIDER, 12);
{% endhighlight %}

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/arpeggio/arpeggio-minor-12-ticks.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Minor
		</a>
		<div class="label"><a href="{{ "/assets/sound/arpeggio/arpeggio-minor-12-ticks.mp3" | prepend: site.baseurl }}">Arpeggio Minor with 12 Ticks</a></div>
	</div>
</div>

## Pitch Shifting

Arpeggio notes can be used to make a pitch shift for the whole track. For example, using only a single note with the value `-12 * BK_FINT20_UNIT` would lower the track's pitch by 1 octave.

{% highlight c %}
BKInt arpeggio [2] = {1, -12 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}
