#include "WidgetDriver.h"


WidgetDriver::WidgetDriver(CurseDriver curseDriver) : m_curseDriver(curseDriver)
{
}

WidgetDriver::~WidgetDriver()
{
    DestroyWidgets();
}

WidgetErrors WidgetDriver::RegisterWidget(Widget widget)
{
    Widget *newWidget = new Widget;
    *newWidget = widget;
    
    newWidget->handle = m_registeredWidgets;

    switch(widget.type)
    {
        case M_LIST:
        {
            m_curseDriver.CreateMenu(newWidget->handle, newWidget->choices, newWidget->nrChoices, newWidget->sizing);
        }

        case M_PANEL:
        {

        }

        case M_TEXT:
        {

        }

        case M_TEXTAREA:
        {

        }
    }

    m_widgets[m_registeredWidgets] = *newWidget;
    m_registeredWidgets++;

    return WidgetErrors::NO_ERROR_WIDGET;
}


WidgetErrors WidgetDriver::DisplayWidgets()
{
    for (int i = 0; i < m_registeredWidgets; i++)
    {
        switch (m_widgets[i].type)
        {
            case M_LIST:
            {
                m_curseDriver.DisplayMenu(m_widgets[i].handle, true);
            }

            case M_PANEL:
            {

            }

            case M_TEXT:
            {

            }

            case M_TEXTAREA:
            {
                
            }
        }

    }

    return WidgetErrors::NO_ERROR_WIDGET;
}


WidgetErrors WidgetDriver::CheckWidgetInteraction()
{
    for (int i = 0; i < MAX_NR_WIDGETS; i++)
    {
        switch (m_widgets[i].type)
        {
            case M_LIST:
            {
                m_curseDriver.CheckMenuInteraction(m_widgets[i].handle);
            }

            case M_PANEL:
            {

            }

            case M_TEXT:
            {

            }

            case M_TEXTAREA:
            {

            }
        }
    }


    return WidgetErrors::NO_ERROR_WIDGET;
}


void WidgetDriver::DestroyWidgets()
{
    for (int i = 0; i< MAX_NR_WIDGETS; i++)
    {
        delete &m_widgets[i];
    }
}