#include "game_single.h"

#include "allegro_lib.h"
#include "component_ball.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_point.h"
#include "component_sprite.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"

GameSingle::GameSingle(Context* _context, int _level) :
	context(_context),
	engine(_context),
	level(_level)
{
	AddSystems();
	MakeEntities();
	context->SetLevel(level);
};

GameSingle::~GameSingle()
{
	RemoveSystems();
	DestroyEntities();
}

int GameSingle::Run()
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
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();

		// TODO: If event key down, toggle key in context
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			engine.GetContext()->ToggleKey(event.keyboard.keycode, true);
		}

		// TODO: If event key up, untoggle key in context
		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			engine.GetContext()->ToggleKey(event.keyboard.keycode, false);
		}

		// TODO: If event timer, update engine
		if (event.type == ALLEGRO_EVENT_TIMER) {
			engine.Update();
		}

		// Update quit value
		quit = AllegroLib::Instance().IsWindowClosed();
	}

	// Reset game state in context and return
	int state = context->GetState();
	context->SetState(0);
	return state;
}

void GameSingle::AddSystems()
{
	// TODO: Add all systems to the engine
	sis = SystemInputSingle();
	engine.AddSystem(&sis);

	smot = SystemMotion();
	engine.AddSystem(&smot);

	scoll = SystemCollision();
	engine.AddSystem(&scoll);

	seyes = SystemEyes();
	engine.AddSystem(&seyes);

	sss = SystemStateSingle();
	engine.AddSystem(&sss);

	sp = SystemPoints();
	engine.AddSystem(&sp);
	
	sr = SystemRender();
	engine.AddSystem(&sr);

}

void GameSingle::RemoveSystems()
{
	// TODO: Remove all systems from the engine
	engine.RemoveSystem(&sis);
	engine.RemoveSystem(&smot);
	engine.RemoveSystem(&scoll);
	engine.RemoveSystem(&seyes);
	engine.RemoveSystem(&sss);
	engine.RemoveSystem(&sp);
	engine.RemoveSystem(&sr);

}

void GameSingle::MakeEntities()
{
	// TODO: Initialize required entities and add them to the engine
	Entity* ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, SLIME_1_INIT_X, BALL_X_OFFSET, X_MAX - BALL_X_OFFSET, BALL_X_OFFSET, BALL_INIT_Y, BALL_X_OFFSET, 299 + BALL_Y_OFFSET, BALL_Y_OFFSET));
	ball->Add(new ComponentMotion(0, 0, 0, BALL_A_Y));
	ball->Add(new ComponentBall());
	engine.AddEntity(ball);

	Entity* player1 = new Entity();
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, SLIME_1_INIT_X, SLIME_X_OFFSET, 372 /* positie net */ - SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX + SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	player1->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	player1->Add(new ComponentPlayer(1, RADIUS_SLIME));
	engine.AddEntity(player1);

	Entity* ai = new Entity();
	if (engine.GetContext()->GetLevel() == 1) {
		ai->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT1, SLIME_2_INIT_X, 377 /* einde net */ + SLIME_X_OFFSET, X_MAX - SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX + SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	}
	else if (engine.GetContext()->GetLevel() == 2) {
		ai->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT2, SLIME_2_INIT_X, 377 /* einde net */ + SLIME_X_OFFSET, X_MAX - SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX + SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	}
	else {
		ai->Add(new ComponentSprite(Graphics::SPRITE_OPPONENT3, SLIME_2_INIT_X, 377 /* einde net */ + SLIME_X_OFFSET, X_MAX - SLIME_X_OFFSET, SLIME_X_OFFSET, 0, 0, Y_MAX + SLIME_Y_OFFSET, SLIME_Y_OFFSET));
	}
	ai->Add(new ComponentMotion(0, 0, 0, SLIME_A_Y));
	ai->Add(new ComponentPlayer(2, RADIUS_SLIME));
	engine.AddEntity(ai);

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
	point8->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 270, 469, 469, 11, 290, 10, 10, 0));
	point8->Add(new ComponentPoint(2, 7));
	engine.AddEntity(point8);

	Entity* point9 = new Entity();
	point9->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 230, 509, 509, 11, 290, 10, 10, 0));
	point9->Add(new ComponentPoint(2, 6));
	engine.AddEntity(point9);

	Entity* point10 = new Entity();
	point10->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 190, 549, 549, 11, 290, 10, 10, 0));
	point10->Add(new ComponentPoint(2, 5));
	engine.AddEntity(point10);

	Entity* point11 = new Entity();
	point11->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 150, 589, 589, 11, 290, 10, 10, 0));
	point11->Add(new ComponentPoint(2, 4));
	engine.AddEntity(point11);

	Entity* point12 = new Entity();
	point12->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 110, 629, 629, 11, 290, 10, 10, 0));
	point12->Add(new ComponentPoint(2, 3));
	engine.AddEntity(point12);

	Entity* point13 = new Entity();
	point13->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 70, 669, 669, 11, 290, 10, 10, 0));
	point13->Add(new ComponentPoint(2, 2));
	engine.AddEntity(point13);

	Entity* point14 = new Entity();
	point14->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX - 30, 709, 709, 11, 290, 290, 290, 0));
	point14->Add(new ComponentPoint(2, 1));
	engine.AddEntity(point14);

	Entity* net = new Entity();
	net->Add(new ComponentSprite(Graphics::SPRITE_NET, 375, 375, 375, NET_X_OFFSET, 39, 39, 39, 0));
	engine.AddEntity(net);

}

void GameSingle::DestroyEntities()
{
	// TODO: Remove and destroy all entities
	//alle sprite componenten van de entities deleten
	std::set<Entity*> sprites = engine.GetEntityStream()->WithTag(Component::SPRITE);
	std::set<Entity*>::iterator it_sprites;
	for (it_sprites = sprites.begin(); it_sprites != sprites.end(); it_sprites++) {
		Entity* temp = *it_sprites;
		delete(temp->Remove(temp->GetComponent(Component::SPRITE)));
	}

	//alle player componenten van de entities deleten
	std::set<Entity*> players = engine.GetEntityStream()->WithTag(Component::PLAYER);
	std::set<Entity*>::iterator it_players;
	for (it_players = players.begin(); it_players != players.end(); it_players++) {
		Entity* temp = *it_players;
		delete(temp->Remove(temp->GetComponent(Component::PLAYER)));
	}

	//alle motion componenten van de entities deleten
	std::set<Entity*> motions = engine.GetEntityStream()->WithTag(Component::MOTION);
	std::set<Entity*>::iterator it_motions;
	for (it_motions = motions.begin(); it_motions != motions.end(); it_motions++) {
		Entity* temp = *it_motions;
		delete(temp->Remove(temp->GetComponent(Component::MOTION)));
	}

	//alle point componenten van de entities deleten
	std::set<Entity*> points = engine.GetEntityStream()->WithTag(Component::POINT);
	std::set<Entity*>::iterator it_points;
	for (it_points = points.begin(); it_points != points.end(); it_points++) {
		Entity* temp = *it_points;
		delete(temp->Remove(temp->GetComponent(Component::POINT)));
	}

	//alle ball componenten van de entities deleten
	std::set<Entity*> ball = engine.GetEntityStream()->WithTag(Component::BALL);
	std::set<Entity*>::iterator it_ball = ball.begin();
	Entity* temp = *it_ball;
	delete(temp->Remove(temp->GetComponent(Component::BALL)));

	//de entities zelf deleten
	std::vector<Entity*> entities = engine.GetEntities();
	std::vector<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		engine.RemoveEntity(*it);
		delete(*it);
	}
}
