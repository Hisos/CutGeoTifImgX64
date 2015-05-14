#pragma once
#include "gdal.h"
#include "gdal_alg.h"
#include "ogr_srs_api.h"
#include "cpl_string.h"
#include "cpl_conv.h"
#include "cpl_multiproc.h"
#include "gdal_priv.h"
#include "cpl_vsi.h"
#include "ogr_spatialref.h"
#include "vrtdataset.h"
#include "commonutils.h"
#include <iostream>
#include <string>
#include "Pixcoord.h"
class ImgInfo
{
public:
	ImgInfo(void);
	ImgInfo(std::string srcImgPath);
	//��ֻ����ʽ��ԭʼͼ�񣬳ɹ���true��ʧ�ܣ�false
	void openImg(std::string srcImgPath);
//	bool getPixelLongLat(int widthPoint, int heightPoint);
	virtual ~ImgInfo(void);
	int getSrcImgHeigh();
	int getSrcImgWidth();
	GDALDataset*& getDataset();
//	double convertLongLat2double(const std::string& longORlat);
	//��ȡ����һ����ľ�γ��
	//hDataset��ͼ���GDALDatasetH����
	//widthPoint�����صĿ�����
	//heightPoint�����ص�������
	//longttude��������ľ��ȣ���ʽ��291d 4'34.58''E
	//latitude���������γ�ȸ�ʽ��22d17'28.73''S
//	void transCoord2longitudeLatitude(double widthPoint, double heightPoint,std::string &longitude, std::string &latitude);

	//��ͼ����ȡԭʼͼ����ָ������ľ��Σ�����Ŀ��ͼ
	//outImgPath��Ŀ��ͼ���·����������jpgͼ��
	//widthPoint���з��������Ͻǵĺ����꣨������Ϊ��λ��
	//heightPoint���з��������Ͻǵ������꣨������Ϊ��λ��
	//widthPixelLen���з�����������ϵĳ��ȣ�������Ϊ��λ��
	//heightPixelLen���з������������ϵĳ��ȣ�������Ϊ��λ��
	int translate(std::string outImgPath, std::string widthPoint, std::string heightPoint, std::string widthPixelLen, std::string heightPixelLen);
	double getImgMaxLongitude();
	double getImgMinLongitude();
	double getImgMaxLatitude();
	double getImgMinLatitude();
	//������Ƭ���Ͻǵľ��ȺͲ��������ļ��е�����
	int calcuTileDirName(double pixLongitude, int tileFloor);
	//������Ƭ���Ͻǵ�γ�ȺͲ��������ļ�������
	int calcuTileFileName(double pixLatitude, int tileFloor);
	//������Ƭ�ļ��е����ֺͲ���������Ƭ���Ͻǵľ���
	double calcuTilePixLongitude(int tileDirName, int tileFloor);
	//������Ƭ�ļ������ֺͲ���������Ƭ���Ͻǵ�γ��
	double calcuTilePixLatitude(int tileFileName, int tileFloor);

	

	//���ݾ�γ����ͼ���϶�Ӧ�ĵ�
	bool Projection2ImageRowCol(double longitude, double latitude, Pixcoord &coord)  ;
	//����ͼ���ϵ�ľ�γ��
	bool ImageRowCol2Projection(int width, int height, double &longitude, double &latitude) ;

	int translate(std::string outImgPath, int widthPoint, int heightPoint, int widthPixelLen, int heightPixelLen);
private:
	//����ԭʼͼ��ľ�γ�ȷ�Χ��������浽��������
	void calcuLongitudeLatitudeRange();

	void CopyBandInfo( GDALRasterBand * poSrcBand, GDALRasterBand * poDstBand,
                          int bCanCopyStatsMetadata, int bCopyScale, int bCopyNoData );

	void AttachMetadata( GDALDatasetH hDS, char **papszMetadataOptions );

	int ArgIsNumeric( const char *pszArg );

	int ProxyMain(int argc, char ** argv );

	int FixSrcDstWindow( int* panSrcWin, int* panDstWin,
                            int nSrcRasterXSize,
                            int nSrcRasterYSize );

	void SrcToDst( double dfX, double dfY,
                      int nSrcXOff, int nSrcYOff,
                      int nSrcXSize, int nSrcYSize,
                      int nDstXOff, int nDstYOff,
                      int nDstXSize, int nDstYSize,
                      double &dfXOut, double &dfYOut );

	void Usage(const char* pszErrorMsg, int bShort);

	//bool GDALInfoReportCorner(OGRCoordinateTransformationH hTransform,
 //                     double x, double y , std::string &longitude, std::string &latitude);
	//ԭʼͼ���Dataset
	GDALDataset *srcImgDataset_;
	//ԭʼͼ��Ŀ�
	int srcImgWidth_;
	//ԭʼͼ�εĸ�
	int srcImgHigh_;
	//ԭʼͼ��Ĳ�����
	int srcImgBandCnt_;
	//ԭʼͼ�ε�·��
	std::string srcImgPath_;
	//pointCoordinate 
	int bSubCall;
	//����ͼƬ��γ�ȵķ�Χ
	double imgMaxLongitude;
	double imgMinLongitude;
	double imgMaxLatitude;
	double imgMinLatitude;

};
//����һ�������
typedef struct pointCoordinate{
	double abscissa;
	double ordinate;		 
};

enum
{
    MASK_DISABLED,
    MASK_AUTO,
    MASK_USER
};

#define CHECK_HAS_ENOUGH_ADDITIONAL_ARGS(nExtraArg) \
    do { if (i + nExtraArg >= argc) \
        Usage(CPLSPrintf("%s option requires %d argument(s)", argv[i], nExtraArg)); } while(0)


typedef struct
{
    int     bScale;
    int     bHaveScaleSrc;
    double  dfScaleSrcMin, dfScaleSrcMax;
    double  dfScaleDstMin, dfScaleDstMax;
} ScaleParams;