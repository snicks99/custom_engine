#include "Containers/ScopedPtr.h"
#include "Stream/Stream.h"
#include "Cryptography/AES_256_CBC.h"

#include <openssl/err.h>

AES256CBC::AES256CBC()
    : mEnc{ nullptr }
    , mDec{ nullptr }
{
    mEnc = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init( mEnc );

    mDec = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init( mDec );
}

AES256CBC::~AES256CBC()
{
    EVP_CIPHER_CTX_cleanup( mEnc );
    EVP_CIPHER_CTX_cleanup( mDec );

    EVP_CIPHER_CTX_free( mEnc );
    EVP_CIPHER_CTX_free( mDec );
}

void AES256CBC::InitEncKey( const unsigned char* key, const unsigned char* iv )
{
    EVP_EncryptInit_ex( mEnc, EVP_aes_256_cbc(), nullptr, key, iv );
}

void AES256CBC::InitDecKey( const unsigned char* key, const unsigned char* iv )
{
    EVP_DecryptInit_ex( mDec, EVP_aes_256_cbc(), nullptr, key, iv );
}

void AES256CBC::Encrypt( const unsigned char* inData, int inLen, Stream& out )
{
    int                      outLen{ static_cast<int>( inLen + AES_BLOCK_SIZE ) };
    ScopedPtr<unsigned char> buffer{ new unsigned char[outLen] };

    unsigned char* outData{ buffer.get() };

    int fLen{ 0 };

    if ( EVP_EncryptInit_ex( mEnc, nullptr, nullptr, nullptr, nullptr ) == 0 )
        return;

    if ( EVP_EncryptUpdate( mEnc, outData, &outLen, inData, inLen ) == 0 )
        return;

    if ( EVP_EncryptFinal_ex( mEnc, outData + outLen, &fLen ) == 0 )
        return;

    out.append( outData, outLen + fLen );
}

void AES256CBC::Decrypt( const unsigned char* inData, int inLen, Stream& out )
{
    int                      outLen{ static_cast<int>( inLen ) };
    ScopedPtr<unsigned char> buffer{ new unsigned char[outLen] };

    unsigned char* outData{ buffer.get() };

    int fLen{ 0 };

    if ( EVP_DecryptInit_ex( mDec, nullptr, nullptr, nullptr, nullptr ) == 0 )
        return;

    if ( EVP_DecryptUpdate( mDec, outData, &outLen, inData, inLen ) == 0 )
        return;

    if ( EVP_DecryptFinal_ex( mDec, outData + outLen, &fLen ) == 0 )
        return;

    out.append( outData, outLen + fLen );
}
