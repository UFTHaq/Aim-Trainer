// Aim-Trainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
// [DONE] IMPLEMENT THE FPP AIM 
// [DONE - MAYBE] Fix Bug the Target spawn in gun area
// Fix the bullet, must be travel not like this
// Coba Buat tampilin 3D OBJ
// Add Timer
//

#include <iostream>
#include <raylib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#include <map>
#include <filesystem>
#include <chrono>

// MAIN COLOR
#define MAINCOLOR                   CLITERAL(Color) {  36,  37,  46, 255 }

// MAIN MENU BUTTON
#define BUTTON_PLAY_COLOR_BASE      CLITERAL(Color) { 118, 234, 192, 255 }
#define BUTTON_PLAY_COLOR_HOVER     CLITERAL(Color) { 143, 255, 207, 255 }

#define BUTTON_QUIT_COLOR_BASE      CLITERAL(Color) { 199,  60,  60, 255 }
#define BUTTON_QUIT_COLOR_HOVER     CLITERAL(Color) { 223,  87,  87, 255 }

// SETUP MENU BUTTON
#define BUTTON_GUN_COLOR_BASE       CLITERAL(Color) {  71, 206, 224, 255 }
#define BUTTON_GUN_COLOR_HOVER      CLITERAL(Color) { 101, 232, 255, 255 }

#define BUTTON_TIME_COLOR_BASE      CLITERAL(Color) {  68, 196, 150, 255 }
#define BUTTON_TIME_COLOR_HOVER     CLITERAL(Color) {  91, 214, 183, 255 }

#define BUTTON_LEVEL_COLOR_BASE     CLITERAL(Color) { 140, 196,  68, 255 }
#define BUTTON_LEVEL_COLOR_HOVER    CLITERAL(Color) { 167, 212, 102, 255 }

#define BUTTON_START_COLOR_BASE     CLITERAL(Color) { 245, 250,   0, 255 }
#define BUTTON_START_COLOR_HOVER    CLITERAL(Color) { 255, 255,  77, 255 }

#define BUTTON_BACK_COLOR_BASE      CLITERAL(Color) { 199,  60,  60, 255 }
#define BUTTON_BACK_COLOR_HOVER     CLITERAL(Color) { 223,  87,  87, 255 }

#define LEADERBOARDS_CANVAS_COLOR   CLITERAL(Color) { 217, 217, 217, 255 }
#define SETUPMENU_CLICKED_COLOR     CLITERAL(Color) { 227, 227, 227, 255 }

// GUN CARD
#define GUN_CARD_COLOR              CLITERAL(Color) {  28,  32,  65, 255 }
#define GUN_POV_CARD_COLOR          CLITERAL(Color) {  40,  43,  68, 255 }
#define GUN_STATS_CARD_COLOR        CLITERAL(Color) {  40,  43,  68, 255 }
#define GUN_CARD_TITLE_COLOR        CLITERAL(Color) { 179, 217, 228, 225 }
#define GUN_CARD_BUTTON_COLOR_BASE  CLITERAL(Color) {  28,  32,  65, 255 }
#define GUN_CARD_BUTTON_COLOR_HOVER CLITERAL(Color) {  55,  64, 110, 255 }

#define GUN_M416_FPP_LOCATION       {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-M416-FPP-1080.png"}
#define GUN_M416_SIDE_LOCATION      {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-M416-SIDE-1080.png"}
#define GUN_AK47_FPP_LOCATION       {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-AK47-FPP-1080.png"}
#define GUN_AK47_SIDE_LOCATION      {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-AK47-SIDE-1080.png"}
#define GUN_AWM_FPP_LOCATION        {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-AWM-FPP-1080.png"}
#define GUN_AWM_SIDE_LOCATION       {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-AWM-SIDE-1080.png"}
#define GUN_GLOCK_FPP_LOCATION      {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-GLOCK-FPP-1080.png"}
#define GUN_GLOCK_SIDE_LOCATION     {"D:/Coding/Raylib C++/Aim-Trainer/Assets/Gun/Gun-GLOCK-SIDE-1080.png"}

#define GUN_COLOR_STOCK             CLITERAL(Color) {  23,  23,  23, 255 }
#define GUN_COLOR_STOCK_HOVER       CLITERAL(Color) {  45,  45,  45, 255 }
#define GUN_COLOR_CAMO              CLITERAL(Color) {  67,  72,  53, 255 }
#define GUN_COLOR_CAMO_HOVER        CLITERAL(Color) {  90,  96,  77, 255 }
#define GUN_COLOR_CANDY             CLITERAL(Color) {  49,  96, 166, 255 }
#define GUN_COLOR_CANDY_HOVER       CLITERAL(Color) {  74, 124, 198, 255 }
#define GUN_COLOR_GOLDEN            CLITERAL(Color) { 225, 192,  17, 255 }
#define GUN_COLOR_GOLDEN_HOVER      CLITERAL(Color) { 240, 212,  55, 255 }

std::vector<std::vector<Color>> gunBtnColorHover{
    {GUN_COLOR_STOCK, GUN_COLOR_STOCK_HOVER},
    {GUN_COLOR_CAMO, GUN_COLOR_CAMO_HOVER},
    {GUN_COLOR_CANDY, GUN_COLOR_CANDY_HOVER},
    {GUN_COLOR_GOLDEN, GUN_COLOR_GOLDEN_HOVER}
};

#define STATS_BASE_BAR_COLOR        CLITERAL(Color) { 217, 217, 217, 255 }
#define STATS_SPEED_COLOR           CLITERAL(Color) { 176,  74,  74, 255 }
#define STATS_POWER_COLOR           CLITERAL(Color) {  74, 115, 176, 255 }
#define STATS_CAPACITY_COLOR        CLITERAL(Color) { 117,  98,  98, 255 }

// TIME CARD
#define TIME_CARD_COLOR             CLITERAL(Color) {  34,  34,  34, 255 }
#define TIME_CARD_BUTTON_HOVER      CLITERAL(Color) { 255, 255, 255, 255 }
#define TIME_CARD_BUTTON_CLICKED    CLITERAL(Color) {  20,  20,  20, 255 }
#define TIME_120_COLOR              CLITERAL(Color) { 110, 207, 108, 255 }
#define TIME_90_COLOR               CLITERAL(Color) { 169, 209,  55, 255 }
#define TIME_60_COLOR               CLITERAL(Color) { 246, 142,  45, 255 }
#define TIME_30_COLOR               CLITERAL(Color) { 243,  71,  71, 255 }

// LEVEL CARD
#define LEVEL_CARD_COLOR            CLITERAL(Color) {  34,  34,  34, 255 }
#define LEVEL_CARD_BUTTON_HOVER     CLITERAL(Color) { 255, 255, 255, 255 }
#define LEVEL_CARD_BUTTON_CLICKED   CLITERAL(Color) {  20,  20,  20, 255 }
#define LEVEL_1_COLOR               CLITERAL(Color) { 110, 207, 108, 255 }
#define LEVEL_2_COLOR               CLITERAL(Color) { 169, 209,  55, 255 }
#define LEVEL_3_COLOR               CLITERAL(Color) { 246, 142,  45, 255 }
#define LEVEL_4_COLOR               CLITERAL(Color) { 243,  71,  71, 255 }


#define ICON_APP_LOC                {"Icons/bullseye.png"}
#define ICON_ARROW_LOC              {"Icons/Arrow2.png"}
#define ICON_SCROLL_BUTTON_LOC      {"Icons/Icon-Scroll3.png"}
#define ICON_SCROLL_BAR_ACC_LOC     {"Icons/Icon-Scroll_Bar.png"}
#define ICON_CLOSE_FIGHT_LOC        {"Icons/Close.png"}

#define FIGHT_BTN_COOLDOWN_FRAMES   100
#define LEADERBOARD_DATA_CAPACITY   100

static const char* CSV_FILENAME_LEADERBOARDS{ "Data/Leaderboards.txt" };


enum GamePage
{
    MAIN_MENU       = 0,
    SETUP_MENU      = 1,
    IN_GAME         = 2,
    GAMEOVER_MENU   = 3
};

enum SetupProperties
{
    GUN     = 0,
    TIME    = 1,
    LEVEL   = 2,
    BACK    = 3,
    START   = 4
};

enum Weapons {
    M416    = 0,
    AK47    = 1,
    AWM     = 2,
    GLOCK   = 3
};

enum Target_Visibility {
    TARGET_VISIBLE = 0,
    TARGET_INVISIBLE = 1
};

struct Game {
    const int w{ 1920 };
    const int h{ 1080 };
    const char* title{ "AIM-TRAINER" };
    int FPS{ 99 };
};

Game game = {};

struct MainMenu {
    const char* title{ "AIM-TRAINER" };
    int title_Pos_Y{ 180 };
    float font_size{ 100 };
    float font_space{ 1 };
    float button_space{ 45 };

    struct Button {
        const char* text{};
        Color color{};
        Color text_color{};
        int BtnPosY{};

        int height{ 400 };
        int width{ 95 };
        float font_size{ 60 };
        float font_space{ 1.F };
        float roundness{ 0.05F };
        int segments{ 10 };
        Rectangle rect { 
            (float)game.w / 2 - height / 2, 
            (float)BtnPosY, 
            (float)height, 
            (float)width 
        };
    };

    Button play{ "PLAY", BUTTON_PLAY_COLOR_BASE, BLACK, (int)((game.h / 2) - (button_space / 2) - (button_space * 2)) };
    Button quit{ "QUIT", BUTTON_QUIT_COLOR_BASE, WHITE, (int)((game.h / 2) + (button_space / 2)) };

    std::vector<const char*> credit{ "First Game By", "UFTHaq" };
    std::vector<float> credit_Pos_Y{ 850, 920 };
    float credit_font_size{ 30 };
    Color credit_color = WHITE;
};

MainMenu mainMenu{};

struct SetupMenu {
    const char* title{ "AIM - TRAINER" };
    int title_Pos_Y{ 80 };
    float title_font_size{ 50 };
    float font_size{ 36 };
    float font_space{ 1 };

    Rectangle clicked_effect_rect{ 200, 200, 180, 100 };
    Color clicked_effect_color{ SETUPMENU_CLICKED_COLOR };

    float roundness{ 0.005F };
    int segments{ 10 };
    Rectangle Base_Canvas_rect{ 200, 280, 1000, 500 };
    Color canvas_color{ BUTTON_GUN_COLOR_BASE };
    const char* leaderboard_text{ "LEADERBOARDS" };
    Rectangle leaderboards_rect{ 1248, 280, 470, 700 };
    Color leaderboards_color{ LEADERBOARDS_CANVAS_COLOR };

    const char* choose_text{ "CHOOSE YOUR PROPERTIES" };

    struct Button {
        const char* text{};
        Vector2 coor{};
        Color color{};
        Color text_color{};

        int height{ 60 };
        int width{ 180 };
        float font_size{ 40 };
        float font_space{ 1 };
        float roundness{ 0.01F };
        int segments{ 10 };
        Rectangle rect{
            coor.x,
            coor.y,
            (float)width,
            (float)height
        };
    };

    Button gun{ "GUN", { 200, 200 }, BUTTON_GUN_COLOR_BASE, BLACK };
    Button time{ "TIME", { 400, 200 }, BUTTON_TIME_COLOR_BASE, BLACK };
    Button level{ "LEVEL", { 600, 200 }, BUTTON_LEVEL_COLOR_BASE, BLACK };
    Button start{ "START", { (Base_Canvas_rect.x + Base_Canvas_rect.width / 2 - gun.width / 2), 920 }, BUTTON_START_COLOR_BASE, BLACK };
    Button back{ "BACK", { (float)(game.w - 180 - 40), 40 }, BUTTON_BACK_COLOR_BASE, WHITE };

};

SetupMenu setupMenu{};
//SetupMenu* setupMenu = new SetupMenu;

struct GunCard{
    float roundness{ 0.01F };
    int segments{ 10 };
    Rectangle rect{ 300, 350, 800, 300 };
    Color color{ GUN_CARD_COLOR };

    struct MiniCard {
        const char* text{};
        Vector2 coor{};
        Color color{};
        Vector2 title_coor{};

        float font_size{ 30 };
        float font_space{ 0 };
        float roundness{ 0.2F };
        int segments{ 10 };
        int width{ 180 };
        int height{ 270 };
        Rectangle rect{
            coor.x,
            coor.y,
            (float)width,
            (float)height
        };

        int title_width{ 140 };
        int title_height{ 36 };
        Rectangle title_rect{
            title_coor.x,
            title_coor.y,
            (float)title_width,
            (float)title_height
        };
        Color title_color{ GUN_CARD_TITLE_COLOR };
        Color text_color{ GUN_CARD_COLOR };
    };

    MiniCard pov{ "POV",{ 320, 366 },  GUN_POV_CARD_COLOR, { 340, 360 } };
    MiniCard stats{ "STATS", {900, 366}, GUN_STATS_CARD_COLOR, { 920, 360 } };

    struct Button {
        Vector2 coor{};
        Color color{ GUN_CARD_COLOR };
        Color texture_color{ WHITE };

        int width{ 106 };
        int height{ 42 };
        float roundness{ 0.5F };
        int segments{ 10 };
        Rectangle rect{
            coor.x,
            coor.y,
            (float)width,
            (float)height
        };
    };

    Button prev{ {592, 656} };
    Button next{ {704, 656} };

    const char* text_color{ "COLOR" };
    float text_color_pos_y{ 558 };
    float color_font_size{ 20.F };
    float font_space{ 1 };
    Color font_color{ WHITE };

    struct ColorButton {
        Rectangle rect{};
        Color color{};
        float roundness{ 0.01F };
        int segments{ 10 };
    };

    float color_width_base{ 60 };
    float color_height_base{ 40 };
    float color_height_clicked{ 44 };

