#ifndef HANGMAN_HPP
#define HANGMAN_HPP

#include <string>

extern void sent_message(const char* msg);

class HANGMAN_GAME {
private:
    bool game_must_end = false;
    std::string words[15] = {
    "bicycle",      "umbrella", "jazz",
    "penguin",      "cactus",   "telescope",
    "origami",      "volcano",  "harmonica",
    "butterfly",    "country",  "mountain",
    "ocean",        "forest",   "city"
};


public:
    std::string tamagotchi_name;
    std::string tamagotchi_msg = "NaN";
    
    std::string random_word;
    std::string visible_word;
    std::string used_chars;
    int word_selected_id;


    void choose_random_word();

    bool check_word_is_valid(std::string c); 
    bool check_end_game();

    void loop();
    void play();
    void set_tamagotchi_name(std::string tama_name);
};

#endif