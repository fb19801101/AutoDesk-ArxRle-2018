// ArxRleEntityClass.h: interface for the ArxRleEntity class.
//

#ifndef ARXRLE_ENTITY_H
#define ARXRLE_ENTITY_H

#include "ArxRleString.h"
#include <complex>
#include <vector>
using namespace std;


//���ֶ��뷽ʽ
enum ArxAlignment
{
	ArxAlignNone      = 0,
	ArxLeftTop        = 1,
	ArxMiddleTop      = 2,
	ArxRightTop       = 3,
	ArxLeftMiddle     = 4,
	ArxCenter         = 5,
	ArxRightMiddle    = 6,
	ArxLeftBottom     = 7,
	ArxMiddleBottom   = 8,
	ArxRightBottom    = 9
};

//�����뷽ʽ
enum ArxMargin
{
	ArxMarginTop         = 0x01,
	ArxMarginLeft        = 0x02,
	ArxMarginBottom      = 0x04,
	ArxMarginRight       = 0x08,
	ArxMarginHorzSpacing = 0x10,
	ArxMarginVertSpacing = 0x20
};

// ��ɫ����
enum ArxColorType
{
	ArxByBlock = -2,		//�ɿ�
	ArxByLayer = -1,		//��ͼ��
	ArxByNone = 0,     	//��
	ArxByValue = 1,  	//RGB
	ArxByACI = 2	    	//����
};

// �ļ�����
enum ArxFileType
{
	ArxDwg = 1,		//DWG
	ArxDxf = 2,		//DXF
	ArxNull = 0,      //��
};

// ��ע����
enum ArxDimtad
{
	ArxTadCenter = 0,
	ArxTadAbove,
	ArxTadSide,
	ArxTadJis
};

// ��������
enum ArxSpaceType
{
	ArxModel = 0,
	ArxActive = 1,
	ArxPaper = 2,
	ArxOther = 3,
};

#ifndef PI
#define PI 3.141592653589793238462643383279502884197169399375105820974944592308   //Բ���� PI
#endif

#ifndef INVALIDCOOR
#define INVALIDCOOR -987654321.0f
#endif

#ifndef ARXRLEDB
#define ARXRLEDB  ArxRleDataBase()
#endif

#ifndef ARXRLEDS
#define ARXRLEDS  ArxRleDrawSpace()
#endif

#ifndef ARXRLEPSV
#define ARXRLEPSV  ArxRlePlotSettingsValidator()
#endif

#ifndef ARXRLEDLM
#define ARXRLEDLM  ArxRleDataLinkManager()
#endif

#ifndef ARXRLEDCT
#define ARXRLEDCT  ArxRleApDocument()
#endif

class CPt3d
{
public:
	double x,y,z;

public:
	CPt3d();
	CPt3d(const double xx, const double yy, const double zz = 0);
	CPt3d(const double* xyz);
	CPt3d(const complex<double> xy);
	CPt3d(const CPt3d& pt);
	CPt3d(const AcGePoint2d& pt);
	CPt3d(const AcGePoint3d& pt);
	CPt3d(const AcGeVector3d& pt);
	CPt3d(const bool bValid);

	bool operator == (const CPt3d& pt) const;
	bool operator != (const CPt3d& pt) const;
	bool operator > (const CPt3d& pt) const;
	bool operator < (const CPt3d& pt) const;

	CPt3d operator = (const double* xyz);
	CPt3d operator = (const complex<double> xy);
	CPt3d operator = (const CPt3d& pt);
	CPt3d operator = (const ads_point& pt);
	CPt3d operator = (const AcGePoint2d& pt);
	CPt3d operator = (const AcGePoint3d& pt);
	CPt3d operator = (const AcGeVector3d& pt);
	CPt3d operator + (const double* xyz);
	CPt3d operator + (const complex<double> xy);
	CPt3d operator + (const CPt3d& pt);
	CPt3d operator + (const AcGePoint2d& pt);
	CPt3d operator + (const AcGePoint3d& pt);
	CPt3d operator + (const AcGeVector3d& pt);
	CPt3d operator - (const double* xyz);
	CPt3d operator - (const complex<double> xy);
	CPt3d operator - (const CPt3d& pt);
	CPt3d operator - (const AcGePoint2d& pt);
	CPt3d operator - (const AcGePoint3d& pt);
	CPt3d operator - (const AcGeVector3d& pt);
	CPt3d operator += (const double* xyz);
	CPt3d operator += (const complex<double> xy);
	CPt3d operator += (const CPt3d& pt);
	CPt3d operator += (const AcGePoint2d& pt);
	CPt3d operator += (const AcGePoint3d& pt);
	CPt3d operator += (const AcGeVector3d& pt);
	CPt3d operator -= (const double* xyz);
	CPt3d operator -= (const complex<double> xy);
	CPt3d operator -= (const CPt3d& pt);
	CPt3d operator -= (const AcGePoint2d& pt);
	CPt3d operator -= (const AcGePoint3d& pt);
	CPt3d operator -= (const AcGeVector3d& pt);
	CPt3d operator * (const CPt3d& scale);
	CPt3d operator / (const CPt3d& scale);
	CPt3d operator *= (const CPt3d& scale);
	CPt3d operator /= (const CPt3d& scale);
	CPt3d operator * (const double fScale);
	CPt3d operator / (const double fScale);
	CPt3d operator *= (const double fScale);
	CPt3d operator /= (const double fScale);
	CPt3d operator * (const double* fScale);
	CPt3d operator / (const double* fScale);
	CPt3d operator *= (const double* fScale);
	CPt3d operator /= (const double* fScale);

	double operator [] (int index) const;

	operator double*() const;
	operator complex<double>() const;
	operator AcGePoint2d() const;
	operator AcGePoint3d() const;
	operator AcGeVector3d() const;

	double* fPtr() const;
	complex<double> complexDbl() const;
	AcGePoint2d aPt2() const;
	AcGePoint3d aPt() const;
	AcGeVector3d vPt() const;
	CString sPt(int index = 3, int prec = 3) const;
	const char* cPt(int index = 3, int prec = 3);

	double GetX() const;
	double GetY() const;
	double GetZ() const;
	double* Get() const;
	void SetX(const double xx);
	void SetY(const double yy);
	void SetZ(const double zz);
	void Set(const double xx, const double yy, const double zz);

