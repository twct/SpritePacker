#include <Sprite.h>
#include <iostream>

Sprite::Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y)
{
    position(x, y);

    auto sourcePixbuf = Gdk::Pixbuf::create_from_file(path);
    auto sourceWidth = sourcePixbuf->get_width();
    auto sourceHeight = sourcePixbuf->get_height();

    auto pixelData = sourcePixbuf->get_pixels();

    for (int py = 0; py < sourceHeight; ++py) {
        for (int px = 0; px < sourceWidth; ++px) {
            int offset = py * sourcePixbuf->get_rowstride() + px * sourcePixbuf->get_n_channels();
            auto pixel = &pixelData[offset];

            printf("(%i, %i, %i, %i)\n", pixel[0], pixel[1], pixel[2], pixel[3]);
            if (pixel[3] < 255) {
                pixel[3] = 100;
            }
        }
    }

    m_image = Gtk::Image(sourcePixbuf);

    set_tooltip_text(name);

    add_events(Gdk::EventMask::POINTER_MOTION_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this, &Sprite::on_motion_notify));

    add(m_image);
    show_all();
}

void Sprite::position(const int x, const int y)
{
    m_x = x;
    m_y = y;
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