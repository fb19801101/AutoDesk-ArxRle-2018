// ArxRleEntityClass.h: interface for the ArxRleEntity class.
//

#ifndef ARXRLE_ENTITY_H
#define ARXRLE_ENTITY_H

#include "ArxRleString.h"
#include <complex>
#include <vector>
using namespace std;


//文字对齐方式
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

//表格对齐方式
enum ArxMargin
{
	ArxMarginTop         = 0x01,
	ArxMarginLeft        = 0x02,
	ArxMarginBottom      = 0x04,
	ArxMarginRight       = 0x08,
	ArxMarginHorzSpacing = 0x10,
	ArxMarginVertSpacing = 0x20
};

// 颜色类型
enum ArxColorType
{
	ArxByBlock = -2,		//由块
	ArxByLayer = -1,		//由图层
	ArxByNone = 0,     	//无
	ArxByValue = 1,  	//RGB
	ArxByACI = 2	    	//索引
};

// 文件类型
enum ArxFileType
{
	ArxDwg = 1,		//DWG
	ArxDxf = 2,		//DXF
	ArxNull = 0,      //无
};

// 标注类型
enum ArxDimtad
{
	ArxTadCenter = 0,
	ArxTadAbove,
	ArxTadSide,
	ArxTadJis
};

// 布局类型
enum ArxSpaceType
{
	ArxModel = 0,
	ArxActive = 1,
	ArxPaper = 2,
	ArxOther = 3,
};

#ifndef PI
#define PI 3.141592653589793238462643383279502884197169399375105820974944592308   //圆周率 PI
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
	double GetVectorAzimuth(const CPt3d& ptEnd); //返回值-π到π
	static double GetVectorAzimuth(const CPt3d& ptStart, const CPt3d& ptEnd);
	CPt3d GetLineEnd(const double fLength, const double fRotation); //如果fLength小于零，相当于反向
	static CPt3d GetLineEnd(const CPt3d& ptStart, double fLength, double fRotation);
};
typedef vector<CPt3d> CPt3dArray;

// 图层
class CLayer
{
public:
	CLayer();
	CLayer(AcDbObjectId& objectId);
	CLayer(const CLayer& oLayer);
	~CLayer();
	AcDbLayerTableRecord* GetRecord() {return m_pLayer;}

	void SetName(ArxRleString lpszName);			//设置图层名
	void SetColor(COLORREF clr);	//设置颜色
	void SetDescription(ArxRleString lpszDescription);	//设置描述
	void SetLineWidth(double fWidth);	//设置线宽
	void SetOff(bool bIsOff = false);			//设置On/Off
	void SetLocked(bool bIsLocked = false);		//设置锁定
	void SetFrozen(bool bIsFrozen = false);		//设置冻结
	void SetHidden(bool bIsHidden = false);		//设置隐藏
	void SetPrintable(bool bIsPrint = false);	//设置打印
	void SetLineType(AcDbObjectId& objectId);   	//设置线形

	bool isValid();
	CLayer& operator = (AcDbObjectId& objectId);
	CLayer& operator = (CLayer& layer);
	bool operator == (CLayer& layer);
	bool operator != (CLayer& layer);

	char* GetName();							//得到图层名
	COLORREF GetColor();
	AcDbObjectId GetObjectId();

protected:
	AcDbLayerTableRecord* m_pLayer;
};
typedef AcArray<CLayer> CLayerArray;

class CEntity;
class CLayout;
class CViewport;

// 文字样式
class CTextStyle
{
public:
	CTextStyle(); //缺省构造函数，空对象
	CTextStyle(AcDbObjectId& objectId);//基于对象索引创建
	CTextStyle(CTextStyle& oTextStyle); //复制构造函数
	virtual ~CTextStyle();
	bool isValid();

