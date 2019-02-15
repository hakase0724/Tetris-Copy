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
		//������
		void Start();
		//�t���[���J�n���̑���
		void TetriMinoPreUpdate();
		//�e�g���~�m�̍X�V
		void TetriMinoUpdate();
		//�e�g���~�m���ړ�������
		//�d�����Ă����ꍇ�t�����Ɉړ�������
		//rowMove = �s�ړ���
		//columnMove = ��ړ���
		bool MoveTetriMino(int rowMove, int columnMove);
		//���s�����ꍇ�t�ړ�����
		bool MoveTetriMinoSafe(int rowMove, int columnMove);
		//�E��]
		bool RightRotation();
		//���s�����ꍇ�t�ړ�����
		bool RightRotationSafe();
		//����]
		bool LeftRotation();
		//���s�����ꍇ�t�ړ�����
		bool LeftRotationSafe();
		//�v���C���[�����삷��e�g���~�m���Z�b�g����
		//row = �s�ԍ�
		//column = ��ԍ�
		//type = �`
		void SetPlayerTetriMino(int row, int column,TetriMinoType type);
		//���̃e�g���~�m�̌`��Ԃ�
		TetriMinoType GetTetriMinoType() { return mType; }
		//�e�g���~�m������
		void ErasePiece() { mFieldManager->ErasePiece(); }
		//���n�t���O���Z�b�g����
		void SetIsLanding(bool isLanding) { mIsLanding = isLanding; }
		//���̃e�g���~�m���o����
		bool GetIsNext() { return mIsNext; }
		//�Q�[���I�[�o�[��
		bool GetIsGameOver() { return mIsGameOver; }
		//���֍s��
		void GoNext();
		//���̉�]��Ԃ�Ԃ�
		TetriMinoRotationState GetRotationState() { return mRotationState; }
	private:
		//�s�[�X�̈ʒu���L��
		void MemoryPrePiecePosition();
		//��]��ԗ񋓑̗̂v�f��
		const int ROTATIONSTATENUM = 4;
		//���S���W�����ƂɊe�s�[�X�̍��W���v�Z����
		void CalcPiecePosition();
		//�S�[�X�g�̈ʒu�v�Z
		void CalcGhostPosition();
		//�d�����Ă��邩
		bool IsDuplication();
		//�S�[�X�g���d�����Ă��邩
		bool IsGhostDuplication();
		//���n���Ă��邩
		bool IsLanding();
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
		//�S�[�X�g�̈ʒu
		PiecePosition mGhostPositions[4];
		//���n���Ă��邩
		bool mIsLanding = false;
		//���n�o�߃t���[��
		int mLandingFrame = 0;
		//���n���ČŒ肳���܂ł̃t���[����
		int mLandingJudgeFrame = 30;
		//���̃e�g���~�m���o����
		bool mIsNext = false;
		//�Q�[���I�[�o�[����
		bool mIsGameOver = false;
	};
}


