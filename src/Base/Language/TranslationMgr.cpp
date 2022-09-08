#include "Language/TranslationMgr.h"

TranslationMgr& GetTranslationMgr()
{
    return TranslationMgr::Instance();
}

TranslationMgr::TranslationMgr()
    : mTranslations{}
{
}

const char8* TranslationMgr::Translate( StringID translation )
{
    auto it{ mTranslations.find( translation ) };

    if ( it == mTranslations.end() )
        return UNTRANSLATED_STRING;

    return it->second.c_str();
}
