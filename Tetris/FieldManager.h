#pragma once
#include "DXGameObject.h"
#include "MyStructs.h"
#include "Piece.h"
#include <vector>
#include "ReactiveProperty.h"

using namespace MyObservarPattern;
namespace MyDirectX
{
	class Scene;
	class FieldManager
	{
	public:
		FieldManager(Scene* scene);
		~FieldManager() {};
		//������
		void Start();
		//�v���C���[�����삵�Ă����e�g���~�m��ՖʂɌŒ肷��
		void LockPiece();
		//�s�[�X�����X�V����
		void UpdatePiece(int i, int j, PieceState state, PieceColor color);
		//��������
		void CheckErase();
		//�s�[�X�𗎉�������
		void DropPiece();
		//�f�o�b�O���[�h��؂�ւ���
		void ChangeDebugMode();
		//�w�肵����Ԃ̃s�[�X���󔒃s�[�X�ɕς���
		void ChangePieceStateToSpace(PieceState state = PlayerControll);
		//���x���ɉ����������t���[������Ԃ�
		int GetFreeFallFrame() const { return mFreeFallFrame; }
		//�w�肵���ʒu�̃s�[�X��Ԃ��擾����
		PieceState GetPieceState(int i, int j);
		//���������i����Ԃ�
		int GetEraseLineCount() { return mEraseLine.size(); }
		//���݂̃��x����Ԃ�
		int GetLevel() { return mLevelRP->GetValue(); }
	private:
		//�n���ꂽ�Y�������z��͈͓̔����ǂ�������
		bool IsWidthInTheFieldRange(int i, int j);
		//�Ֆʂ̃s�[�X
		std::vector <std::vector<Piece*>> mPieces;
		//�ǂ������i�������邩�L������z��
		std::vector <std::vector<int>> mDropCounts;
		//�����G�t�F�N�g���o��
		void EraseEffect();
		//�s�[�X�̗���
		void PieceDrop();
		Scene* mScene;
		const int ROWNUM = 12;
		const int COLUMNNUM = 24;
		//����ڂ��������邩�L��
		std::vector<int> mEraseLine;
		//���x���Ǘ�
		//���x�����ύX�����ƑΉ�UI���X�V����
		std::unique_ptr<ReactiveProperty<int>, Deleter> mLevelRP;
		//���������i���Ǘ�
		//�����i������������ƑΉ�UI���X�V����
		std::unique_ptr<ReactiveProperty<int>, Deleter> mEraseLineCountRP;
		//���R�����̃t���[����
		int mFreeFallFrame = mDefaultFreeFallFrame;
		//���x��UI
		DXGameObject* mLevelUI;
		DXText* mLevelUIText;
		//������UI
		DXGameObject* mEraseLineCountUI;
		DXText* mEraseLineCountUIText;
		//�f�o�b�O���[�h�ł��邩
		bool mIsDebug = false;
		//���������t���[��
		int mDefaultFreeFallFrame = 60;
		//�ő僌�x��
		int mMaxLevel = 15;
		//�����G�t�F�N�g
		DXGameObject* mOneLineEffect;
		DXGameObject* mOneLineEffect2;
	};
}

