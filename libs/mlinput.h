#pragma once
#include "my_string/String.h"
#include "non_canon_terminal.h"
#include "my_queue.h"

void correct_in(std::istream &, int &,
                const char *, unsigned int,
                const char *);
void correct_in(std::istream &, float &,
                const char *,
                unsigned int,
                const char *);
void correct_in(std::istream &, float &);
void correct_in(std::istream &, int &);
void correct_in(std::istream &, float *);
void correct_in(std::istream &, int *);
void get_data(std::istream &, my_queue<int *> &);
void getch(char &);
void get_data(std::istream &, my_queue<long> &);
void get_data(String &, my_queue<long> &);
long convert(String &);
my_queue<String> separate(String &, const char *);

template <typename Type> //функция корректного ввода
Type correctInput(const char *firstStr,
                  const char *errStr,
                  const char term_simbol = '\n',
                  bool (*comp)(Type n) = nullptr
                  )
{
   if (comp == nullptr)
      comp = [](Type n)
      { return true; }; // nullptr - default

   Type result;
   std::cout << firstStr;

   // Correct input...
   while (
            !(std::cin >> result) 
            || (std::cin.peek() != term_simbol) 
            || !comp(result)
         )
   {
      std::cin.clear();
      std::cin.ignore
      (
         std::numeric_limits<std::streamsize>::max(),
         '\n'
      );
      std::cout << errStr;
   }
   std::cin.clear();
   std::cin.ignore
   (
      std::numeric_limits<std::streamsize>::max(),
      term_simbol
   );
   return result;
}

template <typename Q> //функция корректного ввода
void dell_ptr_queue(my_queue<Q> &queue_)
{
   auto i = queue_.begin_i();
   auto j = queue_.end_i();
   for (; i != j; i++)
      delete *i;
}
