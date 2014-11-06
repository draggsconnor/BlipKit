---
layout: doc
title: Fixed-Point Numbers
order: 100
description: Fixed-point numbers are used to represent floating point numbers in form of integers.
---

Fixed-point numbers are used to represent floating point numbers in form of integers. They have some advantages in certain situations. However, the downside is that they are limited to a relatively small value range, depending on the desired precision.

The library defines a type `BKFInt20` and its unsigned variant `BKFUInt20`. This is a 32 bit fixed-point number which has its integer part in the upper 12 bits and the fractional part in the lower 20 bits. Its absolute integer value is 4095 for the unsigned version and 2047 for the signed one, respectively.

{% highlight text %}
BKFInt20, BKFUInt20

+-------------------------------------------------+
|                 32 bit integer                  |
+------------------+------------------------------+
| int part 12 bits |   fractional part 20 bits    |
+------------------+------------------------------+
{% endhighlight %}

## Calculation Examples

The following expression is frequently used in the code examples:

{% highlight c %}
BK_C_3 * BK_FINT20_UNIT
{% endhighlight %}

This means that `BK_C_3` (which has the value 36) is multiplied by the fixed-point fractional part which is expressed by `BK_FINT20_UNIT`. The result is a integer that is shifted by 20 bits to the left, so its value is now in the upper 12 bits of the 32 bit integer.

MORE TODO

## Volume and Frame Values

Volume and frame values (amplitudes) are also fixed-point numbers. They are expressed by the type `BKFrame` which is a 16 bit signed integer that has only a fractional part of 15 bits.

{% highlight text %}
BKFrame

+----------------------------------------------------+
|                   32 bit integer                   |
+--------------------------+-------------------------+
|          unused          | fractional part 15 bits |
+--------------------------+-------------------------+
{% endhighlight %}

This allows to multiply two volume or amplitude values and shift the result by 15 bits to the right to get the multiplied value.

Anyway, volume values are expressed with the type `BKInt` to allow the multiplication of two volume values and shifted the result with `BK_VOLUME_SHIFT` to create the fractional value.

{% highlight c %}
BKInt volume1 = 21900;
BKInt volume2 = 16500;

// = 11027
BKInt volume = (volume1 * volume2) >> BK_VOLUME_SHIFT;
{% endhighlight %}

MORE TODO

## References

* [Floating Point/Fixed-Point Numbers](http://en.wikibooks.org/wiki/Floating_Point/Fixed-Point_Numbers) - wikibooks.org
* [Fixed-Point Numbers](http://www.coranac.com/tonc/text/fixed.htm) - coranac.com
