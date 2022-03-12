#include "projectile.h"
using namespace std;

projectile::projectile() : time(0.6f), translateX(0), translateY(0), angularStep(0) {}

void projectile::setAngle(float angularStepP) {
	angularStep = angularStepP;
}