#include <gtkmm-3.0/gtkmm/filechooserdialog.h>
#include <gdkmm-3.0/gdkmm/general.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <SpritePackerWindow.h>
#include <cairomm/surface.h>
#include <Sprite.h>
#include <iostream>
#include <sstream>

SpritePackerWindow::SpritePackerWindow() :
    m_button("Hello World")
{
    set_border_width(10);
    set_default_size(1280, 720);
;
    m_fileState.isOpen = false;
    m_fileState.title = "Untitled";
    m_fileState.recentDirectory = ".";
    m_modified = false;

    set_headerbar_title();
    m_headerBar.set_show_close_button(true);

    m_saveButton.set_label("Save");
    m_saveButton.set_tooltip_text("Save Sprite Sheet");
    m_saveButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_save_button_clicked));

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

    oss << m_fileState.title;
    
    if (spriteSize > 0) {
        oss << " (" <<  spriteSize << "x" << spriteSize << ")";
    }

    oss << " — Sprite Packer";

    m_headerBar.set_title(Glib::ustring(oss.str()));
    m_saveButton.set_sensitive(m_modified);
}

void SpritePackerWindow::on_add_button_clicked()
{
    auto filter = Gtk::FileFilter::create();
    filter->add_pattern("*.png");

    Gtk::FileChooserDialog dialog("Add Sprites");
    dialog.set_transient_for(*this);
    dialog.set_current_folder(m_fileState.recentDirectory);
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
            m_fileState.recentDirectory = dialog.get_current_folder();
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
    if (!m_fileState.isOpen) {
        auto filter = Gtk::FileFilter::create();
        filter->set_name("PNG Images");
        filter->add_pattern("*.png");

        Gtk::FileChooserDialog dialog("Save Sprite Sheet");
        dialog.set_action(Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.set_do_overwrite_confirmation(true);
        dialog.add_filter(filter);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);

        int result = dialog.run();

        switch (result) {
            case Gtk::RESPONSE_OK:
            {
                auto file = dialog.get_file();
                m_fileState.isOpen = true;
                m_fileState.path = file->get_path();
                m_fileState.title = Glib::ustring(file->get_basename());
            }
            break;
        }
    }

    auto spriteSize = m_grid.spriteSize();

    auto width = m_grid.totalColumns() * spriteSize;
    auto height = m_grid.totalRows() * spriteSize;

    auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
    auto context = Cairo::Context::create(surface);

    for (auto &child : m_grid.grid().get_children()) {
        auto sprite = dynamic_cast<Sprite*>(child);
        auto image = sprite->image();
        // TODO: Add options to snap to center, top, left, bottom, right for x and y
        int x = (sprite->x() * spriteSize) + ((spriteSize / 2) - (sprite->width() / 2));
        int y = (sprite->y() * spriteSize) + (spriteSize - sprite->height());
        Gdk::Cairo::set_source_pixbuf(context, image->get_pixbuf(), x, y);
        context->paint();
    }
    
    surface->write_to_png(m_fileState.path);
    m_modified = false;
    set_headerbar_title();
}