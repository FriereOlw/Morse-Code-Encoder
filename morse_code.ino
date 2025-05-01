
const int yellow_led{2};
const int blue_led{4};
const int time_unit{100};

const int one_pin{5};


const char* morse_code[27] = {"001","1000","1010","100","0","0010","110",
                        "0000","00","0111","101","0100","11","10",
                        "111","0110","1101","010","000","1","001",
                        "0001","011","1001","1011","1100"};

char worde[]{"BANJARMASIN"};


void setup() {
  pinMode(yellow_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(one_pin, OUTPUT);
  Serial.begin(9600);  
}


void sendSignal(int bol){
  // if(bol){ //IF LINE (1)
  //   digitalWrite(yellow_led,  HIGH);
  //   delay(time_unit*3);
  //   digitalWrite(yellow_led,  LOW);
  // } else  { //IF DOT (0)
  //   digitalWrite(blue_led,  HIGH);
  //   delay(time_unit);
  //   digitalWrite(blue_led,  LOW);
  // }

  digitalWrite(one_pin, HIGH);
  if(bol){ //IF LINE (1)
    delay(time_unit*3);
  } else  { //IF DOT (0)
    delay(time_unit);
  }
  digitalWrite(one_pin, LOW);

}


void printMorse(char letter){ //CONVERT LETTER TO CORRESPONGING MORSE CODE 
  char* morse[] = {morse_code[letter-65]};

  for(int i = 0; morse[0][i] != '\0'; i++){
    Serial.print(morse[0][i]);
    sendSignal(morse[0][i]-'0'); //ARGUMENT IS 0/1 
    if (i+1 != '\0') 
      delay(time_unit);
  }
}


void readWord(char worde[]){ //SPLIT WORD TO EACH LETTER
  int len = strlen(worde);
  for (int i = 0; i < len; i++){
    printMorse(worde[i]); //ARGUMENT IS EACH LETTER
    Serial.print('\n');
    delay(time_unit*3);
  }
}


void loop() {
  readWord(worde);
  delay(20000);

}
