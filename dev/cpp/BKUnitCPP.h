/**
 * Copyright (c) 2012-2014 Simon Schoenenberger
 * http://blipkit.monoxid.net/
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef _BK_UNIT_CPP_H_
#define _BK_UNIT_CPP_H_

#include "BlipKit.h"
#include "BKContextCPP.h"

namespace BlipKit
{
	class Unit;
}

class BlipKit::Unit
{

public:
	BKUnit unit;

	Unit (BKEnum waveform) { BKUnitInit (& unit, waveform); }
	
	~Unit () { BKUnitDispose (& unit); }
	
	BKInt attach (BlipKit::Context & ctx) { return BKUnitAttach (& unit, & ctx.ctx); }
	void detach (void) { BKUnitDetach (& unit); }
	
	BKInt setAttr (BKEnum attr, BKInt value) { return BKUnitSetAttr (& unit, attr, value); }
	BKInt getAttr (BKEnum attr, BKInt * outValue) const { return BKUnitGetAttr (& unit, attr, outValue); }

	BKInt setPtr (BKEnum attr, void * ptr) { return BKUnitSetPtr (& unit, attr, ptr); }
	BKInt getPtr (BKEnum attr, void * outPtr) const { return BKUnitGetPtr (& unit, attr, outPtr); }

};

#endif /* ! _BK_UNIT_CPP_H_ */