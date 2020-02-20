#pragma once

#include <QVariant>
#include <QList>
#include <QSize>
#include <QPixmap>

#include <memory>

#include "NodeDatas/NodeDatas"
/*!
 * \brief The TreeNode class
 *
 * Class for representing nodes in tree structure model.
 */
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
    /// Deletes all childs.
    ~TreeNode();
    /// Inserts child node.
    void appendChild(TreeNode *child);
    /// Sets size that node take on view.
    void setSize(const QSize &size);
    /// Returns size that node take on view.
    QSize getSize() const;
    /// Sets view node icon.
    void setIcon(const QPixmap &icon);
    /// Returns view node icon.
    QPixmap getIcon() const;
    /// Returns child nodes by index.
    TreeNode* child(int row);
    int childCount() const;
    int columnCount() const;
    /// Returns "name" field of data.
    QString data() const;
    /// Returns base pointer to data object.
    AbstractData* dataPtr() const;
    int row() const;
    TreeNode* parentNode();
    /// Returns NodeType for simply node identification.
    NodeType type() const;

private:
    QList<TreeNode*> pChildItems;
    std::unique_ptr<AbstractData> pNodeData;
    TreeNode* pParentNode;
    NodeType pType;
    QSize pNodeViewSize;
    QPixmap pIcon;
};
