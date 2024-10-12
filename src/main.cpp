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

const char* hello_message[2]  = { "Hello!", "Hi!" };
const char* hungry_message[2] = { "I'm hungry.", "I'm very hungry, feed me!" };
const char* sad_message[1]    = { "We can play something?" };

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
                //std::getline(std::cin, tama_name);


                std::cout << "[DEBUG]" << tama_name << "\n\n";

                tamagotchi_data.name       = tama_name;
                tamagotchi_data.health     = 100;
                tamagotchi_data.hunger     = 10;
                tamagotchi_data.sleepiness = 100;
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

void loop() {
    int msg_id;
    msg_id = rand() % 2;
    draw_sprite(SPRITE_HAPPY);
    sent_message(hello_message[msg_id]);
    
    show_actions();
    std::string input;
    std::cout << "> ";

    while (std::getline(std::cin, input)) {
        std::system("clear");

        draw_sprite(SPRITE_HAPPY);
        show_actions();
        std::cout << "> ";

        if (input == "q" || input == "Q") {
            save_data();
            return;
        }

        if (input == "f" || input == "F") {
            feed_tamagotchi();
        }

        if (input == "p" || input == "P") {
        }

        if (input == "s" || input == "S") {
            show_stats();
        }
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