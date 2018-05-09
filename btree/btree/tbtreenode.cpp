#include "tbtreenode.h"


TBTreeNode::TBTreeNode(bool leaf) {
    this->Leaf = leaf;
}

size_t TBTreeNode::Size() {
    return this->items.GetSize();
}

TBTreeItem &TBTreeNode::operator[](size_t n) {
    return items[n];
}

TBTreeNode* TBTreeNode::LeftChild(size_t n) {
    return children[this->LCI(n)];
}

TBTreeNode* TBTreeNode::RightChild(size_t n) {
    return children[RCI(n)];
}

TBTreeItem TBTreeNode::Pop(size_t n) {
    auto l = this->LCI(n);
    auto r = this->RCI(n);

    children.Pop(l);
    children.Pop(r - 1);
    return items.Pop(n);
}

bool TBTreeNode::InsertBefore(TBTreeItem val, size_t n) {
    this->items.InsertBefore(val, n);
    this->children.InsertBefore(nullptr, this->LCI(n));
    this->children.InsertBefore(nullptr, this->RCI(n));
    return true;
}

size_t TBTreeNode::InsertInSorted(TBTreeItem ins) {
    size_t i = 0;
    for (auto it : items) {
        if (ins < it)
            break;
        ++i;
    }
    InsertBefore(ins, i);
    return i;
}

TBTreeNode* TBTreeNode::Split(bool leaf) {
    auto newRoot = new TBTreeNode(false);
    auto left    = new TBTreeNode(leaf);
    auto right   = this;
    right->Leaf  = leaf;

    const size_t n = (items.GetSize() % 2 == 1)
            ?   (items.GetSize() / 2)
            : ( (items.GetSize() - 1) / 2);
    left->items.TakeAway(items, 0, n);
    left->children.TakeAway(children, 0, n + 1);

    newRoot->InsertInSorted(this->Pop(0));
    newRoot->children[LCI(0)] = left;
    newRoot->children[RCI(0)] = right;

    return newRoot;
}

void TBTreeNode::SplitLeftChild(size_t n) {
    auto left     = new TBTreeNode(this->Leaf);
    auto right    = new TBTreeNode(this->Leaf);
    auto oldChild = this->children.Pop(LCI(n));

    const size_t nToTake = (items.GetSize() % 2 == 1)
            ?   (items.GetSize() / 2)
            : ( (items.GetSize() - 1) / 2);

    left->items.TakeAway(oldChild->items, 0, nToTake);
    left->children.TakeAway(oldChild->children, 0, nToTake + 1);

    this->InsertBefore(oldChild->Pop(0), n);

    right->items.TakeAway(oldChild->items, 0, nToTake);
    right->children.TakeAway(oldChild->children, 0, nToTake + 1);

    this->children.InsertBefore(left,  LCI(n));
    this->children.InsertBefore(right, RCI(n));
}


decltype(TBTreeNode::items.begin()) TBTreeNode::begin() {
    return items.begin();
}

decltype(TBTreeNode::items.end()) TBTreeNode::end() {
    return items.end();
}

size_t TBTreeNode::LCI(size_t item_index) {
    return item_index;
}

size_t TBTreeNode::RCI(size_t item_index) {
    return item_index + 1;
}