	void SetName(ArxRleString lpszName); //设置样式名称
	void SetFont(ArxRleString lpszFontName, bool bold = false, bool italic = false); //设置windows字体
	void SetFont(ArxRleString lpszFontName, ArxRleString lpszBigFontName, bool vertical = false); //设置cad字体
	void SetHeight(double fHeight); //设置字体高
	void SetWidthFactor(double fXScale); //设置字体高宽比
	void SetOblique(double fOblique); //设置字体倾斜角度
	void SetUpsideDown(bool bUpsideDown); //设置字体颠倒
	void SetBackward(bool bBackward); //设置字体反向
	char* GetName(); //得到样式名称
	double GetHeight(); //得到字体高
	double GetWidthFactor(); //得到字体高宽比
	double GetOblique(); //得到字体倾斜角度
	bool GetUpsideDown(); //得到字体颠倒
	bool GetBackward();//得到字体反向
	void GetFont(char* lpszFontFace, bool& bBold, bool& bItalic);
	void GetFont(char* lpszFontName, char* lpszBigFontName, bool& bVertical);
	int GetFontType() const;

	AcDbObjectId GetObjectId();

protected:
	AcDbTextStyleTableRecord* m_pTextStyleRecord;
};

// 表格样式
class CTableStyle
{
public:
	CTableStyle(); //缺省构造函数，空对象
	CTableStyle(AcDbObjectId& objectId);//基于对象索引创建
	CTableStyle(CTableStyle& oTableStyle); //复制构造函数
	virtual ~CTableStyle();
	bool isValid();

	void SetName(ArxRleString lpszName); //设置样式名称
	void SetTextStyle(CTextStyle* pTextStyle); //设置文本样式
	void SetTextHeight(double fHeight); //设置字体高
	void CreateCellStyle(ArxRleString lpszName); //创建单元样式
	void SetRotation(double fRotation, ArxRleString lpszCellStyle = ""); //设置旋转角度
	void SetFlowDirection(bool bFlow); //设置表格方向
	void SetTextStyle(CTableStyle* pTextStyle);
	char* GetName(); //得到样式名称
	CTextStyle GetTextStyle(); //得到文本样式
	double GetTextHeight(); //得到字体高
	double GetRotation(ArxRleString lpszCellStyle); //得到旋转角度
	void SetMargin(ArxMargin eMargin, double fMargin, ArxRleString lpszCellStyle = ""); //设置边距 
	bool GetFlowDirection(); //得到表格方向
	
	AcDbObjectId GetObjectId();

protected:
	AcDbTableStyle* m_pTableStyle;
};

// 块记录
class CBlockRecord
{
public:
	CBlockRecord(); //缺省构造函数，空对象
	CBlockRecord(AcDbObjectId& objectId);//基于对象索引创建
	CBlockRecord(CBlockRecord& oBlockRcd); //复制构造函数
	CBlockRecord(ArxRleString lpszName);
	virtual ~CBlockRecord();

	bool LoadFile(ArxRleString lpszPathName);	//从dwg文件中加载块
	bool AppendEntity(CEntity* pEntity);		//添加图元
	bool isValid();

	CBlockRecord& operator = (CBlockRecord& record);
	CBlockRecord& operator = (AcDbObjectId& objectId);

	void SetName(ArxRleString lpszName);
	void SetOrigin(CPt3d pt);                   //设置基点
	void SetComments(ArxRleString lpszComment);	//设置说明
	void SetLayout(CLayout* pLayout);			//设置布局
	void SetBlockScaling(bool bAny); //false-kAny:Block references can be non-uniformly scaled.
	void SetExplodable(bool bExplodable);		//设置是否可以炸开
	bool Explodable(); //是否可以炸开
	
	AcDbObjectId GetObjectId();
	char* GetName();

protected:
	AcDbBlockTableRecord* m_pBlockRecord;
};

