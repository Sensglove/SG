#ifndef REKA3D_HPP
#define REKA3D_HPP

#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
	Q_OBJECT

	public:
		double kat1;
		double kat2;
		double kat3;
		double kat4;
		double kat5;
		Viewer(QWidget *wRodzic = 0);
		void Reka();

	protected:
	  virtual void draw();
	  virtual void init();

  private:
  	qglviewer::Camera cam;

  	public slots:
  		void aktualizuj(QStringList);
};

#endif