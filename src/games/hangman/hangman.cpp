#include "hangman.hpp"

void HANGMAN_GAME::choose_random_word() {
    int v = rand() % sizeof(words) / sizeof(words[0]);
    random_word = words[v];
    word_selected_id = v;

    visible_word = "";
    used_chars   = "";
    game_must_end = false;
    for (int i = 0; i < words[v].size(); i++) {
        visible_word += "_";
    }
}

bool HANGMAN_GAME::check_word_is_valid(std::string c) {
    bool exist = false;

    for (int i = 0; i < used_chars.size(); i++) {
        if (used_chars[i] == c[0]) {
            tamagotchi_msg = "You already used this char";
            return false;
        }
    }
    
    for (int i = 0; i < random_word.size(); i++) {
        if (random_word[i] == c[0]) {
            visible_word[i] = c[0];
            exist = true;
        }
    }

    if (exist) tamagotchi_msg = "Nice!";
    else       tamagotchi_msg = "Well, no.";

    used_chars += c[0];
    return exist;
}

bool HANGMAN_GAME::check_end_game() {
    bool game_must_end = true;

    for (int i = 0; i < visible_word.size(); i++) {
        if (visible_word[i] == "_"[0]) {
            return false;
        }
    }

    return true;
}

void HANGMAN_GAME::loop() {
    sent_message("I chose a word, try to guess what it is!");

    while (!game_must_end) {
        std::system("clear");
        if (tamagotchi_msg != "NaN") {
            sent_message(tamagotchi_msg.c_str()); 
            tamagotchi_msg = "NaN";
        }

        std::cout << visible_word << "\n\n";
        std::cout << "Used chars: " << used_chars << "\n\n> ";
    
        std::string line;
        std::getline(std::cin, line);

        bool char_exist = check_word_is_valid(line.c_str());

        if (char_exist) {
            if (check_end_game()) {
                std::system("clear");
                std::string end_message = "The word was:" + random_word;

                std::system("clear");
                sent_message("Yey! You won!");
                //sent_message(end_message.c_str());
                sent_message(("The word was: " + random_word).c_str());

                std::cin.ignore();
                game_must_end = true;
            }
        }
    }
}

void HANGMAN_GAME::play() {
    choose_random_word();

    loop();
}

void HANGMAN_GAME::set_tamagotchi_name(std::string tama_name) {
    tamagotchi_name = tama_name;
}