#ifndef UiHelper_hpp
#define UiHelper_hpp

#include <QtGui>
#include <QtCore>

namespace sqt {

void switchStackPage(QStackedWidget* stack, int index)
{
    if (stack->count() != 0)
    {
        QSizePolicy policyMin(QSizePolicy::Ignored, QSizePolicy::Ignored);
        QSizePolicy policyMax(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // minimal previous page
        if (stack->currentIndex() != index)
        {
            stack->currentWidget()->setSizePolicy(policyMin);
        }
        else
        {
            // minimal all page
            for (int i = 0; i < stack->count(); ++i)
            {
                stack->widget(i)->setSizePolicy(policyMin);
            }
        }
        // show and maximal new page
        stack->setCurrentIndex(index);
        stack->currentWidget()->setSizePolicy(policyMax);
        stack->adjustSize();
    }
}

}

#endif