// 标注
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

	void SetArrow(ArxRleString lpszName);        //同时设置箭头样式
	void SetArrow(ArxRleString lpszName1, ArxRleString lpszName2);		//箭头1样式, 箭头2样式
	void SetDimasz(double fSize);		//设置箭头大小
	void SetDimzin(byte nBits);		//十进制小数显示时，抑制后续零

	CDimensionStyle& operator = (AcDbObjectId& objectId);
	CDimensionStyle& operator = (CDimensionStyle& style);
	bool operator == (CDimensionStyle& dim);
	bool operator != (CDimensionStyle& dim);

	AcDbObjectId GetObjectId();

protected:
	AcDbDimStyleTableRecord* m_pDimensionStyle;
};

//用户坐标系
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

// CEntity  图元基类
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

// 点
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

// 直线
class CLine : public CEntity
{
public:
	CLine();
	CLine(AcDbObjectId& objectId);
	CLine(CLine& oLine);
	~CLine();

public:
	void SetPoint(CPt3d ptStart, CPt3d ptEnd);	//设置起终点
	void Set(CPt3d ptStart, double fLength, double fRotation); //设置起点，长度，旋转角度(相对于x轴，逆时针为正)
	void GetPoint(CPt3d& ptStart, CPt3d& ptEnd);	//获得起终点
};

// CPolyline  多段线图元
class CPolyline : public CEntity
{
public:
	CPolyline();
	CPolyline(AcDbObjectId& objectId);
	CPolyline(CPolyline& oPolyLine);
	virtual ~CPolyline();

public:
	void AddPoint(CPt3dArray arrPoint);	//添加直线点
	void AddPoint(AcGePoint3dArray arrPoint);	//添加直线点
	long AddPoint(CPt3d ptPosition);		//添加直线点
	long AddLine(CPt3d ptStart, double fLength, double fRotation);
	long AddArc(CPt3d ptStart, double fCentralAngle); //添加圆弧:起点坐标、圆心角度
	void InsertPoint(long nIndex, CPt3d ptPosition);
	void SetIsClosed(bool bIsClosed);	//设置是否闭合
	bool IsClosed() const;	//是否闭合
	void SetLineWidth(double fWidth);	//设置全局线宽度
	void SetWidthAt(long nIndex, double fStartWidth, double fEndWidth);
	int GetPointNum() const;	//得到点数
	CPt3dArray GetPoint();	//得到点组
	double GetLineWidth() const;//获得全局线宽度
	bool HasArc();	//是否有圆曲线
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

// 圆
class CCircle : public CEntity
{
public:
	CCircle();
	CCircle(AcDbObjectId& objectId);
	CCircle(CCircle& oCircle);
	~CCircle();

public:
	void Set(CPt3d ptCenter, double fRadius);	//圆心 半径
	void SetPoint(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd); //三角形外接圆
	bool SetPointRadius(CPt3d ptStart, CPt3d ptEnd, double fRadius); // 起终点、半径带方向
	bool GetIsClosed();
	CPt3d GetCenter();
	double GetRadius();
	double GetArea();

	bool SelEntity(ArxRleString strPrompt);
};

// 圆弧
class CArc : public CEntity
{
public:
	CArc();
	CArc(AcDbObjectId& objectId);
	CArc(CArc& oArc);
	~CArc();

public:
	bool Set(CPt3d ptCenter, double fRadius, double fStartAngle,  double fEndAngle);	//圆心 半径	圆弧起终点角度
	bool Set(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd); //三角形外接圆
	bool Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, double fStartTangle); // 起终点、半径带正负（圆弧在弦的左侧为负否则在右为正）、起点切线角
	bool Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, bool bMinorArc = true); // 起终点、半径带正负（圆弧在弦的左侧为负否则在右为正）、优弧还是劣弧
	bool GetIsClosed();
	CPt3d GetCenter();
	double GetRadius();
	double GetStartAngle();
	double GetEndAngle();
	double GetArea();
};

