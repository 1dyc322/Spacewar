#include "splashkit.h"
#include "space_war.h"
// Create bullet function
bullet_data new_bullet(int px)
{
    bullet_data result;
    result.name = bitmap_named("bullet");
    result.x = px+30;
    result.y = screen_height() - 80;
    return result;
}
// Draw a bullet on th screen
void draw_bullet(const bullet_data &bullet_to_draw)
{
    bitmap to_draw;
    to_draw = bullet_to_draw.name;
    draw_bitmap(to_draw,bullet_to_draw.x,bullet_to_draw.y);
}
//Check if bullet hit Ufo, return bool
bool bullet_hit_ufo(const bullet_data &bullet, const ufo_data &ufo)
{
    
    bitmap bullet_bmp = bullet.name;
    bitmap ufo_bmp = ufo.name;
    return bitmap_collision(bullet_bmp,0,bullet.x,bullet.y,ufo_bmp,0,ufo.x,ufo.y);
}

//Check if bullet hit alien, return bool
bool bullet_hit_alien(const bullet_data &bullet, const alien_data &alien)
{
    
    bitmap bullet_bmp = bullet.name;
    bitmap alien_bmp = alien_bitmap(alien.kind);
    return bitmap_collision(bullet_bmp,0,bullet.x,bullet.y,alien_bmp,0,alien.x,alien.y);
}

// Move bullet to enermy site, by looping this function
void update_bullet(bullet_data &bullet)
{
   bullet.y = bullet.y - 15;
}