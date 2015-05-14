#pragma once
#include <string>
#include "Pixcoord.h"
#include "ImgInfo.h"
class TileInfo
{
public:
	TileInfo(void);
	virtual ~TileInfo(void);
	//
	TileInfo(ImgInfo *img, int tileFloor, int widthPixLen, int heightPixLen);
	std::string getTilePath();
	Pixcoord findPixcoord(int dirName, int fileName);
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
	//������Ƭ���Ͻ���ԭʼͼ���е����꣨������Ϊ��λ��
	Pixcoord calcuTileCoord(int dirName, int fileName);
	//�Զ��ֲ��ҵķ�ʽ��low��height���ҳ�һ��ֵ����ֵ���ڵ���small��С�ڵ���big
	//����-1����ʧ��
	int binarySearchPixHeightCoord(int low, int height, int small, int big);
	int binarySearchPixWidthCoord(int low, int height, int small, int big);
	ImgInfo *img_;
	//��Ƭ·��
	std::string filePath_;
	int tileFloor_;
	//��Ƭ���½���ԭͼ�ϵĵ�����
	int widthPixPoint_;
	int heightPixPoint_;
	//��Ƭ��ԭͼ�еĴ�С
	int cutWidthPixLen_;
	int cutHeightPixLen_;
};