    ColorButton BASE    { {578, 586, 244, 44}, WHITE };
    ColorButton STOCK   { {580, 588, color_width_base, color_height_base}, GUN_COLOR_STOCK };
    ColorButton CAMO    { {640, 588, color_width_base, color_height_base}, GUN_COLOR_CAMO };
    ColorButton CANDY   { {700, 588, color_width_base, color_height_base}, GUN_COLOR_CANDY };
    ColorButton GOLDEN  { {760, 588, color_width_base, color_height_base}, GUN_COLOR_GOLDEN };

    std::vector<ColorButton> GunsColor{ STOCK, CAMO, CANDY, GOLDEN };

    float stats_font_size{ 20.F };
    const char* text_type{ "TYPE" };
    float text_type_y{ 410 };
    float type_gun_y_coor{ 440 };
    float bar_width{ 140 };
    float bar_heigth{ 16 };
    float text_to_bar_space_y{ 22 };
    Color base_bar_color{ STATS_BASE_BAR_COLOR };

    struct Stats {
        const char* text{};
        float bar_coor_y{};
        Color color{};
    };

    Stats speed     { "Speed", 510, STATS_SPEED_COLOR };
    Stats power     { "Power", 554, STATS_POWER_COLOR };
    Stats capacity  { "Capacity", 598, STATS_CAPACITY_COLOR };

    std::vector<Stats> stats_base{ speed, power, capacity };

};

GunCard gunCard{};

struct Gun {
    const char* name{};
    const char* type{};
    int speed{};
    int power{};
    int capacity{};
    Texture2D FPP{};
    Texture2D SIDE{};
    Texture2D FPP_GAME{};
    float bar_length{ 140 };
    int speed_coef{ 1000 };
    int power_coef{ 100 };
    int capacity_coef{ 50 };

    float speed_display() {
        return static_cast<float>(speed) / speed_coef * bar_length;
    }
    float power_display() {
        return static_cast<float>(power) / power_coef * bar_length;
    }
    float capacity_display() {
        return static_cast<float>(capacity) / capacity_coef * bar_length;
    }
};

enum GunColor {
    STOCK   = 0,
    CAMO    = 1,
    CANDY   = 2,
    GOLDEN  = 3
};

struct TimeCard {
    float roundness{ 0.01F };
    int segments{ 10 };
    float width{ 606 };
    float height{ 346 };
    Color color{ TIME_CARD_COLOR };

    struct Button {
        int time{};
        int points{};
        Vector2 coor{};
        const char* text_points{};
        Color color{};
        Color color_hover{TIME_CARD_BUTTON_HOVER};
        Color color_cliked{TIME_CARD_BUTTON_CLICKED};
        Color text_color{ BLACK };
        float font_size{ 54 };
        float font_size_points{ 38 };
        float font_space{ 1 };
        float roundness{ 0.01F };
        int segments{ 10 };
        float width = 300.F;
        float height = 170.F;
        Rectangle rect{
            coor.x,
            coor.y,
            width,
            height
        };
    };

    Button btn_120{ 120, 2, {400, 348}, "Point = 2", TIME_120_COLOR };
    Button btn_90{ 90, 3, {702, 348}, "Point = 3",TIME_90_COLOR };
    Button btn_60{ 60, 4, {400, 516}, "Point = 4",TIME_60_COLOR };
    Button btn_30{ 30, 6, {702, 516}, "Point = 6",TIME_30_COLOR };

    std::vector<Button> timeButtons{ btn_120, btn_90, btn_60, btn_30 };

    Color color_hover{ WHITE };
    Color color_clicked{ TIME_CARD_COLOR };
};

TimeCard timeCard{};

enum TimeClicked {
    SECONDS_120 = 120,
    SECONDS_90  = 90,
    SECONDS_60  = 60,
    SECONDS_30  = 30
};

struct LevelCard {
    float roundness{ 0.01F };
    int segments{ 10 };
    float width{ 606 };
    float height{ 346 };
    Color color{ LEVEL_CARD_COLOR };

    struct Button {
        float radius{};
        int points{};
        const char* text_points{};
        Color color{};
        Color circle_color{ LEVEL_CARD_COLOR };
        Vector2 coor{};
        Color color_hover{LEVEL_CARD_BUTTON_HOVER};
        Color color_cliked{LEVEL_CARD_BUTTON_CLICKED};
        Color text_color{ BLACK };
        float font_size{ 54 };
        float font_size_points{ 38 };
        float font_space{ 1 };
        float roundness{ 0.01F };
        int segments{ 10 };
        float width = 300.F;
        float height = 170.F;
        Rectangle rect{
            coor.x,
            coor.y,
            width,
            height
        };
    };

    Button btn_1{ 30.F, 3, "Point = 3", LEVEL_1_COLOR };
    Button btn_2{ 20.F, 5, "Point = 5",LEVEL_2_COLOR };
    Button btn_3{ 15.F, 7, "Point = 7",LEVEL_3_COLOR };
    Button btn_4{ 10.F, 9, "Point = 9",LEVEL_4_COLOR };

    std::vector<Button> levelButtons{ btn_1, btn_2, btn_3, btn_4};

    Color color_hover{ WHITE };
    Color color_clicked{ LEVEL_CARD_COLOR };
};

LevelCard levelCard{};

enum LevelClicked {
    SOFT = 30,
    EASY = 20,
    MED  = 15,
    HARD = 10
};

struct HighScoreEntry {
    int score{};
    std::string date{};
    int time{};
    std::string level{};
    std::string weapon{};
    size_t color{};


    bool operator<(const HighScoreEntry& other) const {
        return score > other.score;
    }

    std::string getTimeFormatted() const {
        int minutes = time / 60;
        int seconds = time % 60;

        std::ostringstream formattedTime{};
        formattedTime << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        return formattedTime.str();
    }

    int getLevelFormatted(const std::string level) const {
        //return level_map[level];
        std::map<std::string, int> level_map{ {"SOFT", SOFT}, {"EASY", EASY}, {"MED", MED}, {"HARD", HARD} };
        auto iterator = level_map.find(level);
        if (iterator != level_map.end()) {
            return iterator->second;
        }
        else {
            return -1;
        }
    }

    std::string getLevel(const int level_choice) {
        std::map<std::string, int> level_map{ {"SOFT", SOFT}, {"EASY", EASY}, {"MED", MED}, {"HARD", HARD} };
        for (const auto& i : level_map) {
            if (i.second == level_choice) {
                return i.first;
            }
        }
        return "";
    }

    int getWeaponFormatted(const std::string weapon) const {
        std::map<std::string, int> weapon_map{ {"M416", M416}, {"AK47", AK47}, {"AWM", AWM}, {"GLOCK", GLOCK} };
        //return weapon_map[weapon];
        auto iterator = weapon_map.find(weapon);
        if (iterator != weapon_map.end()) {
            return iterator->second;
        }
        else {
            return -1;
        }
    }

    std::string getWeapon(const int weapon_choice) {
        std::map<std::string, int> weapon_map{ {"M416", M416}, {"AK47", AK47}, {"AWM", AWM}, {"GLOCK", GLOCK} };
        for (auto& i : weapon_map) {
            if (i.second == weapon_choice) {
                return i.first;
            }
        }
        return "";
    }
};


//bool isFileExists(const char* filename) {
//    std::ifstream file(filename);
//    return file.good();
//}

bool isFileExists(const char* filename) {
    return std::filesystem::exists(filename);
}

void InitFile(const char* filename)
{
    if (!isFileExists(filename))
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            file << 0;
            file.close();
            std::cout << "INFO: [SUCCESS] MAKE FILE TXT: " << filename << std::endl;
        }
        else {
            std::cerr << "INFO: [FAILED] MAKE FILE FOR WRITING: " << filename << std::endl;
        }
    }
    else {
        std::cout << "INFO: FILE: [" << filename << "] ALREADY EXISTS." << std::endl;
    }
}

void saveScore(const std::vector<HighScoreEntry>& highscores) {
    std::ofstream outFile(CSV_FILENAME_LEADERBOARDS);

    if (outFile.is_open()) {
        for (const auto& entry : highscores) {
            outFile << entry.score << " "
                    << entry.date << " "
                    << entry.time << " "
                    << entry.level << " "
                    << entry.weapon << " "
                    << entry.color << std::endl;
        }
        outFile.close();
        std::cout << "INFO: [SUCCESS] Save Score to: " << CSV_FILENAME_LEADERBOARDS << std::endl;
    }
    else {
        std::cout << "INFO: [FAILED] To open file: " << CSV_FILENAME_LEADERBOARDS << std::endl;
    }
}

std::vector<HighScoreEntry> loadLeaderboardsTxt() {
    std::ifstream LeaderboardsFile(CSV_FILENAME_LEADERBOARDS);
    std::vector<HighScoreEntry> highScoreData{};

    if (LeaderboardsFile.is_open()) {
        HighScoreEntry entry{};
        while (LeaderboardsFile >> entry.score >> entry.date >> entry.time >> entry.level >> entry.weapon >> entry.color) {
            highScoreData.push_back(entry);
        }
        LeaderboardsFile.close();
        std::cout << "INFO: [SUCCESS] Load data from: " << CSV_FILENAME_LEADERBOARDS << std::endl;
    }

    return highScoreData;
}


void DisplayMainMenu(GamePage& gamePage, const Font& BigFont, const Font& MainstreamFont);

std::vector<Gun> LoadGunsData();

void DisplaySetupMenu(GamePage& gamePage, std::vector<Gun>& Guns, std::vector<HighScoreEntry>& LeaderboardData, SetupProperties& setupProperties, const Font& BigFont, const Font& MainstreamFont, const Font& NumberFont);

void GunCardDisplay(std::vector<Gun>& Guns, Vector2& mouse_position, const Font& font);

void TimeCardDisplay(Vector2& mouse_position, const Font& font);

void LevelCardDisplay(Vector2& mouse_position, const Font& font);

void DisplayInGame(GamePage& gamePage, std::vector<Gun>& Guns, int time_choice, size_t level_choice, std::chrono::system_clock::time_point& time_start, const Font& font);

Vector2 RandomizeTarget();

void PopupCooldownStart();

void IsPopopCooldownActive();

void DisplayGameOverMenu(GamePage& gamePage, std::vector<HighScoreEntry>& LeaderboardData, std::vector<Gun>& Guns, const Font& BigFont, const Font& MediumFont);

void ResizeContentPopupLeaderboard(std::vector<HighScoreEntry>& LeaderboardData);

std::string getDate();

void ScreenShot();

void btnTimeHoverClikcked(
    Vector2& mouse_position, Vector2& btn_clicked, Vector2& btn_hover,
    Rectangle& btn_120_rect,
    Rectangle& btn_90_rect,
    Rectangle& btn_60_rect,
    Rectangle& btn_30_rect,
    float& line_thick
);

void btnLevelHoverClicked(
    Vector2& mouse_position, Vector2& btn_clicked, Vector2& btn_hover,
    Rectangle& btn_1_rect,
    Rectangle& btn_2_rect,
    Rectangle& btn_3_rect,
    Rectangle& btn_4_rect,
    float& line_thick
);

static Font TitleFont = {};
static Font MediumFont = {};
static Font MainstreamFont = {};
static Font NumberFont = {};
Texture2D ARROW_TEX = {};
Texture2D SCROLL_UP_DOWN_TEX = {};
Texture2D SCROLL_BAR_TEX = {};
Texture2D CLOSE_FIGHT_TEX = {};

Vector2 btn_hover = {};
Vector2 btn_clicked{
    (setupMenu.Base_Canvas_rect.x + (setupMenu.Base_Canvas_rect.width - timeCard.width) / 2) + 2 + 4,
    (setupMenu.Base_Canvas_rect.y + (setupMenu.Base_Canvas_rect.height - timeCard.height) / 2) + 2 + 4,
};

