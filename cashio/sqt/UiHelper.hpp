#ifndef UiHelper_hpp
#define UiHelper_hpp

#include <QtGui>
#include <QtCore>

namespace sqt {

void switchStackPage(QStackedWidget* stack, int index)
{
    // minimal previous page
    QWidget* page = stack->currentWidget();
    if (page != NULL)
    {
        page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    // show and maximal new page
    stack->setCurrentIndex(index);
    page = stack->currentWidget();
    page->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stack->adjustSize();
}

}

#endif
