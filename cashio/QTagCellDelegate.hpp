#ifndef QTAGCELLDELEGATE_HPP
#define QTAGCELLDELEGATE_HPP

#include <QtGui>
#include <QtCore>

namespace sqt {

class QTagCellDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    QTagCellDelegate() {}
    ~QTagCellDelegate() {}

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem newOption(option);
        QStringList list;
        list << "hello" << "world" << "apple";
        painter->setPen(Qt::red);
        painter->drawText(option.rect.center(), "test");
        //painter->fillRect(option.rect, Qt::red);
        qDebug() << "width:" << option.rect.width() << endl;
        //QItemDelegate::paint(painter, option, index);
        newOption.rect.setWidth(200);
        QItemDelegate::paint(painter, newOption, index);
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        qDebug() << "called" << endl;
        return QSize(200, 20);
    }
};

}

#endif // QTAGCELLDELEGATE_HPP
