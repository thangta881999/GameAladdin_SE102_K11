#ifndef _GEMITEM_H
#define _GEMITEM_H

#include "Entity.h"
#include "Camera.h"
#include "MapGame.h"


class GemItem : public Entity
{
private:

public:
	GemItem(float x, float y);
	~GemItem();
	void update(std::vector<Entity*>* listObj, float frameTime);
	void getBoundingBox(float& left, float& top, float& right, float& bottom);
	void setState(int state);
};

#endif