#ifndef PLAYER_H
#define PLAYER_H
#include <QTimer>
#include <QTime>
#include <QGst/Pipeline>
#include <QGst/Ui/VideoWidget>
#include <QMessageBox>
class Player : public QGst::Ui::VideoWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = 0);
    ~Player();
    void setUri(const QString & uri);
    QTime length() const;
    QGst::State state() const;
public Q_SLOTS:
    void play();
    void pause();
    void stop();
    void takeSnapshot();
Q_SIGNALS:
    void stateChanged();
private:
    void onBusMessage(const QGst::MessagePtr & message);
    void handlePipelineStateChange(const QGst::StateChangedMessagePtr & scm);
    QGst::PipelinePtr m_pipeline;
    QTimer m_positionTimer;
    QGst::ElementPtr m_source;
    QGst::ElementPtr m_videoSink;
};
#endif
