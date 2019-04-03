#include "splashkit.h"
#include "space_war.h"
// coordinate data
int left = 10;
int top = 20;
// color data
int aliencolor = 0;
bitmap alien_bitmap(alien_kind kind)
{
    switch(kind)
    {
        case RED:
            return bitmap_named("redalien");
            break;
        case BLUE:
            return bitmap_named("bluealien");
            break;
        default:
            return bitmap_named("greenalien");
    }
}
// choose alien kind by sequence
alien_kind choose_alien_kind()
{
return static_cast<alien_kind>( aliencolor );
}

// When a new game start, will call this function to reset the data.
void alien_new_game()
{
left = 10;
top = 20;
aliencolor = 0;
}

alien_data new_alien()
{
    alien_data result;
    // Create different aliens. Divide by rows
    if (left > 410)
    {
        left = 10;
        top = top + 30;
        aliencolor ++;
    }
    result.kind = choose_alien_kind();
    result.x = left;
    result.y = top;
    
    left = left + 70;

    return result;
}

void draw_alien(const alien_data &alien_to_draw)
{
    bitmap to_draw;
    to_draw = alien_bitmap(alien_to_draw.kind);
    draw_bitmap(to_draw,alien_to_draw.x,alien_to_draw.y);
    
}

