#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class Handler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double minSliderValue READ minSliderValue CONSTANT)
    Q_PROPERTY(double maxSliderValue READ maxSliderValue CONSTANT)
    Q_PROPERTY(double sliderIncrement READ sliderIncrement CONSTANT)
    Q_PROPERTY(double sliderValue READ sliderValue WRITE setSliderValue NOTIFY sliderValueChanged)

signals:
    void dirStopClicked();
    void dirForwardClicked();
    void dirBackwardClicked();
    void point1ButtonClicked();
    void point2ButtonClicked();
    void shortWhistleClicked();

    void sliderValueChanged(double);

public:
    Handler(QObject *_parent = nullptr);


public slots:
    void onDirStopClicked();
    void onDirForwardClicked();
    void onDirBackwardClicked();
    void onSliderPlusClicked();
    void onSliderMinusClicked();
    void onPoint1_button_clicked();
    void onPoint2_button_clicked();
    void onShort_whistle_clicked();


    double minSliderValue () const;
    double maxSliderValue () const;
    double sliderIncrement() const;
    double sliderValue() const;

    void setSliderValue(double _sliderValue);

private:
    bool emergencyStop = false;
    bool patrolOnWaypoints = false;

    double m_current_slider_value = 0.0;
    double m_min_slider_value = 0.00;
    double m_max_sldier_value = 1.0;
    double m_slider_increment = 1.0/255.0;

};

#endif // HANDLER_H
