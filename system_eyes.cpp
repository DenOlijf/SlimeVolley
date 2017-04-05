#include "system_eyes.h"

#include <cmath>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

void SystemEyes::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: Iterate over all player entities and set eyes in right position

}

bool SystemEyes::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
