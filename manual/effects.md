---
layout: doc
title: Effects
order: 40
---

Effects are used to "animate" certain track attributes. *Slide* effects "slide" their corresponding track attribute to a new value within a given time (e.g. *portamento* which slides to a new note). *Interval* effects periodicaly lower and/or raise their attribute values by a given amount and interval (e.g. *tremolo* which reduces the volume periodically). Time periods are specified in number of [ticks](../clocks-and-dividers/).

Enabling an effect will begin updating the corresponding track attribute over the given time. Setting new values for an effect before its current slide period has finished will start the new slide period at the current interpolated values.

Disabling an effect before its current slide period has finished will set the slide's end value immediately. Generally, all effects can be disabled by setting their first argument to 0.

- [Volume Slide](#volume-slide)
- [Panning Slide](#panning-slide)
- [Portamento (Note Slide)](#portamento-note-slide)
- [Tremolo](#tremolo)
- [Vibrato](#vibrato)

## Volume Slide

`BK_EFFECT_VOLUME_SLIDE` sets the number of ticks in which `BK_VOLUME` is sliding to its new value.

{% highlight c %}
BKInt ticks = 120;

// Set volume slide
BKTrackSetAttr (& track, BK_EFFECT_VOLUME_SLIDE, ticks);
// Or
BKTrackSetEffect (& track, BK_EFFECT_VOLUME_SLIDE, & ticks, sizeof (ticks));

// BK_VOLUME now slides from its current value to the new value within 120 ticks
BKTrackSetAttr (& track, BK_VOLUME, 0.125 * BK_MAX_VOLUME);
{% endhighlight %}

 The effect is disabled with 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-volume-slide.mp3" | prepend: site.baseurl }}" class="button">
			Volume Slide Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-volume-slide.mp3" | prepend: site.baseurl }}">Volume Slide Effect</a></div>
	</div>
</div>

## Panning Slide

`BK_EFFECT_PANNING_SLIDE` sets the number of ticks in which `BK_PANNING` is sliding to its new value.

{% highlight c %}
BKInt ticks = 120;

// Set panning
BKTrackSetAttr (& track, BK_PANNING, -0.5 * BK_MAX_VOLUME);

// Set panning slide
BKTrackSetAttr (& track, BK_EFFECT_PANNING_SLIDE, ticks);
// Or
BKTrackSetEffect (& track, BK_EFFECT_PANNING_SLIDE, & ticks, sizeof (ticks));

// BK_PANNING now slides from its current value to the new value within 120 ticks
BKTrackSetAttr (& track, BK_PANNING, 0.5 * BK_MAX_VOLUME);
{% endhighlight %}

The effect is disabled with 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-panning-slide.mp3" | prepend: site.baseurl }}" class="button">
			Panning Slide Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-panning-slide.mp3" | prepend: site.baseurl }}">Panning Slide Effect</a></div>
	</div>
</div>

## Portamento (Note Slide)

`BK_EFFECT_PORTAMENTO` sets the number of ticks in which `BK_NOTE` is sliding to its new value. If no note is set at the moment, the new note is set immediately.

{% highlight c %}
BKInt ticks = 120;

// Set portamento
BKTrackSetAttr (& track, BK_EFFECT_PORTAMENTO, ticks);
// Or
BKTrackSetEffect (& track, BK_EFFECT_PORTAMENTO, & ticks, sizeof (ticks));

// Set note
BKTrackSetAttr (& track, BK_NOTE, BK_G_2 * BK_FINT20_UNIT);

// BK_NOTE now slides from its current value to the new value within 120 ticks
BKTrackSetAttr (& track, BK_NOTE, BK_C_3 * BK_FINT20_UNIT);
{% endhighlight %}

The effect is disabled with 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-portamento.mp3" | prepend: site.baseurl }}" class="button">
			Portamento Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-portamento.mp3" | prepend: site.baseurl }}">Portamento Effect</a></div>
	</div>
</div>

## Tremolo

`BK_EFFECT_TREMOLO` reduces the volume periodically by the given amount relatively to the current volume in the given number of ticks.

One tremolo cycle consist of 2 phases, where in the first phase the volume is reduced by the given amount and in the second phase raised up again to the current value.

{% highlight c %}
BKInt tremolo [2] = {24, 0.5 * BK_VOLUME};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo, sizeof (tremolo));
{% endhighlight %}

This reduces the volume to 50% of its current value within 24 ticks and raises it up again within another 24 ticks.

{% highlight text %}
Current volume ------\          /---- repeated
                      \        /
             1 sliding \      / 2 sliding
               down     \    /     up
                         \  /
0.5 of current volume ----\/---------
{% endhighlight %}

The effect is disabled with a NULL pointer or by setting its first argument to 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-tremolo.mp3" | prepend: site.baseurl }}" class="button">
			Tremolo Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-tremolo.mp3" | prepend: site.baseurl }}">Tremolo Effect</a></div>
	</div>
</div>

### Sliding to new values

Normally, the effect values are set immediately. However, a third argument sets the number of ticks in which `BK_EFFECT_TREMOLO` is sliding to its new values.

{% highlight c %}
BKInt tremolo1 [2] = {24, 0.5 * BK_VOLUME};
BKInt tremolo2 [3] = {8, 1.0 * BK_VOLUME, 120};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo1, sizeof (tremolo1));
BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo2, sizeof (tremolo2));
{% endhighlight %}

First, the tremolo effect is set immediately without sliding (`tremolo1`). Then the effect is set to slide to the new values of `tremolo2` within 120 ticks.

When setting a new slide before the current one has finished, the slide is started at the current interpolated values.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-tremolo-slide.mp3" | prepend: site.baseurl }}" class="button">
			Tremolo Effect with Slide
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-tremolo-slide.mp3" | prepend: site.baseurl }}">Tremolo Effect with Slide</a></div>
	</div>
</div>

## Vibrato

`BK_EFFECT_VIBRATO` raises and lowers the pitch periodically by the given number of halftones relatively to the current note in the given number of ticks.

One vibrato cycle consist of 4 phases. In the first phase the pitch is raised up by the given amount and lowered again to 0 in the second phase. The next two phases are the mirrowed version of the first two, in which the pitch is first lowered by the given amount and the raised up to 0 again.

{% highlight c %}
BKInt vibrato [2] = {12, 0.6 * BK_FINT20_UNIT};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato, sizeof (vibrato));
{% endhighlight %}

This first raises the pitch up by 3 halftones within 12 ticks and lowers it again within another 12 ticks; followed by the mirrowed version in which the pitch is lowered by 3 halftones within 12 ticks and raised up again within another 12 ticks.

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

The effect is disabled with a NULL pointer or by setting its first argument to 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-vibrato.mp3" | prepend: site.baseurl }}" class="button">
			Vibrato Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-vibrato.mp3" | prepend: site.baseurl }}">Vibrato Effect</a></div>
	</div>
</div>

### Sliding to new values

Normally, the effect values are set immediately. However, a third argument sets the number of ticks in which `BK_EFFECT_VIBRATO` is sliding to its new values.

{% highlight c %}
BKInt vibrato1 [2] = {36, 3 * BK_FINT20_UNIT};
BKInt vibrato2 [3] = {6, 0.6 * BK_FINT20_UNIT, 240};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato1, sizeof (vibrato1));
BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato2, sizeof (vibrato2));
{% endhighlight %}

First, the vibrato effect is set immediately without sliding (`vibrato1`). Then the effect is set to slide to the new values of `vibrato2` within 240 ticks.

When setting a new slide before the current one has finished, the slide is started at the current interpolated values.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-vibrato-slide.mp3" | prepend: site.baseurl }}" class="button">
			Vibrato Effect with Slide
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-vibrato-slide.mp3" | prepend: site.baseurl }}">Vibrato Effect with Slide</a></div>
	</div>
</div>
