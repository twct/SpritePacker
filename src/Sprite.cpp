#include <Sprite.h>
#include <iostream>

struct Rectangle
{
    int top, left, right, bottom;
};

Sprite::Sprite(const std::string &path, const Glib::ustring &name, const int x, const int y)
{
    position(x, y);

    auto sourcePixbuf = Gdk::Pixbuf::create_from_file(path);
    auto sourceWidth = sourcePixbuf->get_width();
    auto sourceHeight = sourcePixbuf->get_height();

    auto pixelData = sourcePixbuf->get_pixels();

    Rectangle bounds = {-1, -1, -1, -1};

    for (int py = 0; py < sourceHeight; ++py) {
        for (int px = 0; px < sourceWidth; ++px) {
            int offset = py * sourcePixbuf->get_rowstride() + px * sourcePixbuf->get_n_channels();
            auto pixel = &pixelData[offset];

            if (pixel[3] > 0) {
                if (bounds.top == -1) {
                    bounds.top = py;
                }

                if (bounds.left == -1) {
                    bounds.left = px;
                }
                else if (px < bounds.left) {
                    bounds.left = px;
                }

                if (bounds.right == -1) {
                    bounds.right = px;
                }
                else if (bounds.right < px) {
                    bounds.right = px;
                }

                if (bounds.bottom == -1) {
                    bounds.bottom = py;
                }
                else if (bounds.bottom < py) {
                    bounds.bottom = py;
                }
            }
        }
    }

    int trimHeight = bounds.bottom - bounds.top;
    int trimWidth = bounds.right - bounds.left;

    if (trimWidth > trimHeight) {
        m_size = trimWidth;
    }
    else {
        m_size = trimHeight;
    }

    auto pixbuf = Gdk::Pixbuf::create_subpixbuf(sourcePixbuf, bounds.left, bounds.top, trimWidth, trimHeight);

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

bool Sprite::on_motion_notify(GdkEventMotion *event)
{
    std::cout << "Motion!" << std::endl;
    
    return false;
}