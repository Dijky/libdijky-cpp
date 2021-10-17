#pragma once

#ifndef DIJKY_RANGE_H_
#define DIJKY_RANGE_H_

namespace dijky
{

template<typename T, typename DiffT>
class range
{
public:
    class iterator
    {
        friend class range;
    public:
        using value_type = T;
        using difference_type = DiffT;

        iterator() : iterator(range{}) {}
        iterator(const range& r) : iterator(r, r.start_) {}

        const value_type& value() const { return value_; }
        const value_type& operator*() const { return value(); }

        iterator& operator++() {
            auto next = value_ + range_.step_;
            bool in_range = (range_.step_ < difference_type{0}) ? (range_.stop_ < next) : (next < range_.stop_);
            value_ = in_range ? next : range_.stop_;
            return *this;
        }

        bool operator<(const iterator& rhs) const { return range_.step_ < difference_type{0} ? rhs.value_ < value_ : value_ < rhs.value_; }
        bool operator==(const iterator& rhs) const { return this == &rhs || (range_ == rhs.range_ && value_ == rhs.value_); }
        bool operator!=(const iterator& rhs) const { return !this->operator==(rhs); }

    private:
        iterator(const range& r, const value_type& v) : range_{r}, value_{v} {}

        const range& range_;
        value_type value_;
    };

    using value_type = T;
    using difference_type = DiffT;
    
    range() = default;
    range(const value_type& start, const value_type& stop, const difference_type& step) : start_{start}, stop_{stop}, step_{step} {}
    range(const value_type& start, const value_type& stop) : range(start, stop, difference_type{1}) {}
    range(const value_type& stop) : range(value_type{0}, stop) {}

    bool operator==(const range& rhs) const  {
        return this == &rhs || (start_ == rhs.start_ && stop_ == rhs.stop_ && step_ == rhs.step_);
    }

    iterator begin() const { return iterator(*this); }
    iterator end() const { return iterator(*this, stop_); }
    
private:
    value_type start_ = value_type{0};
    value_type stop_ = value_type{0};
    difference_type step_ = difference_type{0};
};

}

#endif // DIJKY_RANGE_H_
