/*
 * BasicLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/FactoryParams.hh>
#include <memory>

#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4cpp {

    BasicLayout::BasicLayout() {
    }
    
    BasicLayout::~BasicLayout() {
    }

    StringBuffer BasicLayout::format(LoggingEvent&& event) {
        StringBuffer message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << event.timeStamp.getSeconds() << " " << priorityName << " " 
                << event.categoryName << " " << event.ndc << ": " << event.message << "\n";

        return message.move();
    }

    std::unique_ptr<Layout> create_basic_layout(const FactoryParams& params)
    {
       return std::unique_ptr<Layout>(new BasicLayout);
    }
}
