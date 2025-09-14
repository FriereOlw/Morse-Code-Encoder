
const int delay_time{100}; // DELAY FOR . 
const int PIN_ONE{3}; // PIN FOR OUTPUT 1

#ifdef TWO_OUTPUT
const int PIN_TWO{2}; // PIN FOR OUTPUT 2
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
    delay(delay_time*3);
  } else {
    delay(delay_time);
  }
  digitalWrite(PIN_ONE, LOW);

#else
  if(symbols == '-'){
    digitalWrite(PIN_ONE, HIGH);
    delay(delay_time*3);
    digitalWrite(PIN_ONE, LOW);
  } else {
    digitalWrite(PIN_TWO, HIGH);
    delay(delay_time);
    digitalWrite(PIN_TWO, LOW);
  }
#endif
}


void sendMorse(char letter){ //CONVERT LETTER TO CORRESPONGING MORSE CODE 
  const String morse_codes[27] = {"..-","-...","-.-.","-..",".","..-.","--.",
                      "....","..",".---","-.-",".-..","--","-.",
                      "---",".--.","--.-",".-.","...","-","..-",
                      "...-",".--","-..-","-.--","--.."};

  int char_a = letter > 'A' && letter <= 'Z' ? 65 : 97;
  String morse = {morse_codes[letter-char_a]};

  for(int i = 0; morse[i] != '\0'; i++){
    Serial.print(morse[i]);
    sendSignal(morse[i]); //ARGUMENT IS 0/1 
    if (i+1 != '\0') 
      delay(delay_time);
  }
}


void readWord(String& word){ //SPLIT WORD TO EACH LETTER
  int len{word.length()};

  for (int i = 0; i < len; i++){
    if(word[i] == ' '){ //Space between word
      Serial.print('\n');
      delay(delay_time*7);
      continue;
    }
    sendMorse(word[i]); //ARGUMENT IS EACH LETTER
    Serial.print('#');
    delay(delay_time*3);
  }

  Serial.print('\n');
}


void loop() {
  String word{Serial.readString()};
  readWord(word);
}