size_t weapon_choice = {};
size_t weapon_color = {};
int time_choice = { SECONDS_120 };
size_t level_choice = { SOFT };
bool time_start_called = false;
auto time_start = std::chrono::system_clock::now();
int score = {};
bool is_leaderboard_saved_to_txt = true;
bool is_new_data_saved_to_vector_leaderboard = true;
bool popup_cooldown_active = false;
std::vector<bool> is_content_popup_opens{};
std::chrono::steady_clock::time_point popup_fight_timer_start{};

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(game.w, game.h, game.title);
    //SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
	SetTargetFPS(game.FPS);
    SetWindowIcon(LoadImage(ICON_APP_LOC));

    TitleFont = LoadFontEx("D:/Coding/Raylib C++/Aim-Trainer/Fonts/Inter/static/Inter-SemiBold.ttf", 140, 0, FONT_DEFAULT);
    SetTextureFilter(TitleFont.texture, TEXTURE_FILTER_BILINEAR);

    MediumFont = LoadFontEx("D:/Coding/Raylib C++/Aim-Trainer/Fonts/Inter/static/Inter-SemiBold.ttf", 80, 0, FONT_DEFAULT);
    SetTextureFilter(MediumFont.texture, TEXTURE_FILTER_BILINEAR);

    MainstreamFont = LoadFontEx("D:/Coding/Raylib C++/Aim-Trainer/Fonts/Inter/static/Inter-SemiBold.ttf", 40, 0, FONT_DEFAULT);
    SetTextureFilter(MainstreamFont.texture, TEXTURE_FILTER_BILINEAR);

    NumberFont = LoadFontEx("D:/Coding/Raylib C++/Aim-Trainer/Fonts/Monomaniac_One/MonomaniacOne-Regular.ttf", 80, 0, FONT_DEFAULT);
    SetTextureFilter(NumberFont.texture, TEXTURE_FILTER_BILINEAR);

    GamePage gamePage = MAIN_MENU;
    SetupProperties setupProperties = GUN;
    
    std::vector<Gun> Guns = LoadGunsData();

    Image ARROW = LoadImage(ICON_ARROW_LOC);
    ARROW_TEX = LoadTextureFromImage(ARROW);
    Color Arrow_TEX_Color = WHITE;

    Image SCROLL_BUTTON = LoadImage(ICON_SCROLL_BUTTON_LOC);
    SCROLL_UP_DOWN_TEX = LoadTextureFromImage(SCROLL_BUTTON);
    SetTextureFilter(SCROLL_UP_DOWN_TEX, TEXTURE_FILTER_BILINEAR);

    Image SCROLL_BAR_ACCENT = LoadImage(ICON_SCROLL_BAR_ACC_LOC);
    SCROLL_BAR_TEX = LoadTextureFromImage(SCROLL_BAR_ACCENT);

    Image CLOSE_FIGHT = LoadImage(ICON_CLOSE_FIGHT_LOC);
    CLOSE_FIGHT_TEX = LoadTextureFromImage(CLOSE_FIGHT);
    SetTextureFilter(CLOSE_FIGHT_TEX, TEXTURE_FILTER_BILINEAR);
    
    InitFile(CSV_FILENAME_LEADERBOARDS);
    std::vector<HighScoreEntry> LeaderboardData = loadLeaderboardsTxt();
    ResizeContentPopupLeaderboard(LeaderboardData);


    while (!WindowShouldClose()) {
        ScreenShot();
        BeginDrawing();
        ClearBackground(MAINCOLOR);
        DrawFPS(5, 5);

        switch (gamePage)
        {
        case MAIN_MENU:
            DisplayMainMenu(gamePage, TitleFont, MainstreamFont);
            break;

        case SETUP_MENU:
            DisplaySetupMenu(gamePage, Guns, LeaderboardData, setupProperties, MediumFont, MainstreamFont, NumberFont);
            break;

        case IN_GAME:
            DisplayInGame(gamePage, Guns, time_choice, level_choice, time_start, MediumFont);
            break;

        case GAMEOVER_MENU:
            DisplayGameOverMenu(gamePage, LeaderboardData, Guns, TitleFont, MediumFont);
            break;

        default:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    UnloadFont(TitleFont);
    

	return 0;
}

void ScreenShot()
{
    if (IsKeyPressed(KEY_S)) {
        TakeScreenshot("./Icons/SS.png");
    }
}

void DisplayGameOverMenu(GamePage& gamePage, std::vector<HighScoreEntry>& LeaderboardData, std::vector<Gun>& Guns, const Font& BigFont, const Font& MediumFont)
{
    ShowCursor();

    if (!is_new_data_saved_to_vector_leaderboard) {
        HighScoreEntry newData{};
        newData.score = score;
        newData.date = getDate();
        newData.time = time_choice;
        newData.level = newData.getLevel((int)level_choice);
        newData.weapon = newData.getWeapon((int)weapon_choice);
        newData.color = weapon_color;

        LeaderboardData.push_back(newData);
        is_new_data_saved_to_vector_leaderboard = true;

        std::sort(LeaderboardData.begin(), LeaderboardData.end());
        is_leaderboard_saved_to_txt = false;

        if (LeaderboardData.size() > LEADERBOARD_DATA_CAPACITY) {
            LeaderboardData.pop_back();
        }

        if (!is_leaderboard_saved_to_txt) {
            saveScore(LeaderboardData);
            is_leaderboard_saved_to_txt = true;
        }

        ResizeContentPopupLeaderboard(LeaderboardData);
    }

    float source_width = (float)Guns.at(weapon_choice).FPP_GAME.width / 4;
    float source_height = 1080;
    static float gun_pos_y = 0;
    float recoil = 0;   // BELUM di IMPLEMENTASI
    gun_pos_y += recoil;
    Rectangle dest = {
        0,
        gun_pos_y,
        source_width,
        source_height
    };
    Rectangle source = { weapon_color * source_width, 0, source_width, source_height };
    DrawTexturePro(Guns.at(weapon_choice).FPP_GAME, source, dest, { 0,0 }, 0, WHITE);

    {
        // SCORE INFO
        float font_size = 40;
        float font_space = 0.5F;
        score = 245;
        std::string score_text_string = "Score : " + std::to_string(score);
        const char* score_text = score_text_string.c_str();
        Vector2 top_pos_info = { 20, 20 };
        Vector2 score_text_measure = MeasureTextEx(MediumFont, score_text, font_size, font_space);
        Vector2 score_text_coor = {
            top_pos_info.x,
            top_pos_info.y
        };
        DrawTextEx(MediumFont, score_text, score_text_coor, font_size, font_space, WHITE);

        // TIME INFO
        int time = 0;
        int minutes = time / 60;
        int seconds = time % 60;

        std::ostringstream formattedTime{};
        formattedTime << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        std::string time_string = formattedTime.str();

        const char* time_text = time_string.c_str();
        Vector2 time_text_measure = MeasureTextEx(MediumFont, time_text, font_size, font_space);
        Vector2 time_text_coor = {
            GetScreenWidth() - time_text_measure.x - top_pos_info.x,
            top_pos_info.y
        };
        DrawTextEx(MediumFont, time_text, time_text_coor, font_size, font_space, WHITE);
    }

    // FILTER BLUR TRANSPARENT
    DrawRectangleRec( 
        { 0,0,(float)GetScreenWidth(), (float)GetScreenHeight() }, 
        Fade(Color{ 38, 38, 41, 255 }, 0.6F) 
    );

    {
        // DRAW GAME OVER TITLE
        float font_size = 150;
        float font_space = 1;
        float alpha = 0.75F;
        const char* game_over_text = "GAME OVER";
        Vector2 game_over_measure = MeasureTextEx(BigFont, game_over_text, font_size, font_space);
        Vector2 game_over_coor = {
            0 + ((GetScreenWidth() - game_over_measure.x) / 2),
            GetScreenHeight() * 0.2F
        };

        if (CheckCollisionPointRec(GetMousePosition(), { game_over_coor.x, game_over_coor.y, game_over_measure.x, game_over_measure.y })) {
            alpha = 0.95F;
        }

        DrawTextEx(BigFont, game_over_text, game_over_coor, font_size, font_space, Fade(WHITE, alpha));
    }

    std::vector<std::string> button_text{ "PLAY AGAIN", "SETUP MENU", "QUIT" };
    std::vector<Color> button_color{ {140, 196, 68, 255}, {71, 206, 224, 255}, {243, 71, 71, 255} };
    
    {
        float width = GetScreenHeight() * 0.35F;
        float height = width * 0.25F;
        float space_rect = height * 0.4F;
        float alpha_rect = {};
        Color font_color = BLACK;
        float alpha_text = {};

        //Rectangle rect = {};

        for (size_t i = 0; i < button_text.size(); i++) {
            Color color = button_color[i];
            Rectangle border_rect = {
                (GetScreenWidth() - width) / 2,
                (GetScreenHeight() / 2) - (height * 0.7F) + ((height + space_rect) * i),
                width,
                height
            };

            float button_padding = 0;

            if (CheckCollisionPointRec(GetMousePosition(), border_rect)) {
                alpha_rect = 0.85F;
                alpha_text = 0.95F;
                font_color = WHITE;
                std::string text = button_text[i];

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    button_padding = border_rect.height * 0.035F;
                }
                else {
                    button_padding = 0;
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (text == "PLAY AGAIN") {
                        time_start_called = false;
                        gamePage = IN_GAME;
                    }
                    else if (text == "SETUP MENU") {
                        gamePage = SETUP_MENU;
                    }
                    else if (text == "QUIT") {
                        CloseWindow();
                    }
                    score = 0;
                }

            }
            else {
                alpha_rect = 0.4F;
                alpha_text = 0.5F;
                font_color = BLACK;
            }

            Rectangle button_rect = {
                border_rect.x + button_padding,
                border_rect.y + button_padding,
                border_rect.width - (button_padding * 2),
                border_rect.height - (button_padding * 2)
            };
            DrawRectangleRounded(button_rect, 0.05F, 10, Fade(color, alpha_rect));

            float font_size = button_rect.height * 0.600F;
            float font_space = 0;
            const char* text = button_text[i].c_str();
            Vector2 text_measure = MeasureTextEx(MediumFont, text, font_size, font_space);
            Vector2 text_coor = {
                button_rect.x + (button_rect.width - text_measure.x) / 2,
                button_rect.y + (button_rect.height - text_measure.y) / 2
            };
            DrawTextEx(MediumFont, text, text_coor, font_size, font_space, Fade(font_color, alpha_text));

        }

    }

}

void ResizeContentPopupLeaderboard(std::vector<HighScoreEntry>& LeaderboardData)
{
    is_content_popup_opens.resize(LeaderboardData.size(), false);
}

void DisplayInGame(GamePage& gamePage, std::vector<Gun>& Guns, int time, size_t level, std::chrono::system_clock::time_point& time_start, const Font& font)
{
    //if (!IsCursorHidden) {
        HideCursor();
    //}

    float dt = GetFrameTime();
    float recoil_distance = 20.F;

    static size_t all_bullet = 200;
    size_t magazine_size = Guns[weapon_choice].capacity;
    static size_t bullet_in_gun = magazine_size;
    size_t reload = magazine_size - bullet_in_gun;
    size_t last_reload = all_bullet;
    static size_t target_visibility = TARGET_VISIBLE;

    Vector2 crosshair_coor = { (float)(GetScreenWidth() / 2), (float)(GetScreenHeight() / 2) };
    float crosshair_radius = 6.F;

    static Vector2 target_coor = { (float)(GetScreenWidth() / 2), (float)(GetScreenHeight() / 2) };
    float target_radius = (float)level_choice;

    if (IsKeyPressed(KEY_Q)) {
        gamePage = SETUP_MENU;
    }
    if (IsKeyPressed(KEY_G)) {
        gamePage = GAMEOVER_MENU;
    }

    bool at_target = CheckCollisionCircles(crosshair_coor, crosshair_radius, target_coor, target_radius);

    static Vector2 prev_mouse_pos = { 0,0 };
    static Vector2 current_mouse_pos = { 0,0 };

    // SHOOT
    if (bullet_in_gun > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        bullet_in_gun--;
        //recoiling

        if (at_target) {
            score++;
            target_visibility = TARGET_INVISIBLE;

            Vector2 target_pos = RandomizeTarget();

            Rectangle area_rect = {
                GetScreenWidth() * 0.375F,
                GetScreenHeight() * 0.40F,
                GetScreenWidth() * 0.25F,
                GetScreenHeight() * 0.60F
            };

            //DrawRectangleRec(area_rect, LIGHTGRAY);

            // CHECK TARGET RESPAWN ON FORBIDEN AREA OR NOT
            while (CheckCollisionPointRec(target_pos, area_rect)) {
                target_pos = RandomizeTarget();
            }

            target_coor = target_pos;
            SetMousePosition((int)crosshair_coor.x, (int)crosshair_coor.y);
            prev_mouse_pos = GetMousePosition();

            target_visibility = TARGET_VISIBLE;
        }
    }




    // RELOAD
    if (IsKeyPressed(KEY_R) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && all_bullet > 0) {
        size_t reload = magazine_size - bullet_in_gun;

        if (reload <= all_bullet) {
            bullet_in_gun += reload;
            all_bullet -= reload;
        }
        else {
            bullet_in_gun += all_bullet;
            all_bullet -= all_bullet;
        }
    }

    current_mouse_pos = GetMousePosition();
    
    float delta_x = current_mouse_pos.x - prev_mouse_pos.x;
    float delta_y = current_mouse_pos.y - prev_mouse_pos.y;

    target_coor.x -= delta_x;
    target_coor.y -= delta_y;

    prev_mouse_pos = current_mouse_pos;

    {
        // DRAW TARGET
        DrawCircle((int)target_coor.x, (int)target_coor.y, (float)level_choice, RED);
    }

    {
        // DRAW CROSSHAIR
        DrawCircle((int)crosshair_coor.x, (int)crosshair_coor.y, crosshair_radius, LIGHTGRAY);
    }

    {
        // DRAW WEAPON
        
        //TEMPORARY FOR DEBUGGING PROCESS ONLY
        if (IsKeyPressed(KEY_ONE)) {
            weapon_choice = M416;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            weapon_choice = AK47;
        }
        else if (IsKeyPressed(KEY_THREE)) {
            weapon_choice = AWM;
        }
        else if (IsKeyPressed(KEY_FOUR)) {
            weapon_choice = GLOCK;
        }
        //

        float source_width = (float)Guns.at(weapon_choice).FPP_GAME.width / 4;
        float source_height = 1080;
        static float gun_pos_y = 0;
        static float offset = 0;
        float recoil = 0;   // BELUM di IMPLEMENTASI
        gun_pos_y += recoil;

        switch (weapon_choice)
        {
        case M416:
            offset = 5;
            break;
        case AK47:
            offset = 1;
            break;
        case AWM:
            offset = 0;
            break;
        case GLOCK:
            offset = 0;
            break;
        default:
            break;
        }

        Rectangle dest = {
            0,
            gun_pos_y + offset,
            source_width,
            source_height
        };
        Rectangle source = { weapon_color * source_width, 0, source_width, source_height };
        DrawTexturePro(Guns.at(weapon_choice).FPP_GAME, source, dest, { 0,0 }, 0, WHITE);
    }

    {
        // SCORE INFO
        float font_size = 40;
        float font_space = 0.5F;
        
        std::string score_text_string = "Score : " + std::to_string(score);
        const char* score_text = score_text_string.c_str();
        Vector2 top_pos_info = { 20, 20 };
        Vector2 score_text_measure = MeasureTextEx(font, score_text, font_size, font_space);
        Vector2 score_text_coor = {
            top_pos_info.x,
            top_pos_info.y
        };
        DrawTextEx(font, score_text, score_text_coor, font_size, font_space, WHITE);

        // TIME INFO
        if (!time_start_called) {
            time_start = std::chrono::system_clock::now();
            all_bullet = 200;
            bullet_in_gun = magazine_size;
            time_start_called = true;
        }

        auto time_now = std::chrono::system_clock::now();
        auto time_diff = std::chrono::duration_cast<std::chrono::seconds>(time_now - time_start);

        int time_reduce = (int)time_diff.count();
        time = time - time_reduce;

        if (time <= 0) {
            time = 0;
            gamePage = GAMEOVER_MENU;
            is_new_data_saved_to_vector_leaderboard = false;
        }

        int minutes = time / 60;
        int seconds = time % 60;

        std::ostringstream formattedTime{};
        formattedTime << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        std::string time_string = formattedTime.str();

        const char* time_text = time_string.c_str();
        Vector2 time_text_measure = MeasureTextEx(font, time_text, font_size, font_space);
        Vector2 time_text_coor = {
            GetScreenWidth() - time_text_measure.x - top_pos_info.x,
            top_pos_info.y
        };
        DrawTextEx(font, time_text, time_text_coor, font_size, font_space, WHITE);
    }

    {
        // BULLET INFO
        float font_size = 40;
        float font_space = 0.5F;

        float width = GetScreenWidth() * 0.09F;
        float height = width * 0.325F;
        Rectangle rect = {
            (float)(GetScreenWidth() - width) / 2,
            (float)(GetScreenHeight() - 130),
            width,
            height
        };
        DrawRectangleRounded(rect, 0.1F, 10, Fade(WHITE, 0.65F));

        std::string bullet_text = std::to_string(bullet_in_gun) + "/" + std::to_string(all_bullet);
        Vector2 bullet_text_measure = MeasureTextEx(font, bullet_text.c_str(), font_size, font_space);
        Vector2 bullet_text_coor = {
            rect.x + ((rect.width - bullet_text_measure.x) / 2),
            rect.y + ((rect.height - bullet_text_measure.y) / 2)
        };
        DrawTextEx(font, bullet_text.c_str(), bullet_text_coor, font_size, font_space, BLACK);
    }

}

