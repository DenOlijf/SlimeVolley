#include "system_input_single.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputSingle::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		Initialize();
	}

	// TODO: Change player's movement, pause and exit according to toggled
	// keys in context

}

bool SystemInputSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
