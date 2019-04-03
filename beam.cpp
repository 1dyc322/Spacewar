#include "splashkit.h"
#include "space_war.h"

//Create New beam.
beam_data new_beam(int ux)
{
    beam_data result;
    result.name = bitmap_named("beam");
    result.x = ux+70;
    result.y = 130;
    return result;
}
// Draw Beam to the screen
void draw_beam(const beam_data &beam_to_draw)
{
    bitmap to_draw;
    to_draw = beam_to_draw.name;
    draw_bitmap(to_draw,beam_to_draw.x,beam_to_draw.y);
}

// Check if beam hit player, return bool.
bool beam_hit_player(const beam_data &beam, const player_data &player)
{
    bitmap beam_bmp = beam.name;
    bitmap player_bmp = player.name;
    return bitmap_collision(beam_bmp,0,beam.x,beam.y,player_bmp,0,player.x,player.y);
}

// beam move to player site
void update_beam(beam_data &beam)
{
   beam.y = beam.y + 15;
}