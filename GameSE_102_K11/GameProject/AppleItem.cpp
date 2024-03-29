#include "AppleItem.h"

AppleItem::AppleItem(float x, float y)
{
	spriteData.x = x;
	spriteData.y = y;
	type = eType::APPLES;
	kind = eKind::ITEM;
}

AppleItem::~AppleItem()
{
}

void AppleItem::update(std::vector<Entity*>* listObj, float frameTime)
{
	Entity::update(listObj, frameTime);
	if (health == 0.0f)
	{
		if (currentFrame > 5 && currentFrame < 9)
			frameDelay = 0.15f;
		else frameDelay = 0.05f;
		if (currentFrame == 11)
			visible = false;
	}

}

void AppleItem::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (health != 0.0f)
	{
		Entity::getBoundingBox(left, top, right, bottom);
	}

}

void AppleItem::setState(int state)
{
	Entity::setState(state);
	if (state == EXPLOSIVE_ITEM)
	{
		health = 0.0f;
		setTextureManager(TextureManager::getIntance()->getTexture((eType)state));
		setFrames(0, 11);
		currentFrame = 0;
		frameDelay = 0.05f;
	}
}
