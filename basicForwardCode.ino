
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   PROBLEMS WITH CODE:
   0) Untested, could be infinitely buggy
   1) Values with 3 "*"s (***) commented indicate the actual value needs to be adjusted in real life.
   2) Design for robot with two sensors: one forward one right at a 90 degree angle to each other .
   3) Issue: hole in wall to right; How to fix
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   Special data type:
   dataSpecial;   data type that accepts values of "LOW" or "HIGH".
   ioSpecial; boolean value of either INPUT or OUTPUT
 *                                                                                                   *
   Explination of methods:
   Serial.
    - begin(int); A method ment to start the collection of data from sensors
    - print(); A method meant to print value or "string" to the Serial Monitor (top right of IDE) .
    - println(); Same as print();, however will make a new line next time print is called.
 *                                                                                                   *
    Unique to this code:
    digitalWrite(int , dataSpecial); will send a signal to int port# to change direction of motor .
    analogWrite(int, int2); will send a signal to port(int)  to change to value of int2, a speed .
    analogRead(int1); will return a value read from the sensor connected to port(int)
    pinMode(int, ioSpecial); defines port int to be either INPUT or OUTPUT.
    delay(int); Pauses execution of code for int milliseconds.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//Start of code

//Declaration and definition of ports
int m1 = 4;                // Motor 1 is assigned to port 4
int m2 = 7;                // Motor 2 is assigned to port 7
int e1 = 5;                // Engine 1 (speed of Motor 1) is assigned to port 5
int e2 = 6;                // Engine 2 (speed of Motor 2) is assigned to port 6
int rightSensor = 1;       // Right-Facing Sensor is assigned to port 1
int forwardSensor = 0;     // Left-Facing Sensor is assigned to port 0

//Declaration and definition of Booleans
bool turnedCorner = false; // Status of whether or not the robot sucessfully turned more than 45 degress of the corner
bool pattern = false;      // Status of whether or not the robot is alligned or not

//Declaration of Integers
int rightStatus;           // Current return value of Right Sensor
int forwardStatus;         // Current return value of Forward Sensor
int previousStatus;        // Previous recorded value from Right Sensor
int previousStatus2;       // Previous Previous recorded values from Right Sensor
int origionalStatus;       // The first Status when the robot initiated its turn
int timesTrue;             // counter of how many times a value was true
int changeTimes = 0;       // counter of how many times the robot has imediately changed turn directions.

//IONRV (integers of no real value)
int velocityStop = 0;      // a value to stop the robot; use for debug
int velocityMax = 255;     // a value to give the robot max speed; use for debug


void setup() {
  //Method is caled at the time of the robot's start up; The entry point for the code
  Serial.begin(9600);               //9600 is a "set-up code"
  Serial.println("Right / Forward");
  Serial.println("____");
  Serial.println("____");
  digitalWrite(m1, LOW);            //HIGH is backward, LOW is forwards
  digitalWrite(m2, LOW);
  analogWrite(e1, velocityMax);     //ranges from 0-255
  analogWrite(e2, velocityMax);     //ranges from 0-255
  pinMode(rightSensor, INPUT);
  pinMode(forwardSensor, INPUT);
  //Go forward, and start collecting data
  //void loop() is called
}



void loop() {
  //This code opperates until the robot is killed (loses power)
  analogWrite(e1, velocityStop);              //0-255
  analogWrite(e2, velocityStop);              //0-255
  rightStatus = analogRead(rightSensor);      // Properly defines rightStatus
  forwardStatus = analogRead(forwardSensor);  // Properly defines forwardStatus
  Serial.print(rightStatus);
  Serial.print(" / ");
  Serial.println(forwardStatus);
  Serial.println("_____");
  delay(400);

  //ISSUE: need int align() to make sure robot is close to wall

  if (forwardStatus <= 300/***/) {    // Values should be so that the robot can 360 without complaint
    analogWrite(e1, velocityMax);     // argument 2 can be 0-255
    analogWrite(e2, velocityMax);     // argument 2 can be 0-255
    //Robot: Hey, I'm crusing here!
  } else {
    int turnLeft();
  }
}


int align() { //Fuction to keep robot on course
  //Needs dual functionality (right to left and left to right)

}


int turnLeft() {
  //Robot: OH SHIT IMMA HIT A WALL! TURN LEFT BITCH!
  previousStatus = rightStatus;        // Start collecting previous results
  origionalStatus = rightStatus;       // Ditto
  digitalWrite(m1, HIGH);
  //Robot: REVERSE LEFT MOTOR
  delay(250);                          // keep doing it for 1/4 a second
  //Robot: I've turned, but now make me flush to the wall!
  while (true) {
    if (forwardStatus <= 100 && rightStatus <= 100 /***/) { //again this is just a dummy value: correct it
      //Robot: OH SHIT I TURNED TOO FAR AND OVERSHOT THE WALL!
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      delay (200);
      digitalWrite(m2, LOW);
      digitalWrite(m1, HIGH);
      //Robot: BACK THAT ASS UP, I'LL DO IT THE LONG WAY
      //Programmer:then...shit gets complicated :-(
    } else if (previousStatus >= rightStatus && turnedCorner == false) {
      //Robot: If my updated distance from my Right Sensor is father than before, AND I haven't acutally turned the corner yet
      do {
        previousStatus = rightStatus;
        delay(50);                       // keep updating how far away it gets at incriments
      } while (previousStatus >= rightStatus);
      //Once it starts to increase, we need to make sure it's actually increasing.
    } else if (previousStatus < rightStatus && turnedCorner == false) {
      if (timesTrue == 4) {                //if its increased 4 times, its safe to say its increasing
        turnedCorner = true;
      } else {
        ++timesTrue;
        delay(50);
      }
    } else if (turnedCorner == true && pattern == false) { //condition to check for a break
      if (changeTimes >= 4) {
        pattern = true;
      } else if (previousStatus > rightStatus) {
        //Robot: I'M OVERSHOOTING!!
        if (previousStatus2 <= previousStatus) {
          ++changeTimes;
        } else {
          changeTimes = 0;
        }
        //Robot: REVERSE!!!!!
        digitalWrite(m1, LOW);
        digitalWrite(m2, HIGH);
        previousStatus2 = previousStatus;
        previousStatus = rightStatus;
        delay(100);
      } else if (previousStatus <= rightStatus) {
        //Robot: I'M UNDERSHOOTING!!
        if (previousStatus2 >= previousStatus) {
          ++changeTimes;
        } else {
          changeTimes = 0;
        }
        //Robot: GO FORWARD!! MOVE BITCH MOVE
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        previousStatus2 = previousStatus;
        previousStatus = rightStatus;
        delay(100);
      }
    } else if (turnedCorner == true && pattern == true) {
      //Robot: I DID IT!!! HUZZAH! I'M STRIGHTENED AND TURNED LEFT! ANXIETY SOLVED!!!
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      //Robot: I'm crusing...until the next corner Q_Q
      break;
    }
  }

  return 0;
}



/* plan to execute:

    Space Properly:
      - shift right function
      - shift left function
    Go stright : Check Forward sensor //Needs to be tested
      Adjust right/left
      else, turn left 90deg, check
*/
