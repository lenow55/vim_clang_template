/* Fig.: hash_table
 * ======================================================
 * Filename: hash_table.h
 * ======================================================
 * Abstract: Header module
 * Description: Блиблиотека с объявлением шаблона класса
 * hash_table и его методами
 * Creation Date: 2021/09/14
 * Copyright:(C)2020,2023.The Regents of the NNSTU
 * Author: Новиков Илья
 * Platform: Linux
 * ===================================================== */
#pragma once

#include "balanced_tree.h"
#include "my_queue.h"
#include <iomanip>
//Макроопределения
#define DEBUG_HASH_TABLE

#ifdef DEBUG_HASH_TABLE
#include <time.h>
#endif //DEBUG_HASH_TABLE

//шаблон класса очередь
template <typename H>
class hash_table
{
private:
   int size_coef = 3;               
   //коэффициент размера таблицы
   const double rehash_size = 0.25; 
   // коэффициент, при котором 
   // произойдет увеличение таблицы
   b_tree<H> *arr;                  
   // соответственно в массиве будут
   // хранится деревья поиска
   size_t size;                     
   // сколько элементов у нас сейчас в массиве
   size_t height;                   
   //показывает максимальное число коллизий
   size_t capacity;                 
   // размер самого массива, сколько памяти
   // выделено под хранение нашей таблицы
   int hash(const H &);
   void resize();

public:
   hash_table();
   ~hash_table();
   void add(H &);
   void add(const H &);
   bool remove(H &);
   bool find(H &);
   std::ostream &print_table(std::ostream &);
   void push_data(my_queue<H> &);
};

template <typename H>
hash_table<H>::hash_table()
{
   capacity = 1 << size_coef;
   size = 0;
   height = 0;
   arr = new b_tree<H>[capacity] {};
}

template <typename H>
hash_table<H>::~hash_table()
{
   delete[] arr;
   capacity = 0;
   size = 0;
}

template <typename H>
bool hash_table<H>::find(H &value_)
{
   if (arr[hash(value_)].find(value_) == true)
      return true;
   else
      return false;
}

template <typename H>
void hash_table<H>::add(H &value_)
{
   size_t height_ 
      = arr[this->hash(value_)].insert(value_);
   size++;
   if (float(height_) / float(size) > rehash_size)
   {
      this->resize();
   }
#ifdef DEBUG_HASH_TABLE
   for (size_t i{}; i < capacity; i++)
      cout << arr[i];
#endif //DEBUG_HASH_TABLE
}

template <typename H>
void hash_table<H>::add(const H &value_)
{
   size_t height_ 
      = arr[this->hash(value_)].insert(value_);
   size++;
   height = height_;
   if (float(height_)/float(capacity) > rehash_size)
   {
      this->resize();
   }
}

template <typename H>
bool hash_table<H>::remove(H &value_)
{
   return arr[this->hash(value_)].remove(value_);
}

template <typename H>
void hash_table<H>::resize()
{
   ++size_coef;
   size_t new_capacity = 1 << size_coef;
   b_tree<H> *new_arr = new b_tree<H>[new_capacity];
   my_queue<H> data_buf;
   for (size_t i{}; i < capacity; i++)
   {
      data_buf = arr[i].pop_all_data();
      for (
            auto it = data_buf.begin_i();
            it != data_buf.end_i();
            it++
         )
         this->height 
            = new_arr[this->hash(*it)].insert(*it);
   }
   delete[] arr;
   arr = new_arr;
   capacity = new_capacity;
   new_arr = nullptr;
}

template <typename H>
std::ostream &operator<<(std::ostream &os,
                         hash_table<H> &table)
{
   table.print_table(os);
   return os;
}

template <typename H>
std::ostream &hash_table<H>::print_table(std::ostream &os)
{
   my_queue<H> out_data;
   for (size_t i{}; i < capacity; i++)
   {
      out_data = arr[i].get_all_data();
      out_data.sort();
      auto it = out_data.begin_i();
      auto et = out_data.end_i();
      for (; it != et; it++)
      {
         os << "+" << std::setw(11) << *it << endl;
      }
   }
   return os;
}

template <typename H>
void hash_table<H>::push_data(my_queue<H> &data)
{
   auto i = data.begin_i();
   auto j = data.end_i();
   for (; i != j; i++)
      this->add(*i);
}
