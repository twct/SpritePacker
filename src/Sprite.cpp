#include <Sprite.h>
#include <iostream>

Sprite::Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y)
{
    position(x, y);

    auto sourcePixbuf = Gdk::Pixbuf::create_from_file(path);
    auto sourceWidth = sourcePixbuf->get_width();
    auto sourceHeight = sourcePixbuf->get_height();

    auto pixelData = sourcePixbuf->get_pixels();

    int top = -1;
    int left = -1;
    int right = -1;
    int bottom = -1;

    for (int py = 0; py < sourceHeight; ++py) {
        for (int px = 0; px < sourceWidth; ++px) {
            int offset = py * sourcePixbuf->get_rowstride() + px * sourcePixbuf->get_n_channels();
            auto pixel = &pixelData[offset];

            if (pixel[3] > 0) {
                if (top == -1) {
                    top = py;
                }

                if (left == -1 || px < left) {
                    left = px;
                }

                if (right == -1 || right < px) {
                    right = px;
                }

                if (bottom == -1 || bottom < py) {
                    bottom = py;
                }
            }
        }
    }

    int trimHeight = bottom - top;
    int trimWidth = right - left;

    if (trimWidth > trimHeight) {
        m_size = trimWidth;
    }
    else {
        m_size = trimHeight;
    }

    auto pixbuf = Gdk::Pixbuf::create_subpixbuf(sourcePixbuf, left, top, trimWidth, trimHeight);
    m_width = pixbuf->get_width();
    m_height = pixbuf->get_height();

    m_image = Gtk::Image(pixbuf);

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

const int Sprite::size() const
{
    return m_size;
}

const int Sprite::width() const
{
    return m_width;
}

const int Sprite::height() const
{
    return m_height;
}

bool Sprite::on_motion_notify(GdkEventMotion *event)
{
    std::cout << "Motion!" << std::endl;
    
    return false;
}