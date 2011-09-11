#ifndef QBaseCellDelegate_hpp
#define QBaseCellDelegate_hpp

#include <QtGui>
#include <QtCore>

/*
  Support cell highlight, text alignment, custom highlight.
*/

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
    void insertHighlightIndex(const QModelIndex& index, const QColor& color)
    {
        mHighlightIndexMap.insert(index, color);
    }

    void removeHighlightIndex(const QModelIndex& index)
    {
        mHighlightIndexMap.remove(index);
    }

    void setTextAlignment(const Qt::Alignment& alignment)
    {
        mAlignment = alignment;
    }

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        paintBackground(painter, option, index);

        if (mHighlightIndexMap.contains(index)) {
            painter->fillRect(option.rect, mHighlightIndexMap[index]);
        }

        QStyle *style = QApplication::style();
        const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
        int textX = option.rect.left() + textMargin;
        int textY = option.rect.top() + (option.rect.height() - option.fontMetrics.height())/2;

        QTextOption textOption;
        textOption.setAlignment(mAlignment);
        textOption.setWrapMode(QTextOption::NoWrap);

        QString text = index.data(Qt::DisplayRole).toString();
        QStaticText staticText(text);
        staticText.setTextWidth(option.rect.width() - textMargin*2);
        staticText.setTextOption(textOption);

        painter->setPen(Qt::black);
        painter->drawStaticText(textX, textY, staticText);
    }

protected:
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // NOTE: enable mouseTracking for the widget!!        
        if (option.state & QStyle::State_Selected) {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setPen(Qt::red);
            painter->setBrush(Qt::white);
            painter->drawRoundedRect(option.rect, 3, 3);
            painter->restore();
        } else if (option.state & QStyle::State_MouseOver) {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setPen(option.palette.highlight().color());
            painter->setBrush(Qt::white);
            painter->drawRoundedRect(option.rect, 3, 3);
            painter->restore();
        } else {
            //if (index.row() & 1)
                painter->fillRect(option.rect, Qt::white);
            //else
            //    painter->fillRect(option.rect, Qt::lightGray);
        }
    }

protected:
    Qt::Alignment mAlignment;
    QHash<QModelIndex, QColor> mHighlightIndexMap;
};

}

#endif
