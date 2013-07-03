#include "BKSequence.h"

static BKInt BKSequenceFuncSimpleCreate (BKSequence ** outSequence, BKSequenceFuncs const * funcs, void const * values, BKUInt length, BKUInt sustainOffset, BKUInt sustainLength)
{
	BKInt        size;
	BKSequence * sequence;

	size = sizeof (BKInt) * length;
	sequence = malloc (sizeof (* sequence) + size);

	if (sequence) {
		memset (sequence, 0, sizeof ( * sequence));
		
		sequence -> values = (void *) sequence + sizeof (* sequence);
		
		memcpy (sequence -> values, values, size);
		
		sequence -> funcs         = funcs;
		sequence -> length        = length;
		sequence -> sustainOffset = BKClamp (sustainOffset, 0, length);
		sequence -> sustainLength = BKClamp (sustainLength, 0, length - sequence -> sustainOffset);		
		sequence -> fracShift     = 0;

		* outSequence = sequence;

		return 0;
	}

	return BK_ALLOCATION_ERROR;
}

static BKInt BKSequenceFuncSimpleSetPhase (BKSequenceState * state, BKEnum phase)
{
	BKSequence * sequence = state -> sequence;
	BKInt      * values   = sequence -> values;

	switch (phase) {
		case BK_SEQUENCE_PHASE_MUTE: {
			state -> offset = BK_INT_MAX;
			break;
		}
		case BK_SEQUENCE_PHASE_ATTACK: {
			state -> offset = 0;
			break;
		}
		case BK_SEQUENCE_PHASE_RELEASE: {
			state -> offset = sequence -> sustainOffset + sequence -> sustainLength;
			break;
		}
		default: {
			return BK_INVALID_ATTRIBUTE;
			break;
		}
	}
	
	if (state -> offset < sequence -> length) {
		state -> value = values [state -> offset];
	}
	else {
		//state -> value  = sequence -> defaultValue;
		state -> offset = BK_INT_MAX;
	}
	
	state -> phase = phase;

	return 0;
}

static BKEnum BKSequenceFuncSimpleStep (BKSequenceState * state, BKEnum level)
{
	if (level < BK_SEQUENCE_STEP_DIVIDED)
		return BK_SEQUENCE_RETURN_NONE;

	if (state -> offset == BK_INT_MAX)
		return BK_SEQUENCE_RETURN_NONE;
	
	BKInt        ret        = BK_SEQUENCE_RETURN_STEP;
	BKSequence * sequence   = state -> sequence;
	BKInt        sustainEnd = sequence -> sustainOffset + sequence -> sustainLength;
	BKInt      * phases     = sequence -> values;

	// reset sustain phase
	if (state -> phase == BK_SEQUENCE_PHASE_ATTACK) {
		if (state -> offset >= sustainEnd) {
			state -> offset = sequence -> sustainOffset;
			ret = BK_SEQUENCE_RETURN_REPEAT;
		}
	}
	
	if (state -> offset < sustainEnd) {
		state -> value = phases [state -> offset];
		state -> offset ++;
	}
	else {
		state -> offset = BK_INT_MAX;
		ret = BK_SEQUENCE_RETURN_FINISH;
	}

	return ret;
}

static BKInt BKSequenceFuncSimpleSetValue (BKSequenceState * state, BKInt value)
{
	state -> value = value;
	
	return 0;
}

static BKInt BKSequenceFuncSimpleCopy (BKSequence ** outCopy, BKSequence const * sequence)
{
	BKInt        size;
	BKSequence * copy;
	BKInt      * values;

	size = sizeof (* values) * sequence -> length;
	copy = malloc (sizeof (* copy) + size);

	if (copy) {
		values = (void *) copy + sizeof (* copy);
		copy -> values = values;

		memcpy (copy, sequence, sizeof (* copy));
		memcpy (copy -> values, sequence -> values, size);

		* outCopy = copy;

		return 0;
	}

	return BK_ALLOCATION_ERROR;
}

BKSequenceFuncs const BKSequenceFuncsSimple =
{
	.create   = BKSequenceFuncSimpleCreate,
	.step     = BKSequenceFuncSimpleStep,
	.setValue = BKSequenceFuncSimpleSetValue,
	.setPhase = BKSequenceFuncSimpleSetPhase,
	.copy     = BKSequenceFuncSimpleCopy,
};

/**
 * Get the maximum absolute value of a sequence
 */
static BKUInt BKSequencePhaseGetMaxAbsValue (BKSequencePhase const * phases, BKUInt length)
{
	BKInt maxValue = 0;

	for (BKInt i = 0; i < length; i ++)
		maxValue = BKMax (maxValue, BKAbs (phases [i].value));

	return maxValue;
}

