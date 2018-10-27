#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__

#define SAFE_RELEASE(p) if ( (p) ) { (p)->Release(); (p) = NULL; }
#define SAFE_DELETE(a) if( (a) ) { delete (a); (a) = NULL; }

namespace Define
{
    const float PLAYER_MAX_JUMP_VELOCITY = 480.0f; //van toc nhay lon nhat
    const float PLAYER_MIN_JUMP_VELOCITY = -480.0f; //van toc nhay thap nhat
    const float PLAYER_MAX_RUNNING_SPEED = 350.0f; //toc do chay nhanh nhat cua player
    const float PLAYER_BOTTOM_RANGE_FALLING = 6.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
}

#endif
