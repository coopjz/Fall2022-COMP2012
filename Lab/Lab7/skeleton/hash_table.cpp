#include "hash_table.h"
#include <cmath>
#include <iostream>

int HashTable::hashFunction(const std::string &name, int base, int table_size)
{
  int res = 0;
  for (unsigned int i = 0; i < name.size(); i++)
  {
    res = (base * res + name[i] - 'a') % table_size;
  }
  return res;
}

int HashTable::getNextHashTableSize(int now_hash_table_size)
{
  int res = now_hash_table_size * 2;
  bool is_prime = false;
  while (true)
  {
    is_prime = true;
    int sq = sqrt(res);
    for (int i = 2; i <= sq; i++)
    {
      if (res % i == 0)
      {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      break;
    res++;
  }
  return res;
}

HashTable::HashTable(int init_size, int maximum_probe_num,
                     ProbeMode probe_mode)
    : base_1_(37), base_2_(41), maximum_probe_num_(maximum_probe_num), probe_mode_(probe_mode), hash_table_size_(init_size), table_(new HashCell[init_size])
{
  for (int i = 0; i < init_size; i++)
  {
    table_[i].state = HashCellState::Empty;
    table_[i].student = nullptr;
  }
  if (probe_mode_ == ProbeMode::Linear)
  {
    probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size)
    {
      int p = (hash_value1 + num_probe) % hash_table_size;
      std::cout << "Probing for the position: " << p << std::endl;
      return p;
    };
  }
  else if (probe_mode_ == ProbeMode::Quadratic)
  {
    probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size)
    {
      int p = (hash_value1 + num_probe * num_probe) % hash_table_size;
      std::cout << "Probing for the position: " << p << std::endl;
      return p;
    };
  }
  else if (probe_mode_ == ProbeMode::DoubleHash)
  {
    probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size)
    {
      int p = (hash_value1 + num_probe * hash_value2) % hash_table_size;
      std::cout << "Probing for the position: " << p << std::endl;
      return p;
    };
  }
}

HashTable::~HashTable()
{ // Task 1
  // for (int i = 0; i < hash_table_size_; i++)
  // {
  //   delete table_[i].student;
  //   table_[i].student = nullptr;
  // }
  delete[] table_;
  table_ = nullptr;
}

 bool HashTable::add(const std::string &name, int score)
{ // Task 2 & 5
  int hash_value1 = hashFunction(name, base_1_, hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash)
  {
    hash_value2 = hashFunction(name, base_2_, hash_table_size_);
    if (hash_value2 == 0)
      hash_value2 = 1;
  }
  for (int i = 0; i < maximum_probe_num_; i++)
  {
    int hash_value = probe_func_(hash_value1, hash_value2, i, hash_table_size_);
    if (table_[hash_value].state == HashCellState::Active)
    {
      if (table_[hash_value].student->name() == name)
      {
        return false;
      }
    }
    else if (table_[hash_value].state == HashCellState::Empty || table_[hash_value].state == HashCellState::Deleted)
    {
      table_[hash_value].student = new Student(name, score);
      table_[hash_value].state = HashCellState::Active;
      return true;
    }
  }
  // return false;
  reHashUntilSuccess();
  return add(name, score);
}

int HashTable::search(const std::string &name) const
{ // Task 3
  int hash_value1 = hashFunction(name, base_1_, hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash)
  {
    hash_value2 = hashFunction(name, base_2_, hash_table_size_);
    if (hash_value2 == 0)
      hash_value2 = 1;
  }
  for (int i = 0; i < hash_table_size_; i++)
  {
    int hash_value = probe_func_(hash_value1, hash_value2, i, hash_table_size_);
    if (table_[hash_value].state == HashCellState::Active)
    {
      if (table_[hash_value].student->name() == name)
      {
        return table_[hash_value].student->score();
      }
    }
    else if (table_[hash_value].state == HashCellState::Empty)
    {
      return -1;
    }
    else if (table_[hash_value].state == HashCellState::Deleted)
    {
      continue;
    }
  }
  return -1;
}

