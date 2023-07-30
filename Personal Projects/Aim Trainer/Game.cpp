#include "Game.h"

// Constructors / Destructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
    this->initHitSounds();
    this->initBackground();

    loadScoresFromFile();
}

Game::~Game() {
    delete this->window;
}

const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

void Game::saveScoresToFile() {
    std::ofstream file("scores.txt");
    if (!file.is_open()) {
        std::cout << "ERROR::GAME::saveScoresToFile::Failed to open scores file!" << std::endl;
        return;
    }

    // Save the scores to the file
    for (const auto& score : scores) {
        file << score << std::endl;
    }

    file.close();
}

void Game::loadScoresFromFile() {
    std::ifstream file("scores.txt");
    if (!file.is_open()) {
        std::cout << "ERROR::GAME::loadScoresFromFile::Failed to open scores file!" << std::endl;
        return;
    }

    // Clear existing scores before loading from the file
    scores.clear();

    // Read scores from the file and insert them into the std::set
    unsigned score;
    while (file >> score) {
        scores.insert(score);
    }

    file.close();
}

void Game::displayScores(sf::RenderTarget& target) {
    // Prepare the text to display the scores
    sf::Text scoresText;
    scoresText.setFont(this->font);
    scoresText.setFillColor(sf::Color::White);

    // Prepare the string to hold the scores
    std::stringstream ss;
    ss << "High Scores:\n";

    int count = 0;
    // Loop through the set using a reverse iterator to get scores in descending order
    for (auto it = scores.rbegin(); it != scores.rend() && count < 10; ++it, ++count) {
        ss << std::to_string(*it) << "\n";
    }

    scoresText.setString(ss.str());
    scoresText.setPosition(10.f, 120.f);

    // Draw the scores on the target (game window)
    target.draw(scoresText);
}


bool Game::checkSpriteOverlap(const Enemy& newSprite) const {
    for (const auto& it : this->enemies) {
        // Get the bounding box of the new sprite and the existing sprite
        sf::FloatRect newBounds = newSprite.getGlobalBounds();
        sf::FloatRect existingBounds = it.second.getGlobalBounds();

        // Check for intersection of bounding boxes
        if (newBounds.intersects(existingBounds)) {
            return true; // Overlapping sprites
        }
    }
    return false; // No overlapping sprites
}


void Game::initVariables() {
    this->window = nullptr;

    // Game logic
    this->endGame = false;
    this->points = 0;
    timeLimit = sf::seconds(62.0f);
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 3;
    this->mouseHeld = false;
}


void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->videoMode = sf::VideoMode::getDesktopMode(); // Use the desktop resolution

    this->window = new sf::RenderWindow(this->videoMode, "Aim Trainer", sf::Style::Fullscreen);

    this->window->setFramerateLimit(85);
}


void Game::initFonts() {
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}


void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}


void Game::initEnemies() {
    if (!this->circleTexture.loadFromFile("Ball/aimlab.png")) {
        std::cout << "ERROR::GAME::INITENEMIES::Failed to load circle image!" << "\n";
    }
}


void Game::initHitSounds()
{
    // Load the sound buffer from file
    if (!this->clickBuffer.loadFromFile("HitSounds/aimbooster_hit.ogg")) {
        std::cout << "ERROR::GAME::Failed to load click sound!" << std::endl;
    }

    // Set the sound buffer to the sound object
    this->clickSound.setBuffer(this->clickBuffer);
    this->clickSound.setVolume(50);
}


void Game::initBackground()
{
    // Load the background texture from file
    if (!this->backgroundTexture.loadFromFile("Background/robloxcreation.png")) {
        std::cout << "ERROR::GAME::Failed to load background texture!" << std::endl;
    }

    // Set the texture to the background sprite
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setPosition(0.f, 0.f);
    this->backgroundSprite.setScale(
        static_cast<float>(this->window->getSize().x) / this->backgroundTexture.getSize().x,
        static_cast<float>(this->window->getSize().y) / this->backgroundTexture.getSize().y
    );
}


void Game::spawnEnemy() {
    std::random_device rd;
    std::mt19937 mt(rd());

    // Calculate the maximum allowed x and y positions for spawning sprites within the square area
    float squareSize = 800.f; // Adjust this value to control the size of the square area
    float maxX = this->window->getSize().x / 2 + squareSize / 2 - this->circleTexture.getSize().x * 0.3f;
    float maxY = this->window->getSize().y / 2 + squareSize / 2 - this->circleTexture.getSize().y * 0.3f;
    float minX = this->window->getSize().x / 2 - squareSize / 2 + this->circleTexture.getSize().x * 0.3f;
    float minY = this->window->getSize().y / 2 - squareSize / 2 + this->circleTexture.getSize().y * 0.3f;

    std::uniform_real_distribution<float> xDist(minX, maxX);
    std::uniform_real_distribution<float> yDist(minY, maxY);

    // Create a new enemy with the circleTexture
    Enemy newEnemy(this->circleTexture);
    newEnemy.setPosition(xDist(mt), yDist(mt));

    // Repeatedly generate random positions within the square area until a position is found
    bool overlapping = true;
    while (overlapping) {
        overlapping = this->checkSpriteOverlap(newEnemy);
        if (overlapping) {
            // Regenerate position if overlapping
            newEnemy.setPosition(xDist(mt), yDist(mt));
        }
    }

    static int newEnemyID = 0;
    int uniqueID = newEnemyID++;

    // Insert the enemy into the hashmap with the unique ID
    this->enemies[uniqueID] = newEnemy;
}


void Game::pollEvents() {
    // Event Polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close(); // Manually close the window
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}


void Game::updateMousePositions() {
    /*
        @return void
        Updates the mouse Positions
        - Mouse Positions relative to window (Vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::updateText() {
    // Calculate the remaining time
    sf::Time remainingTime = timeLimit - timerClock.getElapsedTime();

    std::stringstream ss;
    ss << "Points: " << points << "\n"
        << "Time: " << static_cast<int>(remainingTime.asSeconds()) << "s\n";

    uiText.setString(ss.str());
}


void Game::updateEnemies() {
    // Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }
    }

    // Check if clicked Upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;
            for (auto it = this->enemies.begin(); it != this->enemies.end(); ) {
                if (it->second.getGlobalBounds().contains(this->mousePosView)) {
                    // Play the click sound
                    this->clickSound.play();

                    // Gain points
                    this->points += 1;

                    // Delete the enemy from the hashmap
                    it = this->enemies.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}


void Game::update() {
    this->pollEvents();

    if (this->endGame == false) {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }

    // End game condition
    if (timerClock.getElapsedTime() >= timeLimit) {
        endGame = true;
        addScore(points);

        saveScoresToFile();
    }
}


void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}


void Game::renderEnemies(sf::RenderTarget& target) {
    // Rendering all the enemies
    for (const auto& it : this->enemies) {
        it.second.draw(target);
    }
}


void Game::render() {
    /*
        @return void
        - Clear odd frame
        - Render objects
        - Display frame in window

        Renders the game Objects.
    */
    this->window->clear();

    // Draw the background first
    this->window->draw(this->backgroundSprite);

    // Draw game Objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    displayScores(*this->window);

    this->window->display();
}


void Game::addScore(unsigned points)
{
    scores.insert(points);
}
