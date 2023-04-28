/* Fig.: less.cpp
 * ============================================================================
 * Filename: less.cpp
 * ============================================================================
 * Filename: less.cpp
 * Abstract: Исполняемый модуль
 * Description: Оператор < 
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

bool operator<(const String &str1, const String &str2)
{
    if (str1.data() == nullptr || str2.data() == nullptr)
        throw std::invalid_argument("Exception in operator<(const String, const String): arg = nullptr.");
    size_t len1{str1.size()}, len2{str2.size()};
    const char *_s1 = str1.data();
    const char *_s2 = str2.data();
    if (len1 > len2)
    {
        return false;
    }
    if (len1 < len2)
    {
        return true;
    }
    if (strncmp(_s1, _s2, len1) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(const String &str1, const char *str2)
{
    if (str1.data() == nullptr || str2 == nullptr)
        throw std::invalid_argument("Exception in operator<(const String, const char): arg = nullptr.");
    size_t len1{str1.size()}, len2{strlen(str2)};
    const char *_s1 = str1.data();
    if (len1 > len2)
    {
        return false;
    }
    if (len1 < len2)
    {
        return true;
    }
    if (strncmp(_s1, str2, len1) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(const char *str1, const String &str2)
{
    if (str1 == nullptr || str2.data() == nullptr)
        throw std::invalid_argument("Exception in operator<(const char, const String): arg = nullptr.");
    size_t len1{strlen(str1)}, len2{str2.size()};
    const char *_s2 = str2.data();
    if (len1 > len2)
    {
        return false;
    }
    if (len1 < len2)
    {
        return true;
    }
    if (strncmp(str1, _s2, len1) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(const String &str1, char *str2)
{
    if (str1.data() == nullptr || str2 == nullptr)
        throw std::invalid_argument("Exception in operator<(const String, char): arg = nullptr.");
    size_t len1{str1.size()}, len2{strlen(str2)};
    const char *_s1 = str1.data();
    const char *_s2 = const_cast<const char *>(str2);
    if (len1 > len2)
    {
        return false;
    }
    if (len1 < len2)
    {
        return true;
    }
    if (strncmp(_s1, _s2, len1) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(char *str1, const String &str2)
{
    if (str1 == nullptr || str2.data() == nullptr)
        throw std::invalid_argument("Exception in operator<(char, const String): arg = nullptr.");
    size_t len1{strlen(str1)}, len2{str2.size()};
    const char *_s1 = const_cast<const char *>(str1);
    const char *_s2 = str2.data();
    if (len1 > len2)
    {
        return false;
    }
    if (len1 < len2)
    {
        return true;
    }
    if (strncmp(_s1, _s2, len1) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}