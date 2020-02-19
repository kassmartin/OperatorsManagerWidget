#include "TreeNode.hpp"

TreeNode::TreeNode(NodeType type, const QList<QVariant> &data, TreeNode *parent)
    : pNodeData(std::move(data)), pParentNode(parent), pType(type)
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
    return pNodeData.count();
}

QString TreeNode::data() const
{
    QStringList result;
    for (auto element : pNodeData) {
        switch (element.type()) {
        case QVariant::Int:
            result << QString::number(element.toInt());
            break;
        case QVariant::String:
            result << element.toString();
            break;
        default:
            break;
        }
    }
    return result.join(" ");
}

QString TreeNode::data(int number) const
{
    QVariant element = pNodeData.at(number);
    switch (element.type()) {
    case QVariant::Int:
        return QString::number(element.toInt());
    case QVariant::String:
        return element.toString();
    default:
        return {};
    }
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
