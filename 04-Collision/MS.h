#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"

#define WHIP_NORMAL		0
#define WHIP_PURPLE		1
#define WHIP_YELLOW		2
#define WHIP_RED		3

#define WHIP_STATE_ATTACK 1
#define MS_ATTACK_TIME 300

#define WHIP_ANI_NORMAL_RIGHT	0
#define WHIP_ANI_NORMAL_LEFT	1
#define WHIP_ANI_PURPLE_RIGHT	2
#define WHIP_ANI_PURPLE_LEFT	3

#define WHIP_NORMAL_BOX_WIDTH	15
#define WHIP_NORMAL_BOX_HEIGHT	15

#define WHIP_LONG_BOX_WIDTH		18
#define WHIP_LONG_BOX_HEIGHT	15

class CMS :public CGameObject
{
public:
	bool isAttack;
	int type;
	int attack;
	CGameObject* simon;
	DWORD attack_start;
	int attackStart;
	boolean active = false;
public:
	CMS() :CGameObject()
	{
		isAttack = false;
		type = WHIP_NORMAL;
		attack = 0;

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetActive(boolean a)
	{
		active = a;
	}
	void StartAttack() { attack = 1; attack_start = GetTickCount(); }
	void SetLevel(int l) { type = l; }
	void GetSimon(CGameObject* Simon) {
		simon = Simon; 
	}
	void SetWhipFacing();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

