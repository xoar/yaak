#ifndef SETTINGSVALUE_H
#define SETTINGSVALUE_H

#include "Color.h"
#include "Position.h"

union SettingsValue
{
    int intValue;
    double doubleValue;
    Color colorValue;
    Position positionValue;
    const char *stringValue;
};

#endif