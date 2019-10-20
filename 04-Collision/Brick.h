#pragma once
#include "GameObject.h"
#include "Simon.h"
#define BRICK_BBOX_WIDTH 32
#define BRICK_BBOX_HEIGHT 32


class CBrick : public CGameObject
{
	public:
		boolean active = true;
		void SetActive(boolean a) { active = a; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
