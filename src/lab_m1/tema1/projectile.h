#pragma once
class projectile {
public:
	float time;
	float translateX;
	float translateY;
	float angularStep;
	projectile();
	void setAngle(float angularStepP);
};