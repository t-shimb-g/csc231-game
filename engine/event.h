#pragma once

#include <memory>
#include <vector>

// forward declaration
class Engine;

// Events are things that happen in the world (entities cannot do them
// directly) and will be processed to completion before entities take
// more turns. Useful for animations, enemies taking damage, etc.
class Event {
public:
    Event(int number_of_frames=1); // how many frames it should last
    virtual ~Event() {}

    //Event(Event&& other);
    
    void update();

    // returns whether event has finished
    virtual bool is_done() const;

    // what the event does per update frame
    virtual void execute(Engine& engine) = 0;

    // called when the event is completed, useful for cleaning up
    // (e.g. resetting a sprite after an animation)
    virtual void when_done(Engine& engine);

    // add events that will take place after this current one
    template <typename T>
    void add_next(T&& event) {
        next_events.push_back(std::make_shared<T>(std::forward<T>(event)));
    }
    void add_next(std::shared_ptr<Event> event) {
        next_events.push_back(event);
    }
    
protected:
    int number_of_frames, frame_count;

public:
    // holds the events that will be run when this event is done
    std::vector<std::shared_ptr<Event>> next_events;
};
