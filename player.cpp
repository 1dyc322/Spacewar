#include "splashkit.h"
#include "space_war.h"

// Create new player
player_data new_player()
{
    player_data result;
    result.name = bitmap_named("player");
    result.x = 160;
    result.y = 400;
    return result;
}
// Draw player image to screen
void draw_player(const player_data &player_to_draw)
{
    bitmap to_draw;
    to_draw = bitmap_named("player");
    draw_bitmap(to_draw,player_to_draw.x,player_to_draw.y);

}

// handle user input keys to control the jet.
void handle_input( player_data &player)
{
    if ( key_down(RIGHT_KEY) && player.x < screen_width() - 50) player.x += 10 ;
    if ( key_down(LEFT_KEY)&& player.x > 0) player.x -= 10;
}