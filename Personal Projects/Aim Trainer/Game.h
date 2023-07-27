#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <random>
#include <unordered_map>
#include <set>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Enemy.h"

class Game {
private:
    // Scores
    std::set<unsigned> scores;
    void saveScoresToFile();
    void loadScoresFromFile();
    void displayScores(sf::RenderTarget& target);

    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font font;
    sf::Texture circleTexture;

    // Sound
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Text
    sf::Text uiText;

    // Game Logic
    bool endGame;
    unsigned points;
    sf::Clock timerClock;
    sf::Time timeLimit;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    bool checkSpriteOverlap(const Enemy& newSprite) const;

    // Game Objects
    // Use unordered_map to store enemies with unique IDs
    std::unordered_map<int, Enemy> enemies;

    // Private functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
    void spawnEnemy();

public:
    // Constructor / Destructor
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Functions
    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

    void addScore(unsigned points);
};
