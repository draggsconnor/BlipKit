---
layout: doc
title: Effects
order: 40
---

Like other attributes, effects can be set with the attribute functions. However, for effects with multiple arguments there are special functions for reading and writing: `BKTrackSetEffect` is used for setting effect values and `BKTrackGetEffect`is used for reading effect values.

## Volume slide

`BK_EFFECT_VOLUME_SLIDE` sets the number of ticks in which `BK_VOLUME` is sliding to the new value. The effect is disabled with 0.

{% highlight c %}
BKInt slide = 24;

BKTrackSetAttr (& track, BK_EFFECT_VOLUME_SLIDE, slide);
// or
BKTrackSetEffect (& track, BK_EFFECT_VOLUME_SLIDE, & slide, sizeof (slide));
{% endhighlight %}

## Panning slide

`BK_EFFECT_PANNING_SLIDE` sets the number of ticks in which `BK_PANNING` is sliding to the new value. The effect is disabled with 0.

{% highlight c %}
BKInt slide = 24;

BKTrackSetAttr (& track, BK_EFFECT_PANNING_SLIDE, slide);
// or
BKTrackSetEffect (& track, BK_EFFECT_PANNING_SLIDE, & slide, sizeof (slide));
{% endhighlight %}

## Portamento

`BK_EFFECT_PORTAMENTO` sets the number of ticks in which `BK_NOTE` is sliding to the new value. The effect is disabled with 0.

{% highlight c %}
BKInt portamento = 24;

BKTrackSetAttr (& track, BK_EFFECT_PORTAMENTO, portamento);
// or
BKTrackSetEffect (& track, BK_EFFECT_PORTAMENTO, & portamento, sizeof (portamento));
{% endhighlight %}

## Tremolo

`BK_EFFECT_TREMOLO` lowers the volume by the given amount repeatedly in the given number of ticks. The effects is disabled when setting the first value to 0.

{% highlight c %}
BKInt tremolo [2] = {24, 0.25 * BK_VOLUME};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo, sizeof (tremolo));
{% endhighlight %}

{% highlight text %}
Current volume -------\          /---- repeated
                       \        /
              1 sliding \      / 2 sliding
                down     \    /     up
                          \  /
0.75 of current volume ----\/---------
{% endhighlight %}

Each tremolo phase has a duration of the given number of ticks. So one complete tremolo cycle would by 48 ticks.

### Sliding

The tremolo effect can also be slided. A third argument sets the number of ticks in which `BK_EFFECT_TREMOLO` is sliding to the new values.

{% highlight c %}
BKInt tremolo1 [2] = {24, 0.25 * BK_VOLUME};
BKInt tremolo2 [3] = {18, 1.0 * BK_VOLUME, 60};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo1, sizeof (tremolo1));
BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo2, sizeof (tremolo2));
{% endhighlight %}

First, the tremolo effect is set without sliding (`tremolo1`). Then with the second call, the effect is set to slide to the new values of `tremolo2` within 60 ticks. If setting a new slide before the current slide has finished, the slide is started again form the current interpolated values.

## Vibrato

`BK_EFFECT_VIBRATO` raises and lowers the note pitch by the given number of halftones repeatedly in the given number of ticks. The effects is disabled when setting the first value to 0.

{% highlight c %}
BKInt vibrato [2] = {24, 1 * BK_FINT20_UNIT};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato, sizeof (vibrato));
{% endhighlight %}

{% highlight text %}
                      /\
           1 sliding /  \ 2 sliding
              up    /    \   down
                   /      \
 Current note ----/        \        /---- repeated
                            \      /
                   3 sliding \    / 4 sliding
                     down     \  /     up
                               \/
{% endhighlight %}

Each vibrato phase has a duration of the given number of ticks. So one complete vibrato cycle would by 96 ticks.

### Sliding

The vibrato effect can also be slided. A third argument sets the number of ticks in which `BK_EFFECT_VIBRATO` is sliding to the new values.

{% highlight c %}
BKInt vibrato1 [2] = {24, 1 * BK_FINT20_UNIT};
BKInt vibrato2 [3] = {18, 5 * BK_FINT20_UNIT, 60};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato1, sizeof (vibrato1));
BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato2, sizeof (vibrato2));
{% endhighlight %}

First, the vibrato effect is set without sliding (`vibrato1`). Then with the second call, the effect is set to slide to the new values of `vibrato2` within 60 ticks. If setting a new slide before the current slide has finished, the slide is started again form the current interpolated values.
