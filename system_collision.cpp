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
		HandleBallWallCollision();
		HandleBallNetCollision();
		HandlePlayerWallCollision(cspr_player_1, cmot_player_1);
		HandlePlayerWallCollision(cspr_player_2, cmot_player_2);
		HandleBallPlayerCollision(cspr_player_1, cmot_player_1);
		HandleBallPlayerCollision(cspr_player_2, cmot_player_2);
	}
}

void SystemCollision::HandleBallWallCollision()
{
	
	if (cspr_ball->x < cspr_ball->x_min) {
		cspr_ball->x = cspr_ball->x_min;
		cmot_ball->v_x *= -1;
	}
	else if(cspr_ball->x > cspr_ball->x_max) {
		cspr_ball->x = cspr_ball->x_max;
		cmot_ball->v_x *= -1;
	}
	
	/*if (cspr_ball->y > cspr_ball->y_max) {
		cspr_ball->y = cspr_ball->y_max + BALL_Y_OFFSET;
	}*/
}

void SystemCollision::HandleBallNetCollision()
{
	
	if (cspr_ball->x >= 375 - BALL_X_OFFSET && cspr_ball->x <= 375 && cspr_ball->y >= 253 - BALL_X_OFFSET) {
		cmot_ball->v_x *= -1;
	}
	if (cspr_ball->x >= 375 - BALL_X_OFFSET && cspr_ball->x <= 375 && cspr_ball->y >= 253 - 2*BALL_X_OFFSET && cspr_ball->y < 253-BALL_X_OFFSET) {
		cmot_ball->v_x *= -1;
		cmot_ball->v_y *= -1;
	}

}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	if (csprPlayer->x < csprPlayer->x_min) {
		csprPlayer->x = csprPlayer->x_min;
		cmotPlayer->v_x = 0;
	}
	if (csprPlayer->x > csprPlayer->x_max) {
		csprPlayer->x = csprPlayer->x_max;
		cmotPlayer->v_x = 0;
	}
	if (csprPlayer->y > csprPlayer->y_max) {
		csprPlayer->y = csprPlayer->y_max;
		cmotPlayer->v_y = 0;
	}

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
