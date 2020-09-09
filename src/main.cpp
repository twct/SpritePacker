#include <gtkmm-3.0/gtkmm/application.h>
#include <SpritePackerWindow.h>

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "com.atomial.spritepacker");

    SpritePackerWindow mainWindow;

    return app->run(mainWindow);
}