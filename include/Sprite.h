#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <gdkmm-3.0/gdkmm/event.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/box.h>

class Sprite : public Gtk::Box
{
private:
    Gtk::Image m_image;
    int m_x, m_y, m_size;
public:
    Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y);
    Gtk::Image *image();
    void position(const int x, const int y);
    const int x() const;
    const int y() const;
    const int size() const;
    bool on_motion_notify(GdkEventMotion *event);
};

#endif