	bool IsValid();
	double GetDistance(const CPt3d& ptEnd);
	static double GetDistance(const CPt3d& ptStart, const CPt3d& ptEnd);
	double GetAngle(const CPt3d& ptEnd);
	static double GetAngle(const CPt3d& ptStart, const CPt3d& ptEnd);
	double GetVectorAzimuth(const CPt3d& ptEnd); //����ֵ-�е���
	static double GetVectorAzimuth(const CPt3d& ptStart, const CPt3d& ptEnd);
	CPt3d GetLineEnd(const double fLength, const double fRotation); //���fLengthС���㣬�൱�ڷ���
	static CPt3d GetLineEnd(const CPt3d& ptStart, double fLength, double fRotation);
};
typedef vector<CPt3d> CPt3dArray;

// ͼ��
class CLayer
{
public:
	CLayer();
	CLayer(AcDbObjectId& objectId);
	CLayer(const CLayer& oLayer);
	~CLayer();
	AcDbLayerTableRecord* GetRecord() {return m_pLayer;}

	void SetName(ArxRleString lpszName);			//����ͼ����
	void SetColor(COLORREF clr);	//������ɫ
	void SetDescription(ArxRleString lpszDescription);	//��������
	void SetLineWidth(double fWidth);	//�����߿�
	void SetOff(bool bIsOff = false);			//����On/Off
	void SetLocked(bool bIsLocked = false);		//��������
	void SetFrozen(bool bIsFrozen = false);		//���ö���
	void SetHidden(bool bIsHidden = false);		//��������
	void SetPrintable(bool bIsPrint = false);	//���ô�ӡ
	void SetLineType(AcDbObjectId& objectId);   	//��������

	bool isValid();
	CLayer& operator = (AcDbObjectId& objectId);
	CLayer& operator = (CLayer& layer);
	bool operator == (CLayer& layer);
	bool operator != (CLayer& layer);

	char* GetName();							//�õ�ͼ����
	COLORREF GetColor();
	AcDbObjectId GetObjectId();

protected:
	AcDbLayerTableRecord* m_pLayer;
};
typedef AcArray<CLayer> CLayerArray;

class CEntity;
class CLayout;
class CViewport;

// ������ʽ
class CTextStyle
{
public:
	CTextStyle(); //ȱʡ���캯�����ն���
	CTextStyle(AcDbObjectId& objectId);//���ڶ�����������
	CTextStyle(CTextStyle& oTextStyle); //���ƹ��캯��
	virtual ~CTextStyle();
	bool isValid();

	void SetName(ArxRleString lpszName); //������ʽ����
	void SetFont(ArxRleString lpszFontName, bool bold = false, bool italic = false); //����windows����
	void SetFont(ArxRleString lpszFontName, ArxRleString lpszBigFontName, bool vertical = false); //����cad����
	void SetHeight(double fHeight); //���������
	void SetWidthFactor(double fXScale); //��������߿��
	void SetOblique(double fOblique); //����������б�Ƕ�
	void SetUpsideDown(bool bUpsideDown); //��������ߵ�
	void SetBackward(bool bBackward); //�������巴��
	char* GetName(); //�õ���ʽ����
	double GetHeight(); //�õ������
	double GetWidthFactor(); //�õ�����߿��
	double GetOblique(); //�õ�������б�Ƕ�
	bool GetUpsideDown(); //�õ�����ߵ�
	bool GetBackward();//�õ����巴��
	void GetFont(char* lpszFontFace, bool& bBold, bool& bItalic);
	void GetFont(char* lpszFontName, char* lpszBigFontName, bool& bVertical);
	int GetFontType() const;

	AcDbObjectId GetObjectId();

protected:
	AcDbTextStyleTableRecord* m_pTextStyleRecord;
};

// �����ʽ
class CTableStyle
{
public:
	CTableStyle(); //ȱʡ���캯�����ն���
	CTableStyle(AcDbObjectId& objectId);//���ڶ�����������
	CTableStyle(CTableStyle& oTableStyle); //���ƹ��캯��
	virtual ~CTableStyle();
	bool isValid();

	void SetName(ArxRleString lpszName); //������ʽ����
	void SetTextStyle(CTextStyle* pTextStyle); //�����ı���ʽ
	void SetTextHeight(double fHeight); //���������
	void CreateCellStyle(ArxRleString lpszName); //������Ԫ��ʽ
	void SetRotation(double fRotation, ArxRleString lpszCellStyle = ""); //������ת�Ƕ�
	void SetFlowDirection(bool bFlow); //���ñ����
	void SetTextStyle(CTableStyle* pTextStyle);
	char* GetName(); //�õ���ʽ����
	CTextStyle GetTextStyle(); //�õ��ı���ʽ
	double GetTextHeight(); //�õ������
	double GetRotation(ArxRleString lpszCellStyle); //�õ���ת�Ƕ�
	void SetMargin(ArxMargin eMargin, double fMargin, ArxRleString lpszCellStyle = ""); //���ñ߾� 
	bool GetFlowDirection(); //�õ������
	
	AcDbObjectId GetObjectId();

protected:
	AcDbTableStyle* m_pTableStyle;
};

// ���¼
class CBlockRecord
{
public:
	CBlockRecord(); //ȱʡ���캯�����ն���
	CBlockRecord(AcDbObjectId& objectId);//���ڶ�����������
	CBlockRecord(CBlockRecord& oBlockRcd); //���ƹ��캯��
	CBlockRecord(ArxRleString lpszName);
	virtual ~CBlockRecord();

	bool LoadFile(ArxRleString lpszPathName);	//��dwg�ļ��м��ؿ�
	bool AppendEntity(CEntity* pEntity);		//���ͼԪ
	bool isValid();

	CBlockRecord& operator = (CBlockRecord& record);
	CBlockRecord& operator = (AcDbObjectId& objectId);

	void SetName(ArxRleString lpszName);
	void SetOrigin(CPt3d pt);                   //���û���
	void SetComments(ArxRleString lpszComment);	//����˵��
	void SetLayout(CLayout* pLayout);			//���ò���
	void SetBlockScaling(bool bAny); //false-kAny:Block references can be non-uniformly scaled.
	void SetExplodable(bool bExplodable);		//�����Ƿ����ը��
	bool Explodable(); //�Ƿ����ը��
	
	AcDbObjectId GetObjectId();
	char* GetName();

protected:
	AcDbBlockTableRecord* m_pBlockRecord;
};

// ��ע
class CDimensionStyle
{
public:
	CDimensionStyle();
	CDimensionStyle(AcDbObjectId& objectId);
	CDimensionStyle(CDimensionStyle& oDimStyle);
	~CDimensionStyle();

	bool isValid();
	void SetName(ArxRleString lpszName);
	char* GetName();

