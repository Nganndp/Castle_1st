#pragma once
#include <iostream>
#include <memory>
#include "GameObject.h"
#include "MS.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define PULL_UP_SIMON_AFTER_SITTING 10.0f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_SQUAT		500

#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK 500
#define SIMON_STATE_SIT 600

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1

#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_ATTACK_RIGHT				4
#define SIMON_ANI_ATTACK_LEFT				5
#define SIMON_ANI_JUMP_RIGHT 6
#define SIMON_ANI_JUMP_LEFT 7
#define SIMON_ANI_SIT_RIGHT 8
#define SIMON_ANI_SIT_LEFT 9
#define SIMON_ANI_DIE		99		

//#define SIMON_PULL_SIT 18.0f
#define SIMON_IDLE_BBOX_WIDTH  16
#define SIMON_IDLE_BBOX_HEIGHT 30
#define SIMON_SIT_BBOX_HEIGHT 20

#define SIMON_JUMP_TIME 500
#define SIMON_ATTACK_TIME 300


class CSimon: public CGameObject
{
	int jump;
	int attack;
	int right;
	bool active = true;
	bool sit = false;
	DWORD jump_start;
	DWORD attack_start;
public: 
	CSimon() : CGameObject()
	{
		jump = 0;
		attack = 0;
		sit = false;
	}
	void StandUp();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetRight(int right) {
		right = right;
	};
	boolean GetActive() { return active; };
	void SetActive(boolean a) {
		active = a;
	}
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
	void StartAttack() { attack = 1; attack_start = GetTickCount(); }
	void SetSit(boolean a) { sit= a; };
	void CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};