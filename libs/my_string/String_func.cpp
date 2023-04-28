/* Fig.: String_func.cpp
 * ============================================================================
 * Filename: String_func.cpp
 * ============================================================================
 * Filename: String_func.cpp
 * Abstract: Исполняемый модуль
 * Description: Конструкторы-деструкторы + другие функции класса String
 * Creation Date: 2021/03/12
 * Copyright: (C) 2020, 2023. The Regents of the NNSTU n.a. R.E. Alekseev.
 * Author: Новиков Илья
 * Platform: Linux
 * ============================================================================
 * Nizhny Novgorod State Technical University n.a. R.E. Alekseev (NNSTU)
 * Educational and Scientific Institute of Radio Electronics
 * and Information Technology
 * Department of Computing Systems and Technologies.
 * e-mail: vt@nntu.ru
 * ============================================================================
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/* ======================================================================== */

#include "String.h"

//========================
//КОН(ДЕ)СТРУКТОРЫ_STRING==============================================
String::String() //конструктор string без парамметров
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    buf = new char[_STANDART_CAPACITY_]{'\0'};
    len = 0;
    capacity = _STANDART_CAPACITY_;
}

String::~String() //деструктор string
{
#ifdef DEBUG_STRING
    cout << "delete " << this << endl;
#endif //DEBUG_STRING
    delete[] buf;
    buf = nullptr;
    len = 0;
    capacity = 0;
}

String::String(const char *src)
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    size_t src_len{strlen(src)};
    buf = new char[src_len + _STANDART_AKKUMULATION_]{'\0'};
    strcpy_s(buf, src_len, src);
    len = src_len;
    capacity = src_len + _STANDART_AKKUMULATION_;
}

String::String(const String &src)
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    if (src.buf == nullptr)
    {
        this->~String();
        throw std::invalid_argument("Exception in construction(String&): arg = nullptr.");
    }
    if (src.len > _STANDART_CAPACITY_)
    {
        buf = new char[src.len + _STANDART_AKKUMULATION_]{'\0'};
        strcpy_s(buf, src.len, src.buf);
        len = src.len;
        capacity = src.len;
    }
    else
    {
        buf = new char[_STANDART_CAPACITY_]{'\0'};
        strcpy_s(buf, src.len, src.buf);
        len = src.len;
        capacity = _STANDART_CAPACITY_;
    }
}

String::String(String &&src)
{
    if (&src == this)
    {
    }
    else
    {
        std::swap(buf, src.buf);
        //Возможны два варианта проверить позже
        std::swap(capacity, src.capacity);
        std::swap(len, src.len);
        //len = src.len;
        //capacity = src.capacity;
        src.buf = new char[_STANDART_CAPACITY_];
        src.buf[0] = 0;
        //src.len = 0;
        //src.capacity = _STANDART_CAPACITY_;
#ifdef DEBUG_STRING
    cout << "move string:" << &src << ":to:" << this << endl;
#endif //DEBUG_STRING
    }
}

String::String(char *&str)
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    delete[] buf;
    buf = nullptr;
    size_t stlen = strlen(str);
    std::swap(buf, str);
    len = stlen;
    capacity = stlen;
    delete[] str;
}

String::String(int &value): String()
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    buf[0] = value;
    len = 1;
}

String::String(unsigned int &value): String()
{
#ifdef DEBUG_STRING
    cout << "create string" << this << endl;
#endif //DEBUG_STRING
    buf[0] = value;
    len = 1;
}


//END_КОН(ДЕ)СТРУКТОРЫ_STRING==============================================

size_t String::size()
{
    return len;
}

size_t String::size() const
{
    return len;
}

const char *String::data() const
{
    if (buf == nullptr)
        throw std::invalid_argument("Exception in function data(): arg = nullptr.");
    return buf;
}

char *String::m_data()
{
    if (buf == nullptr)
        throw std::invalid_argument("Exception in function data(): arg = nullptr.");
    return buf;
}

const char *String::att(int point) const
{
    if (point < 0 || point > static_cast<int>(capacity) - 1)
    {
        throw std::out_of_range("att() out of range");
    }
    if (buf == nullptr)
    {
        throw std::invalid_argument("att() invalid argument");
    }

    return &this->buf[point];
}

const char *String::att(int point)
{
    if (point < 0 || point > static_cast<int>(capacity) - 1)
    {
        throw std::out_of_range("att() out of range");
    }
    if (buf == nullptr)
    {
        throw std::invalid_argument("att() invalid argument");
    }

    return &this->buf[point];
}

void String::setchar(char ch)
{
    for (size_t i{}; i < capacity; i++)
    {
        buf[i] = ch;
    }
}

void String::set(const char *src)
{
    if (src == nullptr)
    {
        throw std::invalid_argument("Exception in function set(): arg = nullptr.");
    }
    size_t src_len = strlen(src) + 1;
    if (src_len > capacity)
    {
        delete[] buf;
        buf = new char[src_len + _STANDART_AKKUMULATION_]{'\0'};
        strcpy_s(buf, src_len, src);
        len = src_len - 1;
        capacity = src_len + _STANDART_AKKUMULATION_;
    }
    else
    {
        this->setchar('\0');
        strcpy_s(buf, src_len, src);
        len = src_len - 1;
    }
}

std::ostream &operator<<(std::ostream &out, const String &obj)
{
    if (obj.data() == nullptr)
        throw std::invalid_argument("Exception in operator<<: arg = nullptr.");
    out << obj.data();
    return out;
}
std::istream &operator>>(std::istream &in, String &obj)
{
    if (obj.data() == nullptr)
        throw std::invalid_argument("Exception in operator<<: arg = nullptr.");
    std::streamsize n = 60;
    char _buf[n];
    in.getline(_buf, n - 1);
    _buf[n - 1] = '\0';
    obj.set(_buf);
    return in;
}

void strcpy_s(char *dest, size_t len, const char *src)
{
    if (dest == nullptr || src == nullptr)
        throw std::invalid_argument("Exception in function strcpy_s: arg = nullptr.");
    if (len == 0)
        return;
    for (size_t i{0}; i < len + 1; i++)
    {
        dest[i] = src[i];
    }
}

size_t strtoi(String &str)
{
    const size_t buf = std::stoi(str.data());
    return buf;
}

long strtol(String &str)
{
    long buf = std::stol(str.data());
    return buf;
}
float strtof(String &str){
    const float buf = std::stof(str.data());
    return buf;
}
