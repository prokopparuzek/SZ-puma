#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>

#include "music/morse.h"
#include "music/tetris.h"

#define LCD_BACKLIGHT 10
#define BUTTONS A0
#define RANDOM_PIN A5

#define BUZZER A1
#define TIMER_PRELOAD 652288  // 12.5 ms

#define RGB_PIN A2
#define RGB_TIME 250

#define CLEAR 0xA0
#define CHANGE_LEVEL 10

enum buttons {
    NO_BUTTON,
    SELECT,
    LEFT,
    DOWN,
    UP,
    RIGHT
};
enum COLORS {
    RED,
    GREEN,
    BLUE,
    YELLOW
};
enum fruits {
    TWO,
    DINO,
    TREE,
    HEAD,
    CHERRY,
    APPLE,
    PEAR,
    BANANA
};
const char dino[8] PROGMEM = {0x06, 0x0D, 0x0F, 0x0E, 0x1F, 0x1E, 0x0A, 0x0A};
const char tree[8] PROGMEM = {0x04, 0x1F, 0x0E, 0x04, 0x1F, 0x0E, 0x04, 0x04};
const char head[8] PROGMEM = {0x00, 0x0E, 0x15, 0x1F, 0x0E, 0x00, 0x0E, 0x00};
const char two[8] PROGMEM = {0x07, 0x01, 0x01, 0x17, 0x04, 0x04, 0x07, 0x00};
const char cherry[8] PROGMEM = {0x10, 0x08, 0x0C, 0x0B, 0x0B, 0x08, 0x0C, 0x0C};
const char apple[8] PROGMEM = {0x04, 0x04, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00};
const char pear[8] PROGMEM = {0x00, 0x04, 0x04, 0x0E, 0x0E, 0x1F, 0x1F, 0x0E};
const char banana[8] PROGMEM = {0x02, 0x04, 0x0C, 0x0C, 0x18, 0x1C, 0x0E, 0x06};
const char* const fruitsChars[8] PROGMEM = {two, dino, tree, head, cherry, apple, pear, banana};

const char colorsChars[4] PROGMEM = {'R', 'G', 'B', 'Y'};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_RGB + NEO_KHZ800);

buttons getButton() {
    int val = analogRead(BUTTONS);
    if (val > 1000) return NO_BUTTON;
    if (val < 50) return RIGHT;
    if (val < 195) return UP;
    if (val < 380) return DOWN;
    if (val < 555) return LEFT;
    if (val < 790) return SELECT;
    return NO_BUTTON;
}
void waitButton() {
    while (getButton() == NO_BUTTON) {
    }
}

struct sound_t {
    uint32_t timer;
    uint16_t* song;
    size_t songLen;
    size_t songPos;
    uint16_t frequency;
    uint16_t duration;
    uint8_t octave;
    uint8_t maxOctave;
    bool pause;

    void play(uint16_t* song, size_t songLen, uint8_t maxOctave = 0) {
        cli();
        this->song = song;
        songPos = 0;
        this->songLen = songLen;
        timer = millis();
        pause = true;
        octave = 0;
        this->maxOctave = maxOctave;
        sei();
    }
    void stop(void) {
        song = nullptr;
        noTone(BUZZER);
    }
};

sound_t sound;
ISR(TIMER1_OVF_vect) {
    TCNT1 = TIMER_PRELOAD;        // Timer Preloading
    if (sound.song == nullptr) {  // no song
        return;
    }
    if (sound.timer > millis()) {  // no need to change
        return;
    }
    if (!sound.pause) {  // pause beetwen notes
        sound.timer = millis() + sound.duration >> 4;
        noTone(BUZZER);
        sound.pause = true;
    } else {  // play note
        sound.frequency = pgm_read_word_near(sound.song + 2 * sound.songPos);
        sound.duration = pgm_read_word_near(sound.song + 2 * sound.songPos + 1);
        sound.timer = millis() + sound.duration;
        tone(BUZZER, sound.frequency << sound.octave);
        if (sound.songPos == sound.songLen / 4 - 1) {
            sound.songPos = 0;
            if (sound.octave < sound.maxOctave) {
                ++sound.octave;
            } else {
                sound.octave = 0;
            }
        } else {
            ++sound.songPos;
        }
        sound.pause = false;
    }
}

int selector(char* things) {
    static char buttons[4] = {'L', 'D', 'U', 'R'};
    int selected = 0;
    lcd.clear();
    lcd.print(F("Select: "));
    for (byte i = 0; i < 4; i++) {
        lcd.setCursor(10 + 2 * i, 0);
        lcd.write(things[i]);
    }
    for (byte i = 0; i < 4; i++) {
        lcd.setCursor(10 + 2 * i, 1);
        lcd.write(buttons[i]);
    }
    waitButton();
    selected = getButton() - 2;
    lcd.clear();
    return selected;
}

