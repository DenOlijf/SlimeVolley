//Groep 27 system_state_single.cpp
#include "system_state_single.h"

#include <set>

#include "component.h"
#include "component_player.h"
#include "component_motion.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemStateSingle::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// Is the level in freeze state?
		if (freeze_time == 0)
		{
			// TODO: Check if the ball has dropped. If so, freeze the game for
			// 1.2 seconds and reset all velocities. Determine the winner and
			// update the context accordingly.
			if (engine->GetContext()->GetState() != LEVEL_WON && engine->GetContext()->GetState() != LEVEL_LOST) {
				engine->GetContext()->SetFrozen(false);
			}

			if (cspr_ball->y <= cspr_ball->y_min) {
				engine->GetContext()->SetFrozen(true);

				freeze_time = engine->GetContext()->GetFps()*1.2;

				cmot_player_1->v_x = 0;
				cmot_player_1->v_y = 0;

				cmot_player_2->v_x = 0;
				cmot_player_2->v_y = 0;

				cmot_ball->v_x = 0;
				cmot_ball->v_y = 0;

				cspr_ball->y = cspr_ball->y_min;
				if (engine->GetContext()->GetState() != LEVEL_WON && engine->GetContext()->GetState() != LEVEL_LOST) {
					if (cspr_ball->x < 375 - BALL_X_OFFSET) {
                        srand(time(NULL));
                        int r = rand() % 3;
                        engine->GetContext()->IncreasePoints(2);
                        engine->GetContext()->SetState(PLAYER_RIGHT_SCORES1 - r);
						engine->GetContext()->UpdateScore(-100);
					}
					else {
                        srand(time(NULL));
                        int r = rand() % 3;
						engine->GetContext()->IncreasePoints(1);
						engine->GetContext()->SetState(PLAYER_LEFT_SCORES1-r);
						engine->GetContext()->UpdateScore(200);
					}
				}
			}

		}
		else
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context as to
			// end the level gracefully. Wait for user input: spacebar to
			// continue to next level (if won) or retry (if lost), ESC to quit
			// (handled by input system already). If the game is not finished
			// yet, update the context and reset player and ball positions.
			freeze_time -= 1;
			if (freeze_time == 0) {
				if (engine->GetContext()->GetPoints(1) == 7) {
					engine->GetContext()->SetState(LEVEL_WON);
				}
				else if (engine->GetContext()->GetPoints(2) == 7) {
					engine->GetContext()->SetState(LEVEL_LOST);
				}
				else {
					if (engine->GetContext()->GetState() == PLAYER_LEFT_SCORES1 || engine->GetContext()->GetState() == PLAYER_LEFT_SCORES2 || engine->GetContext()->GetState() == PLAYER_LEFT_SCORES3) {
						cspr_ball->x = SLIME_1_INIT_X;
					}
					else if (engine->GetContext()->GetState() == PLAYER_RIGHT_SCORES1 || engine->GetContext()->GetState() == PLAYER_RIGHT_SCORES2 || engine->GetContext()->GetState() == PLAYER_RIGHT_SCORES3) {
						cspr_ball->x = SLIME_2_INIT_X;
					}
					else { //random beslissen wie bij volgende keren als eerste mag opslaan
						srand(time(NULL));
						int opslag = rand() % 2;
						if (opslag < 1) {
							cspr_ball->x = SLIME_1_INIT_X;
						}
						else {
							cspr_ball->x = SLIME_2_INIT_X;
						}
					}
					cspr_ball->y = BALL_INIT_Y;
					cspr_player_1->x = SLIME_1_INIT_X;
					cspr_player_1->y = 0;
					cspr_player_2->x = SLIME_2_INIT_X;
					cspr_player_2->y = 0;
					engine->GetContext()->SetState(0);
				}
			}

		}
	}
}

bool SystemStateSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	std::set<Entity*> ents = engine->GetEntityStream()->WithTag(Component::MOTION);
	std::set<Entity*>::iterator it;

	for (it = ents.begin(); it != ents.end(); it++) {
		Graphics::Sprite temp = ((ComponentSprite*)(*it)->GetComponent(Component::SPRITE))->sprite;
		if (temp == Graphics::SPRITE_PLAYER1) {
			cspr_player_1 = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
			cmot_player_1 = (ComponentMotion*)(*it)->GetComponent(Component::MOTION);
		}
		else {
			if (temp == Graphics::SPRITE_OPPONENT1 || temp == Graphics::SPRITE_OPPONENT2 || temp == Graphics::SPRITE_OPPONENT3) {
				cspr_player_2 = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
				cmot_player_2 = (ComponentMotion*)(*it)->GetComponent(Component::MOTION);
			}
			else {
				if (temp == Graphics::SPRITE_BALL) {
					cspr_ball = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
					cmot_ball = (ComponentMotion*)(*it)->GetComponent(Component::MOTION);
				}
			}
		}
	}
	return true;
}
