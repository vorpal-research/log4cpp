/*
 * SimpleLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/Priority.hh>
#include <ios>
#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif

#include <memory>
#include <log4cpp/FactoryParams.hh>

namespace log4cpp {

    SimpleLayout::SimpleLayout() {
    }
    
    SimpleLayout::~SimpleLayout() {
    }

    StringBuffer SimpleLayout::format(LoggingEvent&& event) {
        std::ostringstream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
		message.width(Priority::MESSAGE_SIZE);message.setf(std::ios::left);
		message << priorityName << ": " << std::flush;

        return StringBuffer().append(message.str()).append(std::move(event.message)).append("\n").move();
    }

   std::unique_ptr<Layout> create_simple_layout(const FactoryParams& params)
   {
      return std::unique_ptr<Layout>(new SimpleLayout);
   }
}
