#ifndef TRACKERSETTINGS_H
#define TRACKERSETTINGS_H

#include <QSettings>

// PWM Values here are divided by 2 plus 400 = actual uS output
#define MIN_PWM 1001 // 1000 % 2 + 400 = 900 uS
#define MAX_PWM 3400 // 3400 /2 + 400 = 2100 uS
#define DEF_MIN_PWM 1200 // 1200 = 1000uS
#define DEF_MAX_PWM 3200 // 1200 = 1000uS
#define MIN_CNT (((MAX_PWM-MIN_PWM)/2)+MIN_PWM-550)
#define MAX_CNT (((MAX_PWM-MIN_PWM)/2)+MIN_PWM+550)
#define MIN_GAIN 0
#define MAX_GAIN 500

#define HT_TILT_REVERSE_BIT     0x01
#define HT_ROLL_REVERSE_BIT     0x02
#define HT_PAN_REVERSE_BIT      0x04

// Axis Mapping
#define AXIS_X 0x00
#define AXIS_Y 0x01
#define AXIS_Z 0x02
#define AXES_MAP(XX,YY,ZZ) (ZZ<<4|YY<<2|XX)
#define X_REV 0x04
#define Y_REV 0x02
#define Z_REV 0x01

class TrackerSettings
{    
public:
    TrackerSettings();
    int Rll_min() const;
    void setRll_min(int value);

    int Rll_max() const;
    void setRll_max(int value);

    int Rll_gain() const;
    void setRll_gain(int value);

    int Rll_cnt() const;
    void setRll_cnt(int value);

    int Pan_min() const;
    void setPan_min(int value);

    int Pan_max() const;
    void setPan_max(int value);

    int Pan_gain() const;
    void setPan_gain(int value);

    int Pan_cnt() const;
    void setPan_cnt(int value);

    int Tlt_min() const;
    void setTlt_min(int value);

    int Tlt_max() const;
    void setTlt_max(int value);

    int Tlt_gain() const;
    void setTlt_gain(int value);

    int Tlt_cnt() const;
    void setTlt_cnt(int value);

    int lpPan() const;
    void setLPPan(int value);

    int lpTiltRoll() const;
    void setLPTiltRoll(int value);

    int gyroWeightTiltRoll() const;
    void setGyroWeightTiltRoll(int value);

    int gyroWeightPan() const;
    void setGyroWeightPan(int value);

    char servoReverse() const;
    void setServoreverse(char value);
    void setRollReversed(bool value);
    void setPanReversed(bool Value);
    void setTiltReversed(bool Value);
    bool isRollReversed();
    bool isTiltReversed();
    bool isPanReversed();

    uint panCh() const;
    void setPanCh(uint value);

    uint tiltCh() const;
    void setTiltCh(uint value);

    uint rollCh() const;
    void setRollCh(uint value);

    int count() const {return 22;}

    uint axisRemap() const {return _data["axisremap"].toUInt();}
    void setAxisRemap(uint value);

    uint axisSign() const {return _data["axissign"].toUInt();}
    void setAxisSign(uint value);

    void storeSettings(QSettings *settings);
    void loadSettings(QSettings *settings);

private:
    QMap<QString,QVariant> _data;
};

#endif // TRACKERSETTINGS_H