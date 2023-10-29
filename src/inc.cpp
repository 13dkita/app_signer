#include <iostream>
#include <openssl/evp.h>
#include <openssl/rsa.h>

using std::cout;

void function(){
	cout << "include works\n";
}

int generateRSAkey(const int kBits, const int kExp, RSA **rsa){
	int ret = 0;
	BIGNUM *bne = NULL;
	BIO *bp_public = NULL, *bp_private = NULL;
	unisgned long e = RSA_F4;

	//1.Generate RSA key
	bne = BN_new();
	ret = BN_set_word(bne,e);
	if (ret != 1)
		goto error;

	*rsa = RSA_new();
	ret = RSA_generate_key_ex(*rsa, kBits, bne, NULL); 
	if (ret != 1)
		goto error;

	//2. save key
	bp_public = BIO_new_file("public.pem", "w+");
	ret = PEM_write_bio_RSAPublicKey(bp_public, *rsa);
	if(ret != 1){
		goto error;

	BIO_free_all(bp_public);
	RSA_free(rsa);
	BN_free(bne);

	return 1;	

error:
	cout << "ERROR OCCURED\n";
	return EXIT_FAILURE;
}

bool generate_key()
{
	int ret = 0;
	RSA *r = NULL;
	BIGNUM *bne = NULL;
	BIO *bp_public = NULL, *bp_private = NULL;
 
	int bts = 2048;
	unisgned long e = RSA_F4;
	
	// 1. generate rsa key
	bne = BN_new();
	ret = BN_set_word(bne,e);
	if(ret != 1){
		goto free_all;
	}

	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if(ret != 1){
		goto free_all;
	}

	// 2. save public key
	bp_public = BIO_new_file("public.pem", "w+");
	ret = PEM_write_bio_RSAPublicKey(bp_public, r);
	if(ret != 1){
		goto free_all;
	}

	// 3. save private key
	bp_private = BIO_new_file("private.pem", "w+");
	ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

	// 4. free
	free_all:
	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);

	return (ret == 1);
}
