//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_
#include "../object/base/save_object.h"
namespace Scene {
	namespace Game {
		class CGameObjectSave : public CSaveObject
		{
		public:
			typedef enum {
				Null = 0,
				PLAYER,	// �v���C���[
				FIELD,	// �t�B�[���h
				BILLBOAD,	// �r���{�[�h
				TREE, // ��
				STAGE_MANEGER,	// �X�e�[�W�}�l�[�W���[
				// �G
				ENEMY000,
				ENEMY100,
				MAX,
			}TYPE;

			CGameObjectSave() = delete;
			CGameObjectSave(CObject* object);
			~CGameObjectSave() override;
			CGameObjectSave* GetPrev()override { return (CGameObjectSave*)CSaveObject::GetPrev(); }
			CGameObjectSave* GetNext()override { return (CGameObjectSave*)CSaveObject::GetNext(); }
			static CGameObjectSave* crate(CObject* object, TYPE type);	//�@����
			TYPE m_type;
		private:
		};


		class CGameData
		{
		public:
			CGameObjectSave* SaveObject(CGameObjectSave::TYPE type, CObject* object);	// �I�u�W�F�N�g�ۑ�
			CGameObjectSave* GetTop();	// �I�u�W�F�N�g�擾
			void FlagDeath(CGameObjectSave* pSave);				// �I�u�W�F�N�g�j��
			void AllFlagDeath();				// �I�u�W�F�N�g�j��
		private:
			CGameObjectSave* m_pTop;
			CGameObjectSave* m_pCur;
		};
	}
}



#endif //_GAME_DATA_H_