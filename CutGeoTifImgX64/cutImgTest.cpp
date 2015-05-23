#include <iostream>
#include "gdal_priv.h"
#include "cpl_conv.h" 
#include "DebugPrint.h"
#include "ImgInfo.h"
#include "TileInfo.h"
#include <io.h>
#include <algorithm>
#include <cmath>
#include <string>
#include "Pixcoord.h"
using namespace std;
/**
* ���ߣ�����
* ��д���ڣ�2015-05-22
* �޸��ߣ�
* �޸����ڣ�
*
* �����ܣ���GeoTiffͼ����ͼ������TMS�㷨��Ŀǰ���㷨Ϊ����
* �ĳɶ��̳߳���ǳ��򵥣�ֻ��Ҫ��main�����е�����for�������о�OK
* ������򵥵ķ����ǲ���openMP�������Ӹ㶨��
*
* ����˼�룺�������������ͼ��ľ�γ�ȷ�Χ�����ݸþ�γ�ȷ�Χ�����ļ��С�Ĵָͼ�ļ��ķ�Χ
* �����ļ��С��ļ������֣����Ƴ�ԭʼͼ�����Ŀ������Ӧ��Ĵָͼ�����ֱ���ҵ������򣬽����������¼���
*
* ͨ���ļ��С��ļ��������ƴ���ͼ������ķ��������Ȼ�õ�ǰ�ļ����½ǵľ�γ�ȣ�Ȼ��������Ͻǵľ�γ�� 
* ͨ�������Ծ�γ�ȵ�ֵ���ҵ��ڴ���ͼ���е����꣬�ҵ�����֮��
*
**/
int main(int argc, char* argv[])
{
	GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO"); 
	ImgInfo img("D:\\GDALTEST\\test.tif");

	for(int floor = 1; floor <=17; ++ floor)
	{
		int tileFloor = floor;
		string rootPath("D:\\GDALTEST");

		int dirNameMin = img.calcuTileDirName(img.getImgMinLongitude(), tileFloor);
		int dirNameMax = img.calcuTileDirName(img.getImgMaxLongitude(), tileFloor);
		int fileNameMin = img.calcuTileFileName(img.getImgMinLatitude(), tileFloor);
		int fileNameMax = img.calcuTileFileName(img.getImgMaxLatitude(), tileFloor);

		if(dirNameMin > dirNameMax)
		{
			swap(dirNameMin, dirNameMax);
		}
		if(fileNameMin > fileNameMax)
		{
			swap(fileNameMin, fileNameMax);
		}

		/*int stepWidthLen = (img.getSrcImgWidth() % static_cast<int>( pow(2, tileFloor)) == 0) ?
			(img.getSrcImgWidth() / static_cast<int>( pow(2, tileFloor))) :
			(img.getSrcImgWidth() / static_cast<int>( pow(2, tileFloor)) + 1);
		int stepHeightLen = (img.getSrcImgHeigh() % static_cast<int>( pow(2, tileFloor)) == 0) ? 
			(img.getSrcImgHeigh() / static_cast<int>( pow(2, tileFloor))) : 
			(img.getSrcImgHeigh() / static_cast<int>( pow(2, tileFloor)) + 1);*/

		for(int dirName = dirNameMin; dirName <= dirNameMax; ++ dirName )
		{
			for(int fileName = fileNameMin; fileName <= fileNameMax; ++ fileName)
			{
				TileInfo tile(&img, tileFloor);
				Pixcoord pix;
				if(!tile.findPixcoord(dirName, fileName, pix) )
				{
					continue;
				}

				if(tile.getCutWidthPixLen() <= 0 || tile.getCutHeightPixLen() <= 0 || tile.getHeightPixPoint() <= 0)
				{
					continue;
				}
				tile.createTileFilePath(rootPath, dirName, fileName);
				img.translate(tile.getTilePath(), tile.getWidthPixPoint(), tile.getHeightPixPoint() - tile.getCutHeightPixLen(), 
					tile.getCutWidthPixLen(), tile.getCutHeightPixLen() );
			}
		}
	}
	return 0;
}
