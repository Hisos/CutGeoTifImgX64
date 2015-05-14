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
	//���캯������ԭʼͼ�񣬻��ͼ��Ĳ����������ߡ�ͼ��ľ�γ�ȷ�Χ
	//srcImgPath:ԭʼͼ���·��
	ImgInfo(std::string srcImgPath);
	//�Թ���ķ�ʽ��ԭʼͼ��
	//srcImgPath��ԭʼͼ���·��
	void openImg(std::string srcImgPath);
	virtual ~ImgInfo(void);
	int getSrcImgHeigh();
	int getSrcImgWidth();
	GDALDataset*& getDataset();

	//��ָ������ľ��Σ�����Ŀ��ͼ
	//outImgPath��Ŀ��ͼ���·����������jpgͼ��
	//widthPoint���з��������ϽǵĿ����꣨������Ϊ��λ��
	//heightPoint���з��������Ͻǵ������꣨������Ϊ��λ��
	//widthPixelLen���з���������귽���ϵĳ��ȣ�������Ϊ��λ��
	//heightPixelLen���з����������귽���ϵĳ��ȣ�������Ϊ��λ��
	int translate(std::string outImgPath, std::string widthPoint, std::string heightPoint, std::string widthPixelLen, std::string heightPixelLen);

	//��ָ������ľ��Σ�����Ŀ��ͼ
	//outImgPath��Ŀ��ͼ���·����������jpgͼ��
	//widthPoint���з��������ϽǵĿ����꣨������Ϊ��λ��
	//heightPoint���з��������Ͻǵ������꣨������Ϊ��λ��
	//widthPixelLen���з���������귽���ϵĳ��ȣ�������Ϊ��λ��
	//heightPixelLen���з����������귽���ϵĳ��ȣ�������Ϊ��λ��
	int translate(std::string outImgPath, int widthPoint, int heightPoint, int widthPixelLen, int heightPixelLen);
	double getImgMaxLongitude();
	double getImgMinLongitude();
	double getImgMaxLatitude();
	double getImgMinLatitude();
	//������Ƭ���½ǵľ��ȺͲ��������ļ��е�����
	int calcuTileDirName(double pixLongitude, int tileFloor);
	//������Ƭ���½ǵ�γ�ȺͲ��������ļ�������
	int calcuTileFileName(double pixLatitude, int tileFloor);
	//������Ƭ�ļ��е����ֺͲ���������Ƭ���½ǵľ���
	double calcuTilePixLongitude(int tileDirName, int tileFloor);
	//������Ƭ�ļ������ֺͲ���������Ƭ���½ǵ�γ��
	double calcuTilePixLatitude(int tileFileName, int tileFloor);	

	//���ݾ�γ����ͼ���϶�Ӧ�ĵ㣬���þ�γ�ȳ���ͼ��ķ�Χ
	//��ͼ��������þ�γ�ȵĵ�
	//longitude������
	//latitude��γ��
	//coord���洢������
	//ת���ɹ�����true��ʧ�ܷ���false
	bool Projection2ImageRowCol(double longitude, double latitude, Pixcoord &coord)  ;

	//����ͼ���ϵ�ľ�γ�ȣ�width��height����������Ͻǵ�ƫ������
	//width���������Ŀ�����
	//height���������ĸ�����
	//longitude���õ�ľ���
	//latitude���õ��γ��
	//����ɹ�����true������false
	bool ImageRowCol2Projection(int width, int height, double &longitude, double &latitude) ;
	
private:
	//����ԭʼͼ��ľ�γ�ȷ�Χ������浽����Ӧ��������
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