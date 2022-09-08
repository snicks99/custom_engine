#ifndef AES_256_CBC_H
#define AES_256_CBC_H

#include "Cryptography/Cryptography.h"

#include <openssl/aes.h>
#include <openssl/evp.h>

class AES256CBC : public ICryptography
{
  public:
    AES256CBC();
    virtual ~AES256CBC();

    void InitEncKey( const unsigned char* key, const unsigned char* iv ) override;
    void InitDecKey( const unsigned char* key, const unsigned char* iv ) override;

    void Encrypt( const unsigned char* inData, int inLen, Stream& out ) override;
    void Decrypt( const unsigned char* inData, int inLen, Stream& out ) override;

  protected:
    EVP_CIPHER_CTX* mEnc;
    EVP_CIPHER_CTX* mDec;
};

#endif
