/* Fig.: plus.cpp
 * ============================================================================
 * Filename: plus.cpp
 * ============================================================================
 * Filename: plus.cpp
 * Abstract: Исполняемый модуль
 * Description: Оператор +
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

String operator+(const String &str1, const String &str2)
{
    size_t len1{str1.size()}, len2{str2.size()};
    char *temp = new char[len1 + len2 + _STANDART_CAPACITY_]{'\0'};
    size_t i{};
    const char *tempbuf{str1.data()};
    for (; i < len1; ++i)
    {
        temp[i] = tempbuf[i];
    }
    tempbuf = str2.data();
    for (size_t j{}; j < len2; ++j)
    {
        temp[i + j] = tempbuf[j];
    }
    tempbuf = nullptr;
    return String(*&temp); //возвращаю объект в стеке на основе семантики перемещения
}

String operator+(const String &str1, const char *str2)
{
    size_t len1{str1.size()}, len2{strlen(str2)};
    char *temp = new char[len1 + len2 + _STANDART_CAPACITY_]{'\0'};
    size_t i{};
    const char *tempbuf{str1.data()};
    for (; i < len1; ++i)
    {
        temp[i] = tempbuf[i];
    }
    tempbuf = nullptr;
    for (size_t j{}; j < len2; ++j)
    {
        temp[i + j] = str2[j];
    }
    return String(*&temp); //возвращаю объект в стеке на основе семантики перемещения
}

String operator+(const char *str1, const String &str2)
{
    size_t len1{strlen(str1)}, len2{str2.size()};
    char *temp = new char[len1 + len2 + _STANDART_CAPACITY_]{'\0'};
    const char *tempbuf{str2.data()};
    size_t i{};
    for (; i < len1; ++i)
    {
        temp[i] = str1[i];
    }
    for (size_t j{0}; j < len2; ++j)
    {
        temp[i + j] = tempbuf[j];
    }
    tempbuf = nullptr;
    return String(*&temp); //возвращаю объект в стеке на основе семантики перемещения
}

String operator+(const String &str1, char *str2)
{
    size_t len1{str1.size()}, len2{strlen(str2)};
    char *temp = new char[len1 + len2 + _STANDART_CAPACITY_]{'\0'};
    size_t i{};
    const char *tempbuf{str1.data()};
    for (; i < len1; ++i)
    {
        temp[i] = tempbuf[i];
    }
    tempbuf = nullptr;
    for (size_t j{}; j < len2; ++j)
    {
        temp[i + j] = str2[j];
    }
    return String(*&temp); //возвращаю объект в стеке на основе семантики перемещения
}

String operator+(char *str1, const String &str2)
{
    size_t len1{strlen(str1)}, len2{str2.size()};
    char *temp = new char[len1 + len2 + _STANDART_CAPACITY_]{'\0'};
    const char *tempbuf{str2.data()};
    size_t i{};
    for (; i < len1; ++i)
    {
        temp[i] = str1[i];
    }
    for (size_t j{0}; j < len2; ++j)
    {
        temp[i + j] = tempbuf[j];
    }
    tempbuf = nullptr;
    return String(*&temp); //возвращаю объект в стеке на основе семантики перемещения
}
