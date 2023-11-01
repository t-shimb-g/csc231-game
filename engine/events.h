#pragma once

#include "event.h"
#include <memory>
#include <vector>

// forward declaration
class Engine;


class Events {
public:
    // add an event to the list of events


    void add(std::shared_ptr<Event> event);
    
    template <typename T, typename... Args>
    std::shared_ptr<T> create_event(Args&&... args) {
        auto event = std::make_shared<T>(std::forward<Args>(args)...);
        add(event);
        return event;
    }

    // update all currently running events
    void execute(Engine& engine);
    bool empty() const;
    
private:
    std::vector<std::shared_ptr<Event>> events;
    void remove_done_events();
};
