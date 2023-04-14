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
int redValue;
int greenValue;
int blueValue;
int yellowValue;

void playSequence() {
  int i = 0;
  
  while (i < level)
  {
    int button = sequence[i];
    
    switch (button) {
      case 0:
        digitalWrite(red, HIGH);
        delay(1000);
        digitalWrite(red, LOW);
        delay(1000);
        break;
      case 1:
        digitalWrite(yellow, HIGH);
        delay(1000);
        digitalWrite(yellow, LOW);
        delay(1000);
        break;
      case 2:
        digitalWrite(green, HIGH);
        delay(1000);
        digitalWrite(green, LOW);
        delay(1000);
        break;
      case 3:
        digitalWrite(blue, HIGH);
        delay(1000);
        digitalWrite(blue, LOW);
        delay(1000);
        break;
    }
    i++;
  }
  checkInputs();
}

void checkInputs()
{
  
  if (digitalRead(btnRed) == LOW) {
    delay(300);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 1; // 1 = rouge
      sequenceIndex++;
    }
  }
  if (digitalRead(btnYellow) == LOW) {
    delay(300);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 2; // 2 = jaune
      sequenceIndex++;
    }
  }
  if (digitalRead(btnGreen) == LOW) {
    delay(300);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 3; // 3 = vert
      sequenceIndex++;
    }
  }
  
  if (digitalRead(btnBlue) == LOW)
  {
    delay(300);  // Ajoutez une petite pause pour éviter les rebonds
    if (inputs[sequenceIndex] == 0)
    {
      inputs[sequenceIndex] == 4; // 4 = bleu
      sequenceIndex++;
    }
  }
}

void checkTabs() {
  // j'ai compris tout s'iterera me faut juste un tableau d'inputs 
  // a checker dans une fonction qui peut arreter le programme
  // et qui reset a chaque tableau rempli juste toutes les 
  // "cases" de celui-ci a 0 (1 rouge, 2 bleu, ...)
  // t'as capte facile juste chiant la j'ai pas envie
  // force a toi si tu t'y mets
  
  
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
  Serial.begin(9600);
}

void loop()
{
  	int check = 0;
  	
  	checkTabs();
  	if (check == 0)
    {
  		Serial.println("i generate the sequence.");
		playSequence();
	    Serial.println("the sequence is generated.");
      	check++;
    }
	
  	if (check == 1)
    {
    	Serial.println("i read the inputs.");
		checkInputs();
    }
  	
	if (sequenceIndex > level)
    {
		level++;
		sequenceIndex = 0;
		generateSequence();
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Niveau: ");
		lcd.print(level);
		delay(2000);
	}
  
  	int i = 0;
  	while (i < 9)
    {
  		Serial.print(sequence[i]);
      	i++;
    }
  	Serial.println(sequence[i++]);
  	i = 0;
  	while (i < 9)
    {
  		Serial.print(inputs[i]);
    }
  	Serial.println(inputs[i++]);
  	i = 0;
}
