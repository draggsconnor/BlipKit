---
layout: doc
title: Arpeggio
full_title: Arpeggio Notes
order: 60
---

Arpeggio is used to play multiple notes repeatedly after each other. They are only played for a short time, which gives the feeling of multiple notes playing at the same time. This makes it a good way to play chords for example, as the notes are played relatively to the note played by the track.

{% highlight c %}
BKInt arpeggio [4] = {3, 0, -5 * BK_FINT20_UNIT, 3 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}

This defines an array with 3 arpeggio notes in which the first element defines the number of notes. The first note is the base note, the second is 5 halftones below and the third is 3 haltones above the base note. The note values itself are [fixed-point numbers](../fixed-point-numbers/) which makes it possible to defined fractional notes.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/arpeggio/arpeggio-minor.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Minor
		</a>
		<div class="label"><a href="{{ "/assets/sound/arpeggio/arpeggio-minor.mp3" | prepend: site.baseurl }}">Arpeggio Minor</a></div>
	</div>
</div>

{% highlight c %}
BKInt arpeggio [3] = {2, 0, -0.5 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}

This will play the base note and another note a half of a haltone below the basenote.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/arpeggio/arpeggio-pitch.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Pitch
		</a>
		<div class="label"><a href="{{ "/assets/sound/arpeggio/arpeggio-pitch.mp3" | prepend: site.baseurl }}">Arpeggio Pitch</a></div>
	</div>
</div>

Arpeggio is disabled with NULL or by setting the number of notes to 0.

## Speed

Each note is played for 4 ticks by default. This can be changed with the attribute `BK_ARPEGGIO_DIVIDER`:

{% highlight c %}
BKTrackSetAttr (& track, BK_ARPEGGIO_DIVIDER, 12);
{% endhighlight %}

This plays each note for 12 ticks, for example.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/arpeggio/arpeggio-minor-12-ticks.mp3" | prepend: site.baseurl }}" class="button">
			Arpeggio Minor
		</a>
		<div class="label"><a href="{{ "/assets/sound/arpeggio/arpeggio-minor-12-ticks.mp3" | prepend: site.baseurl }}">Arpeggio Minor with 12 Ticks</a></div>
	</div>
</div>

## Pitch shifting

Arpeggio notes can be used to create a pitch shift. For example, using only a single note with the value `-12 * BK_FINT20_UNIT` would lower the track's pitch by 1 octave.

{% highlight c %}
BKInt arpeggio [2] = {1, -12 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}