class rgb_t {
   public:
    rgb_t(Adafruit_NeoPixel& rgb) : rgb(rgb) {}
    void clear(void) {
        rgb.clear();
        rgb.show();
    }
    void green(void) {
        rgb.setPixelColor(0, 0, 64, 0);
        rgb.show();
    }
    void yellow(void) {
        rgb.setPixelColor(0, 64, 42, 0);
        rgb.show();
    }
    void red(void) {
        rgb.setPixelColor(0, 64, 0, 0);
        rgb.show();
    }
    void blue(void) {
        rgb.setPixelColor(0, 0, 0, 64);
        rgb.show();
    }
    void color(int color) {
        switch (color) {
            case RED:
                red();
                break;
            case GREEN:
                green();
                break;
            case BLUE:
                blue();
                break;
            case YELLOW:
                yellow();
                break;
        }
        rgb.show();
    }

   private:
    Adafruit_NeoPixel& rgb;
    uint32_t timer;
    uint8_t state;
};

class dino_t {
   public:
    dino_t(LiquidCrystal& lcd, rgb_t& rgb) : lcd(lcd), rgb(rgb) {}
    void play() {
        lcd.clear();
        while (playDino() < 12);
    }
    int playDino() {
        // init
        dinoGround = true;
        trees = 0;
        difficulty = 0x7;
        refresh = 600;
        score = 0;
        lcd.clear();
        ledDifficulty();
        // start play music
        sound.play(const_cast<uint16_t*>(tetris), sizeof(tetris), 2);
        // game init
        showDino();
        printScore();
        dinoRun = true;
        // play
        while (dinoRun) {
            game();
        }
        return score;
    }

   private:
    unsigned long int timerGame;
    unsigned long int timerDino;
    uint16_t maxScore = 0;
    bool dinoGround = true;
    uint16_t trees = 0;
    byte difficulty = 0x7;
    uint16_t refresh = 600;
    uint16_t score = 0;
    bool dinoRun = false;
    LiquidCrystal& lcd;
    rgb_t& rgb;

    void ledDifficulty() {
        switch (difficulty) {
            case 0b111:
                rgb.green();
                break;
            case 0b11:
                rgb.yellow();
                break;
            case 0b1:
                rgb.red();
                break;
            default:
                rgb.clear();
                break;
        }
    }
    void showDino() {
        if (dinoGround) {
            lcd.setCursor(1, 0);
            lcd.write(CLEAR);
            lcd.setCursor(1, 1);
        } else {
            showTrees();  // trees clear dino ground
            lcd.setCursor(1, 0);
        }
        lcd.write(fruits::DINO);
    }
    void printScore() {
        lcd.setCursor(6, 0);
        lcd.print(F("Score:"));
        lcd.print(score);
    }
    void moveTrees() {
        if (random(0, 2) && (trees & difficulty) == 0) {
            trees <<= 1;
            trees |= 0x1;
        } else {
            trees <<= 1;
        }
        if (trees & 0x8000) {
            score++;
            printScore();
            if (score % CHANGE_LEVEL == 0 && difficulty > 1) {
                refresh -= 100;
                difficulty >>= 1;
                ledDifficulty();
            }
        }
    }
    void showTrees() {
        uint16_t mask = 0x8000;
        for (int i = 0; i < 16; i++) {
            if (!(dinoGround && mask == 0x4000)) {
                lcd.setCursor(i, 1);
                lcd.write(bool(trees & mask) ? fruits::TREE : CLEAR);
            }
            mask >>= 1;
        }
    }
    void endDino() {
        lcd.setCursor(1, 0);
        lcd.write(CLEAR);
        lcd.setCursor(1, 1);
        lcd.write(fruits::HEAD);
        sound.stop();
        lcd.setCursor(3, 1);
        lcd.print(F("MaxScore:"));  // print old max score
        lcd.print(maxScore);
        if (score > maxScore) {  // save new max score
            maxScore = score;
        }
        dinoRun = false;
        delay(1000);
        waitButton();
    }
    bool button() {
        return getButton() != NO_BUTTON;
    }
    void game() {
        if (button() && dinoGround &&
            (millis() - timerDino) >= (refresh / 3)) {
            dinoGround = false;
            showDino();
            timerDino = millis();
        }
        if (!dinoGround && (millis() - timerDino) >= ((refresh * 3) >> 1)) {
            dinoGround = true;
            showDino();
            timerDino = millis();
        }
        if (dinoGround && (trees & 0x4000)) {  // end
            endDino();
            return;
        }
        if (millis() - timerGame >= refresh) {
            moveTrees();
            showTrees();
            timerGame = millis();
        }
    }
};

