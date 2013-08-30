#include "TextBox.h"

#include <iostream>
#include <algorithm>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Mouse.hpp>


TextBox::TextBox() : WCore::Widget(), m_backgroundShape(), m_string(""), m_text(), m_padding(0), m_selectionBegin(0), m_selectionEnd(0), m_isCursorVisible(true), m_cursorShape()
{
    m_dragSelection.isDragging = false;
    m_dragSelection.first = 0;
    m_dragSelection.second = 0;
    m_dragSelection.timer = 0;
    m_dragSelection.mousePosition = NoBorder;

    m_text.setColor(sf::Color(255, 0, 0, 255));
    m_text.setPosition(5, 5);

    m_cursorShape.setOutlineThickness(0);
    m_cursorShape.setFillColor(sf::Color(0, 0, 150, 255));

    m_backgroundShape.setOutlineThickness(1);

    InitPalette();
    UpdateDrawables();

    ComputeCursorPosition();
}

TextBox::~TextBox()
{

}

void TextBox::Draw(sf::RenderTarget &wnd)
{
    wnd.draw(m_backgroundShape, m_currentTransform);
    if(m_isCursorVisible && m_enabled)
        wnd.draw(m_cursorShape, m_currentTransform);

    wnd.draw(m_text, m_currentTransform);
}

int TextBox::GetSelectionBegin() const
{
    return m_selectionBegin;
}

int TextBox::GetSelectionEnd() const
{
    return m_selectionEnd;
}

void TextBox::Select(int position)
{
    int typeOfMove = position < m_selectionBegin ? 0 : 1; //0 -> Reward ; 1 -> Forward

    if(position < 0)
    {
        m_selectionBegin = 0;
        m_selectionEnd = 0;
    }
    else if(position > m_string.getSize())
    {
        m_selectionBegin = m_string.getSize();
        m_selectionEnd = m_string.getSize();
    }
    else
    {
        m_selectionBegin = position;
        m_selectionEnd = position;
    }
    ComputeVisibleString();

    while(m_selectionBegin - m_padding < 0)
    {
        m_padding--;
        ComputeVisibleString();
    }

    while(m_selectionBegin - m_padding > m_text.getString().getSize())
    {
        m_padding++;
        ComputeVisibleString();
    }

    if(typeOfMove == 0)
    {
        for(int a = 0; a < 3 && m_padding > 0 && m_selectionBegin - 3 < m_padding; a++)
        {
            m_padding--;
        }
    }

    ComputeCursorPosition();
    UpdateSelectionDrawable();
}

void TextBox::Select(int selectionBegin, int selectionEnd)
{
    m_selectionBegin = selectionBegin;
    m_selectionEnd = selectionEnd;

    ComputeCursorPosition();
    UpdateSelectionDrawable();
}

int TextBox::GetCharacterOnPoint(sf::Vector2f position) const
{
    sf::Vector2f posOnText(position.x, position.y);

    int i = 0;

    if(posOnText.x < m_text.findCharacterPos(0).x)
    {
        return m_padding;
    }

    while(i < m_text.getString().getSize())
    {
        if(posOnText.x >= ((m_text.findCharacterPos(std::max(i - 1, 0)) + m_text.findCharacterPos(i)) / 2.f).x &&
           posOnText.x < ((m_text.findCharacterPos(i) + m_text.findCharacterPos(i + 1)) / 2.f).x)
        {
            return i + m_padding;
        }

        i++;
    }

    return m_text.getString().getSize() + m_padding;
}

void TextBox::SetText(sf::String text)
{
    m_string = text;
    m_padding = 0;
    ComputeVisibleString();
    Select(0);
}

sf::String TextBox::GetText() const
{
    return m_string;
}

sf::String TextBox::GetSelectedText() const
{
    sf::String selectedText(m_string);
    selectedText.erase(m_selectionEnd, m_string.getSize() - m_selectionEnd);
    selectedText.erase(0, m_selectionBegin);

    return selectedText;
}

void TextBox::SetFont(const sf::Font &font)
{
    m_text.setFont(font);
    UpdateDrawables();
}

const sf::Font* TextBox::GetFont() const
{
    return m_text.getFont();
}

void TextBox::SetCharacterSize(unsigned int s)
{
    m_text.setCharacterSize(s);
    UpdateDrawables();
}

unsigned int TextBox::GetCharacterSize() const
{
    return m_text.getCharacterSize();
}

