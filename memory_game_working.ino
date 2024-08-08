// Define note frequencies
#define NOTE_B0 31
#define NOTE_C1 33
// (Keep all your defined note frequencies)

// Define button and LED choices
#define CHOICE_OFF 0
#define CHOICE_NONE 0
#define CHOICE_RED (1 << 0)
#define CHOICE_GREEN (1 << 1)
#define CHOICE_BLUE (1 << 2)
#define CHOICE_YELLOW (1 << 3)

// LED pins
#define LED_RED 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_YELLOW 5

// Button pins
#define BUTTON_RED 6
#define BUTTON_GREEN 7
#define BUTTON_BLUE 8
#define BUTTON_YELLOW 9
#define BUTTON_START 10  // New start/reset button

// Buzzer pin definitions
#define BUZZER1 11
#define BUZZER2 12

// Define game parameters
#define ROUNDS_TO_WIN 13
#define ENTRY_TIME_LIMIT 3000

// Game modes
#define MODE_MEMORY 0
#define MODE_BATTLE 1
#define MODE_BEEGEES 2

// Difficulty levels
#define DIFFICULTY_EASY 0
#define DIFFICULTY_MEDIUM 1
#define DIFFICULTY_HARD 2

// Game state variables
byte gameMode = MODE_MEMORY;
byte difficultyLevel = DIFFICULTY_MEDIUM;
byte gameBoard[32];
byte gameRound = 0;
int score = 0;  // New score variable

void setup() {
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  // Default mode and difficulty
  gameMode = MODE_MEMORY;
  difficultyLevel = DIFFICULTY_MEDIUM;

  if (checkButton() == CHOICE_YELLOW) play_beegees();
  if (checkButton() == CHOICE_GREEN) {
    gameMode = MODE_BATTLE;
    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);
    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);
    while (checkButton() != CHOICE_NONE);
  }

  play_winner();  // Play initial welcome sound
}

void loop() {
  if (digitalRead(BUTTON_START) == LOW) {
    resetGame();  // Reset game if the start button is pressed
  }

  attractMode();
  
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  if (gameMode == MODE_MEMORY) {
    if (play_memory() == true) {
      play_winner();
    } else {
      play_loser();
    }
  }

  if (gameMode == MODE_BATTLE) {
    play_battle();
    play_loser();
  }
}

// New function to reset the game
void resetGame() {
  gameRound = 0;
  score = 0;
  gameMode = MODE_MEMORY;
  delay(500);
}

boolean play_memory(void) {
  randomSeed(millis());
  gameRound = 0;

  while (gameRound < ROUNDS_TO_WIN) {
    add_to_moves();
    playMoves();
    for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) {
        play_error();  // New error feedback
        return false;
      }
    }
    score++;  // Increase score after each correct round
    delay(1000);
  }

  return true;
}

// Enhanced function to play moves with dynamic tone
void playMoves(void) {
  int delayTime = 150;  // Default delay

  // Adjust delay based on difficulty level
  if (difficultyLevel == DIFFICULTY_EASY) delayTime = 200;
  else if (difficultyLevel == DIFFICULTY_HARD) delayTime = 100;

  for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
    toner(gameBoard[currentMove], 150);
    delay(delayTime);
  }
}

// New function to provide error feedback
void play_error(void) {
  setLEDs(CHOICE_RED);
  buzz_sound(500, 300);
  setLEDs(CHOICE_OFF);
  delay(500);
}

void add_to_moves(void) {
  byte newButton = random(0, 4);
  if (newButton == 0) newButton = CHOICE_RED;
  else if (newButton == 1) newButton = CHOICE_GREEN;
  else if (newButton == 2) newButton = CHOICE_BLUE;
  else if (newButton == 3) newButton = CHOICE_YELLOW;
  gameBoard[gameRound++] = newButton;
}

// Function to select difficulty level based on button press
void selectDifficulty() {
  // Logic to select difficulty based on button press
  // Set difficultyLevel to DIFFICULTY_EASY, DIFFICULTY_MEDIUM, or DIFFICULTY_HARD
}

void toner(byte which, int buzz_length_ms) {
  setLEDs(which);
  int frequencyOffset = random(-50, 50);  // Randomize frequency slightly
  switch (which) {
    case CHOICE_RED:
      buzz_sound(buzz_length_ms, 1136 + frequencyOffset);
      break;
    case CHOICE_GREEN:
      buzz_sound(buzz_length_ms, 568 + frequencyOffset);
      break;
    case CHOICE_BLUE:
      buzz_sound(buzz_length_ms, 851 + frequencyOffset);
      break;
    case CHOICE_YELLOW:
      buzz_sound(buzz_length_ms, 638 + frequencyOffset);
      break;
  }
  setLEDs(CHOICE_OFF);
}

// (Keep all other functions the same as in your original code)