/**
 * This will calculate the maximum shift value for a sequence to fit in a 32 bit integer
 * The shift value will be used to increase the precision when interpolate between two phases 
 */
static BKUInt BKSequencePhaseGetFracShift (BKSequencePhase const * phases, BKUInt length)
{
	BKInt shift    = 0;
	BKInt maxValue = BKSequencePhaseGetMaxAbsValue (phases, length);

	while ((1 << shift) < maxValue && shift < 31)
		shift ++;

	shift = 31 - shift;

	return shift;
}

/**
 * Check step sum of envelope values
 */
static BKInt BKSequenceEnvelopeCheckValues (BKSequencePhase const * values, BKUInt length)
{
	BKInt steps = 0;

	for (BKInt i = 0; i < length; i ++)
		steps += values [i].steps;

	if (steps == 0)
		return BK_INVALID_VALUE;

	return 0;
}

static BKInt BKSequenceFuncEnvelopeCreate (BKSequence ** outSequence, BKSequenceFuncs const * funcs, void const * values, BKUInt length, BKUInt sustainOffset, BKUInt sustainLength)
{
	if (BKSequenceEnvelopeCheckValues (values, length) != 0)
		return BK_INVALID_VALUE;

	BKInt        size     = sizeof (BKSequencePhase) * length;
	BKSequence * sequence = malloc (sizeof (* sequence) + size);

	if (sequence) {
		sequence -> values = (void *) sequence + sizeof (* sequence);

		memset (sequence, 0, sizeof ( * sequence));
		memcpy (sequence -> values, values, size);

		sequence -> funcs         = funcs;
		sequence -> length        = length;
		sequence -> sustainOffset = BKClamp (sustainOffset, 0, length);
		sequence -> sustainLength = BKClamp (sustainLength, 0, length - sequence -> sustainOffset);		
		sequence -> fracShift     = BKSequencePhaseGetFracShift (values, length);

		* outSequence = sequence;

		return 0;
	}

	return BK_ALLOCATION_ERROR;
}

static BKEnum BKSequenceFuncEnvelopeStep (BKSequenceState * state, BKEnum level);

static BKInt BKSequenceFuncEnvelopeSetPhase (BKSequenceState * state, BKEnum phase)
{
	BKSequence * sequence = state -> sequence;
	
	switch (phase) {
		case BK_SEQUENCE_PHASE_MUTE: {
			state -> steps        = 0;
			state -> delta        = 0;
			state -> offset       = BK_INT_MAX;
			//state -> value        = sequence -> defaultValue;
			state -> shiftedValue = (state -> value << sequence -> fracShift);
			state -> endValue     = 0;
			break;
		}
		case BK_SEQUENCE_PHASE_ATTACK: {
			state -> steps  = 0;
			state -> offset = 0;
			BKSequenceFuncEnvelopeStep (state, 0);  // make first step
			break;
		}
		case BK_SEQUENCE_PHASE_RELEASE: {
			state -> steps  = 0;
			state -> offset = sequence -> sustainOffset + sequence -> sustainLength;
			BKSequenceFuncEnvelopeStep (state, 0);  // make first step
			break;
		}
		default: {
			return BK_INVALID_ATTRIBUTE;
			break;
		}
	}
	
	state -> phase = phase;
	
	if (state -> offset == BK_INT_MAX)
		return BK_SEQUENCE_RETURN_FINISH;

	return 0;
}

static BKEnum BKSequenceFuncEnvelopeStep (BKSequenceState * state, BKEnum level)
{
	if (level < BK_SEQUENCE_STEP_MAX)
		return BK_SEQUENCE_RETURN_NONE;

	if (state -> offset == BK_INT_MAX)
		return BK_SEQUENCE_RETURN_NONE;

	BKEnum            ret        = BK_SEQUENCE_RETURN_STEP;
	BKSequence      * sequence   = state -> sequence;
	BKSequencePhase * phases     = sequence -> values;
	BKInt             sustainEnd = sequence -> sustainOffset + sequence -> sustainLength;
	
	do {
		if (state -> steps) {
			state -> steps --;
			
			if (state -> steps > 0) {
				state -> shiftedValue += state -> delta;
				break;
			}
			else {
				state -> shiftedValue = state -> endValue;
				state -> offset ++;
			}

			state -> value = (state -> shiftedValue >> sequence -> fracShift);
		}
		
		// reset sustain phase
		if (state -> phase == BK_SEQUENCE_PHASE_ATTACK) {
			if (state -> offset >= sustainEnd) {
				state -> offset = sequence -> sustainOffset;
				ret = BK_SEQUENCE_RETURN_REPEAT;
			}
		}
		
		if (state -> offset < sustainEnd) {
			BKSequencePhase * phase = & phases [state -> offset];

			if (phase -> steps) {
				state -> steps = phase -> steps;
				state -> delta = ((state -> shiftedValue << sequence -> fracShift) - state -> value) / phase -> steps;
				state -> endValue = phase -> value;
			}
			else {
				state -> shiftedValue = (phase -> value << sequence -> fracShift);
				state -> steps = 0;
			}

			state -> value = (state -> shiftedValue >> sequence -> fracShift);
		}
		else {
			state -> offset = BK_INT_MAX;
			ret = BK_SEQUENCE_RETURN_FINISH;
			break;
		}
	}
	while (state -> steps == 0);
	
	return ret;
}

