#ifndef __SORTED_SEQUENCE__
#define __SORTED_SEQUENCE__

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class SortedSequence
{
public:
  SortedSequence() : capacity_(0), size_(0), data_(nullptr) {}
  ~SortedSequence() { delete[] data_; }

  void add(const T &a)
  { // Task 2 - To Do
    if (data_ == nullptr)
    {
      data_ = new T[1];
      capacity_++;
    }
    if (size_ == capacity_)
    {
      capacity_ = capacity_ * 2;
      T *temp = new T[capacity_];
      for (int i = 0; i < size_; i++)
      {
        temp[i] = data_[i];
      }
      delete[] data_;
      data_ = temp;
    }
    data_[size_] = a;
    size_++;
    int i = size_ - 1;
    while (i > 0 && data_[i] < data_[i - 1])
    {
      T temp = data_[i];
      data_[i] = data_[i - 1];
      data_[i - 1] = temp;
      i--;
    }
  }

  std::string toString() const
  {
    std::stringstream ss;
    ss << "capacity: " << capacity_ << ", size: " << size_
       << ", data: " << std::endl;
    if (data_ == nullptr)
    {
      ss << "None";
    }
    else
    {
      for (int i = 0; i < size_; i++)
      {
        ss << data_[i] << " ";
      }
    }
    return ss.str();
  }

private:
  int capacity_;
  int size_;
  T *data_;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const SortedSequence<T> &t)
{
  os << t.toString();
  return os;
}

#endif