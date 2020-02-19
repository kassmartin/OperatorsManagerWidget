#pragma once

#include <QVariant>
#include <QList>

class TreeNode
{
public:
    enum NodeType {
        Country = 0,
        Operator,
        TypeCount
    };

public:
    explicit TreeNode(NodeType pType = Country, const QList<QVariant> &data = {}, TreeNode *parentNode = nullptr);
    ~TreeNode();

    void appendChild(TreeNode *child);

    TreeNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data() const;
    QString data(int number) const;
    int row() const;
    TreeNode* parentNode();
    NodeType type() const;

private:
    QList<TreeNode*> pChildItems;
    QList<QVariant> pNodeData;
    TreeNode* pParentNode;
    NodeType pType;
};
