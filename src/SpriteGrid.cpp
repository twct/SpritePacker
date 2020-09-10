#include <gtkmm-3.0/gtkmm/image.h>
#include <SpriteGrid.h>
#include <iostream>
#include <Sprite.h>

int closest(int a, int b)
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

        // if (sourceWidth > m_spriteSize || sourceHeight > m_spriteSize) {
        //     if (sourceWidth > sourceHeight) {
        //         m_spriteSize = closest(sourceWidth, 2);
        //     }
        //     else {
        //         m_spriteSize = closest(sourceHeight, 2);
        //     }
        // }

        // std::cout << "Sprite Size: " << m_spriteSize << std::endl;
    
        // auto image = Gtk::make_managed<Gtk::Image>(sourcePixbuf);
        // image->set_tooltip_text(file->get_basename());
        // image->show();

        // m_grid.attach(*image, m_column, m_row);
        ++m_column;
        #if test
        auto sourcePixbuf = Gdk::Pixbuf::create_from_file(file->get_path());
        auto sourceWidth = sourcePixbuf->get_width();
        auto sourceHeight = sourcePixbuf->get_height();
        auto pixelData = sourcePixbuf->get_pixels();
        auto pixelLen = sourceWidth * sourceHeight;
        // pixels.erase(
        //     std::remove_if(pixels.begin(), pixels.end(), [](const guint8 &byte) {
        //         // return byte == 0x00;
        //         return false;
        //     })
        // , pixels.end());
        // for (auto &pixel : pixels) {
        //     printf("%02X ", pixel);
        // }
        // printf("\n");
        auto pixbuf = Gdk::Pixbuf::create_from_data(pixelData, sourcePixbuf->get_colorspace(), sourcePixbuf->get_has_alpha(), sourcePixbuf->get_bits_per_sample(), sourceWidth, sourceHeight, sourcePixbuf->get_rowstride());
        auto image = Gtk::make_managed<Gtk::Image>(pixbuf);
        image->set_tooltip_text(file->get_basename());
        image->show();

        m_grid.attach(*image, m_column, m_row);
        ++m_column;
        #endif
    }

    ++m_row;

    if (m_column > m_totalColumns) {
        m_totalColumns = m_column;
    }
}