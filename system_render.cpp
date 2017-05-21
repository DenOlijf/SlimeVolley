//Groep 27 system_render.cpp
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

	Color c;
	Color black = Color(0, 0, 0);
	Color white = Color(255, 255, 255);
	Color mustard = Color(227, 190, 66);
	Color olive = Color(85, 107, 47);

	// TODO: Use an appropriate color for the different backgrounds
	if (engine->GetContext()->GetLevel() == 0 || engine->GetContext()->GetLevel() == 1)
	{
		c = black;
	}
	else if (engine->GetContext()->GetLevel() == 2) {
		c = white;
	}
	else if (engine->GetContext()->GetLevel() == 3) {
		c = black;
	}

	// TODO: Print the current score if it is a singleplayer game
	int level = engine->GetContext()->GetLevel();
	if (level != 0) {
		Graphics::Instance().DrawString(std::to_string(engine->GetContext()->GetScore()), 375,Y_MAX - 290, c, Graphics::ALIGN_CENTER);
	}

	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay
	int state = engine->GetContext()->GetState();
	bool replay = engine->GetContext()->IsReplay();
	if (state == 0 && replay == false) {
		Graphics::Instance().DrawString("Press P to pause, press ESC to quit without saving", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
	}
	else if (replay == true) {
		Graphics::Instance().DrawString("Speed down (left), up (right) or pause (p)", 375, Y_MAX - (-15), c, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("next point (up), level (down) or quit (esc)", 375, Y_MAX - (-45), c, Graphics::ALIGN_CENTER);
	}

	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)
	if (level == 0) {
        if (state == PLAYER_LEFT_SCORES1) {
            Graphics::Instance().DrawString("Player 1 scored!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES2) {
            Graphics::Instance().DrawString("Well done player 1!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES3) {
            Graphics::Instance().DrawString("Keep it going player 1!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES1) {
            Graphics::Instance().DrawString("You've got skills player 2!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES2) {
            Graphics::Instance().DrawString("Way to go player 2!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES3) {
            Graphics::Instance().DrawString("Humiliate player 1!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
		else if (state == PLAYER_LEFT_WINS) {
			Graphics::Instance().DrawString("Player 1 wins!", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
		else if (state == PLAYER_RIGHT_WINS) {
			Graphics::Instance().DrawString("Player 2 wins!", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
	}
	else if (level == 1 && replay == false) {
		if (state == PLAYER_LEFT_SCORES1) {
			Graphics::Instance().DrawString("You scored!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES2) {
            Graphics::Instance().DrawString("Well done!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES3) {
            Graphics::Instance().DrawString("Nice one!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
		else if (state == PLAYER_RIGHT_SCORES1) {
			Graphics::Instance().DrawString("Keep trying!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES2) {
            Graphics::Instance().DrawString("Too hard?", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES3) {
            Graphics::Instance().DrawString("You'll have to try harder!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
		else if (state == LEVEL_WON) {
			Graphics::Instance().DrawString("The slime novice needs more practice to beat you!", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press space to continue or esc to quit without saving", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
		else if (state == LEVEL_LOST) {
			Graphics::Instance().DrawString("Anyone can deal with victory. Only the mighty can bear defeat.", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
	}
	else if (level == 2 && replay == false) {
        if (state == PLAYER_LEFT_SCORES1) {
            Graphics::Instance().DrawString("You scored!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES2) {
            Graphics::Instance().DrawString("Well done!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES3) {
            Graphics::Instance().DrawString("Nice one!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES1) {
            Graphics::Instance().DrawString("Keep trying!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES2) {
            Graphics::Instance().DrawString("Too hard?", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES3) {
            Graphics::Instance().DrawString("You'll have to try harder!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
		else if (state == LEVEL_WON) {
			Graphics::Instance().DrawString("The slime expert clearly was no match for you!", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press space to continue or esc to quit without saving", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
		else if (state == LEVEL_LOST) {
			Graphics::Instance().DrawString("Anyone can deal with victory. Only the mighty can bear defeat.", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
	}
	else if (level == 3 && replay == false) {
        if (state == PLAYER_LEFT_SCORES1) {
            Graphics::Instance().DrawString("You scored!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES2) {
            Graphics::Instance().DrawString("Well done!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_LEFT_SCORES3) {
            Graphics::Instance().DrawString("Nice one!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES1) {
            Graphics::Instance().DrawString("Keep trying!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES2) {
            Graphics::Instance().DrawString("Too hard?", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
        else if (state == PLAYER_RIGHT_SCORES3) {
            Graphics::Instance().DrawString("You'll have to try harder!", 375, Y_MAX - (-30), c, Graphics::ALIGN_CENTER);
        }
		else if (state == LEVEL_WON) {
			Graphics::Instance().DrawString("You're too good at this, get a life...", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press space to continue or esc to quit without saving", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
		else if (state == LEVEL_LOST) {
			Graphics::Instance().DrawString("Anyone can deal with victory. Only the mighty can bear defeat.", 375, Y_MAX - 150, c, Graphics::ALIGN_CENTER);
			Graphics::Instance().DrawString("Press SPACE to play again, press ESC to go back to menu", 375, Y_MAX - 120, c, Graphics::ALIGN_CENTER);
		}
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
	if (level == 0 || level == 1) {
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND1);
	}
	else if (level == 2) {
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND2);
	}
	else {
		Graphics::Instance().SetBackground(Graphics::SPRITE_BACKGROUND3);
	}

	return true;
}
