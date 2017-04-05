#pragma once

#include <map>
#include <set>

#include "component.h"
#include "entity.h"

using namespace std;

class EntityStream
{
public:
	EntityStream::EntityStream()
	{
	}

	EntityStream::~EntityStream()
	{
	}

	std::set<Entity*> WithTag(Component::Tag tag);
	std::set<Entity*> WithTags(std::set<Component::Tag> tags);
	void EntityAdded(Entity* entity);
	void EntityRemoved(Entity* entity);

private:
	std::map<Component::Tag, std::set<Entity*>> index;
};
