#define HEALTH_ATTRIB       0
#define HUNGER_ATTRIB       1
#define SLEEPINESS_ATTRIB   2
#define HAPPINESS_ATTRIB    3

#define SPRITE_HAPPY        "assets/happy.gotchi"
#define SPRITE_SAD          "assets/sad.gotchi"
#define SPRITE_ANGRY        "assets/angry.gotchi"

#include <iostream>
#include <fstream>
#include <string>

struct TAMAGOTCHI_DATA {
    int health;
    int hunger;
    int sleepiness;
    int happiness;
};

TAMAGOTCHI_DATA tamagotchi_data;

const char* get_face_id() {
    if (tamagotchi_data.happiness > 60 && tamagotchi_data.health > 65) {
        return SPRITE_HAPPY;
    }

    // TODO:

    return "";
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
                tamagotchi_data.health     = 100;
                tamagotchi_data.hunger     = 10;
                tamagotchi_data.sleepiness = 100;
                tamagotchi_data.happiness  = 100;
            } else {
                if (line_count == 0) set_tamagotchi_attrib(HEALTH_ATTRIB,     std::stoi(line));
                if (line_count == 1) set_tamagotchi_attrib(HUNGER_ATTRIB,     std::stoi(line));
                if (line_count == 2) set_tamagotchi_attrib(SLEEPINESS_ATTRIB, std::stoi(line));
                if (line_count == 3) set_tamagotchi_attrib(HAPPINESS_ATTRIB,  std::stoi(line));
            }

            line_count++;
        }

        data.close();
    }
}

void loop() {
    show_actions();
    std::string input;

    while (std::getline(std::cin, input)) {
        std::system("clear");

        show_actions();
    }
}

int main() {
    std::system("clear");
    load_data();
    save_data();
    std::cout << "health:     " << tamagotchi_data.health << "\n";
    std::cout << "hunger:     " << tamagotchi_data.hunger << "\n";;
    std::cout << "sleepiness: " << tamagotchi_data.sleepiness << "\n";
    std::cout << "happiness:  " << tamagotchi_data.happiness << "\n";

    loop();

    return 0;
}