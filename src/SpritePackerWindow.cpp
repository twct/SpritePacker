#include <gtkmm-3.0/gtkmm/filechooserdialog.h>
#include <gdkmm-3.0/gdkmm/general.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <SpritePackerWindow.h>
#include <cairomm/surface.h>
#include <iostream>
#include <sstream>

SpritePackerWindow::SpritePackerWindow() :
    m_button("Hello World")
{
    set_border_width(10);
    set_default_size(1280, 720);

    m_fileTitle = "Untitled";
    m_modified = false;

    // m_headerBar.set_title("Sprite Packer");
    set_headerbar_title();
    m_headerBar.set_show_close_button(true);

    m_saveButton.set_label("Save");
    m_saveButton.set_tooltip_text("Save Sprite Sheet");
    m_saveButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_save_button_clicked));
    // m_exportButton.set_sensitive(false);

    m_openButton.set_label("Open");
    m_openButton.set_tooltip_text("Open Sprite Sheet");
    m_openButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_open_button_clicked));

    m_settingsButton.set_image_from_icon_name("open-menu-symbolic");

    m_headerBar.pack_start(m_addButton);
    m_headerBar.pack_start(m_openButton);
    
    m_headerBar.pack_end(m_settingsButton);
    m_headerBar.pack_end(m_saveButton);

    m_addButton.set_image_from_icon_name("list-add");
    m_addButton.set_tooltip_text("Add Sprite(s)");
    m_addButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_add_button_clicked));

    set_titlebar(m_headerBar);

    add(m_grid.grid());

    show_all();
}

SpritePackerWindow::~SpritePackerWindow()
{

}

void SpritePackerWindow::set_headerbar_title()
{
    auto spriteSize = m_grid.spriteSize();

    std::ostringstream oss;

    if (m_modified) {
        oss << "*";
    }

    oss << m_fileTitle;
    
    if (spriteSize > 0) {
        oss << " (" <<  spriteSize << "x" << spriteSize << ")";
    }

    oss << " — Sprite Packer";

    m_headerBar.set_title(Glib::ustring(oss.str()));
}

void SpritePackerWindow::on_add_button_clicked()
{
    auto filter = Gtk::FileFilter::create();
    filter->add_pattern("*.png");

    Gtk::FileChooserDialog dialog("Add Sprites");
    dialog.set_transient_for(*this);
    dialog.set_select_multiple(true);
    dialog.set_filter(filter);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    switch (result)
    {
        case Gtk::RESPONSE_OK:
        {
            m_grid.add(dialog.get_files());
            m_modified = true;
            set_headerbar_title();
        }
        break;
    }
}

void SpritePackerWindow::on_open_button_clicked()
{
    auto filter = Gtk::FileFilter::create();
    filter->add_pattern("*.png");

    Gtk::FileChooserDialog dialog("Open Sprite Sheet");
    dialog.set_transient_for(*this);
    dialog.set_filter(filter);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    switch (result)
    {
        case Gtk::RESPONSE_OK:
        {
            auto file = dialog.get_file();

            std::cout << file->get_basename() << ": " << file->get_path() << std::endl;
        }
        break;
    }
}

void SpritePackerWindow::on_save_button_clicked()
{
    auto spriteSize = m_grid.spriteSize();

    auto width = m_grid.totalColumns() * spriteSize;
    auto height = m_grid.totalRows() * spriteSize;

    auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
    auto context = Cairo::Context::create(surface);

    auto child = m_grid.grid().get_child_at(0, 0);
    auto image = dynamic_cast<Gtk::Image*>(child);

    int x = 0;
    int y = 0;

    Gdk::Cairo::set_source_pixbuf(context, image->get_pixbuf(), x, y);
    context->paint();
    surface->write_to_png("/tmp/test.png");

    std::cout << width << "x" << height << std::endl;
}