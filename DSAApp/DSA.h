#pragma once
#include <iostream>
#include <utility>
#include "BigInt.h"

using namespace std;

/// <summary>
/// ��������� ������ ��� ��������� DSA
/// </summary>
struct DSAKeys 
{
	uint32_t Q;
	uint32_t P;
	uint32_t G;
	/// <summary>
	/// �������� ����
	/// </summary>
	BigInt PrivateKey;
	/// <summary>
	/// �������� ����
	/// </summary>
	BigInt PublicKey;
};

/// <summary>
/// ������� ��������� ������
/// </summary>
/// <param name="q"></param>
/// <param name="p"></param>
/// <param name="g"></param>
/// <returns>���������� ���������, ���������� �������� �������� Q, P, G,
/// � ����� �������� � �������� �����</returns>
DSAKeys dsa_generate_keys(uint32_t q, uint32_t p, uint32_t g);

/// <summary>
/// ������� �������� �������� �������
/// </summary>
/// <param name="message">������������� ���������</param>
/// <param name="keys">��������� ������</param>
/// <returns>��������� ���� �������� (r,s), �������������� 
/// �������� ������� ���������</returns>
pair<BigInt, BigInt> dsa_create_signature(CString message, DSAKeys keys);

/// <summary>
/// ������� �������� �������� ������� ���������
/// </summary>
/// <param name="message">���������, ������� �������� ��������� ���������</param>
/// <param name="signature">������� ���������</param>
/// <param name="keys">��������� ������</param>
/// <returns>���������� true ���� ������� ����� � false �����</returns>
bool dsa_verify_signature(CString message, pair<BigInt, BigInt> signature, DSAKeys keys);