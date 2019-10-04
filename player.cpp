#include "player.h"
#include <QDir>
#include <QUrl>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Bus>
#include <QGst/Message>
#include <QGst/Query>
#include <QGst/ClockTime>
#include <QGst/Event>
#include <QGst/StreamVolume>
#include <glib-object.h>
#include <QGst/Sample>
#include <QGst/Buffer>

#include <glib-object.h>
#include <gst/gstsample.h>
#include <gst/gstcaps.h>
#include <gst/video/video.h>
Player::Player(QWidget *parent, QString configure)
    : QGst::Ui::VideoWidget(parent)
{
       this->configure = configure;
       m_pipeline      = QGst::Pipeline::create();
       //m_source        = QGst::ElementFactory::make("videotestsrc", "videotestsrc");
      m_videoSink     = QGst::ElementFactory::make("autovideosink");
       m_source = QGst::Bin::fromDescription(this->configure);
        // m_videoSink = QGst::Bin::fromDescription(this->configure);
       if (!m_pipeline || !m_source || !m_videoSink) {
           QMessageBox::critical(
                       this,
                       "Error",
                       "One or more elements could not be created. Verify that you have all the necessary element plugins installed."
                       );
           return;
       }
       m_videoSink->setProperty("enable-last-sample", true);

       // Add elements to pipeline
       m_pipeline->add(m_source);
       m_pipeline->add(m_videoSink);

       // Link elements
       m_source->link(m_videoSink);

       watchPipeline(m_pipeline);
       setAutoFillBackground(true);

       // Connect to pipeline's bus
       QGst::BusPtr bus = m_pipeline->bus();
       bus->addSignalWatch();
       QGlib::connect(bus, "message", this, &Player::onBusMessage);
       bus.clear();

       m_pipeline->setState(QGst::StatePlaying);
}
Player::~Player()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
    }
}


QGst::State Player::state() const
{
    return m_pipeline ? m_pipeline->currentState() : QGst::StateNull;
}
void Player::play()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePlaying);
    }
}
void Player::pause()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePaused);
    }
}
void Player::stop()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
        //once the pipeline stops, the bus is flushed so we will
        //not receive any StateChangedMessage about this.
        //so, to inform the ui, we have to emit this signal manually.
        Q_EMIT stateChanged();
    }
}
void Player::onBusMessage(const QGst::MessagePtr & message)
{
    switch (message->type()) {
    case QGst::MessageEos: //End of stream. We reached the end of the file.
        stop();
        break;
    case QGst::MessageError: //Some error occurred.
        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();
        stop();
        break;
    case QGst::MessageStateChanged: //The element in message->source() has changed state
        if (message->source() == m_pipeline) {
            handlePipelineStateChange(message.staticCast<QGst::StateChangedMessage>());
        }
        break;
    default:
        break;
    }
}
void Player::handlePipelineStateChange(const QGst::StateChangedMessagePtr & scm)
{
    switch (scm->newState()) {
    case QGst::StatePlaying:
        //start the timer when the pipeline starts playing
        m_positionTimer.start(100);
        break;
    case QGst::StatePaused:
        //stop the timer when the pipeline pauses
        if(scm->oldState() == QGst::StatePlaying) {
            m_positionTimer.stop();
        }
        break;
    default:
        break;
    }
    Q_EMIT stateChanged();
}
void Player::takeSnapshot()
{
    QDateTime currentDate = QDateTime::currentDateTime();
        QString location = QString("%1/snap_%2.png").arg(QDir::homePath()).arg(currentDate.toString(Qt::ISODate));
        QImage snapShot;
        QImage::Format snapFormat;
        QGlib::Value val = m_videoSink->property("last-sample");
        GstSample *videoSample = (GstSample *)g_value_get_boxed(val);
        QGst::SamplePtr sample = QGst::SamplePtr::wrap(videoSample);
        QGst::SamplePtr convertedSample;
        QGst::BufferPtr buffer;
        QGst::CapsPtr caps = sample->caps();
        QGst::MapInfo mapInfo;
        GError *err = NULL;
        GstCaps * capsTo = NULL;
        const QGst::StructurePtr structure = caps->internalStructure(0);
        int width, height;

        width = structure.data()->value("width").get<int>();
        height = structure.data()->value("height").get<int>();

        qDebug() << "Sample caps:" << structure.data()->toString();

        /*
         * { QImage::Format_RGBX8888, GST_VIDEO_FORMAT_RGBx  },
         * { QImage::Format_RGBA8888, GST_VIDEO_FORMAT_RGBA  },
         * { QImage::Format_RGB888  , GST_VIDEO_FORMAT_RGB   },
         * { QImage::Format_RGB16   , GST_VIDEO_FORMAT_RGB16 }
         */
        snapFormat = QImage::Format_RGB888;
        capsTo = gst_caps_new_simple("video/x-raw",
                                     "format", G_TYPE_STRING, "RGB",
                                     "width", G_TYPE_INT, width,
                                     "height", G_TYPE_INT, height,
                                     NULL);

        convertedSample = QGst::SamplePtr::wrap(gst_video_convert_sample(videoSample, capsTo, GST_SECOND, &err));
        if (convertedSample.isNull()) {
            qWarning() << "gst_video_convert_sample Failed:" << err->message;
        }
        else {
            qDebug() << "Converted sample caps:" << convertedSample->caps()->toString();

            buffer = convertedSample->buffer();
            buffer->map(mapInfo, QGst::MapRead);

            snapShot = QImage((const uchar *)mapInfo.data(),
                              width,
                              height,
                              snapFormat);

            qDebug() << "Saving snap to" << location;
            snapShot.save(location);

            buffer->unmap(mapInfo);
        }

        val.clear();
        sample.clear();
        convertedSample.clear();
        buffer.clear();
        caps.clear();
        g_clear_error(&err);
        if (capsTo)
            gst_caps_unref(capsTo);

}
