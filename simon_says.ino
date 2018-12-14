/*
 * Technical documentation
 * 
 * 
 * The core concept for the simon says game is seeding the rand() function every time to read back the sequence
 * 
 * First, the user presses the game select button and it uses the millisecond timing of that press to generate the seed. This will always be something different
 * because the button will not be pressed exactly at the same millisecond each time a game has started.
 * 
 * Next, the game runs like a normal simon says, but the playback and read in modes re-seed rand() with the srand() function with the seed previously generated each time it needs
 * to be read from the beginning.
 * 
 * The game knows the end of the sequence by just counting. This way, the sequence can be endless and no arrays are ever used which would take up space and cpu power to initialize
 * all elements
 * 
 * Realistically, the user can only have a max score of 63 because of only having 6 LEDs, and subsequently, a 6 bit number. This could be extended by adding more LEDs.
 * 
 */


/* all of the defines for pins and other constant numbers for controlling important tasks */
/* LEDs on the breadboard from left to right */
#define LED_0 2
#define LED_1 3
#define LED_2 4
#define LED_3 5
#define LED_4 6
#define LED_5 7

#define SPEAKER_CHANNEL_0 8 /* the speaker is on pin 8 */

/* buttons on the breadboard from left to right */
#define BUTTON_0 23
#define BUTTON_1 24
#define BUTTON_2 25
#define BUTTON_3 26
#define BUTTON_4 27

/* the amount of time that dynamic button sound effects play for */
#define BUTTON_SOUND_LENGTH 200

#define ROUND_DELAY 600

/* global variables */

/* all of the states that the simon says can be in */
enum game_states_e
{
  STATE_MENU,
  STATE_GAME_MODE_0,
  STATE_GAME_MODE_1,
  STATE_GAME_MODE_2,
  STATE_GAME_MODE_3,
  STATE_HIGHSCORE,
  STATE_HIGHSCORE_0,
  STATE_HIGHSCORE_1,
  STATE_HIGHSCORE_2,
  STATE_HIGHSCORE_3
};

enum note_pitches_e /* all 88 pitch vales rounded from the list at https://en.wikipedia.org/wiki/Piano_key_frequencies */
{
  NOTE_OFF = 0, /* for turning notes off in a channel */
  NOTE_A0 = 28,
  NOTE_As0Bb0 = 29,
  NOTE_B0 = 31,
  NOTE_C1 = 33,
  NOTE_Cs1Db1 = 35,
  NOTE_D1 = 37,
  NOTE_Ds1Eb1 = 39,
  NOTE_E1 = 41,
  NOTE_F1 = 44,
  NOTE_Fs1Gb1 = 46,
  NOTE_G1 = 49,
  NOTE_Gs1Ab1 = 52,
  NOTE_A1 = 55,
  NOTE_As1Bb1 = 58,
  NOTE_B1 = 62,
  NOTE_C2 = 65,
  NOTE_Cs2Db2 = 69,
  NOTE_D2 = 73,
  NOTE_D2sEb2 = 78,
  NOTE_E2 = 82,
  NOTE_F2 = 87,
  NOTE_Fs2Gb2 = 92,
  NOTE_G2 = 98,
  NOTE_Gs2Ab2 = 104,
  NOTE_A2 = 110,
  NOTE_As2Bb2 = 117,
  NOTE_B2 = 123,
  NOTE_C3 = 131,
  NOTE_Cs3Db3 = 139,
  NOTE_D3 = 147,
  NOTE_Ds3Eb3 = 156,
  NOTE_E3 = 165,
  NOTE_F3 = 175,
  NOTE_Fs3Gb3 = 185,
  NOTE_G3 = 196,
  NOTE_Gs3Ab3 = 208,
  NOTE_A3 = 220,
  NOTE_As3Bb3 = 233,
  NOTE_B3 = 247,
  NOTE_C4 = 262,
  NOTE_Cs4Db4 = 277,
  NOTE_D4 = 294,
  NOTE_Ds4Eb4 = 311,
  NOTE_E4 = 330,
  NOTE_F4 = 349,
  NOTE_Fs4Gb4 = 370,
  NOTE_G4 = 392,
  NOTE_Gs4Ab4 = 415,
  NOTE_A4 = 440,
  NOTE_As4Bb4 = 466,
  NOTE_B4 = 494,
  NOTE_C5 = 523,
  NOTE_Cs5Db5 = 554,
  NOTE_D5 = 587,
  NOTE_Ds5Eb5 = 622,
  NOTE_E5 = 659,
  NOTE_F5 = 698,
  NOTE_Fs5Gb5 = 740,
  NOTE_G5 = 784,
  NOTE_Gs5Ab5 = 840,
  NOTE_A5 = 880,
  NOTE_As5Bb5 = 932,
  NOTE_B5 = 988,
  NOTE_C6 = 1047,
  NOTE_Cs6Db6 = 1109,
  NOTE_D6 = 1175,
  NOTE_Ds6Eb6 = 1245,
  NOTE_E6 = 1319,
  NOTE_F6 = 1397,
  NOTE_Fs6Gb6 = 1480,
  NOTE_G6 = 1568,
  NOTE_Gs6Ab6 = 1661,
  NOTE_A6 = 1760,
  NOTE_As6Bb6 = 1865,
  NOTE_B6 = 1976,
  NOTE_C7 = 2093,
  NOTE_Cs7Db7 = 2217,
  NOTE_D7 = 2349,
  NOTE_Ds7Eb7 = 2489,
  NOTE_E7 = 2637,
  NOTE_F7 = 2794,
  NOTE_Fs7Gb7 = 2960,
  NOTE_G7 = 3136,
  NOTE_Gs7Ab7 = 3322,
  NOTE_A7 = 3520,
  NOTE_As7Bb7 = 3729,
  NOTE_B7 = 3951,
  NOTE_C8 = 4186
};

