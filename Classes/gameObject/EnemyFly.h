#ifndef _ENEMY_FLY_H_
#define _ENEMY_FLY_H_
#include "cocos2d.h"
enum ENEMY_ACTION
{
	ENEMY_HURT	=	1, //֮���hit
	ENEMY_FLY,
	ENEMY_BLOWUP
};
class EnemyFly : public cocos2d::Sprite
{
public:
	EnemyFly(void);
	~EnemyFly(void);

	virtual bool init();
	CREATE_FUNC(EnemyFly);

public:
	//���ͣ����У���ը������
	void init(int type,int fly ,int blowup,int hit);  
	//�л��ƶ�
	void move();
	//�л���ը
	void explode();
	//�л�����
	void hurt(float dmg);
	//�л�����
	void destory();
	//�л����ӵ���ײ���
	bool hitTest(Node* hitNode);
	//��ȡ��ǰ��״̬
	float getIsDead() const;

private:
	//��������
	cocos2d::Animation* createAnimation(const std::string& head,const std::string& mid,int num);
	//���ź������Ͷ���
	void playActionWithType(int actionType ,bool loop = false, bool del = false);

private:
	/*�ƶ��ٶ�*/
	float vy;
	/*����*/
	float hp;
	/*�л�����*/
	int typeNum;
	/*��������*/
	int flyNum;
	/*��ը����*/
	int blowupNum;
	/*��������*/
	int hitNum;


};

#endif	//_ENEMY_FLY_H_