// 椭圆弧
class CEllipse : public CEntity
{
public:
	CEllipse();
	CEllipse(AcDbObjectId& objectId);
	CEllipse(CEllipse& oEllipse);
	~CEllipse();

public:
	void Set(CPt3d ptCenter, CPt3d vtMajorAxis, double fRadiusRatio, double fStartAngle = 0.0, double fEndAngle = 2 * PI);
	void SetEx(CPt3d ptMajorStart, CPt3d ptMajorEnd, double fMinorRadius, double fStartAngle = 0.0, double fEndAngle = 2 * PI); 	//设置椭圆参数: 主轴起点坐标，主轴终点坐标，次轴最大半径，起始角度，终止角度
	bool GetIsClosed();
	CPt3d GetCenter();
	CPt3d GetMajorAxis();
	double GetStartAngle();
	double GetEndAngle();
	double GetArea();
};

// 文本
class CText : public CEntity
{
public:
	CText();
	CText(AcDbObjectId& objectId);
	CText(CText& oText);
	~CText();

public:
	void SetPosition(CPt3d ptPosition);			//位置
	void SetText(ArxRleString lpszText);				//文本
	void SetRotation(double fRotation);				//旋转角度（逆时针为正）
	void SetOblique(double fOblique);				//倾斜角度（类似于斜体字）
	void SetTextHeight(double fHeight);					//字高
	void SetAlignmentMode(ArxAlignment eAlign);		//对齐方式
	// 	void SetAlignmentPoint(CPt3d ptPosition);	//设置对齐点
	void SetTextStyle(AcDbTextStyleTableRecord* pTextStyle);     //设置文本样式
	void SetTextStyle(AcDbObjectId& oTextStyleId);     //设置文本样式
	void SetTextStyle(CTextStyle& ts);
	void SetWidthFactor(double fFactor);			//宽度因子

	CPt3d GetPosition();
	char* GetText();
	double GetHeight();
	double GetRotation();
	double GetOblique();
	double GetWidthFactor();
	double GetActualWidth();                              //得到文本宽度，必须已经添加到数据库中
	void GetBoundPoint(CPt3d& ptTopLeft, CPt3d& ptTopRight, CPt3d& ptBottomRight, CPt3d& ptBottomLeft);
	void GetGeomExtents(CPt3d& ptMin, CPt3d& ptMax);
};

// 多文本
class CMText :  public CEntity
{
public:
	CMText();
	CMText(AcDbObjectId& objectId);
	CMText(CMText& oMText);
	~CMText();

public:
	void SetPosition(CPt3d ptPosition);			//位置
	void SetText(ArxRleString lpszText);				//文本
	void SetRotation(double fRotation);				//旋转角度
	void SetHeight(double fHeight);					//图元高，缺省=(行数-1)*5/3*字高*行距比例+字高
	void SetWidth(double fWidth);                   //宽度，超过这个宽度自动换行
	void SetTextHeight(double fHeight);				//字高
	void SetAlignmentMode(ArxAlignment eAlign);		//对齐方式
	void SetTextStyle(AcDbTextStyleTableRecord* pTextStyle);     //设置文本样式
	void SetTextStyle(AcDbObjectId& oTextStyleId);     //设置文本样式
	void SetTextStyle(CTextStyle& ts);     //设置文本样式
	void SetLineSpaceFactor(double fFactor);        //设置行距比例
	void SetLineSpaceStyle(short nStyle);         //设置行距样式
	void SetBackgroundFill(bool bFill, double fScaleFactor, bool bUseBackground, COLORREF clr); //设置背景遮罩
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

// 块。
class CBlock : public CEntity
{
public:
	CBlock();
	CBlock(AcDbObjectId& objectId);
	CBlock(CBlock& oBlock);
	~CBlock();

public:
	void SetPosition(CPt3d ptPosition);		//位置
	void SetRotation(double fRotation);			//旋转
	void SetBlockRecord(AcDbBlockTableRecord *pRecord);//设置数据库中的块记录
	void SetScaleFactors(CPt3d ptScale);	//设置比例
	void GetEntityArray(AcDbObjectIdArray& arrObjectId); //得到块中的图元
	void Explode(AcDbObjectIdArray& arrObjectId, AcDbBlockTableRecord* pBlockRecord); //炸开块，将图元添加到指定块记录中
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

// 视口
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

// 标注
class CDimension : public CEntity
{
public:
	CDimension();
	CDimension(AcDbObjectId& objectId);
	CDimension(CDimension& oDimension);
	virtual ~CDimension();

