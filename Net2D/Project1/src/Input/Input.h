// Input.h
#pragma once
#include <map>
#include <vector>
#include "../Core/Window.h"

class KeyInput {
public:
    // Takes a list of which keys to keep state for
    KeyInput(std::vector<int> keysToMonitor);
    ~KeyInput();

    bool get_is_key_down(int key);
    bool get_is_enabled() { return _isEnabled; }
    void set_is_enabled(bool value) { _isEnabled = value; }

    // Static setup function that must be called before any KeyInput instances will work
    static void setup_key_inputs(Window& window);

private:
    // Used internally to update key states. Called by the GLFW callback
    void set_is_key_down(int key, bool isDown);

    // Map from monitored keys to their pressed states
    std::map<int, bool> _keys;

    // If disabled, KeyInput.getIsKeyDown always returns false
    bool _isEnabled;

    // The GLFW callback for key events. Sends events to all KeyInput instances
    static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Keep a list of all KeyInput instances and notify them all of key events
    static std::vector<KeyInput*> _instances;
};
