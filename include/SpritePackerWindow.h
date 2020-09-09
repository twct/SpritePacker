#ifndef __SPRITEPACKERWINDOW_H__
#define __SPRITEPACKERWINDOW_H__

#include <gtkmm-3.0/gtkmm/filechooserdialog.h>
#include <gtkmm-3.0/gtkmm/headerbar.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/label.h>

class SpritePackerWindow : public Gtk::Window
{
private:
    Gtk::Button m_button;
    Gtk::Button m_addButton;
    Gtk::Button m_openButton;
    Gtk::HeaderBar m_headerBar;
    Gtk::VBox m_vbox;
    Gtk::Label m_label;
public:
    SpritePackerWindow();
    ~SpritePackerWindow();
    // Signals
    void on_add_button_clicked();
    void on_open_button_clicked();
};

#endif