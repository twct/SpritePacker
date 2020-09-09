#include <gtkmm-3.0/gtkmm/label.h>
#include <SpritePackerWindow.h>
#include <iostream>

SpritePackerWindow::SpritePackerWindow() :
    m_button("Hello World")
{
    set_border_width(10);
    set_default_size(1280, 720);

    m_headerBar.set_title("Sprite Packer");
    m_headerBar.set_show_close_button(true);

    m_openButton.set_image_from_icon_name("document-open");
    m_openButton.set_tooltip_text("Open Sprite Sheet");
    m_openButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_open_button_clicked));
    
    m_headerBar.add(m_openButton);

    // m_addButton.set_image_from_icon_name("list-add");
    // m_addButton.set_tooltip_text("Add sprite row");
    // m_addButton.signal_clicked().connect(sigc::mem_fun(*this, &SpritePackerWindow::on_add_button_clicked));
    // m_headerBar.add(m_addButton);

    set_titlebar(m_headerBar);

    add(m_vbox);

        // Gtk::Label label;
    // label.set_text("Hello, world!");
    // m_hbox.add(label);
    // m_hbox.add(m_button);
    // m_hbox.show_all();
    // add(label.get());

    // m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

    // add(m_button);

    // m_headerBar.show();
    // m_button.show();
    show_all();
}

SpritePackerWindow::~SpritePackerWindow()
{

}

void SpritePackerWindow::on_add_button_clicked()
{
    Gtk::Label *label = Gtk::manage(new Gtk::Label());
    label->set_text("Hello, world!");
    label->show();
    m_vbox.pack_start(*label, 1, 1);
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