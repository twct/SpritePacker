#include <gtkmm-3.0/gtkmm/aboutdialog.h>
#include <SettingsPopover.h>

SettingsPopover::SettingsPopover()
{
    m_aboutButton.set_label("About Sprite Packer");
    m_aboutButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPopover::on_about_button_clicked));

    m_vbox.add(m_aboutButton); 

    add(m_vbox);
}

void SettingsPopover::on_about_button_clicked()
{
    Gtk::AboutDialog dialog;
    auto parent = dynamic_cast<Gtk::Window*>(get_toplevel());
    if (parent) {
        dialog.set_transient_for(*parent);
    }
    dialog.set_version("1.0.0");
    dialog.set_comments("A simple tool for packing sprite sheets from standalone image files.");
    dialog.set_license("MIT");
    dialog.run();
}