//--------------------------------------------------------------------------------------
// File: VSPTSprite.hlsl
//
//--------------------------------------------------------------------------------------

#include "INCStructs.hlsli"

cbuffer ConstantBuffer : register(b0)
{
	float4x4 World	: packoffset(c0);
	float4x4 View	: packoffset(c4);
	float4x4 Projection	: packoffset(c8);
	float4 Emissive : packoffset(c12);
	float4 Diffuse : packoffset(c13);
};


PSPTInput main(VSPTInput input)
{
	PSPTInput result;
	//���_�̈ʒu��ϊ�
	float4 pos = float4(input.position.xyz, 1.0f);
	//���[���h�ϊ�
	pos = mul(pos, World);
	//�r���[�ϊ�
	pos = mul(pos, View);
	//�ˉe�ϊ�
	pos = mul(pos, Projection);
	//�s�N�Z���V�F�[�_�ɓn���ϐ��ɐݒ�
	result.position = pos;
	result.tex = input.tex;

	return result;
}