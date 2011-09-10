#ifndef QTAGCELLDELEGATE_HPP
#define QTAGCELLDELEGATE_HPP

#include <QtGui>
#include <QtCore>
#include "QBaseCellDelegate.hpp"

/*
  Support colorful text in cell
*/

namespace sqt {

class QTagCellDelegate: public QBaseCellDelegate
{
    Q_OBJECT

private:
    typedef QVector<QString> RowTag;

public:
    QTagCellDelegate() {}
    ~QTagCellDelegate() {}

    void setTagSpace(int space)
    {
        mTagSpace = space;
    }

    void setTagFont(const QFont& font)
    {
        mTagFont = font;
    }

    // for tag-color hash
    void insertTagColorPair(const QString& tag, int color)
    {
        mTagColors.insert(tag, color);
    }

    void removeTagColorPair(const QString& tag)
    {
        mTagColors.remove(tag);
    }

    void updateTagColorKey(const QString& oldTag, const QString& newTag)
    {
        mTagColors.insert(newTag, mTagColors.take(oldTag));
    }

    void updateTagColorValue(const QString& tag, int color)
    {
        mTagColors[tag] = color;
    }

    void reserveTagColor(int size)
    {
        mTagColors.reserve(size);
    }

    void clearTagColor()
    {
        mTagColors.clear();
    }

    // for record all row tags
    void insertRowTag(int pos, const QStringList& list)
    {
        RowTag* rowTag = new RowTag;
        rowTag->reserve(list.size());
        QStringListIterator iter(list);
        while (iter.hasNext())
        {
            rowTag->push_back(iter.next());
        }
        mRowTagPtrs.insert(pos, rowTag);
    }

    void appendRowTag(const QStringList& list)
    {
        insertRowTag(mRowTagPtrs.size(), list);
    }

    void removeRowTag(int pos)
    {
        delete mRowTagPtrs[pos];
        mRowTagPtrs.remove(pos);
    }

    void updateRowTag(int pos, const QStringList& list)
    {
        RowTag* rowTag = mRowTagPtrs[pos];
        rowTag->clear();
        rowTag->reserve(list.size());
        QStringListIterator iter(list);
        while (iter.hasNext())
        {
            rowTag->push_back(iter.next());
        }
    }

    void clearRowTagPtrs()
    {
        mRowTagPtrs.clear();
    }

    void reserveRowTagPtrs(int size)
    {
        mRowTagPtrs.reserve(size);
    }

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {               
        paintBackground(painter, option);

        if (mRowTagPtrs.empty()) {
            qDebug() << "empty mRowTagPtrs" <<  endl;
            return;
        }

        const int row = index.row();
        if (row >= mRowTagPtrs.size()) {
            qDebug() << "FATAL: <QTagCellDelegate> row index outof range" << endl;
            qDebug() << "index:" << row << endl;
            qDebug() << "size:" << mRowTagPtrs.size() << endl;
            return;
        }

        int textX = option.rect.left() + mTagSpace;
        int textY = option.rect.top() + (option.rect.height() - option.fontMetrics.height())/2;
        const RowTag& rowTag = *mRowTagPtrs[row];
        for (int col = 0; col < rowTag.size(); ++col) {
            QString tag = rowTag[col];
            painter->setPen(mTagColors[tag]);
            painter->drawStaticText(textX, textY, QStaticText(tag));
            textX += option.fontMetrics.width(tag) + mTagSpace;
        }
    }

    int  QColorToInt(const QColor &color) const
    {
    //将Color 从QColor 转换成 int
    return   (int)(((unsigned int)color.blue()<< 16) | (unsigned short)(((unsigned short)color.green()<< 8) | color.red()));
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        const int row = index.row();
        if (row >= mRowTagPtrs.size()) {
            return option.rect.size();
        }

        QFontMetrics metric(option.font);
        int cellWidth = mTagSpace;
        int cellHeight = metric.height();;
        const RowTag& rowTag = *mRowTagPtrs[row];
        for (int col = 0; col < rowTag.size(); ++col) {
            cellWidth += metric.width(rowTag[col]) + mTagSpace;
        }

        return QSize(cellWidth, cellHeight);
    }

private:
    int mTagSpace;
    QFont mTagFont;
    QSize mCellSize;
    QVector<RowTag*> mRowTagPtrs;
    QHash<QString, int> mTagColors;
};

}

#endif // QTAGCELLDELEGATE_HPP
