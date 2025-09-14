
const int DELAY_TIME{100}; // Delay for dot
const int PIN_ONE{3}; // Pin for buzzer


void setup() {
  Serial.begin(9600);  
  pinMode(PIN_ONE, OUTPUT);
}


void sendSignal(char signal){ 
  digitalWrite(PIN_ONE, HIGH);
  if(signal == '-'){
    delay(DELAY_TIME*3);
  } 
  else {
    delay(DELAY_TIME);
  }
  digitalWrite(PIN_ONE, LOW);
}


void sendMorse(char letter){ // Encode letter to code
  const char* morse_codes[26] = {".-","-...","-.-.","-..",".","..-.","--.",
                      "....","..",".---","-.-",".-..","--","-.",
                      "---",".--.","--.-",".-.","...","-","..-",
                      "...-",".--","-..-","-.--","--.."};

  letter = tolower(letter)-'a';
  if (letter < 0 || letter > 25)
    return;

  String morse = {morse_codes[letter]};

  for(int i = 0; i < morse.length(); i++){
    Serial.print(morse[i]);
    sendSignal(morse[i]); // 
    if (i < morse.length()-1)
      delay(DELAY_TIME);
  }
}


void readText(String& text){
  for (int i = 0; i < text.length(); i++){
    if(text[i] == ' '){ // Space between word
      Serial.print('#');
      delay(DELAY_TIME*7);
      continue;
    }
    sendMorse(text[i]); // Argument is each letter
    if (i < text.length() && text[i+1] != ' ') // "/" between letter
      Serial.print('/');
    delay(DELAY_TIME*3);
  }

  Serial.print('\n');
}


void loop() {
  if (Serial.available()) {
    String text{Serial.readString()};
    readText(text);
  }
}
