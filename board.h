#pragma once
#include <windows.h>

class board
{
public:
    static constexpr LONG rect_size = 60; // Rozmiar prostok¹ta [cite: 289]

    board();

    // Metody do sterowania [cite: 269]
    void move(int dx, int dy);
    RECT get_position() const { return m_rect_pos; }

private:
    RECT m_rect_pos; // Pozycja prostok¹ta [cite: 278]
    int m_speed = 10;
};