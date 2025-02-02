#ifndef RBT_H_
#define RBT_H_

template<typename T>
class RBT
{
private:
    struct Node
    {
        enum Color { Red, Black };

        T value;
        Node *left{};
        Node *right{};
        Node *parent{};
        Color color{Red};
    };



private:
    Node *root_{};
};

#endif // RBT_H_