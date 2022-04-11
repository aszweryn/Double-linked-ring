#pragma once
#include <iostream>
using namespace std;

template<typename Key, typename Info>
class Ring {
private:
    struct Node {
        Key key;
        Info info;
        Node *next;
        Node *back;
        Node(const Key& key, const Info& info, Node *next, Node *back)
                : key(key), info(info), next(next), back(back) {}
        Node(const Key& key, const Info& info) : key(key), info(info), next(this), back(this) {}
    };
    Node *head;
    Node *tail;
    int count;
    bool isFound(Node*& n, const Key& k, int occur = 1);

public:
    class iterator {
    private:
        friend class Ring<Key, Info>;
        explicit iterator(Node* itr);
        mutable Node* node;

    public:
        iterator();

        ~iterator() = default;

        iterator(const iterator& src);

        const iterator& operator++() const;

        iterator operator++(int) const;

        const iterator& operator--() const;

        iterator operator--(int) const;

        bool operator==(const iterator& itr) const;

        bool operator!=(const iterator& itr) const;

        Info& operator*();

        Info getInfo() const;

        Key getKey() const;

        void setKey(const Key& k);

        void setInfo(const Info& i);
    };


    Ring();

    Ring(const Ring &src);

    ~Ring();

    void clear();

    void print() const;

    void push_front(const Key& k, const Info& i);

    bool find(const Key& k, iterator& x, int occur);

    bool remove(const iterator& it);

    bool remove(const Key& k, int occur);

    bool insertAfter(const Key& where, const Key& what, const Info& info, int occur);

    iterator insertBefore(iterator position, const Key &key, const Info &info)
    {
        if(position.node == nullptr && head != nullptr)
            return position;

        Node *current = position.node;
        Node *newNode = new Node(key, info);

        if(head == nullptr) {
            head = new Node(key, info);
            position = iterator(newNode);
            return position;
        }
        newNode -> next = current;
        newNode -> back = current -> back;
        current -> back -> next = newNode;
        current -> back = newNode;
        return --position;
    };
};

template<typename Key, typename Info>
Ring<Key, Info>::Ring()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& src)
{
    if(src.first == nullptr)
        head = nullptr;
    else{
        head = new Ring(src.first -> next);
        Ring *current = head;
        Ring *srcFirst = src.first;
        Ring *currentSrc = srcFirst;
        while(currentSrc -> next != head) {
            current -> next = new Ring(currentSrc -> next -> next);
            currentSrc = currentSrc -> next;
            current = current -> next;
        }
        count = 0;
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::clear()
{
    if(head != nullptr) {
        Node *current = head;
        do {
            Node *temp = current;
            current = current -> next;
            delete temp;
        } while(current != head);
        tail = nullptr;
        head = nullptr;
        count = 0;
    }
}

template<typename Key, typename Info>
Ring<Key, Info>::~Ring()
{
    clear();
}

template<typename Key, typename Info>
bool Ring<Key, Info>::find(const Key& k, iterator& x, int occur)
{
    Node *temp = head;
    if(isFound(temp, k, occur) == true) {
        x = iterator(temp);
        return true;
    }
    return false;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::isFound(Node*& n, const Key& k, int occur)
{
    int x = 0;
    do {
        if(n -> key == k) {
            if(--occur == 0)
                return true;
            x++;
        }
        n = n -> next;
    } while(n != head && occur != 0);

    if(n != head && occur != 0) {
        int y = occur % x;
        if(y != 0)
            x = y;

        do {
            if(n -> key == k) {
                if(--x == 0)
                    return true;
            }
            n = n -> next;
        } while(n != head && x != 0);
    }
    return false;
}

template<typename Key, typename Info>
Ring<Key, Info>::iterator::iterator()
{
    node = nullptr;
}

template<typename Key, typename Info>
Ring<Key, Info>::iterator::iterator(Node *itr)
{
    node = itr;
}

template<typename Key, typename Info>
Info Ring<Key, Info>::iterator::getInfo() const
{
    return node -> info;
}

template<typename Key, typename Info>
Key Ring<Key, Info>::iterator::getKey() const
{
    return node -> key;
}

template<typename Key, typename Info>
Ring<Key, Info>::iterator::iterator(const iterator &src)
{
    node = src.node;
}

template<typename Key, typename Info>
const typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator++() const
{
    node = node -> next;
    return *this;
}

template<typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator++(int) const
{
    iterator it(*this);
    node = node -> next;
    return it;
}

template<typename Key, typename Info>
const typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator--() const
{
    node = node -> back;
    return *this;
}

template<typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator--(int) const
{
    iterator it(*this);
    node = node -> back;
    return it;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator==(const iterator& itr) const
{
    return node == itr.node;
};

template<typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator!=(const iterator& itr) const
{
    return node != itr.node;
}

template<typename Key, typename Info>
Info& Ring<Key, Info>::iterator::operator*()
{
    if(node == nullptr) cout << "Pointer doesn't exist!";
    return node -> info;
}

template<typename Key, typename Info>
void Ring<Key, Info>::iterator::setInfo(const Info &i)
{
    if(node) {
        node -> info = i;
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::iterator::setKey(const Key &k)
{
    if(node) {
        node -> key = k;
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::push_front(const Key& k, const Info& i)
{
    if(head == nullptr) {
        Node *newNode = new Node(k, i);
        head = newNode;
        tail = head;
    }
    else {
        Node *newNode = new Node(k, i, head, head -> back);
        head -> back -> next = newNode;
        head -> back = newNode;
        head = newNode;
    }
    count++;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::insertAfter(const Key &where, const Key &what, const Info &info, int occur)
{
    if(head == nullptr)
        push_front(what, info);

    if(occur < 1)
        return false;

    Node *curr = head;
    do {
        if(curr -> key == where) {
            Node *move = curr -> next;
            Node *newNode = new Node(what, info, curr, curr -> next);
            newNode -> next = move;
            newNode -> back = curr;
            curr -> next = newNode;
            move -> back = newNode;
        }
        curr = curr -> next;
    } while(curr != head);
    count++;
    return true;
}

template<typename Key, typename Info>
void Ring<Key, Info>::print() const
{
    if(head != nullptr) {
        Node *current = head;
        do {
            cout << "Key: " << current -> key << "   ";
            cout << "Info: " << current -> info << endl;
            current = current -> next;
        } while(current != head);
    }
    else {
        cout << "Ring is empty!" << endl;
    }
}

template<typename Key, typename Info>
bool Ring<Key, Info>::remove(const iterator &it)
{
    if(it.node == nullptr)
    {
        return false;
    }
    else {
        if(head -> next != head) {
            head = head -> next;
        }
        else {
            delete head;
            head = nullptr;
            tail = nullptr;
            return true;
        }
    }
    it.node -> back -> next = it.node -> next;
    it.node -> next -> back = it.node -> back;
    if(it.node == tail)
        tail = tail -> back;
    delete it.node;
    it.node = nullptr;
    count--;
    return true;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::remove(const Key &k, int occur) {
    Node *temp = head;
    if(head == nullptr)
        return false;

    do {
        if(temp -> key == k) {
            temp -> back -> next = temp -> next;
            temp -> next -> back = temp -> back;
            if(temp == tail)
                tail = tail -> back;
            delete temp;
            count--;
            return true;
        }
        else temp = temp -> next;

    } while (temp != head);
}