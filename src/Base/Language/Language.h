#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "Common/Platform.h"
#include "Hash/String/StringID.h"

#define CREATE_LANGUAGE_VARIABLE( translate ) \
    CONSTEXPR_INLINE StringID translate { HashStringEval( #translate ) }

// CREATE_LANGUAGE_VARIABLE( DST_OPTION_GRAPHIC_GAMMA );

#endif
