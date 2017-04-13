#include "system_state_multi.h"

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

void SystemStateMulti::Update()
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
			
			//engine->GetContext()->SetFrozen(false);

			if (cspr_ball->y <= cspr_ball->y_min) {
				//engine->GetContext()->SetFrozen(true);
				
				freeze_time = 1;

				cmot_player_1->v_x = 0;
				cmot_player_1->v_y = 0;

				cmot_player_2->v_x = 0;
				cmot_player_2->v_y = 0;

				cmot_ball->v_x = 0;
				cmot_ball->v_y = 0;

				if (engine->GetContext()->GetState() != PLAYER_LEFT_WINS && engine->GetContext()->GetState() != PLAYER_RIGHT_WINS) {

					if (cspr_ball->x < 375 - BALL_X_OFFSET) {
						engine->GetContext()->IncreasePoints(2);
						engine->GetContext()->SetState(PLAYER_RIGHT_SCORES);
					}
					else {
						engine->GetContext()->IncreasePoints(1);
						engine->GetContext()->SetState(PLAYER_LEFT_SCORES);
					}
				}
			}
		}
		else
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context and wait
			// for	user input: spacebar to restart, ESC to quit (handled by
			// input system already). If the game is not finished yet, update
			// the context and reset player and ball positions.
			freeze_time -= 1;

			if (freeze_time == 0) {
				if (engine->GetContext()->GetPoints(1) == 7) {
					engine->GetContext()->SetState(PLAYER_LEFT_WINS);
				}
				else if (engine->GetContext()->GetPoints(2) == 7) {
					engine->GetContext()->SetState(PLAYER_RIGHT_WINS);
				}
				//nog wachten op user input, geen idee hoe die shit moet

				else{
					if (engine->GetContext()->GetState() == PLAYER_LEFT_SCORES) {
						cspr_ball->x = SLIME_1_INIT_X;
					}
					else {
						cspr_ball->x = SLIME_2_INIT_X;
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

bool SystemStateMulti::Initialize()
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
			if (temp == Graphics::SPRITE_PLAYER2) {
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
