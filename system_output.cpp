#include "system_output.h"

#include <fstream>
#include <list>

#include "component_player.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"

void SystemOutput::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: Push back coordinates if they are different from last frame

	// Is there a winner?
	if (engine->GetContext()->GetState() > 0)
	{
		// TODO: Output coordinates to file

	}
}

bool SystemOutput::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
