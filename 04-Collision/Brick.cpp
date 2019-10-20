#include <algorithm>
#include "Brick.h"
#include "debug.h"
#include "Game.h"

#include "Torch.h"

void CBrick::Render()
{
	if (active != true)
		return;
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
