#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"

int main(int argc, char** argv) {    
    log4cpp::Appender* appender = 
        new log4cpp::OstreamAppender("default", &std::cout);

    log4cpp::Layout* layout = new log4cpp::BasicLayout();
    appender->setLayout(layout);

    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.setAppender(appender);
    root.setPriority(log4cpp::Priority::ERROR);
    
    log4cpp::Category& sub1 = 
        log4cpp::Category::getInstance(std::string("sub1"));

    log4cpp::Category& sub2 = 
        log4cpp::Category::getInstance(std::string("sub1.sub2"));

    std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;
    
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    
    sub1.setPriority(log4cpp::Priority::INFO);
    std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;
   
    std::cout << "priority info" << std::endl;
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");

    sub2.warnStream() << "streamed warn";

    /* XXX 
     * MSC++ barfs on "ambiguous operators" and char[6] undefined input type
     * May be caused by improper streaming support in Category. 
     * Anyone with more iostream expertise, look at this.
     */ 
#ifndef _MSC_VER 
    sub2 << log4cpp::Priority::WARN << "warn2" << " warn3" << 
        log4cpp::CategoryStream::ENDLINE << " warn4";
#endif

    log4cpp::Category::shutdown();
}