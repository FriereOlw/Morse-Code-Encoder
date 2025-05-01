#define TWO_OUTPUT

const int time_unit{70};
const int PIN_ONE{3};

#ifdef TWO_OUTPUT
const int PIN_TWO{2};
#endif


void setup() {
  Serial.begin(9600);  
  pinMode(PIN_ONE, OUTPUT);

#ifdef TWO_OUTPUT
  pinMode(PIN_TWO, OUTPUT);
#endif
}


void sendSignal(char symbols){ //SEND EACH LETTER   
#ifndef TWO_OUTPUT
  digitalWrite(PIN_ONE, HIGH);
  if(symbols == '-'){
    delay(time_unit*3);
  } else {
    delay(time_unit);
  }
  digitalWrite(PIN_ONE, LOW);

#else
  if(symbols == '-'){
    digitalWrite(PIN_ONE, HIGH);
    delay(time_unit*3);
    digitalWrite(PIN_ONE, LOW);
  } else {
    digitalWrite(PIN_TWO, HIGH);
    delay(time_unit);
    digitalWrite(PIN_TWO, LOW);
  }
#endif
}


void sendMorse(char letter){ //CONVERT LETTER TO CORRESPONGING MORSE CODE 
  const String morse_codes[27] = {"..-","-...","-.-.","-..",".","..-.","--.",
                      "....","..",".---","-.-",".-..","--","-.",
                      "---",".--.","--.-",".-.","...","-","..-",
                      "...-",".--","-..-","-.--","--.."};

  String morse = {morse_codes[letter-65]};

  for(int i = 0; morse[i] != '\0'; i++){
    Serial.print(morse[i]);
    sendSignal(morse[i]); //ARGUMENT IS 0/1 
    if (i+1 != '\0') 
      delay(time_unit);
  }
}


void readWord(String& word){ //SPLIT WORD TO EACH LETTER
  int len{word.length()};

  for (int i = 0; i < len; i++){
    if(word[i] == ' '){ //SPACE BETWEEN WORDS
      Serial.print('\n');
      delay(time_unit*7);
      continue;
    }
    sendMorse(word[i]); //ARGUMENT IS EACH LETTER
    Serial.print('#');
    delay(time_unit*3);
  }
  Serial.print('\n');
}


void loop() {
  String word{Serial.readString()};
  readWord(word);
}
