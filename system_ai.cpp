#include "system_ai.h"

#include <set>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "entity.h"
#include "engine.h"

void SystemAI::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Reset state and AI's decisions
	if (engine->GetContext()->GetState() != 0)
	{
		state = -1;
		Stop();
	}

	// Update AI's decisions if the game is not paused
	if (!engine->GetContext()->IsPaused())
	{
		UpdateKeys();
	}

	// Update player's movement
	UpdateMovement();
}

double SystemAI::XBallBelow(double y_target)
{
	double time = (-cmot_ball->v_y - sqrt(cmot_ball->v_y*cmot_ball->v_y - 2 * y_target*cmot_ball->a_y)) / cmot_ball->a_y;
	return cspr_ball->x + cmot_ball->v_x*time + 1 / 2 * cmot_ball->a_x*time*time;
}

void SystemAI::MoveLeft()
{
	pressed_left = true;
	pressed_right = false;
}

void SystemAI::MoveRight()
{
	pressed_left = false;
	pressed_right = true;
}

void SystemAI::Jump()
{
	pressed_up = true;
}

void SystemAI::Stop()
{
	pressed_left = false;
	pressed_right = false;
	pressed_up = false;
}

float SystemAI::GetRandom()
{
	return (float)rand() / (RAND_MAX);
}