void TextBox::HandleKeyboardEvent(sf::Keyboard::Key button, bool pressed)
{
    if(!m_focus || !m_enabled)
        return;

    if(pressed)
    {
        if(button == sf::Keyboard::Left)
        {
            Select(GetSelectionBegin() - 1);
        }
        else if(button == sf::Keyboard::Right)
        {
            Select(GetSelectionEnd() + 1);
        }
        else if(button == sf::Keyboard::BackSpace)
        {
            if(GetSelectionBegin() == GetSelectionEnd())
            {
                if(GetSelectionBegin() > 0)
                {
                    m_string.erase(GetSelectionBegin() - 1, 1);
                    Select(GetSelectionBegin() - 1);
                }
            }
            else
            {
                m_string.erase(GetSelectionBegin(), GetSelectionEnd() - GetSelectionBegin());
                Select(GetSelectionBegin());
            }

            ComputeVisibleString();
            ComputeCursorPosition();
        }
        else if(button == sf::Keyboard::Delete)
        {
            if(GetSelectionBegin() == GetSelectionEnd())
            {
                if(GetSelectionEnd() < m_string.getSize())
                    m_string.erase(GetSelectionEnd(), 1);
            }
            else
            {
                m_string.erase(GetSelectionBegin(), GetSelectionEnd() - GetSelectionBegin());
            }
            Select(GetSelectionBegin());

            ComputeVisibleString();
            ComputeCursorPosition();
        }
    }
}

void TextBox::HandleMouseMoveEvent(int x, int y)
{
    if(!m_enabled)
        return;

    sf::Vector2f mousePos(x, y);

    if(m_dragSelection.isDragging)
    {
        m_dragSelection.second = GetCharacterOnPoint(mousePos);

        Select(std::min(m_dragSelection.first, m_dragSelection.second), std::max(m_dragSelection.first, m_dragSelection.second));

        if(x < 40 && m_padding > 0)
        {
            m_dragSelection.mousePosition = LeftBorder;
        }
        else if(x > m_size.x - 10 && m_padding < m_string.getSize() - m_text.getString().getSize())
        {
            m_dragSelection.mousePosition = RightBorder;
        }
        else
        {
            m_dragSelection.mousePosition = NoBorder;
        }

    }
}

void TextBox::HandleMouseButtonEvent(sf::Mouse::Button button, bool pressed, int x, int y)
{
    if(!m_enabled)
        return;

    sf::Vector2f mousePos(x, y);

    if(pressed)
    {
        if(IsOnWidget(mousePos) && !m_focus)
        {
            GrabFocus();
        }
        if(!IsOnWidget(mousePos) && m_focus)
        {
            LostFocus();
        }

        if(m_focus)
        {
            m_dragSelection.isDragging = true;
            m_dragSelection.first = m_dragSelection.second = GetCharacterOnPoint(mousePos);
        }
    }
    else
    {
        if(m_focus)
        {
            if(m_dragSelection.isDragging)
            {
                m_dragSelection.second = GetCharacterOnPoint(mousePos);
                m_dragSelection.isDragging = false;
                m_dragSelection.mousePosition = NoBorder;

                Select(std::min(m_dragSelection.first, m_dragSelection.second), std::max(m_dragSelection.first, m_dragSelection.second));
            }
        }
    }
}

void TextBox::HandleTextEntered(sf::Uint32 character)
{
    if(!m_focus || !m_enabled)
        return;

    if(character > 0x1f && character != 0x7f)
    {
        if(m_selectionBegin == m_selectionEnd)
        {
            m_string.insert(m_selectionBegin, sf::String(character));
        }
        else
        {
            m_string.erase(m_selectionBegin, m_selectionEnd - m_selectionBegin);
            m_string.insert(m_selectionBegin, sf::String(character));
        }

        Select(GetSelectionBegin() + 1);
    }
}

void TextBox::HandleSizeChange()
{
    m_backgroundShape.setSize(m_size);
    ComputeVisibleString();
    ComputeCursorPosition();
}

void TextBox::HandleTime(float time)
{
    m_dragSelection.timer += time;

    if(m_dragSelection.isDragging && m_dragSelection.timer > 0.2)
    {
        m_dragSelection.timer -= 0.2;
        if(m_dragSelection.mousePosition == LeftBorder && m_padding > 0)
        {
            m_padding--;

            ComputeVisibleString();
            ComputeCursorPosition();
        }
        else if(m_dragSelection.mousePosition == RightBorder && m_padding < m_string.getSize() - m_text.getString().getSize())
        {
            m_padding++;

            ComputeVisibleString();
            ComputeCursorPosition();
        }
    }
}

void TextBox::UpdateDrawables()
{
    WCore::State state = WCore::GetWidgetState(*this);

    m_text.setColor(GetPalette().GetColor("text", state));
    m_backgroundShape.setFillColor(GetPalette().GetColor("background", state));
    m_backgroundShape.setOutlineColor(GetPalette().GetColor("border", state));

    UpdateSelectionDrawable();

    sf::Vector2f cursorSize = m_cursorShape.getSize();
    if(m_text.getFont())
        cursorSize.y = m_text.getFont()->getLineSpacing(m_text.getCharacterSize()) + 2;

    m_cursorShape.setSize(cursorSize);
}

