/*
 * Project speaker
 * Description:
 * Author:
 * Date:
 */

#include "talkie.h"
#include "Vocab_US_Large.h"
#include "JsonParserGeneratorRK.h"

Talkie voice;

JsonParser jsonParser;

// initializes speaker
const int SPEAKER = D5;

// initializes speaker
const int BUTTON = D7;

// Declares and initializes previous button state for OLED button
int stateButtonPrev = HIGH;

int number = 0;

// setup() runs once, when the device is first turned on.
void setup()
{
  // Initializes serial monitor
  Serial.begin(9600);

  // Put initialization like pinMode and begin functions here.
  pinMode(SPEAKER, OUTPUT);

  // initialize repeat button
  pinMode(BUTTON, INPUT);

  Particle.subscribe("speech", speechEventHandler, ALL_DEVICES);
}

void speechEventHandler(const char *event, const char *data)
{
  String eventName = String(event);
  String eventData = String(data); // convert the pointer to be string

  // Part 1 allows for webhook responses to be delivered in multple "chunks"; you don't need to change this
  int responseIndex = 0;
  const char *slashOffset = strrchr(event, '/');
  if (slashOffset)
    responseIndex = atoi(slashOffset + 1);
  if (responseIndex == 0)
    jsonParser.clear();
  jsonParser.addString(data);

  // Part 2 is where you can parse the actual data; you code goes in the IF
  if (jsonParser.parse())
  {
    // String test = jsonParser.getReference().key("main").valueString();
    int number = jsonParser.getReference().key("main").key("number").valueInt();
    String city = jsonParser.getReference().key("name").valueString();

    // get the wind speed
    // get weather - main
    double wind = jsonParser.getReference().key("wind").key("speed").valueDouble();

    // when you access weather, you get an array with one object
    String weather = jsonParser.getReference().key("weather").index(0).key("main").valueString();
  }

  // loop through each number in the array
  for (int i = 0; i < 7; i++)
  {
    speakNum(number);
  }
}

void speakNum(int num)
{
  // speak the number
  if (num == 0)
  {
    voice.say(sp2_ZERO);
  }
  else if (num == 1)
  {
    voice.say(sp2_ONE);
  }
  else if (num == 2)
  {
    voice.say(sp2_TWO);
  }
  else if (num == 3)
  {
    voice.say(sp2_THREE);
  }
  else if (num == 4)
  {
    voice.say(sp2_FOUR);
  }
  else if (num == 5)
  {
    voice.say(sp2_FIVE);
  }
  else if (num == 6)
  {
    voice.say(sp2_SIX);
  }
  if (num == 7)
  {
    voice.say(sp2_SEVEN);
  }
  else if (num == 8)
  {
    voice.say(sp2_EIGHT);
  }
  else
  {
    voice.say(sp2_NINE);
  }
  // if button press say the numbers again. save the numbers as an array
}

void repeat()
{
  // Reads from button
  int stateButton = digitalRead(BUTTON);

  // Switches states on rising edge when button is pressed
  if (stateButton == HIGH && stateButtonPrev == LOW)
  {
  }
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.
}