	void SetArrow(ArxRleString lpszName);        //ͬʱ���ü�ͷ��ʽ
	void SetArrow(ArxRleString lpszName1, ArxRleString lpszName2);		//��ͷ1��ʽ, ��ͷ2��ʽ
	void SetDimasz(double fSize);		//���ü�ͷ��С
	void SetDimzin(byte nBits);		//ʮ����С����ʾʱ�����ƺ�����

	CDimensionStyle& operator = (AcDbObjectId& objectId);
	CDimensionStyle& operator = (CDimensionStyle& style);
	bool operator == (CDimensionStyle& dim);
	bool operator != (CDimensionStyle& dim);

	AcDbObjectId GetObjectId();

protected:
	AcDbDimStyleTableRecord* m_pDimensionStyle;
};

//�û�����ϵ
class CUcsRecord
{
public:
	CUcsRecord();
	CUcsRecord(AcDbObjectId& objectId);
	CUcsRecord(CUcsRecord& oUcsRcd);
	~CUcsRecord();

	bool isValid();
	void SetName(ArxRleString lpszName);
	char* GetName();
	void SetOrigin(CPt3d ptPosition);
	void SetAxis(CPt3d xAxis, CPt3d yAxis);
	void SetUcsBaseOrigin(CPt3d ptOrigin);
	CPt3d GetUcsBaseOrigin();
	CPt3d GetOrigin();

	AcDbObjectId GetObjectId();

protected:
	AcDbUCSTableRecord* m_pUcsRecord;
};

// CEntity  ͼԪ����
class CEntity
{
public:
	CEntity();
	CEntity(AcDbObjectId& objectId);
	CEntity(const CEntity& oEntity);
	virtual ~CEntity();

	bool isNull() const;
	AcDbEntity* getent() const;
	void setent(AcDbObject* pEnt);
	void addToSpace();
	void addToSpaceAndClose();

	COLORREF         getColor() const;
	void             setColor(COLORREF clr);
	int              getColorIndex() const;
	void             setColorIndex(int aci);
	ArxRleString     getLayer() const;
	void             setLayer(ArxRleString name);
	AcDbObjectId     getLayerId() const;
	void             setLayerId(AcDbObjectId id);
	ArxRleString     getLineType() const;
	void             setLineType(ArxRleString lt);
	AcDbObjectId     getLineTypeId() const;
	void             setLineTypeId(AcDbObjectId id);
	double           getLineTypeScale() const;
	void             setLineTypeScale(double lts);
	AcDb::LineWeight getLineWeight() const;
	void             setLineWeight(AcDb::LineWeight lw);

protected:
	AcDbEntity* m_pEntity;
};

// ��
class CPointEnt : public CEntity
{
public:
	CPointEnt();
	CPointEnt(AcDbObjectId& objectId);
	CPointEnt(CPointEnt& oPoint);
	~CPointEnt();

public:
	void SetPoint(CPt3d pt);
	void SetPoint(AcGePoint3d pt);
	void SetPoint(AcGePoint2d pt);
	void SetPoint(double fX, double fY, double fZ = 0);
	void SetX(double fX);
	void SetY(double fX);
	void SetZ(double fX);
	CPt3d GetPoint() {return CPt3d(x,y,z);}
	void GetPoint(AcGePoint3d& pt) {pt = AcGePoint3d(x,y,z);}
	void GetPoint(AcGePoint2d& pt) {pt = AcGePoint2d(x,y);}
	double GetX() {return x;}
	double GetY() {return y;}
	double GetZ() {return z;}

protected:
	double x,y,z;
};

// ֱ��
class CLine : public CEntity
{
public:
	CLine();
	CLine(AcDbObjectId& objectId);
	CLine(CLine& oLine);
	~CLine();

public:
	void SetPoint(CPt3d ptStart, CPt3d ptEnd);	//�������յ�
	void Set(CPt3d ptStart, double fLength, double fRotation); //������㣬���ȣ���ת�Ƕ�(�����x�ᣬ��ʱ��Ϊ��)
	void GetPoint(CPt3d& ptStart, CPt3d& ptEnd);	//������յ�
};

// CPolyline  �����ͼԪ
class CPolyline : public CEntity
{
public:
	CPolyline();
	CPolyline(AcDbObjectId& objectId);
	CPolyline(CPolyline& oPolyLine);
	virtual ~CPolyline();

public:
	void AddPoint(CPt3dArray arrPoint);	//���ֱ�ߵ�
	void AddPoint(AcGePoint3dArray arrPoint);	//���ֱ�ߵ�
	long AddPoint(CPt3d ptPosition);		//���ֱ�ߵ�
	long AddLine(CPt3d ptStart, double fLength, double fRotation);
	long AddArc(CPt3d ptStart, double fCentralAngle); //���Բ��:������ꡢԲ�ĽǶ�
	void InsertPoint(long nIndex, CPt3d ptPosition);
	void SetIsClosed(bool bIsClosed);	//�����Ƿ�պ�
	bool IsClosed() const;	//�Ƿ�պ�
	void SetLineWidth(double fWidth);	//����ȫ���߿��
	void SetWidthAt(long nIndex, double fStartWidth, double fEndWidth);
	int GetPointNum() const;	//�õ�����
	CPt3dArray GetPoint();	//�õ�����
	double GetLineWidth() const;//���ȫ���߿��
	bool HasArc();	//�Ƿ���Բ����
	void SetPointAt(long nIndex, CPt3d ptNew);
	void ClearPoint();
	void RemovePointAt(long nIndex);
	double GetArea();
	CPt3d GetStartPoint();
	CPt3d GetEndPoint();
	double GetDistAtPoint(CPt3d ptOnCurve);
	CPt3d GetPointAtDist(double fDistance);
	double GetLength();
	void SetElevation(double fElevation);
	double GetElevation();
	void AddRectangular(CPt3d& oBeginPt, CPt3d& oEndPt);
};

// Բ
class CCircle : public CEntity
{
public:
	CCircle();
	CCircle(AcDbObjectId& objectId);
	CCircle(CCircle& oCircle);
	~CCircle();

public:
	void Set(CPt3d ptCenter, double fRadius);	//Բ�� �뾶
	void SetPoint(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd); //���������Բ
	bool SetPointRadius(CPt3d ptStart, CPt3d ptEnd, double fRadius); // ���յ㡢�뾶������
	bool GetIsClosed();
	CPt3d GetCenter();
	double GetRadius();
	double GetArea();

	bool SelEntity(ArxRleString strPrompt);
};