Vector2 RandomizeTarget()
{
    Vector2 random_coor{};
    float random_x = (float)GetRandomValue(150, 1550);
    float random_y = (float)GetRandomValue(150, 650);
    random_coor = { random_x, random_y };

    return random_coor;
}

std::string getDate()
{
    auto now{ std::chrono::system_clock::now() };
    auto now_time_t{ std::chrono::system_clock::to_time_t(now) };
    tm now_tm{}; 
    localtime_s(&now_tm, &now_time_t);

    std::stringstream ss{};
    ss << std::setw(2) << std::setfill('0') << now_tm.tm_mday << "/"
        << std::setw(2) << std::setfill('0') << now_tm.tm_mon + 1 << "/"
        << std::setw(2) << std::setfill('0') << (now_tm.tm_year + 1900);

    std::string formatted_date = ss.str();

    return formatted_date;
}

std::vector<Gun> LoadGunsData() {
    std::vector<std::vector<int>> size{ {1920 * 1, 295 * 1}, {1280 * 1, 180 * 1} };

    Image FPP_M416 = LoadImage(GUN_M416_FPP_LOCATION);
    Image SIDE_M416 = LoadImage(GUN_M416_SIDE_LOCATION);
    Texture2D FPP_M416_TEX_IN_GAME = LoadTextureFromImage(FPP_M416);
    ImageResize(&FPP_M416, size[0][0], size[0][1]);
    ImageResize(&SIDE_M416, size[1][0], size[1][1]);
    Texture2D FPP_M416_TEX_SETUP = LoadTextureFromImage(FPP_M416);
    Texture2D SIDE_M416_TEX_SETUP = LoadTextureFromImage(SIDE_M416);

    Image FPP_AK47 = LoadImage(GUN_AK47_FPP_LOCATION);
    Image SIDE_AK47 = LoadImage(GUN_AK47_SIDE_LOCATION);
    Texture2D FPP_AK47_TEX_IN_GAME = LoadTextureFromImage(FPP_AK47);
    ImageResize(&FPP_AK47, size[0][0], size[0][1]);
    ImageResize(&SIDE_AK47, size[1][0], size[1][1]);
    Texture2D FPP_AK47_TEX_SETUP = LoadTextureFromImage(FPP_AK47);
    Texture2D SIDE_AK47_TEX_SETUP = LoadTextureFromImage(SIDE_AK47);

    Image FPP_AWM = LoadImage(GUN_AWM_FPP_LOCATION);
    Image SIDE_AWM = LoadImage(GUN_AWM_SIDE_LOCATION);
    Texture2D FPP_AWM_TEX_IN_GAME = LoadTextureFromImage(FPP_AWM);
    ImageResize(&FPP_AWM, size[0][0], size[0][1]);
    ImageResize(&SIDE_AWM, size[1][0], size[1][1]);
    Texture2D FPP_AWM_TEX_SETUP = LoadTextureFromImage(FPP_AWM);
    Texture2D SIDE_AWM_TEX_SETUP = LoadTextureFromImage(SIDE_AWM);

    Image FPP_GLOCK = LoadImage(GUN_GLOCK_FPP_LOCATION);
    Image SIDE_GLOCK = LoadImage(GUN_GLOCK_SIDE_LOCATION);
    Texture2D FPP_GLOCK_TEX_IN_GAME = LoadTextureFromImage(FPP_GLOCK);
    ImageResize(&FPP_GLOCK, size[0][0], size[0][1]);
    ImageResize(&SIDE_GLOCK, size[1][0], size[1][1]);
    Texture2D FPP_GLOCK_TEX_SETUP = LoadTextureFromImage(FPP_GLOCK);
    Texture2D SIDE_GLOCK_TEX_SETUP = LoadTextureFromImage(SIDE_GLOCK);

    Gun M416 = { "M416", "ASSAULT RIFLE", 820, 45, 30 , FPP_M416_TEX_SETUP, SIDE_M416_TEX_SETUP, FPP_M416_TEX_IN_GAME };
    Gun AK47 = { "AK47", "ASSAULT RIFLE", 700, 50, 30 , FPP_AK47_TEX_SETUP, SIDE_AK47_TEX_SETUP, FPP_AK47_TEX_IN_GAME };
    Gun AWM = { "AWM", "SNIPER RIFLE", 300, 95, 7, FPP_AWM_TEX_SETUP, SIDE_AWM_TEX_SETUP, FPP_AWM_TEX_IN_GAME };
    Gun GLOCK = { "GLOCK", "HANDGUN", 400, 25, 7 , FPP_GLOCK_TEX_SETUP, SIDE_GLOCK_TEX_SETUP, FPP_GLOCK_TEX_IN_GAME };

    std::vector<Gun> Guns{ M416, AK47, AWM, GLOCK };

    UnloadImage(FPP_M416);
    UnloadImage(SIDE_M416);
    //UnloadTexture(FPP_M416_TEX_IN_GAME);
    //UnloadTexture(FPP_M416_TEX_SETUP);
    //UnloadTexture(SIDE_M416_TEX_SETUP);

    UnloadImage(FPP_AK47);
    UnloadImage(SIDE_AK47);
    //UnloadTexture(FPP_AK47_TEX_IN_GAME);
    //UnloadTexture(FPP_AK47_TEX_SETUP);
    //UnloadTexture(SIDE_AK47_TEX_SETUP);

    UnloadImage(FPP_AWM);
    UnloadImage(SIDE_AWM);
    //UnloadTexture(FPP_AWM_TEX_IN_GAME);
    //UnloadTexture(FPP_AWM_TEX_SETUP);
    //UnloadTexture(SIDE_AWM_TEX_SETUP);

    UnloadImage(FPP_GLOCK);
    UnloadImage(SIDE_GLOCK);
    //UnloadTexture(FPP_GLOCK_TEX_IN_GAME);
    //UnloadTexture(FPP_GLOCK_TEX_SETUP);
    //UnloadTexture(SIDE_GLOCK_TEX_SETUP);

    return Guns;
}

