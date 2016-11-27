#ifndef DF_GUARD
#include "defines.h"
#endif
#include "IRremote.h"
#include "game_logic.c"
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
void write_leds(char arr[LED_CNT][LED_CNT]){
  /*
    Light corresponding leds (RED or YLW) or none,
    on a row j in column i, using persistance of vision.
  */
  for(char j = 0;j < LED_CNT;j++){
    for(char i = 0;i < LED_CNT;i++){
      if((arr[j][i]) == RED){
        light_led(REDS[i],ROWS[j]);
      } else if(arr[j][i] == YLW){
        light_led(YLWS[i],ROWS[j]);
      }
      delay(RFRSH_RT);
      clear_pins();
    }
  }
}
void light_color(char color){
    char light_all[3][3];
    if (color == YLW) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = YLW;
    else if (color == RED) for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) light_all[i][j] = RED;
    #ifdef DEBUG
    // print out contents of light all array
    for(char i=0;i<LED_CNT;i++) for(char j=0;j<LED_CNT;j++) Serial.println(light_all[i][j],DEC);
    #endif
    write_leds(light_all);
}
void choose_color(){
 if(irrecv.decode(&results)){
 if(results.value == PAUSE) game_state.state = GM_RDY;
 else if(results.value == MODE && game_state.yellow_player == PLYR_ONE){
  light_color(RED);
  game_state.yellow_player = PLYR_TWO; 
  game_state.red_player = PLYR_ONE;
 }else if(results.value == MODE && game_state.yellow_player == PLYR_TWO){
  game_state.yellow_player = PLYR_ONE;
  game_state.red_player = PLYR_TWO;
  light_color(YLW);
 }
 irrecv.resume();
 } else{
 if(game_state.yellow_player == PLYR_ONE) light_color(YLW);
 else if(game_state.yellow_player == PLYR_TWO) light_color(RED);
 }
}

void setup() {
  // put your setup code here, to run once:
  DDRD |= DDRD_PINS;
  DDRB |= DDRB_PINS;
  clear_pins();
  irrecv.enableIRIn();
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  game_state.state = NOT_STRTD;
  game_state.yellow_player = PLYR_ONE;
}

void loop() {
  // put your main code here, to run repeatedly:
    if (!gameOver()) write_leds(board); 
    if (game_state.state == NOT_STRTD){
      choose_color();
    }else if ((!gameOver()) && irrecv.decode(&results)) {
      // if game is being played
      #ifdef DEBUG
      Serial.println(results.value, HEX);
      Serial.println(gameOver(),DEC);
      #endif
      if (!gameOver()){
        //if game is not over pass in player input.
        getPlayerInput(results.value);
      }
      irrecv.resume();
    }else if(gameOver() && irrecv.decode(&results) || game_state.state == GM_LCKD && irrecv.decode(&results)){
      // handle start new game
      clear_pins();
      new_game(results.value);
      irrecv.resume();
    } else if(game_state.state == GM_LCKD){
      write_leds(board);
    }else if(gameOver()){
      // if game is over and yellow wins, light up yellow leds else light up red leds
      switch(game_state.state){
        case YLW_WIN:
            light_color(YLW);
            break;
        case RED_WIN:
            light_color(RED);
            break;
        case DRAW:
            light_color(RED);
            light_color(YLW);
            break;
      }
    } 
}