// Բ��
class CArc : public CEntity
{
public:
	CArc();
	CArc(AcDbObjectId& objectId);
	CArc(CArc& oArc);
	~CArc();

public:
	bool Set(CPt3d ptCenter, double fRadius, double fStartAngle,  double fEndAngle);	//Բ�� �뾶	Բ�����յ�Ƕ�
	bool Set(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd); //���������Բ
	bool Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, double fStartTangle); // ���յ㡢�뾶��������Բ�����ҵ����Ϊ����������Ϊ������������߽�
	bool Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, bool bMinorArc = true); // ���յ㡢�뾶��������Բ�����ҵ����Ϊ����������Ϊ�������Ż������ӻ�
	bool GetIsClosed();
	CPt3d GetCenter();
	double GetRadius();
	double GetStartAngle();
	double GetEndAngle();
	double GetArea();
};

// ��Բ��
class CEllipse : public CEntity
{
public:
	CEllipse();
	CEllipse(AcDbObjectId& objectId);
	CEllipse(CEllipse& oEllipse);
	~CEllipse();

public:
	void Set(CPt3d ptCenter, CPt3d vtMajorAxis, double fRadiusRatio, double fStartAngle = 0.0, double fEndAngle = 2 * PI);
	void SetEx(CPt3d ptMajorStart, CPt3d ptMajorEnd, double fMinorRadius, double fStartAngle = 0.0, double fEndAngle = 2 * PI); 	//������Բ����: ����������꣬�����յ����꣬�������뾶����ʼ�Ƕȣ���ֹ�Ƕ�
	bool GetIsClosed();
	CPt3d GetCenter();
	CPt3d GetMajorAxis();
	double GetStartAngle();
	double GetEndAngle();
	double GetArea();
};

// �ı�
class CText : public CEntity
{
public:
	CText();
	CText(AcDbObjectId& objectId);
	CText(CText& oText);
	~CText();

public:
	void SetPosition(CPt3d ptPosition);			//λ��
	void SetText(ArxRleString lpszText);				//�ı�
	void SetRotation(double fRotation);				//��ת�Ƕȣ���ʱ��Ϊ����
	void SetOblique(double fOblique);				//��б�Ƕȣ�������б���֣�
	void SetTextHeight(double fHeight);					//�ָ�
	void SetAlignmentMode(ArxAlignment eAlign);		//���뷽ʽ
	// 	void SetAlignmentPoint(CPt3d ptPosition);	//���ö����
	void SetTextStyle(AcDbTextStyleTableRecord* pTextStyle);     //�����ı���ʽ
	void SetTextStyle(AcDbObjectId& oTextStyleId);     //�����ı���ʽ
	void SetTextStyle(CTextStyle& ts);
	void SetWidthFactor(double fFactor);			//�������

	CPt3d GetPosition();
	char* GetText();
	double GetHeight();
	double GetRotation();
	double GetOblique();
	double GetWidthFactor();
	double GetActualWidth();                              //�õ��ı���ȣ������Ѿ���ӵ����ݿ���
	void GetBoundPoint(CPt3d& ptTopLeft, CPt3d& ptTopRight, CPt3d& ptBottomRight, CPt3d& ptBottomLeft);
	void GetGeomExtents(CPt3d& ptMin, CPt3d& ptMax);
};

// ���ı�
class CMText :  public CEntity
{
public:
	CMText();
	CMText(AcDbObjectId& objectId);
	CMText(CMText& oMText);
	~CMText();

public:
	void SetPosition(CPt3d ptPosition);			//λ��
	void SetText(ArxRleString lpszText);				//�ı�
	void SetRotation(double fRotation);				//��ת�Ƕ�
	void SetHeight(double fHeight);					//ͼԪ�ߣ�ȱʡ=(����-1)*5/3*�ָ�*�о����+�ָ�
	void SetWidth(double fWidth);                   //��ȣ������������Զ�����
	void SetTextHeight(double fHeight);				//�ָ�
	void SetAlignmentMode(ArxAlignment eAlign);		//���뷽ʽ
	void SetTextStyle(AcDbTextStyleTableRecord* pTextStyle);     //�����ı���ʽ
	void SetTextStyle(AcDbObjectId& oTextStyleId);     //�����ı���ʽ
	void SetTextStyle(CTextStyle& ts);     //�����ı���ʽ
	void SetLineSpaceFactor(double fFactor);        //�����о����
	void SetLineSpaceStyle(short nStyle);         //�����о���ʽ
	void SetBackgroundFill(bool bFill, double fScaleFactor, bool bUseBackground, COLORREF clr); //���ñ�������
	void SetTextWidthFactor(double fWidthFactor);

	CPt3d GetPosition();
	char* GetText();
	double GetHeight();
	double GetWidth();
	double GetTextHeight();
	double GetRotation();
	double GetActualWidth();

protected:
	double m_fWidthFactor;
};

// �顣
class CBlock : public CEntity
{
public:
	CBlock();
	CBlock(AcDbObjectId& objectId);
	CBlock(CBlock& oBlock);
	~CBlock();

public:
	void SetPosition(CPt3d ptPosition);		//λ��
	void SetRotation(double fRotation);			//��ת
	void SetBlockRecord(AcDbBlockTableRecord *pRecord);//�������ݿ��еĿ��¼
	void SetScaleFactors(CPt3d ptScale);	//���ñ���
	void GetEntityArray(AcDbObjectIdArray& arrObjectId); //�õ����е�ͼԪ
	void Explode(AcDbObjectIdArray& arrObjectId, AcDbBlockTableRecord* pBlockRecord); //ը���飬��ͼԪ��ӵ�ָ�����¼��
	void SetAttribute(ArxRleString lpszName, ArxRleString lpszText);
	char* GetAttribute(ArxRleString lpszName);
	void AppendAttribute(ArxRleString lpszName, AcDbText* pText);
	void SetAttributeAlign(ArxRleString lpszName, ArxAlignment eAlign);
	void SetAttributeFontHeight(ArxRleString lpszName, double fFontHeight);
	bool SetBlockAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef);

	CPt3d GetPosition();
	double GetRotation();
	CPt3d GetScaleFactors();
};

// �ӿ�
class CViewport : public CEntity
{
public:
	CViewport();
	CViewport(AcDbObjectId& objectId);
	CViewport(const CViewport& oViewport);
	~CViewport();

