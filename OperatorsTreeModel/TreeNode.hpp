#pragma once

#include <QVariant>
#include <QList>

class TreeNode
{
public:
    explicit TreeNode(const QList<QVariant> &data = {}, TreeNode *parentNode = nullptr);
    ~TreeNode();

    void appendChild(TreeNode *child);

    TreeNode *child(int row);
    int childCount() const;
    int columnCount() const;
    QString data() const;
    QString data(int number) const;
    int row() const;
    TreeNode* parentNode();

private:
    QList<TreeNode*> pChildItems;
    QList<QVariant> pNodeData;
    TreeNode* pParentNode;
};
