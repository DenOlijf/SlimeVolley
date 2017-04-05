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
	// TODO: Calculate the value of x when y is first below y_target

	return 0;
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
		
		// If state equals 0 or the ball is in serving position (v_x = 0, x == 600)
		//    Set state equal to 0 and serve only if the ball drops below y = 110 by simply moving right and jump
		//    Return
		
		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 600 (i.e. use abs(x - 600) < 6) by moving left/right (otherwise just stop)
		//    Return

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150
		//        Jump
		//    Return

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)

		// Else if the slime's x >= 675
		//    Move right

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
	}
	else if (level == 2)
	{
		// If ball is on left side of the net, set state equal to -1

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

		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 480 (i.e. use abs(x - 480) < 6) by moving left/right (otherwise just stop)
		//    Return

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150 and random value < 0.5
		//        Jump
		//    Return

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)

		// Else if the slime's x >= 675
		//    Move right

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
	}
	else if (level == 3)
	{
		
	}
}

void SystemAI::UpdateMovement()
{
	// TODO: Change player's movement according to AI decisions (i.e. pressed_xxx)

}

bool SystemAI::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