/* the button struct for getting data from buttons */
typedef struct
{
  uint8_t button_0;
  uint8_t button_1;
  uint8_t button_2;
  uint8_t button_3;
  uint8_t button_menu;
  uint8_t last_button;
  uint8_t last_press_millis;
} buttons_t;

/* the global variable declarations */
buttons_t button_states;

uint8_t state, reset_game, playback, difficulty_1_hs = 0, difficulty_2_hs = 0, difficulty_3_hs = 0, difficulty_4_hs = 0;
uint32_t random_seed = 0, game_level;

/* the functions */

/* display a number in binary (maximum 6 bits though). This means that the high score has to be, at max, 63. */
void display_binary(uint8_t number)
{
  /* display the least signifigant bit */
  if(number & 0b00000001) /* bitwise AND "&" (not logical and "&&") the number to get the least signifigant bit first */
  {
    digitalWrite(LED_5, HIGH); /* writing it to the furthest right led */
  }
  else
  {
    digitalWrite(LED_5, LOW);
  }

  if(number & 0b00000010) /* bitwise AND "&" (not logical and "&&") the number to get the next bit */
  {
    digitalWrite(LED_4, HIGH); /* following the same pattern until the leftmost led */
  }
  else
  {
    digitalWrite(LED_4, LOW);
  }

  if(number & 0b00000100) /* bitwise AND "&" (not logical and "&&") the number to get the next bit */
  {
    digitalWrite(LED_3, HIGH); /* following the same pattern until the leftmost led */
  }
  else
  {
    digitalWrite(LED_3, LOW);
  }

  if(number & 0b00001000) /* bitwise AND "&" (not logical and "&&") the number to get the next bit */
  {
    digitalWrite(LED_2, HIGH); /* following the same pattern until the leftmost led */
  }
  else
  {
    digitalWrite(LED_2, LOW);
  }

  if(number & 0b00010000) /* bitwise AND "&" (not logical and "&&") the number to get the next bit */
  {
    digitalWrite(LED_1, HIGH); /* following the same pattern until the leftmost led */
  }
  else
  {
    digitalWrite(LED_1, LOW);
  }

  if(number & 0b00100000) /* bitwise AND "&" (not logical and "&&") the number to get the most signifigant bit */
  {
    digitalWrite(LED_0, HIGH); /* the furthest left led is the most signifigant bit (for a 6 bit number) */
  }
  else
  {
    digitalWrite(LED_0, LOW);
  }

  /* not enough LEDs to get the last two of the 8 bit number sent. Cant send less than 8 bits so we dont display the last 2*/
}

