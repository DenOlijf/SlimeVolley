//Groep 27 system_eyes.cpp
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
	std::set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	std::set<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		ComponentPlayer* player = (ComponentPlayer*)(*it)->GetComponent(Component::PLAYER);
		ComponentSprite* slime = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);

		//berekenen waar pupil x- en y-waarden moet liggen
		double centre_x = (player->player_id == 1) ? slime->x + EYE_OFFSET : slime->x - EYE_OFFSET;
		double centre_y = slime->y + EYE_OFFSET;
		double dx = cspr_ball->x - centre_x;
		double dy = cspr_ball->y - centre_y;
		double hypothenusa = sqrt(pow(dx, 2) + pow(dy, 2));
		double cos = dx / hypothenusa;
		double sin = dy / hypothenusa;

		player->pupil_y = centre_y + sin*3;
		player->pupil_x = centre_x + cos*3;
	}

}

bool SystemEyes::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	std::set<Entity*> entity = engine->GetEntityStream()->WithTag(Component::BALL);
	cspr_ball = (ComponentSprite*)(*entity.begin())->GetComponent(Component::SPRITE);
	return true;
}
