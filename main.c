#include <stdio.h>
#include <ctype.h>
#include <AudioToolbox/AudioToolbox.h>
#include <unistd.h>
#include <string.h>

const char* convertTextToMorse(char letter) {
    static const char* morseTable[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    if (letter >= 'a' && letter <= 'z') {
        return morseTable[letter - 'a'];
    } else if (letter >= 'A' && letter <= 'Z') {
        return morseTable[letter - 'A'];
    } else {
        return "";
    }
}
void playDot() {
    AudioServicesPlaySystemSound(kSystemSoundID_UserPreferredAlert);
    usleep(100000); // Joue pendant 100 ms
}

void playDash() {
    AudioServicesPlaySystemSound(kSystemSoundID_UserPreferredAlert);
    usleep(300000); // Joue pendant 300 ms
}

void playMorseCode(const char* morse) {
    size_t length = strlen(morse);
    for(int i = 0; i < length; i++) {
        switch(morse[i]) {
            case '.':
                playDot();
                break;
            case '-':
                playDash();
                break;
            case ' ':
                usleep(200000); // Pause pendant 200 ms
                break;
        }
        usleep(100000); // Espace entre chaque symbole
    }
}


int main() {
    char* text = (char*) malloc(60 * sizeof(char));;
    printf("word : ");
    fgets(text,sizeof(strlen(text)),stdin);

    size_t length = strlen(text);

    for(int i = 0; i < length; i++) {
        const char* morseCode = convertTextToMorse(tolower(text[i]));
        printf("%c\n", text[i]); 
        printf("%s\n", morseCode);
        playMorseCode(morseCode);
    }
    free(text);

    return 0;
}
