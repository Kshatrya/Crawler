/*
 754410 Motor Controller Sketch
 Direct control of the 754410 motor controller IC.
 Enable control on pins D8 & D9, output controls on D10, D11, D12, D13 
 */

int i;                           // Generic - Incrementing variable for loops

// Motor control pins
int TIME;                        // Duration of movement.
int EN_A = 7;                    // Enable 1 & 2 - I/C Pin 1
int EN_B = 8;                    // Enable 3 & 4 - I/C Pin 9
int A_1 = 10;                    // Control A1 - I/C Pin 2
int A_2 = 11;                    // Control A2 - I/C Pin 7
int B_1 = 12;                    // Control B1 - I/C Pin 10
int B_2 = 13;                    // Control B2 - I/C Pin 15


// Variables used in rangefinding
const int us_trigPin = 5;
const int us_echoPin = 6;
int distance;
int OOR = 300;     // Out Of Range value
long duration, cm; 

void setup()
{
  Serial.begin(4800);  // Sets up serial output. Use for printing debugging info.

  // Motor Control Setup
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(B_1, OUTPUT);
  pinMode(B_2, OUTPUT);
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);

  // Ultrasonic Setup
  pinMode(us_trigPin, OUTPUT);
  pinMode(us_echoPin, INPUT);

}


void loop()
{
/*
  go_fwd(1000);
  turn_left(1000);
  turn_right(1000);
  rot_CW(1000);
  rot_CCW(1000);
  stop(1000);
*/
  distance = (getDistanceAsCM());

/*  // Print routine for debugging
  if(distance >= OOR)
  {
    Serial.println("Out of Range");
  }
  else{
    Serial.println(distance);
  }
*/
  if(distance >= 20)
  {
    go_fwd(500);
  }
  else{
    rot_CW(1500);
  }

  // Delay needed to prevent hearing previous ping.
  delay(100);

}

void go_fwd(int TIME)              // Move forward
{
  digitalWrite(A_1, HIGH);
  digitalWrite(A_2, LOW);
  digitalWrite(B_1, HIGH);
  digitalWrite(B_2, LOW);
  delay(TIME);
}

void go_rev(int TIME)              // Move backward
{
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, HIGH);
  digitalWrite(B_1, LOW);
  digitalWrite(B_2, HIGH);
  delay(TIME);
}

void turn_left(int TIME)            // Turn Left
{
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, LOW);
  digitalWrite(B_1, HIGH);
  digitalWrite(B_2, LOW);
  delay(TIME);
}

void turn_right(int TIME)           // Turn right
{
  digitalWrite(A_1, HIGH);
  digitalWrite(A_2, LOW);
  digitalWrite(B_1, LOW);
  digitalWrite(B_2, LOW);
  delay(TIME);
}

void rot_CW(int TIME)            // Rotate Clockwise
{
  digitalWrite(A_1, HIGH);
  digitalWrite(A_2, LOW);
  digitalWrite(B_1, LOW);
  digitalWrite(B_2, HIGH);
  delay(TIME);
}

void rot_CCW(int TIME)          // Rotate Counter Clockwise
{
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, HIGH);
  digitalWrite(B_1, HIGH);
  digitalWrite(B_2, LOW);
  delay(TIME);
}

void stop(int TIME)              // Stop both motors
{
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, LOW);
  digitalWrite(B_1, LOW);
  digitalWrite(B_2, LOW);
  delay(TIME);
}

// Ultrasonic Rangefinder Function - returns distance in cm.
long getDistanceAsCM(){
  //send trigger signal
  digitalWrite(us_trigPin, HIGH);
  digitalWrite(us_trigPin, LOW);

  //get the time to receive rebound
  duration = pulseIn(us_echoPin, HIGH);

  /*sonar math is nicely explained in manual for the branded PING)) module here:
   http://www.parallax.com/dl/docs/prod/acc/28015-PING-1.3.pdf
   results seem accurate.*/
  return duration / 29 / 2;
}









