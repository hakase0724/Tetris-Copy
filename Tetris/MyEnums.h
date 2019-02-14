#pragma once
namespace MyDirectX
{
	//�e�Q�[���I�u�W�F�N�g�ɐݒ�ł���^�O
	enum Tag
	{
		//�v���C���[
		PlayerTag = 0,
		//�G
		EnemyTag = 1,
		//���e
		PlayerBullet = 2,
		//�G�e
		EnemyBullet = 3,
		//���I��������A�C�e���@�V�[���I�����ɂ���Δj�������
		DynamicInstantiateItem = 4,
		//�ÓI��������A�C�e���@�V�[���I�����ɔj������Ȃ�
		StaticInstantiateItem = 5,
	};

	enum PieceState
	{
		Space,
		PlayerControll,
		FieldLock,
		Wall,
		Ghost
	};

	enum PieceColor
	{
		Red,
		Blue,
		Yellow,
		Orange,
		Purple,
		Green,
		LightBlue,
	};

	enum TetriMinoType
	{
		I,
		O,
		T,
		J,
		L,
		S,
		Z,
	};

	enum TetriMinoRotationState
	{
		A,
		B,
		C,
		D,
	};

	enum SuperRotationState
	{
		Zero,
		One,
		Two,
		Three,
		Four
	};

}