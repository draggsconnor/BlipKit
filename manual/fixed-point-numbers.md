---
layout: doc
title: Fixed-Point Numbers
order: 80
---

Fixed-point numbers are used to represent floating point numbers in form of integers. They have some advantages in certain situations. However, the downside is that they are limited to a certain value range.

This library defines a type `BKFUInt20` and its signed variant `BKFInt20` to declare fixed-point numbers. This is a 32 bit integer which has the integer part in the upper 12 bits and the fractional part in the lower 20 bits. Its absolute integer value is 4095 for the unsigned version and 2047 for the signed one which.

{% highlight text %}
+------------------+------------------------------+
| int part 12 bits |      frac part 20 bits       |
+------------------+------------------------------+
{% endhighlight %}

## Calculation examples

TODO

## References

* [Floating Point/Fixed-Point Numbers](http://en.wikibooks.org/wiki/Floating_Point/Fixed-Point_Numbers) - wikibooks.org
* [Fixed-Point Numbers](http://www.coranac.com/tonc/text/fixed.htm) - coranac.com
