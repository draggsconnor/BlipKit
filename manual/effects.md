---
layout: doc
title: Effects
order: 40
---

Effects are used to "animate" certain track attributes. Single argument effects can be set with the normal attribute setter and getter functions. For effects with multiple arguments there are special functions: `BKTrackSetEffect` is used for setting effects and `BKTrackGetEffect` for reading effect values.

## Volume slide

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

## Panning slide

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

## Portamento

`BK_EFFECT_PORTAMENTO` sets the number of ticks in which `BK_NOTE` is sliding to its new value. If no note is set at the moment the new note is set immediately.

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

`BK_EFFECT_TREMOLO` reduces the volume relatively to the current volume by the given amount repeatedly in the given number of ticks.

One tremolo cycle consist of 2 phases. In the first phase the volume is reduced by the given amount. In the second phase the volume is raised up to the current volume again.

{% highlight c %}
BKInt tremolo [2] = {24, 0.5 * BK_VOLUME};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo, sizeof (tremolo));
{% endhighlight %}

This would reduce the volume to 50% (1.0 - 0.5) of its current value within 24 ticks and raise it again within another 24 ticks.

{% highlight text %}
Current volume ------\          /---- repeated
                      \        /
             1 sliding \      / 2 sliding
               down     \    /     up
                         \  /
0.5 of current volume ----\/---------
{% endhighlight %}

The effects is disabled with NULL or by setting its first argument to 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-tremolo.mp3" | prepend: site.baseurl }}" class="button">
			Tremolo Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-tremolo.mp3" | prepend: site.baseurl }}">Tremolo Effect</a></div>
	</div>
</div>

### Sliding values

The number of ticks and volume reduction can also be slided. A third argument sets the number of ticks in which `BK_EFFECT_TREMOLO` is sliding to its new values.

{% highlight c %}
BKInt tremolo1 [2] = {24, 0.5 * BK_VOLUME};
BKInt tremolo2 [3] = {8, 1.0 * BK_VOLUME, 120};

BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo1, sizeof (tremolo1));
BKTrackSetEffect (& track, BK_EFFECT_TREMOLO, tremolo2, sizeof (tremolo2));
{% endhighlight %}

First, the tremolo effect is set immediately without sliding (`tremolo1`). Then with the second call, the effect is set to slide to the new values of `tremolo2` within 120 ticks. If setting new values to be slided to before the current slide has finished, the slide is started again from the current interpolated values.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-tremolo-slide.mp3" | prepend: site.baseurl }}" class="button">
			Tremolo Effect with Slide
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-tremolo-slide.mp3" | prepend: site.baseurl }}">Tremolo Effect with Slide</a></div>
	</div>
</div>

## Vibrato

`BK_EFFECT_VIBRATO` raises and lowers the pitch relatively to the current note by the given number of halftones repeatedly in the given number of ticks.

One vibrato cycle consist of 4 phases. In the first phase the pitch is raised by the given amount. In the second phase the pitch is lowered to 0 again. The next two phases are the mirrowed variant of the first two, in which the pitch is first lowered by the given amount and the raised up to 0 again.

{% highlight c %}
BKInt vibrato [2] = {12, 0.6 * BK_FINT20_UNIT};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato, sizeof (vibrato));
{% endhighlight %}

This would first raise the pitch by 3 halftones within 12 ticks and lower it again within another 12 ticks, followed by the mirrowed variant in which the pitch is lowered by 3 halftones within 12 ticks and raised again within another 12 ticks.

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

The effects is disabled with NULL or by setting its first argument to 0.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-vibrato.mp3" | prepend: site.baseurl }}" class="button">
			Vibrato Effect
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-vibrato.mp3" | prepend: site.baseurl }}">Vibrato Effect</a></div>
	</div>
</div>

### Sliding values

The number of ticks and pitch amount can also be slided. A third argument sets the number of ticks in which `BK_EFFECT_VIBRATO` is sliding to its new values.

{% highlight c %}
BKInt vibrato1 [2] = {36, 3 * BK_FINT20_UNIT};
BKInt vibrato2 [3] = {6, 0.6 * BK_FINT20_UNIT, 240};

BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato1, sizeof (vibrato1));
BKTrackSetEffect (& track, BK_EFFECT_VIBRATO, vibrato2, sizeof (vibrato2));
{% endhighlight %}

First, the vibrato effect is set immediately without sliding (`vibrato1`). Then with the second call, the effect is set to slide to the new values of `vibrato2` within 240 ticks. If setting new values to be slided to before the current slide has finished, the slide is started again from the current interpolated values.

<div class="buttons">
	<div class="player" data-volume="0.7">
		<a href="{{ "/assets/sound/effects/effect-vibrato-slide.mp3" | prepend: site.baseurl }}" class="button">
			Vibrato Effect with Slide
		</a>
		<div class="label"><a href="{{ "/assets/sound/effects/effect-vibrato-slide.mp3" | prepend: site.baseurl }}">Vibrato Effect with Slide</a></div>
	</div>
</div>