	void SetDimBlockRecord(CBlockRecord* pRecord); //和这个标注关联的块

	void SetDimensionStyle(CDimensionStyle *pDimStyle);
	void SetText(ArxRleString lpszText);
	void SetTextPosition(CPt3d ptPosition);
	void SetTextRotation(double fRotation);
	void SetArrowFlipped(bool bFirst, bool bSecond);
	void SetDynamicDimension(bool bDynamic);

	void SetArrow(ArxRleString lpszName);		//箭头样式
	void SetExtLineFixLenEnable(bool bEnable);	//固定尺寸界线
	void SetExtLineFixLen(double fLength);		//尺寸界线的固定长度
	void SetDimExt1Linetype(AcDbObjectId& objectId);	//尺寸界线1的线形
	void SetDimExt2Linetype(AcDbObjectId& objectId);	//尺寸界线2的线形
	void SetArrowSize(double fSize);		//设置箭头大小
	void SetDimzin(byte nBits);		//十进制小数显示时，抑制后续零
	void SetDimexe(double fDis);	//设置尺寸界线超出尺寸线距离
	void SetDimexo(double fOffset);	//设置尺寸界线的起点偏移量
	void SetTextHeight(double fHeight);	//设置文字高度
	void SetTextHorz(ArxDimtad eTad);	//设置文字位置，水平默认为居中，不用设置
	void SetTextOffset(double fGap);	//设置文字位置-从尺寸线的偏移量
	void SetDimtih(bool bTih);	//设置标注文字方向沿尺寸界线内侧，false和尺寸界线对齐，true横向
	void SetDimtoh(bool bToh);	//设置标注文字方向沿尺寸界线外侧，false和尺寸界线对齐，true横向
	void SetDimtix(bool bTix);	//设置标注文字始终绘制在尺寸界线之间
	void SetDimtofl(bool bTofl);	//即使箭头放置于测量点之外，尺寸线也将绘制在测量点之间。false不能，true能
	void SetLineColor(COLORREF clr);	//尺寸线颜色
	void SetExtLineColor(COLORREF clr);	//尺寸界线颜色
	void SetTextColor(COLORREF clr);	//文字颜色
	void SetDimLineType(AcDbObjectId oLineType);  //尺寸线样式

	//对齐标注
	void SetAlignedDimPoint(CPt3d pt1, CPt3d pt2, double fDis);//两点间距离标注，第三个参数是标注离两点连线距离，左负右正
	void SetAlignedDimPoint(CPt3d pt);
	void SetAlignedDimOblique(double fOblique);				//倾斜角度（类似于斜体字）

	//角度标注
	void SetPoint(CPt3d ptStart1, CPt3d ptStart2, CPt3d ptCenter); //直线1的起点，直线2的起点，交点
	void SetArc(CPt3d ptArc); //圆上点

	//弧长标注
	void SetArcDimPoint(CPt3d ptArc); //圆上点
	void SetArcDimCenterPoint(CPt3d ptCenter); //圆心
	void SetArcDimLeaderPoint(CPt3d pt1, CPt3d pt2); //引线端点

	//坐标标注
	void SetGridDimDefiningPoint(CPt3d ptDefine);//指定点
	void SetGridDimLeaderEndPoint(CPt3d ptEnd); //引线端点


