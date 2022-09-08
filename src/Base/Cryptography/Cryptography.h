#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "Common/Types.h"

class Stream;

class ICryptography
{
  public:
    virtual ~ICryptography() = default;

    virtual void InitEncKey( const unsigned char* key, const unsigned char* iv ) = 0;
    virtual void InitDecKey( const unsigned char* key, const unsigned char* iv ) = 0;

    virtual void Encrypt( const unsigned char* inData, int inLen, Stream& out ) = 0;
    virtual void Decrypt( const unsigned char* inData, int inLen, Stream& out ) = 0;

  protected:
    ICryptography() = default;
};

#endif
