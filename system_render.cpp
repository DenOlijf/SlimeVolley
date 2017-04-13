#include "system_render.h"

#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include <vector>

#include "color.h"
#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"
#include "tags.h"

void SystemRender::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Clear screen and draw background
	Graphics::Instance().ClearScreen();
	Graphics::Instance().DrawBackground();

	// TODO: Iterate over all entities with the sprite component and print to
	// screen. For player slimes, draw the pupils as well.

	//alles tekenen, behalve pupillen
	std::set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::SPRITE);
	std::set<Entity*>::iterator it;

	for (it = entities.begin(); it != entities.end(); it++) {
		Entity* temp = *it;
		ComponentSprite* tempo = (ComponentSprite*)temp->GetComponent(Component::SPRITE);
		Graphics::Instance().DrawBitmap(tempo->sprite, tempo->x, Y_MAX-tempo->y, tempo->x_off, -tempo->y_off);
	}

	//pupillen tekenen
	std::set<Entity*> players = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for (it = players.begin(); it != players.end(); it++) {
		ComponentPlayer* player = (ComponentPlayer*)(*it)->GetComponent(Component::PLAYER);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_PUPIL, player->pupil_x, Y_MAX - player->pupil_y, 5, 5);
	}

	Color c(0, 0, 0);

	// TODO: Use an appropriate color for the different backgrounds
	/*if (engine->GetContext()->GetLevel() == ...)
	{
		c = Color(..., ..., ...);
	}*/

	// TODO: Print the current score if it is a singleplayer game

	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay

	int state = engine->GetContext()->GetState();
	int level = engine->GetContext()->GetLevel();

	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)

	if (state == PLAYER_LEFT_SCORES) {
		Graphics::Instance().DrawString("Player 1 scores!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();
		Sleep(1000 * FREEZE_TIME);
	}
	else if (state == PLAYER_RIGHT_SCORES) {
		Graphics::Instance().DrawString("Player 2 scores!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();
		Sleep(1000 * FREEZE_TIME);
	}
	else if (state == PLAYER_LEFT_WINS) {
		Graphics::Instance().DrawString("Player 1 wins!", 375, Y_MAX - (-20), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - (-50),c,Graphics::ALIGN_CENTER);
		//engine->GetContext()->SetState(0); //state moet niet op nul want spel is gedaan?
		Graphics::Instance().ExecuteDraws();
		//Sleep(1000 * FREEZE_TIME);
	}
	else if (state == PLAYER_RIGHT_WINS) {
		Graphics::Instance().DrawString("Player 2 wins!!", 375, Y_MAX - (-20), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - (-50), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();
		//Sleep(1000 * FREEZE_TIME);
	}

	// Update current frame rate
	fps_accum++;
	t = al_get_time();
	if (t - fps_time >= 1)
	{
		fps = fps_accum;
		fps_accum = 0;
		fps_time = t;
	}
	Graphics::Instance().DrawString(std::to_string(fps), 375, 40, c, Graphics::ALIGN_CENTER);

	// Execute all draws
	Graphics::Instance().ExecuteDraws();
}

bool SystemRender::Initialize()
{
	int level = engine->GetContext()->GetLevel();

	// TODO: Set background according to level

	return true;
}
