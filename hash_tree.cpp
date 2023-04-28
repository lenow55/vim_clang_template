/* Fig.: hash_tree
 * ======================================================
 * Filename: hash_tree.cpp
 * =====================================================
 * Abstract: Основной исполняемый модуль 
 * лаборатоной по хеш таблицам
 * Description: Считывает номера и по хешам записывает
 * в таблицу, используя для решения коллизий 
 * дерево
 * Creation Date: 2021/11/06
 * Copyright:(C)2020,2023.The Regents of the NNSTU
 * Author: Новиков Илья
 * Platform: Linux
 * ======================================================
 * Nizhny Novgorod State Technical University
 * Educational and Scientific Institute of Radio 
 * Electronics and Information Technology
 * Department of Computing Systems and Technologies.
 * e-mail: vt@nntu.ru
 * =======================================================
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OF OR OTHER DEALINGS IN THE SOFTWARE.
 */
/* ==================================================== */
const char *help =
    "Командные символы:\n"
    "[A,a] - добавить элементы в таблицу\n"
    "[O,o] - добавить элементы в таблицу из файла\n"
    "[R,r] - удалить элемент из таблицы\n"
    "[F,f] - поиск по таблице\n"
    "[P,p] - вывести таблицу на экран\n"
    "[H,h] - вывести справку\n"
    "[E,e] - закончить выполнение\n";

#include "libs/mlinput.h"
#include "libs/hash_table.h"

int main()
{
   hash_table<long> h_table;
   my_queue<long> data;
   char controll_simbol{'h'};
   String strbuf{};
   bool result{};
   long find_d{};
   while (controll_simbol != 'e' && controll_simbol != 'E')
   {
      try
      {
         switch (controll_simbol)
         {
         case 'H':
         case 'h':
            cout << help;
            cout << "Введите контрольный символ: ";
            break;
         case 'A':
         case 'a':
            cout << endl;
            get_data(cin, data);
            h_table.push_data(data);
            data.clean();
            cout << "Введите контрольный символ: ";
            break;
         case 'O':
         case 'o':
            cout << "\nВведите путь до файла: ";
            cin >> strbuf;
            get_data(strbuf, data);
            h_table.push_data(data);
            data.clean();
            cout << "\nВведите контрольный символ: ";
            break;
         case 'F':
         case 'f':
            cout << "\nВведите номер поиска: ";
            cin >> strbuf;
            find_d = convert(strbuf);
            result = h_table.find(find_d);
            if (result)
               cout << "Номер есть в таблице\n";
            else
               cout << "Номера нет в таблице\n";
            cout << "Введите контрольный символ: ";
            break;
         case 'R':
         case 'r':
            cout << "\nВведите номер для удаления: ";
            cin >> strbuf;
            find_d = convert(strbuf);
            result = h_table.remove(find_d);
            if (result)
               cout << "Запись успешно удалена\n";
            cout << "Введите контрольный символ: ";
            break;
         case 'P':
         case 'p':
            cout << "\nСодержимое таблицы:\n";
            cout << h_table;
            cout << "Введите контрольный символ: ";
            break;
         default:
            controll_simbol = '\0';
            break;
         }
      }
      catch (std::invalid_argument &ex)
      {
         cout << ex.what() << endl;
      }
      catch (std::exception &ex)
      {
         cout << ex.what() << endl;
      }
      getch(controll_simbol);
   }
   cout << endl;
   return 0;
}

template <>
int hash_table<int>::hash(const int &value_)
{
   int value_2 = value_;
   value_2 *= value_2;
   value_2 >>= 11 - (size_coef / 2);
   return value_2 % capacity;
}

template <>
int hash_table<long>::hash(const long &value_)
{
   long value_2 = value_;
   value_2 *= value_2;
   value_2 >>= 11 - (size_coef / 2);
   return value_2 % capacity;
}