bool HashTable::remove(const std::string &name)
{ // Task 4
  int hash_value1 = hashFunction(name, base_1_, hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash)
  {
    hash_value2 = hashFunction(name, base_2_, hash_table_size_);
    if (hash_value2 == 0)
      hash_value2 = 1;
  }
  for (int i = 0; i < hash_table_size_; i++)
  {
    int hash_value = probe_func_(hash_value1, hash_value2, i, hash_table_size_);
    if (table_[hash_value].state == HashCellState::Active)
    {
      if (table_[hash_value].student->name() == name)
      {
        delete table_[hash_value].student;
        table_[hash_value].student = nullptr;
        table_[hash_value].state = HashCellState::Deleted;
        return true;
      }
    }
    else if (table_[hash_value].state == HashCellState::Empty)
    {
      return false;
    }
  }
  return false;
}

void HashTable::reHashUntilSuccess()
{
  int next_hash_table_size = getNextHashTableSize(hash_table_size_);
  while (true)
  {
    if (reHash(next_hash_table_size))
    {
      return;
    }
    next_hash_table_size = getNextHashTableSize(next_hash_table_size);
  }
}

bool HashTable::reHash(int rehash_table_size)
{ // Task 5
  HashCell *new_table_ = new HashCell[rehash_table_size];
  for (int i = 0; i < rehash_table_size; i++)
  {
    new_table_[i].state = HashCellState::Empty;
    new_table_[i].student = nullptr;
  }
  for (int i = 0; i < hash_table_size_; i++)
  {
    if (table_[i].state == HashCellState::Active)
    {
      int hash_value1 = hashFunction(table_[i].student->name(), base_1_, rehash_table_size);
      int hash_value2 = 0;
      if (probe_mode_ == ProbeMode::DoubleHash)
      {
        hash_value2 = hashFunction(table_[i].student->name(), base_2_, rehash_table_size);
        if (hash_value2 == 0)
          hash_value2 = 1;
      }
      int j = 0;
      for (; j < maximum_probe_num_; j++)
      {
        int hash_value = probe_func_(hash_value1, hash_value2, j, rehash_table_size);
        if (new_table_[hash_value].state == HashCellState::Empty)
        {
          new_table_[hash_value].student = new Student(*table_[i].student);
          new_table_[hash_value].state = HashCellState::Active;
          break;
        }
      }
      if (j >= maximum_probe_num_)
      {
        // for (int k = 0; k < rehash_table_size; k++)
        // {
        //   if (new_table_[k].state == HashCellState::Active)
        //   {
        //     delete new_table_[k].student;
        //     new_table_[k].student = nullptr;
        //   }
        // }
        delete[] new_table_;
        new_table_ = nullptr;
        return false;
      }
    }
    else
      continue;
  }
  // for (int i = 0; i < hash_table_size_; i++)
  // {
  //   if (table_[i].state == HashCellState::Active)
  //   {
  //     delete table_[i].student;
  //     table_[i].student = nullptr;
  //   }
  // }
  delete[] table_;
  table_ = new_table_;
  hash_table_size_ = rehash_table_size;
  return true;
}

void HashTable::print() const
{
  std::cout << "hash_table_size:" << hash_table_size_ << std::endl;
  for (int i = 0; i < hash_table_size_; i++)
  {
    std::cout << i << ": state = ";
    if (table_[i].state == HashCellState::Empty)
    {
      std::cout << "Empty" << std::endl;
    }
    else if (table_[i].state == HashCellState::Deleted)
    {
      std::cout << "Deleted" << std::endl;
    }
    else if (table_[i].state == HashCellState::Active)
    {
      std::cout << "Active ";
      std::cout << "Student = (" << table_[i].student->name() << ", "
                << table_[i].student->score() << ")" << std::endl;
    }
  }
}
