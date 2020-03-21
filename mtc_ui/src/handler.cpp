#include "handler.h"
#include <QDebug>


Handler::Handler(QObject *_parent):
    QObject(_parent)
{

}

void Handler::onDirStopClicked() {
    qDebug() << __FUNCTION__;
    emit dirStopClicked();
}

void Handler::onDirForwardClicked() {
    qDebug() << __FUNCTION__;
    emit dirForwardClicked();
}

void Handler::onDirBackwardClicked() {
    qDebug() << __FUNCTION__;
    emit dirBackwardClicked();
}

void Handler::onPoint1_button_clicked() {
    qDebug() << __FUNCTION__;
    emit point1ButtonClicked();
}

void Handler::onPoint2_button_clicked() {
    qDebug() << __FUNCTION__;
    emit point2ButtonClicked();
}

void Handler::onShort_whistle_clicked() {
    qDebug() << __FUNCTION__;
    emit shortWhistleClicked();
}



void Handler::onSliderPlusClicked()
{
    setSliderValue(m_current_slider_value + m_slider_increment);
}

void Handler::onSliderMinusClicked()
{
    setSliderValue(m_current_slider_value - m_slider_increment);
}

double Handler::minSliderValue() const
{
    return m_min_slider_value;
}

double Handler::maxSliderValue() const
{
    return m_max_sldier_value;
}

double Handler::sliderIncrement() const
{
    return m_slider_increment;
}

double Handler::sliderValue() const
{
    return m_current_slider_value;
}

void Handler::setSliderValue(double _sliderValue)
{
    if (_sliderValue >= m_min_slider_value && _sliderValue <= m_max_sldier_value && _sliderValue != m_current_slider_value) {
        m_current_slider_value = _sliderValue;
        emit sliderValueChanged(m_current_slider_value);
    }
}
