#include "TileInfo.h"
#include <algorithm>
#include <iostream>
#include <io.h>
#include "ImgInfo.h"
#include <algorithm>
TileInfo::TileInfo(void)
{}
TileInfo::~TileInfo(void)
{}
//���캯��
//img��ԭʼͼ���ָ��
//tileFloor����Ƭ����
TileInfo::TileInfo(ImgInfo *img, int tileFloor):
	img_(img), tileFloor_(tileFloor)
{}
//���ݸ�·������Ƭ�������ļ��С��ļ���������Ƭ·��
//rootPath����·��
//dir���ļ�������
//file:�ļ�����
bool TileInfo::createTileFilePath(std::string rootPath, int dir, int file)
{
	char tileFileDir[256];
	sprintf_s(tileFileDir, "%s\\%d\\%d", rootPath.c_str(), this->tileFloor_, dir);
	//Ŀ¼�����ڣ��򴴽�
	if(_access(tileFileDir, 0) == -1)
	{
		char createDirCmd[256];
		memset(createDirCmd, 0, sizeof(createDirCmd));
		sprintf_s(createDirCmd, "cmd /c md %s", tileFileDir);
		system(createDirCmd);
	}
	char filePath[256];
	sprintf_s(filePath, "%s\\%d.png", tileFileDir, file);
	this->filePath_ = filePath;
	return true;
}
//�����ļ��С��ļ������ּ�����Ƭ���½ǵ�����꣨��������Ͻǣ�������Ϊ��λ��
//������������겻��ԭʼͼ��Χ�ڣ�����ԭʼͼ���ھ���������������
//dirName���ļ�������
//fileName���ļ�����
//����ֵcoord������Ƭ���½ǵ�����
Pixcoord TileInfo::calcuTileCoord(int dirName, int fileName)
{
	Pixcoord coord;
	double pointLongitude, pointLatitude;
	pointLongitude = img_->calcuTilePixLongitude(dirName, this->tileFloor_);
	pointLatitude = img_->calcuTilePixLatitude(fileName, this->tileFloor_);

	img_->Projection2ImageRowCol(pointLongitude, pointLatitude, coord);

	/*coord.setWidth(MIN(coord.getWidth(), img_->getSrcImgWidth() ) );
	coord.setWidth(MAX(coord.getWidth(), 0) );
	coord.setHeight(MIN(coord.getHeight(), img_->getSrcImgHeigh() ) );
	coord.setHeight(MAX(coord.getHeight(), 0) );*/
	return coord;
}
//��ȡ���ļ���ԭʼͼ���϶�Ӧ�����򣬼����
//this->widthPixPoint_������������ϽǵĿ�����
//this->heightPixPoint_������������ϽǵĿ�����
//this->cutHeightPixLen_���������ĸ߶�
//this->cutWidthPixLen_���������Ŀ��
//dirName:�ļ�������
//fileName���ļ�����
//������귵��true��û�������false��pix�洢��������Ľ��
bool TileInfo::findPixcoord(int dirName, int fileName, Pixcoord &pix)
{
	Pixcoord tileCoord[2];
	Pixcoord rtn;
	tileCoord[0] = this->calcuTileCoord(dirName, fileName);
	tileCoord[1] = this->calcuTileCoord(dirName + 1, fileName + 1);

	if(tileCoord[0].getHeight() >= img_->getSrcImgHeigh() && tileCoord[1].getHeight() >= img_->getSrcImgHeigh()
		|| tileCoord[0].getHeight() <= 0 && tileCoord[1].getHeight() <= 0
		||tileCoord[0].getWidth() >= img_->getSrcImgWidth() && tileCoord[1].getWidth() >= img_->getSrcImgWidth()
		||tileCoord[0].getWidth() <= 0 && tileCoord[1].getWidth() <= 0)
	{
		return false;
	}
	//��ԭʼͼ��������ͼ�еĴ�СС������ͼ��С��1/3�������ɸ�ͼ
	if(img_->getSrcImgHeigh() < abs(tileCoord[0].getHeight() - tileCoord[1].getHeight() ) / 3 
		|| img_->getSrcImgWidth() < abs(tileCoord[0].getWidth() - tileCoord[1].getWidth() ) / 3 )
	{
		return false;
	}

	this->cutHeightPixLen_ = abs(tileCoord[0].getHeight() - tileCoord[1].getHeight() );
	this->cutWidthPixLen_ = abs(tileCoord[0].getWidth() - tileCoord[1].getWidth() );

	this->widthPixPoint_ = MIN(tileCoord[0].getWidth(), tileCoord[1].getWidth() );
	this->heightPixPoint_ = MAX(tileCoord[0].getHeight(), tileCoord[1].getHeight() );
	
	pix.setWidth(this->widthPixPoint_);
	pix.setHeight(this->heightPixPoint_);
	return true;
	//return Pixcoord(this->widthPixPoint_, this->heightPixPoint_);
}
//������Ƭ·��
std::string TileInfo::getTilePath()
{
	return this->filePath_;
}
