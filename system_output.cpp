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
	coordinates test = { cspr_player_1->x, cspr_player_1->y, cspr_player_2->x, cspr_player_2->y, cspr_ball->x, cspr_ball->y };
	if (cs.size() > 0) {
		coordinates last = cs.back();
		if (test.x_ball != last.x_ball
			|| test.y_ball != last.y_ball
			|| test.x_player_1 != last.x_player_1
			|| test.y_player_1 != last.y_player_1
			|| test.x_player_2 != last.x_player_2
			|| test.y_player_2 != last.y_player_2)
			cs.push_back(test);
	}
	else
		cs.push_back(test);
	// Is there a winner?
	if (engine->GetContext()->GetState() > 0)
	{
		// TODO: Output coordinates to file
		start_time = engine->GetContext()->GetStartTime();
		level = engine->GetContext()->GetLevel();
		ofstream highscores;
		highscores.open("assets/highscores/" + std::to_string(start_time) + "_" + std::to_string(level) + ".txt", ios::out);
		std::list<coordinates>::iterator it;
		for (it = cs.begin(); it != cs.end(); it++) {
			coordinates temp = *it;
			highscores << temp.x_player_1 << " " << temp.y_player_1 << " " << temp.x_player_2 << " " << temp.y_player_2 << " " << temp.x_ball << " " << temp.y_ball  << endl;
		}
		highscores.close();
	}
}

bool SystemOutput::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	std::set<Entity*> ents = engine->GetEntityStream()->WithTag(Component::MOTION);
	std::set<Entity*>::iterator it;

	for (it = ents.begin(); it != ents.end(); it++) {
		Graphics::Sprite temp = ((ComponentSprite*)(*it)->GetComponent(Component::SPRITE))->sprite;
		if (temp == Graphics::SPRITE_PLAYER1) {
			cspr_player_1 = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
		}
		else {
			if (temp == Graphics::SPRITE_PLAYER2 || temp == Graphics::SPRITE_OPPONENT1 || temp == Graphics::SPRITE_OPPONENT2 || temp == Graphics::SPRITE_OPPONENT3) {
				cspr_player_2 = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
			}
			else {
				if (temp == Graphics::SPRITE_BALL) {
					cspr_ball = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
				}
			}
		}
	}
	return true;
}
