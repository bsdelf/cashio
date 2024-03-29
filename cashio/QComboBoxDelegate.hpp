#ifndef QComboBoxDelegate_hpp
#define QComboBoxDelegate_hpp

#include <QtCore>
#include <QtGui>
#include "QBaseCellDelegate.hpp"

/*
  Show a combobox in cell when edit. Support text alignment when normal.
*/

namespace sqt {

class QComboBoxDelegate : public QBaseCellDelegate
{
    Q_OBJECT

public:
    QComboBoxDelegate() {}
    ~QComboBoxDelegate() {}

    void addText(const QString& text)
    {
        mOptions.append(text);
    }

    void clearText()
    {
        mOptions.clear();
    }

public:
    QWidget *createEditor(
        QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
    {        
        QComboBox* box = new QComboBox(parent);
        box->addItems(mOptions);
        box->sizeHint();
        return box;
    }

    void setEditorData(
        QWidget *editor, const QModelIndex &index) const
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *box = static_cast<QComboBox*>(editor);
        int optionIndex = mOptions.indexOf(value);
        if (optionIndex < 0) optionIndex = 0;
        box->setCurrentIndex(optionIndex);
    }

    void setModelData(
        QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox *box = static_cast<QComboBox*>(editor);
        QString value = box->currentText();
        model->setData(index, value, Qt::EditRole);
    }

    void updateEditorGeometry(
        QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex&) const
    {
        editor->setGeometry(option.rect);
    }      

    QSize sizeHint(
        const QStyleOptionViewItem & option, const QModelIndex & index) const
    {
        QComboBox box;
        box.setFont(option.font);
        box.setSizeAdjustPolicy(QComboBox::AdjustToContents);
        box.addItems(mOptions);
        return box.sizeHint();
    }

private:
    QStringList mOptions;
};

}

#endif // QComboBoxDelegate_hpp
