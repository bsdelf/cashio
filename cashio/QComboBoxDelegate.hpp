#ifndef QComboBoxDelegate_hpp
#define QComboBoxDelegate_hpp

#include <QtCore>
#include <QtGui>

namespace sqt {

class QComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    QComboBoxDelegate() {};
    ~QComboBoxDelegate() {};

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
        QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QComboBox* box = new QComboBox(parent);
        box->addItems(mOptions);
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
        QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }

private:
    QStringList mOptions;
};

}

#endif // QComboBoxDelegate_hpp
