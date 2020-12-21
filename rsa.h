//#pragma once
#include<gmp.h>
#include<cstring>
#include<cstdlib>
#include<ctime>

#define KEY_LENGTH 128
#define BASE 2

struct key_pair{
    char* n;
    char* d;
    int e;
};

mpz_t * gen_primes();
key_pair * gen_key_pair();
char * encrypt(const char * plain_text, const char * key_n, int key_e);
char * decrypt(const char * cipher_text, const char * key_n, const char * key);

//To generate two big primes
mpz_t * gen_primes(){
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, time(NULL));

    mpz_t key_p, key_q;
    mpz_init(key_p);
    mpz_init(key_q);

    mpz_urandomb(key_p, grt, KEY_LENGTH / 2);
    mpz_urandomb(key_q, grt, KEY_LENGTH / 2);

    mpz_t * result = new mpz_t[2];
    mpz_init(result[0]);
    mpz_init(result[1]);

    mpz_nextprime(result[0], key_p);
    mpz_nextprime(result[1], key_q);

    mpz_clear(key_p);
    mpz_clear(key_q);

    return result;
}

//To generate key_pair
key_pair * gen_key_pair() {
    mpz_t * primes = gen_primes();

    mpz_t key_n, key_e, key_f;
    mpz_init(key_n);
    mpz_init(key_f);
    mpz_init_set_ui(key_e, 65537);

    mpz_mul(key_n, primes[0], primes[1]);
    mpz_sub_ui(primes[0], primes[0], 1);
    mpz_sub_ui(primes[1], primes[1], 1);
    mpz_mul(key_f, primes[0], primes[1]);

    mpz_t key_d;
    mpz_init(key_d);
    mpz_invert(key_d, key_e, key_f);

    key_pair * result = new key_pair;

    char * buf_n = new char[KEY_LENGTH + 10];
    char * buf_d = new char[KEY_LENGTH + 10];

    mpz_get_str(buf_n, BASE, key_n);
    result->n = buf_n;
    mpz_get_str(buf_d, BASE, key_d);
    result->d = buf_d;
    result->e = 65537;

    mpz_clear(primes[0]);
    mpz_clear(primes[1]);
    mpz_clear(key_n);
    mpz_clear(key_d);
    mpz_clear(key_e);
    mpz_clear(key_f);
    delete []primes;

    return result;
}

char * encrypt(const char * plain_text, const char * key_n, int key_e){
    mpz_t M, C, n;
    mpz_init_set_str(M, plain_text, BASE);
    mpz_init_set_str(n, key_n, BASE);
    mpz_init_set_ui(C, 0);

    mpz_powm_ui(C, M, key_e, n);

    char * result = new char[KEY_LENGTH + 10];
    mpz_get_str(result, BASE, C);

    return result;
}

char * decrypt(const char * cipher_text, const char * key_n, const char * key_d){
    mpz_t M, C, n, d;
    mpz_init_set_str(C, cipher_text, BASE);
    mpz_init_set_str(n, key_n, BASE);
    mpz_init_set_str(d, key_d, BASE);
    mpz_init(M);

    mpz_powm(M, C, d, n);

    char * result = new char[KEY_LENGTH + 10];
    mpz_get_str(result, BASE, M);

    return result;
}