#ifndef DBL_DEFINES_H
#define DBL_DEFINES_H

#include "Common/Types.h"

namespace DBO
{
    enum Race : uint8
    {
        RACE_HUMAN = 0,
        RACE_NAMEK,
        RACE_MAJIN,

        MAX_RACES,

        INVALID_RACE = 0xFF
    };

    enum Class : uint8
    {
        HUMAN_CLASS_MARTIAL_ARTIST = 0,
        HUMAN_CLASS_SPIRITUALIST,

        HUMAN_CLASS_ENGINEER,

        NAMEK_CLASS_WARRIOR,
        NAMEK_CLASS_DRAGON_CLAN,

        MAJIN_CLASS_MIGHTY,
        MAJIN_CLASS_WONDER,

        HUMAN_CLASS_FIGHTER,
        HUMAN_CLASS_SWORDMAN,

        HUMAN_CLASS_TURTLE_HERMIT,
        HUMAN_CLASS_CRANE_HERMIT,

        HUMAN_CLASS_MACHINE_MANIAC,
        HUMAN_CLASS_GUN_MANIAC,

        NAMEK_CLASS_DARK_WARRIOR,
        NAMEK_CLASS_SHADOW_KNIGHT,

        NAMEK_CLASS_DENDE_PRIEST,
        NAMEK_CLASS_POKO_PRIEST,

        MAJIN_CLASS_MUSICIAN,
        MAJIN_CLASS_GRAND_CHEF,

        MAJIN_CLASS_PLASMA,
        MAJIN_CLASS_KARMA,

        MAX_CLASSES,

        INVALID_CLASS = 0xFF
    };

}    // namespace DBO

#endif
