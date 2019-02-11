#pragma once
#include "FieldManager.h"
#include "MyEnums.h"
#include "MyStructs.h"

namespace MyDirectX
{
	class TetriMino
	{
	public:
		TetriMino(FieldManager* field);
		~TetriMino() {};
		//�v���C���[�����삷��e�g���~�m���Z�b�g����
		//row = �s�ԍ�
		//column = ��ԍ�
		//type = �`
		//color = �F
		void TetriMinoPreUpdate();
		void TetriMinoUpdate();
		bool MoveTetriMino(int rowMove, int columnMove);
		bool RightRotation();
		bool LeftRotation();
		void SetPlayerTetriMino(int row, int column,TetriMinoType type);
		TetriMinoType GetTetriMinoType() { return mType; }
		void ErasePiece() { mFieldManager->ErasePiece(); }
		void SetIsLanding(bool isLanding) { mIsLanding = isLanding; }
		bool GetIsNext() { return mIsNext; }
	private:
		//��]��ԗ񋓑̗̂v�f��
		const int ROTATIONSTATENUM = 4;
		//���S���W�����ƂɊe�s�[�X�̍��W���v�Z����
		void CalcPiecePosition();
		//�d�����Ă��邩
		bool IsDuplication();
		//���ݕۗL���Ă���s�[�X�̏㉺���E�̍ő�
		PiecePosition mMinPosition;
		//���ݕۗL���Ă���s�[�X�̏㉺���E�̍ŏ�
		PiecePosition mMaxPosition;
		//�Ֆ�
		FieldManager* mFieldManager;
		//�`
		TetriMinoType mType;
		//�F
		PieceColor mColor;
		//��]���
		TetriMinoRotationState mRotationState;
		//�O��̉�]���
		TetriMinoRotationState mPreRotationState;
		//�ۗL����s�[�X
		//0�Ԗڂ����S
		PiecePosition mPiecePositions[4];
		//�t���[���J�n���̃s�[�X�̈ʒu
		PiecePosition mPrePiecePositions[4];
		//���n���Ă��邩
		bool mIsLanding = false;
		int mLandingFrame = 0;
		int mLandingJudgeFrame = 60;
		bool mIsNext = false;
	};
}