/* controls the indicator LEDs when use pressing */
void button_echo(void)
{
  if(!playback) /* do not control the LEDs if the game is playing back the simon says pattern */
  {
    if(digitalRead(BUTTON_0) == LOW)
  {
    digitalWrite(LED_0, HIGH);
  }
  else
  {
    digitalWrite(LED_0, LOW);
  }

  if(digitalRead(BUTTON_1) == LOW)
  {
    digitalWrite(LED_1, HIGH);
  }
  else
  {
    digitalWrite(LED_1, LOW);
  }

  if(digitalRead(BUTTON_2) == LOW)
  {
    digitalWrite(LED_2, HIGH);
  }
  else
  {
    digitalWrite(LED_2, LOW);
  }

  if(digitalRead(BUTTON_3) == LOW)
  {
    digitalWrite(LED_3, HIGH);
  }
  else
  {
    digitalWrite(LED_3, LOW);
  }

  if(digitalRead(BUTTON_4) == LOW)
  {
    digitalWrite(LED_5, HIGH);
  }
  else
  {
    digitalWrite(LED_5, LOW);
  }
  }
  
}

/* this function plays button sound effects when a button is pressed and depends on the current state of the game */
void button_sound(void)
{
  static unsigned int last_press = 0;
  float wobbly_sound = 0.0f;

  
  if(button_states.last_button != 255)
  {
    last_press = millis();
  }


  /* the menu sounds */
  if((state == STATE_MENU || state == STATE_HIGHSCORE || state == STATE_HIGHSCORE_0 || state == STATE_HIGHSCORE_1 || state == STATE_HIGHSCORE_2 || state == STATE_HIGHSCORE_3) && millis() - last_press < BUTTON_SOUND_LENGTH)
  {
    if((millis() - last_press) % 23 == 0)
    {
      tone(SPEAKER_CHANNEL_0, 120 + ((millis() - last_press) * 2), 100);
    }
      
  }

  /* game sounds */

  if((state == STATE_GAME_MODE_0 || state == STATE_GAME_MODE_1 || state == STATE_GAME_MODE_2 || state == STATE_GAME_MODE_3) && millis() - last_press < BUTTON_SOUND_LENGTH)
  {
    /* having to multiply the amplitude as the pitch gets higher because it is harder to distinguish higher pitch notes than lower pitch */
    wobbly_sound = sin((millis() - last_press) / 70.0) * (25 + button_states.last_button * 12);
    
    if((millis() - last_press) % 23 == 0)
    {

      /* the original 1978 game appears to go from middle c and travels 2 whole step intervals up to c5 depending on the button pressed */
      if(button_states.last_button == 0)
      {
        tone(SPEAKER_CHANNEL_0, NOTE_C4 + wobbly_sound, 100);
      }
      else if(button_states.last_button == 1)
      {
        tone(SPEAKER_CHANNEL_0, NOTE_E4 + wobbly_sound, 100);
      }
      else if(button_states.last_button == 2)
      {
        tone(SPEAKER_CHANNEL_0, NOTE_G4 + wobbly_sound, 100);
      }
      else if(button_states.last_button == 3)
      {
        tone(SPEAKER_CHANNEL_0, NOTE_C5 + wobbly_sound, 100);
      }
      else if(button_states.last_button == 4)
      {
        tone(SPEAKER_CHANNEL_0, 120 + ((millis() - last_press) * 2), 100);
      }
    }

  }

}

