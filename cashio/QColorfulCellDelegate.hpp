#ifndef QColorfulCellDelegate_hpp
#define QColorfulCellDelegate_hpp

#include <QtGui>
#include <QtCore>

namespace sqt {

class QColorfulCellDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    QColorfulCellDelegate() {}
    ~QColorfulCellDelegate() {}

public:
    void insertIndex(const QModelIndex &index)
    {
        mIndexSet.insert(index);
    }

    void removeIndex(const QModelIndex &index)
    {
        mIndexSet.remove(index);
    }

    void setCellColor(const QColor& color)
    {
        mCellColor = color;
    }

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem newOption(option);
        if (mIndexSet.contains(index))
        {
            painter->fillRect(newOption.rect, mCellColor);
            newOption.palette.setColor(QPalette::Base, mCellColor);
            newOption.palette.setColor(QPalette::Window, mCellColor);
            newOption.palette.setColor(QPalette::Highlight, mCellColor);
        }
        QItemDelegate::paint(painter, newOption, index);
    }

private:
    QSet<QModelIndex> mIndexSet;
    QColor mCellColor;
};

}

#endif
