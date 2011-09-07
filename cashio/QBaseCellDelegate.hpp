#ifndef QBaseCellDelegate_hpp
#define QBaseCellDelegate_hpp

#include <QtGui>
#include <QtCore>

namespace sqt {

class QBaseCellDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    QBaseCellDelegate():
        mAlignment(Qt::AlignLeft | Qt::AlignVCenter)
    {
    }

    ~QBaseCellDelegate() {}

public:
    void insertIndex(const QModelIndex& index)
    {
        mIndexSet.insert(index);
    }

    void removeIndex(const QModelIndex& index)
    {
        mIndexSet.remove(index);
    }

    void setCellColor(const QColor& color)
    {
        mCellColor = color;
    }

    void setTextAlignment(const Qt::Alignment& alignment)
    {
        mAlignment = alignment;
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
        newOption.displayAlignment = mAlignment;
        QItemDelegate::paint(painter, newOption, index);
    }

protected:
    QSet<QModelIndex> mIndexSet;
    QColor mCellColor;
    Qt::Alignment mAlignment;
};

}

#endif
