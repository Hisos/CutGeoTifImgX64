#pragma once
#include <string>
#include "Pixcoord.h"
#include "ImgInfo.h"
class TileInfo
{
public:
	TileInfo(void);
	virtual ~TileInfo(void);
	//���캯��
	//img��ԭʼͼ���ָ��
	//tileFloor����Ƭ����
	TileInfo(ImgInfo *img, int tileFloor);
	//������Ƭ·��
	std::string getTilePath();
//��ȡ���ļ���ԭʼͼ���϶�Ӧ�����򣬼����
//this->widthPixPoint_������������ϽǵĿ�����
//this->heightPixPoint_������������ϽǵĿ�����
//this->cutHeightPixLen_���������ĸ߶�
//this->cutWidthPixLen_���������Ŀ��
//dirName:�ļ�������
//fileName���ļ�����
//������귵��true��û�������false��pix�洢��������Ľ��
bool TileInfo::findPixcoord(int dirName, int fileName, Pixcoord &pix);
	//���ݸ�·������Ƭ�������ļ��С��ļ���������Ƭ·��
	//rootPath����·��
	//dir���ļ�������
	//file:�ļ�����
	bool createTileFilePath(std::string rootPath, int dir, int file);

	int getWidthPixPoint()
	{
		return this->widthPixPoint_;
	}
	int getHeightPixPoint()
	{
		return this->heightPixPoint_;
	}
	int getCutWidthPixLen()
	{
		return this->cutWidthPixLen_;
	}
	int getCutHeightPixLen()
	{
		return this->cutHeightPixLen_;
	}
private:
	//�����ļ��С��ļ������ּ�����Ƭ���½ǵ�����꣨��������Ͻǣ�������Ϊ��λ��
	//������������겻��ԭʼͼ��Χ�ڣ�����ԭʼͼ���ھ���������������
	//dirName���ļ�������
	//fileName���ļ�����
	//����ֵcoord������Ƭ���½ǵ�����
	Pixcoord calcuTileCoord(int dirName, int fileName);
	//ԭʼͼ��
	ImgInfo *img_;
	//��Ƭ·��
	std::string filePath_;
	//��Ƭ����
	int tileFloor_;
	//��Ƭ���½���ԭͼ�ϵĿ�����
	int widthPixPoint_;
	//��Ƭ���½���ԭͼ�ϵĸ�����
	int heightPixPoint_;
	//��Ƭ��ԭͼ�п����귽���ϵĴ�С��������Ϊ��λ��
	int cutWidthPixLen_;
	//��Ƭ��ԭͼ�и����귽���ϵĴ�С��������Ϊ��λ��
	int cutHeightPixLen_;
};

