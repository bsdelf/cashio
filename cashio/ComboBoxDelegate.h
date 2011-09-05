#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QtCore>
#include <QtGui>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ComboBoxDelegate();
    ~ComboBoxDelegate();

    void addText(const QString& text);

public:
    QWidget *createEditor(
        QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(
        QWidget *editor, const QModelIndex &index) const;

    void setModelData(
        QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(
        QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QStringList mOptions;
};

#endif // COMBOBOXDELEGATE_H
