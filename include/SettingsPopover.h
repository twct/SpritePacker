#ifndef __SETTINGS_POPOVER_H__
#define __SETTINGS_POPOVER_H__

#include <gtkmm-3.0/gtkmm/popover.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/box.h>

class SettingsPopover : public Gtk::Popover
{
private:
    Gtk::VBox m_vbox;
    Gtk::Button m_aboutButton;
public:
    SettingsPopover();
    void on_about_button_clicked();
};

#endif