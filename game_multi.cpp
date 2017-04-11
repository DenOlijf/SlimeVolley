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


		engine.Update();
		
		// Update quit value
		quit = AllegroLib::Instance().IsWindowClosed();
	}

	// Reset game state in context
	context->SetState(0);
}

void GameMulti::AddSystems()
{
	System* systemmotion = (System*) new SystemMotion();
	systemmotion->SetEngine(&engine);
	engine.AddSystem(systemmotion);

	System* systemcollision = (System*) new SystemCollision();
	systemcollision->SetEngine(&engine);
	engine.AddSystem(systemcollision);
	
	System* systemrender = (System*) new SystemRender();
	systemrender->SetEngine(&engine);
	engine.AddSystem(systemrender);
}

void GameMulti::RemoveSystems()
{
	// TODO: Remove all systems from the engine

}

void GameMulti::MakeEntities()
{
	Entity* ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, SLIME_1_INIT_X, BALL_X_OFFSET, X_MAX-BALL_X_OFFSET, BALL_X_OFFSET, BALL_INIT_Y, 2*BALL_X_OFFSET, 299+BALL_Y_OFFSET, BALL_Y_OFFSET));
	ball->Add(new ComponentMotion(0, 0, 0, BALL_A_Y));
	ball->Add(new ComponentBall());
	engine.AddEntity(ball);

	Entity* player1 = new Entity();
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, SLIME_1_INIT_X, 0, 373 /* positie net */ -SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX+SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	player1->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	player1->Add(new ComponentPlayer(1, RADIUS_SLIME));
	engine.AddEntity(player1);

	Entity* player2 = new Entity();
	player2->Add(new ComponentSprite(Graphics::SPRITE_PLAYER2, SLIME_2_INIT_X, 377 /* einde net */, X_MAX-SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX+SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	player2->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	player2->Add(new ComponentPlayer(2, RADIUS_SLIME));
	engine.AddEntity(player2);

	Entity* point1 = new Entity();
	point1->Add(new ComponentSprite(Graphics::SPRITE_POINT, 30, 20, 20, 11, 290, 10, 10, 0));
	point1->Add(new ComponentPoint(1, 1));
	engine.AddEntity(point1);

	Entity* point2 = new Entity();
	point2->Add(new ComponentSprite(Graphics::SPRITE_POINT, 70, 60, 60, 11, 290, 10, 10, 0));
	point2->Add(new ComponentPoint(1, 2));
	engine.AddEntity(point2);

	Entity* point3 = new Entity();
	point3->Add(new ComponentSprite(Graphics::SPRITE_POINT, 110, 100, 100, 11, 290, 10, 10, 0));
	point3->Add(new ComponentPoint(1, 3));
	engine.AddEntity(point3);

	Entity* point4 = new Entity();
	point4->Add(new ComponentSprite(Graphics::SPRITE_POINT, 150, 140, 140, 11, 290, 10, 10, 0));
	point4->Add(new ComponentPoint(1, 4));
	engine.AddEntity(point4);

	Entity* point5 = new Entity();
	point5->Add(new ComponentSprite(Graphics::SPRITE_POINT, 190, 180, 180, 11, 290, 10, 10, 0));
	point5->Add(new ComponentPoint(1, 5));
	engine.AddEntity(point5);

	Entity* point6 = new Entity();
	point6->Add(new ComponentSprite(Graphics::SPRITE_POINT, 230, 220, 220, 11, 290, 10, 10, 0));
	point6->Add(new ComponentPoint(1, 6));
	engine.AddEntity(point6);

	Entity* point7 = new Entity();
	point7->Add(new ComponentSprite(Graphics::SPRITE_POINT, 270, 260, 260, 11, 290, 10, 10, 0));
	point7->Add(new ComponentPoint(1, 7));
	engine.AddEntity(point7);

	Entity* point8 = new Entity();
	point8->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-270, 469, 469, 11, 290, 10, 10, 0));
	point8->Add(new ComponentPoint(2, 1));
	engine.AddEntity(point8);

	Entity* point9 = new Entity();
	point9->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-230, 509, 509, 11, 290, 10, 10, 0));
	point9->Add(new ComponentPoint(2, 2));
	engine.AddEntity(point9);

	Entity* point10 = new Entity();
	point10->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-190, 549, 549, 11, 290, 10, 10, 0));
	point10->Add(new ComponentPoint(2, 3));
	engine.AddEntity(point10);

	Entity* point11 = new Entity();
	point11->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-150, 589, 589, 11, 290, 10, 10, 0));
	point11->Add(new ComponentPoint(2, 4));
	engine.AddEntity(point11);

	Entity* point12 = new Entity();
	point12->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-110, 629, 629, 11, 290, 10, 10, 0));
	point12->Add(new ComponentPoint(2, 5));
	engine.AddEntity(point12);

	Entity* point13 = new Entity();
	point13->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-70, 669, 669, 11, 290, 10, 10, 0));
	point13->Add(new ComponentPoint(2, 6));
	engine.AddEntity(point13);

	Entity* point14 = new Entity();
	point14->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX-30, 709, 709, 11, 290, 290, 290, 0));
	point14->Add(new ComponentPoint(2, 7));
	engine.AddEntity(point14);

	Entity* net = new Entity();
	net->Add(new ComponentSprite(Graphics::SPRITE_NET, 375, 375, 375, NET_X_OFFSET, 39,39,39, 0));
	engine.AddEntity(net);
}

void GameMulti::DestroyEntities()
{
	// TODO: Remove and destroy all entities

}