	void SetRect(CPt3d pt1, CPt3d pt2);
	void SetWidth(double fWidth);
	void SetHeight(double fHeight);
	void SetOn(bool bOn); //true-on false-off
	void SetLocked(bool bLock); //true-lock false-unlock
	void SetUcs(CPt3d origin, CPt3d xAxis, CPt3d yAxis);
	void SetNonRectClipEntity(CPolyline* pLine);
	void SetNonRectClipOff();
	void SetScale(double fScale);
	void SetLensLength(double fLensLength);
	void SetViewCenter(CPt3d ptCenter);
	void SetViewDirection(CPt3d viewDirection);
	void SetTwistAngle(double fAngle);
	void SetViewTarget(CPt3d ptCenter);
	void SetViewHeight(double fHeight);
	void FreezeLayersInViewport(CLayerArray& arrLayer);

	void GetPoint(CPt3d& pt1, CPt3d& pt2);
	double GetWidth();
	double GetHeight();
	bool IsOn();
	bool IsLocked();
	void GetUcs(CPt3d& origin, CPt3d& xAxis, CPt3d& yAxis);
	double GetScale();
	CPt3d GetViewCenter();
	CPt3d GetViewDirection();
	CPt3d GetViewTarget();
	double GetTwistAngle();
	double GetViewHeight();

protected:
	CPt3d m_pt1, m_pt2;
};
typedef AcArray<CViewport> CViewportArray;

// ��ע
class CDimension : public CEntity
{
public:
	CDimension();
	CDimension(AcDbObjectId& objectId);
	CDimension(CDimension& oDimension);
	virtual ~CDimension();

	void SetDimBlockRecord(CBlockRecord* pRecord); //�������ע�����Ŀ�

	void SetDimensionStyle(CDimensionStyle *pDimStyle);
	void SetText(ArxRleString lpszText);
	void SetTextPosition(CPt3d ptPosition);
	void SetTextRotation(double fRotation);
	void SetArrowFlipped(bool bFirst, bool bSecond);
	void SetDynamicDimension(bool bDynamic);

	void SetArrow(ArxRleString lpszName);		//��ͷ��ʽ
	void SetExtLineFixLenEnable(bool bEnable);	//�̶��ߴ����
	void SetExtLineFixLen(double fLength);		//�ߴ���ߵĹ̶�����
	void SetDimExt1Linetype(AcDbObjectId& objectId);	//�ߴ����1������
	void SetDimExt2Linetype(AcDbObjectId& objectId);	//�ߴ����2������
	void SetArrowSize(double fSize);		//���ü�ͷ��С
	void SetDimzin(byte nBits);		//ʮ����С����ʾʱ�����ƺ�����
	void SetDimexe(double fDis);	//���óߴ���߳����ߴ��߾���
	void SetDimexo(double fOffset);	//���óߴ���ߵ����ƫ����
	void SetTextHeight(double fHeight);	//�������ָ߶�
	void SetTextHorz(ArxDimtad eTad);	//��������λ�ã�ˮƽĬ��Ϊ���У���������
	void SetTextOffset(double fGap);	//��������λ��-�ӳߴ��ߵ�ƫ����
	void SetDimtih(bool bTih);	//���ñ�ע���ַ����سߴ�����ڲ࣬false�ͳߴ���߶��룬true����
	void SetDimtoh(bool bToh);	//���ñ�ע���ַ����سߴ������࣬false�ͳߴ���߶��룬true����
	void SetDimtix(bool bTix);	//���ñ�ע����ʼ�ջ����ڳߴ����֮��
	void SetDimtofl(bool bTofl);	//��ʹ��ͷ�����ڲ�����֮�⣬�ߴ���Ҳ�������ڲ�����֮�䡣false���ܣ�true��
	void SetLineColor(COLORREF clr);	//�ߴ�����ɫ
	void SetExtLineColor(COLORREF clr);	//�ߴ������ɫ
	void SetTextColor(COLORREF clr);	//������ɫ
	void SetDimLineType(AcDbObjectId oLineType);  //�ߴ�����ʽ

	//�����ע
	void SetAlignedDimPoint(CPt3d pt1, CPt3d pt2, double fDis);//���������ע�������������Ǳ�ע���������߾��룬������
	void SetAlignedDimPoint(CPt3d pt);
	void SetAlignedDimOblique(double fOblique);				//��б�Ƕȣ�������б���֣�

	//�Ƕȱ�ע
	void SetPoint(CPt3d ptStart1, CPt3d ptStart2, CPt3d ptCenter); //ֱ��1����㣬ֱ��2����㣬����
	void SetArc(CPt3d ptArc); //Բ�ϵ�

	//������ע
	void SetArcDimPoint(CPt3d ptArc); //Բ�ϵ�
	void SetArcDimCenterPoint(CPt3d ptCenter); //Բ��
	void SetArcDimLeaderPoint(CPt3d pt1, CPt3d pt2); //���߶˵�

	//�����ע
	void SetGridDimDefiningPoint(CPt3d ptDefine);//ָ����
	void SetGridDimLeaderEndPoint(CPt3d ptEnd); //���߶˵�


	//�뾶��ע
	void SetRadiusDimCenter(CPt3d ptCenter);//ָ��Բ
	void SetRadiusDimChordPoint(CPt3d ptChord, double fLeaderLength); //�ҵ㣬���߳���
};

// ͼ�����
class CHatch : public CEntity
{
public:
	CHatch();
	CHatch(AcDbObjectId& objectId);
	CHatch(CHatch& oHatch);
	~CHatch();

	enum ArxHatchObjectType{zHatch = 0, zGradient};
	void SetHatchObjectType(ArxHatchObjectType type);
	void SetGradiant(ArxRleString lpszName, bool bUser = false); //���ý���ͼ��
	void SetOriginPoint(CPt3d pt);
	enum ArxHatchStyle{zNormal = 0, zOuter, zIgnore};
	void SetHatchStyle(ArxHatchStyle style); //�µ������ʽ
	enum ArxHatchPatternType{zUserDefined = 0, zPreDefined, zCustomDefined};
	bool SetPattern(ArxRleString lpszName, ArxHatchPatternType eType); //���ͼ����ʽ�������Ԥ�跽ʽ�������Ȱ����Entity��ӵ�dwg�С�
	void SetPatternAngle(double fAngle); //ͼ����б��
	void SetPatternScale(double fScale); //ͼ������
	void SetAssociative(bool bAssociative); //���ù����߽�
	void AppendAssocObjectIds(AcDbObjectIdArray& arrObjectId); //�����߽���󣬱����Ƿ�յ�ͼ�Ρ���Բ�������Ρ����Ρ���Բ�������
	void AppendLoopPoint(CPt3d *pPoint, int nNum);
	void SetPickPoint(CPt3d ptPick);
	void EvaluateHatch();
};

