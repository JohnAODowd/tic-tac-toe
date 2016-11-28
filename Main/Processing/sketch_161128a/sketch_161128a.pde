import processing.serial.*;
static boolean DEBUG = false;
Serial myPort;
String val;
final static int COM_PORT = 0;
final static int LED_SIZE = 30;
final static int LED_OFFSET = 15;
final static int LED_START = 55;
final static int COLUMN_2 = (LED_START + LED_SIZE + LED_OFFSET);
final static int COLUMN_3 = (LED_START + (LED_SIZE * 2) + (LED_OFFSET * 2));
final static int EMPTY = 0;
final static int RED = 255; // color for red
final static int YLW = 255; // color for yellow
int[][][] COORDS = {{{LED_START,LED_START,EMPTY},
                     {LED_START,COLUMN_2,EMPTY},
                     {LED_START,COLUMN_3,EMPTY}},
                    {{COLUMN_2,LED_START,EMPTY},
                     {COLUMN_2,COLUMN_2,EMPTY},
                     {COLUMN_2,COLUMN_3,EMPTY}},
                    {{COLUMN_3,LED_START,EMPTY},
                     {COLUMN_3,COLUMN_2,EMPTY},
                     {COLUMN_3,COLUMN_3,EMPTY}
                    }};

void setup(){
  // Serial.list()[0] opens COM1 on windows;
  // Change COM_PORT to the one that arduino
  // is connected to.
  size(200,200);
  background(255);
  for(int[][] row: COORDS){
    for(int[] led : row){
      stroke(led[2]);
      fill(led[2]);
      ellipse(led[0],led[1],LED_SIZE,LED_SIZE);
    }
  }
  try{
    String portName = Serial.list()[COM_PORT];
    myPort = new Serial(this,portName,9600);
  }catch(ArrayIndexOutOfBoundsException e){
    DEBUG = true;
  }
}
void draw(){
  if(!DEBUG && myPort.available() > 0){
    val = myPort.readStringUntil('\n');
    int led = Integer.parseInt(val);
    println(val);
    println(led);
  }
}
