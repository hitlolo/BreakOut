#include "PhysicsProtocol.h"

float PhysicsProtocol::ptm(float pixel)
{
	return pixel / PTM_RATIO;
}

float PhysicsProtocol::mtp(float meter)
{
	return meter * PTM_RATIO;
}