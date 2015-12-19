/** 
 * A hello world program that encapsulates the entire
 * application and gui in the object MyApp.
 * 
 * It uses a d pointer to store private data.
 * Note that the widgets are created by on the heap.
 * When using this method it does not work to create
 * widgets on the stack as in the qt examples.
 *
 * @return 
 */
#include "TreeVisibility.h"
#include "TestTV.h"

class TestTV::Priv {
public:
    TreeVisibility *tree_visibility;
};

TestTV::TestTV(int argc, char *argv[])
    : QApplication(argc, argv)
{
    d = new Priv;
    d->tree_visibility = new TreeVisibility;
    d->tree_visibility->addItem("foo/bar/baz");
    d->tree_visibility->addItem("foo/wuz");
    QObject::connect(d->tree_visibility,
                     SIGNAL(visibilityChanged()),
                     this,
                     SLOT(onVisibilityChanged()));


    d->tree_visibility->show();
}

TestTV::~TestTV()
{
    delete d;
}

void TestTV::onVisibilityChanged()
{
    d->tree_visibility->dumpVisibility();
}

int main(int argc, char **argv)
{
    TestTV app(argc, argv);
    return app.exec();
}

