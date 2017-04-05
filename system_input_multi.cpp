#include "system_input_multi.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: Change players' movement, pause and exit according to toggled
	// keys in context

}

bool SystemInputMulti::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
