#define LED_0 2
#define LED_1 3
#define LED_2 4
#define LED_3 5
#define LED_4 6
#define LED_5 7

#define SPEAKER_CHANNEL_0 8

#define BUTTON_0 23
#define BUTTON_1 24
#define BUTTON_2 25
#define BUTTON_3 26
#define BUTTON_4 27

#define BUTTON_SOUND_LENGTH 200

/* global variables */
enum game_states_e
{
  STATE_MENU,
  STATE_GAME,
  STATE_HIGHSCORE
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

/*
enum note_rhythm_e
{
  NOTE_FOREVER,
  NOTE_WHOLE,
  NOTE_HALF,
  NOTE_QUARTER,
  NOTE_SIXTEENTH
};
*/

enum note_percussion_e
{
  NOTE_PERCUSSION_OFF,
  NOTE_PERCUSSION_SNARE,
  NOTE_PERCUSSION_TOM
};

enum music_qualities_e
{
  MUSIC_ONCE,
  MUSIC_LOOP
};

typedef struct
{
  uint8_t button_0;
  uint8_t button_1;
  uint8_t button_2;
  uint8_t button_3;
  uint8_t button_menu;
  uint8_t last_button;
} buttons_t;

typedef struct
{
  unsigned int channel_melody0_note;
  unsigned int channel_melody1_note;
  unsigned int channel_melody2_note;
  unsigned int channel_percussion_instrum;
} song_channel_t;

buttons_t button_states;


/* using this song as the example, every song has columns that are, at max (with normal tempos), a quarter note so every 4 notes is a whole note. One could make 16th or 32nd notes by speeding up the tempo by 2 or 4 */
song_channel_t menu_music[] = {
  /*{MUSIC_LOOP, 0, 0, 80}, /* needed for the settings of every song to tell the player whats it needs to know. row 1 is looping ability and last is tempo */
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_TOM},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_SNARE},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_TOM},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_TOM},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_TOM},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_SNARE},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},

  
  {NOTE_C4, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_E4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_SNARE},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_SNARE},
  {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_PERCUSSION_TOM}
};

song_channel_t test_music[] = {
  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},

  {NOTE_D4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},


  {NOTE_OFF, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_Gs3Ab3, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_Gs3Ab3, NOTE_PERCUSSION_OFF},

  {NOTE_OFF, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},
  {NOTE_D4, NOTE_OFF, NOTE_G3, NOTE_PERCUSSION_OFF},


  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},
  
  {NOTE_D4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_D4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},


  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_E4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_F4, NOTE_OFF, NOTE_As3Bb3, NOTE_PERCUSSION_OFF},
  {NOTE_F4, NOTE_OFF, NOTE_As3Bb3, NOTE_PERCUSSION_OFF},

  {NOTE_G4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_G4, NOTE_C3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_A4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},
  {NOTE_A4, NOTE_OFF, NOTE_A3, NOTE_PERCUSSION_OFF},


  {NOTE_OFF, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},

  {NOTE_C4, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_A3, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},
  {NOTE_A3, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},


  {NOTE_G3, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_G3, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},

  {NOTE_C4, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},
  {NOTE_C4, NOTE_OFF, NOTE_C4, NOTE_PERCUSSION_OFF},


  {NOTE_F3, NOTE_D3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_F3, NOTE_D3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_G3, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_G3, NOTE_E3, NOTE_OFF, NOTE_PERCUSSION_OFF},

  {NOTE_A3, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_A3, NOTE_F3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_B3, NOTE_As3Bb3, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_B3, NOTE_As3Bb3, NOTE_OFF, NOTE_PERCUSSION_OFF},


  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_F4, NOTE_G4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  
  {NOTE_F4, NOTE_G4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_F4, NOTE_G4, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF},
  {NOTE_OFF, NOTE_OFF, NOTE_OFF, NOTE_PERCUSSION_OFF}
};

uint8_t state, previous_state, button_press, music_output;

unsigned int random_seed = 0;



/* functions */

