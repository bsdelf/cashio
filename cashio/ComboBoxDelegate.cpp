#include "ComboBoxDelegate.h"

ComboBoxDelegate::ComboBoxDelegate()
{
}

ComboBoxDelegate::~ComboBoxDelegate()
{

}

void ComboBoxDelegate::addText(const QString &text)
{
    mOptions.append(text);
}

QWidget* ComboBoxDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* box = new QComboBox(parent);
    box->addItems(mOptions);
    return box;
}

void ComboBoxDelegate::setEditorData(
    QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *box = static_cast<QComboBox*>(editor);
    int optionIndex = mOptions.indexOf(value);
    if (optionIndex < 0) optionIndex = 0;
    box->setCurrentIndex(optionIndex);
}

void ComboBoxDelegate::setModelData(
    QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    QString value = box->currentText();
    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
