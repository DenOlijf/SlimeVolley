#define NOMINMAX

#include "system_collision.h"

#include <algorithm>
#include <cmath>
#include <set>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"

void SystemCollision::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Handle all possible collisions

	}
}

void SystemCollision::HandleBallWallCollision()
{
	// TODO: Handle a possible collision between the ball and a wall

}

void SystemCollision::HandleBallNetCollision()
{
	// TODO: Handle a possible collision between the ball and the net

}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	// TODO: Handle a possible collision between a player and the walls/floor

}

void SystemCollision::HandleBallPlayerCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	double d_x = cspr_ball->x - csprPlayer->x;
	double d_y = cspr_ball->y - csprPlayer->y;
	double dist = std::sqrt(d_x * d_x + d_y * d_y);
	if (d_y > 0 && dist < 46.875)
	{
		cspr_ball->x = csprPlayer->x + 46.875 * d_x / dist;
		cspr_ball->y = csprPlayer->y + 46.875 * d_y / dist;
		double d_v_x = cmot_ball->v_x - cmotPlayer->v_x;
		double d_v_y = cmot_ball->v_y - cmotPlayer->v_y;
		double s = (d_x * d_v_x + d_y * d_v_y * 2) / dist;
		if (s < 0)
		{
			cmot_ball->v_x += cmotPlayer->v_x - 2 * d_x * s / dist;
			cmot_ball->v_y += cmotPlayer->v_y - d_y * s / dist;
			cmot_ball->v_x = std::max(cmot_ball->v_x, -11.25);
			cmot_ball->v_x = std::min(cmot_ball->v_x, 11.25);
			cmot_ball->v_y = std::max(cmot_ball->v_y, -8.25);
			cmot_ball->v_y = std::min(cmot_ball->v_y, 8.25);
		}
	}
}

bool SystemCollision::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
