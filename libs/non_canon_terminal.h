/* Fig.: non_canon_terminal.h
 * ============================================================================
 * Filename: non_canon_terminal.h
 * ============================================================================
 * Filename: non_canon_terminal.h
 * Abstract: Header module
 * Description: Блиблиотека с структурой, создание объекта которой переводит
 * терминал в неканонический режим
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
/* ======================================================================== */
#include <termios.h>
/* ======================================================================== */
struct TerminalOpt //структура, объект которой устанавливает неканонический режим
{
    TerminalOpt()
    {
        termios new_settings;                 //создание объекта новой конфигурации
        tcgetattr(0, &stored_settings);       //сохраняем текущие настройки
        new_settings = stored_settings;       //записываем в новую конфигурацию
                                              //текущие настройки
        new_settings.c_lflag &= (~ICANON);    //установка терминала в неканонический режим
        new_settings.c_lflag &= (~ECHO);      //отключение отображения символа
        new_settings.c_cc[VTIME] = 0;         //а вот этого я не знаю
        new_settings.c_cc[VMIN] = 1;          //установка символьного буфера равного 1
        tcsetattr(0, TCSANOW, &new_settings); //установка новой конфигурации для использования
        //Объект new_settings удалён при выходе из конструктора
    }
    ~TerminalOpt() //деструктор
    {
        tcsetattr(0, TCSANOW, &stored_settings); //устанавливает изначальные
                                                 //настройки терминала
    }
    termios stored_settings; //объект сохраняющий настройки по умолчанию
};

/* ======================================================================== */