void DisplayMainMenu( GamePage& gamePage, const Font& BigFont, const Font& MainstreamFont) {
    ShowCursor();

    Vector2 mouse_position = GetMousePosition();

    // PLAY BUTTON COLLISION
    Rectangle play_border_rect = mainMenu.play.rect;
    Rectangle quit_border_rect = mainMenu.quit.rect;
    float play_rect_padding = 0;
    float quit_rect_padding = 0;
    float btn_padding = play_border_rect.height * 0.025F;
    
    if (CheckCollisionPointRec(mouse_position, play_border_rect)) {
        mainMenu.play.color = BUTTON_PLAY_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            play_rect_padding = btn_padding;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamePage = SETUP_MENU;
        }
    }
    else {
        mainMenu.play.color = BUTTON_PLAY_COLOR_BASE;
        play_rect_padding = 0;
    }

    // QUIT BUTTON COLLISION
    if (CheckCollisionPointRec(mouse_position, quit_border_rect)) {
        mainMenu.quit.color = BUTTON_QUIT_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            quit_rect_padding = btn_padding;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            CloseWindow();
        }
    }
    else {
        mainMenu.quit.color = BUTTON_QUIT_COLOR_BASE;
        quit_rect_padding = 0;
    }

    Rectangle play_btn_rect = {
        play_border_rect.x + play_rect_padding,
        play_border_rect.y + play_rect_padding,
        play_border_rect.width - (play_rect_padding * 2),
        play_border_rect.height - (play_rect_padding * 2)
    };
    float play_btn_font_size = play_btn_rect.height * 0.65F;

    Rectangle quit_btn_rect = {
        quit_border_rect.x + quit_rect_padding,
        quit_border_rect.y + quit_rect_padding,
        quit_border_rect.width - (quit_rect_padding * 2),
        quit_border_rect.height - (quit_rect_padding * 2)
    };
    float quit_btn_font_size = quit_btn_rect.height * 0.65F;


    // TITLE TEXT
    Vector2 title_text_measure = MeasureTextEx(BigFont, mainMenu.title, mainMenu.font_size, mainMenu.font_space);
    Vector2 TitleTextPos = {
        (float)game.w / 2 - title_text_measure.x / 2,
        (float)mainMenu.title_Pos_Y
    };
    DrawTextEx(BigFont, mainMenu.title, TitleTextPos, mainMenu.font_size, mainMenu.font_space, WHITE);

    // PLAY BUTTON
    DrawRectangleRounded(play_btn_rect, mainMenu.play.roundness, mainMenu.play.segments, mainMenu.play.color);
    Vector2 play_text_measure = MeasureTextEx(BigFont, mainMenu.play.text, play_btn_font_size, mainMenu.play.font_space);
    Vector2 play_text_coor = {
        (float)mainMenu.play.rect.x + ((mainMenu.play.rect.width - play_text_measure.x) / 2),
        (float)mainMenu.play.rect.y + ((mainMenu.play.rect.height - play_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, mainMenu.play.text, play_text_coor, play_btn_font_size, mainMenu.play.font_space, mainMenu.play.text_color);

    // QUIT BUTTON
    DrawRectangleRounded(quit_btn_rect, mainMenu.quit.roundness, mainMenu.quit.segments, mainMenu.quit.color);
    Vector2 quit_text_measure = MeasureTextEx(BigFont, mainMenu.quit.text, quit_btn_font_size, mainMenu.quit.font_space);
    Vector2 quit_text_coor = {
        (float)mainMenu.quit.rect.x + ((mainMenu.quit.rect.width - quit_text_measure.x) / 2),
        (float)mainMenu.quit.rect.y + ((mainMenu.quit.rect.height - quit_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, mainMenu.quit.text, quit_text_coor, quit_btn_font_size, mainMenu.quit.font_space, mainMenu.quit.text_color);

    // CREDIT TEXT
    Vector2 credit_0_measure = MeasureTextEx(MainstreamFont, mainMenu.credit.at(0), mainMenu.credit_font_size, mainMenu.font_space);
    Vector2 credit_0_coor = {
        (float)game.w / 2 - credit_0_measure.x / 2,
        (float)mainMenu.credit_Pos_Y.at(0)
    };
    DrawTextEx(MainstreamFont, mainMenu.credit.at(0), credit_0_coor, mainMenu.credit_font_size, mainMenu.font_space, mainMenu.credit_color);

    Vector2 credit_1_measure = MeasureTextEx(MainstreamFont, mainMenu.credit.at(1), mainMenu.credit_font_size, mainMenu.font_space);
    Vector2 credit_1_coor = {
        (float)game.w / 2 - credit_1_measure.x / 2,
        (float)mainMenu.credit_Pos_Y.at(1)
    };
    DrawTextEx(MainstreamFont, mainMenu.credit.at(1), credit_1_coor, mainMenu.credit_font_size, mainMenu.font_space, mainMenu.credit_color);
}

void DisplaySetupMenu(
    GamePage& gamePage, 
    std::vector<Gun>& Guns, 
    std::vector<HighScoreEntry>& LeaderboardData, 
    SetupProperties& setupProperties, 
    const Font& BigFont, const Font& MainstreamFont, const Font& NumberFont) {
    
    ShowCursor();

    Vector2 mouse_position = GetMousePosition();

    // GUN BUTTON COLLISION
    if (CheckCollisionPointRec(mouse_position, setupMenu.gun.rect)) {
        setupMenu.gun.color = BUTTON_GUN_COLOR_HOVER;
        setupMenu.gun.text_color = {250, 250, 250, 220};

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            setupProperties = GUN;
        }
    }
    else {
        setupMenu.gun.color = BUTTON_GUN_COLOR_BASE;
        setupMenu.gun.text_color = BLACK;
    }

    // TIME BUTTON COLLISION
    if (CheckCollisionPointRec(mouse_position, setupMenu.time.rect)) {
        setupMenu.time.color = BUTTON_TIME_COLOR_HOVER;
        setupMenu.time.text_color = { 250, 250, 250, 220 };

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            setupProperties = TIME;
        }
    }
    else {
        setupMenu.time.color = BUTTON_TIME_COLOR_BASE;
        setupMenu.time.text_color = BLACK;
    }

    // LEVEL BUTTON COLLISION
    if (CheckCollisionPointRec(mouse_position, setupMenu.level.rect)) {
        setupMenu.level.color = BUTTON_LEVEL_COLOR_HOVER;
        setupMenu.level.text_color = { 250, 250, 250, 220 };

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            setupProperties = LEVEL;
        }
    }
    else {
        setupMenu.level.color = BUTTON_LEVEL_COLOR_BASE;
        setupMenu.level.text_color = BLACK;
    }

    // START BUTTON COLLISION
    Rectangle start_border_rect = setupMenu.start.rect;
    Rectangle back_border_rect = setupMenu.back.rect;
    float start_rect_padding = 0;
    float back_rect_padding = 0;
    float btn_setup_padding = start_border_rect.height * 0.025F;

    if (CheckCollisionPointRec(mouse_position, start_border_rect)) {
        setupMenu.start.color = BUTTON_START_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            start_rect_padding = btn_setup_padding;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamePage = IN_GAME;
            SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
        }
    }
    else {
        setupMenu.start.color = BUTTON_START_COLOR_BASE;
        start_rect_padding = 0;
    }

    // BACK BUTTON COLLISION
    if (CheckCollisionPointRec(mouse_position, back_border_rect)) {
        setupMenu.back.color = BUTTON_BACK_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            back_rect_padding = btn_setup_padding;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamePage = MAIN_MENU;
        }
    }
    else {
        setupMenu.back.color = BUTTON_BACK_COLOR_BASE;
        back_rect_padding = 0;
    }
    
    Rectangle start_btn_rect = {
        start_border_rect.x + start_rect_padding,
        start_border_rect.y + start_rect_padding,
        start_border_rect.width - (start_rect_padding * 2),
        start_border_rect.height - (start_rect_padding * 2)
    };
    float start_btn_font_size = start_btn_rect.height * 0.65F;

    Rectangle back_btn_rect = {
        back_border_rect.x + back_rect_padding,
        back_border_rect.y + back_rect_padding,
        back_border_rect.width - (back_rect_padding * 2),
        back_border_rect.height - (back_rect_padding * 2)
    };
    float back_btn_font_size = back_btn_rect.height * 0.65F;

    // TITLE TEXT
    Vector2 title_text_measure = MeasureTextEx(BigFont, setupMenu.title, setupMenu.title_font_size, setupMenu.font_space);
    Vector2 title_text_coor = {
        (float)game.w / 2 - title_text_measure.x / 2,
        (float)setupMenu.title_Pos_Y
    };
    DrawTextEx(BigFont, setupMenu.title, title_text_coor, setupMenu.title_font_size, setupMenu.font_space, WHITE);

    // CLICKED_BUTTON_EFFECT
    DrawRectangleRounded(setupMenu.clicked_effect_rect, setupMenu.roundness, setupMenu.segments, setupMenu.clicked_effect_color);

    // GUN BUTTON
    DrawRectangleRounded(setupMenu.gun.rect, setupMenu.gun.roundness, setupMenu.gun.segments, setupMenu.gun.color);
    Vector2 gun_text_measure = MeasureTextEx(BigFont, setupMenu.gun.text, setupMenu.gun.font_size, setupMenu.gun.font_space);
    Vector2 gun_text_coor = {
        (float)setupMenu.gun.rect.x + ((setupMenu.gun.rect.width - gun_text_measure.x) / 2),
        (float)setupMenu.gun.rect.y + ((setupMenu.gun.rect.height - gun_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, setupMenu.gun.text, gun_text_coor, setupMenu.gun.font_size, setupMenu.gun.font_space, setupMenu.gun.text_color);

    // TIME BUTTON
    DrawRectangleRounded(setupMenu.time.rect, setupMenu.time.roundness, setupMenu.time.segments, setupMenu.time.color);
    Vector2 time_text_measure = MeasureTextEx(BigFont, setupMenu.time.text, setupMenu.time.font_size, setupMenu.time.font_space);
    Vector2 time_text_coor = {
        (float)setupMenu.time.rect.x + ((setupMenu.time.rect.width - time_text_measure.x) / 2),
        (float)setupMenu.time.rect.y + ((setupMenu.time.rect.height - time_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, setupMenu.time.text, time_text_coor, setupMenu.time.font_size, setupMenu.time.font_space, setupMenu.time.text_color);

    // LEVEL BUTTON
    DrawRectangleRounded(setupMenu.level.rect, setupMenu.level.roundness, setupMenu.level.segments, setupMenu.level.color);
    Vector2 level_text_measure = MeasureTextEx(BigFont, setupMenu.level.text, setupMenu.level.font_size, setupMenu.level.font_space);
    Vector2 level_text_coor = {
        (float)setupMenu.level.rect.x + ((setupMenu.level.rect.width - level_text_measure.x) / 2),
        (float)setupMenu.level.rect.y + ((setupMenu.level.rect.height - level_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, setupMenu.level.text, level_text_coor, setupMenu.level.font_size, setupMenu.level.font_space, setupMenu.level.text_color);

    // BACK BUTTON
    DrawRectangleRounded(back_btn_rect, setupMenu.back.roundness, setupMenu.back.segments, setupMenu.back.color);
    Vector2 back_text_measure = MeasureTextEx(BigFont, setupMenu.back.text, back_btn_font_size, setupMenu.back.font_space);
    Vector2 back_text_coor = {
        (float)setupMenu.back.rect.x + ((setupMenu.back.rect.width - back_text_measure.x) / 2),
        (float)setupMenu.back.rect.y + ((setupMenu.back.rect.height - back_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, setupMenu.back.text, back_text_coor, back_btn_font_size, setupMenu.back.font_space, setupMenu.back.text_color);

    // START BUTTON
    DrawRectangleRounded(start_btn_rect, setupMenu.start.roundness, setupMenu.start.segments, setupMenu.start.color);
    Vector2 start_text_measure = MeasureTextEx(BigFont, setupMenu.start.text, start_btn_font_size, setupMenu.start.font_space);
    Vector2 start_text_coor = {
        (float)setupMenu.start.rect.x + ((setupMenu.start.rect.width - start_text_measure.x) / 2),
        (float)setupMenu.start.rect.y + ((setupMenu.start.rect.height - start_text_measure.y) / 2)
    };
    DrawTextEx(BigFont, setupMenu.start.text, start_text_coor, start_btn_font_size, setupMenu.start.font_space, setupMenu.start.text_color);

    // BASE CANVAS
    DrawRectangleRounded(setupMenu.Base_Canvas_rect, setupMenu.roundness, setupMenu.segments, setupMenu.canvas_color);

    // TEXT PROPERTIES
    double current_time = GetTime();
    float frequency_blinking = 3.0F;
    double sine_value = sin(current_time * 2.0 * PI / frequency_blinking);
    float alpha = (float)(sine_value + 1.0F) / 2.0F;
    Vector2 choose_text_measure = MeasureTextEx(BigFont, setupMenu.choose_text, setupMenu.font_size, setupMenu.font_space);
    Vector2 choose_text_coor = {
        (float)setupMenu.Base_Canvas_rect.x + ((setupMenu.Base_Canvas_rect.width - choose_text_measure.x) / 2),
        (float)818
    };
    DrawTextEx(BigFont, setupMenu.choose_text, choose_text_coor, setupMenu.font_size, setupMenu.font_space, Fade(WHITE, alpha));

    // BASE LEADERBOARDS
    Vector2 leaderboards_text_measure = MeasureTextEx(BigFont, setupMenu.leaderboard_text, setupMenu.font_size, setupMenu.font_space);
    Vector2 leaderboards_text_coor = {
        (float)setupMenu.leaderboards_rect.x + ((setupMenu.leaderboards_rect.width - leaderboards_text_measure.x) / 2),
        (float)212
    };
    DrawTextEx(BigFont, setupMenu.leaderboard_text, leaderboards_text_coor, setupMenu.font_size, setupMenu.font_space, WHITE);
    DrawRectangleRounded(setupMenu.leaderboards_rect, 0.05F, setupMenu.segments, setupMenu.leaderboards_color);

    // DRAW LEADERBOARDS CONTENT & SCROLLING
    size_t data_size = LeaderboardData.size();

    static bool scrollable = true;
    float content_height = (float)setupMenu.leaderboards_rect.height * 0.065F;
    float content_pad_threshold = 0.2F;

    Rectangle content_scissor_rect = {
        (float)setupMenu.leaderboards_rect.x,
        (float)setupMenu.leaderboards_rect.y + (int)(content_height * content_pad_threshold),
        (float)setupMenu.leaderboards_rect.width,
        (float)setupMenu.leaderboards_rect.height - (int)((content_height * content_pad_threshold) * 2)
    };

    float min_content_threshold = content_scissor_rect.y;
    float max_content_threshold = 0;
 
    if ((content_height * data_size) > (float)setupMenu.leaderboards_rect.height) {
        max_content_threshold = min_content_threshold + content_scissor_rect.height - (content_height * data_size);
        scrollable = true;
    }
    else {
        max_content_threshold = min_content_threshold ;
        scrollable = false;
    }
    
    static float content_scroll = min_content_threshold;
    static float content_velocity = 0;
    content_velocity *= 0.95F;

    Rectangle content_boundary = {
        (float)setupMenu.leaderboards_rect.x,
        (float)content_scroll,
        (float)setupMenu.leaderboards_rect.width * 0.930F,
        content_height
    };
    float content_padding = (content_boundary.width * 0.0125F);

    Rectangle scroll_bar_boundary = {
        content_boundary.x + content_boundary.width + ((content_padding * 1.F)),
        content_scissor_rect.y + content_padding,
        -(content_boundary.x + content_boundary.width) + (setupMenu.leaderboards_rect.x + setupMenu.leaderboards_rect.width) - ((content_padding * 1.4F) * 2),
        content_scissor_rect.height - (content_padding * 2)
    };
    DrawRectangleRoundedLines(scroll_bar_boundary, 0.3F, 10, 2.F, MAINCOLOR);


    float scroll_padding = scroll_bar_boundary.width * 0.1F;
    float scroll_top_bot_pad = scroll_bar_boundary.width * 1.1F;

    static float scroll_bar_height_line = 0;
    static float scroll_bar_ratio = 0;
    static float scroll_height = 0;

    float min_scroll_bar_threshold = scroll_bar_boundary.y + scroll_top_bot_pad;
    float max_scroll_bar_threshold = min_scroll_bar_threshold + (scroll_bar_height_line - scroll_height);
    static float scroll_bar = min_scroll_bar_threshold;
    static float scroll_velocity = 0;
    static float scroll_coef = 0.0F;
    scroll_velocity *= 0.95F;

    scroll_bar_height_line = (scroll_bar_boundary.height - (scroll_top_bot_pad * 2));
    float visible_area_height = content_scissor_rect.height;
    scroll_bar_ratio = visible_area_height / (content_height * (data_size - 1));
    scroll_bar_ratio = scroll_bar_ratio * scroll_bar_height_line / visible_area_height;

    if (scrollable) {
        scroll_height = scroll_bar_height_line * scroll_bar_ratio;
        scroll_coef = 7.0F;
    }
    else {
        scroll_height = scroll_bar_height_line;
        scroll_coef = 0.5F;
    }


    if (content_scroll > min_content_threshold) {
        content_scroll = min_content_threshold;
        scroll_bar = min_scroll_bar_threshold;
        scroll_coef = 2.0F;
    } 
    else if (content_scroll < max_content_threshold) {
        content_scroll = max_content_threshold;
        scroll_bar = max_scroll_bar_threshold;
        scroll_coef = 2.0F;
    }

    if (CheckCollisionPointRec(mouse_position, setupMenu.leaderboards_rect)) {
        float scroll_adjustment = GetMouseWheelMove() * content_height * scroll_coef;
        content_velocity += scroll_adjustment;
        scroll_velocity -= scroll_adjustment * scroll_bar_ratio;
    }

    content_scroll += content_velocity * GetFrameTime();
    scroll_bar += scroll_velocity * GetFrameTime();

    static bool print_once = false;
    if (print_once == false) {
        std::cout << "INFO: VISIBLE-AREA: " << visible_area_height << std::endl;
        std::cout << "INFO: RATIO: " << scroll_bar_ratio << std::endl;
        std::cout << "INFO: HEIGHT-LINE: " << scroll_bar_height_line << std::endl;
        std::cout << "INFO: HEIGHT: " << scroll_height << std::endl;
        print_once = true;
    }

    // DRAW SCROLL BAR
    Rectangle scroll_bar_rect = {
        scroll_bar_boundary.x + scroll_padding,
        scroll_bar,
        scroll_bar_boundary.width - (scroll_padding * 2),
        scroll_height
    };
    DrawRectangleRounded(scroll_bar_rect, 0.5F, 10, MAINCOLOR);

    // DRAW SCROLL BAR ACCENT
    float scroll_accent_width = scroll_bar_rect.width * 0.9F;
    float scroll_accent_height = scroll_accent_width;
    Rectangle scroll_bar_accent = {
        scroll_bar_rect.x + (scroll_bar_rect.width * 0.05F),
        scroll_bar_rect.y + (scroll_bar_rect.height - scroll_accent_height) / 2,
        scroll_accent_width,
        scroll_accent_height
    };
    {
        Rectangle dest = scroll_bar_accent;
        Rectangle source = { 0, 0, 100, 100 };
        DrawTexturePro(SCROLL_BAR_TEX, source, dest, { 0,0 }, 0, setupMenu.leaderboards_color);
    }

    // BUTTON SCROLL
    static Color Scroll_TEX_Color = GRAY;
    static Rectangle scroll_icon_source = {};

    float btn_clicked = scroll_bar_boundary.width * 0.1F;
    float btn_not_clicked = 0.0F;
    float btn_scroll_padding = 0;
    Rectangle top_btn_dest = {
        scroll_bar_boundary.x,
        scroll_bar_boundary.y,
        scroll_bar_boundary.width,
        scroll_top_bot_pad
    };
    Rectangle bot_btn_dest = {
        scroll_bar_boundary.x,
        scroll_bar_boundary.y + scroll_bar_boundary.height - scroll_top_bot_pad * 1,
        scroll_bar_boundary.width,
        scroll_top_bot_pad
    };

    if (CheckCollisionPointRec(mouse_position, top_btn_dest)) {
        Scroll_TEX_Color = DARKGRAY;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scroll_velocity -= content_height * (scroll_coef * scroll_bar_ratio) * 2;
            content_velocity += content_height * scroll_coef * 2;

            btn_scroll_padding = btn_clicked;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            scroll_velocity -= content_height * (scroll_coef * scroll_bar_ratio) * 0.1F;
            content_velocity += content_height * scroll_coef * 0.1F;

            btn_scroll_padding = btn_clicked;
        }
        else {
            btn_scroll_padding = btn_not_clicked;
        }
    }
    else {
        Scroll_TEX_Color = MAINCOLOR;
    }
    {
        Rectangle top_btn_dest = {
        scroll_bar_boundary.x + btn_scroll_padding,
        scroll_bar_boundary.y + btn_scroll_padding,
        scroll_bar_boundary.width - (btn_scroll_padding * 2),
        scroll_top_bot_pad - (btn_scroll_padding * 2)
        };
        scroll_icon_source = { (0 * 100), 0, 100, 100 };
        DrawTexturePro(SCROLL_UP_DOWN_TEX, scroll_icon_source, top_btn_dest, { 0,0 }, 0, Scroll_TEX_Color);
        btn_scroll_padding = btn_not_clicked;
    }

    if (CheckCollisionPointRec(mouse_position, bot_btn_dest)) {
        Scroll_TEX_Color = DARKGRAY;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scroll_velocity += content_height * (scroll_coef * scroll_bar_ratio) * 2;
            content_velocity -= content_height * scroll_coef * 2;

            btn_scroll_padding = btn_clicked;
        } 
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            scroll_velocity += content_height * (scroll_coef * scroll_bar_ratio) * 0.1F;
            content_velocity -= content_height * scroll_coef * 0.1F;

            btn_scroll_padding = btn_clicked;
        }
        else {
            btn_scroll_padding = btn_not_clicked;
        }
    }
    else {
        Scroll_TEX_Color = MAINCOLOR;
    }
    {
        Rectangle bot_btn_dest = {
        scroll_bar_boundary.x + btn_scroll_padding,
        scroll_bar_boundary.y + scroll_bar_boundary.height - scroll_top_bot_pad * 1 + btn_scroll_padding,
        scroll_bar_boundary.width - (btn_scroll_padding * 2),
        scroll_top_bot_pad - (btn_scroll_padding * 2)
        };
        scroll_icon_source = { (1 * 100), 0, 100, 100 };
        DrawTexturePro(SCROLL_UP_DOWN_TEX, scroll_icon_source, bot_btn_dest, { 0,0 }, 0, Scroll_TEX_Color);
    }

    
    BeginScissorMode(
        static_cast<int>(content_scissor_rect.x),
        static_cast<int>(content_scissor_rect.y),
        static_cast<int>(content_scissor_rect.width),
        static_cast<int>(content_scissor_rect.height)
    );

    for (size_t i = 0; i < data_size; i++) {
        Color content_color{ RAYWHITE };
        Color font_color{ BLACK };

        Rectangle content = {
            content_boundary.x + (content_padding * 2),
            (content_boundary.y + content_padding) + (i * content_height),
            content_boundary.width - (content_padding * 3),
            content_boundary.height - (content_padding * 2)
        };

        if (CheckCollisionPointRec(mouse_position, content_scissor_rect)) {

            if (CheckCollisionPointRec(mouse_position, content) && is_content_popup_opens[i] == false) {
                content_color = Fade(gunCard.color, 0.8F);
                font_color = RAYWHITE;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    // OPEN AND RESET CONTENT POPUP INDEX
                    is_content_popup_opens.assign(LeaderboardData.size(), false);
                    is_content_popup_opens[i] = true;
                    PopupCooldownStart();
                }
            }
            else {
                content_color = RAYWHITE;
                font_color = BLACK;
            }
        }


        // CHECK FIGHT ACTIVE
        IsPopopCooldownActive();
        

        if (is_content_popup_opens[i] == true) {
            content_color = Fade(RED, 0.9F);
            font_color = RAYWHITE;
        }

        {
            // DRAW CONTENT BASE
            //DrawRectangleRec(content, content_color);
            DrawRectangleRounded(content, 0.2F, 10, content_color);

            // DRAW LINE BETWEEN CONTENT ONLY
            if (i != data_size - 1) {
                float line_pad = 7.F;
                Rectangle line_rect = {
                    content.x + line_pad,
                    content.y + content.height + (content_padding * 0.8F),
                    content.width - (line_pad * 2),
                    content_padding / 2
                };
                DrawRectangleRec(line_rect, RAYWHITE);
            }

        }

        // DRAW CONTENT-NUMBER
        float font_size = 24;
        std::string number = "";
        if (i < 9) {
            number = "0" + std::to_string(i + 1);
        }
        else {
            number = std::to_string(i + 1);
        }
        Vector2 number_text_measure = MeasureTextEx(NumberFont, number.c_str(), font_size, 0);
        Vector2 number_text_coor = {
            content.x + 7,
            content.y + (content.height - number_text_measure.y) / 2 - 1.5F
        };
        DrawTextEx(NumberFont, number.c_str(), number_text_coor, font_size, 0, font_color);


        // DRAW CONTENT-DATA
        font_size = 20;
        std::string score = std::to_string(LeaderboardData[i].score);
        std::string date = LeaderboardData[i].date;
        std::string time = LeaderboardData[i].getTimeFormatted();
        std::string level = LeaderboardData[i].level;
        std::string weapon = LeaderboardData[i].weapon;

        //std::string combinedString = score + " - " + date + " - " + time + " - " + level + " - " + weapon;
        //const char* content_text = TextFormat(combinedString.c_str());
        //Vector2 content_text_measure = MeasureTextEx(font, content_text, font_size, 0);
        //Vector2 content_text_coor = {
        //    content.x + (content.width * 0.1F),
        //    content.y + (content.height - content_text_measure.y) / 2
        //};
        //DrawTextEx(font, content_text, content_text_coor, font_size, 0, font_color);

        float space_rect = content.height * 0.225F;
        Rectangle score_rect = {
            content.x + (content.width * 0.100F),
            content.y,
            content.width * 0.125F,
            content.height
        };

        Rectangle date_rect = {
            score_rect.x + score_rect.width + space_rect,
            score_rect.y,
            content.width * 0.260F,
            score_rect.height
        };

        Rectangle time_rect = {
            date_rect.x + date_rect.width + space_rect,
            score_rect.y,
            content.width * 0.1390F,
            score_rect.height
        };

        Rectangle level_rect = {
            time_rect.x + time_rect.width + space_rect,
            score_rect.y,
            content.width * 0.1390F,
            score_rect.height
        };

        Rectangle weapon_rect = {
            level_rect.x + level_rect.width + space_rect,
            score_rect.y,
            content.width * 0.1400F,
            score_rect.height
        };

        std::vector<std::string> content_text{};
        std::vector<Rectangle> content_rect{};

        // POP UP
        if (is_content_popup_opens[i] == false) {
            content_text = { score, date, time, level, weapon };
            content_rect = { score_rect, date_rect, time_rect, level_rect, weapon_rect };
        }

        if (is_content_popup_opens[i] == true) {
            time_rect.x = date_rect.x - (space_rect * 0.0F);
            level_rect.x = time_rect.x + time_rect.width;
            weapon_rect.x = level_rect.x + level_rect.width;

            content_text = { score, time, level, weapon };
            content_rect = { score_rect, time_rect, level_rect, weapon_rect };

            font_color = RAYWHITE;
            float popUp_width = content.width * 0.305F;

            // DRAW POPUP
            Color popUp_color = MAINCOLOR;
            Rectangle popUp_rect = {
                content.x + content.width - popUp_width,
                content.y,
                popUp_width,
                content.height
            };
            DrawRectangleRounded(popUp_rect, 0.25F, 10, popUp_color);
            //DrawRectangleRec(popUp_rect, popUp_color);

            // popUp - btn FIGHT
            Color border_color = RAYWHITE;
            Color fight_btn_color = timeCard.btn_120.color;
            Color close_btn_color = RED;
            Color fight_text_color = BLACK;
            Color close_icon_color = {};
            float fight_alpha = 0.0F;
            float close_alpha = 0.0F;
            float border_padding = popUp_rect.height * 0.1F;
            float roundness = 0.3F;
            int segments = 10;
            float btn_pad_clicked = border_padding * 0.8F;
            float btn_pad_unclicked = border_padding * 0.4F;
            static float btn_padding = btn_pad_unclicked;

            Rectangle fight_border_rect = {
                popUp_rect.x + (border_padding * 4),
                popUp_rect.y + border_padding,
                popUp_rect.width * 0.75F - (border_padding * 5),
                popUp_rect.height - (border_padding * 2)
            };
            DrawRectangleRounded(fight_border_rect, roundness, segments, border_color);

            // popUp - btn CLOSE
            Rectangle close_border_rect = {
                fight_border_rect.x + fight_border_rect.width + (border_padding),
                fight_border_rect.y,
                popUp_rect.width * 0.25F - (border_padding),
                fight_border_rect.height
            };
            DrawRectangleRounded(close_border_rect, roundness, segments, border_color);

            // FIGHT BUTTON CLICK
            if (CheckCollisionPointRec(mouse_position, fight_border_rect)) {
                fight_text_color = BLACK;
                fight_alpha = 1.0F;

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    btn_padding = btn_pad_clicked;
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && popup_cooldown_active == false) {
                    // FIGHT THE CHOOSEN LEADERBOARDS
                    time_choice = LeaderboardData[i].time;
                    level_choice = LeaderboardData[i].getLevelFormatted(LeaderboardData[i].level);
                    weapon_choice = LeaderboardData[i].getWeaponFormatted(LeaderboardData[i].weapon);
                    weapon_color = LeaderboardData[i].color;
                    gamePage = IN_GAME;
                }
            }
            else {
                fight_text_color = BLACK;
                fight_alpha = 0.5F;
                btn_padding = btn_pad_unclicked;
            }
            
            Rectangle fight_btn_rect = {
                fight_border_rect.x + btn_padding,
                fight_border_rect.y + btn_padding,
                fight_border_rect.width - (btn_padding * 2),
                fight_border_rect.height - (btn_padding * 2)
            };

            // CLOSE BUTTON CLICK
            if (CheckCollisionPointRec(mouse_position, close_border_rect) && popup_cooldown_active == false) {
                close_icon_color = RAYWHITE;
                close_alpha = 1.0F;

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    btn_padding = btn_pad_clicked;
                }

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    // CLOSE POPUP
                    is_content_popup_opens[i] = false;
                }
            }
            else {
                close_icon_color = RAYWHITE;
                close_alpha = 0.5F;
                btn_padding = btn_pad_unclicked;
            }

            Rectangle close_btn_rect = {
                close_border_rect.x + btn_padding,
                close_border_rect.y + btn_padding,
                close_border_rect.width - (btn_padding * 2),
                close_border_rect.height - (btn_padding * 2)
            };


            DrawRectangleRounded(fight_btn_rect, roundness, segments, Fade(fight_btn_color, fight_alpha));
            const char* fight_text = "FIGHT";
            float fight_font_size = fight_btn_rect.height * 0.8F;
            Vector2 fight_text_measure = MeasureTextEx(MainstreamFont, fight_text, fight_font_size, 0);
            Vector2 fight_text_coor = {
                fight_border_rect.x + ((fight_border_rect.width - fight_text_measure.x) / 2),
                fight_border_rect.y + ((fight_border_rect.height - fight_text_measure.y) / 2),
            };
            DrawTextEx(MainstreamFont, fight_text, fight_text_coor, fight_font_size, 0, fight_text_color);

            DrawRectangleRounded(close_btn_rect, roundness, segments, Fade(close_btn_color, close_alpha));
            float vertical_pad = btn_padding;
            float horizontal_pad = vertical_pad * 1.25F;
            float icon_index = 0;
            float icon_size = 40;
            Rectangle dest = {
                close_btn_rect.x + horizontal_pad,
                close_btn_rect.y + vertical_pad,
                close_btn_rect.width - (horizontal_pad * 2),
                close_btn_rect.height - (vertical_pad * 2)
            };
            Rectangle source = { icon_size * icon_index, 0, icon_size, icon_size };
            DrawTexturePro(CLOSE_FIGHT_TEX, source, dest, { 0,0 }, 0, close_icon_color);
        }

        for (size_t j = 0; j < content_text.size(); j++) {
            const char* text = content_text[j].c_str();
            Vector2 text_measure = MeasureTextEx(MainstreamFont, text, font_size, 0);
            Vector2 text_coor = {
                content_rect[j].x + ((content_rect[j].width - text_measure.x) / 2),
                content_rect[j].y + ((content_rect[j].height - text_measure.y) / 2)
            };
            //DrawRectangleRec(content_rect[j], LIGHTGRAY);
            DrawTextEx(MainstreamFont, text, text_coor, font_size, 0, font_color);
        }

    }

    EndScissorMode();


    switch (setupProperties)
    {
    case GUN:
        //
        GunCardDisplay(Guns, mouse_position ,BigFont);
        break;

    case TIME:
        //
        TimeCardDisplay(mouse_position, MediumFont);
        break;

    case LEVEL:
        // 
        LevelCardDisplay(mouse_position, BigFont);
        break;

    default:
        break;
    }

    time_start_called = false;
}

