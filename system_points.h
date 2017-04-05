#pragma once

#include "entity.h"
#include "system.h"

class SystemPoints : public System
{
public:
	SystemPoints() : System()
	{
	};

	virtual ~SystemPoints()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_POINTS;
	};
};
