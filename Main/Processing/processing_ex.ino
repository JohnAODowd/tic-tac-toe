#define WHITE_BG 60
#define RED_BG 61
#define GREEN_BG 62

#define LAG 300

int testPattern1[]={1,2,3,6,5,4,7,8,9,0,19,16,13,12,15,18,17,14,11,1,4,7,8,5,2,3,6,9,19,18,17,14,15,16,13,12,11,0};
int testPattern2[]={100,101,200,201,202,250,251,252,0};
int testPattern3[]={61,60,62,60,61,60,62,60,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  int j=0;
  while(testPattern1[j]){
     Serial.write(testPattern1[j]);
     delay(LAG);
     j++;
  }
  j=0;
  while(testPattern2[j]){
     Serial.write(testPattern2[j]);
     delay(LAG);
     j++;
  }
  j=0;
  while(testPattern3[j]){
     Serial.write(testPattern3[j]);
     delay(LAG);
     j++;
  }

  
}
