/* Fig.: b_tree
 * ======================================================
 * Filename: b_tree.h
 * ======================================================
 * Abstract: Заголовочный модуль
 * Description: Заголовочный файл бинарного дерева поиска
 * Creation Date: 2021/11/06
 * Copyright:(C)2020,2023.The Regents of the NNSTU
 * Author: Новиков Илья
 * Platform: Linux
/* ==================================================== */

#pragma once

#include "mlinput.h"
#include <utility>

//#define DEBUG_B_TREE_B_TREE

template <typename T>
class b_tree
{
   struct node;

public:
   b_tree();
   ~b_tree();
   size_t insert(const T &);
   bool remove(const T &);
   bool find(const T &);
   size_t insert(T &);
   bool remove(T &);
   bool find(T &);
   my_queue<T> pop_all_data();
   my_queue<T> get_all_data();
#ifdef DEBUG_HASH_TABLE
   std::ostream &operator<<(std::ostream &os,
                            b_tree<T> &tree)
#endif //DEBUG_HASH_TABLE
       private : size_t count_node{};
   node *root{};
   struct node // структура для представления узлов дерева
   {
      T data;
      unsigned char height;
      node *left;
      node *right;
      node(const T &);
      node(T &);
      ~node();
   };
   node *rotate_right(node *);
   node *rotate_left(node *);
   void fix_height(node *);
   int balance_factor(node *);
   unsigned char height(node *);
   node *balance(node *);
   node *add(node *, const T &);
   bool find(node *, const T &);
   void get_delete_data(node *, my_queue<T> &);
   void get_data(node *, my_queue<T> &);
   std::pair<node *, bool> remove(node *, const T &);
   std::pair<node *, node *> fr_min(node *);
};

template <typename T>
b_tree<T>::node::node(const T &val_): data(val_),
                                      height(1),
                                      left(nullptr),
                                      right(nullptr)
{
#ifdef DEBUG_B_TREE
   cout << "create b_tree node#" << this << endl;
#endif //DEBUG_B_TREE
}

template <typename T>
b_tree<T>::node::node(T &val_): data(val_),
                                height(1),
                                left(nullptr),
                                right(nullptr)
{
#ifdef DEBUG_B_TREE
   cout << "create b_tree node#" << this << endl;
#endif //DEBUG_B_TREE
}

template <typename T>
b_tree<T>::node::~node()
{
   if (left != nullptr)
   {
      delete left;
      // left = nullptr;
   }
   if (right != nullptr)
   {
      delete right;
      // right = nullptr;
   }
#ifdef DEBUG_B_TREE
   cout << "create b_tree node#" << this << endl;
#endif //DEBUG_B_TREE
}

template <typename T>
b_tree<T>::b_tree() : count_node(0), root(nullptr)
{
#ifdef DEBUG_B_TREE
   cout << "create b_tree#" << this << endl;
#endif //DEBUG_B_TREE
}

template <typename T>
b_tree<T>::~b_tree()
{
   if (count_node > 0)
      delete root;
   count_node = 0;
#ifdef DEBUG_B_TREE
   cout << "delete b_tree#" << this << endl;
#endif //DEBUG_B_TREE
}

template <typename T>
unsigned char b_tree<T>::height(node *node_)
{
   return node_ != nullptr ? node_->height : 0;
}

template <typename T>
int b_tree<T>::balance_factor(node *node_)
{
   return height(node_->right) - height(node_->left);
}

template <typename T>
void b_tree<T>::fix_height(node *node_)
{
   unsigned char height_left = height(node_->left);
   unsigned char height_right = height(node_->right);
   node_->height 
   = (
         height_left > height_right 
         ? height_left 
         : height_right
      ) + 1;
}

template <typename T>
typename b_tree<T>::node *b_tree<T>::add(node *node_,
                                         const T &data_)
{
   if (node_ == nullptr)
   {
      node *new_node = new node(data_);
#ifdef DEBUG_B_TREE
      cout << "insert b_tree node#" << new_node << endl;
#endif //DEBUG_B_TREE
      return new_node;
   }
   if (data_ < node_->data)
   {
      node_->left = add(node_->left, data_);
   }
   else
   {
      if (data_ > node_->data)
         node_->right = add(node_->right, data_);
      //для вставки нескольких одинаковых
      //элементов удалить эти две строки
      else             //data == node_->data       
         return node_; 
   }
   return balance(node_);
}

template <typename T>
std::pair<typename b_tree<T>::node *,
          bool> b_tree<T>::remove(node *node_,
                                  const T &data_)
{
   std::pair<node *, bool> result;
   if (node_ == nullptr)
      return std::make_pair(node_, false);
   if (data_ < node_->data)
   {
      result = remove(node_->left, data_);
      node_->left = result.first;
   }
   else if (data_ > node_->data)
   {
      result = remove(node_->right, data_);
      node_->right = result.first;
   }
   else //  k == p->data
   {
      node *left_ = node_->left;
      node_->left = nullptr;
      node *right_ = node_->right;
      node_->right = nullptr;
      delete node_;
#ifdef DEBUG_B_TREE
      cout << "delete b_tree node#" << node_ << endl;
#endif //DEBUG_B_TREE
      if (!right_)
         return std::make_pair(left_, true);
      std::pair<node *, node *> minim = fr_min(right_);
      minim.first->right = minim.second;
      minim.first->left = left_;
      return std::make_pair(balance(minim.first), true);
   }
   result.first = balance(node_);
   return result;
}