	//半径标注
	void SetRadiusDimCenter(CPt3d ptCenter);//指定圆
	void SetRadiusDimChordPoint(CPt3d ptChord, double fLeaderLength); //弦点，引线长度
};

// 图案填充
class CHatch : public CEntity
{
public:
	CHatch();
	CHatch(AcDbObjectId& objectId);
	CHatch(CHatch& oHatch);
	~CHatch();

	enum ArxHatchObjectType{zHatch = 0, zGradient};
	void SetHatchObjectType(ArxHatchObjectType type);
	void SetGradiant(ArxRleString lpszName, bool bUser = false); //设置渐变图案
	void SetOriginPoint(CPt3d pt);
	enum ArxHatchStyle{zNormal = 0, zOuter, zIgnore};
	void SetHatchStyle(ArxHatchStyle style); //孤岛检测样式
	enum ArxHatchPatternType{zUserDefined = 0, zPreDefined, zCustomDefined};
	bool SetPattern(ArxRleString lpszName, ArxHatchPatternType eType); //填出图案样式，如果是预设方式，必须先把这个Entity添加到dwg中。
	void SetPatternAngle(double fAngle); //图案倾斜角
	void SetPatternScale(double fScale); //图案比例
	void SetAssociative(bool bAssociative); //设置关联边界
	void AppendAssocObjectIds(AcDbObjectIdArray& arrObjectId); //关联边界对象，必须是封闭的图形。如圆、三角形、矩形、椭圆、多边形
	void AppendLoopPoint(CPt3d *pPoint, int nNum);
	void SetPickPoint(CPt3d ptPick);
	void EvaluateHatch();
};

// 表(2008版及以后支持)
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

// 布局
class CLayout
{
public:
	CLayout();
	CLayout(AcDbObjectId objectId);
	CLayout(CLayout& layout);
	virtual ~CLayout();

	//添加视口：视口，对应模型空间左下坐标，视口宽度，视口高度，插入到图纸空间坐标，比例(模型空间到图纸空间，缺省1mm:1m)，旋转角度(弧度)，裁剪多边形
	void AddViewport(CViewport* pViewport, CPt3d ptMapLeftBottom, double fWidth, double fHeight,
		             CPt3d ptLeftBottom, double fScaleFactor, double fAngle, CPolyline* pLine = NULL);
	void SetPlotPaperSize(ArxRleString lpszName); //设置打印图纸大小
	void SetPlotPaperSize(double fWidth, double fHeight, short nPaperUnits = 1); //设置打印纸大小，毫米
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

//创建实体
class CCreatEnt
{
public:
	CCreatEnt();
	~CCreatEnt();
	static AcDbObjectId CreateLine(AcGePoint3d ptStart,AcGePoint3d ptEnd);//起终点画线
	static AcDbObjectId PostToModelSpace(AcDbEntity* pEnt);//将实体添加到图形数据库的模型空间
	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter,AcGeVector3d vec, double radius);//画圆
	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter, double radius);//
	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);//
	static AcDbObjectId CreateArc(AcGePoint3d ptCenter, AcGeVector3d vec,
		                          double radius, double startAngle, double endAngle);//
	static AcDbObjectId CreateArc(AcGePoint2d ptCenter, double radius,
		                          double startAngle, double endAngle);
	static AcDbObjectId CreateArc(AcGePoint2d ptStart, AcGePoint2d ptOnArc,AcGePoint2d ptEnd);//
	static AcDbObjectId CreateText(const AcGePoint3d& ptInsert,
		                           ArxRleString text, AcDbObjectId style,
		                           double height, double rotation);//创建文字

	static AcDbObjectId CreateMText(const AcGePoint3d& ptInsert,
		                            ArxRleString text, AcDbObjectId style = AcDbObjectId::kNull,
		                            double height = 2.5, double width = 10);// 创建多行文字
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

//线形操作
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