#ifndef TRANSLATION_MGR_H
#define TRANSLATION_MGR_H

#include "Common/Platform.h"
#include "Containers/UnorderedMap.h"
#include "Containers/BasicString.h"
#include "Hash/String/StringID.h"

CONSTEXPR_INLINE const char8* UNTRANSLATED_STRING{ "[MT]" };

class TranslationMgr
{
  public:
    static TranslationMgr& Instance()
    {
        static TranslationMgr sTransMgr{};

        return sTransMgr;
    }

    ~TranslationMgr() = default;

    const char8* Translate( StringID translation );

  protected:
    TranslationMgr();

    UnorderedMap<StringID, String> mTranslations;
};

extern TranslationMgr& GetTranslationMgr();

#endif