/* listen for button presses */
void listen()
{
  static uint8_t liftup = 0;

  if(liftup) /* only register a button press if all buttons are not being pressed/have not been pressed on the last cycle */
  {
    if(digitalRead(BUTTON_0) == LOW)
    {
      liftup = 0;
      button_states.button_0 = 1;
      button_states.last_press_millis = millis();
      button_states.last_button = 0;
    }

    if(digitalRead(BUTTON_1) == LOW)
    {
      liftup = 0;
      button_states.button_1 = 1;
      button_states.last_press_millis = millis();
      button_states.last_button = 1;
    }

    if(digitalRead(BUTTON_2) == LOW)
    {
      liftup = 0;
      button_states.button_2 = 1;
      button_states.last_press_millis = millis();
      button_states.last_button = 2;
    }

    if(digitalRead(BUTTON_3) == LOW)
    {
      liftup = 0;
      button_states.button_3 = 1;
      button_states.last_press_millis = millis();
      button_states.last_button = 3;
    }

    if(digitalRead(BUTTON_4) == LOW)
    {
      liftup = 0;
      button_states.button_menu = 1;
      button_states.last_press_millis = millis();
      button_states.last_button = 4;
    }
  }
  else
  {
    if(digitalRead(BUTTON_0) == HIGH && digitalRead(BUTTON_1) == HIGH && digitalRead(BUTTON_2) == HIGH && digitalRead(BUTTON_3) == HIGH && digitalRead(BUTTON_4) == HIGH)
    {
      liftup = 1;
    }
    else
    { /* set everything to default because a button is only "active" for a single cycle */
      button_states.button_0 = 0;
      button_states.button_1 = 0;
      button_states.button_2 = 0;
      button_states.button_3 = 0;
      button_states.button_menu = 0;
      button_states.last_button = 255;
    }
  }
}

