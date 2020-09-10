#include <Sprite.h>
#include <iostream>

Sprite::Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y):
    m_x(x),
    m_y(y)
{
    auto sourcePixbuf = Gdk::Pixbuf::create_from_file(path);
    m_image = Gtk::Image(sourcePixbuf);

    set_tooltip_text(name);

    add_events(Gdk::EventMask::POINTER_MOTION_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this, &Sprite::on_motion_notify));

    add(m_image);
    show_all();
}

Gtk::Image *Sprite::image()
{
    return &m_image;
}

const int Sprite::x() const
{
    return m_x;
}

const int Sprite::y() const
{
    return m_y;
}

bool Sprite::on_motion_notify(GdkEventMotion *event)
{
    std::cout << "Motion!" << std::endl;
    
    return false;
}