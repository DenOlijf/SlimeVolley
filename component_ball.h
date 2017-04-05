#pragma once

#include "component.h"

class ComponentBall : public Component
{
public:
	ComponentBall()
	{
	};

	virtual ~ComponentBall()
	{
	};

	virtual Tag GetTag()
	{
		return BALL;
	};
};
