/*
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#if !defined(h_8e4861a3_f607_479c_ac2d_0b2d81b4c36c)
#define h_8e4861a3_f607_479c_ac2d_0b2d81b4c36c

#include <log4cpp/Layout.hh>

namespace log4cpp
{
   class PassThroughLayout : public Layout
   {
      public:
         virtual StringBuffer format(LoggingEvent&& event) { return StringBuffer().append(std::move(event.message)).move(); }
   };
}

#endif // h_8e4861a3_f607_479c_ac2d_0b2d81b4c36c
