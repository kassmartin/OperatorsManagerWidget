#include "TreeNode.hpp"

TreeNode::TreeNode(NodeType type, AbstractData *data, TreeNode *parent)
    : pNodeData(data), pParentNode(parent), pType(type), pNodeViewSize(0, 0)
{}

TreeNode::~TreeNode()
{
    qDeleteAll(pChildItems);
}

void TreeNode::appendChild(TreeNode *child)
{
    pChildItems.append(child);
}

void TreeNode::setSize(const QSize &size)
{
    pNodeViewSize = size;
}

QSize TreeNode::getSize() const
{
    return pNodeViewSize;
}

void TreeNode::setIcon(const QPixmap &icon)
{
    pIcon = icon;
}

QPixmap TreeNode::getIcon() const
{
    return pIcon;
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
