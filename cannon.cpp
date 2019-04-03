#include "splashkit.h"
#include "space_war.h"

//Create a new cannon
cannon_data new_cannon(int ax, int ay)
{
    cannon_data result;
    result.name = bitmap_named("cannon");
    result.x = ax+10;
    result.y = ay+5;
    return result;
}
// Draw cannon images on the screen
void draw_cannon(const cannon_data &cannon_to_draw)
{
    bitmap to_draw;
    to_draw = cannon_to_draw.name;
    draw_bitmap(to_draw,cannon_to_draw.x,cannon_to_draw.y);
}

// Check if cannon hit player, return bool
bool cannon_hit_player(const cannon_data &cannon, const player_data &player)
{
    
    bitmap cannon_bmp = cannon.name;
    bitmap player_bmp = player.name;
    return bitmap_collision(cannon_bmp,0,cannon.x,cannon.y,player_bmp,0,player.x,player.y);
}

// Move cannon to player site by looping this function
void update_cannon(cannon_data &cannon)
{
   cannon.y = cannon.y + 8;
}