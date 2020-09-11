#ifndef __SPRITEPACKERWINDOW_H__
#define __SPRITEPACKERWINDOW_H__

#include <gtkmm-3.0/gtkmm/headerbar.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <SpriteGrid.h>

struct FileState
{
    bool isOpen;
    Glib::ustring title;
    std::string path;
    std::string recentDirectory;
};

class SpritePackerWindow : public Gtk::Window
{
private:
    FileState m_fileState;
    Gtk::Button m_button;
    Gtk::Button m_addButton;
    Gtk::Button m_openButton;
    Gtk::Button m_saveButton;
    Gtk::Button m_settingsButton;
    Gtk::HeaderBar m_headerBar;
    SpriteGrid m_grid;
    bool m_modified;
    void set_headerbar_title();
public:
    SpritePackerWindow();
    ~SpritePackerWindow();
    // Signals
    void on_add_button_clicked();
    void on_open_button_clicked();
    void on_save_button_clicked();
};

#endif