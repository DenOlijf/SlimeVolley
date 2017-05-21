//Groep 27 system_points.cpp
#include "system_points.h"

#include "component_point.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

void SystemPoints::Update()
{
	// TODO: Set the correct sprites of all entities with point component
	//alle entities met point component nemen
	std::set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::POINT);
	std::set<Entity*>::iterator it;
	
	//punten aanpassen van sprite indien nodig
	for (it = entities.begin(); it != entities.end(); it++) {
		Entity* temp = *it;
		int player = ((ComponentPoint*)temp->GetComponent(Component::POINT))->player_id;
		int point = ((ComponentPoint*)temp->GetComponent(Component::POINT))->point_id;
		if (player == 1) {
			if (point <= engine->GetContext()->GetPoints(1) && point != 0) {
				delete(temp->Remove(temp->GetComponent(Component::SPRITE)));
				temp->Add(new ComponentSprite(Graphics::SPRITE_POINT_P1, 30 + (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
			}
			else {
				delete(temp->Remove(temp->GetComponent(Component::SPRITE)));
				temp->Add(new ComponentSprite(Graphics::SPRITE_POINT, 30 + (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
			}
		}
		else if (player == 2) {
			if (point <= engine->GetContext()->GetPoints(2) && point != 0) {
				delete(temp->Remove(temp->GetComponent(Component::SPRITE)));
				if (engine->GetContext()->GetLevel() == 0 || engine->GetContext()->GetLevel() == 1) {
					temp->Add(new ComponentSprite(Graphics::SPRITE_POINT_P2, X_MAX - 30 - (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
				}
				else if (engine->GetContext()->GetLevel() == 2) {
					temp->Add(new ComponentSprite(Graphics::SPRITE_POINT_O2, X_MAX - 30 - (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
				}
				else {
					temp->Add(new ComponentSprite(Graphics::SPRITE_POINT_O3, X_MAX - 30 - (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
				}
			}
			else {
				delete(temp->Remove(temp->GetComponent(Component::SPRITE)));
				temp->Add(new ComponentSprite(Graphics::SPRITE_POINT, X_MAX -30 - (point - 1) * 40, 0, 0, BALL_X_OFFSET, 290, 0, 0, 0));
			}
		}
	}
}
