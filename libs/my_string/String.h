/* Fig.: String.h
 * ============================================================================
 * Filename: String.h
 * ============================================================================
 * Filename: String.h
 * Abstract: Header module
 * Description: Блиблиотека с объявлением класса String и его методами
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
#pragma once
//#define DEBUG_STRING
/*МАКРООПРЕДЕЛЕНИЯ ======================================================== */

/* ======================================================================== */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <limits>
#include <exception>
#include <iomanip>

#define _STANDART_CAPACITY_ 64
#define _STANDART_AKKUMULATION_ 8
#define LEN_INT64 20

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class String
{
private:
    char *buf{nullptr};
    size_t capacity{};
    size_t len{};

public:
    String();
    ~String();
    String(const char *);
    String(const String &);
    String(String &&);
    String(char *&);
    String(int &);
    String(unsigned int &);
    String &operator=(const String &);
    String &operator=(const char *);
    String &operator=(std::initializer_list<char>);
    String &operator=(const char);
    String &operator=(String &&);
    void set(const char *);
    void setchar(char);
    const char *data() const;
    char *m_data();
    size_t size();
    size_t size() const;
    const char *att(int) const;
    const char *att(int);
};

size_t strtoi(String &);
long strtol(String &);
float strtof(String &);

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
String operator+(const String &, char*);
String operator+(char*, const String &);
//String operator+(const String &, int &);

bool operator==(const String &, const String &);
bool operator==(const String &, const char *);
bool operator==(const char *, const String &);
bool operator==(const String &, char*);
bool operator==(char*, const String &);

bool operator!=(const String &, const String &);
bool operator!=(const String &, const char *);
bool operator!=(const char *, const String &);
bool operator!=(const String &, char*);
bool operator!=(char*, const String &);

bool operator>(const String &, const String &);
bool operator>(const String &, const char *);
bool operator>(const char *, const String &);
bool operator>(const String &, char*);
bool operator>(char*, const String &);

bool operator<(const String &, const String &);
bool operator<(const String &, const char *);
bool operator<(const char *, const String &);
bool operator<(const String &, char*);
bool operator<(char*, const String &);

std::ostream &operator<<(std::ostream &, const String &);
std::istream &operator>>(std::istream &, String &);

void strcpy_s(char *, size_t, const char *);

