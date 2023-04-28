/* Fig.: my_queue.h
 * ============================================================================
 * Filename: my_queue.h
 * Abstract: Header module
 * Description: Блиблиотека с объявлением шаблона класса my_queue и его методами
 * Creation Date: 2021/09/14
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

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
//Макроопределения
//#define DEBUG_QUEUE


#ifdef DEBUG_QUEUE
#include <time.h>
#endif //DEBUG_QUEUE

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::setw;
//шаблон класса очередь
template <typename Q>
class my_queue
{
    private:
        //структура узла очереди
        struct node
        {
            Q data;
            node *next;
            node *previous;
            node(Q &val_): data(val_), next(nullptr), previous(nullptr)
            {
            #ifdef DEBUG_QUEUE
                cout << "create node" << this << endl;
            #endif //DEBUG_QUEUE
            }
            node(Q &&val_): data(std::move(val_)), next(nullptr), previous(nullptr){};
            ~node() = default;
        };
        void sort(node *, node *);
        void swap_node(node *, node *);

        node *head{nullptr};                    //указатель на начало очереди
        node *end{nullptr};                     //указатель на конец очереди
        size_t cout_node{};                     //количество элементов в очереди
    public:
        //класс итераторов для очереди
        class q_iterator
        {
            friend class my_queue<Q>;
            node *current_node;
            public:
                q_iterator(node *nod): current_node{nod} {};
                void operator++();
                void operator++(int);
                Q operator*();
                bool operator==(q_iterator);
                bool operator!=(q_iterator);
        };
        //конструкторы
        my_queue();
        my_queue(Q *, int);
        my_queue(my_queue<Q> &&);
        my_queue<Q> &operator=(my_queue<Q> &&);
        my_queue<Q> &operator=(my_queue<Q> &);
        //дестуктор
        ~my_queue();
        //вставки элементов
        void push_front(Q &);
        void push_back(Q &);
        void push_back(Q &&);
        void push(Q &, size_t);
        void push(Q &, my_queue<Q>::q_iterator&);
        //удаление элементов
        void pop_front();
        void pop_back();
        void pop(size_t);
        void pop(my_queue<Q>::q_iterator&);
        //очистка всей очереди
        void clean();
        //получение элементов очереди
        Q &front();
        Q &back();
        Q &get(size_t);
        //получение количества элементов очереди
        size_t size();
        size_t size() const;
        //сортировка элементов по возрастанию
        void sort();
        //получение итератора на начальный элемент
        q_iterator begin_i()
        {
            return q_iterator(head);
        }
        //получение итератора на конечный элемент
        q_iterator end_i()
        {
            return q_iterator(nullptr);
        }
        q_iterator set_i(size_t pos)
        {
            if(pos > cout_node)
                throw std::out_of_range("Попытка установить итератор на несуществующий элемент");
            if(pos == cout_node)
                return q_iterator(nullptr, 0);
            else
            {
                node *current_node = head;
                size_t i{0};
                for(; i < pos; i++)
                {
                    current_node = current_node->next;
                }
                return q_iterator(current_node, i);
            }
        }
};


template <typename Q>
my_queue<Q>::my_queue(): head(nullptr), end(nullptr), cout_node(0)
{
#ifdef DEBUG_QUEUE
    cout << "create queue" << this << endl;
#endif //DEBUG_QUEUE
}



template <typename Q>
my_queue<Q>::my_queue(Q *array, int count_) : my_queue<Q>()
{
    if(array == nullptr)
    {
        this->~my_queue<Q>();
        throw std::invalid_argument("Exception in construction(my_queue(array)): arg = nullptr.");
    }
    for(size_t i = 0; i < count_; i++)
        push_front(array[i]);

#ifdef DEBUG_QUEUE
    cout << "create queue" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
my_queue<Q>::~my_queue()
{
    this->clean();
#ifdef DEBUG_QUEUE
    cout << "delete queue" << this << endl;
#endif //DEBUG_QUEUE
    head = nullptr;
    end = nullptr;
}
//new feature
//        my_queue(std::initializer_list<Q>);
//        my_queue<Q> &operator=(std::initializer_list<Q>);
template <typename Q>
my_queue<Q>::my_queue(my_queue<Q> &&queue_)
{
    this->head = queue_.head;
    this->end = queue_.end;
    queue_.head = nullptr;
    queue_.end = nullptr;
    this->cout_node = queue_.cout_node;
    queue_.cout_node = 0;
}

template <typename Q>
my_queue<Q> &my_queue<Q>::operator=(my_queue<Q> &&queue_)
{
    this->clean();
    this->head = queue_.head;
    this->end = queue_.end;
    queue_.head = nullptr;
    queue_.end = nullptr;
    this->cout_node = queue_.cout_node;
    queue_.cout_node = 0;
#ifdef DEBUG_QUEUE
    cout << "move queue:" << &queue_ << ":to:" << this << endl;
#endif //DEBUG_QUEUE
    return *this;
}

template <typename Q>
my_queue<Q> &my_queue<Q>::operator=(my_queue<Q> &queue_)
{
    this->clean();
    auto i = queue_.begin_i();
    auto j = queue_.end_i();
    for(; i != j; i++)
        this->push_back(*i);
#ifdef DEBUG_QUEUE
    cout << "queue:" << &queue_ << ":assigmen to:" << this << endl;
#endif //DEBUG_QUEUE
    return *this;
}

template <typename Q>
void my_queue<Q>::push_front(Q &data_) //добавление элемента в начало очереди
{
    node *p_node = new node(data_);
    if (head == nullptr)
    {
        head = p_node;
        end = p_node;
    }
    else
    {
        head->previous = p_node;
        p_node->next = head;
        head = p_node;
    }
    cout_node++;                        //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "push_front node #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
void my_queue<Q>::push_back(Q &data_) //добавление элемента в конец очереди
{
    node *p_node = new node(data_);
    if (head == nullptr)
    {
        head = p_node;
        end = p_node;
    }
    else
    {
        end->next = p_node;
        p_node->previous = end;
        end = p_node;
    }
    cout_node++;                        //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "push_back node #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
void my_queue<Q>::push_back(Q &&data_) //добавление элемента в конец очереди
{
    node *p_node = new node(data_);
    if (head == nullptr)
    {
        head = p_node;
        end = p_node;
    }
    else
    {
        end->next = p_node;
        p_node->previous = end;
        end = p_node;
    }
    cout_node++;                        //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "push_back node #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
void my_queue<Q>::push(Q &data_, size_t num_place)  //вставка в произвольное место
{                                           //заметь! нумерация с нуля
    if (num_place == 0)                //частный случай вставки в начало
    {
        this->push_front(data_);
        return;
    }
    if (num_place == cout_node)       //частный случай вставки в конец
    {
        this->push_back(data_);
        return;
    }
    if(num_place > cout_node)               //проверка места вставки на валидность
    {
        throw std::invalid_argument("Exception in push metod: this place out_of_range.");
    }
    node *p_node = new node(data_);
    node *current_node{head};           //вспомогательная переменная
    for(size_t i{}; i < num_place; i++) //в цикле нахожу нужное место
    {
        current_node = current_node->next;
    }
    p_node->next = current_node;
    p_node->previous = current_node->previous;
    current_node->previous->next = p_node;
    current_node->previous = p_node;
    cout_node++;                            //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "node push in place #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template<typename Q>
void my_queue<Q>::push(Q &data_, my_queue<Q>::q_iterator &it)
{
                                           //заметь! нумерация с нуля
    if (it.current_node->previous == nullptr)                //частный случай вставки в начало
    {
        this->push_front(data_);
        return;
    }
    if (it.current_node == nullptr)       //частный случай вставки в конец
    {
        this->push_back(data_);
        return;
    }
    node *p_node = new node(data_);
    node *current_node{it.current_node};           //вспомогательная переменная
    p_node->next = current_node;
    p_node->previous = current_node->previous;
    current_node->previous->next = p_node;
    current_node->previous = p_node;
    cout_node++;                            //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "node push in place #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
void my_queue<Q>::pop_front()
{
    if (cout_node == 0)                 //если очередь пустая, то ничего не делаем
    {
#ifdef DEBUG_QUEUE
    cout << "queue is empty #queue:" << this << endl;
#endif //DEBUG_QUEUE
        return;
    }
#ifdef DEBUG_QUEUE
    cout << "delete #node:" << head << endl;
#endif //DEBUG_QUEUE
    if (cout_node == 1)
    {
        delete head;
        head = nullptr;
        end = nullptr;
    }
    else
    {
        node *del_node{head};           //вспомогательный указатель
        head->next->previous = nullptr; //для удаления элемента
        head = head->next;
        delete del_node;
    }
    cout_node--;                        //уменьшаем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "delete node #queue:" << this << endl;
#endif //DEBUG_QUEUE
}

template <typename Q>
void my_queue<Q>::pop_back()
{
    if (cout_node == 0)                      //если очередь пустая, то ничего не делаем
    {
#ifdef DEBUG_QUEUE
    cout << "queue is empty #queue:" << this << endl;
#endif //DEBUG_QUEUE
        return;
    }
    if (cout_node == 1)
    {
#ifdef DEBUG_QUEUE
    cout << "delete #queue:" << this << " #node:" << head << endl;
#endif //DEBUG_QUEUE
        delete end;
        head = nullptr;
        end = nullptr;
    }
    else
    {
        node *del_node{end};           //вспомогательный указатель
        end->previous->next = nullptr; //для удаления элемента
        end = end->previous;
#ifdef DEBUG_QUEUE
    cout << "delete #queue:" << this << " #node:" << del_node << endl;
#endif //DEBUG_QUEUE
        delete del_node;
        del_node = nullptr;
    }
    cout_node--;                        //уменьшаем счётчик элементов очереди
}

template <typename Q>
void my_queue<Q>::pop(size_t num_place)
{                                       //заметь! нумерация с нуля
    if (num_place == 0)                 //частный случай удаления с начала
    {
        this->pop_front();
        return;
    }
    if (num_place == cout_node)         //частный случай удалени с  конца
    {
        this->pop_back();
        return;
    }
    if(num_place > cout_node)           //проверка места вставки на валидность
    {
        throw std::invalid_argument("Exception in push metod: this place out_of_range.");
    }
    node *dell_node{head};           //вспомогательная переменная
    for(size_t i{}; i < num_place; i++) //в цикле нахожу нужное место
    {
        dell_node = dell_node->next;
    }
    dell_node->previous->next = dell_node->next;
    dell_node->next->previous = dell_node->previous;
    delete dell_node;
    cout_node--;                            //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "delete node #queue:" << this << endl;
#endif //DEBUG_QUEUE
}



template<typename Q>
void my_queue<Q>::pop(my_queue<Q>::q_iterator &it)
{
    if(it.current_node == nullptr)
        throw std::invalid_argument("Exception in push metod: this place out_of_range.");

    if (it.current_node->previous == nullptr)                 //частный случай удаления с начала
    {
        it++;
        this->pop_front();
        return;
    }
    if (it.current_node->next == nullptr)         //частный случай удалени с  конца
    {
        it++;
        this->pop_back();
        return;
    }
    node *dell_node{it.current_node};           //вспомогательная переменная
    it++;
    dell_node->previous->next = dell_node->next;
    dell_node->next->previous = dell_node->previous;
    delete dell_node;
    cout_node--;                            //увеличиваем счётчик элементов очереди
#ifdef DEBUG_QUEUE
    cout << "delete node #queue:" << this << endl;
#endif //DEBUG_QUEUE

}

template <typename Q>
void my_queue<Q>::clean()
{
    while (cout_node > 0)
        this->pop_back();
#ifdef DEBUG_QUEUE
    cout << "clean #queue:" << this << endl;
#endif //DEBUG_QUEUE

}
        //получение элементов очереди
template <typename Q>
Q &my_queue<Q>::front()
{
    return head->data;
}

template <typename Q>
Q &my_queue<Q>::back()
{
    return end->data;
}

template <typename Q>
Q &my_queue<Q>::get(size_t num_place)
{
    if(num_place == cout_node)
    {
        return this->back();
    }
    if(num_place > cout_node)           //проверка места доступа
    {
        throw std::invalid_argument("Exception in push metod: this place out_of_range.");
    }
    node *current_node{head};
    for(size_t i{0}; i < num_place; i++)
    {
        current_node = current_node->next;
    }
    return current_node->data;

}

template <typename Q>
size_t my_queue<Q>::size()
{
    return cout_node;
}

template <typename Q>
size_t my_queue<Q>::size() const
{
    return cout_node;
}

template<typename Q>
void my_queue<Q>::sort()
{
    if (cout_node < 2)
        return;
#ifdef DEBUG_QUEUE
    size_t t = clock();
#endif //DEBUG_QUEUE
    this->sort(head, end);
#ifdef DEBUG_QUEUE
    t = clock() - t;
    printf("time -> %f", (float)t/CLOCKS_PER_SEC);
#endif //DEBUG_QUEUE
}

template<typename Q>
void my_queue<Q>::sort(node *start_node, node *fin_node)
{
    node *start_iter{start_node->next};
    node *tmp_iter{start_iter};
    do
    {
        while((tmp_iter->previous != nullptr) && (tmp_iter->data < tmp_iter->previous->data))
        {
            this->swap_node(tmp_iter->previous, tmp_iter);
            tmp_iter = tmp_iter->previous;
        }
        start_iter = start_iter->next;
        tmp_iter = start_iter;
    }
    while (start_iter != fin_node && start_iter != nullptr);
}

template<typename Q>
void my_queue<Q>::swap_node(node *first_node, node *second_node)
{
    if (first_node == second_node)
        return;
    Q tmp  = first_node->data;
    first_node->data = second_node->data;
    second_node->data = tmp;
}


template<typename Q>
std::ostream &operator<<(std::ostream &os, my_queue<Q> &out_queue)
{
    auto j = out_queue.end_i();
    auto i = out_queue.begin_i();
    for(; i != j; i++)
        os << *i << endl;
    return os;
}


template<typename Q>
void my_queue<Q>::q_iterator::operator++()
{
    current_node = current_node->next;
}

template<typename Q>
void my_queue<Q>::q_iterator::operator++(int)
{
    current_node = current_node->next;
}

template<typename Q>
Q my_queue<Q>::q_iterator::operator*()
{
    return current_node->data;
}

template<typename Q>
bool my_queue<Q>::q_iterator::operator==(q_iterator nod_iter)
{
    return (current_node == nod_iter.current_node);
}

template<typename Q>
bool my_queue<Q>::q_iterator::operator!=(q_iterator nod_iter)
{
    return (current_node != nod_iter.current_node);
}

