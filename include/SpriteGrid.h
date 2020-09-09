#ifndef __SPRITEGRID_H__
#define __SPRITEGRID_H__

#include <gtkmm-3.0/gtkmm/grid.h>
#include <giomm/application.h>

class SpriteGrid
{
private:
    Gtk::Grid m_grid;
    int m_column, m_row, m_totalColumns;
    int m_spriteSize;
public:
    SpriteGrid();
    Gtk::Grid &grid();
    void add(const Gio::Application::type_vec_files &files);
    const int totalColumns() const;
    const int totalRows() const;
    const int spriteSize() const;
};

#endif