#pragma once
#include "GameObject.h"

#define TORCH_WALKING_SPEED 0.05f;

#define TORCH_BBOX_WIDTH 16
#define TORCH_BBOX_HEIGHT 15
#define TORCH_BBOX_HEIGHT_DIE 9

#define TORCH_STATE_WALKING 100
#define TORCH_STATE_DIE 200

#define TORCH_ANI_WALKING 0
#define TORCH_ANI_DIE 1

class CTorch : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();


public: 	
	boolean active = true;
	virtual void SetState(int state);
};