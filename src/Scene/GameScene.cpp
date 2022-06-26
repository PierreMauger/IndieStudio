/*
** EPITECH PROJECT, 2022
** GameScene.cpp
** File description:
** GameScene
*/

#include "GameScene.hpp"

using namespace neo;

GameScene::GameScene(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_incrementor = 0;
    this->_winTimer = 0.0f;
    Packet playMusic;
    playMusic << "gameMusic.mp3";
    this->_messageBus->sendMessage(Message(playMusic, AudioCommand::PLAY_MUSIC, Module::AUDIO));

    this->_botEngine = std::make_unique<BotEngine>();
    this->_objects[-1] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(100.0f));
    this->_objects[-1]->setShiny(false);
    this->_objects[-2] = std::make_unique<GameObject>(0, "SpaceShip", glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(5.0f));
    this->_objects[-2]->setRotation(glm::vec3(0.0f, 0.0f, 180.0f));
}

GameScene::~GameScene()
{
    for (auto &[playerKey, player] : this->_players)
        player.reset();
    for (auto &[wallKey, wall] : this->_walls)
        wall.reset();
    for (auto &[bombKey, bomb] : this->_bombs)
        bomb.reset();
    for (auto &[powerUpKey, powerUp] : this->_powerUps)
        powerUp.reset();
    for (auto &[objectKey, object] : this->_objects)
        object.reset();
    this->_players.clear();
    this->_walls.clear();
    this->_bombs.clear();
    this->_powerUps.clear();
    this->_objects.clear();
    this->_botEngine.reset();
}

void GameScene::loadScene()
{
    Packet packet;
    this->_winTimer = 0.0f;

    for (auto &[playerKey, player] : this->_players)
        packet << player->getType() << playerKey << *player;
    for (auto &[wallKey, wall] : this->_walls)
        packet << wall->getType() << wallKey << *wall;
    for (auto &[bombKey, bomb] : this->_bombs)
        packet << bomb->getType() << bombKey << *bomb;
    for (auto &[objectKey, object] : this->_objects)
        packet << object->getType() << objectKey << *object;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, -50.0f, 100.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
    Packet playMusic;
    playMusic << "gameMusic.mp3";
    this->_messageBus->sendMessage(Message(playMusic, AudioCommand::PLAY_MUSIC, Module::AUDIO));
}