void play_music(void *music_temp, unsigned long note_count, unsigned long &song_column, unsigned int bpm)
{
  song_channel_t *music = (song_channel_t *)music_temp; /* have to typecast it because the compiler acts strange with a typedef in the function arguments */
  uint8_t can_loop;
  unsigned int beat_millis = 60000 / bpm, effect_speed = 10, delay_adjust = 2, channel_select = 0, playable_channel = 0;
  uint8_t channels_playing = 0;
  static unsigned int column_began = millis();
  static unsigned int column_end = column_began + beat_millis;
  static unsigned int last_effect = column_began;
  

  if(song_column > note_count)
  {
    song_column = 0;
  }

  
  if(music[song_column].channel_melody0_note != NOTE_OFF)
  {
    channels_playing++;
  }

  if(music[song_column].channel_melody1_note != NOTE_OFF)
  {
    channels_playing++;
  }

  if(music[song_column].channel_melody2_note != NOTE_OFF)
  {
    channels_playing++;
  }

  /*
  if(music[song_column].channel_percussion_instrum != NOTE_PERCUSSION_OFF)
  {
    channels_playing++;
  }
  */
  

  /* This was my first attempt. Its arpeggios are dependant on the tempo and notes playing. Its very subpar */
  /*
  if(channels_playing == 0)
    delay(beat_millis);
  else
  {
    if(music[song_column].channel_melody0_note)
    {
      tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody0_note, beat_millis);
      delay(beat_millis/channels_playing);
    }
    if(music[song_column].channel_melody1_note)
    {
      tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody1_note, beat_millis);
      delay(beat_millis/channels_playing);
    }
    if(music[song_column].channel_melody2_note)
    {
      tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody2_note, beat_millis);
      delay(beat_millis/channels_playing);
    }
    if(music[song_column].channel_percussion_instrum)
    {
      if(music[song_column].channel_percussion_instrum == NOTE_PERCUSSION_SNARE)
      {
        for(int i = 0; i < 200/channels_playing; i++)
        {
          tone(SPEAKER_CHANNEL_0, random(NOTE_C6, NOTE_C8), beat_millis/(200/channels_playing));
          delay(beat_millis/channels_playing/(200/channels_playing));
        }
      }
      if(music[song_column].channel_percussion_instrum == NOTE_PERCUSSION_TOM)
      {
        for(int i = 0; i < 200/channels_playing; i++)
        {
          tone(SPEAKER_CHANNEL_0, random(NOTE_C3, NOTE_C6), beat_millis/(200/channels_playing));
          delay(beat_millis/channels_playing/(200/channels_playing));
        }
      }
      //delay(200/channels_playing/50);
    }
  }
    */
    

    if(millis() <= column_end)
    {
      /* TODO: non-percussion music effects */
      if(effect_speed < millis() - last_effect)
      {
        /* TODO make percissuin land first and take half*/
        if(music[song_column].channel_percussion_instrum == NOTE_PERCUSSION_SNARE && millis() - column_began < ((column_end - column_began) / 2))
        {
          tone(SPEAKER_CHANNEL_0, random(NOTE_C6, NOTE_C8), effect_speed);
        }
        else if(music[song_column].channel_percussion_instrum == NOTE_PERCUSSION_TOM && millis() - column_began < ((column_end - column_began) / 2))
        {
          tone(SPEAKER_CHANNEL_0, random(NOTE_C3, NOTE_C6), effect_speed);
        }
        else
        {
          if(channels_playing)
          {
            while(!playable_channel)
            {
              switch(channel_select % 3)
              {
                case 0:
                  if(music[song_column].channel_melody0_note)
                  {
                    tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody0_note, effect_speed + delay_adjust);
                    playable_channel++;
                  }
                break;
                case 1:
                  if(music[song_column].channel_melody1_note)
                  {
                    tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody1_note, effect_speed + delay_adjust);
                    playable_channel++;
                  }
                break;

                case 2:
                  if(music[song_column].channel_melody1_note)
                  {
                    tone(SPEAKER_CHANNEL_0, music[song_column].channel_melody2_note, effect_speed + delay_adjust);
                    playable_channel++;
                  }
                break;
              }

              channel_select++; /* the melody channels need an arpeggio to simulate chords */
            }
          }
          
        }

        

        
        last_effect = millis();
      }
      
    }
    else
    {
      column_began = millis();
      column_end = column_began + beat_millis;
      song_column += 1;
    }
    
    
    

    

  

  

  
}

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
  if(button_states.button_0)
  {
    digitalWrite(LED_0, HIGH);
  }
  else
  {
    digitalWrite(LED_0, LOW);
  }

  if(button_states.button_1)
  {
    digitalWrite(LED_1, HIGH);
  }
  else
  {
    digitalWrite(LED_1, LOW);
  }

  if(button_states.button_2)
  {
    digitalWrite(LED_2, HIGH);
  }
  else
  {
    digitalWrite(LED_2, LOW);
  }

  if(button_states.button_3)
  {
    digitalWrite(LED_3, HIGH);
  }
  else
  {
    digitalWrite(LED_3, LOW);
  }

  if(button_states.button_menu)
  {
    digitalWrite(LED_5, HIGH);
  }
  else
  {
    digitalWrite(LED_5, LOW);
  }

  
}

