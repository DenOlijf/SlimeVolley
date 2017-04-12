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

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_SPACE, true)) {
		engine->GetContext()->SwitchPaused();
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true)) {
		// IK SNAP NIET HOE JE EXIT
	}

	std::set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	std::set<Entity*>::iterator it;

	Entity* player1 = NULL;
	Entity* player2 = NULL;

	//entities juist zetten
	for (it = entities.begin(); it != entities.end(); it++) {
		Entity* temp = *it;
		ComponentPlayer* player = (ComponentPlayer*)temp->GetComponent(Component::PLAYER);
		if (player->player_id == 1) {
			player1 = temp;
		}
		else {
			player2 = temp;
		}
	}
	//nu verder werken met movement van player1 en 2
	ComponentMotion* mot1 = (ComponentMotion*)player1->GetComponent(Component::MOTION);
	ComponentMotion* mot2 = (ComponentMotion*)player2->GetComponent(Component::MOTION);

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_D, false)) {
		mot1->v_x = 6;
	}else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Q, false)) {
		mot1->v_x = -6;
	}else {
		mot1->v_x = 0;
	}
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Z, true)) {
		mot1->v_y = 11.625;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_S, true)) {
		mot1->v_y = -5;
	}
	
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, true)) {
		mot2->v_y = 11.625;
	}else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_DOWN, true)) {
		mot2->v_y = -5;
	}
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, false)) {
		mot2->v_x = 6;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, false)) {
		mot2->v_x = -6;
	}
	else {
		mot2->v_x = 0;
	}

}

bool SystemInputMulti::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	//SNAP NIET WAT ZE BEDOELEN
	return true;
}
