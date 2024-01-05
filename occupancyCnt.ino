/***********************************************************************************************
** Description: Project uses ultrasonic sensors to check whether a person has entered or left
**              the common lounge area in the Chestnut Residence. If the max number is passed,
**              a led will turn red and a buzzer will emit a noise. Once the number of people
**              goes below the max number, the red light will turn off, a green ligt
**              will turn on, and the buzzer will silence.
***********************************************************************************************/

#include <NewPing.h>

// Defining where each component is connected
#define TRIG_IN A1
#define TRIG_OUT 3
#define ECHO_IN A2
#define ECHO_OUT 4
#define LED_GREEN 6
#define LED_RED 7
#define BUZZER 8

// Defining constants used in code
#define LIMIT 10 // Max amount of people allowed
#define DISTANCE 50 // Distance from entry and exit point
#define NOTEDURATION 125 // Length of eighth note for melody

float entryDistance; // Float records distance that Ultrasonic sensors read at entry point
float exitDistance; // Float records distance that Ultrasonic sensors read at exit point
int people = 0; // Net number of people in lounge room
bool entryBlock = false; // Boolean records whether the entry is blocked
bool exitBlock = false; // Boolean records whether the exit is blocked
int melody[] = {262, 262, 233, 262, 0, 165, 0, 165, 262, 392, 330, 262, 131, 131, 131, 131, 165, 0, 165, 165, 220, 220, 0, 330, 330, 294, 262, 0}; // Integer array stores frequencies of all notes in a song

NewPing sonar[2] = {NewPing(TRIG_IN, ECHO_IN, DISTANCE), NewPing(TRIG_OUT, ECHO_OUT, DISTANCE)};

void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
 
  // Set all components up
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(11, OUTPUT);

  // Activate all components
  digitalWrite(2, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(A0, HIGH);
  digitalWrite(A3, LOW);
  digitalWrite(11, LOW);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Print out distance that sensors are tracking at and amount of people at start
  Serial.print("Entry threshold distance on both sides of entry/exit path to: ");
  Serial.println(DISTANCE);
  Serial.print("Net People (< 10): 0\n");
 
  delay(1000);
}

void loop()
{
  // Check if number of people in lounge is less than or equal to the max amount of poeple
  if (people <= LIMIT)
  {
    // If true, green light stays on
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else
  {
    // If false, green light turns off, red light turns on, and buzzer plays tune
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER, HIGH);

    // Plays Funkytown tune by Lipps Inc.
    for(int noteCount = 0; noteCount < 28; noteCount++)
    {
      // Exits music loop if someone passes entry/exit point
      entryDistance = sonar[0].ping_cm();
      exitDistance = sonar[1].ping_cm();
      delay(40);
      if ((exitDistance < DISTANCE && exitDistance > 0) || (entryDistance < DISTANCE && entryDistance > 0))
      {
        break;
      }
     
      if(noteCount == 12)
      {
        delay(750);
      }
      else
      {
        tone(BUZZER, melody[noteCount], NOTEDURATION);
        delay(NOTEDURATION*1.3);
      }
    }
  }

  // Records the distance at the entry point
  entryDistance = sonar[0].ping_cm();
  delay(70); // Wait 40 milliseconds between pings. 29ms should be the shortest delay between pings.

  // Records the distance at the exit point
  exitDistance = sonar[1].ping_cm();
  delay(70);

  // Checks if the distance is less than the wall and is greater than zero at entry point
  if (entryDistance < DISTANCE && entryDistance > 0)
  {
    // If closer than wall then check if person has fully passed yet
    if (entryBlock == false)
    {
      // If they have passed, add one to count and display new net amount of people in lounge
      people++;
      Serial.print("Net People (< 10): ");
      Serial.println(people);
    }            
    entryBlock = true;
  }
  else
  {
    entryBlock = false;
  }

  // Checks if the distance is less than the wall and is greater than zero at exit point
  if (exitDistance < DISTANCE && exitDistance > 0)
  {
    // If closer than wall then check if person has fully passed yet
    if (exitBlock == false)
    {
      // If they have passed, subtract one from count and display new net amount of people in lounge
      people--;
      Serial.print("Net People (< 10): ");
      Serial.println(people);
    }
    exitBlock = true;
  }
  else
  {
    exitBlock = false;
  }
}
