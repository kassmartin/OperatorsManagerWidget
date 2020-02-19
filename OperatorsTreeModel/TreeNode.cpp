#include "TreeNode.hpp"

TreeNode::TreeNode(NodeType type, AbstractData *data, TreeNode *parent)
    : pNodeData(data), pParentNode(parent), pType(type)
{}

TreeNode::~TreeNode()
{
    qDeleteAll(pChildItems);
}

void TreeNode::appendChild(TreeNode *child)
{
    pChildItems.append(child);
}

TreeNode *TreeNode::child(int row)
{
    if (row < 0 || row >= pChildItems.size()) {
        return nullptr;
    }
    return pChildItems.at(row);
}

int TreeNode::childCount() const
{
    return pChildItems.count();
}

int TreeNode::columnCount() const
{
    return 1;
}

QString TreeNode::data() const
{
    return pNodeData->name;
}

AbstractData *TreeNode::dataPtr() const
{
    return pNodeData.get();
}

TreeNode *TreeNode::parentNode()
{
    return pParentNode;
}

TreeNode::NodeType TreeNode::type() const
{
    return pType;
}

int TreeNode::row() const
{
    if (pParentNode) {
        return pParentNode->pChildItems.indexOf(const_cast<TreeNode*>(this));
    }
    return 0;
}
