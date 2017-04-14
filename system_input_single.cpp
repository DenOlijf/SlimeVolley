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
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ENTER, true)) {
		engine->GetContext()->SwitchPaused();
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true)) {
		engine->GetContext()->SetState(2);
	}

	//bewegen
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_D, false)) {
		cmot_player_1->v_x = SLIME_V_X;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Q, false)) {
		cmot_player_1->v_x = -SLIME_V_X;
	}
	else {
		cmot_player_1->v_x = 0;
	}
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Z, true && cmot_player_1->v_y == 0)) {
		cmot_player_1->v_y = SLIME_V_Y;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_S, true)) {
		cmot_player_1->v_y = -5;
	}

}

bool SystemInputSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	std::set<Entity*> ents = engine->GetEntityStream()->WithTag(Component::PLAYER);
	std::set<Entity*>::iterator it;
	for (it = ents.begin(); it != ents.end(); it++) {
		Entity* temp = *it;
		if (((ComponentPlayer*)temp->GetComponent(Component::PLAYER))->player_id == 1) {
			cmot_player_1 = (ComponentMotion*)temp->GetComponent(Component::MOTION);
		}
	}
	return true;
}
