/*
 * StringQueueAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4cpp/StringQueueAppender.hh>

namespace log4cpp {

    StringQueueAppender::StringQueueAppender(const std::string& name) : 
        LayoutAppender(name) {
    }
    
    StringQueueAppender::~StringQueueAppender() {
        close();
    }

    void StringQueueAppender::close() {
        // empty
    }

    void StringQueueAppender::_append(LoggingEvent&& event) {
        auto buf = _getLayout().format(std::move(event));
        for(auto&& chunk : buf) _queue.push(std::move(chunk));
    }

    bool StringQueueAppender::reopen() {
        return true;
    }      

    std::queue<std::string>& StringQueueAppender::getQueue() {
        return _queue;
    }

    const std::queue<std::string>& StringQueueAppender::getQueue() const {
        return _queue;
    }

    size_t StringQueueAppender::queueSize() const {
        return getQueue().size();
    }

    std::string StringQueueAppender::popMessage() {        
        std::string message;

        if (!_queue.empty()) {
            message = std::move(_queue.front());
            _queue.pop();
        }

        return std::move(message);
    }
}
