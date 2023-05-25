#include "WidgetDriver.h"


WidgetDriver::WidgetDriver(CurseDriver curseDriver) : m_curseDriver(curseDriver)
{
}

WidgetDriver::~WidgetDriver()
{
    DestroyWidgets();
}

int WidgetDriver:: RegisterWidget(Widget widget)
{
    Widget *newWidget = new Widget;
    *newWidget = widget;
    
    newWidget->handle = m_registeredWidgets;

    switch(widget.type)
    {
        case M_MENU:
        {
            Menu *menu = (Menu *) newWidget->data;
            m_curseDriver.CreateMenu(newWidget->handle, menu->choices, menu->nrChoices, newWidget->sizing);

            break;
        }

        case M_PANEL:
        {
            break;

        }

        case M_TEXT:
        {
            break;

        }

        case M_TEXTAREA:
        {
            TextArea *textArea = (TextArea *) newWidget->data;
            m_curseDriver.CreateTextArea(newWidget->handle, textArea->data, textArea->toggleLines, newWidget->sizing);

            break;

        }
    }

    m_widgets[m_registeredWidgets] = *newWidget;
    m_registeredWidgets++;

    return newWidget->handle;
}


WidgetErrors WidgetDriver::DisplayWidgets()
{
    for (int i = 0; i < m_registeredWidgets; i++)
    {
        switch (m_widgets[i].type)
        {
            case M_MENU:
            {
                m_curseDriver.DisplayMenu(m_widgets[i].handle, true);

                break;

            }

            case M_PANEL:
            {
                break;

            }

            case M_TEXT:
            {
                break;

            }

            case M_TEXTAREA:
            {
                m_curseDriver.DisplayTextArea(m_widgets[i].handle, true);

                break;
            }
        }

    }

    return WidgetErrors::NO_ERROR_WIDGET;
}

WidgetErrors WidgetDriver::CheckWidgetInteraction()
{
    for (int i = 0; i < 1; i++)
    {
        switch (m_widgets[i].type)
        {
            case M_MENU:
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


void *WidgetDriver::CreateMenuData(std::vector<std::string> choices, int nrChoices)
{
    Menu *ptr = (Menu *) calloc(1, sizeof(Menu));

    if (ptr == nullptr)
    {
        return nullptr;
    }

    ptr->choices = choices;
    ptr->nrChoices = nrChoices;

    return ptr;
}

std::string WidgetDriver::FetchMenuSelection(Widget widget)
{
    if (widget.handle < 0 && widget.type != M_MENU)
    {
        return std::string();
    }

    return m_curseDriver.FetchMenuSelection(widget.handle);
}

void *WidgetDriver::CreateTextAreaData(std::string data, bool toggleLines)
{
    TextArea *ptr = (TextArea *) calloc(1, sizeof(TextArea));

    if (ptr == nullptr)
    {
        return nullptr;
    }

    ptr->data = data;
    ptr->toggleLines = toggleLines;

    return ptr;
}

void WidgetDriver::SetTextAreaData(int handle, std::string data, bool toggleLines)
{
    if (m_widgets[handle].type == M_TEXTAREA)
    {
        Widget& widget = m_widgets[handle];
        // delete &m_widgets[handle].data
    
        widget.data = CreateTextAreaData(data, toggleLines);

        TextArea *textArea = (TextArea *) widget.data;
        // std::cout << textArea->data << "\n";
        m_curseDriver.UpdateTextArea(handle, textArea->data, textArea->toggleLines, widget.sizing);
    }
}

Widget WidgetDriver::GetWidget(int handle)
{
    // probably segfaults, dont care tho   
    return m_widgets[handle];
}

void WidgetDriver::DestroyWidgets()
{
    for (int i = 0; i < MAX_NR_WIDGETS; i++)
    {
        delete &m_widgets[i].data;
        delete &m_widgets[i];
    }
}