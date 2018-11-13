#include <LiquidCrystal.h> 
LiquidCrystal 
lcd(12,11,5,4,3,2); 
int h=0; 
int m; 
int s;
int t=0; 
int r=0; 
int q=0; 
int nail,slag,nil=0,tag=1,mag=1,gft=1;
int TIME; 
const int hs=13; 
const int ms=A4;
const int ss=10; 
const int but=A5;
int state1; 
int state2; 
int state3;
int bag=0;
int button[] = {A0,A1,A2,A3};  //red is button[0], yellow is button[1], green is button[2], blue is button[3]
int led[] = {6,7,8,9};     //red is led[0], yellow is led[1], green is led[2], blue is led[3]
int roundsToWin = 10;         //number of rounds the player has to play before they win the game (the array can only hold up to 16 rounds)
boolean gameStarted = false;
int buttonSequence[16];       //make an array of numbers that will be the sequence that the player needs to remember

int buzzerPin = 1;           //pin that the buzzer is connected to
int flag=0;
int pressedButton = 4;        //a variable to remember which button is being pressed. 4 is the value if no button is being pressed.
int roundCounter = 3;         //keeps track of what round the player is on
int clay=0;
int lag=0;
long startTime = 0;           //timer variable for time limit on button press
long timeLimit = 2000;        //time limit to hit a button
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
  pinMode(button[2], INPUT_PULLUP);
  pinMode(button[3], INPUT_PULLUP);
  // Print a message to the LCD.
  //set all of the LED pins to output
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);

  pinMode(buzzerPin, OUTPUT);   //set the buzzer pin to output 
}

void loop() {
  // put your main code here, to run repeatedly:
if(bag==0){
  if(nil==0){  
   lcd.setCursor(0,0); 
   lcd.print("Set Time:"); 
   lcd.setCursor(0,1);
   lcd.print(h); 
   lcd.print(":"); 
   lcd.print(m); 
   lcd.print(":"); 
   lcd.print(s); 
  if(nail==24)nail=0; 
   delay(200); 
   lcd.clear(); 
}
if(slag==0){
}
  state1=digitalRead(hs); 
  if(state1==HIGH) 
  { 
    h=h+1; 
    nail=nail+1; 
  if(nail==24)nail=0; 
  if(h==13)h=0; 
  } 
  state2=digitalRead(ms); 
  if(state2==HIGH){ 
    s=0; 
    m=m+1; 
 }
 state3=digitalRead(ss);  
 if(state3==HIGH) 
 { 
    s=s+1; 
 } 
if ((digitalRead(but)==HIGH)  or tag==0)
 {
  tag=0;
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Time:"); 
  lcd.print(t); 
  lcd.print(":"); 
  lcd.print(r); 
  lcd.print(":"); 
  lcd.print(q);
  if(nail==24)nail=0; 
  delay(1000); 
  lcd.clear();
  slag=1;  
  q=q+1;  
  nil=1;
  if(q==60){ 
    q=0; 
    r=r+1; 
 } 
  if(r==60) 
 { 
    r=0; 
    t=t+1; 
    nail=nail+1; 
 } 
  if(t==13) 
 { 
    t=1; 
 } 
 mag=0;
}
if(mag==0){
 if(h==t and m==r and s==q){
  tag=1;
  gft=0;
  }
}  
  }
/*LED Game*/
  if(gft==0){
   if(clay==0){
    lcd.clear();
    lcd.print("ALARM...........");
    lcd.setCursor(0,1);
    lcd.print(".........ALARM");
    digitalWrite(buzzerPin,HIGH);
    delay(200);
    lag=1;
  }else{
    digitalWrite(buzzerPin,LOW);
    lag=0;
  }     
if(lag==1){
  if (gameStarted == false) {   //if the game hasn't started yet
    startSequence();            //flash the start sequence
    roundCounter =3;           //reset the round counter
    delay(1500);                //wait a second and a half
    gameStarted = true;         //set gameStarted to true so that this sequence doesn't start again
  }

  //each round, start by flashing out the sequence to be repeated
  for (int i = 0; i <= roundCounter; i++) { //go through the array up to the current round number
    flashLED(buttonSequence[i]);          //turn on the LED for that array position and play the sound
    delay(200);                           //wait
    allLEDoff();                          //turn all of the LEDs off
    delay(200);
  }

  //then start going through the sequence one at a time and see if the user presses the correct button
  for (int i = 0; i <= roundCounter; i++) { //for each button to be pressed in the sequence

    startTime = millis();                 //record the start time

    while (gameStarted == true) { //loop until the player presses a button or the time limit is up (the time limit check is in an if statement)

      pressedButton = buttonCheck();      //every loop check to see which button is pressed

      if (pressedButton < 4) {            //if a button is pressed... (4 means that no button is pressed)

        flashLED(pressedButton);          //flash the LED for the button that was pressed

        if (pressedButton == buttonSequence[i]) { //if the button matches the button in the sequence
          delay(250);                   //leave the LED light on for a moment
          allLEDoff();                  //then turn off all of the lights a
          flag=flag+1;
          break;                        //end the while loop (this will go to the next number in the for loop)
          
        } else {                          //if the button doesn't match the button in the sequence
          loseSequence();               //play the lose sequence (the loose sequence stops the progra
          lag=1;
          flag=0;
          break;                        //when the program gets back from the lose sequence, break the while loop so that the game can start over  
        }  
      } else {                            //if no button is pressed
        allLEDoff();                      //turn all the LEDs off
      }
    }
    if(flag==roundCounter+1){
        lcd.clear();
        lcd.print("welcome");
        digitalWrite(buzzerPin,LOW);
        delay(5000);
        nil=0;
        lcd.clear();
        slag=0;
        nail=0;
        h=0;
        m=0;
        s=0;
        t=0; 
        r=0; 
        q=0; 
        clay=0;
        lag=1;
        mag=1;
        gft=1;
        flag=0;
        break;
        }else{
          digitalWrite(buzzerPin,HIGH);
          lag=1; 
          }
      //check to see if the time limit is up
      if (millis() - startTime > timeLimit) { //if the time limit is up
        lag=1;
        loseSequence();                       //play the lose sequence
        break;                                //when the program gets back from the lose sequence, break the while loop so that the game can start over
      }
  }

 if (gameStarted == true) {
    roundCounter = roundCounter ;      //increase the round number by 1

    if (roundCounter >= roundsToWin) {              //if the player has gotten to the 16th round
      winSequence();                      //play the winning song
    }

    delay(500);                           //wait for half a second between rounds
  }

}

else{
  digitalWrite(buzzerPin,LOW);
}
}
}
  