//балансировка дерева
template <typename T>
typename b_tree<T>::node *b_tree<T>::balance(node *node_)
{
   fix_height(node_);
   if (balance_factor(node_) == 2)
   {
      if (balance_factor(node_->right) < 0)
         node_->right = rotate_right(node_->right);
      return rotate_left(node_);
   }
   if (balance_factor(node_) == -2)
   {
      if (balance_factor(node_->left) > 0)
         node_->left = rotate_left(node_->left);
      return rotate_right(node_);
   }
   return node_; // балансировка не нужна
}

template <typename T>
std::pair<typename b_tree<T>::node *,
          typename b_tree<T>::node *>
          b_tree<T>::fr_min(node *node_)
{
   if (node_->left == 0)
   {
      return std::make_pair(node_, node_->right);
   }
   std::pair<node *, node *> result = fr_min(node_->left);
   node_->left = result.second;
   result.second = balance(node_);
   return result;
}

template <typename T>
size_t b_tree<T>::insert(T &data_)
{
   root = this->add(root, data_);
   count_node++;
#ifdef DEBUG_B_TREE
   cout << "insert b_tree#" << this << endl;
#endif //DEBUG_B_TREE
   return static_cast<size_t>(root->height());
}

template <typename T>
size_t b_tree<T>::insert(const T &data_)
{
   root = this->add(root, data_);
   count_node++;
#ifdef DEBUG_B_TREE
   cout << "insert b_tree#" << this << endl;
#endif //DEBUG_B_TREE
   return static_cast<size_t>(this->height(root));
}

template <typename T>
bool b_tree<T>::remove(T &data_)
{
   std::pair<node *, bool> result{};
   result = this->remove(root, data_);
   root = result.first;
   if (result.second == true)
   {
      --count_node;
      return true;
   }
   else
   {
      return false;
   }
}

template <typename T>
bool b_tree<T>::remove(const T &data_)
{
   std::pair<node *, bool> result{};
   result = this->remove(root, data_);
   root = result.first;
   if (result.second == true)
   {
      --count_node;
      return true;
   }
   else
   {
      return false;
   }
}

template <typename T>
bool b_tree<T>::find(T &data_)
{
   return find(root, data_);
}

template <typename T>
bool b_tree<T>::find(const T &data_)
{
   return find(root, data_);
}

template <typename T>
bool b_tree<T>::find(node *node_, const T &data_)
{
   if (node_ == nullptr)
      return false;
   if (data_ > node_->data)
      return find(node_->right, data_);
   else if (data_ < node_->data)
      return find(node_->left, data_);
   else //data_ = node_->data
      return true;
}

template <typename T>
my_queue<T> b_tree<T>::pop_all_data()
{
   my_queue<T> output_data;
   get_delete_data(root, output_data);
   root = nullptr;
   count_node = 0;
   return output_data;
}

template <typename T>
my_queue<T> b_tree<T>::get_all_data()
{
   my_queue<T> output_data;
   get_data(root, output_data);
   return output_data;
}

template <typename T>
void b_tree<T>::get_delete_data(node *node_,
                                my_queue<T> &out_data_)
{
   if (node_ == nullptr)
      return;
   get_delete_data(node_->left, out_data_);
   node_->left = nullptr;
   get_delete_data(node_->right, out_data_);
   node_->right = nullptr;
   out_data_.push_back(node_->data);
   delete node_;
}

template <typename T>
void b_tree<T>::get_data(node *node_,
                         my_queue<T> &out_data_)
{
   if (node_ == nullptr)
      return;
   get_data(node_->left, out_data_);
   get_data(node_->right, out_data_);
   out_data_.push_back(node_->data);
}

//левый поворот вокруг node_q
template <typename T>
typename b_tree<T>::node 
   *b_tree<T>::rotate_left(node *node_q) 
{
   node *node_p = node_q->right;
   node_q->right = node_p->left;
   node_p->left = node_q;
   fix_height(node_q);
   fix_height(node_p);
   return node_p;
}

//правый поворот вокруг node_q
template <typename T>
typename b_tree<T>::node 
   *b_tree<T>::rotate_right(node *node_q)
{
   node *node_p = node_q->left;
   node_q->left = node_p->right;
   node_p->right = node_q;
   fix_height(node_q);
   fix_height(node_p);
   return node_p;
}

#ifdef DEBUG_HASH_TABLE
template <typename T>
std::ostream &b_tree<T>::operator<<(std::ostream &os,
                                    b_tree<T> &tree)
{
   os << root << endl;
}
#endif //DEBUG_HASH_TABLE