static BKInt BKSequenceFuncEnvelopeSetValue (BKSequenceState * state, BKInt value)
{
	BKSequence * sequence = state -> sequence;

	state -> value        = value;
	state -> shiftedValue = (value << sequence -> fracShift);

	if (state -> steps)
		state -> delta = (state -> endValue - state -> shiftedValue) / state -> steps;

	return 0;
}

static BKInt BKSequenceFuncEnvelopeCopy (BKSequence ** outCopy, BKSequence const * sequence)
{
	BKInt              size;
	BKSequence       * copy;
	BKSequencePhase  * values;

	size = sizeof (* values) * sequence -> length;
	copy = malloc (sizeof (* copy) + size);

	if (copy) {
		values = (void *) copy + sizeof (* copy);
		copy -> values = values;

		memcpy (copy, sequence, sizeof (* copy));
		memcpy (copy -> values, sequence -> values, size);

		* outCopy = copy;

		return 0;
	}

	return BK_ALLOCATION_ERROR;
}

BKSequenceFuncs const BKSequenceFuncsEnvelope =
{
	.create   = BKSequenceFuncEnvelopeCreate,
	.step     = BKSequenceFuncEnvelopeStep,
	.setValue = BKSequenceFuncEnvelopeSetValue,
	.setPhase = BKSequenceFuncEnvelopeSetPhase,
	.copy     = BKSequenceFuncEnvelopeCopy,
};

BKInt BKSequenceCreate (BKSequence ** outSequence, BKSequenceFuncs const * funcs, void const * values, BKUInt length, BKUInt sustainOffset, BKUInt sustainLength)
{
	return funcs -> create (outSequence, funcs, values, length, sustainOffset, sustainLength);
}

static void BKSequenceStateAddToSequence (BKSequenceState * state, BKSequence * sequence)
{
	if (state -> sequence == NULL) {
		state -> sequence   = sequence;
		state -> prevState  = NULL;
		state -> nextState  = sequence -> stateList;
		
		if (sequence -> stateList)
			sequence -> stateList -> prevState = state;
		
		sequence -> stateList = state;
	}
}

static void BKSequenceStateRemoveFromSequence (BKSequenceState * state)
{
	BKSequence * sequence = state -> sequence;

	if (sequence != NULL) {
		if (state -> prevState)
			state -> prevState -> nextState = state -> nextState;
		
		if (state -> nextState)
			state -> nextState -> prevState = state -> prevState;
		
		if (sequence -> stateList == state)
			sequence -> stateList = state -> nextState;
		
		state -> sequence   = NULL;
		state -> prevState  = NULL;
		state -> nextState  = NULL;
	}
}

BKInt BKSequenceStateSetSequence (BKSequenceState * state, BKSequence * sequence)
{
	if (state -> sequence != sequence) {
		if (state -> sequence)
			BKSequenceStateRemoveFromSequence (state);

		if (sequence)
			BKSequenceStateAddToSequence (state, sequence);

		state -> sequence = sequence;

		return sequence -> funcs -> setPhase (state, state -> phase);
	}

	return 0;
}

BKInt BKSequenceCopy (BKSequence ** outSequence, BKSequence * sequence)
{
	return sequence -> funcs -> copy (outSequence, sequence);
}

void BKSequenceDispose (BKSequence * sequence)
{
	if (sequence)
		free (sequence);
}

BKInt BKSequenceStateSetPhase (BKSequenceState * state, BKEnum phase)
{
	if (state -> sequence == NULL)
		return BK_INVALID_STATE;

	return state -> sequence -> funcs -> setPhase (state, phase);
}

BKInt BKSequenceStateStep (BKSequenceState * state, BKEnum level)
{
	if (state -> sequence == NULL)
		return BK_INVALID_STATE;

	return state -> sequence -> funcs -> step (state, level);
}

BKInt BKSequenceStateSetValue (BKSequenceState * state, BKInt value)
{
	if (state -> sequence == NULL)
		return BK_INVALID_STATE;

	return state -> sequence -> funcs -> setValue (state, value);
}