//----------FUNCTIONS------------

//FLASH LED
void flashLED (int ledNumber) {
  digitalWrite(led[ledNumber], HIGH);
}

//TURN ALL LEDS OFF
void allLEDoff () {
  //turn all the LEDs off
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(led[3], LOW);
}

//CHECK WHICH BUTTON IS PRESSED
int buttonCheck() {
  //check if any buttons are being pressed
  if (digitalRead(button[0]) == HIGH) {
    return 0;
  } else if (digitalRead(button[1]) == HIGH) {
    return 1;
  } else if (digitalRead(button[2]) == HIGH) {
    return 2;
  } else if (digitalRead(button[3]) == HIGH) {
    return 3;
  } else {
    return 4; //this will be the value for no button being pressed
  }
}

//START SEQUENCE
void startSequence() {
  //populate the buttonSequence array with random numbers from 0 to 3
  randomSeed(analogRead(0));
  for (int i = 0; i <= roundsToWin; i++) {
    buttonSequence[i] = round(random(0, 4));
  }
  delay(3000);
  //flash all of the LEDs when the game starts
  for (int i = 0; i <= 3; i++) {
    //turn all of the leds on
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);

    delay(100);         //wait for a moment

    //turn all of the leds off
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);

    delay(100);   //wait for a moment

  } //this will repeat 4 times
}

//WIN SEQUENCE
void winSequence() {

  //turn all the LEDs on
  for (int j = 0; j <= 3; j++) {
    digitalWrite(led[j], HIGH);
  }
  //wait until a button is pressed
  do {
    pressedButton = buttonCheck();
  } while (pressedButton > 3);
  delay(100);

  gameStarted = false;   //reset the game so that the start sequence will play again.

}

//LOSE SEQUENCE
void loseSequence() {
  //flash all of the LEDs when the game starts
  for (int i = 0; i <= 3; i++) {
    //turn all of the leds on
    delay(100);
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);

    delay(100);         //wait for a moment

    //turn all of the leds off
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);

    delay(100);   //wait for a moment
  }
  do {
    pressedButton = buttonCheck();
  } while (pressedButton > 3);
  delay(200);
  
  gameStarted = false;   //reset the game so that the start sequence will play again.
}