/* this is where the simon says game logic happens */
void game_logic()
{
  static uint32_t temp_level = 0, last_millis = 0, mode = 0;
  static uint16_t counter = 0, last_press = 255;

  uint8_t random_value; /* a temporary variable for storing the current frame of playback or testing */

  if(reset_game)
  {
    counter = 0;
    reset_game = 0;
    mode = 0;
    last_millis = millis();
    random_seed = millis();
    srand(random_seed);
    game_level = 0;
    playback = 1;
  }
  if(playback)
  {
    button_states.last_button = 255;
  }
  
  /* controls the speed of the game. The original intention was to not block the sound effects from playing because of using a delay, but the microcontroller was not fast enough to do both anyway */
  if(millis() - last_millis > ROUND_DELAY) /* if the mode is the reading mode, there will be no delay because the user can play back the sequence however fast they want */
  {
        if(counter <= game_level && mode == 0) /* this is the playback mode. This plays back the sequence */
        {
          digitalWrite(LED_0, LOW);
          digitalWrite(LED_1, LOW);
          digitalWrite(LED_2, LOW);
          digitalWrite(LED_3, LOW);

          /* The game "remembers" sequences using the rand() function. The way this works is by resetting the seed that was generated before running the game.
           *  this means that in order to read back the sequence, it has to be re seeded back to the generated seed, and then read from the beginning and cannot
           *  be randomly accessed. This is perfectly fine because this game will only be played from the start to finish of the passed "levels" of the sequence.
           */

          random_value = rand() % 4; /* only allow 0-3 from the random function */
          
          button_states.last_button = random_value; /* sets the button state artificially to simulate button presses to make it play the button sound effect */

          switch(random_value) /* turn on the appropriate LED */
          {
            case 0:
              digitalWrite(LED_0, HIGH);
            break;
            case 1:
              digitalWrite(LED_1, HIGH);
            break;
            case 2:
              digitalWrite(LED_2, HIGH);
            break;
            case 3:
              digitalWrite(LED_3, HIGH);
            break;
          }

          last_millis = millis();
          counter++;
        }
        else if(mode == 0) /* if it has reached the end of the total sequence, change and prepare the user input mode */
        {
          srand(random_seed); /* reset rand to the original seed so it goes back to the beginning */
          counter = 0;
          mode = 1;
          playback = 0;
        }

        

        if(counter <= game_level && mode == 1) /* the input reading mode */
        {
          if(button_states.button_0 || button_states.button_1 || button_states.button_2 || button_states.button_3) /* if any of the 4 buttons are pressed */
          {

            random_value = rand() % 4; /* get the current sequence */

            if(random_value == button_states.last_button) /* make sure it is a valid press */
            {
              counter++;
            }
            else /* the user pressed the wrong button here */
            {
              /* dun dun dunnn sound effect for losing the stream */
              noTone(SPEAKER_CHANNEL_0);
              digitalWrite(LED_5, HIGH);
              tone(SPEAKER_CHANNEL_0, NOTE_F4);
              delay(500);
              noTone(SPEAKER_CHANNEL_0);
              tone(SPEAKER_CHANNEL_0, NOTE_C4);
              delay(500);
              noTone(SPEAKER_CHANNEL_0);
              tone(SPEAKER_CHANNEL_0, NOTE_B3);
              delay(800);
              noTone(SPEAKER_CHANNEL_0);

              switch(state) /* determine which one and whether or not to write the high score for the difficulty selected */
              {
                case STATE_GAME_MODE_0:
                  if(game_level > difficulty_1_hs) /* this is true for all of the following cases in the switch statement, but it will only write to the high score variable if it is higher */
                  {
                    difficulty_1_hs = game_level;
                  }
                  state = STATE_HIGHSCORE_0;
                break;
                case STATE_GAME_MODE_1:
                  if(game_level > difficulty_2_hs)
                  {
                    difficulty_2_hs = game_level;
                  }
                  state = STATE_HIGHSCORE_1;
                break;
                case STATE_GAME_MODE_2:
                  if(game_level > difficulty_3_hs)
                  {
                    difficulty_3_hs = game_level;
                  }
                  state = STATE_HIGHSCORE_2;
                break;
                case STATE_GAME_MODE_3:
                  if(game_level > difficulty_4_hs)
                  {
                    difficulty_4_hs = game_level;
                  }
                  state = STATE_HIGHSCORE_3;
                break;
              }
              
              /* TODO write score to flash. Never got this to work. MSP flash sections were difficult to get documentation on and there wasnt enough time to dive completely into the very long documentation for the MSP432 microcontroller */
            }
          }
          else if(button_states.button_menu) /* this is the escape button. Completely exits the current game and returns back to the main menu */
          {
            state = STATE_MENU;
          }
        }
        else if(mode == 1) /* reached the end of the sequence from the players input mode */
        {
          game_level+= 1 + (state - STATE_GAME_MODE_0); /* TODO increase by difficulty */
          counter = 0;
          mode = 0;
          playback = 1;
          srand(random_seed);
          /* delay and let the last sound play. It gets confusing if the sequence plays immediately after the user ends playing it back */
          last_millis = millis() + 400;
          delay(400);
        }

    
  }
  
}

void setup()
{
  /* set up the led pins */
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  /* the speaker/buzzer */
  pinMode(SPEAKER_CHANNEL_0, OUTPUT);

  /* the buttons */
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  /* set the global control variables here */
  state = STATE_MENU;
  game_level = 0;
  reset_game = 1;
  playback = 0;

  /* initialize the button state struct */
  button_states.button_0 = 0;
  button_states.button_1 = 0;
  button_states.button_2 = 0;
  button_states.button_3 = 0;
  button_states.button_menu = 0;


}

