#include "splashkit.h"
#include "space_war.h"


void load_resources()
{
    load_resource_bundle("game_bundle", "space_war.txt");
}


int main()
{
    // Create a new window.
    open_window("Space WAR", 400, 500);
    // Load resources, such a image, font and sound
    load_resources();
    // Create a new Game.
    space_war_data game;
    game = new_game();


    
    while ( not quit_requested() )
    {
        process_events();
        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }

    return 0;
}