class SimonSays {
   public:
    SimonSays(LiquidCrystal& lcd, rgb_t& rgb) : lcd(lcd), rgb(rgb) {}
    void play() {
        lcd.clear();
        lcd.print(F("Simon says"));
        while (true) {
            showLevel();
            showColors();
            byte sel = selector(const_cast<char*>(colorsChars));
            if (sel == colors[level]) {
                level++;
                showColors();
                if (level >= 8) {
                    lcd.clear();
                    break;
                } else {
                    level = 0;
                }
            }
        }
    }

   private:
    void showColors() {
        for (int i = 0; i < level; i++) {
            rgb.color(colors[i]);
            delay(1500);
            rgb.clear();
            delay(200);
        }
    }
    void showLevel() {
        lcd.setCursor(0, 1);
        lcd.print(F("Level:"));
        lcd.print(level);
    }
    int level = 0;
    const byte colors[8] = {RED, GREEN, GREEN, YELLOW, BLUE, RED, YELLOW, GREEN};
    LiquidCrystal& lcd;
    rgb_t& rgb;
};

class Morse {
   public:
    Morse(LiquidCrystal& lcd, rgb_t& rgb) : lcd(lcd), rgb(rgb) {}
    void play() {
        lcd.clear();
        lcd.print(F("Morse code"));
        while (true) {
            showLevel();
            switch (level) {
                case 0:
                    sound.play(const_cast<uint16_t*>(morse1), sizeof(morse1), 1);
                    break;
                case 1:
                    sound.play(const_cast<uint16_t*>(morse2), sizeof(morse2), 1);
                    break;
                case 2:
                    sound.play(const_cast<uint16_t*>(morse3), sizeof(morse3), 1);
                    break;
            }
            byte sel = selector(const_cast<char*>(colorsChars));
            sound.stop();
            if (sel == words[level]) {
                level++;
                if (level >= 3) {
                    lcd.clear();
                    break;
                } else {
                    level = 0;
                }
            }
        }
    }

   private:
    void showLevel() {
        lcd.setCursor(0, 1);
        lcd.print(F("Level:"));
        lcd.print(level);
    }
    byte level = 0;
    const byte words[3] = {GREEN, YELLOW, RED};
    LiquidCrystal& lcd;
    rgb_t& rgb;
};

class Dobble {
   public:
    Dobble(LiquidCrystal& lcd) : lcd(lcd) {};
    void play() {
        lcd.clear();
        lcd.print(F("Dobble"));
        while (true) {
            showLevel();
            byte sel = selector(const_cast<char*>(dobble[level]));
            if (sel == answers[level]) {
                level++;
                if (level >= 4) {
                    lcd.clear();
                    break;
                } else {
                    level = 0;
                }
            }
        }
    }

   private:
    void showLevel() {
        lcd.setCursor(0, 1);
        lcd.print(F("Level:"));
        lcd.print(level);
    }

    const char dobble[4][4] = {{DINO, CHERRY, APPLE, TREE},
                               {HEAD, PEAR, BANANA, TWO},
                               {PEAR, CHERRY, DINO, HEAD},
                               {TWO, APPLE, TREE, BANANA}};
    const char answers[4] = {1, 3, 0, 2};

    int level = 0;
    LiquidCrystal& lcd;
};

void customCharacterLoad(LiquidCrystal& lcd, const char* data, byte addr) {
    uint8_t buffer[8];
    for (uint8_t i = 0; i < 8; i++) {
        buffer[i] = pgm_read_byte(data + i);
    }
    lcd.createChar(addr, buffer);
}

rgb_t rgbLed(rgb);
dino_t dinoGame(lcd, rgbLed);
SimonSays simon(lcd, rgbLed);
Morse morse(lcd, rgbLed);
Dobble dobble(lcd);

void setup() {
    pinMode(RANDOM_PIN, INPUT);
    srandom(analogRead(RANDOM_PIN));
    pinMode(BUTTONS, INPUT);
    pinMode(LCD_BACKLIGHT, OUTPUT);
    digitalWrite(LCD_BACKLIGHT, HIGH);
    lcd.begin(16, 2);
    pinMode(BUZZER, OUTPUT);
    // custom characters
    for (uint8_t i = 0; i < 8; i++) {
        const char* fruit = (const char*)pgm_read_word(&(fruitsChars[i]));
        customCharacterLoad(lcd, fruit, i);
    }
    // song interrut
    TCCR1A = 0;             // Init Timer1
    TCCR1B = 0;             // Init Timer1
    TCCR1B |= B00000011;    // Prescalar = 64
    TCNT1 = TIMER_PRELOAD;  // Timer Preloading
    TIMSK1 |= B00000001;    // Enable Timer Overflow Interrupt

    // RGB
    rgb.begin();
    rgb.clear();
    rgb.show();

    Serial.begin(9600);
    Serial.println(F("Start"));

    dobble.play();
    dinoGame.play();
    morse.play();
    simon.play();
    lcd.clear();
    lcd.print(F("Defused"));
}

void loop() {
}
