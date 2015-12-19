#ifndef _TESTTV_H_
#define _TESTTV_H_

#include <QApplication>

class TestTV : public QApplication {
  Q_OBJECT;

public:
  TestTV(int argc, char *argv[]);
  ~TestTV();
  
private:
  class Priv;
  Priv *d;

private slots:
  void onVisibilityChanged();
};

#endif /* TESTTV */
