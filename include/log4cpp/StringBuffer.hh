#ifndef _LOG4CPP_STRINGBUFFER_H
#define _LOG4CPP_STRINGBUFFER_H

#include <deque>
#include <string>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <utility>

namespace log4cpp {

class StringBuffer {
    using container = std::deque<std::string>;

    container data_;
    size_t length_ = 0;

public:
    StringBuffer() = default;
    StringBuffer(StringBuffer&&) = default;

    template<class T>
    StringBuffer& operator+=(T&& value) {
        return append(std::forward<T>(value));
    }

    template<class T>
    StringBuffer& operator<<(T&& value) {
        return append(std::forward<T>(value));
    }

    StringBuffer& append(std::string&& str) {
        length_ += str.size();
        data_.push_back(std::move(str));
        return *this;
    }
    StringBuffer& append(StringBuffer&& str) {
        for(auto&& e: str.data_) {
            append(std::move(e));
        }
        return *this;
    }

    template<class T>
    StringBuffer& append(T&& value) {
        std::ostringstream ostr;
        ostr << std::forward<T>(value);
        return append(ostr.str());
    }

    StringBuffer move() {
        return std::move(*this);
    }

    std::string str() const {
        std::string res;
        res.reserve(length_ + 1);
        for(auto&& e : data_) res += e;
        return std::move(res);
    }

    friend std::ostream& operator<<(std::ostream& ost, const StringBuffer& sb) {
        for(auto&& e: sb.data_) ost << e;
        return ost;
    }


    using iterator = typename container::iterator;
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }

};

} /* namespace log4cpp */


#endif //_LOG4CPP_STRINGBUFFER_H
