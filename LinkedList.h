#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <cstddef>

class LinkedList
{
public:
    typedef int                ValueType;
    typedef std::size_t        SizeType;
    typedef ValueType&         Reference;
    typedef const ValueType&   ConstReference;
    typedef ValueType*         Pointer;
    typedef const Pointer      ConstPointer;
    typedef LinkedListIterator Iterator;
    typedef const LinkedListIterator ConstIterator;

private:
    Node*    FHead;
    Node*    FTail;
    SizeType FSize;
    Iterator FBegin;
    Iterator FEnd;

public:
    LinkedList();
    LinkedList(const LinkedList& AOther);
    LinkedList(LinkedList&& AOther);
    ~LinkedList();

private:
    void Copy(const LinkedList& AOther);

public:
    LinkedList& operator=(const LinkedList& ARhs);
    LinkedList& operator=(LinkedList&& ARhs);
    void Assign(SizeType ACount, const ValueType& AValue);

public:
    Iterator Begin();
    ConstIterator Begin() const;
    Iterator End();
    ConstIterator End() const;
    
public:
    bool Empty() const;
    SizeType Size() const;
    
public:
    void Clear();
    void Insert(Iterator APos, const ValueType& AValue);
    void Erase(Iterator APos);
    void PushBack(const ValueType& AValue);
    void PushFront(const ValueType& AValue);
    void PopBack();
    void PopFront();

public:
    void Reverse();
};

struct Node
{
public:
    LinkedList::ValueType Value;
    Node*                 Prev;
    Node*                 Next;

public:
    Node(LinkedList::ValueType AValue = LinkedList::ValueType(), 
            Node*              APrev  = nullptr, 
            Node*              ANext  = nullptr)
            : Value(AValue)
            , Prev(APrev)
            , Next(ANext)
    {}
};

class LinkedListIterator
{
friend LinkedList;
private:
    Node* FData;
    
private:
    LinkedListIterator(Node* AData = nullptr)
        : FData(AData)
    {}

public:
    bool operator==(LinkedListIterator AIter) const { return FData == AIter.FData; }
    bool operator!=(LinkedListIterator AIter) const { return !(*this == AIter); }
    
    LinkedListIterator& operator++()
    {
        FData = FData->Next;
        return *this;
    }

    LinkedListIterator operator++(int)
    {
        LinkedListIterator tmp = *this;
        FData = FData->Next;
        return tmp;
    }

    LinkedListIterator& operator--()
    {
        FData = FData->Prev;
        return *this;
    }

    LinkedListIterator operator--(int)
    {
        LinkedListIterator tmp = *this;
        FData = FData->Prev;
        return tmp;
    }

    int& operator*()             { return FData->Value; }
    const int& operator*() const { return FData->Value; }

    int* operator->()             { return &(FData->Value); }
    const int* operator->() const { return &(FData->Value); }
};
    

#endif