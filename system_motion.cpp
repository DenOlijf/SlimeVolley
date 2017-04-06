#define NOMINMAX

#include "system_motion.h"

#include <algorithm>
#include <cmath>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

void SystemMotion::Update()
{
	// Is the game running?
	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Update velocity and position of all entities with motion
		// component
		
		std::set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::MOTION);
		std::set<Entity*>::iterator it;

		for (it = entities.begin(); it != entities.end(); it++) {
			Entity* temp = *it;
			ComponentMotion* motion = (ComponentMotion*)temp->GetComponent(Component::MOTION);
			motion->v_x += motion->a_x;
			motion->v_y += motion->a_y;
			ComponentSprite* sprite = (ComponentSprite*)temp->GetComponent(Component::SPRITE);
			sprite->x -= motion->v_x; //-= vanwege de omgekeerde board door de allegro
			sprite->y -= motion->v_y;
		}

	}
}