void IsPopopCooldownActive()
{
    if (popup_cooldown_active) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - popup_fight_timer_start).count();

        if (elapsed_time > 1) {
            popup_cooldown_active = false;
        }
        else {
            popup_cooldown_active = true;
        }
    }
}

void PopupCooldownStart()
{
    popup_cooldown_active = true;
    popup_fight_timer_start = std::chrono::steady_clock::now();
}


void GunCardDisplay(std::vector<Gun>& Guns, Vector2& mouse_position, const Font& font)
{
    setupMenu.canvas_color = BUTTON_GUN_COLOR_BASE;
    setupMenu.clicked_effect_rect.x = setupMenu.gun.rect.x;


    // BUTTON PREV GUN
    Rectangle prev_rect = gunCard.prev.rect;
    Rectangle next_rect = gunCard.next.rect;

    float prev_vertical_pad = 2.F;
    float next_vertical_pad = 2.F;

    if (CheckCollisionPointRec(mouse_position, prev_rect)) {
        gunCard.prev.color = GUN_CARD_BUTTON_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            prev_vertical_pad = 4.F;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (weapon_choice == 0) {
                weapon_choice = Guns.size() - 1;
            }
            else {
                weapon_choice--;
            }
        }
    }
    else {
        gunCard.prev.color = GUN_CARD_BUTTON_COLOR_BASE;
        prev_vertical_pad = 2.F;
    }
    // BUTTON NEXT GUN
    if (CheckCollisionPointRec(mouse_position, next_rect)) {
        gunCard.next.color = GUN_CARD_BUTTON_COLOR_HOVER;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            next_vertical_pad = 4.F;
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (weapon_choice == Guns.size() - 1) {
                weapon_choice = 0;
            }
            else {
                weapon_choice++;
            }
        }
    }
    else {
        gunCard.next.color = GUN_CARD_BUTTON_COLOR_BASE;
        next_vertical_pad = 2.F;
    }

    // BASE CARD
    DrawRectangleRounded(gunCard.rect, gunCard.roundness, gunCard.segments, gunCard.color);

    // MINI CARD POV
    {
        // DRAW POV BASE RECT
        DrawRectangleRounded(gunCard.pov.rect, gunCard.pov.roundness, gunCard.pov.segments, gunCard.pov.color);
        DrawRectangleRounded(gunCard.pov.title_rect, gunCard.roundness, gunCard.segments, gunCard.pov.title_color);
        Vector2 pov_text_measure = MeasureTextEx(font, gunCard.pov.text, gunCard.pov.font_size, gunCard.pov.font_space);
        Vector2 pov_text_coor = {
            (float)gunCard.pov.title_rect.x + ((gunCard.pov.title_rect.width - pov_text_measure.x) / 2),
            (float)gunCard.pov.title_rect.y + ((gunCard.pov.title_rect.height - pov_text_measure.y) / 2)
        };
        DrawTextEx(font, gunCard.pov.text, pov_text_coor, gunCard.pov.font_size, gunCard.pov.font_space, gunCard.pov.text_color);

        // DRAW POV GUN
        Rectangle dest = {
            gunCard.pov.rect
        };
        Rectangle source = { 150 + (float)(weapon_color * 480), 0, gunCard.pov.rect.width, gunCard.pov.rect.height };
        DrawTexturePro(Guns.at(weapon_choice).FPP, source, dest, Vector2{ 0,0 }, 0, WHITE);
    }


    // GUN PREVIEW SECTION
    {

        // DRAW GUN NAME
        Rectangle gun_title_rect = {
            gunCard.rect.x + (gunCard.rect.width - gunCard.pov.title_rect.width) / 2,
            gunCard.pov.title_rect.y,
            gunCard.pov.title_rect.width,
            gunCard.pov.title_rect.height
        };
        DrawRectangleRounded(gun_title_rect, gunCard.roundness, gunCard.segments, gunCard.pov.title_color);
        Vector2 gun_text_measure = MeasureTextEx(font, Guns.at(weapon_choice).name, gunCard.stats.font_size, gunCard.stats.font_space);
        Vector2 gun_text_coor = {
            (float)gun_title_rect.x + ((gun_title_rect.width - gun_text_measure.x) / 2),
            (float)gun_title_rect.y + ((gun_title_rect.height - gun_text_measure.y) / 2)
        };
        DrawTextEx(font, Guns.at(weapon_choice).name, gun_text_coor, gunCard.pov.font_size, gunCard.pov.font_space, gunCard.pov.text_color);

        // DRAW GUN PREVIEW
        float source_width = (float)Guns.at(weapon_choice).SIDE.width / 4;
        float source_height = (float)Guns.at(weapon_choice).SIDE.height;
        Rectangle dest = {
            gunCard.rect.x + gunCard.rect.width / 2 - source_width / 2,
            390.F,
            source_width,
            source_height
        };
        Rectangle source = { weapon_color * source_width, 0, source_width, source_height };
        DrawTexturePro(Guns.at(weapon_choice).SIDE, source, dest, Vector2{ 0,0 }, 0, WHITE);
    }

    // COLOR TEXT
    Vector2 color_text_measure = MeasureTextEx(MainstreamFont, gunCard.text_color, gunCard.color_font_size, gunCard.font_space);
    Vector2 color_text_coor = {
        (float)gunCard.rect.x + ((gunCard.rect.width - color_text_measure.x) / 2),
        (float)gunCard.rect.y + (float)(gunCard.rect.height / 2.9F) * 2
    };
    DrawTextEx(MainstreamFont, gunCard.text_color, color_text_coor, gunCard.color_font_size, gunCard.font_space, gunCard.font_color);

    // COLOR BUTTON
    {
        // DRAW BASE COLOR BUTTON
        DrawRectangleRounded(gunCard.BASE.rect, gunCard.roundness, gunCard.segments, gunCard.BASE.color);
        
        Rectangle clicked_effect_rect{
            gunCard.BASE.rect.x + (weapon_color * 60),
            gunCard.BASE.rect.y,
            gunCard.STOCK.rect.width + 4,
            gunCard.BASE.rect.height + 4
        };
        // DRAW CLICKED EFFECT COLOR BUTTON
        DrawRectangleRounded(clicked_effect_rect, gunCard.roundness, gunCard.segments, gunCard.BASE.color);
    }

    std::vector<GunCard::ColorButton> gunsColor = gunCard.GunsColor;
    for (size_t i = 0; i < gunCard.GunsColor.size(); i++) {
        if (CheckCollisionPointRec(mouse_position, gunsColor[i].rect)) {
            gunsColor[i].color = gunBtnColorHover[i][1];

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                weapon_color = i;
            }
        }
        else {
            gunsColor[i].color = gunBtnColorHover[i][0];
        }

        if (weapon_color == i) {
            gunsColor[i].rect.height = gunCard.color_height_clicked;
        }
        else {
            gunsColor[i].rect.height = gunCard.color_height_base;
        }
        DrawRectangleRounded(gunsColor[i].rect, gunCard.roundness, gunCard.segments, gunsColor[i].color);
    }


    // MINI CARD STATS
    {
        DrawRectangleRounded(gunCard.stats.rect, gunCard.stats.roundness, gunCard.stats.segments, gunCard.stats.color);
        DrawRectangleRounded(gunCard.stats.title_rect, gunCard.roundness, gunCard.segments, gunCard.stats.title_color);
        Vector2 stats_text_measure = MeasureTextEx(font, gunCard.stats.text, gunCard.stats.font_size, gunCard.stats.font_space);
        Vector2 stats_text_coor = {
            (float)gunCard.stats.title_rect.x + ((gunCard.stats.title_rect.width - stats_text_measure.x) / 2),
            (float)gunCard.stats.title_rect.y + ((gunCard.stats.title_rect.height - stats_text_measure.y) / 2)
        };
        DrawTextEx(font, gunCard.stats.text, stats_text_coor, gunCard.stats.font_size, gunCard.stats.font_space, gunCard.stats.text_color);

        // TEXT TYPE
        Vector2 type_text_measure = MeasureTextEx(MainstreamFont, gunCard.text_type, gunCard.stats_font_size, gunCard.stats.font_space);
        Vector2 type_text_coor = {
            (float)gunCard.stats.rect.x + ((gunCard.stats.rect.width - type_text_measure.x) / 2),
            (float)gunCard.text_type_y
        };
        DrawTextEx(MainstreamFont, gunCard.text_type, type_text_coor, gunCard.stats_font_size, gunCard.font_space, gunCard.font_color);

        // BASE STATS BAR
        for (auto& stats : gunCard.stats_base) {
            // DRAW BASE BAR STATS
            Rectangle rect = {
                (float)gunCard.stats.rect.x + (gunCard.stats.rect.width - gunCard.bar_width) / 2,
                (float)stats.bar_coor_y,
                (float)gunCard.bar_width,
                (float)gunCard.bar_heigth 
            };
            DrawRectangleRounded(rect, gunCard.roundness, gunCard.segments, gunCard.base_bar_color);

            Vector2 text_measure = MeasureTextEx(MainstreamFont, stats.text, gunCard.stats_font_size, gunCard.font_space);
            Vector2 text_coor = {
                rect.x,
                stats.bar_coor_y - gunCard.text_to_bar_space_y,
            };
            DrawTextEx(MainstreamFont, stats.text, text_coor, gunCard.stats_font_size, gunCard.font_space, gunCard.font_color);
        }

        // STATS GUN
        {
            // TYPE
            Vector2 type_measure = MeasureTextEx(MainstreamFont, Guns.at(weapon_choice).type, gunCard.stats_font_size, gunCard.font_space);
            Vector2 type_coor = {
                (float)gunCard.stats.rect.x + ((gunCard.stats.rect.width - type_measure.x) / 2),
                (float)gunCard.type_gun_y_coor
            };
            DrawTextEx(MainstreamFont, Guns.at(weapon_choice).type, type_coor, gunCard.stats_font_size, gunCard.font_space, gunCard.font_color);

            // STATS BAR
            int speed = 0;
            Rectangle speed_rect = {
                (float)gunCard.stats.rect.x + (gunCard.stats.rect.width - gunCard.bar_width) / 2,
                (float)gunCard.stats_base.at(speed).bar_coor_y,
                Guns.at(weapon_choice).speed_display(),
                (float)gunCard.bar_heigth
            };
            DrawRectangleRounded(speed_rect, gunCard.roundness, gunCard.segments, gunCard.stats_base.at(speed).color);
            
            int power = 1;
            Rectangle power_rect = {
                (float)gunCard.stats.rect.x + (gunCard.stats.rect.width - gunCard.bar_width) / 2,
                (float)gunCard.stats_base.at(power).bar_coor_y,
                Guns.at(weapon_choice).power_display(),
                (float)gunCard.bar_heigth
            };
            DrawRectangleRounded(power_rect, gunCard.roundness, gunCard.segments, gunCard.stats_base.at(power).color);

            int capacity = 2;
            Rectangle capacity_rect = {
                (float)gunCard.stats.rect.x + (gunCard.stats.rect.width - gunCard.bar_width) / 2,
                (float)gunCard.stats_base.at(capacity).bar_coor_y,
                Guns.at(weapon_choice).capacity_display(),
                (float)gunCard.bar_heigth
            };
            DrawRectangleRounded(capacity_rect, gunCard.roundness, gunCard.segments, gunCard.stats_base.at(capacity).color);

        }
        
    }


    // BUTTON PREV ARROW
    {
        DrawRectangleRounded(gunCard.prev.rect, gunCard.prev.roundness, gunCard.prev.segments, gunCard.prev.color);
        float icon_index = 0;
        float icon_size = 300;
        Rectangle dest = {
            gunCard.prev.rect.x + gunCard.prev.rect.width / 2 - (gunCard.prev.rect.height - prev_vertical_pad) / 2,
            gunCard.prev.rect.y + prev_vertical_pad,
            gunCard.prev.rect.height - (prev_vertical_pad * 2),
            gunCard.prev.rect.height - (prev_vertical_pad * 2)
        };

        //Rectangle dest = prev_icon_rect;
        Rectangle source = { icon_size * icon_index, 0, icon_size, icon_size };
        DrawTexturePro(ARROW_TEX, source, dest, { 0,0 }, 0, gunCard.prev.texture_color);
    }
    // BUTTON NEXT ARROW
    {
        DrawRectangleRounded(gunCard.next.rect, gunCard.next.roundness, gunCard.next.segments, gunCard.next.color);
        float icon_index = 1;
        float icon_size = 300;
        Rectangle dest = {
            gunCard.next.rect.x + gunCard.next.rect.width / 2 - (gunCard.next.rect.height - next_vertical_pad) / 2,
            gunCard.next.rect.y + next_vertical_pad,
            gunCard.next.rect.height - (next_vertical_pad * 2),
            gunCard.next.rect.height - (next_vertical_pad * 2)
        };
        Rectangle source = { icon_size * icon_index, 0, icon_size, icon_size };
        DrawTexturePro(ARROW_TEX, source, dest, { 0,0 }, 0, gunCard.next.texture_color);
    }
}

