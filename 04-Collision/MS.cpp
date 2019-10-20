#include "MS.h"
#include "Simon.h"

void CMS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	
	if (GetTickCount() - attack_start > MS_ATTACK_TIME)
	{
		attack_start = 0;
		attack = 0;
	}
	SetWhipFacing();
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	// block 
	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	y += min_ty * dy + ny * 0.4f;

	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;

	for (UINT i = 0; i < coEventsResult.size(); i++) {

		LPCOLLISIONEVENT e = coEventsResult[i];

		//if (dynamic_cast<FirePilar*>(e->obj))
		//{
		//	FirePilar* fire = dynamic_cast<FirePilar*>(e->obj);
		//	if (e->ny < 0) {

		//	}
		//	//delete FirePilar here
		//}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMS::Render() {
	if (active != true || simon->vx != 0)
	{
		return;
	}
	if (attack == 0)
	{
		active = false;
	}
	int ani;
		if (simon->nx > 0)
			{
				ani = 0;
			}
			else 
				ani = 1; 
    int alpha = 255;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMS::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case WHIP_STATE_ATTACK:
		isAttack = true;
		break;

	}

}
void CMS::SetWhipFacing()
{
	if (simon->nx > 0)
		{

		if (animations[0]->GetCurrentFrame() == 0) {
			x = simon->x - 7;
			y = simon->y + 2;
		}

		else if (animations[0]->GetCurrentFrame() == 1) {
			x = simon->x - 16;
			y = simon->y;
		}

		else if (animations[0]->GetCurrentFrame() == 2) {
			x = simon->x + 16;
			y = simon->y + 6;
		}
		}
	else if (simon->nx < 0)
		{
			if (animations[1]->GetCurrentFrame() == 0) {
				x = simon->x + 18;
				y = simon->y + 2;
			}

			else if (animations[1]->GetCurrentFrame() == 1) {
				x = simon->x + 16;
				y = simon->y;
			}

			else if (animations[1]->GetCurrentFrame() == 2) {
				x = simon->x - 20;
				y = simon->y + 6;
			}
		}
	}
void CMS::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + 22;
	bottom = y + 10;

}
