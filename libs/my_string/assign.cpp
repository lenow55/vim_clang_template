/* Fig.: assign.cpp
 * ============================================================================
 * Filename: assign.cpp
 * ============================================================================
 * Filename: assign.cpp
 * Abstract: Исполняемый модуль
 * Description: Оператор присвоения строкового контейнера
 * Creation Date: 2021/04/12
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

String &String::operator=(const String &obj)
{
    if (obj.buf == nullptr)
    {
        throw std::invalid_argument("Exception in operator=(const String &): arg = nullptr.");
    }
    size_t src_len = obj.len;
    if (src_len > capacity)
    {
        delete[] buf;
        buf = nullptr;
        buf = new char[src_len + _STANDART_AKKUMULATION_]{'\0'};
        strcpy_s(buf, src_len, obj.buf);
        len = src_len;
        capacity = src_len + _STANDART_AKKUMULATION_;
    }
    else
    {
        this->setchar('\0');
        strcpy_s(buf, src_len, obj.buf);
        len = src_len;
    }
    return *this;
}
String &String::operator=(const char *src)
{
    if (src == nullptr)
    {
        throw std::invalid_argument("Exception in operator=(const char *): arg = nullptr.");
    }
    size_t src_len = strlen(src);
    if (src_len > capacity)
    {
        delete[] buf;
        buf = new char[src_len + _STANDART_AKKUMULATION_]{'\0'};
        strcpy_s(buf, src_len, src);
        len = src_len;
        capacity = src_len + _STANDART_AKKUMULATION_;
    }
    else
    {
        this->setchar('\0');
        strcpy_s(buf, src_len, src);
        len = src_len;
    }
    return *this;
}

String &String::operator=(std::initializer_list<char> list)
{
    size_t _len{list.size()};
    if (capacity < _len)
    {
        delete[] buf;
        buf = new char[_len + _STANDART_AKKUMULATION_];
        capacity = _len + _STANDART_AKKUMULATION_;
    }
    this->setchar('\0');
    size_t i{};
    for (auto &element : list)
    {
        buf[i] = element;
        ++i;
    }
    len = _len;
    return *this;
}

String &String::operator=(char ch)
{
    this->setchar('\0');
    buf[0] = ch;
    len = 1U;
    return *this;
}

String &String::operator=(String &&src)
{
    if (&src == this)
        return *this;
    delete[] buf;
    std::swap(buf, src.buf);
    len = src.len;
    capacity = src.capacity;
    src.buf = new char[_STANDART_CAPACITY_]{'\0'};
    src.buf[0] = 0;
    src.len = 0;
    src.capacity = _STANDART_CAPACITY_;
#ifdef DEBUG_STRING
    cout << "move string: "<< src << ":to:" << this << endl;
#endif //DEBUG_STRING
    return *this;

}
