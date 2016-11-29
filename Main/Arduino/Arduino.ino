#include <EEPROM.h>
#include "game_logic.c"
#ifndef DF_GUARD
#include "defines.h"
#endif
#ifndef SOUND_GRD
#include "sounds.h"
#endif
#include "IRremote.h"

/*
 YELLOW LEDS ON PORTS: 2,3,4
 RED LEDS ON PORTS: 5,6,7
 ROW CONTROLLS ON PORTS: 8,9,10
*/
static char REDS[] = {RED1,RED2,RED3};
static char YLWS[] = {YLW1,YLW2,YLW3};
static char ROWS[] = {ROW1,ROW2,ROW3};
IRrecv irrecv(IR_PIN);
decode_results results;
void invalid_move();
void clear_pins();
void light_led(char led, char row);
void light_led(char led, char row,char index_row,char index_col,char color);
void write_ledS(char arr[LED_CNT][LED_CNT]);
void light_color(char color);
void choose_color();
void play_note(char col);
void horn_pipe();
void victory_tune();
void save_game();
void write_empty(char col,char row);

void setup() {
  // put your setup code here, to run once:
  DDRD |= DDRD_PINS;
  DDRB |= DDRB_PINS;
  clear_pins();
  irrecv.enableIRIn();
  Serial.begin(BAUD);
  char turn = EEPROM.read(TRN_ADDR);
  if(turn != RED && turn != YLW){
    game_state.yellow_player = PLYR_ONE;
    game_state.red_player = PLYR_TWO;
  }else if(turn == RED) {
    game_state.yellow_player = PLYR_TWO;
    game_state.red_player = PLYR_ONE;
  }else if(turn == YLW){
    game_state.yellow_player = PLYR_ONE;
    game_state.red_player = PLYR_TWO;
  }
  char saved = EEPROM.read(SAVE_ADDR);
  if (saved){
    game_state.state = EEPROM.read(STATE_ADDR);
    game_state.move_num = EEPROM.read(MOVE_ADDR);
    game_state.mute_state = EEPROM.read(MUTE_ADDR);
    TOP_RIGHT = EEPROM.read(BRD1);
    TOP_MID = EEPROM.read(BRD2);
    TOP_LEFT = EEPROM.read(BRD3);
    MID_RIGHT = EEPROM.read(BRD4);
    MID_MID = EEPROM.read(BRD5);
    MID_LEFT = EEPROM.read(BRD6);
    BOT_RIGHT = EEPROM.read(BRD7);
    BOT_MID = EEPROM.read(BRD8);
    BOT_LEFT = EEPROM.read(BRD9);
  } else{
    game_state.mute_state = SOUND_ON;
    game_state.state = NOT_STRTD;
  }
  game_state.saved = NTSVD;
}