void loop()
{
  static int press_selection = 255, temp_delay = 0;

  /* these run to check the status of input and respond accordingly */
  listen();
  button_echo();

  
  switch(state) /* the state machine of the game or menus */
  {
    case STATE_MENU:
      /* display_binary(0b11111100); */
      /* navigate the menu */
      /* menu press on the far right goes to highscore menu. any others are diffculty in the game */

      /* the LEDs indicate valid selections */
      digitalWrite(LED_0, HIGH);
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      if(millis() - temp_delay > 500 && press_selection != 255) /* select a game and also delay between changing to the desired state so the sound effect plays out */
      {
        switch(press_selection)
      {
        case 0:
          state = STATE_GAME_MODE_0;
          reset_game = 1;
          press_selection = 255; /* set this to 255 to not confuse the game logic */
        break;
        case 1:
          state = STATE_GAME_MODE_1;
          reset_game = 1;
          press_selection = 255;
        break;
        case 2:
          state = STATE_GAME_MODE_2;
          reset_game = 1;
          press_selection = 255;
        break;
        case 3:
          state = STATE_GAME_MODE_3;
          reset_game = 1;
          press_selection = 255;
        break;
      }
      }

      /* respond to button presses */
      if(button_states.button_0)
      {
        press_selection = 0;
        temp_delay = millis();
        delay(10); /* delay here because the game goes into a glitched state without it. The sound effects probably effect the timing of future delays for some reason */
      }

      if(button_states.button_1)
      {
        press_selection = 1;
        temp_delay = millis();
        delay(10); /* delay here because the game goes into a glitched state without it. The sound effects probably effect the timing of future delays for some reason */
      }

      if(button_states.button_2)
      {
        press_selection = 2;
        temp_delay = millis();
        delay(10); /* delay here because the game goes into a glitched state without it. The sound effects probably effect the timing of future delays for some reason */
      }

      if(button_states.button_3)
      {
        press_selection = 3;
        temp_delay = millis();
        delay(10); /* delay here because the game goes into a glitched state without it. The sound effects probably effect the timing of future delays for some reason */
      }

      if(button_states.button_menu) /* if the menu/back button is pressed, it will change to the highscore selection menu */
      {
        state = STATE_HIGHSCORE;
      }
    break;
    
    case STATE_GAME_MODE_0: /* NOTE: there are no break;'s here because all difficulty states use the same logic. The logic decides how to respond though. This is a valid switch statement */
    case STATE_GAME_MODE_1:
    case STATE_GAME_MODE_2:
    case STATE_GAME_MODE_3:
      /* update the game logic */
      game_logic();
    break; /* treats all of the game difficulty states the same in the state machine */

    case STATE_HIGHSCORE: /* this is the highscore selecting menu state */
      /* display_binary(63); */
      digitalWrite(LED_0, HIGH);
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH); /* the next to last LED on the right indicates that this is the high score selection menu */

      if(button_states.button_0)
      {
        state = STATE_HIGHSCORE_0;
      }

      if(button_states.button_1)
      {
        state = STATE_HIGHSCORE_1;
      }

      if(button_states.button_2)
      {
        state = STATE_HIGHSCORE_2;
      }

      if(button_states.button_3)
      {
        state = STATE_HIGHSCORE_3;
      }

      if(button_states.button_menu) /* send it back to the main menu if this has been pressed */
      {
        state = STATE_MENU;
        digitalWrite(LED_4, LOW);
      }
    break;

    /* all of the display highscore states that all exit when the back button is pressed */
    case STATE_HIGHSCORE_0:
      display_binary(difficulty_1_hs);
      if(button_states.button_menu)
      {
        state = STATE_HIGHSCORE; /* send it back to the high score selection menu */
      }
    break;
    case STATE_HIGHSCORE_1:
      display_binary(difficulty_2_hs);
      if(button_states.button_menu)
      {
        state = STATE_HIGHSCORE; /* send it back to the high score selection menu */
      }
    break;
    case STATE_HIGHSCORE_2:
      display_binary(difficulty_3_hs);
      if(button_states.button_menu)
      {
        state = STATE_HIGHSCORE; /* send it back to the high score selection menu */
      }
    break;
    case STATE_HIGHSCORE_3:
      display_binary(difficulty_4_hs);
      if(button_states.button_menu)
      {
        state = STATE_HIGHSCORE; /* send it back to the high score selection menu */
      }
    break;
  }

  /* play the button sound. Put at the very end because the button state can be internally modified to inject button presses and it will be reset otherwise */
  button_sound();
  
}
