
#include "dynamicarray.h"

#ifndef btree_H
#define btree_H
using namespace dynamicarray;
namespace binarytreename {


    template <typename T>
    struct node
    {
        T val;
        node<T>* child1;
        node<T>* child2;
        node(T value, node* parentptr);
        node(T value);
        bool hasleft();

        int numchildren();
        bool hasright();
        T remove();
        bool setleft(T value);
        bool setright(T value);
        node<T>* parent;
        void insertleft(T value);
        void insertright(T value);
    private:





    };

    template <typename T>
    class binarytree {


    public:
        node<T>* root;
        array<T> preorder();
        void appendleft(T value);
        void appendright(T value);
        void removerec(node<T>* curr, array<node<T>*> list);
        void remove(node<T>* start);
        void preorder(node<T>* curr, array<T>& list);

        binarytree(T value);
        ~binarytree();
    private:






    };



    template<typename T>
    bool node<T>::setleft(T value)
    {
        if (this != nullptr)
        {
            if (this->child1 == nullptr)
            {
                node<T>* newnode = new node<T>(value, this);
                this->child1 = newnode;

            }
            else
            {
                this->child1->val = val;
            }
            return true;
        }
        return false;

    }
    template<typename T>
    bool node<T>::setright(T value)
    {
        if (this != nullptr)
        {
            if (this->child2 == nullptr)
            {
                node<T>* newnode = new node<T>(value, this);
                this->child2 = newnode;

            }
            else
            {
                this->child2->val = val;
            }
            return true;
        }

        return false;

    }

    template<typename T>
    void node<T>::insertleft(T value)
    {
        if (child1 != nullptr)
        {
            node<T>* newnode = new node<T>(value, this);

            this->child1->parent = newnode;
            newnode->child1 = this->child1;
            this->child1 = newnode;

        }
        else
        {
            this->setleft(value);
        }

    }

    template<typename T>
    void node<T>::insertright(T value)
    {
        if (child2 != nullptr)
        {
            node<T>* newnode = new node<T>(value, this);

            this->child2->parent = newnode;
            newnode->child2 = this->child2;
            this->child2 = newnode;

        }
        else
        {
            this->setright(value);
        }
    }


    template<typename T>
    array<T> binarytree<T>::preorder()
    {

        array<T> list;
        preorder(root, list);
        return list;

    }

    template<typename T>
    void binarytree<T>::appendleft(T value)
    {

        node<T>* curr = root;
        while (true)
        {
            if (curr->child1 != nullptr)
            {
                curr = curr->child1;
            }
            else
            {
                curr->setleft(value);
                return;
            }
        }
    }
    template<typename T>
    void binarytree<T>::appendright(T value)
    {

        node<T>* curr = root;
        while (true)
        {
            if (curr->child2 != nullptr)
            {
                curr = curr->child2;
            }
            else
            {
                curr->setright(value);
                return;
            }
        }
    }
    template<typename T>
    void binarytree<T>::removerec(node<T>* curr, array<node<T>*> list) {


        list.append(curr);


        if (curr->hasleft())
        {

            removerec(curr->child1, list);


        }

        if (curr->hasright())
        {

            removerec(curr->child2, list);


        }



    }


    template<typename T>
    void binarytree<T>::remove(node<T>* start)
    {
        array<node<T>*> list;
        if (start->hasleft())
        {
            removerec(root->child1, list);
            start->child1 = nullptr;
        }
        if (start->hasright())
        {
            removerec(root->child2, list);
            start->child2 = nullptr;
        }

        delete[](list.data());
        start->remove();
    }

    template<typename T>
    void binarytree<T>::preorder(node<T>* curr, array<T>& list)
    {

        list.append(curr->val);

        if (curr->hasleft())
        {

            preorder(curr->child1, list);


        }

        if (curr->hasright())
        {

            preorder(curr->child2, list);


        }


    }
    template<typename T>
    binarytree<T>::binarytree(T val)
    {
        root = new node<T>(val, nullptr);
        root->child1 = nullptr;
        root->child2 = nullptr;


    }

    template<typename T>
    binarytree<T>::~binarytree()
    {
    }

    template<typename T>
    inline bool node<T>::hasleft()
    {
        if (this != nullptr && this->child1 != nullptr)
        {
            return true;
        }
        return false;
    }

    template<typename T>
    int node<T>::numchildren()
    {

        if (this->hasleft() && this->hasright())
        {
            return 2;
        }
        if (this->hasleft() ^ this->hasright())
        {
            return 1;
        }
        return 0;
    }

    template<typename T>
    inline bool node<T>::hasright()
    {
        if (this != nullptr && this->child2 != nullptr)
        {
            return true;
        }
        return false;
    }

    template<typename T>
    T node<T>::remove()
    {
        if (this != nullptr && this->parent != nullptr)
        {
            if (this->child1 == nullptr && this->child2 == nullptr)
            {

                if (this == this->parent->child1)
                {
                    parent->child1 = nullptr;

                }
                if (this == this->parent->child2)
                {
                    parent->child2 = nullptr;
                }


                delete this;

                return true;
            }




        }



        return false;
    }






    template<typename T>
    node<T>::node(T value, node* parentptr)
    {

        parent = parentptr;
        val = value;
        child1 = nullptr;
        child2 = nullptr;
    }

    template<typename T>
    node<T>::node(T value)
    {

        val = value;
    }

}
#endif // !btree_H
