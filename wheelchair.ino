int RPWM_Output = 5; 
int LPWM_Output = 6; 

int RPWM_Output2 = 9; 
int LPWM_Output2 = 10; 


const int trigPin = 11;
const int echoPin = 12;

const int trigPin2 = 7;
const int echoPin2 = 8;
float duration, distance, duration2, distance2;


void setup()
{
  Serial.begin(9600);
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);

  pinMode(RPWM_Output2, OUTPUT);
  pinMode(LPWM_Output2, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  stopMotor();
}
 
void loop()
{

  float uLeft = sensorLeft();
  float uRight = sensorRight();

  if(uLeft < 30 && uRight < 30) {
    Serial.println("Stop");
    stopMotor();
    delay(200);
  } 
  else if (uLeft < 30 && uRight > 30) {
    Serial.println("Stop");
    stopMotor();
    delay(200);
  }
   else if (uLeft > 30 && uRight < 30) {
    Serial.println("Stop");
    stopMotor();
    delay(200);
  }
  else {
    
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      Serial.println(data);
  
      if(data.indexOf("forward") >= 0){
           Serial.print("forwarding");
          forward();
      }
  
      else if(data.indexOf("close") >= 0){
        Serial.print("stop");
          stopMotor();
      }
  
      else if(data.indexOf("left") >= 0){
        Serial.print("left movement");
          left();
      }
  
      else if(data.indexOf("right") >= 0){
        Serial.print("right movement");
          right();
      }
  
      Serial.println("No serial received");
    }
  }
//  forward();
//  delay(2000);
//  left();
//  delay(5000);
//  right();
//  delay(5000);
//  stopMotor();
//  delay(5000);
}

void forward() {
  analogWrite(LPWM_Output, 255);
  analogWrite(RPWM_Output, 0);

  analogWrite(LPWM_Output2, 255);
  analogWrite(RPWM_Output2, 0);
}

void stopMotor() {
 analogWrite(LPWM_Output, 5);
  analogWrite(RPWM_Output, 5);

  analogWrite(LPWM_Output2, 5);
  analogWrite(RPWM_Output2, 5);
}

void left() {
  analogWrite(LPWM_Output, 255);
  analogWrite(RPWM_Output, 0);

  analogWrite(LPWM_Output2, 0);
  analogWrite(RPWM_Output2, 0);
}

void right() {
  analogWrite(LPWM_Output, 0);
  analogWrite(RPWM_Output, 0);

  analogWrite(LPWM_Output2, 255);
  analogWrite(RPWM_Output2, 0);
}

float sensorLeft() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
 
  return distance;
}

float sensorRight() {
   
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2*.0343)/2;
  Serial.print("Distance2: ");
  Serial.println(distance2);

  return distance2;
}
