#pragma once

#include "component_motion.h"
#include "system.h"

class SystemInputSingle : public System
{
public:
	SystemInputSingle() : System(), initialized(false), pressed_left(false), pressed_right(false), pressed_up(false)
	{
	};

	virtual ~SystemInputSingle()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_INPUT_SINGLE;
	};

private:
	bool Initialize();

	bool initialized;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentMotion* cmot_player_1;
};
