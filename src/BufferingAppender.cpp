/*
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4cpp/BufferingAppender.hh>
#include <algorithm>
#include <sstream>
#include <memory>

namespace log4cpp
{
   BufferingAppender::BufferingAppender(const std::string name, unsigned long max_size, 
                                        std::unique_ptr<Appender>&& sink, std::unique_ptr<TriggeringEventEvaluator>&& evaluator)
                     :LayoutAppender(name), max_size_(max_size), sink_(std::move(sink)), evaluator_(std::move(evaluator)), lossy_(false)
   {
      max_size_ = (max)(1UL, max_size_);
   }
   
   void BufferingAppender::_append(LoggingEvent&& event)
   {
      if (queue_.size() == max_size_) {
         if (lossy_)
            queue_.pop_back();
         else
            dump();
      }

      bool e = evaluator_->eval(event);

      queue_.emplace_front(std::move(event));
      
      if (e)
      {
         dump();
         queue_.clear();
      }
   }

   static const std::string EMPTY;
   
   void BufferingAppender::dump()
   {
      Layout& layout = _getLayout();

      if(queue_.size() == 1) {
         auto s = layout.format(std::move(queue_.front()));

         LoggingEvent event(EMPTY, s.str(), EMPTY, Priority::NOTSET);
         sink_->doAppend(std::move(event));
      }

      std::ostringstream s;
      //  Solaris 10 CC can't work with const_reverse_iterator
      for(queue_t::reverse_iterator i = queue_.rbegin(), last = queue_.rend(); i != last; ++i)
         s << layout.format(std::move(*i));

      LoggingEvent event(EMPTY, s.str(), EMPTY, Priority::NOTSET);
      sink_->doAppend(std::move(event));
   }
}

