---
layout: doc
title: Arpeggio
full_title: Arpeggio sequences
order: 60
---

As a track can only play one note at a time, arpeggio sequences can be used to get the feeling of multiple notes. A maximum of 8 notes can be defined to be played repeatedly after each other. Each note is played for 4 ticks by default.

{% highlight c %}
BKInt arpeggio [4] = {3, 0, 3 * BK_FINT20_UNIT, 7 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}

This defines an array with 3 arpeggio notes in which the first element defines the number of notes. The first note is 0, the second 3, and the third 7 haltones above the base note. Notes are defined relatively to the note played by the track, so negative values are allowed too. The note values itself have the type `BKFInt20`, which is a fixed-pointer number. This makes it possible to defined fractional notes.

{% highlight c %}
BKInt arpeggio [3] = {2, 0, -0.5 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}

This will play the base note and another note a half of a haltone below the basenote.

## Pitch shifting

Arpeggio notes can also be used to create a pitch shift. For example, using only a single note with the value `-12 * BK_FINT20_UNIT` would lowered the entire track pitch by 1 octave.

{% highlight c %}
BKInt arpeggio [2] = {1, -12 * BK_FINT20_UNIT};

BKTrackSetPtr (& track, BK_ARPGGIO, arpeggio);
{% endhighlight %}
