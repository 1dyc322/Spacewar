#include "splashkit.h"
#include "space_war.h"
using namespace std;
int alien = 18;
int ufohp = 100;
int playerhp = 20;
bool theend = 0;
bool win = 0;
int stage = 0;
bool create = 0;

// Create a new game by calling this function
space_war_data new_game() {
  space_war_data result;
  // Create a player and aliens initially
  result.player = new_player();
  add_alien(result);
  return result;
}
// Draw the related component on the screen
void draw_game(space_war_data & game) {
  clear_screen(COLOR_BLACK);
  // check if the game is end.
  if (theend == 0) {
    //draw background
    draw_bitmap(bitmap_named("background"),0,0);
    
    //draw player's image
    draw_player(game.player);
    for (int i = 0; i < game.bullets.size(); i++) {
      draw_bullet(game.bullets[i]);
    }
    

    if (stage == 0) {
      for (int i = 0; i < game.cannons.size(); i++) {
        draw_cannon(game.cannons[i]);
      }
      for (int i = 0; i < game.aliens.size(); i++) {
        draw_alien(game.aliens[i]);
      }
    }

    if (stage == 1) {
      //draw ufo's image
      for (int i = 0; i < game.ufos.size(); i++) {
        draw_ufo(game.ufos[i]);
      }
      for (int i = 0; i < game.beams.size(); i++) {
        draw_beam(game.beams[i]);
      }
    }

    // show the hp
    if (stage == 1) {
      draw_text("BOSS HP: " + to_string(ufohp), COLOR_YELLOW, "a", 20, 150, 10);
    }

    draw_text("Player HP: " + to_string(playerhp), COLOR_WHITE, "a", 20, 10, 10);
  }

  if (theend == 1) {
    // Clear the vector when end game.
    stage = 3;
    game.ufos.clear();
    game.aliens.clear();
    game.bullets.clear();
    game.beams.clear();
    game.cannons.clear();
    // if player win the game
    if (win == 1) {
      draw_text("You WIN !!", COLOR_WHITE, "a", 40, 90, 200);
      draw_text("Press Enter To Play Again", COLOR_WHITE, "a", 20, 80, 300);

    } else
    // if player lose the game
    {
      draw_text("Game Over.", COLOR_WHITE, "a", 40, 90, 200);
      draw_text("Press Enter To Play Again", COLOR_WHITE, "a", 20, 80, 300);
    }

    if (key_typed(RETURN_KEY)) {
      //Reset the game.  
      alien_new_game();
      add_alien(game);
      alien = 18;
      ufohp = 100;
      playerhp = 20;
      theend = 0;
      win = 0;
      stage = 0;
      create = 0;

    }

  }
  refresh_screen();
}

void remove_cannon(vector < cannon_data > & cannons, int idx) {
  // remove cannon from vector
  cannons[idx] = cannons[cannons.size() - 1];
  cannons.pop_back();
}

void remove_alien(vector < alien_data > & aliens, int idx) {
  // remove alien from vector
  aliens[idx] = aliens[aliens.size() - 1];
  aliens.pop_back();
}

void remove_ufo(vector < ufo_data > & ufos, int idx) {
  // remove ufo from vector
  ufos[idx] = ufos[ufos.size() - 1];
  ufos.pop_back();
}

void remove_beam(vector < beam_data > & beams, int idx) {
  // remove beam from vector
  beams[idx] = beams[beams.size() - 1];
  beams.pop_back();
}

void remove_bullet(vector < bullet_data > & bullets, int idx) {
  // remove bullet from vector
  bullets[idx] = bullets[bullets.size() - 1];
  bullets.pop_back();
}

void update_bullets(vector < bullet_data > & bullets, vector < ufo_data > & ufos, vector < alien_data > & aliens) {
  vector < int > to_remove;
  vector < int > to_remove2;
  for (int i = 0; i < bullets.size(); i++) {
    // if bullet out of the screen, then remove it from vector
    update_bullet(bullets[i]);
    if (bullets[i].y <= 0) {
      to_remove.push_back(i);
    }
    for (int j = 0; j < ufos.size(); j++) {
      // if bullet hit the ufo, then ufo hp decrease and remove the bullet.
      if (bullet_hit_ufo(bullets[i], ufos[j])) {
        play_sound_effect("hit");
        ufohp = ufohp - 5;
        to_remove.push_back(i);
      }
    }
    for (int k = 0; k < aliens.size(); k++) {
      // if bullet hit the alien, then alien hp decrease and remove the bullet.
      if (bullet_hit_alien(bullets[i], aliens[k])) {
        play_sound_effect("hit");
        to_remove.push_back(i);
      }
    }
    for (int l = 0; l < aliens.size(); l++) {
      // if bullet hit the alien, then alien hp decrease and remove the bullet.
      if (bullet_hit_alien(bullets[i], aliens[l])) {
        alien--;
        
        to_remove2.push_back(l);
      }
    }

  }
  for (int i = to_remove.size() - 1; i >= 0; i--) {
    remove_bullet(bullets, to_remove[i]);
  }
  for (int i = to_remove2.size() - 1; i >= 0; i--) {
    remove_alien(aliens, to_remove2[i]);
  }
}