// ��(2008�漰�Ժ�֧��)
class CTable : public CBlock
{
public:
	CTable();
	CTable(AcDbObjectId& objectId);
	CTable(CTable& oTable);
	~CTable();

	void SetTableStyle(CTableStyle* pTableStyle);
	void SetRows(long nRows);
	void SetCols(long nCols);
	void SetHeight(double fHeight);
	void SetWidth(double fWidth);
	void SetGridColor(COLORREF clr);
	void SetGridWidth(long nRow, long nCol, double fWidth);
	void SetRowHeight(long nRow, double fHeight);
	void SetColName(long nCol, ArxRleString lpszName);
	void SetColWidth(long nCol, double fWidth);
	void SetCellValue(long nRow, long nCol, ArxRleString lpszText);
	void SetCellValue(long nRow, long nCol, long nValue);
	void SetCellValue(long nRow, long nCol, double fValue);
	void SetCellValue(long nRow, long nCol, __int64 fValue);

	void SetBackgroundColor(COLORREF clr);
	void SetAlignment(ArxAlignment align);
	void SetAlignment(long nRow, long nCol, ArxAlignment align);
	void SetTextHeight(double fHeight);
	void SetTextHeight(long nRow, long nCol, double fHeight);
	void SetTextColor(COLORREF clr);
	void SetTextColor(long nRow, long nCol, COLORREF clr);
	void SetTextStyle(CTextStyle* pTextStyle);
	void SetTextStyle(long nRow, long nCol, CTextStyle* pTextStyle);
	void MergeCells(long nRow1, long nRow2, long nCol1, long nCol2);
	void UnmergeCells(long nRow1, long nRow2, long nCol1, long nCol2);

	void InsertRows(long nRow, long nRows, double fHeight = 0);
};

// ����
class CLayout
{
public:
	CLayout();
	CLayout(AcDbObjectId objectId);
	CLayout(CLayout& layout);
	virtual ~CLayout();

	//����ӿڣ��ӿڣ���Ӧģ�Ϳռ��������꣬�ӿڿ�ȣ��ӿڸ߶ȣ����뵽ͼֽ�ռ����꣬����(ģ�Ϳռ䵽ͼֽ�ռ䣬ȱʡ1mm:1m)����ת�Ƕ�(����)���ü������
	void AddViewport(CViewport* pViewport, CPt3d ptMapLeftBottom, double fWidth, double fHeight,
		             CPt3d ptLeftBottom, double fScaleFactor, double fAngle, CPolyline* pLine = NULL);
	void SetPlotPaperSize(ArxRleString lpszName); //���ô�ӡͼֽ��С
	void SetPlotPaperSize(double fWidth, double fHeight, short nPaperUnits = 1); //���ô�ӡֽ��С������
	void SetInsertBase(CPt3d& pt);
	void SetLimits(CPt3d ptMin, CPt3d ptMax, bool bCheck);
	void GetLimits(CPt3d& ptMin, CPt3d& ptMax, bool& bCheck);
	void SetExtents(CPt3d ptMin, CPt3d ptMax);
	void GetExtents(CPt3d& ptMin, CPt3d& ptMax);
	void GetViewportList(CViewportArray& arr);
	void GetPaperSize(double& fWidth, double fHeight);
	void GetMargin(double& fLeft, double& fTop, double& fRight, double& fBottom);
	AcDbObjectId GetObjectId();
	void SetPlotViewportBorders(bool bPlot);
	char* GetPlotDeviceName();

	bool isValid();
	CLayout& operator = (AcDbObjectId objectId);
	CLayout& operator = (CLayout& layout);
	bool operator == (CLayout& layout);
	bool operator != (CLayout& layout);

	void SetName(ArxRleString lpszName);
	char* GetName() const;

protected:
	AcDbLayout* m_pLayout;
};

class CGroup
{
public:
	CGroup();
	CGroup(AcDbObjectId objectId);
	CGroup(CGroup& oGroup);
	~CGroup();
	bool IsNull() const;
	char* GetDescription() const;
	void SetDescription(ArxRleString lpszName);
	bool IsSelectable() const;
	void SetSelectable(bool bSelectable = true);
	char* GetName() const;
	void SetName(ArxRleString lpszName);
	bool IsNotAccessible() const;
	bool IsAnonymous() const;
	void SetAnonymous();
	void Append(AcDbObjectId objectId);
	void Append(vector<AcDbObjectId> objectIds);
	void Prepend(AcDbObjectId objectId);
	void Prepend(vector<AcDbObjectId> objectIds);
	void InsertAt(long index, AcDbObjectId objectId);
	void InsertAt(long index, vector<AcDbObjectId> objectIds);
	void Remove(AcDbObjectId objectId);
	void RemoveAt(long index);
	void Remove(vector<AcDbObjectId> objectIds);
	void RemoveAt(long index,vector<AcDbObjectId> objectIds);
	void Replace(AcDbObjectId oldId, AcDbObjectId newId);
	void Transfer(long fromIndex, long toIndex, long numItems);
	void Clear();
	long GetEntities() const;
	bool Has(CEntity* pEntity) const;
	int  AllEntityIds(vector<AcDbObjectId> objectIds) const;
	long GetIndex(AcDbObjectId objectId) const;
	void Reverse();
	void SetColorIndex(long index);
	void SetColor(COLORREF clr);
	void SetLayer(ArxRleString lpszName);
	void SetLayer(AcDbObjectId objectId);
	void SetLinetype(ArxRleString lpszName);
	void SetLinetype(AcDbObjectId objectId);
	void SetLinetypeScale(double fScale);
	void SetVisibility(bool bVisibility);
	void SetHighlight(bool newVal);
	void SetMaterial(ArxRleString lpszName);
	void SetMaterial(AcDbObjectId objectId);
	AcDbObjectId GetObjectId();
	AcDbGroup* GetObject();
protected:
	AcDbGroup* m_pGroup;
};