void TimeCardDisplay(Vector2& mouse_position, const Font& font)
{
    setupMenu.canvas_color = BUTTON_TIME_COLOR_BASE;
    setupMenu.clicked_effect_rect.x = setupMenu.time.rect.x;

    // DRAW BASE RECT
    float base_offset = setupMenu.Base_Canvas_rect.height * 0.05F;
    Rectangle base_rect{
        setupMenu.Base_Canvas_rect.x + (setupMenu.Base_Canvas_rect.width - timeCard.width) / 2,
        setupMenu.Base_Canvas_rect.y + (setupMenu.Base_Canvas_rect.height - timeCard.height) / 2 - base_offset,
        timeCard.width,
        timeCard.height
    };
    DrawRectangleRounded(base_rect, timeCard.roundness, timeCard.segments, timeCard.color);

    // SECONDS TEXT
    Rectangle seconds_text_rect = {
        base_rect.x,
        //setupMenu.Base_Canvas_rect.y + setupMenu.Base_Canvas_rect.height + 5,
        base_rect.y + base_rect.height - 10,
        base_rect.width,
        //base_rect.y - setupMenu.Base_Canvas_rect.y + 5,
        (setupMenu.Base_Canvas_rect.y + setupMenu.Base_Canvas_rect.height) - (base_rect.y + base_rect.height) - 0
    };
    
    float seconds_font_size = seconds_text_rect.height * 0.375F;
    float seconds_font_space = 1;
    const char* seconds_text = "SECONDS";
    Vector2 seconds_text_measure = MeasureTextEx(font, seconds_text, seconds_font_size, seconds_font_space);
    Vector2 seconds_text_coor = {
        seconds_text_rect.x + ((seconds_text_rect.width - seconds_text_measure.x) / 2),
        seconds_text_rect.y + ((seconds_text_rect.height - seconds_text_measure.y) / 2)
    };
    DrawTextEx(font, seconds_text, seconds_text_coor, seconds_font_size, seconds_font_space, BLACK);

    // BUTTON 120 SECONDS
    float line_thick{ 5.F };
    Rectangle btn_120_rect{
        (base_rect.x + 2),
        (base_rect.y + 2),
        timeCard.btn_120.rect.width,
        timeCard.btn_120.rect.height
    };
    
    // BUTTON 90 SECONDS
    Rectangle btn_90_rect{
        (base_rect.x + 1 + (base_rect.width / 2)),
        (base_rect.y + 2),
        timeCard.btn_90.rect.width,
        timeCard.btn_90.rect.height
    };

    // BUTTON 60 SECONDS
    Rectangle btn_60_rect{
        (base_rect.x + 2),
        (base_rect.y + 1 + (base_rect.height / 2)),
        timeCard.btn_60.rect.width,
        timeCard.btn_60.rect.height
    };

    // BUTTON 30 SECONDS
    Rectangle btn_30_rect{
        (base_rect.x + 1 + (base_rect.width / 2)),
        (base_rect.y + 1 + (base_rect.height / 2)),
        timeCard.btn_30.rect.width,
        timeCard.btn_30.rect.height
    };

    // DRAW BUTTONS
    std::vector<Rectangle> buttons_rect{ btn_120_rect, btn_90_rect, btn_60_rect, btn_30_rect };

    for (size_t i = 0; i < buttons_rect.size(); i++) {
        TimeCard::Button button = timeCard.timeButtons[i];

        DrawRectangleRounded(buttons_rect[i], button.roundness, button.segments, button.color);

        std::string time_string = std::to_string(button.time);
        const char* time = time_string.c_str();
        const char* points = button.text_points;

        Vector2 time_measure = MeasureTextEx(font, time, button.font_size, button.font_space);
        Vector2 time_coor = {
            buttons_rect[i].x + (buttons_rect[i].width - time_measure.x) / 2,
            buttons_rect[i].y + (buttons_rect[i].height / 4.5F)
        };
        DrawTextEx(font, time, time_coor, button.font_size, button.font_space, button.text_color);

        Vector2 points_measure = MeasureTextEx(font, points, button.font_size_points , button.font_space);
        Vector2 points_coor = {
            buttons_rect[i].x + (buttons_rect[i].width - points_measure.x) / 2,
            buttons_rect[i].y + (buttons_rect[i].height / 1.8F)
        };
        DrawTextEx(font, points, points_coor, button.font_size_points, button.font_space, button.text_color);
        
    }
    
    btnTimeHoverClikcked(mouse_position, btn_clicked, btn_hover, btn_120_rect, btn_90_rect, btn_60_rect, btn_30_rect, line_thick);

    // DRAW HOVER TIME BUTTON
    if (btn_hover.x != 0) {
        float line_smaller{ 2 };
        DrawRectangleRoundedLines
        (
            {
                btn_hover.x - line_smaller,
                btn_hover.y - line_smaller,
                timeCard.width / 2 - ((line_thick - line_smaller) * 2),
                timeCard.height / 2 - ((line_thick - line_smaller) * 2)
            },
            0.F,
            10,
            line_thick - line_smaller,
            timeCard.color_hover
        );
    }

    // DRAW CLICKED TIME BUTTON
    DrawRectangleRoundedLines
    (
        {
            btn_clicked.x,
            btn_clicked.y,
            timeCard.width / 2 - (line_thick * 2),
            timeCard.height / 2 - (line_thick * 2)
        },
        0.F,
        10,
        line_thick,
        timeCard.color_clicked
    );
}


