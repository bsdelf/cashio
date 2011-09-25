#ifndef PAGEINF_H
#define PAGEINF_H



namespace Ui {
    class MainWindow;
}

class PageInf
{
public:
    virtual ~PageInf() {}

    virtual void init(const Ui::MainWindow* ui) = 0;
    virtual void active() = 0;
    virtual void saveState() = 0;

};

#endif // PAGEINF_H
