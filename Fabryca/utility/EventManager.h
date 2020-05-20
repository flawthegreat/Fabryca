#pragma once

#include "Foundation.h"

#include <unordered_map>
#include <vector>
#include <string>


template<typename Type>
class EventManager {
public:
    using EventListener = std::function<Void (Type*)>;


    virtual ~EventManager() {};


    Void addEventListener(const std::string& event, const EventListener& listenter) {
        _listeners[event].emplace_back(listenter);
    }

protected:
    std::unordered_map<std::string, std::vector<EventListener>> _listeners;


    Void _postEvent(const std::string& event) {
        auto itr = _listeners.find(event);
        if (itr == _listeners.end()) return;

        for (auto callback: itr->second) {
            if (!callback) continue;

            callback(dynamic_cast<Type*>(this));
        }
    }
};
