/**
 * @file       VideoControl.h
 * @version    1.0
 * @date       2017年07月08日
 * @author     C_Are
 * @copyright  Leju
 *
 * @brief      接收摄像头图像，VideoControl类的h文件
 */

#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include "global_var.h"
#include "DiscernColor.h"

/**
 * @class     VideoControl
 * @brief     接收摄像头图像
 */

class VideoControl : public QThread
{
    Q_OBJECT
public:
    explicit VideoControl(QObject *parent = 0);
    ~VideoControl();

    void openUrl(const QString &ip);
    void stop();
    void setBrightness(double val);
    void setContrast(int val);
    void setCameraResolution(int w, int h);
    void setHsvInRange(const QString &type, int val);

private slots:
    void restartCamera();

protected:
    virtual void run();

signals:
    void sendInfo(const QString &);
    void sendFrame(QImage &);

private:
    bool isPause;
    bool isSendFrame;         /**< 是否向客户端发送摄像头头像的标志 */

    QString m_client_ip;      /**< 客户端ip */

    Mat srcFrame;

    QUdpSocket *udpSocket;

    Mat rgb_mat;
    QImage rgbImg;
    QImage m_displayImage;

    double alpha;             /**< 亮度 */
    int beta;                 /**< 对比度 */

    void sendFrameOfYUV();
    void sendFrameOfHSV();

};

#endif // VIDEOCONTROL_H