void btnTimeHoverClikcked
(
    Vector2& mouse_position, Vector2& btn_clicked, Vector2& btn_hover,
    Rectangle& btn_120_rect,   
    Rectangle& btn_90_rect, 
    Rectangle& btn_60_rect, 
    Rectangle& btn_30_rect,
    float& line_thick
)
{
    Vector2 btn_120_hover = {
            (btn_120_rect.x - 2) + line_thick,
            (btn_120_rect.y - 2) + line_thick
    };
    Vector2 btn_90_hover = {
           (btn_90_rect.x - 1) + line_thick,
           (btn_90_rect.y - 2) + line_thick
    };
    Vector2 btn_60_hover = {
            (btn_60_rect.x - 2) + line_thick,
            (btn_60_rect.y - 1) + line_thick
    };
    Vector2 btn_30_hover = {
            (btn_30_rect.x - 1) + line_thick,
            (btn_30_rect.y - 1) + line_thick
    };
    std::vector<Vector2> btns_TIME_hover{ btn_120_hover, btn_90_hover, btn_60_hover, btn_30_hover };

    //TimeCard::Button button = timeCard.timeButtons[time_choice];

    if (CheckCollisionPointRec(mouse_position, btn_120_rect)) {
        btn_hover = btns_TIME_hover[0];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            time_choice = SECONDS_120;
        }
    }
    else if (CheckCollisionPointRec(mouse_position, btn_90_rect)) {
        btn_hover = btns_TIME_hover[1];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            time_choice = SECONDS_90;
        }
    }
    else if (CheckCollisionPointRec(mouse_position, btn_60_rect)) {
        btn_hover = btns_TIME_hover[2];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            time_choice = SECONDS_60;
        }
    }
    else if (CheckCollisionPointRec(mouse_position, btn_30_rect)) {
        btn_hover = btns_TIME_hover[3];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            time_choice = SECONDS_30;
        }
    }
    else {
        btn_hover = {};
    }

    switch (time_choice)
    {
    case SECONDS_120:
        btn_clicked = btns_TIME_hover[0];
        break;
    case SECONDS_90:
        btn_clicked = btns_TIME_hover[1];
        break;
    case SECONDS_60:
        btn_clicked = btns_TIME_hover[2];
        break;
    case SECONDS_30:
        btn_clicked = btns_TIME_hover[3];
        break;
    default:
        break;
    }
}


void LevelCardDisplay(Vector2& mouse_position, const Font& font)
{
    setupMenu.canvas_color = BUTTON_LEVEL_COLOR_BASE;
    setupMenu.clicked_effect_rect.x = setupMenu.level.rect.x;

    // DRAW BASE RECT
    float base_offset = setupMenu.Base_Canvas_rect.height * 0.05F;
    Rectangle base_rect{
        setupMenu.Base_Canvas_rect.x + (setupMenu.Base_Canvas_rect.width - levelCard.width) / 2,
        setupMenu.Base_Canvas_rect.y + (setupMenu.Base_Canvas_rect.height - levelCard.height) / 2 + base_offset,
        levelCard.width,
        levelCard.height
    };
    DrawRectangleRounded(base_rect, levelCard.roundness, levelCard.segments, levelCard.color);

    // TARGET SIZE TEXT
    Rectangle target_text_rect = {
        base_rect.x,
        setupMenu.Base_Canvas_rect.y + 10,
        base_rect.width,
        base_rect.y - setupMenu.Base_Canvas_rect.y + 0,
    };

    float target_text_font_size = target_text_rect.height * 0.375F;
    float target_text_font_space = 1;
    const char* target_text = "TARGET SIZE";
    Vector2 target_text_measure = MeasureTextEx(font, target_text, target_text_font_size, target_text_font_space);
    Vector2 target_text_coor = {
        target_text_rect.x + ((target_text_rect.width - target_text_measure.x) / 2),
        target_text_rect.y + ((target_text_rect.height - target_text_measure.y) / 2)
    };
    DrawTextEx(font, target_text, target_text_coor, target_text_font_size, target_text_font_space, BLACK);

    // BUTTON 1 LEVEL
    float line_thick{ 5.F };
    Rectangle btn_1_rect{
        (base_rect.x + 2),
        (base_rect.y + 2),
        levelCard.btn_1.rect.width,
        levelCard.btn_1.rect.height
    };

    // BUTTON 2 LEVEL
    Rectangle btn_2_rect{
        (base_rect.x + 1 + (base_rect.width / 2)),
        (base_rect.y + 2),
        levelCard.btn_2.rect.width,
        levelCard.btn_2.rect.height
    };

    // BUTTON 3 LEVEL
    Rectangle btn_3_rect{
        (base_rect.x + 2),
        (base_rect.y + 1 + (base_rect.height / 2)),
        levelCard.btn_3.rect.width,
        levelCard.btn_3.rect.height
    };

    // BUTTON 4 LEVEL
    Rectangle btn_4_rect{
        (base_rect.x + 1 + (base_rect.width / 2)),
        (base_rect.y + 1 + (base_rect.height / 2)),
        levelCard.btn_4.rect.width,
        levelCard.btn_4.rect.height
    };

    // DRAW BUTTONS
    std::vector<Rectangle> buttons_rect{ btn_1_rect, btn_2_rect, btn_3_rect, btn_4_rect };

    for (size_t i = 0; i < buttons_rect.size(); i++) {
        LevelCard::Button button = levelCard.levelButtons[i];
        const char* points = button.text_points;

        DrawRectangleRounded(buttons_rect[i], button.roundness, button.segments, button.color);

        Vector2 circle_coor{
            (buttons_rect[i].x + buttons_rect[i].width / 2),
            (buttons_rect[i].y + buttons_rect[i].height / 2.75F)
        };
        DrawCircle(
            (int)circle_coor.x, 
            (int)circle_coor.y, 
            button.radius, 
            button.circle_color
        );

        Vector2 points_measure = MeasureTextEx(font, points, button.font_size_points, button.font_space);
        Vector2 points_coor = {
            buttons_rect[i].x + (buttons_rect[i].width - points_measure.x) / 2,
            buttons_rect[i].y + (buttons_rect[i].height / 1.8F)
        };
        DrawTextEx(font, points, points_coor, button.font_size_points, button.font_space, button.text_color);

    }

    btnLevelHoverClicked(mouse_position, btn_clicked, btn_hover, btn_1_rect, btn_2_rect, btn_3_rect, btn_4_rect, line_thick);

    // DRAW HOVER LEVEL BUTTON
    if (btn_hover.x != 0) {
        float line_smaller{ 2 };
        DrawRectangleRoundedLines
        (
            {
                btn_hover.x - line_smaller,
                btn_hover.y - line_smaller,
                levelCard.width / 2 - ((line_thick - line_smaller) * 2),
                levelCard.height / 2 - ((line_thick - line_smaller) * 2)
            },
            0.F,
            10,
            line_thick - line_smaller,
            levelCard.color_hover
        );
    }

    // DRAW CLICKED LEVEL BUTTON
    DrawRectangleRoundedLines
    (
        {
            btn_clicked.x,
            btn_clicked.y,
            levelCard.width / 2 - (line_thick * 2),
            levelCard.height / 2 - (line_thick * 2)
        },
        0.F,
        10,
        line_thick,
        levelCard.color_clicked
    );
}

void btnLevelHoverClicked
(
    Vector2& mouse_position, Vector2& btn_clicked, Vector2& btn_hover, 
    Rectangle& btn_1_rect, 
    Rectangle& btn_2_rect, 
    Rectangle& btn_3_rect,
    Rectangle& btn_4_rect, 
    float& line_thick
)
{
    Vector2 btn_1_hover = {
            (btn_1_rect.x - 2) + line_thick,
            (btn_1_rect.y - 2) + line_thick
    };
    Vector2 btn_2_hover = {
           (btn_2_rect.x - 1) + line_thick,
           (btn_2_rect.y - 2) + line_thick
    };
    Vector2 btn_3_hover = {
            (btn_3_rect.x - 2) + line_thick,
            (btn_3_rect.y - 1) + line_thick
    };
    Vector2 btn_4_hover = {
            (btn_4_rect.x - 1) + line_thick,
            (btn_4_rect.y - 1) + line_thick
    };

    std::vector<Vector2> btns_LEVEL_hover{ btn_1_hover, btn_2_hover, btn_3_hover, btn_4_hover };

    if (CheckCollisionPointRec(mouse_position, btn_1_rect)) {
        btn_hover = btns_LEVEL_hover[0];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            level_choice = SOFT;
        }
    } 
    else if (CheckCollisionPointRec(mouse_position, btn_2_rect)) {
        btn_hover = btns_LEVEL_hover[1];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            level_choice = EASY;
        }
    } 
    else if (CheckCollisionPointRec(mouse_position, btn_3_rect)) {
        btn_hover = btns_LEVEL_hover[2];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            level_choice = MED;
        }
    }
    else if (CheckCollisionPointRec(mouse_position, btn_4_rect)) {
        btn_hover = btns_LEVEL_hover[3];

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            level_choice = HARD;
        }
    }
    else {
        btn_hover = {};
    }

    switch (level_choice)
    {
    case SOFT:
        btn_clicked = btns_LEVEL_hover[0];
        break;
    case EASY:
        btn_clicked = btns_LEVEL_hover[1];
        break;
    case MED:
        btn_clicked = btns_LEVEL_hover[2];
        break;
    case HARD:
        btn_clicked = btns_LEVEL_hover[3];
        break;
    default:
        break;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
