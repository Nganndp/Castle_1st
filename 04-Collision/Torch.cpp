#include "Torch.h"

void CTorch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	/*left = x;
	top = y;
	right = x + TORCH_BBOX_WIDTH;

	if (state == TORCH_STATE_DIE)
		bottom = y + TORCH_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + TORCH_BBOX_HEIGHT;*/
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure TORCH can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}*/
}

void CTorch::Render()
{
	if (active != true)
		return;
	int ani = TORCH_ANI_WALKING;
	if (state == TORCH_STATE_DIE) {
		ani = TORCH_ANI_DIE;
	}

	animations[ani]->Render(x,y);
	//RenderBoundingBox();
}

void CTorch::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case TORCH_STATE_DIE:
			y += TORCH_BBOX_HEIGHT - TORCH_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case TORCH_STATE_WALKING: 
			vx = -TORCH_WALKING_SPEED;
	}

}
