#ifndef QTAGCELLDELEGATE_HPP
#define QTAGCELLDELEGATE_HPP

#include <QtGui>
#include <QtCore>

namespace sqt {

struct TagSlice
{
    QStaticText name;
    QColor color;
    int textWidth;

    TagSlice() {}

    TagSlice(const QString& tagName, const int tagColor):
        name(tagName),
        color(QColor(tagColor)),
        textWidth(0)
    {
    }
};

typedef QVector<TagSlice> TagSliceVector;
typedef QVector<TagSliceVector> RowTagVector;

class QTagCellDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    QTagCellDelegate(): mPtrRowTags(NULL) {}
    ~QTagCellDelegate() {}

    void setTagSpace(int space)
    {
        mTagSpace = space;
    }

    void setTagFont(const QFont& font)
    {
        mTagFont = font;
    }

    void setRowTags(RowTagVector* ptr)
    {
        mPtrRowTags = ptr;
    }

    void measureHint()
    {
        if (mPtrRowTags == NULL)
            return;

        QFontMetrics metric(mTagFont);

        int cellWidth = mTagSpace;
        int cellHeight = 0;
        for (int r = 0; r < mPtrRowTags->size(); ++r)
        {
            int rowWidth = mTagSpace;
            int rowHeight = 0;
            for (int i = 0; i < mPtrRowTags->at(r).size(); ++i)
            {
                QRect rect = metric.boundingRect(mPtrRowTags->at(r)[i].name.text());
                //mPtrRowTags->at(r)[i].textWidth = rect.width();
                rowWidth += rect.width() + mTagSpace;
                rowHeight = qMax(cellHeight, rect.height());
            }
            cellWidth = qMax(cellWidth, rowWidth);
            cellHeight = qMax(cellHeight, rowHeight);
        }
        mCellSize.setWidth(cellWidth);
        mCellSize.setHeight(cellHeight);
    }

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if (mPtrRowTags == NULL)
        {
            qDebug() << "null mPtrRowTags" <<  endl;
            return;
        }

        if (index.row() >= mPtrRowTags->size())
        {
            qDebug() << "FATAL: index.row() >= mPtrRowTags->size()" << endl;
            qDebug() << "index:" << index.row() << endl;
            qDebug() << "size:" << mPtrRowTags->size() << endl;
            return;
        }

        //QStyleOptionViewItem newOption(option);

        int textX = option.rect.left() + mTagSpace;
        int textY = option.rect.top() + (option.rect.height() - option.fontMetrics.height())/2;
        for (int tagCol = 0; tagCol < mPtrRowTags->at(index.row()).size(); ++tagCol)
        {
            painter->setPen(mPtrRowTags->at(index.row())[tagCol].color);
            painter->drawStaticText(textX, textY,
                                    mPtrRowTags->at(index.row())[tagCol].name);
            textX += option.fontMetrics.width(mPtrRowTags->at(index.row())[tagCol].name.text()) + mTagSpace;//mPtrRowTags->at(index.row())[tagCol].textWidth + mTagSpace;
        }

        //painter->fillRect(option.rect, Qt::red);
        //qDebug() << "width:" << option.rect.width() << endl;
        //QItemDelegate::paint(painter, option, index);
        //newOption.rect.setWidth(200);
        //QItemDelegate::paint(painter, newOption, index);
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        return mCellSize;
    }

private:
    int mTagSpace;
    QFont mTagFont;
    QSize mCellSize;
    RowTagVector* mPtrRowTags;
};

}

#endif // QTAGCELLDELEGATE_HPP
