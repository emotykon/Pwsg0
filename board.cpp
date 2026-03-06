#include "board.h"

board::board()
{
    // Pocz¹tkowa pozycja [cite: 300, 305]
    m_rect_pos.left = 50;
    m_rect_pos.top = 50;
    m_rect_pos.right = m_rect_pos.left + rect_size;
    m_rect_pos.bottom = m_rect_pos.top + rect_size;
}

void board::move(int dx, int dy)
{
    m_rect_pos.left += dx * m_speed;
    m_rect_pos.top += dy * m_speed;
    m_rect_pos.right = m_rect_pos.left + rect_size;
    m_rect_pos.bottom = m_rect_pos.top + rect_size;
}
