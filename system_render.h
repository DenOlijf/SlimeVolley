#pragma once

#include "entity.h"
#include "system.h"

class SystemRender : public System
{
public:
	SystemRender() : System(), initialized(false)
	{
		srand((unsigned int)time(NULL));
	};

	virtual ~SystemRender()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_RENDER;
	};

private:
	bool Initialize();

	bool initialized;
	int fps;
	int fps_accum;
	double fps_time;
	double t;
};
