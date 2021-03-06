//Groep 27 system_input_multi.cpp
#include "system_input_multi.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "game.h"


void SystemInputMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: Change players' movement, pause and exit according to toggled
	// keys in context

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_P, true)) {
		engine->GetContext()->SwitchPaused();
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true)) {
		engine->GetContext()->Reset(2, false);
	}
	//indien spel gedaan: wachten op input
	else if (engine->GetContext()->GetState() == PLAYER_LEFT_WINS || engine->GetContext()->GetState() == PLAYER_RIGHT_WINS) {
		if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_SPACE, true)) {
			engine->GetContext()->Reset(0, false);
		}
		else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true)) {
			engine->GetContext()->Reset(2, false);
		}
	}

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_D, false)) {
		cmot_player_1->v_x = SLIME_V_X;
	}else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Q, false)) {
		cmot_player_1->v_x = -SLIME_V_X;
	}else {
		cmot_player_1->v_x = 0;
	}
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Z, true ) && cmot_player_1->v_y == 0) {
		cmot_player_1->v_y = SLIME_V_Y;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_S, true)) {
		cmot_player_1->v_y = -5;
	}
	
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, true) && cmot_player_2->v_y == 0) {
		cmot_player_2->v_y = SLIME_V_Y;
	}else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_DOWN, true)) {
		cmot_player_2->v_y = -5;
	}
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, false)) {
		cmot_player_2->v_x = SLIME_V_X;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, false)) {
		cmot_player_2->v_x = -SLIME_V_X;
	}
	else {
		cmot_player_2->v_x = 0;
	}

}

bool SystemInputMulti::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	std::set<Entity*> ents = engine->GetEntityStream()->WithTag(Component::PLAYER);
	std::set<Entity*>::iterator it;
	for (it = ents.begin(); it != ents.end(); it++) {
		Entity* temp = *it;
		if (((ComponentPlayer*)temp->GetComponent(Component::PLAYER))->player_id == 1) {
			cmot_player_1 = (ComponentMotion*)temp->GetComponent(Component::MOTION);
		}
		else cmot_player_2 = (ComponentMotion*)temp->GetComponent(Component::MOTION);
	}
	return true;
}
