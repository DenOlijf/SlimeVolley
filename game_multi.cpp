#include "game_multi.h"

#include "allegro_lib.h"
#include "component_ball.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_point.h"
#include "component_sprite.h"
#include "constants.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

GameMulti::GameMulti(Context* _context) :
	context(_context),
	engine(_context)
{
	AddSystems();
	MakeEntities();
	context->SetLevel(0);
};

GameMulti::~GameMulti()
{
	RemoveSystems();
	DestroyEntities();
}

void GameMulti::Run()
{
	// Initialize game loop
	AllegroLib::Instance().StartLoop();
	bool quit = AllegroLib::Instance().IsWindowClosed();

	// Enter game loop
	while (!quit && context->GetState() <= 0)
	{
		// Start Allegro iteration
		AllegroLib::Instance().StartIteration();

		// TODO: Get the current Allegro event

		// TODO: If event key down, toggle key in context

		// TODO: If event key up, untoggle key in context

		// TODO: If event timer, update engine

		// The following six lines clear the screen, redraw the background,
		// draw sprites and render both to screen. This should be handled by
		// the render system, but is here to make sure Allegro works properly.
		//Graphics::Instance().ClearScreen();
		//Graphics::Instance().DrawBackground();
		/*Graphics::Instance().DrawBitmap(Graphics::SPRITE_PLAYER1, 150, 299 - 0, 39, 39);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_PLAYER2, 600, 299 - 0, 39, 39);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_BALL, 150, 299 - 133.5, 11, 11);
		Graphics::Instance().ExecuteDraws();*/

		engine.Update();
		
		// Update quit value
		quit = AllegroLib::Instance().IsWindowClosed();
	}

	// Reset game state in context
	context->SetState(0);
}

void GameMulti::AddSystems()
{
	System* temp = (System*) new SystemRender();
	temp->SetEngine(&engine);
	engine.AddSystem(temp);

}

void GameMulti::RemoveSystems()
{
	// TODO: Remove all systems from the engine

}

void GameMulti::MakeEntities()
{
	Entity* ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, 150, BALL_X_OFFSET, 738, BALL_X_OFFSET, BALL_INIT_Y, BALL_Y_OFFSET, 288, BALL_Y_OFFSET));
	ball->Add(new ComponentMotion(0, 0, 0, BALL_A_Y));
	ball->Add(new ComponentBall());
	engine.AddEntity(ball);

	Entity* player1 = new Entity();
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, SLIME_1_INIT_X, SLIME_X_OFFSET, 710, SLIME_X_OFFSET, SLIME_X_OFFSET, SLIME_X_OFFSET, 260, SLIME_Y_OFFSET));
	player1->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	player1->Add(new ComponentPlayer(1, RADIUS_SLIME));
	engine.AddEntity(player1);

	Entity* player2 = new Entity();
	player2->Add(new ComponentSprite(Graphics::SPRITE_PLAYER2, SLIME_2_INIT_X, SLIME_X_OFFSET, 710, SLIME_X_OFFSET, SLIME_X_OFFSET, SLIME_X_OFFSET, 260, SLIME_Y_OFFSET));
	player2->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	player2->Add(new ComponentPlayer(2, RADIUS_SLIME));
	engine.AddEntity(player2);

	Entity* point1 = new Entity();
	point1->Add(new ComponentSprite(Graphics::SPRITE_POINT, 20, 20, 20, 0, 239, 239, 239, 0));
	point1->Add(new ComponentPoint(1, 1));
	engine.AddEntity(point1);

	Entity* point2 = new Entity();
	point2->Add(new ComponentSprite(Graphics::SPRITE_POINT, 50, 50, 50, 0, 239, 239, 239, 0));
	point2->Add(new ComponentPoint(1, 2));
	engine.AddEntity(point2);

	Entity* point3 = new Entity();
	point3->Add(new ComponentSprite(Graphics::SPRITE_POINT, 80, 80, 80, 0, 239, 239, 239, 0));
	point3->Add(new ComponentPoint(1, 3));
	engine.AddEntity(point3);

	Entity* point4 = new Entity();
	point4->Add(new ComponentSprite(Graphics::SPRITE_POINT, 110, 110, 110, 0, 239, 239, 239, 0));
	point4->Add(new ComponentPoint(1, 4));
	engine.AddEntity(point4);

	Entity* point5 = new Entity();
	point5->Add(new ComponentSprite(Graphics::SPRITE_POINT, 140, 140, 140, 0, 239, 239, 239, 0));
	point5->Add(new ComponentPoint(1, 5));
	engine.AddEntity(point5);

	Entity* point6 = new Entity();
	point6->Add(new ComponentSprite(Graphics::SPRITE_POINT, 170, 170, 170, 0, 239, 239, 239, 0));
	point6->Add(new ComponentPoint(1, 6));
	engine.AddEntity(point6);

	Entity* point7 = new Entity();
	point7->Add(new ComponentSprite(Graphics::SPRITE_POINT, 200, 200, 200, 0, 239, 239, 239, 0));
	point7->Add(new ComponentPoint(1, 7));
	engine.AddEntity(point7);

	Entity* point8 = new Entity();
	point8->Add(new ComponentSprite(Graphics::SPRITE_POINT, 395, 395, 395, 0, 239, 239, 239, 0));
	point8->Add(new ComponentPoint(2, 1));
	engine.AddEntity(point8);

	Entity* point9 = new Entity();
	point9->Add(new ComponentSprite(Graphics::SPRITE_POINT, 415, 415, 415, 0, 239, 239, 239, 0));
	point9->Add(new ComponentPoint(2, 2));
	engine.AddEntity(point9);

	Entity* point10 = new Entity();
	point10->Add(new ComponentSprite(Graphics::SPRITE_POINT, 435, 435, 435, 0, 239, 239, 239, 0));
	point10->Add(new ComponentPoint(2, 3));
	engine.AddEntity(point10);

	Entity* point11 = new Entity();
	point11->Add(new ComponentSprite(Graphics::SPRITE_POINT, 455, 455, 455, 0, 239, 239, 239, 0));
	point11->Add(new ComponentPoint(2, 4));
	engine.AddEntity(point11);

	Entity* point12 = new Entity();
	point12->Add(new ComponentSprite(Graphics::SPRITE_POINT, 475, 475, 475, 0, 239, 239, 239, 0));
	point12->Add(new ComponentPoint(2, 5));
	engine.AddEntity(point12);

	Entity* point13 = new Entity();
	point13->Add(new ComponentSprite(Graphics::SPRITE_POINT, 495, 495, 495, 0, 239, 239, 239, 0));
	point13->Add(new ComponentPoint(2, 6));
	engine.AddEntity(point13);

	Entity* point14 = new Entity();
	point14->Add(new ComponentSprite(Graphics::SPRITE_POINT, 515, 515, 515, 0, 239, 239, 239, 0));
	point14->Add(new ComponentPoint(2, 7));
	engine.AddEntity(point14);

	Entity* net = new Entity();
	net->Add(new ComponentSprite(Graphics::SPRITE_NET, 375, 375, 375, 0, 0, 0, 0, 0));
	engine.AddEntity(net);
}

void GameMulti::DestroyEntities()
{
	// TODO: Remove and destroy all entities

}