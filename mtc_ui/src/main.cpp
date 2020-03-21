
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include <QThread>
#include <QObject>

#include "ros/ros.h"

#include "handler.h"
#include "communicator.h"


int main(int argc, char **argv){
    qDebug() << "ENTERED MAIN";
    ros::init(argc, argv, "group_ui");
    qDebug() << "ROS INITIALIZED";
    QApplication app(argc, argv);
    qDebug() << "QT INITIALIZED";


    QThread *communicator_thread = new QThread();
    Handler *handler = new Handler();
    Communicator *communicator = new Communicator();



    communicator->moveToThread(communicator_thread);
    QObject::connect(communicator_thread, &QThread::started, communicator, &Communicator::run);
    QObject::connect(handler, &Handler::dirStopClicked, communicator, &Communicator::reportDirStopClicked, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::dirForwardClicked, communicator, &Communicator::reportDirForwardClicked, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::dirBackwardClicked, communicator, &Communicator::reportDirBackwardClicked, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::sliderValueChanged, communicator, &Communicator::handleSpeedChange, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::point1ButtonClicked, communicator, &Communicator::reportPoint1ButtonClicked, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::point2ButtonClicked, communicator, &Communicator::reportPoint2ButtonClicked, Qt::QueuedConnection);
    QObject::connect(handler, &Handler::shortWhistleClicked, communicator, &Communicator::reportShortWhistleClicked, Qt::QueuedConnection);



    communicator_thread->start();

    QQuickView view;
    view.rootContext()->setContextProperty("handler", handler);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///handler.qml"));
    view.show();


    return app.exec();
}

