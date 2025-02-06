//===========================================
// 
// �V�[���x�[�X[scene_base.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_H_
#define _SCENE_H_





namespace Scene {
	class CCommonData;	// ���L�f�[�^
	class CBase {		// �x�[�X�N���X
	protected:
		// ���C�����[�v�O�ɂ̂ݎg�p����R���X�g���N�^
		CBase(CCommonData* const commonData) :
			m_pCommonData(commonData)
		{}
		// �h���N���X�̃R���X�g���N�^�Ŏg�p����R���X�g���N�^
		CBase(const CBase&) = default;

	public:
		//�R�s�[�֎~
		CBase& operator=(const CBase&) = delete;

		// ���z�֐��������f�X�g���N�^
		virtual ~CBase() = default;

		virtual CBase* Update() = 0;	// �X�V
		virtual void Draw() const = 0;	// �`��

		virtual bool IsPose() = 0;
	protected:

		CCommonData* const m_pCommonData;	// ���L�f�[�^

		//���̐����p�֐�
		template<typename T>
		CBase* makeScene();
	private:
	};
}
#endif // _SCENE_H_