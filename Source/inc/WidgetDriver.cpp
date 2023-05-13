#include "WidgetDriver.h"


WidgetDriver::WidgetDriver(CurseDriver curseDriver) : m_curseDriver(curseDriver)
{}

WidgetDriver::~WidgetDriver()
{}

WidgetErrors WidgetDriver::RegisterWidget(Widget widget)
{
    m_widgets[m_registeredWidgets] = widget;
    widget.handle = m_registeredWidgets;

    switch(widget.type)
    {
        case M_LIST:
        {
            // m_curseDriver.CreateMenu(widget.handle, widget.choices, widget.nrChoices, widget.sizing);
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
                std::cout << "HERE" << "\n";
                m_curseDriver.DisplayMenu(m_widgets[i].handle);
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