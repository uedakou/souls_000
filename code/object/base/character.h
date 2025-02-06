//===========================================
// 
// �L�����N�^�[[charactor.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "motion.h"
#include "../../base/calculation.h"

#define BASE_RESISTANCE 0.01f


class CCharacter : public CObjectMotion
{
public:
	CCharacter();
	virtual ~CCharacter()	override;
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��

	virtual int GetNextMotion() override ;	// �����[�V����

		// �X�e�[�^�X�ݒ�
	void SetLife(int nLife)				{ m_nLife = nLife; }				// �̗͐ݒ�
	void SetInvincible(int nInvincible) { m_nCntInvincible = nInvincible; }	// ���G���Ԑݒ�
	void SetAttcak(int nAttcak)			{ m_nAttcak = nAttcak; }			// �U���͐ݒ�
	void SetDefense(int nDefense)		{ m_nDefense = nDefense; }			// �h��͐ݒ�
	void SetSpeed(int nSpeed)			{ m_fSpeed = nSpeed; }				// ���x�ݒ�
	// �X�e�[�^�X�擾
	int GetLife()		{ return m_nLife; }				// �̗͐ݒ�
	int GetInvincible() { return m_nCntInvincible; }	// ���G���Ԑݒ�
	int GetAttcak()		{ return m_nAttcak; }			// �U���͐ݒ�
	int GetDefense()	{ return m_nDefense; }			// �h��͐ݒ�
	int GetSpeed()		{ return m_fSpeed; }			// ���x�ݒ�
	// �X�e�[�^�X���Z
	void AddLife(int nLife)				{ m_nLife += nLife; }						// �̗͐ݒ�
	void AddInvincible(int nInvincible)	{ m_nCntInvincible += nInvincible; }		// ���G���Ԑݒ�
	void AddAttcak(int nAttcak)			{ m_nAttcak += nAttcak; }					// �U���͐ݒ�
	void AddDefense(int nDefense)		{ m_nDefense += nDefense; }					// �h��͐ݒ�
	void AddSpeed(int fSpeed)			{ m_fSpeed += fSpeed; }						// ���x�ݒ�

	// �^���ʐݒ�
	void SetMoveX(X x) { m_xmove = x;}
	void SetMovePos(D3DXVECTOR3 pos) { m_xmove.pos = pos; }// �ʒu�ݒ�
	void SetMovePosX(float x) { m_xmove.pos.x = x; }// �ʒu�ݒ�
	void SetMovePosY(float y) { m_xmove.pos.y = y; }// �ʒu�ݒ�
	void SetMovePosZ(float z) { m_xmove.pos.z = z; }// �ʒu�ݒ�
	void SetMoveRot(D3DXVECTOR3 rot) { m_xmove.rot = rot; }// �����ݒ�
	void SetMoveRotX(float x) { m_xmove.rot.x = x; }// �����ݒ�
	void SetMoveRotY(float y) { m_xmove.rot.y = y; }// �����ݒ�
	void SetMoveRotZ(float z) { m_xmove.rot.z = z; }// �����ݒ�
	void SetMoveSiz(D3DXVECTOR3 siz) { m_xmove.siz = siz; }// �傫���ݒ�
	void SetMoveSizX(float x) { m_xmove.siz.x = x; }// �傫���ݒ�
	void SetMoveSizY(float y) { m_xmove.siz.y = y; }// �傫���ݒ�
	void SetMoveSizZ(float z) { m_xmove.siz.z = z; }// �傫���ݒ�

	X GetMoveX() { return m_xmove; }
	D3DXVECTOR3 GetMovePos() { return m_xmove.pos; }// �^���ʐݒ�
	D3DXVECTOR3 GetMoveRot() { return m_xmove.rot; }// ��]�ʐݒ�
	D3DXVECTOR3 GetMoveSiz() { return m_xmove.siz; }// �c���ʐݒ�

	void AddMoveX(X x) {
		m_xmove.pos += x.pos;
		m_xmove.rot += x.rot;
		m_xmove.siz += x.siz;
	}
	void AddMovePos(D3DXVECTOR3 pos) { m_xmove.pos += pos; }// �ʒu�ݒ�
	void AddMovePosX(float x) { m_xmove.pos.x += x; }// �傫���ݒ�
	void AddMovePosY(float y) { m_xmove.pos.y += y; }// �傫���ݒ�
	void AddMovePosZ(float z) { m_xmove.pos.z += z; }// �傫���ݒ�
	void AddMoveRot(D3DXVECTOR3 rot) { m_xmove.rot += rot; }// �����ݒ�
	void AddMoveRotX(float x) { m_xmove.rot.x += x; }// �傫���ݒ�
	void AddMoveRotY(float y) { m_xmove.rot.y += y; }// �傫���ݒ�
	void AddMoveRotZ(float z) { m_xmove.rot.z += z; }// �傫���ݒ�
	void AddMoveSiz(D3DXVECTOR3 siz) { m_xmove.siz += siz; }// �傫���ݒ�
	void AddMoveSizX(float x) { m_xmove.siz.x += x; }// �傫���ݒ�
	void AddMoveSizY(float y) { m_xmove.siz.y += y; }// �傫���ݒ�
	void AddMoveSizZ(float z) { m_xmove.siz.z += z; }// �傫���ݒ�

	// �����蔻��

	void SetCollisionX(X pX) { m_Xcollision = pX; }	//	�����蔻��ݒ�
	void SetCollisionPos(D3DXVECTOR3 pPos) { m_Xcollision.pos = pPos; }	//	�����蔻��ݒ�
	void SetCollisionRot(D3DXVECTOR3 pRot) { m_Xcollision.rot = pRot; }	//	�����蔻��ݒ�
	void SetCollisionSiz(D3DXVECTOR3 pSiz) { m_Xcollision.siz = pSiz; }	//	�����蔻��ݒ�

	X GetCollisionX() { return m_Xcollision; }	//	�����蔻��擾
	D3DXVECTOR3 GetCollisionPos() { return m_Xcollision.pos; }	//	�����蔻��擾
	D3DXVECTOR3 GetCollisionRot() { return m_Xcollision.rot; }	//	�����蔻��擾
	D3DXVECTOR3 GetCollisionSiz() { return m_Xcollision.siz; }	//	�����蔻��擾
protected:
	virtual void Hit(int nDamage);
	virtual void Hit(int nCntInvincible, int nDamage);
	virtual void Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage);
protected :
	virtual void MoveAttenuation();	// �ړ�����
	class CActivity
	{
	public:
		CActivity() {}
		virtual CActivity* update() = 0;
	};
	virtual void ActivityUpdate();
	CActivity* m_pActivity;		// �U���s��

private:
	int m_nLife;	// �̗�
	int m_nCntInvincible;	// ���G����
	int m_nAttcak;	// �U����
	int m_nDefense;	// �h��
	int m_fSpeed;	// ���x

	X m_Xcollision;	// �����蔻��ʒu
	X m_xmove;		// �ω���(�^����,��]��,�c����)
	bool bJump;

};


#endif // !_CHARACTER_H_


