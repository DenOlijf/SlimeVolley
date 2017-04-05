#pragma once

#include "entity.h"
#include "system.h"

class SystemMotion : public System
{
public:
	SystemMotion() : System()
	{
	};

	virtual ~SystemMotion()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_MOTION;
	};
};
