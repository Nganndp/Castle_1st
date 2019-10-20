#include <algorithm>
#include<vector>
#include "debug.h"

#include "SIMON.h"
#include "Game.h"

#include "Torch.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - jump_start > SIMON_JUMP_TIME) 
	{
		jump_start = 0;
		jump = 0;
	}
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		attack = 0;
	}
	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState()!= GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -SIMON_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSimon::Render()
{
	if (active != true)
		return;
	int ani;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (state == SIMON_STATE_SIT)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
		else ani = SIMON_ANI_SIT_LEFT;
	}
	else if (state == SIMON_STATE_IDLE)
	{
		if (vx == 0)
		{
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
		}
	}
	else if (state == SIMON_STATE_WALKING_RIGHT)
	{
		ani = SIMON_ANI_WALKING_RIGHT;
	}
	else if (state == SIMON_STATE_WALKING_LEFT)
	{
	    ani = SIMON_ANI_WALKING_LEFT;
	}
	if (attack != 0)
		{
			if (nx > 0)
				ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}
	if (jump != 0)
	{
		if (nx > 0)
			ani = SIMON_ANI_JUMP_RIGHT;
		else ani = SIMON_ANI_JUMP_LEFT;
	}
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		vx = 0;
		break;
	case SIMON_STATE_SIT:
		vx = 0;
		SetSit(true);
		break;
	}
}

void CSimon::StandUp()
{
	y = y - PULL_UP_SIMON_AFTER_SITTING;
	sit = false;
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + SIMON_IDLE_BBOX_WIDTH;
	bottom = y + SIMON_IDLE_BBOX_HEIGHT;

	if (state == SIMON_STATE_SIT || state == SIMON_STATE_JUMP)
	{
		right = x + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

