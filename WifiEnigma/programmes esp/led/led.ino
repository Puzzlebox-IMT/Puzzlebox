void setup() {
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
}

//allume 1,2,3 ou 4 led suivant les bonnes réponses aux questions.
void question(int number){
  if (number == 1){
    digitalWrite(25, HIGH);
  }else if (number == 2){
    digitalWrite(26, HIGH);
  }else if (number == 3){
    digitalWrite(27, HIGH);
  }else if (number == 4){
    digitalWrite(14, HIGH);
  }else if (number == 0){
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    digitalWrite(14, LOW);
  }
}


void loop() {

    delay(500);
    question(1);
    delay(500);
    question(2);
    delay(500);
    question(3);
    delay(500);
    question(4);
    delay(2000);
    question(0);
    delay(500);


}