void SystemAI::UpdateKeys()
{
	int level = engine->GetContext()->GetLevel();

	// TODO: Implement game logic for different levels
	if (level == 1)
	{
		// If ball is on left side of the net, set state equal to -1
		if (cspr_ball->x < 375) {
			state = -1;
		}
		// If state equals 0 or the ball is in serving position (v_x = 0, x == 600)
		//    Set state equal to 0 and serve only if the ball drops below y = 110 by simply moving right and jump
		//    Return
		if (state == 0 || (cmot_ball->v_x == 0 && cspr_ball->x == SLIME_2_INIT_X)) {
			state = 0;
			if (cspr_ball->y < 110) {
				MoveRight();
				Jump();
			}
			return;
		}
		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		double P = XBallBelow(90.0);
		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 600 (i.e. use abs(x - 600) < 6) by moving left/right (otherwise just stop)
		//    Return
		if (P < 375) {
			if (abs(cspr_player_2->x - P) > 6) {
				if (cspr_player_2->x < 595) {
					MoveRight();
				}
				else if (cspr_player_2->x > 605) {
					MoveLeft();
				}
			}
			else {
				Stop();
			}
			return;
		}
		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150
		//        Jump
		//    Return
		if (abs(P - cspr_player_2->x) < 25 && cspr_player_2->y == cspr_player_2->y_min) {
			if ((cspr_player_2->x >= 675 && cspr_ball->x > 625) 
				|| (cspr_player_2->x <= 435 && cspr_ball->x < 395)
				|| (abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150)) {
				Jump();
			}
			return;
		}
		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)
		else if (cspr_player_2->y == cspr_player_2->y_min) {
			if (cspr_player_2->x <= P - 25) MoveRight();
			else {
				if (cspr_player_2->x >= P + 25) MoveLeft();
				else Stop();
			}
		}
		// Else if the slime's x >= 675
		//    Move right
		else if (cspr_player_2->x >= 675) MoveRight();
		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
		else {
			if (cspr_player_2->x <= cspr_ball->x - 25) MoveRight();
			else if (cspr_player_2->x >= cspr_ball->x + 25) MoveLeft();
			else Stop();
		}
		return;
	}
	else if (level == 2)
	{
		// If ball is on left side of the net, set state equal to -1
		if (cspr_ball->x < 375) {
			state = -1;
		}

		// If state does not equal -1 or the ball is in serving position (v_x = 0, x == 600)
		//    If state equals -1
		//        Randomly set the state equal to 0, 1 or 2
		//    If state equals 0
		//        If the ball drops below y = 75, move right and jump
		//    If state equals 1
		//        If the ball drops below y = 75, move left and jump
		//    If state equals 2
		//        If the ball's vertical speed is higher than 4.5 and slime's x < 645
		//            Move right (until slime's x >= 645)
		//        If slime's x >= 645
		//            Stop
		//        If the ball's vertical speed equals -1.125 and slime's x != 600
		//            Jump
		//        If the ball's vertical speeds is lower than -4.5 and the slime is mid-air and slime's x >= 633
		//            Move left
		//    Return
		if (state != -1 || (cmot_player_2->v_x == 0 && cspr_player_2->x == 600)) {
			if (state == -1) {
				float random = GetRandom();
				if (random < 0.33) {
					state = 0;
				}
				else if (random < 0.66) {
					state = 1;
				}
				else {
					state = 2;
				}
			}
			else if (state == 0) {
				if (cspr_ball->y < 75) {
					MoveRight();
					Jump();
				}
			}
			else if (state == 1) {
				if (cspr_ball->y < 75) {
					MoveLeft();
					Jump();
				}
			}
			else if (state == 2) {
				if (cmot_ball->v_y > 4.5 && cspr_player_2->x < 645) {
					MoveRight();
				}
				if (cspr_player_2->x >= 645) {
					Stop();
				}
				if (cmot_ball->v_y == -1.125 && cspr_player_2->x != 600) {
					Jump();
				}
				if (cmot_ball->v_y < -4.5 && cspr_player_2->y>0 && cspr_player_2->x >= 633) {
					MoveLeft();
				}
			}
		}


		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		double P = XBallBelow(90.0);
		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 480 (i.e. use abs(x - 480) < 6) by moving left/right (otherwise just stop)
		//    Return
		if (P < 375) {
			if (abs(cspr_player_2->x - 480) > 6) {
				if (cspr_player_2->x - 480 > 0) {
					MoveLeft();
				}
				else {
					MoveRight();
				}
			}
			else {
				Stop();
			}
			return;
		}
		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150 and random value < 0.5
		//        Jump
		//    Return
		if (abs(P - cspr_player_2->x) < 25 && cspr_player_2->y == cspr_player_2->y_min) {
			if (cspr_player_2->x >= 675 && cspr_ball->x > 625) {
				Jump();
			}
			if (cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(cspr_ball->x - cspr_player_2->x) < 75) {
				Jump();
			}
			if (abs(cspr_player_2->x - cspr_ball->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150 && GetRandom()<0.5) {
				Jump();
			}
			return;
		}

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)
		else if (cspr_player_2->y == cspr_player_2->y_min) {
			if (abs(cspr_player_2->x - P) > 25) {
				if (cspr_player_2->x - P > 0) {
					MoveLeft();
				}
				else {
					MoveRight();
				}
			}
			else {
				Stop();
			}
		}

		// Else if the slime's x >= 675
		//    Move right
		else if (cspr_player_2->x >= 675) {
			MoveRight();
		}

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
		else {
			if (abs(cspr_player_2->x - cspr_ball->x) > 25) {
				if (cspr_player_2->x - cspr_ball->x > 0) {
					MoveLeft();
				}
				else {
					MoveRight();
				}
			}
			else {
				Stop();
			}
		}
	}
	else if (level == 3)
	{
		
	}
}

void SystemAI::UpdateMovement()
{
	// TODO: Change player's movement according to AI decisions (i.e. pressed_xxx)
	if (pressed_up && cmot_player_2->v_y == 0) cmot_player_2->v_y = SLIME_V_Y;
	if (pressed_left) cmot_player_2->v_x = -SLIME_V_X;
	else if (pressed_right) cmot_player_2->v_x = SLIME_V_X;
}

bool SystemAI::Initialize()
{
	std::set<Entity*> ents = engine->GetEntityStream()->WithTag(Component::MOTION);
	std::set<Entity*>::iterator it;

	for (it = ents.begin(); it != ents.end(); it++) {
		Graphics::Sprite temp = ((ComponentSprite*)(*it)->GetComponent(Component::SPRITE))->sprite;
		if (temp == Graphics::SPRITE_PLAYER1) {
			cspr_player_1 = (ComponentSprite*)(*it)->GetComponent(Component::SPRITE);
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