//����ʵ��
class CCreatEnt
{
public:
	CCreatEnt();
	~CCreatEnt();
	static AcDbObjectId CreateLine(AcGePoint3d ptStart,AcGePoint3d ptEnd);//���յ㻭��
	static AcDbObjectId PostToModelSpace(AcDbEntity* pEnt);//��ʵ����ӵ�ͼ�����ݿ��ģ�Ϳռ�
	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter,AcGeVector3d vec, double radius);//��Բ
	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter, double radius);//
	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);//
	static AcDbObjectId CreateArc(AcGePoint3d ptCenter, AcGeVector3d vec,
		                          double radius, double startAngle, double endAngle);//
	static AcDbObjectId CreateArc(AcGePoint2d ptCenter, double radius,
		                          double startAngle, double endAngle);
	static AcDbObjectId CreateArc(AcGePoint2d ptStart, AcGePoint2d ptOnArc,AcGePoint2d ptEnd);//
	static AcDbObjectId CreateText(const AcGePoint3d& ptInsert,
		                           ArxRleString text, AcDbObjectId style,
		                           double height, double rotation);//��������

	static AcDbObjectId CreateMText(const AcGePoint3d& ptInsert,
		                            ArxRleString text, AcDbObjectId style = AcDbObjectId::kNull,
		                            double height = 2.5, double width = 10);// ������������
};

bool isUcs();
int PointTrans(TCHAR *mode, ads_point pt_from, ads_point pt_to, int disp = false, struct resbuf* ent_from = NULL, struct resbuf* ent_to = NULL);
CPt3d U2W(CPt3d pt);
CPt3d W2U(CPt3d pt);
AcGePoint3d U2W(AcGePoint3d pt);
AcGePoint3d W2U(AcGePoint3d pt);

AcDbSymbolTableRecord* GetRecordPtr(AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead);
AcDbEntity* GetEntPtr(AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead);
bool UnLockEntity(AcDbEntity* ent, bool bLock = false);
COLORREF AcCmColorToRefColor(AcCmColor clr, AcDbObjectId layerId = 0);
AcCmColor RefColorToAcCmColor(COLORREF clr, AcCmEntityColor::ColorMethod clrMethod = AcCmEntityColor::kByACI, AcDbObjectId layerId = 0);
double MeasureTextLength(ArxRleString strText, double fFontWidth, int nFontType = 1);

void EraseGroup();
void EraseGroup(ArxRleString groupName);

AcDbObjectId AddLayer(ArxRleString lpszName);
AcDbObjectId AddLayer(ArxRleString lpszLayer,int iColorIndex, AcDb::LineWeight AcLineWeight = AcDb::kLnWt013, ArxRleString lpszLinetype = _T("Continuous"));
AcDbObjectId SetCurLayer(ArxRleString lpszName);
AcDbObjectId GetCurLayer();
ArxRleString GetCurLayerName();
AcDbObjectId FindLayer(ArxRleString lpszName);
bool DelLayer(ArxRleString lpszName);

AcDbObjectId AddLayout(ArxRleString lpszName);
bool DelLayout(ArxRleString lpszName);
void RenameLayout(ArxRleString lpszOldName, ArxRleString lpszNewName);
AcDbObjectId FindLayout(ArxRleString lpszName);
AcDbObjectId SetCurLayout(ArxRleString lpszName);
AcDbObjectId GetActiveLayout();
bool AddViewportRecord(AcDbViewportTableRecord* pViewportRecord);
AcDbObjectId GetActiveViewport();
void GetMediaNameList(CStringArray& arrName);
AcDbObjectId GetLayoutOfModelSpace();

AcDbObjectId AddBlockRecord(ArxRleString lpszName);
AcDbObjectId GetBlockRecord(ArxRleString lpszName);
void InsertDwg(ArxRleString lpszFileName);
void InsertRef(ArxRleString lpszFileName);
AcDbObjectId InsertBlockRecord(ArxRleString lpszFileName);
AcDbObjectId InsertBlockRecord(ArxRleString lpszFileName, ArxRleString lpszSource);
AcDbObjectId InsertBlockRecord(ArxRleString lpszNewName, ArxRleString lpszFileName, ArxRleString lpszSource);
AcDbObjectId InsertBlockRecordByReference(ArxRleString lpszName, ArxRleString lpszFileName);
bool GetBlockRecordName(ArxRleString lpszFileName, CStringArray& arrName);
long GetBlockRecordNameFromFile(ArxRleString lpszFilePath, ArxRleString lpszName, long nLength);
void SetInsbase(CPt3d ptInsBase);
CPt3d GetInsbase();

AcDbObjectId AddDimensionStyle(ArxRleString lpszName);
void AddDimensionStyle(AcDbDimStyleTableRecord* pDimStyleRecord);
AcDbObjectId GetDimensionStyle(ArxRleString lpszName);
AcDbObjectId GetStandardDimensionStyle();
bool SetCurDimensionStyle(ArxRleString  lpszName);

//���β���
void LoadLineType(ArxRleString lpszFile, ArxRleString lpszName);
bool SetCurLineType(ArxRleString lpszName);
void SetLTScale(double fScalse);
ArxRleString GetCurLineType();
AcDbObjectId GetLineType(ArxRleString lpszName);
bool GetLineTypeFromFile(ArxRleString lpszFile, CStringArray& arrLine);

AcDbObjectId AddTextStyle(ArxRleString lpszName, ArxRleString lpszFontName = "txt", ArxRleString lpszBigFontName = "tjhzf", double fWidthFactor = 0.7);
AcDbObjectId FindTextStyle(ArxRleString lpszName);
AcDbObjectId GetStandardTextStyle();
AcDbObjectId SetCurTextStyle(ArxRleString lpszName);
AcDbObjectId GetCurTextStyle();

AcDbObjectId GetCurTableStyle();

AcDbObjectId AddDimStyle(ArxRleString lpszName);
AcDbObjectId FindDimStyle(ArxRleString lpszName);
AcDbObjectId GetStandardDimStyle();
AcDbObjectId SetCurDimStyle(ArxRleString lpszName);
AcDbObjectId GetCurDimStyle();

enum POINTMODE{PM_POINT=0,PM_WHITE,PM_CROSS,PM_FORK,PM_ERECT,
	PM_CPOINT=32,PM_CWHITE,PM_CCROSS,PM_CFORK,PM_CERECT,
	PM_RPOINT=64,PM_RWHITE,PM_RCROSS,PM_RFORK,PM_RERECT,
	PM_RCPOINT=96,PM_RCWHITE,RM_RCCROSS,PM_RCFORK,PM_RCERECT};
void SetPointMode(POINTMODE mode);
POINTMODE GetPointMode();
void SetPointSize(double fSize);
double GetPointSize();
void SetLimits(const CPt3d ptMin, const CPt3d ptMax, bool bCheck);
void GetLimits(CPt3d& ptMin, CPt3d& ptMax, bool& bCheck);
AcDbObjectId AddUcs(ArxRleString lpszName);
AcDbObjectId SetCurrentUcs(CPt3d ptOrigin, CPt3d xAxis, CPt3d yAxis);
void SetCurrentUcs(AcDbUCSTableRecord* pUcsTableRcd);
AcDbObjectId SetCurrentUcs(ArxRleString lpszName);

