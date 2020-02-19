#pragma once

#include <QVariant>
#include <QList>

#include <memory>

#include "NodeDatas/NodeDatas"

class TreeNode
{
public:
    enum NodeType {
        Country = 0,
        Operator,
        TypeCount
    };

public:
    explicit TreeNode(NodeType pType = Country, AbstractData *data = nullptr, TreeNode *parentNode = nullptr);
    ~TreeNode();

    void appendChild(TreeNode *child);

    TreeNode* child(int row);
    int childCount() const;
    int columnCount() const;
    QString data() const;
    AbstractData* dataPtr() const;
    int row() const;
    TreeNode* parentNode();
    NodeType type() const;

private:
    QList<TreeNode*> pChildItems;
    std::unique_ptr<AbstractData> pNodeData;
    TreeNode* pParentNode;
    NodeType pType;
};
