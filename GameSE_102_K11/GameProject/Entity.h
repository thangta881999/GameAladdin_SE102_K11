﻿#ifndef _ENTITY_H               // Prevent multiple definitions if this 
#define _ENTITY_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"
#include "Camera.h"
#include <algorithm>

class Entity;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent
{
	Entity* entity;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, Entity* entity = NULL);

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b) {
		return a->t < b->t;
	}
};

class Entity : public Image
{
	// Entity properties
protected:
	D3DXVECTOR2 center;         // center of entity
	RECT    edge;           // for BOX and ROTATED_BOX collision detection

	D3DXVECTOR2 velocity;       // velocity
	D3DXVECTOR2 deltaV;         // added to velocity during next call to update()

	float   health;         // health 0 to 100
	float   gravity;        // gravitational constant of the game universe
	
	HRESULT hr;             // standard return type
	bool    active;         // only active entities may collide

	int state;

	int type;	// loại object để phân biệt nhau
	int kind;	// loại chung của object. (ex: apple, gem, heart -> items, nahbi ->enemies)

	float dx, dy;

	bool finished;

public:
	// Constructor
	Entity();
	// Destructor
	virtual ~Entity() { }

	////////////////////////////////////////
	//           Get functions            //
	////////////////////////////////////////

	// Return center of scaled Entity as screen x,y.
	virtual const D3DXVECTOR2* getCenter()
	{
		center = D3DXVECTOR2(getCenterX(), getCenterY());
		return &center;
	}

	// Return RECT structure used for BOX and ROTATED_BOX collision detection.
	virtual const RECT& getEdge() const { return edge; }

	// Return velocity vector.
	virtual const D3DXVECTOR2 getVelocity() const { return velocity; }

	// Return active.
	virtual bool  getActive()         const { return active; }

	// Return gravitational constant.
	virtual float getGravity()        const { return gravity; }

	// Return health;
	virtual float getHealth()         const { return health; }

	// Return State
	virtual int getState()			  const { return state; }

	virtual float getDX() { return dx; }
	virtual float getDY() { return dy; }

	virtual int   getType() { return type; }
	virtual int	  getKind() { return kind; }

	virtual void getBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void RenderBoundingBox(Camera* camera);

	////////////////////////////////////////
	//           Set functions            //
	////////////////////////////////////////

	// Set velocity.
	virtual void  setVelocity(D3DXVECTOR2 v) { velocity = v; }
	virtual void  setVelocityX(float x) { velocity.x = x; }
	virtual void  setVelocityY(float y) { velocity.y = y; }

	// Set delta velocity. Added to velocity in update().
	virtual void  setDeltaV(D3DXVECTOR2 dv) { deltaV = dv; }

	// Set active.
	virtual void  setActive(bool a) { active = a; }

	// Set health.
	virtual void setHealth(float h) { health = h; }

	// Set gravitational constant. Default is 6.67428e-11
	virtual void  setGravity(float g) { gravity = g; }

	// Set RECT structure used for BOX and ROTATED_BOX collision detection.
	virtual void setEdge(RECT e) { edge = e; }

	virtual void setDX(float dx) { this->dx = dx; }
	virtual void setDY(float dy) { this->dy = dy; }

	// Set state
	virtual void setState(int state) { this->state = state; }
	virtual void setKind(int kind) { this->kind = kind; }

	virtual void setFinished(bool finish) { this->finished = finish; }
	virtual bool getFinished() { return this->finished; }
	////////////////////////////////////////
	//         Other functions            //
	////////////////////////////////////////

	// Update Entity.
	// typically called once per frame
	// frameTime is used to regulate the speed of movement and animation
	virtual void update(float frameTime);

	virtual void update(std::vector<Entity*>* listObj, float frameTime)
	{
		update(frameTime);
	};

	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);

	// Activate Entity.
	virtual void activate();

	// Is this entity outside the specified rectangle?
	virtual bool outsideRect(RECT rect);

	// Damage this Entity with weapon.
	virtual void damage(int weapon);


	LPCOLLISIONEVENT SweptAABBEx(Entity* ent2, float frameTime);

	void SweptAABB(
		float ml, //move left
		float mt, //move top
		float mr, //move right
		float mb, //move bottom
		float dx,
		float dy,
		float sl, //static left
		float st, //static top
		float sr, //static right
		float sb, //static bottom
		float& t,
		float& nx,
		float& ny);

	void CalcPotentialCollisions(std::vector<Entity*>* coEntities, std::vector<LPCOLLISIONEVENT>& coEvents, float frameTime);
	void FilterCollision(
		std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	bool checkAABB(Entity* ent);
	bool checkAABB(float b1left, float b1top, float b1right, float b1bottom, float b2left, float b2top, float b2right, float b2bottom);
	bool isCollitionObjectWithObject(Entity* ent, float frameTime);	// kiểm tra bằng AABB và Sweept AABB

};

#endif