void GameScene::updatePlayers(void)
{
    Packet deleteGraphicObject;

    for (auto &[playerKey, player] : this->_players) {
        if (player->getDirection(RIGHT))
            player->getSpeed().x += 0.1f + player->getSpeedUp() * 0.05f;
        if (player->getDirection(LEFT))
            player->getSpeed().x += -0.1f - player->getSpeedUp() * 0.05f;
        if (player->getDirection(UP))
            player->getSpeed().y += 0.1f + player->getSpeedUp() * 0.05f;
        if (player->getDirection(DOWN))
            player->getSpeed().y += -0.1f - player->getSpeedUp() * 0.05f;
        for (auto it = this->_walls.begin(); it != this->_walls.end();) {
            if (it->second->getName() == "Wall" && player->getWallPass()) {
                it++;
                continue;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
            if (player->getSpeed().x && player->getSpeed().y && CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            } else {
                it++;
            }
        }
        for (auto &[bombKey, bomb] : this->_bombs) {
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f)))
                continue;
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
            if (player->getSpeed().x && player->getSpeed().y && CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
        }
        for (auto it = this->_powerUps.begin(); it != this->_powerUps.end();) {
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f)) &&
                (player->isBot() && it->second->getName() != "SpeedUp" || !player->isBot())) {
                if (it->second->getName() == "BombUp")
                    player->getBombUp() += 1;
                if (it->second->getName() == "SpeedUp" && player->getSpeedUp() < 5)
                    player->getSpeedUp() += 1;
                if (it->second->getName() == "FireUp")
                    player->getFireUp() += 1;
                if (it->second->getName() == "WallPass")
                    player->getWallPass() = true;
                Packet playSound;
                playSound << "powerUp.mp3";
                this->_messageBus->sendMessage(Message(playSound, AudioCommand::PLAY_SOUND, Module::AUDIO));
                deleteGraphicObject << it->second->getType() << it->first;
                this->_powerUps.erase(it++);
            } else {
                it++;
            }
        }
        if (player->getSpeed() != glm::vec3(0.0f)) {
            player->move(player->getSpeed());
            Packet moveGraphicObject;
            moveGraphicObject << playerKey << player->getPos().x << player->getPos().y << player->getPos().z;
            this->_messageBus->sendMessage(Message(moveGraphicObject, GraphicsCommand::MOVE, Module::GRAPHICS));
            player->getSpeed() = glm::vec3(0.0f);
        }
    }
    if (deleteGraphicObject.checkSize(1))
        this->_messageBus->sendMessage(Message(deleteGraphicObject, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::explode(std::unique_ptr<Bomb> &bomb)
{
    Packet addData;
    Packet deleteData;

    for (size_t i = RIGHT; i <= DOWN; i++) {
        for (auto &[explosionKey, explosion] : bomb->getExplosions())
            if (explosion->getPos().x == bomb->getPos().x + (i == RIGHT ? bomb->getState() : i == LEFT ? -bomb->getState() : 0) &&
                explosion->getPos().y == bomb->getPos().y + (i == UP ? bomb->getState() : i == DOWN ? -bomb->getState() : 0))
                deleteData << explosion->getType() << explosionKey;

        if (bomb->getStop(i) == true)
            continue;

        for (auto it = this->_players.begin(); it != this->_players.end();) {
            if (std::floor(it->second->getPos().x) + 0.5f == bomb->getPos().x + (i == RIGHT ? bomb->getState() : i == LEFT ? -bomb->getState() : 0) &&
                std::floor(it->second->getPos().y) + 0.5f == bomb->getPos().y + (i == UP ? bomb->getState() : i == DOWN ? -bomb->getState() : 0)) {
                deleteData << it->second->getType() << it->first;
                this->_winners[this->_top] = it->second->getName();
                this->_top--;
                this->_players.erase(it++);
            } else {
                it++;
            }
        }

        for (auto &[bombKey, other_bomb] : this->_bombs) {
            if (other_bomb->getPos() == bomb->getPos())
                continue;
            if (other_bomb->getPos().x == bomb->getPos().x + (i == RIGHT ? bomb->getState() : i == LEFT ? -bomb->getState() : 0) &&
                other_bomb->getPos().y == bomb->getPos().y + (i == UP ? bomb->getState() : i == DOWN ? -bomb->getState() : 0))
                other_bomb->getTimer() = 0.0f;
        }

        for (auto it = this->_powerUps.begin(); it != this->_powerUps.end();) {
            if (it->second->getPos().x == bomb->getPos().x + (i == RIGHT ? bomb->getState() : i == LEFT ? -bomb->getState() : 0) &&
                it->second->getPos().y == bomb->getPos().y + (i == UP ? bomb->getState() : i == DOWN ? -bomb->getState() : 0)) {
                deleteData << it->second->getType() << it->first;
                this->_powerUps.erase(it++);
            } else {
                it++;
            }
        }

        for (auto it = this->_walls.begin(); it != this->_walls.end(); it++) {
            if (it->second->getPos().x == bomb->getPos().x + (i == RIGHT ? bomb->getState() : i == LEFT ? -bomb->getState() : 0) &&
                it->second->getPos().y == bomb->getPos().y + (i == UP ? bomb->getState() : i == DOWN ? -bomb->getState() : 0)) {
                if (bomb->getState() != 0)
                    bomb->getStop(i) = true;
                if (it->second->getName() == "Block")
                    break;
                deleteData << it->second->getType() << it->first;
                if (std::rand() % 5 == 0) {
                    this->_powerUps[this->_incrementor] = std::make_unique<PowerUp>(powerUps[std::rand() % 10], it->second->getPos(), glm::vec3(0.5f));
                    addData << this->_powerUps[this->_incrementor]->getType() << this->_incrementor << *this->_powerUps[this->_incrementor];
                    this->_incrementor++;
                }
                this->_walls.erase(it++);
                break;
            }
        }

        if (bomb->getState() != 2 + bomb->getFireUp() && !bomb->getStop(i)) {
            bomb->getExplosions()[this->_incrementor] = std::make_unique<GameObject>(0, "Fire",
                glm::vec3(bomb->getPos().x + (i == RIGHT ? bomb->getState() + 1 : i == LEFT ? -bomb->getState() - 1 : 0),
                bomb->getPos().y + (i == UP ? bomb->getState() + 1 : i == DOWN ? -bomb->getState() - 1 : 0), bomb->getPos().z), glm::vec3(0.45f));
            addData << bomb->getExplosions()[this->_incrementor]->getType() << this->_incrementor << *bomb->getExplosions()[this->_incrementor];
            this->_incrementor++;
        }
    }
    if (addData.checkSize(1))
        this->_messageBus->sendMessage(Message(addData, GraphicsCommand::ADD, Module::GRAPHICS));
    if (deleteData.checkSize(1))
        this->_messageBus->sendMessage(Message(deleteData, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::updateBombs(void)
{
    Packet data;

    for (auto it = this->_bombs.begin(); it != this->_bombs.end();) {
        if ((GetTime() - it->second->getTimer()) * 10 > (it->second->getState() == 0 ? 30 : 1)) {
            this->explode(it->second);
            Packet playSound;
            playSound << "bombExplosion.mp3";
            this->_messageBus->sendMessage(Message(playSound, AudioCommand::PLAY_SOUND, Module::AUDIO));
            data << it->second->getType() << it->first;
            it->second->getState()++;
            it->second->getTimer() = GetTime();
            if (it->second->getState() == 2 + it->second->getFireUp() + 1)
                this->_bombs.erase(it++);
        } else {
            it++;
        }
    }
    if (data.checkSize(1))
        this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::update(void)
{
    if (this->_winTimer == 0.0f) {
        this->_botEngine->updateBot(this);
        this->updatePlayers();
        this->updateBombs();
    } else if (this->_winTimer > 10.0f) {
        Packet packet;
        packet << 4;
        if (this->_players.size() == 1)
            this->_winners[this->_top] = this->_players.begin()->second->getName();
        for (auto &[winnerKey, winner] : this->_winners)
            packet << winner << winnerKey;
        this->_messageBus->sendMessage(Message(packet, CoreCommand::START_GAME, Module::CORE));
        packet.clear();
        packet << 4;
        this->_messageBus->sendMessage(Message(packet, CoreCommand::CHANGE_SCENE, Module::CORE));
    }
    if (this->_players.size() <= 1) {
        if (this->_winTimer == 0.0f) {
            Packet packet;
            packet << 0 << glm::vec3(0.0f, -50.0f, 100.0f);
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
        }
        this->_winTimer += GetFrameTime();
    }
}

bool GameScene::canPlaceBomb(int playerID)
{
    size_t bombsCount = 0;

    for (auto it = this->_bombs.begin(); it != this->_bombs.end(); it++)
        if (it->second->getPlayerId() == playerID)
            bombsCount++;
    if (1 + this->_players[playerID]->getBombUp() > bombsCount)
        return true;
    return false;
}

void GameScene::handleKeyPressed(int playerID, std::string action)
{
    if (this->_players.find(playerID) == this->_players.end())
        return;
    if (action == "Adjust")
        this->_players[playerID]->teleport(glm::vec3(
        std::floor(this->_players[playerID]->getPos().x) + 0.5f,
        std::floor(this->_players[playerID]->getPos().y) + 0.5f,
        this->_players[playerID]->getPos().z));
    else if (action == "MoveRight")
        this->_players[playerID]->getDirection(RIGHT) = true;
    else if (action == "MoveLeft")
        this->_players[playerID]->getDirection(LEFT) = true;
    else if (action == "MoveUp")
        this->_players[playerID]->getDirection(UP) = true;
    else if (action == "MoveDown")
        this->_players[playerID]->getDirection(DOWN) = true;
    else if (action == "Main" && canPlaceBomb(playerID)) {
        glm::vec3 pos(floor(this->_players[playerID]->getPos().x) + 0.5f, floor(this->_players[playerID]->getPos().y) + 0.5f, this->_players[playerID]->getPos().z);
        this->_bombs[this->_incrementor] = std::make_unique<Bomb>("Bomb", pos, this->_players[playerID]->getFireUp(), playerID, glm::vec3(0.5f));
        Packet packet;
        packet << this->_bombs[this->_incrementor]->getType() << this->_incrementor << *this->_bombs[this->_incrementor];
        this->_incrementor++;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
    }
}

void GameScene::handleKeyReleased(int playerID, std::string action)
{
    if (this->_players.find(playerID) == this->_players.end())
        return;
    if (action == "MoveRight")
        this->_players[playerID]->getDirection(RIGHT) = false;
    else if (action == "MoveLeft")
        this->_players[playerID]->getDirection(LEFT) = false;
    else if (action == "MoveUp")
        this->_players[playerID]->getDirection(UP) = false;
    else if (action == "MoveDown")
        this->_players[playerID]->getDirection(DOWN) = false;
}


void GameScene::handleButtonClicked(int button)
{
}

void GameScene::handleConfig(std::vector<std::string> config)
{
}

void GameScene::handleStartGame(Packet data)
{
    std::vector<std::string> map;
    std::vector<std::string> models;
    int size = 0;
    int it = 0;

    data >> size;
    for (int i = 0; i < size; i++) {
        std::string tmp;
        data >> tmp;
        map.push_back(tmp);
    }
    while (data.checkSize(1)) {
        std::string model;
        data >> model;
        models.push_back(model);
    }

    this->_mapSize = CAST(Vector2, (float)size, (float)size);
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)map[i].size() - 1) / 2, -j + ((float)map.size() - 1) / 2, 0.0f};
            if (map[i][j] == 'P')
                this->_players[this->_incrementor++] = std::make_unique<Player>(models[it++], pos, false, glm::vec3(0.4f));
            else if (map[i][j] == 'B')
                this->_players[this->_incrementor++] = std::make_unique<Player>(models[it++], pos, true, glm::vec3(0.4f));
        }
    }
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)map[i].size() - 1) / 2, -j + ((float)map.size() - 1) / 2, 0.0f};
            if (map[i][j] == '#')
                this->_walls[this->_incrementor++] = std::make_unique<Wall>("Block", pos, glm::vec3(0.5f));
            else if (map[i][j] == 'W')
                this->_walls[this->_incrementor++] = std::make_unique<Wall>("Wall", pos, glm::vec3(0.5f));
        }
    }
    this->_top = this->_players.size();
}

std::shared_ptr<MessageBus> GameScene::getMessageBus()
{
    return this->_messageBus;
}

std::map<int, std::unique_ptr<Player>> &GameScene::getPlayers()
{
    return this->_players;
}

std::map<int, std::unique_ptr<Bomb>> &GameScene::getBombs()
{
    return this->_bombs;
}

std::map<int, std::unique_ptr<Wall>> &GameScene::getWalls()
{
    return this->_walls;
}

std::map<int, std::unique_ptr<PowerUp>> &GameScene::getPowerUps()
{
    return this->_powerUps;
}

Vector2 GameScene::getMapSize()
{
    return this->_mapSize;
}
