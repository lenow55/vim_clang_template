#include "mlinput.h"
#include <fstream>

void correct_in(std::istream &in,
                int &val,
                const char *firstStr,
                unsigned int number,
                const char *errStr)
{
   bool correct{false};
   String strbuf{};
   cout << firstStr << number << "#:";
   while (!correct)
   {
      try
      {
         in >> strbuf;
         if (strbuf == ".")
            throw "end_of_root";
         val = strtoi(strbuf);
         correct = true;
      }
      catch (std::exception &exept)
      {
         cerr << errStr;
         strbuf.setchar('\0');
      }
   }
}

void correct_in(std::istream &in,
                float &val,
                const char *firstStr,
                unsigned int number,
                const char *errStr)
{
   bool correct{false};
   String strbuf{};
   cout << firstStr << number << "#:";
   while (!correct)
   {
      try
      {
         in >> strbuf;
         if (strbuf == ".")
            throw "end_of_root";
         val = strtof(strbuf);
         correct = true;
      }
      catch (std::exception &exept)
      {
         cerr << errStr;
         strbuf.setchar('\0');
      }
   }
}

void correct_in(std::istream &in, int *val)
{
   String strbuf{};
   in >> strbuf;
   if (strbuf == ".")
      throw "end";
   *val = strtoi(strbuf);
}

void correct_in(std::istream &in, float *val)
{
   String strbuf{};
   in >> strbuf;
   if (strbuf == ".")
      throw "end";
   *val = strtof(strbuf);
}

void correct_in(std::istream &in, int &val)
{
   String strbuf{};
   in >> strbuf;
   if (strbuf == ".")
      throw "end";
   val = strtoi(strbuf);
}

void correct_in(std::istream &in, float &val)
{
   String strbuf{};
   in >> strbuf;
   if (strbuf == ".")
      throw "end";
   val = strtof(strbuf);
}

void get_data(std::istream &in, my_queue<int *> &data_)
{
   String strbuf{};
   int *buf{};
   in >> strbuf;
   my_queue<String> str_data;
   str_data = separate(strbuf, " ");
   while (str_data.size() != 0)
   {
      try
      {
         if (str_data.front() == ".")
         {
            buf = nullptr;
            data_.push_back(buf);
         }
         else
         {
            buf = new int;
            *buf = strtoi(str_data.front());
            data_.push_back(buf);
            buf = nullptr;
         }
         str_data.pop_front();
      }
      catch (std::invalid_argument &ex)
      {
         delete buf;
         buf = nullptr;
         cout << ex.what() << endl;
         throw std::invalid_argument("Введите слой снова");
      }
   }
}

void getch(char &cc_char)
{
   {
      //тут не работает каконический режим
      TerminalOpt term;
      cin.get(cc_char); //получаем один символ
   }
}

my_queue<String> separate(String &in_str,
                          const char *delim)
{
   String strbuf = in_str;
   my_queue<String> output;
   String push_buf;
   const char *ctmp{};
   char *buf{strbuf.m_data()};
   ctmp = strtok(buf, delim);
   while (ctmp != nullptr)
   {
      push_buf = ctmp;
      output.push_back(push_buf);
      ctmp = strtok(NULL, delim);
   }
   return output;
}

void get_data(std::istream &in, my_queue<long> &data)
{
   cout << "Для выхода введите stop\n"
        << "Вводите номера в международном формате:\n";
   String strbuf = "";
   long buf{};
   in >> strbuf;
   while (strbuf != "stop")
   {
      try
      {
         buf = convert(strbuf);
         data.push_back(buf);
         in >> strbuf;
      }
      catch (std::invalid_argument &ex)
      {
         cout << ex.what() << endl;
         cout << "Повторите ввод: ";
         in >> strbuf;
      }
   }
}

void get_data(String &in, my_queue<long> &data)
{
   std::ifstream my_file(in.data(), my_file.in);
   if (!my_file.is_open())
      throw std::invalid_argument
      (
         "Неправильно задано имя файла"
      );
   char buf[20]{'\0'};
   long lbuf{};
   String strbuf;
   my_file.getline(buf, 15, ' ');
   while (!my_file.eof())
   {
      try
      {
         strbuf = buf;
         cout << strbuf;
         lbuf = convert(strbuf);
         data.push_back(lbuf);
         my_file.getline(buf, 15, ' ');
      }
      catch (std::invalid_argument &ex)
      {
         my_file.close();
         throw std::invalid_argument(ex.what());
      }
      catch (std::exception &ex)
      {
         my_file.close();
         throw std::invalid_argument(ex.what());
      }
   }
   my_file.close();
}

long convert(String &str_data)
{
   if (*(str_data.att(0)) != '+')
      throw std::invalid_argument
      (
         "Некорректный формат номера."
         " Вводите в международном формате"
      );
   const char *buf = str_data.att(1);
   String tmp(buf);
   if (tmp.size() != 11)
      throw std::invalid_argument
      (
         "Некорректный формат номера."
      );
   return strtol(tmp);
}