void TextBox::InitPalette()
{
    GetPalette().SetColor("text", WCore::DISABLED, sf::Color(170, 170, 170, 255))
                .SetColor("text", WCore::ENABLED, sf::Color(0, 0, 0, 255))
                .SetColor("text", WCore::HOVERED, sf::Color(0, 0, 0, 255))
                .SetColor("text", WCore::FOCUSED, sf::Color(0, 0, 0, 255))
                .SetColor("text", WCore::FOCUSED_HOVERED, sf::Color(0, 0, 0, 255))

                .SetColor("background", WCore::DISABLED, sf::Color(130, 130, 130, 255))
                .SetColor("background", WCore::ENABLED, sf::Color(210, 210, 210, 255))
                .SetColor("background", WCore::HOVERED, sf::Color(230, 230, 230, 255))
                .SetColor("background", WCore::FOCUSED, sf::Color(255, 255, 255, 255))
                .SetColor("background", WCore::FOCUSED_HOVERED, sf::Color(255, 255, 255, 255))

                .SetColor("border", WCore::DISABLED, sf::Color(0, 0, 0, 255))
                .SetColor("border", WCore::ENABLED, sf::Color(0, 0, 0, 255))
                .SetColor("border", WCore::HOVERED, sf::Color(170, 170, 255, 255))
                .SetColor("border", WCore::FOCUSED, sf::Color(0, 0, 0, 255))
                .SetColor("border", WCore::FOCUSED_HOVERED, sf::Color(170, 170, 255, 255))

                .SetColor("selection", WCore::DISABLED, sf::Color(0, 0, 0, 0))
                .SetColor("selection", WCore::ENABLED, sf::Color(170, 170, 170, 255))
                .SetColor("selection", WCore::HOVERED, sf::Color(170, 170, 170, 255))
                .SetColor("selection", WCore::FOCUSED, sf::Color(100, 100, 255, 255))
                .SetColor("selection", WCore::FOCUSED_HOVERED, sf::Color(100, 100, 255, 255));
}

void TextBox::ComputeVisibleString()
{
    m_text.setString("");

    int i = m_padding;
    //while(m_text.getLocalBounds().width < m_size.x - 10 && i < m_string.getSize())
    while(m_text.findCharacterPos(m_text.getString().getSize()).x < m_size.x - 10 && i < m_string.getSize())
    {
        m_text.setString(m_text.getString() + m_string[i]);

        //Remove last character if the text's size exceed the box's size
        if(m_text.findCharacterPos(m_text.getString().getSize()).x >= m_size.x - 10)
        {
            sf::String newString = m_text.getString();
            newString.erase(m_text.getString().getSize() - 1);
            m_text.setString(newString);

            break;
        }

        i++;
    }
}

void TextBox::ComputeCursorPosition()
{
    float selectionBeginPos = 0;
    bool isSelectionBeginOut = false;
    float selectionEndPos = 0;
    bool isSelectionEndOut = false;

    //Compute selection's begin
    int realPosOnString = m_selectionBegin - m_padding;
    if(realPosOnString < 0)
    {
        selectionBeginPos = 5;
        isSelectionBeginOut = true;
        m_isCursorVisible = true;
    }
    else if(realPosOnString > m_text.getString().getSize())
    {
        selectionBeginPos = 5;
        isSelectionBeginOut = true;
        m_isCursorVisible = false;
    }
    else
    {
        selectionBeginPos = m_text.findCharacterPos(realPosOnString).x;
        m_isCursorVisible = true;
    }
    m_cursorShape.setPosition(selectionBeginPos, 5);

    //Compute selection's end
    int realPosOnString2 = m_selectionEnd - m_padding;
    if(realPosOnString2 < 0)
    {
        selectionEndPos = 5;
        isSelectionEndOut = true;
        m_isCursorVisible = false;
    }
    else if(realPosOnString2 > m_text.getString().getSize())
    {
        selectionEndPos = m_size.x - 5;
        isSelectionEndOut = true;
    }
    else
    {
        selectionEndPos = m_text.findCharacterPos(realPosOnString2).x;
        m_isCursorVisible = true;

    }
    m_cursorShape.setSize(sf::Vector2f(selectionEndPos - selectionBeginPos + 2, m_cursorShape.getSize().y));
}

void TextBox::UpdateSelectionDrawable()
{
    WCore::State state = WCore::GetWidgetState(*this);

    if(m_selectionBegin != m_selectionEnd)
        m_cursorShape.setFillColor(GetPalette().GetColor("selection", state));
    else
        m_cursorShape.setFillColor(GetPalette().GetColor("text", state));
}