void listen_for_buttons(void)
{  
  if(digitalRead(BUTTON_0) == LOW && !button_states.button_0)
  {
    button_states.button_0 = 1;
    button_press = 1;
    button_states.last_button = 0;
  }
  else
  {
    button_states.button_0 = 0;
  }
  
  if(digitalRead(BUTTON_1) == LOW && !button_states.button_1)
  {
    button_states.button_1 = 1;
    button_press = 1;
    button_states.last_button = 1;
  }
  else
  {
    button_states.button_1 = 0;
  }

  if(digitalRead(BUTTON_2) == LOW && !button_states.button_2)
  {
    button_states.button_2 = 1;
    button_press = 1;
    button_states.last_button = 2;
  }
  else
  {
    button_states.button_2 = 0;
  }

  if(digitalRead(BUTTON_3) == LOW && !button_states.button_3)
  {
    button_states.button_3 = 1;
    button_press = 1;
    button_states.last_button = 3;
  }
  else
  {
    button_states.button_3 = 0;
  }

  if(digitalRead(BUTTON_4) == LOW && !button_states.button_menu)
  {
    button_states.button_menu = 1;
    button_press = 1;
    button_states.last_button = 4;
  }
  else
  {
    button_states.button_menu = 0;
  }
  
}
void button_sound(void)
{
  static unsigned int last_press = 0;
  float wobbly_sound = 0.0f;

  
  if(button_press)
  {
    last_press = millis();
    button_press = 0;
  }


  /* the menu sounds */
  if((state == STATE_MENU || state == STATE_HIGHSCORE) && millis() - last_press < BUTTON_SOUND_LENGTH)
  {
    if((millis() - last_press) % 23 == 0)
    {
      tone(SPEAKER_CHANNEL_0, 120 + ((millis() - last_press) * 2), 100);
    }
      
  }

  /* game sounds */

  if(state == STATE_GAME && millis() - last_press < BUTTON_SOUND_LENGTH)
  {
    /* having to multiply the amplitude as the pitch gets higher because it is harder to distinguish higher pitch notes than lower pitch */
    wobbly_sound = sin((millis() - last_press) / 70.0) * (25 + button_states.last_button * 12);
    
    if((millis() - last_press) % 23 == 0)
    {

      /* the original 1978 game appears to go from middle c and travels 2 whole steps up to c5 */
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

void state_game_logic(void)
{
  /* TODO echo the sequence by re-seeding rand with srand(random_seed); and running rand() to get the sequence from the beginning each time the user does well. */
}

void state_menu_logic(void)
{
  /* temporary listening for the menu button to start the game. Will use taps in the future */
  if(button_states.button_menu)
  {
    random_seed = millis();
    state = STATE_GAME;
  }
}

void state_logic(void)
{
  static unsigned long song_column = 0;
  
  if(state == STATE_MENU || state == STATE_HIGHSCORE)
  {
    state_menu_logic();
    //play_music(menu_music, (sizeof(menu_music) / sizeof(menu_music[0])) - 1, song_column, 200);
    //play_music(test_music, (sizeof(test_music) / sizeof(test_music[0])) - 1, song_column, 200 * 2); /* 100*2 */
  }
  else
  {
    state_game_logic();
  }

  
}

void setup(void)
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

  state = STATE_MENU;
  button_press = 0;
  music_output = 1;

  button_states.button_0 = 0;
  button_states.button_1 = 0;
  button_states.button_2 = 0;
  button_states.button_3 = 0;
  button_states.button_menu = 0;
  button_states.last_button = 255;

}

void loop(void)
{
  listen_for_buttons();
  button_sound();
  button_echo();

  state_logic();
}

/*

const int ledPinG = 1;
const int ledPinR = 2;
const int ledPinY = 3;
const int ledPinB = 4;
const int buttonPinG = PUSH2;
const int buttonPinR = PUSH2;
const int buttonPinY = PUSH2;
const int buttonPinB = PUSH2;
int buttonStateG = digitalRead(buttonPinG);
int buttonStateR = digitalRead(buttonPinY);
int buttonStateY = digitalRead(buttonPinR);
int buttonStateB = digitalRead(buttonPinB);
void setup() {
  srand(time(0));
  int lightSequence [50];
  int lightNum = (rand() % 3) + 1;
  int i=0;
  while(buttonStateG == HIGH && buttonStateR == HIGH && buttonStateY == HIGH && buttonStateB == HIGH){
    for (int j=0; j<i; j++){
        switch (lightSequence[j]){
          case  1:
            digitalWrite(ledPinG, HIGH);
            tone(8, NOTE_D4, (4/1000));
            delay(1000);
            digitalWrite(ledPinG, LOW);
            break;
          case  2:
            digitalWrite(ledPinR, HIGH);
            tone(8, NOTE_C4, (4/1000));
            delay(1000);
            digitalWrite(ledPinR, LOW);
            break;
          case  3:
            digitalWrite(ledPinY, HIGH);
            tone(8, NOTE_E4, (4/1000));
            delay(1000);
            digitalWrite(ledPinY, LOW);
            break;
          case  4:
            digitalWrite(ledPinB, HIGH);
            tone(8, NOTE_F4, (4/1000));
            delay(1000);
            digitalWrite(ledPinB, LOW);
            break;
        }
    } //previous pattern
    
    lightSequence[i] = lightNum;
    
    switch (lightNum){
      case  1:
        digitalWrite(ledPinG, HIGH);
        tone(8, NOTE_D4, (4/1000));
        delay(1000);
        digitalWrite(ledPinG, LOW);
        break;
      case  2:
        digitalWrite(ledPinR, HIGH);
        tone(8, NOTE_C4, (4/1000));
        delay(1000);
        digitalWrite(ledPinR, LOW);
        break;
      case  3:
        digitalWrite(ledPinY, HIGH);
        tone(8, NOTE_E4, (4/1000));
        delay(1000);
        digitalWrite(ledPinY, LOW);
        break;
      case  4:
        digitalWrite(ledPinB, HIGH);
        tone(8, NOTE_F4, (4/1000));
        delay(1000);
        digitalWrite(ledPinB, LOW);
        break;
    } //added on to pattern
    
    int totalRight = 0;
    for (int j=0; j<=i; j++){
        if ((buttonStateG == HIGH && lightSequence[j] == 1)||(buttonStateR == HIGH && lightSequence[j] == 2)
            ||(buttonStateY == HIGH && lightSequence[j] == 3)||(buttonStateB == HIGH && lightSequence[j] == 4)){
            totalRight++;
        }
    }
    if (totalRight = i){
        i++;
    }
  }
}

void loop() {
  
  
}
*/
