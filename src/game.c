#include "game.h"
#include "assets.h"

void game_loop();

UBYTE player_x;
UBYTE player_y;

int main()
{
  // Init LCD
  LCDC_REG = 0x67;
  set_interrupts(VBL_IFLAG | LCD_IFLAG);
  STAT_REG = 0x45;
 
  // Set palettes
  BGP_REG = OBP0_REG = 0xE4U;
  OBP1_REG = 0xD2U;

  // Position Window Layer
  WX_REG = 7;
  WY_REG = MAXWNDPOSY - 23;

  // Initialize the background graphics
  set_bkg_data(0, 22, tileset);
  set_bkg_tiles(0, 0, 32, 32, screen_tiles);
  set_win_tiles(0, 0, 20, 3, window_tiles);

  // Initialize the sprite graphics
  set_sprite_data(0, 4, player_sprites);
  set_sprite_tile(0, 0);
  set_sprite_tile(1, 2);

  DISPLAY_ON;
  SHOW_SPRITES;

  player_x = 80;
  player_y = 60;

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(game_loop, 60, 1);
#else
  while(1)
  {
    game_loop();
  }
#endif
}

void game_loop()
{
  UBYTE joy;
  
#ifdef __EMSCRIPTEN__    
  update_registers(SCX_REG, SCY_REG, WX_REG, WY_REG, LYC_REG, BGP_REG, OBP0_REG, OBP1_REG);
#endif
  wait_vbl_done();

  joy = joypad();

  // Scroll Screen Buffer
  SCX_REG++;
  SCY_REG++;

  // Controls
  if(joy & J_LEFT) { // Left pressed
    player_x-=1;
  } else if (joy & J_RIGHT) { // Right pressed
    player_x+=1;
  }
  if(joy & J_UP) { // Up pressed
    player_y-=1;
  } else if (joy & J_DOWN) { // Down pressed
    player_y+=1;
  }

  if(joy & J_A) {
    LOG("Pressing A\n");
  }
  if(joy & J_B) {
    LOG("Pressing B\n");
  }  
  if(joy & J_START) {
    LOG("Pressing Start\n");
  }
  if(joy & J_SELECT) {
    LOG("Pressing Select\n");
  }  

  // Player limits
  if(player_x < 8) {
    player_x = 8;
  }
  if(player_x > 152) {
    player_x = 152;
  }
  if(player_y < 16) {
    player_y = 16;
  }
  if(player_y > 120) {
    player_y = 120;
  }

  // Move player sprite
  move_sprite(0, player_x, player_y);
  move_sprite(1, player_x + 8, player_y);
}
