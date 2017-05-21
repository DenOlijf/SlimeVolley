//Groep 27 component.h
#pragma once

class Component
{
public:
	enum Tag
	{
		SPRITE,
		MOTION,
		PLAYER,
		BALL,
		POINT
	};

	Component()
	{
	};

	virtual ~Component()
	{
	};

	virtual Tag GetTag() = 0;
};
