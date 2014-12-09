#include "Player.h"
#include "../Game.h"
#include "../Models/States.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace Model {

    Player::Player() : Bubble() {
        setPosition(glm::vec3(2.5f, 2.5f, -1.0f));
    }

    Player::~Player() {

    }

    void Player::update(double deltaTime) {
        bool axisAligned = false;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 front;

        if(axisAligned) {
            up    = glm::vec3(0.0f, 1.0f,  0.0f);
            right = glm::vec3(1.0f, 0.0f,  0.0f);
            front = glm::vec3(0.0f, 0.0f, -1.0f);
        } else {
            up    = Model::States::get().gameplay->getCamera().getUp();
            right = Model::States::get().gameplay->getCamera().getRight();
            front = Model::States::get().gameplay->getCamera().getDirection();
        }

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_A) == GLFW_PRESS)
            _position -= _speed * static_cast<float>(deltaTime) * right;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_D) == GLFW_PRESS)
            _position += _speed * static_cast<float>(deltaTime) * right;

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_SPACE) == GLFW_PRESS)
            _position += _speed * static_cast<float>(deltaTime) * up;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            _position -= _speed * static_cast<float>(deltaTime) * up;

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_W) == GLFW_PRESS)
            _position += _speed * static_cast<float>(deltaTime) * front;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_S) == GLFW_PRESS)
            _position -= _speed * static_cast<float>(deltaTime) * front;

        checkBoundries();
    }

    void Player::checkBoundries() {
        Model::Aquarium& aquarium = Model::States::get().gameplay->getAquarium();

        if(getPosition().x - getRadius() < aquarium.getPosition().x)
            _position.x = aquarium.getPosition().x + getRadius();

        if(getPosition().x + getRadius() > aquarium.getPosition().x + aquarium.getSize().x)
            _position.x = aquarium.getPosition().x + aquarium.getSize().x - getRadius();

        if(getPosition().y - getRadius() < aquarium.getPosition().y)
            _position.y = aquarium.getPosition().y + getRadius();

        if(getPosition().y + getRadius() > aquarium.getPosition().y + aquarium.getSize().y)
            _position.y = aquarium.getPosition().y + aquarium.getSize().y - getRadius();
        
        if(getPosition().z - getRadius() < aquarium.getPosition().z)
            _position.z = aquarium.getPosition().z + getRadius();

        if(getPosition().z + getRadius() > aquarium.getPosition().z + aquarium.getSize().z)
            _position.z = aquarium.getPosition().z + aquarium.getSize().z - getRadius();
    }

}