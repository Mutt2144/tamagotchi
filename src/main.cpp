#define NAME_ATTRIB         0
#define HEALTH_ATTRIB       1
#define HUNGER_ATTRIB       2
#define SLEEPINESS_ATTRIB   3
#define HAPPINESS_ATTRIB    4

#define SPRITE_HAPPY        "assets/happy.gotchi"
#define SPRITE_SAD          "assets/sad.gotchi"
#define SPRITE_ANGRY        "assets/angry.gotchi"

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

//void sent_message(const char* msg);

#include "games/hangman/hangman.hpp"

#include "include_files.cpp"

HANGMAN_GAME Hangman_Game;

const char* hello_message[2]  = { "Hello!", "Hi!" };
const char* hungry_message[2] = { "I'm hungry.", "I'm very hungry, feed me!" };
const char* angry_message[1]  = { "I'm angry!" };
const char* feed_message[3]   = { "Thank you!", "Thank you very much!", "I'm full!" };
const char* sad_message[1]    = { "We can play something?" };

const char* invalid_message[2] = { "What?", "I don't understand you." };


struct TAMAGOTCHI_DATA {
    std::string name;
    int health;
    int hunger;
    int sleepiness;
    int happiness;
    int rage;
};

TAMAGOTCHI_DATA tamagotchi_data;

void feed_tamagotchi() {
    int value = rand() % 20;

    tamagotchi_data.hunger -= value;
    tamagotchi_data.happiness += 2;
    
    if (tamagotchi_data.hunger < 0) tamagotchi_data.hunger = 0;
    if (tamagotchi_data.happiness > 100) tamagotchi_data.happiness = 10;
}


const char* get_face_id() {
    if (tamagotchi_data.happiness >= 50 && tamagotchi_data.health > 65) {
        return SPRITE_HAPPY;
    }
    if (tamagotchi_data.happiness < 50) {
        return SPRITE_SAD;
    }
    if (tamagotchi_data.rage > 50) {
        return SPRITE_ANGRY;
    }

    // TODO:

    return "";
};

void sent_message(const char* msg) {
    std::cout << "(" << tamagotchi_data.name << "): " << msg << "\n";
}

void show_stats() {
    std::cout << "Name:       " << tamagotchi_data.name << "\n";
    std::cout << "health:     " << tamagotchi_data.health << "\n";
    std::cout << "hunger:     " << tamagotchi_data.hunger << "\n";;
    std::cout << "sleepiness: " << tamagotchi_data.sleepiness << "\n";
    std::cout << "happiness:  " << tamagotchi_data.happiness << "\n";
}

void show_actions() {
    std::cout << "[F] Feed      [P] Play      [S] Stats      [Q] Quit and save\n";
}

void draw_sprite(const char* path) {
    std::ifstream file(path);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }

        file.close();
    } 
}

void set_tamagotchi_attrib(const int attrib, int value) {
    switch (attrib)
    {
    case HEALTH_ATTRIB:
        tamagotchi_data.health = value;
        break;
    
    case HUNGER_ATTRIB:
        tamagotchi_data.hunger = value;
        break;

    case SLEEPINESS_ATTRIB:
        tamagotchi_data.sleepiness = value;
        break;

    case HAPPINESS_ATTRIB:
        tamagotchi_data.happiness = value;
        break;
    }
}

void save_data() {
    std::ofstream file("./tamagotchi_data.txt");

    if (file.is_open()) {
        file << tamagotchi_data.name << "\n";
        file << tamagotchi_data.health << "\n";
        file << tamagotchi_data.hunger << "\n";
        file << tamagotchi_data.sleepiness << "\n";
        file << tamagotchi_data.happiness << "\n";

        file.close();
    }
}

void load_data() {
    std::ifstream data("./tamagotchi_data.txt");
    std::string line;
    int line_count = 0;

    if (data.is_open()) {
        while (std::getline(data, line)) {
            if (line == "no_data") {
                std::cout << "Type the name of your tamagotchi: ";
                std::string tama_name;
                std::getline(std::cin, tama_name);


                std::cout << "[DEBUG]" << tama_name << "\n\n";

                tamagotchi_data.name       = tama_name;
                tamagotchi_data.health     = 100;
                tamagotchi_data.hunger     = 5;
                tamagotchi_data.sleepiness = 5;
                tamagotchi_data.happiness  = 100;
            } else {
                if (line_count == 0) tamagotchi_data.name = line;
                if (line_count == 1) set_tamagotchi_attrib(HEALTH_ATTRIB,     std::stoi(line));
                if (line_count == 2) set_tamagotchi_attrib(HUNGER_ATTRIB,     std::stoi(line));
                if (line_count == 3) set_tamagotchi_attrib(SLEEPINESS_ATTRIB, std::stoi(line));
                if (line_count == 4) set_tamagotchi_attrib(HAPPINESS_ATTRIB,  std::stoi(line));
            }

            line_count++;
        }

        data.close();
    }
}

void choose_game() {
    std::system("clear");
    std::string line;

    sent_message("Let's play!");

    while (true) {
        sent_message("What you want play?\n");
        std::cout << "[1] Hangman   [2] NULL\n> ";
        std::getline(std::cin, line);

        if (line == "1") {
            Hangman_Game.play();
            break;
        }
        else {
            std::system("clear");
            sent_message("Humm, this isn't a option, choose again");
        }

        break;
    }

    tamagotchi_data.happiness  += rand() % 20;
    tamagotchi_data.hunger     += rand() % 10;
    tamagotchi_data.sleepiness += rand() % 8;
}

void loop() {
    std::string input;
    std::string last_action = "no_action";

    int msg_id;
    
    while (true) {
        std::system("clear");
        draw_sprite(get_face_id());
    
        if (last_action == "no_action")      sent_message(hello_message[rand() % sizeof(hello_message) / sizeof(hello_message[0])]);                
        if (tamagotchi_data.hunger > 75)     sent_message(hungry_message[1]);
        else if (tamagotchi_data.hunger > 50)     sent_message(hungry_message[0]);

        if (last_action == "feed")           sent_message(feed_message[msg_id]);
        if (last_action == "invalid_action") sent_message(invalid_message[msg_id]);
        //std::cout << "ID: " << msg_id << "\n";
        //std::cout << "length: " << sizeof(feed_message) / sizeof(feed_message[0]) << "\n";

        show_actions();
        
        std::cout << "> ";
        std::getline(std::cin, input);
        
        switch (std::tolower(input[0])) {
            case 'q':
                save_data();
                return;
            case 'f':
                feed_tamagotchi();
                last_action = "feed";
                
                if (tamagotchi_data.hunger > 5) msg_id = rand() % 2;
                else msg_id = 2;
                break;
            case 'p':
                // TODO: Implement play functionality
                last_action = "play";
                choose_game();
                break;
            case 's':
                show_stats();
                last_action = "stats";
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                break;
            default:
                msg_id = rand() % sizeof(invalid_message) / sizeof(invalid_message[0]);
                last_action = "invalid_action";
        }
        
        // Update tamagotchi state here (e.g., increase hunger, decrease happiness over time)
        // TODO: Implement state updates
    }
}



int main() {
    srand(time(0));

    std::system("clear");
    load_data();

    loop();

    save_data();
    return 0;
}