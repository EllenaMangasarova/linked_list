#include "LinkedList.h"

LinkedList::LinkedList()
    : FHead(nullptr)
    , FTail(new Node())
    , FSize(0)
    , FBegin(FTail)
    , FEnd(FTail)
{
    FHead = FTail;
}

LinkedList::LinkedList(const LinkedList& AOther)
    : FHead(nullptr)
    , FTail(new Node())
    , FSize(AOther.FSize)
{
    FHead = FTail;
    Copy(AOther);
}

LinkedList::LinkedList(LinkedList&& AOther)
    : FHead(AOther.FHead)
    , FTail(AOther.FTail)
    , FSize(AOther.FSize)
    , FBegin(AOther.FBegin)
    , FEnd(AOther.FEnd)
{
    AOther.FHead = nullptr;
    AOther.FTail = nullptr;
    AOther.FSize = 0;
    AOther.FBegin = nullptr;
    AOther.FEnd = nullptr;
}

LinkedList::~LinkedList()
{
    Clear();

    if (FTail) {
        delete FTail;
    }
}

void LinkedList::Copy(const LinkedList& AOther)
{
    Clear();

    if (AOther.Empty()) { return; }

    Node* oth_node = AOther.FHead;
    FHead = new Node(oth_node->Value, nullptr, FTail);
    Node* node = FHead;
    oth_node = oth_node->Next;

    for (auto it = AOther.Begin(); it != AOther.End(); ++it) {
        node->Next = new Node(*it, node, FTail);
    }

    FBegin = Iterator(FHead);
    FEnd   = Iterator(FTail);
    FSize  = AOther.Size();
}

LinkedList& LinkedList::operator=(const LinkedList& ARhs)
{
    if (this == &ARhs) { return *this; }

    Copy(ARhs);
}

LinkedList& LinkedList::operator=(LinkedList&& ARhs)
{
    if (this == &ARhs) { return *this; }

    FHead = ARhs.FHead;
    ARhs.FHead = nullptr;
    
    FTail = ARhs.FTail;
    ARhs.FTail = nullptr;
    
    FSize = ARhs.FSize;
    ARhs.FSize = 0;
    
    FBegin = ARhs.FBegin;
    ARhs.FBegin = nullptr;
    
    FEnd = ARhs.FEnd;
    ARhs.FEnd = nullptr;
}

void LinkedList::Assign(LinkedList::SizeType ACount, const LinkedList::ValueType& AValue)
{
    Clear();
    
    while (ACount--)
    {
        PushBack(AValue);
    }
}

LinkedList::Iterator LinkedList::Begin()
{
    return FBegin;
}

LinkedList::ConstIterator LinkedList::Begin() const
{
    return FBegin;
}

LinkedList::Iterator LinkedList::End()
{
    return FEnd;
}
    
LinkedList::ConstIterator LinkedList::End() const
{
    return FEnd;
}

bool LinkedList::Empty() const
{
    return Begin() == End();
}

LinkedList::SizeType LinkedList::Size() const
{
    return FSize;
}

void LinkedList::Clear()
{
    if (Empty()) { return; }

    Node* node = FHead;
    while (node != FTail) {
        Node* tmp = node->Next;
        delete node;
        node = tmp;
    }
    FHead  = FTail;
    FSize  = 0;
    FBegin = FTail;
    FEnd   = FTail;
}

void LinkedList::Insert(LinkedList::Iterator APos, const LinkedList::ValueType& AValue)
{
    if (APos == End()) { return; }
    
    Node* node = APos.FData;
    Node* n_node = new Node(AValue, node->Prev, node);

    if (n_node->Prev) {
        n_node->Prev->Next = n_node;
    }
    else {
        FHead = n_node;
        FBegin = Iterator(FHead);
    }

    n_node->Next->Prev = n_node;
}

void LinkedList::Erase(LinkedList::Iterator APos)
{
    if (Empty())       { return; }
    if (APos == End()) { return; }

    Node* node = APos.FData;
    if (node->Prev) {
        node->Prev->Next = node->Next;
    }
    else {
        FHead  = node->Next;
        FBegin = Iterator(FHead);
    }

    node->Next->Prev = node->Prev;

    delete node;
}

void LinkedList::PushBack(const LinkedList::ValueType& AValue)
{
    Node* tmp = new Node(AValue, FTail->Prev, FTail);
    if (FTail->Prev) {
        FTail->Prev->Next = tmp;
    }
    else {
        FHead  = tmp;
        FBegin = Iterator(FHead);
    }
    FTail->Prev = tmp;
    ++FSize;
}

void LinkedList::PushFront(const LinkedList::ValueType& AValue)
{
    Node* tmp = new Node(AValue, nullptr, FHead);
    if (Empty()) {
        FHead = tmp;
        FTail->Prev = FHead;
    }
    else {
        FHead->Prev = tmp;
        FHead = tmp;
    }
    FBegin = Iterator(FHead);
    ++FSize;
}

void LinkedList::PopBack()
{
    if (Empty()) { return; }

    Node* tmp = FTail->Prev;
    FTail->Prev = tmp->Prev;
    FTail->Prev->Next = FTail;
    delete tmp;
    --FSize;
}

void LinkedList::PopFront()
{
    if (Empty()) { return; }

    Node* tmp = FHead;
    FHead = tmp->Next;
    FHead->Prev = nullptr;
    delete tmp;

    FBegin = Iterator(FHead);
    --FSize;
}

// void LinkedList::Reverse();