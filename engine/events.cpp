#include "events.h"
#include <algorithm>

void Events::add(std::shared_ptr<Event> event) {
    events.push_back(event);
}

void Events::execute(Engine& engine) {
    if (empty()) {
        return;
    }

    // When an event is done, there may be some subsequent events to
    // run. Collect those in here, then add them to the event queue.
    std::vector<std::shared_ptr<Event>> next_events;
    
    // process all current events
    for (std::shared_ptr<Event> event : events) {
        event->execute(engine);
        event->update();
        if (event->is_done()) {
            event->when_done(engine); // event clean-up
            // collect any next events
            std::copy(std::begin(event->next_events), std::end(event->next_events),
                      std::back_inserter(next_events));
        }
    }

    remove_done_events();

    // add any new events to event queue
    std::copy(std::begin(next_events), std::end(next_events), std::back_inserter(events));
}

bool Events::empty() const {
    return events.empty();
}

void Events::remove_done_events() {
    std::erase_if(events, [](const std::shared_ptr<Event>& event) { return event->is_done(); });
}
