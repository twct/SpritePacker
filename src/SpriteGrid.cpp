#include <gtkmm-3.0/gtkmm/image.h>
#include <SpriteGrid.h>
#include <iostream>
#include <Sprite.h>

inline int closest(int a, int b)
{
    return (a + b / 2) / b * b;
}

SpriteGrid::SpriteGrid()
{
    m_column = 0;
    m_totalColumns = 0;
    m_row = 0;
    m_spriteSize = 0;

    m_grid.set_row_spacing(25);
    m_grid.set_column_spacing(25);
}

Gtk::Grid &SpriteGrid::grid()
{
    return m_grid;
}

const int SpriteGrid::totalColumns() const
{
    return m_totalColumns;
}

const int SpriteGrid::totalRows() const
{
    return m_row;
}

const int SpriteGrid::spriteSize() const
{
    return m_spriteSize;
}

void SpriteGrid::add(const Gio::Application::type_vec_files &files)
{
    m_column = 0;

    for (auto &file : files) {
        auto sourcePixbuf = Gdk::Pixbuf::create_from_file(file->get_path());
        auto sourceWidth = sourcePixbuf->get_width();
        auto sourceHeight = sourcePixbuf->get_height();
        auto rowStride = sourcePixbuf->get_rowstride();
        auto pixelData = sourcePixbuf->get_pixels();
        auto pixelLen = sourceWidth * sourceHeight * rowStride;

        auto sprite = Gtk::make_managed<Sprite>(file->get_path(), file->get_basename(), m_column, m_row);
        sprite->show();
        m_grid.attach(*sprite, m_column, m_row);

        if (sprite->size() > m_spriteSize) {
            m_spriteSize = closest(sprite->size(), 2);
        }

        ++m_column;
    }

    ++m_row;

    if (m_column > m_totalColumns) {
        m_totalColumns = m_column;
    }
}