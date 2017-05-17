#define NOMINMAX

#include "system_replay.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemReplay::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: According to toggled keys in context, either:
	//   [ARROW_LEFT] Decrease playout speed by factor 2
	//	 [ARROW_RIGHT] Increase playout speed by factor 2
	//   [ARROW_UP] Go to next point
	//	 [ARROW_DOWN] Go to next level
	//	 [P] Pause playout
	//	 [ESC] Return to menu
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, true))
		speed = std::max(0.5,speed/2);
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, true))
		speed = std::min(4.0,speed*2);
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, true))
		GoToNextPoint();
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_DOWN, true))
		GoToNextLevel();
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_P, true))
		engine->GetContext()->SwitchPaused();
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true))
		engine->GetContext()->Reset(STOP_REPLAY, true);
	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// TODO: Go to the next frame(s), if necessary
		if (status != 2) {
			double wacht_tijd = 1 / (FPS*speed);
			for (int i = 0; i < std::round(speed); i++) {
				telTijd += 1 / FPS;
			}
			if (telTijd >= wacht_tijd) {
				GoToNextFrame();
				telTijd = 0;
			}
		}
	}
}

void SystemReplay::GoToNextFrame()
{
	// TODO: Go to next frame by setting the new coordinates. Set state to:
	//   0 if a normal frame has been found
	//   1 if a frame has been found in which the ball has dropped
	//   2 if there are no coordinates left
	// and update the context whenever necessary
	if (cs.size() > 0) {
		if (cs.begin()->y_ball > BALL_X_OFFSET) {
			status = 0;
			if (speed >= 2.0) {
				cs.pop_front();
				if (cs.size() > 0 && cs.begin()->y_ball > BALL_X_OFFSET && speed == 4.0) cs.pop_front();
			}
		}
		else {
			status = 1;
			if (cs.begin()->x_ball < 375 - BALL_X_OFFSET) {
				engine->GetContext()->SetState(PLAYER_RIGHT_SCORES1);
				engine->GetContext()->IncreasePoints(2);
			}
			else {
				engine->GetContext()->SetState(PLAYER_LEFT_SCORES1);
				engine->GetContext()->IncreasePoints(1);
			}
		}
		if (cs.size() > 0) {
			cspr_player_1->x = cs.begin()->x_player_1;
			cspr_player_1->y = cs.begin()->y_player_1;
			cspr_player_2->x = cs.begin()->x_player_2;
			cspr_player_2->y = cs.begin()->y_player_2;
			cspr_ball->x = cs.begin()->x_ball;
			cspr_ball->y = cs.begin()->y_ball;
			cs.pop_front();
		}
	}
	else {
		status = 2;
		engine->GetContext()->Reset(NEXT_LEVEL, true);
	}
}

void SystemReplay::GoToNextPoint()
{
	while (status < 1)
	{
		GoToNextFrame();
	}
}

void SystemReplay::GoToNextLevel()
{
	while (status < 2)
	{
		GoToNextFrame();
	}
}

bool SystemReplay::Initialize()
{
	// TODO: Read input coordinates from file and push to list
	ifstream input;
	input.open(engine->GetContext()->GetInputFile(), ios::in);
	int index = 0;
	double coords [6];
	double temp = 0;
	while (input >> temp) {
		coords[index] = temp;
		if (index == 5)
			cs.push_back({ coords[0], coords[1], coords[2], coords[3], coords[4], coords[5] });
		index++;
		index = index % 6;
	}
	input.close();
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
