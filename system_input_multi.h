#pragma once

#include "component_motion.h"
#include "system.h"

class SystemInputMulti : public System
{
public:
	SystemInputMulti() : System(), initialized(false), pressed_a(false), pressed_d(false), pressed_w(false), pressed_left(false), pressed_right(false), pressed_up(false)
	{
	};

	virtual ~SystemInputMulti()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_INPUT_MULTI;
	};

private:
	bool Initialize();

	bool initialized;
	bool pressed_a;
	bool pressed_d;
	bool pressed_w;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentMotion* cmot_player_1;
	ComponentMotion* cmot_player_2;
};
