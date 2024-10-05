#include "pch.h"
#include "DSA.h"
#include "SHA256.h"
#include <iostream>
#include <random>
#include <math.h>
#include <cstring>

DSAKeys dsa_generate_keys(uint32_t q, uint32_t p, uint32_t g) {
	DSAKeys keys;

	// генерация случайного числа k
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, q - 1);

	keys.Q = q;
	keys.P = p;
	keys.G = g;
	keys.PrivateKey = dist(gen);
	keys.PublicKey = PowMod(g, keys.PrivateKey, p);

	return keys;
}

pair<BigInt, BigInt> dsa_create_signature(CString message, DSAKeys keys) {
	// генерация случайного числа k
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, keys.Q - 1);
	uint32_t k = dist(gen);

	uint32_t g = keys.G;
	uint32_t p = keys.P;
	uint32_t q = keys.Q;
	BigInt r = PowMod(g, k, p) % q;
	
	uint8_t hash_array[32];
	sha256_easy_hash(message, message.GetLength(), hash_array);
	uint64_t hash = sha256_easy_hash_int64(hash_array);
		
	BigInt s = PowMod(k, -1, q) * (hash + keys.PrivateKey * r) % q;

	return pair<BigInt, BigInt>(r, s);
}

bool dsa_verify_signature(CString message, pair<BigInt, BigInt> signature, DSAKeys keys) {
	BigInt r = signature.first;
	BigInt s = signature.second;

	uint8_t hash_array[32];
	sha256_easy_hash(message, message.GetLength(), hash_array);
	uint64_t hash = sha256_easy_hash_int64(hash_array);

	BigInt w = PowMod(s, -1, keys.Q);
	BigInt u1 = (hash * w) % keys.Q;
	BigInt u2 = (r * w) % keys.Q;
	BigInt v = ((PowMod(keys.G, u1, keys.P) * PowMod(keys.PublicKey, u2, keys.P)) % keys.P) % keys.Q;

	return v == r;
}