void loop() {
  // put your main code here, to run repeatedly:
    if(game_state.state == INVALID_MOVE) invalid_move();
    if (game_state.state == SV_GM){
      save_game();
      game_state.state = GM_RDY;
    }
    if (!gameOver()) write_leds(board); 
    if (game_state.state == NOT_STRTD){
      choose_color();
    }else if(game_state.state == SND_HRN){
      horn_pipe();
      game_state.state = GM_RDY;
    }else if ((!gameOver()) && irrecv.decode(&results)) {
      // if game is being played
    if (!gameOver()){
        //if game is not over pass in player input.
        getPlayerInput(results.value);
        if(results.value == ZERO) save_game();
      }
      irrecv.resume();
    }else if(gameOver() && irrecv.decode(&results) || game_state.state == GM_LCKD && irrecv.decode(&results)){
      // handle start new game
      clear_pins();
      new_game(results.value);
      if(results.value == ZERO) save_game();
      irrecv.resume();
    } else if(game_state.state == GM_LCKD){
      write_leds(board);
    }else if(gameOver()){
      // if game is over and yellow wins, light up yellow leds else light up red leds
      switch(game_state.state){
        case YLW_WIN:
            victory_tune(YLW);
            break;
        case RED_WIN:
            victory_tune(RED);
            break;
        case DRAW:
            light_color(RED);
            light_color(YLW);
            break;
      }
    } 
}
void clear_pins(){
  /*
    Turn all pins low.
  */
  PORTD = CLR;
  PORTB = CLR;
}
void light_led(char led, char row){
  /*
   Light led on row
  */
  PORTB |= row;
  PORTD |= led;
}
void light_led(char led, char row,char index_row,char index_col,char color){
  light_led(led,row);
  Serial.print(index_col,DEC);
  Serial.print(SEP);
  Serial.print(index_row,DEC);
  Serial.print(SEP);
  Serial.println(color,DEC);
}
void write_empty(char col,char row){
  Serial.print(col,DEC);
  Serial.print(SEP);
  Serial.print(row,DEC);
  Serial.print(SEP);
  Serial.println(EMPTY_,DEC);
}
void write_leds(char arr[LED_CNT][LED_CNT]){
  /*
    Light corresponding leds (RED or YLW) or none,
    on a row j in column i, using persistance of vision.
  */
  for(char j = 0;j < LED_CNT;j++){
    for(char i = 0;i < LED_CNT;i++){
      if((arr[j][i]) == RED){
        light_led(REDS[i],ROWS[j],j,i,RED);
      } else if(arr[j][i] == YLW){
        light_led(YLWS[i],ROWS[j],j,i,YLW);
      }else write_empty(i,j);
      delay(RFRSH_RT);
      clear_pins();
    }
  }
}
void light_color(char color){
  /*
  Light all leds of given color
  */
    char light_all[3][3];
    if (color == YLW) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = YLW;
    else if (color == RED) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = RED;
    write_leds(light_all);
}
void choose_color(){
  /*
  Player color choice
  */
 if(irrecv.decode(&results)){
 if(results.value == PAUSE){
   game_state.state = SND_HRN;
 }
 else if(results.value == MODE && game_state.yellow_player == PLYR_ONE){
  light_color(RED);
  game_state.yellow_player = PLYR_TWO; 
  game_state.red_player = PLYR_ONE;
  EEPROM.write(TRN_ADDR,RED);
 }else if(results.value == MODE && game_state.yellow_player == PLYR_TWO){
  game_state.yellow_player = PLYR_ONE;
  game_state.red_player = PLYR_TWO;
  light_color(YLW);
  EEPROM.write(TRN_ADDR,YLW);
 }
 irrecv.resume();
 } else{
 if(game_state.yellow_player == PLYR_ONE) light_color(YLW);
 else if(game_state.yellow_player == PLYR_TWO) light_color(RED);
 }
}
void save_game(){
  /*
  Saves the game to EEPROM
  */
  EEPROM.write(STATE_ADDR,game_state.state);
  EEPROM.write(MOVE_ADDR,game_state.move_num);
  EEPROM.write(MUTE_ADDR,game_state.mute_state);
  EEPROM.write(BRD1,TOP_RIGHT);
  EEPROM.write(BRD2,TOP_MID);
  EEPROM.write(BRD3,TOP_LEFT);
  EEPROM.write(BRD4,MID_RIGHT);
  EEPROM.write(BRD5,MID_MID);
  EEPROM.write(BRD6,MID_LEFT);
  EEPROM.write(BRD7,BOT_RIGHT);
  EEPROM.write(BRD8,BOT_MID);
  EEPROM.write(BRD9,BOT_LEFT);
  EEPROM.write(SAVE_ADDR,SVD);
  game_state.saved = SVD;
}
void victory_tune(char col){
    for(int timer = 0; timer < colmans_MAXIMUM_COUNT; timer++){
    note = colmans_tune[timer];
    beat = colmans_beats[timer];
    
    duration = beat * tempo;
    light_color(col);
    play_note(col);
    light_color(col);
    if(game_state.mute_state) delayMicroseconds(pause);
  }
}
void invalid_move(){
    for(int timer = 0; timer < StartingBuzzer_MAXIMUM_COUNT; timer++){
    note = StartingBuzzer_tune[timer];
    beat = StartingBuzzer_beats[timer];
    
    duration = beat * tempo;
    play_note(NONE);
    if(game_state.mute_state) delayMicroseconds(pause);
  }
} 
void horn_pipe(){
    for(int timer = 0; timer < hornpipe_MAXIMUM_COUNT; timer++){
    note = hornpipe_tune[timer];
    beat = hornpipe_beats[timer];
    
    duration = beat * tempo;
    play_note(NONE);
    if(game_state.mute_state) delayMicroseconds(pause);
  }
}
void play_note(char col){
  long time_so_far = 0;
  if (note > 0){
    while(time_so_far < duration){
      // buzzer on
      if(col==YLW || col == RED) light_color(col);
      if(game_state.mute_state) digitalWrite(buzzer_out, HIGH);
      if(game_state.mute_state) delayMicroseconds(note / 2);
      if(col==YLW || col == RED) light_color(col);
      // buzzer off
      if(game_state.mute_state) digitalWrite(buzzer_out, LOW);
      if(game_state.mute_state) delayMicroseconds(note / 2);
      if(col==YLW || col == RED) light_color(col);
      // how much time has gone by
      time_so_far += (note);
    }
  }
  else{
    for (int restbeat = 0; restbeat < rest_count; restbeat++){
      if(game_state.mute_state) delayMicroseconds(duration);
    }
  }
}
