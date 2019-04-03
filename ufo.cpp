#include "splashkit.h"
#include "space_war.h"
bool turnleft = 1;
bool turnright = 0;
const int speed = 5;

ufo_data new_ufo()
{
    ufo_data result;
    result.name = bitmap_named("ufo");
    result.x = 130;
    result.y = 50;
    result.speed = 5;
    return result;
}
void draw_ufo(const ufo_data &ufo_to_draw)
{
    bitmap to_draw;
    to_draw = bitmap_named("ufo");
    draw_bitmap(to_draw,ufo_to_draw.x,ufo_to_draw.y);

}

void update_ufo(ufo_data &ufo)
{
    if (turnleft)
    {
        ufo.x = ufo.x - ufo.speed;
        if (ufo.x < (20 - rnd(60)))
        {
            turnleft = 0;
            turnright = 1;
        }
    }

    if (turnright)
    {
        ufo.x = ufo.x + ufo.speed;
        if (ufo.x > (240 + rnd (120)))
        {
            turnleft = 1;
            turnright = 0;
        }
    }

}