CPt3dArray ReadPtDataFile(ArxRleString strPointFile, bool bChange = false);
bool WritePtDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile);
CPt3dArray ReadZdmDataFile(ArxRleString strPointFile, bool bChange = false);
bool WriteZdmDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile, double stat = 0, double height = 0);
CPt3dArray ReadHdmDataFile(ArxRleString strPointFile, bool bChange = false);
bool WriteHdmDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile, int id = 0, double height = 0);

double AdjustAngle02(double fAngle);
double AdjustAngleNP(double fAngle);
int GetACIByRGB(byte r, byte g, byte b);
int GetACIByREF(COLORREF clr);
COLORREF GetRGBByACI(int aci);

CPt3d GetNewPoint(CPt3d& oBeginPt, double fOffsetLength, double fRadiusotation);
double GetDistOf2Pts(CPt3d& oBeginPt, CPt3d& oEndPt, bool bSpace = false);
double GetAngleOf2Pts(CPt3d& oBeginPt, CPt3d& oEndPt);
int JudgePointOnLine(CPt3d& oPoint, CPt3d& oLineBeginPt, CPt3d& oLineEndPt);
int JudgePointOnCircle(CPt3d& oPoint, CPt3d& oCenterPt, double fRadius);
int JudgePointOnArc(CPt3d& oPoint, CPt3d& oCenterPt, CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius);

AcDbDatabase* ArxRleDataBase();
AcDbBlockTableRecord* ArxRleDrawSpace();
AcDbPlotSettingsValidator* ArxRlePlotSettingsValidator();
AcDbDataLinkManager* ArxRleDataLinkManager();
AcApDocument* ArxRleApDocument();//kWrite
ArxRleString GetCurDwgFilePath();
void SendMsgToAcad(ArxRleString cmd);
void SendCmdToAcad(ArxRleString cmd);
void SendCmdToAcad(ArxRleString cmd, ArxRleString pram);
Acad::ErrorStatus OpenEntity(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode, bool lockDocument = true, bool openErasedEntity = false);
void CloseEntity(AcDbEntity* pEnt, bool unLockDocument = true, bool flushGraphics = true);
AcDbBlockTableRecord* GetDrawSpace(ArxSpaceType SpaceType = ArxModel);
AcDbBlockTableRecord* SetDrawSpace(ArxSpaceType SpaceType = ArxModel);
bool ArxRleSave();
void AddEntity(CEntity* pEntity);
AcDbObjectId add_Entity(AcDbEntity *pEntity);
AcDbObjectId AddEntity(AcDbEntity *pEntity);

void add_Point(double fX, double fY, double fZ);
void AddPoint(double fX, double fY, double fZ);
void AddPoint(CPt3d& oPoint3D);
void AddPoint(CPt3dArray& oPointArray);

void add_Line(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2);
void AddLine(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2);
void AddLine(CPt3d& oBeginPt, CPt3d& oEndPt);

void add_Polyline(CPt3dArray& oPointArray);
void AddPolyline(CPt3dArray& oPointArray, double fConstantWidth = 0);
void AddPolyline(CPt3dArray& oPointArray, vector<unsigned int> index, vector<double> fBeginWidth, vector<double> fEndWidth);
void AddPolyline(CPt3dArray& oPointArray, unsigned int index, double fBeginWidth, double fEndWidth);
void AddRectangular(CPt3d& oBeginPt, CPt3d& oEndPt, double fConstantWidth = 0);
void AddRectangular(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2, double fConstantWidth = 0);

void add_Circle(CPt3d& oCenterPt, double fRadiusadius);
void AddCircle(CPt3d& oCenterPt, double fRadiusadius);
void AddCircle(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadiusadius);

void add_Arc(CPt3d& oCenterPt, double fRadius, double fBeginAngle, double fEndAngle);
void AddArc(CPt3d& oCenterPt, double fRadius, double fBeginAngle, double fEndAngle);
void AddArc(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius, bool bMajorArc = false);
void AddArc(CPt3d& oBeginPt, CPt3d& oMidPt, CPt3d& oEndPt);
double GetArcBulge(CPt3d& oBeginPt, CPt3d& oMidPt, CPt3d& oEndPt);
double GetArcBulge(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius, bool bMajorArc = false);
double GetArcBulge(AcDbArc*& pArc);

void add_Text(ArxRleString lpszText, CPt3d& oInsertPt, double fHeight = 2.5);
void AddText(ArxRleString lpszText, CPt3d& oAlignmentPt, double fHeight = 2.5, double fRotation = 0, ArxAlignment eAlign = ArxCenter);
void AddText(AcDbTextStyleTableRecord* ts, ArxRleString lpszText, CPt3d& oAlignmentPt, double fHeight = 2.5, double fRotation = 0, ArxAlignment eAlign = ArxCenter);

void add_MText(ArxRleString lpszText, CPt3d& oCenterPt, double fWidth);
void AddMText(ArxRleString lpszText, CPt3d& oInsertPt, double fWidth=0, double fHeight=2.5, double fRadiusotation = 0, ArxAlignment eAlign = ArxCenter);

void AddAttributeDefinition(ArxRleString lpszDefinition, ArxRleString lpszPrompt, ArxRleString lpszTag, CPt3d& oInsertPt, double fHeight, double fRotation = 0);
void AddBlock(CPt3d& oInsertPt, ArxRleString lpszBlkName, double fXscale=1, double fYscale = 1, double fRotation = 0, double fZscale = 1);
Acad::ErrorStatus SetBlockAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef);
void AddBlock(ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt = CPt3d(1,1,1), double fRotation = 0);
void AddBlock(ArxRleString lpszDwgFilePath, ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt = CPt3d(1,1,1), double fRotation = 0);
void AddMBlock(ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt, double fRotation, int nRows, int nColumns, double fRowSpace, double fColSpace);

void cmd_offset(AcDbObjectId id, CPt3d pt, double oft);
void cmd_fillet(AcDbObjectId id1, AcDbObjectId id2, CPt3d pt1, CPt3d pt2, double r);
void To2dPolyline(AcDbObjectId objId, int flag =0);
void To2dLine(AcDbObjectId objId);
void To2dArc(AcDbObjectId objId);

#endif //ARXRLEENTITY_H