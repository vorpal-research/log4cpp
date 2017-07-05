/*
 * SimpleLayout.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_SIMPLELAYOUT_HH
#define _LOG4CPP_SIMPLELAYOUT_HH

#include <log4cpp/Portability.hh>
#include <log4cpp/Layout.hh>

namespace log4cpp {
    
    /**
     * BasicLayout is a simple fixed format Layout implementation. 
     **/
    class LOG4CPP_EXPORT SimpleLayout : public Layout {
        public:
        SimpleLayout();
        virtual ~SimpleLayout();

        /**
         * Formats the LoggingEvent in SimpleLayout style:<br>
         * "priority - message"
         **/
        virtual StringBuffer format(LoggingEvent&& event) override;
    };        
}

#endif // _LOG4CPP_SIMPLELAYOUT_HH