void update_beams(vector < beam_data > & beams,
  const player_data & player) {
  vector < int > to_remove;
  for (int i = 0; i < beams.size(); i++) {
    // if beam out of the screen, then remove it from vector
    update_beam(beams[i]);
    if (beams[i].y > 550) {
      to_remove.push_back(i);
    }

    // if beam hit player, then player hp decrease and remove the beam.
    if (beam_hit_player(beams[i], player)) {
      playerhp--;
      to_remove.push_back(i);
    }
  }
  for (int i = to_remove.size() - 1; i >= 0; i--) {
    remove_beam(beams, to_remove[i]);
  }
}

void update_cannons(vector < cannon_data > & cannons,
  const player_data & player) {
  vector < int > to_remove;
  for (int i = 0; i < cannons.size(); i++) {
    // if cannon out of the screen, then remove it from vector
    update_cannon(cannons[i]);
    if (cannons[i].y > 550) {
      to_remove.push_back(i);
    }

    // if cannon hit player, then player hp decrease and remove the cannon.
    if (cannon_hit_player(cannons[i], player)) {
      playerhp--;
      to_remove.push_back(i);
    }
  }
  for (int i = to_remove.size() - 1; i >= 0; i--) {
    remove_cannon(cannons, to_remove[i]);
  }
}
void update_ufos(vector < ufo_data > & ufos) {
  vector < int > to_remove;
  for (int i = 0; i < ufos.size(); i++) {
    // if ufo has no hp, remove it
    update_ufo(ufos[i]);
    if (ufohp <= 0) {
      to_remove.push_back(i);
    }

  }
  for (int i = to_remove.size() - 1; i >= 0; i--) {
    remove_ufo(ufos, to_remove[i]);
  }
}

void update_aliens(vector < alien_data > & aliens) {

  for (int i = 0; i < aliens.size(); i++) {
    // alien move left and right;
    int y = aliens[i].y;
    if (y % 2 == 0) {
      aliens[i].x = aliens[i].x + 25;
    } else {
      aliens[i].x = aliens[i].x - 25;
    }

    aliens[i].y = aliens[i].y + 15;
    // if aliens touch player, then lose;
    if (aliens[i].y > 400) {
      theend = 1;
      win = 0;

    }
  }

}
// create a group of alien
void add_alien(space_war_data & game) {
  for (int i = 0; i < 18; i++) {
    game.aliens.push_back(new_alien());
  }

}

// create a cannon
void add_cannon(space_war_data & game) {
  // Play shooting sound
  play_sound_effect("shoot2");
  int ax, ay;
  int idx;
  for (int i = 0; i < game.aliens.size() - 1; i++) {
    idx = rnd((game.aliens.size() - 1));
    ax = game.aliens[idx].x;
    ay = game.aliens[idx].y;
  }
  game.cannons.push_back(new_cannon(ax, ay));
}

// create a ufo
void add_ufo(space_war_data & game) {
  game.ufos.push_back(new_ufo());
}

// create a bullet
void add_bullet(space_war_data & game) {
  // Play shooting sound
  play_sound_effect("shoot");
  int px = game.player.x;
  game.bullets.push_back(new_bullet(px));
}

// create a beam that is shoot from the ufo
void add_beam(space_war_data & game) {
  // Play shooting sound
  play_sound_effect("shoot3");
  int ux;
  for (int i = 0; i < game.ufos.size(); i++) {
    ux = game.ufos[i].x;
  }

  game.beams.push_back(new_beam(ux));
}

// Stage one procedure
void stage_one(space_war_data & game) {
  //Aliens randomly shoot cannon   
  if (rnd() < 0.03) add_cannon(game);
  update_cannons(game.cannons, game.player);
  //Aliens randomly move to player  
  if (rnd(500) < 5) update_aliens(game.aliens);


}

// Stage two procedure
void stage_two(space_war_data & game) {
  // check beams' status
  update_beams(game.beams, game.player);

  // move ufo
  update_ufos(game.ufos);

  // check ufo's hp , if lower than 50, increase the change to shoot the beam.
  if (ufohp < 50) {
    if (rnd() < 0.06) add_beam(game);
    game.ufos[0].speed = 15;
  } else {
    if (rnd() < 0.03) add_beam(game);
  }

  // check if ufo's hp, if equal to 0, then win.
  if (ufohp == 0) {
    theend = 1;
    win = 1;
  }
}

void update_game(space_war_data & game) {
  // Create Stage 2 and check if ufo created
  if (alien == 0 && create == 0) {
    stage = 1;
    create = 1;
    add_ufo(game);
  }
  // Check current stage
  if (stage == 0) {
    stage_one(game);
  }
  // Check current stage
  if (stage == 1) {
    stage_two(game);
  }
  // check bullets' status
  update_bullets(game.bullets, game.ufos, game.aliens);

  // Press space key to shoot bullet.
  if (key_typed(SPACE_KEY)) {

    add_bullet(game);
  }

  // check if player's hp, if equal to 0, then game over.
  if (playerhp == 0) {
    theend = 1;
    win = 0;
  }

}