#pragma once

#include <vector>
#include <string>

class Input {
public:
    Input();
    ~Input();

    // returns name of last key that was pressed, names are capitalized: Space, Right, A, B, etc
    std::string get_last_keypress();
    std::pair<int, int> get_last_mouse_click();

    // register keypress as the most recent
    void set_last_keypress(std::string key);
    
    // returns list of all input events since last call
    std::vector<std::string> get_all_input_events();


private:
    std::string last_keypress;
    
    // mouse position of last click
    int mouse_x, mouse_y;
};
