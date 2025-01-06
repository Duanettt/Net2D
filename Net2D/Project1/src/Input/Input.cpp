// Input.cpp
#include "Input.h"


std::vector<KeyInput*> KeyInput::_instances;

KeyInput::KeyInput(std::vector<int> keysToMonitor) : _isEnabled(true) {
    for (int key : keysToMonitor) {
        _keys[key] = false;
    }
    _instances.push_back(this);
}

KeyInput::~KeyInput() {
    auto it = std::remove(_instances.begin(), _instances.end(), this);
    _instances.erase(it, _instances.end());
}

bool KeyInput::get_is_key_down(int key) {
    if (!_isEnabled) return false;

    auto it = _keys.find(key);
    return (it != _keys.end()) ? it->second : false;
}

void KeyInput::set_is_key_down(int key, bool isDown) {
    auto it = _keys.find(key);
    if (it != _keys.end()) {
        it->second = isDown;
    }
}

void KeyInput::setup_key_inputs(Window& window) {
    glfwSetKeyCallback(window.GetWindow(), KeyInput::callback);
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (KeyInput* keyInput : _instances) {
        keyInput->set_is_key_down(key, action != GLFW_RELEASE);
    }
}