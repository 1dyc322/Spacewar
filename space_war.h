#include "splashkit.h"
#define PLAYER_SPEED 5
#include <vector>
using namespace std;

enum alien_kind
{
    RED,
    BLUE,
    GREEN,
};

struct player_data
{
    bitmap name;
    double x;
    double y;
};

struct bullet_data
{
    bitmap name;
    double x;
    double y;
};

struct ufo_data
{
    bitmap name;
    double x;
    double y;
    int speed;
};

struct beam_data
{
    bitmap name;
    double x;
    double y;
};

struct cannon_data
{
    bitmap name;
    double x;
    double y;
};

struct alien_data
{
    alien_kind kind;
    double x;
    double y;
};




struct space_war_data
{

    player_data player;
    vector<ufo_data> ufos;
    vector<bullet_data> bullets;
    vector<beam_data> beams;
    vector<cannon_data> cannons;
    vector<alien_data> aliens;
};

// player
void handle_input( player_data &player);
player_data new_player();
void draw_player(const player_data &player_to_draw);

// ufo
ufo_data new_ufo();
void draw_ufo(const ufo_data &ufo_to_draw);
void update_ufo(ufo_data &ufo);
void add_ufo(space_war_data &game);
void remove_ufo(vector<ufo_data> &ufos, int idx);

// game
space_war_data new_game();
void draw_game(space_war_data &game);
void update_game(space_war_data &game);

// bullet
bullet_data new_bullet(int px);
void update_bullet(bullet_data &bullet);
void draw_bullet(const bullet_data &bullet_to_draw);
bool bullet_hit_ufo(const bullet_data &bullet, const ufo_data &ufo);
bool bullet_hit_alien(const bullet_data &bullet, const alien_data &alien);

// alien
alien_data new_alien();
void draw_alien(const alien_data &alien_to_draw);
void add_alien(space_war_data &game);
bitmap alien_bitmap(alien_kind kind);
void update_alien(alien_data &alien);
void remove_alien(vector<alien_data> &aliens, int idx);
void alien_new_game();

// beam
beam_data new_beam(int ux);
void update_beam(beam_data &beam);
void draw_beam(const beam_data &beam_to_draw);
bool beam_hit_player(const beam_data &beam, const player_data &player);

// cannon
cannon_data new_cannon(int ax, int ay);
void update_cannon(cannon_data &cannon);
void draw_cannon(const cannon_data &cannon_to_draw);
bool cannon_hit_player(const cannon_data &cannon, const player_data &player);
void add_cannon(space_war_data &game);