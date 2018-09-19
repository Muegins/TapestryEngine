#include "Emitter.h"


//Emitter Functions
bool Emitter::EmitParticle()
{
	mPrtMan->EventProcess(Event(EMIT_PARTICLE, this));
	return true;
}