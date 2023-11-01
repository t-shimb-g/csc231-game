#include "event.h"


Event::Event(int number_of_frames)
    :number_of_frames{number_of_frames}, frame_count{0} {}

// Event::Event(Event&& other)
//     :number_of_frames{std::move(other.number_of_frames)}, frame_count{other.frame_count},
//      next_events{std::move(other.next_events)} {
//     other.number_of_frames = 0;
//     other.frame_count = 0;
//     other.next_events.clear();
// }

void Event::update() {
    ++frame_count;
}

bool Event::is_done() const {
    return frame_count == number_of_frames;
}

void Event::when_done(Engine&) {}
