#pragma once
#include <iostream>
#include <utility>
#include "BigInt.h"

using namespace std;

/// <summary>
/// Структура ключей для алгоритма DSA
/// </summary>
struct DSAKeys 
{
	uint32_t Q;
	uint32_t P;
	uint32_t G;
	/// <summary>
	/// Закрытый ключ
	/// </summary>
	BigInt PrivateKey;
	/// <summary>
	/// Открытый ключ
	/// </summary>
	BigInt PublicKey;
};

/// <summary>
/// Функция генерации ключей
/// </summary>
/// <param name="q"></param>
/// <param name="p"></param>
/// <param name="g"></param>
/// <returns>Возвращает структуру, содержащую исходнык значения Q, P, G,
/// а также закрытый и открытый ключи</returns>
DSAKeys dsa_generate_keys(uint32_t q, uint32_t p, uint32_t g);

/// <summary>
/// Функция создания цифровой подписи
/// </summary>
/// <param name="message">Подписываемое сообщение</param>
/// <param name="keys">Структура ключей</param>
/// <returns>Возвращае пару значений (r,s), представляющих 
/// цифровую подпись сообщения</returns>
pair<BigInt, BigInt> dsa_create_signature(CString message, DSAKeys keys);

/// <summary>
/// Функция проверки цифровой подписи сообщения
/// </summary>
/// <param name="message">Сообщение, подпись которого требуется проверить</param>
/// <param name="signature">Подпись сообщения</param>
/// <param name="keys">Структура ключей</param>
/// <returns>Возвращает true если подпись верна и false иначе</returns>
bool dsa_verify_signature(CString message, pair<BigInt, BigInt> signature, DSAKeys keys);