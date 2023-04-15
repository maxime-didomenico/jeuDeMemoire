#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int red = 9;
const int yellow = 6;
const int green = 8;
const int blue = 7;

const int btnRed = A0;
const int btnYellow = A3;
const int btnGreen = A1;
const int btnBlue = A2;

int sequence[100];
int inputs[100];
int sequenceIndex = 0;
int level = 0;
int check = 0;

int redValue;
int greenValue;
int blueValue;
int yellowValue;

void playSequence() {
  int i = 0;
  
  while (i <= level)
  {
    int button = sequence[i];
    
      if (sequence[i] == 1)
      {
        digitalWrite(red, HIGH);
        delay(1000);
        digitalWrite(red, LOW);
        delay(1000);
      }
      if (sequence[i] == 2)
      {
        digitalWrite(yellow, HIGH);
        delay(1000);
        digitalWrite(yellow, LOW);
        delay(1000);
      }
      if (sequence[i] == 3)
      {
        digitalWrite(green, HIGH);
        delay(1000);
        digitalWrite(green, LOW);
        delay(1000);
  	  }
      if (sequence[i] == 4)
      {
        digitalWrite(blue, HIGH);
        delay(1000);
        digitalWrite(blue, LOW);
        delay(1000);
      }
      i++;
  }
  checkInputs();
}

void checkInputs()
{
  
  if (digitalRead(btnRed) == LOW) {
    delay(100);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 1)
    {
  		inputs[sequenceIndex] = 1; // 1 = rouge
  		sequenceIndex++;
      	digitalWrite(red, HIGH);
        delay(1000);
        digitalWrite(red, LOW);
        delay(1000);
	}

  }
  if (digitalRead(btnYellow) == LOW) {
    delay(100);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 2; // 2 = jaune
      sequenceIndex++;
      digitalWrite(yellow, HIGH);
        delay(1000);
        digitalWrite(yellow, LOW);
        delay(1000);
    }
  }
  if (digitalRead(btnGreen) == LOW) {
    delay(100);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 3; // 3 = vert
      sequenceIndex++;
      digitalWrite(green, HIGH);
      delay(1000);
      digitalWrite(green, LOW);
      delay(1000);
    }
  }
  
  if (digitalRead(btnBlue) == LOW)
  {
    delay(100);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] = 4; // 4 = bleu
      sequenceIndex++;
      digitalWrite(blue, HIGH);
      delay(1000);
      digitalWrite(blue, LOW);
      delay(1000);
    }
  }
}

void resetTab(int tab[])
{
  int i = 0;
  
  while (i < 100)
  {
    tab[i] = 0;
    i++;
  }
}

int checkIndex()
{
  int i = 0;
  int index = 0;
  
  while (i < 100)
  {
    if (inputs[i] > 0 && i < 100)
    {  
      i++;
      index++;
    }
    else 
    {
      return index;
    }
  }
  return index;
}



void checkTabs()
{
  checkInputs();
  
  // Check if inputs array is full and matches sequence array
  int i = 0;

  while (i < sequenceIndex) {
    if (inputs[i] != sequence[i] && i > 0) {
      // If input does not match sequence, game is lost
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over !");
      delay(2000);
      exit(0); // Exit the program
    }
    i++;
  }

  // If inputs array is full and matches sequence array, game is won
  if (sequenceIndex == level and i > 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next level !");
    delay(2000);
    lcd.clear();
    resetTab(sequence);
    resetTab(inputs);
    check--;
    level++;
  }
  
  if (inputs[0] == sequence[0] && level == 0)
  {
  	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Next level !");
    delay(2000);
    lcd.clear();
    resetTab(sequence);
    resetTab(inputs);
    check--;
    level++;
  }
}




void generateSequence() {
  int i = 0;
  
  while (i <= level)
  {
  	sequence[i] = random(1, 4);
    i++;
  }
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  pinMode(btnRed, INPUT_PULLUP);
  pinMode(btnYellow, INPUT_PULLUP);
  pinMode(btnGreen, INPUT_PULLUP);
  pinMode(btnBlue, INPUT_PULLUP);
  
  Serial.begin(19200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Jeu de Simon");
  
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Commencez!");
  delay(2000);
  
  generateSequence();
}

void loop()
{
  
  	Serial.print("check = ");
  	Serial.println(check);
  	if (check == 0)
    {
  		Serial.println("i generate the sequence.");
      	generateSequence();
		playSequence();
	    Serial.println("the sequence is generated.");
      	check++;
    }
	
  	if (check == 1)
    {
      	checkInputs();
      	checkTabs();
    	Serial.println("i read the inputs.");
      
      	int i = 0;
        while (i < level)
        {
            Serial.print(sequence[i]);
            i++;
        }
        Serial.println(sequence[i++]);
        i = 0;
        while (i < level)
        {
            Serial.print(inputs[i]);
            i++;
        }
        Serial.println(inputs[i++]);
    }
  	
	if (sequenceIndex > level)
    {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Niveau: ");
		lcd.print(level);
		delay(2000);
    }
}
