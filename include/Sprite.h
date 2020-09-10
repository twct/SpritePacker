#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <gdkmm-3.0/gdkmm/event.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/box.h>

class Sprite : public Gtk::Box
{
private:
    Gtk::Image m_image;
    int m_x, m_y;
public:
    Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y);
    const Gtk::Image &image() const;
    const int x() const;
    const int y() const;
    bool on_motion_notify(GdkEventMotion *event);
};

#endif