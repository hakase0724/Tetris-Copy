#pragma once
namespace MyDirectX
{
	//各ゲームオブジェクトに設定できるタグ
	enum Tag
	{
		//プレイヤー
		PlayerTag = 0,
		//敵
		EnemyTag = 1,
		//自弾
		PlayerBullet = 2,
		//敵弾
		EnemyBullet = 3,
		//動的生成するアイテム　シーン終了時にあれば破棄される
		DynamicInstantiateItem = 4,
		//静的生成するアイテム　シーン終了時に破棄されない
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