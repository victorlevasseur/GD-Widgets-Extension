#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "WidgetsCore/Widget.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>


class GD_EXTENSION_API TextBox : public WCore::Widget
{
public:
    TextBox();
    virtual ~TextBox();

    virtual void Draw(sf::RenderTarget &wnd);

    int GetSelectionBegin() const;
    int GetSelectionEnd() const;

    void Select(int position);
    void Select(int selectionBegin, int selectionEnd);

    int GetCharacterOnPoint(sf::Vector2f position) const;

    void SetText(sf::String text);
    sf::String GetText() const;

    sf::String GetSelectedText() const;

    void SetFont(const sf::Font &font);
    const sf::Font* GetFont() const;

    void SetCharacterSize(unsigned int s);
    unsigned int GetCharacterSize() const;

    void SetBorderThickness(int thickness);
    int GetBorderThickness() const;

    void AllowTextSelection(bool allow = true);
    bool IsAllowingTextSelection() const;

protected:
    virtual void HandleMouseButtonEvent(sf::Mouse::Button button, bool pressed, int x, int y);
    virtual void HandleMouseMoveEvent(int x, int y);
    virtual void HandleKeyboardEvent(sf::Keyboard::Key button, bool pressed);
    virtual void HandleTextEntered(sf::Uint32 character);

    virtual void HandleSizeChange();

    virtual void HandleTime(float time);

    virtual void UpdateDrawables();

private:

    enum MousePosition {LeftBorder, RightBorder, NoBorder};

    void InitPalette();

    void ComputeVisibleString();
    void ComputeCursorPosition();

    void UpdateSelectionDrawable();

    sf::RectangleShape m_backgroundShape;
    sf::String m_string;
    sf::Text m_text;

    int m_padding;

    int m_selectionBegin;
    int m_selectionEnd;
    bool m_allowTextSelection;

    struct
    {
        int first;
        int second;

        bool isDragging;

        float timer;

        MousePosition mousePosition;

    } m_dragSelection;

    bool m_isCursorVisible;
    sf::RectangleShape m_cursorShape;
};


#endif
