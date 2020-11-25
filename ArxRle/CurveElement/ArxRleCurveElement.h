// ArxRleCurveElement.h: interface for the ArxRleCurveElement class.
//

#ifndef ARXRLE_CRUVE_ELEMENT_H
#define ARXRLE_CRUVE_ELEMENT_H

typedef struct tagJDELEMENT
{
	CString JD;								 // 交点编号
	double x, y;						     // 交点坐标

	double R1, Ls1, A1;                      // 前缓和曲线半径,长度、参数
	double R2, Ls2, A2;                      // 后缓和曲线半径,长度、参数
	double T1, T2;                           // 前后切线长
	double Rc, Lc;                           // 圆曲线半径,长度
	double L, E, Lz;					     // 曲线总长、外矢距、夹直线长

	double fwj, pj;	                         // 方位角、偏角

	double DK, QD, ZD;                       // 交点里程、起终点里程
	double ZH, HY, QZ, YH, HZ;               // 曲线主点里程

	double QD_x, QD_y, ZD_x, ZD_y;			 // 起终点坐标
	double ZH_x,ZH_y,HZ_x,HZ_y;				 // 直缓缓直点坐标
	double HY_x,HY_y,YH_x,YH_y;				 // 缓圆圆缓点坐标
	double QZ_x,QZ_y;                        // 曲中坐标

	tagJDELEMENT()
	{
		JD = _T("JDXX");
		x = y = 0;

		R1 = Ls1 = A1 = 0;
		R2 = Ls2 = A2 = 0;
		T1 = T2 = 0;
		Rc = Lc = 0;
		L = E = Lz = 0;

		fwj = pj = 0;	

		DK = QD = ZD = 0;
		ZH = HY = QZ = YH = HZ = 0;

		QD_x = QD_y = ZD_x = ZD_y = 0;
		ZH_x = ZH_y = HZ_x = HZ_y = 0;
		HY_x = HY_y = YH_x = YH_y = 0;
		QZ_x = QZ_y = 0;
	}

	tagJDELEMENT(const tagJDELEMENT& src)
	{
		JD = src.JD;
		x = src.x, y = src.y;

		R1 = src.R1, Ls1 = src.Ls1, A1 = src.A1;
		R2 = src.R2, Ls2 = src.Ls2, A2 = src.A2;
		T1 = src.T1, T2 = src.T2;
		Rc = src.Rc, Lc = src.Lc;
		L = src.L, E = src.E, Lz = src.Lz;

		fwj = src.fwj, pj = src.pj;
		
		DK = src.DK, QD = src.QD, ZD = src.ZD;
		ZH = src.ZH, HY = src.HY, QZ = src.QZ, YH = src.YH, HZ = src.HZ;
		
		QD_x = src.QD_x, QD_y = src.QD_y, ZD_x = src.ZD_x, ZD_y = src.ZD_y;
		ZH_x = src.ZH_x, ZH_y = src.ZH_y, HZ_x = src.HZ_x, HZ_y = src.HZ_y;
		HY_x = src.HY_x, HY_y = src.HY_y, YH_x = src.YH_x, YH_y = src.YH_y;
		QZ_x = src.QZ_x, QZ_y = src.QZ_y;
	}

	tagJDELEMENT operator =(const tagJDELEMENT& src)
	{
		JD = src.JD;
		x = src.x, y = src.y;

		R1 = src.R1, Ls1 = src.Ls1, A1 = src.A1;
		R2 = src.R2, Ls2 = src.Ls2, A2 = src.A2;
		T1 = src.T1, T2 = src.T2;
		Rc = src.Rc, Lc = src.Lc;
		L = src.L, E = src.E, Lz = src.Lz;

		fwj = src.fwj, pj = src.pj;

		DK = src.DK, QD = src.QD, ZD = src.ZD;
		ZH = src.ZH, HY = src.HY, QZ = src.QZ, YH = src.YH, HZ = src.HZ;
		
		QD_x = src.QD_x, QD_y = src.QD_y, ZD_x = src.ZD_x, ZD_y = src.ZD_y;
		ZH_x = src.ZH_x, ZH_y = src.ZH_y, HZ_x = src.HZ_x, HZ_y = src.HZ_y;
		HY_x = src.HY_x, HY_y = src.HY_y, YH_x = src.YH_x, YH_y = src.YH_y;
		QZ_x = src.QZ_x, QZ_y = src.QZ_y;

		return *this;
	}

	//获取待算里程位于交点那一部分 1 前直线  2 前缓和曲线  3 圆曲线  4 后缓和曲线  5 后直线
	int in_dk_part(double dk)
	{
		if (dk > QD && dk < ZH)
			return 1;
		if (dk > ZH && dk < HY)
			return 2;
		if (dk > HY && dk < YH)
			return 3;
		if (dk > YH && dk < HZ)
			return 4;
		if (dk > HZ && dk < ZD)
			return 5;

		return -1;
	}
}JDELEMENT;

typedef struct tagSQXELEMENT
{
	double DK, H, R, I1, I2;
	double T, E, L;

	tagSQXELEMENT()
	{
		DK=H=R=I1=I2=T=E=L = 0;
	}

	tagSQXELEMENT(const tagSQXELEMENT& src)
	{
		DK = src.DK;
		H = src.H;
		R = src.R;
		I1 = src.I1;
		I2 = src.I2;
		T = src.T;
		E = src.E;
		L = src.L;
	}

	tagSQXELEMENT operator =(const tagSQXELEMENT& src)
	{
		DK = src.DK;
		H = src.H;
		R = src.R;
		I1 = src.I1;
		I2 = src.I2;
		T = src.T;
		E = src.E;
		L = src.L;

		return *this;
	}

}SQXELEMENT;

typedef std::vector<JDELEMENT> JDELEMENTLIST;
typedef std::vector<SQXELEMENT> SQXELEMENTLIST;

class ArxRleCurveElement
{
public:
	ArxRleCurveElement();
	~ArxRleCurveElement();

	void InputJDData(CString inputfilename);//文件输入函数
	void InputSQXData(CString inputfilename);//文件输入函数
	void ReadMDBTable(CString mdbFname,CString TabFname);
	void OutputJDResult(CString outputfilename);//文件输出函数
	void WriteMDBTable(CString mdbFname, CString TabFname);
	BOOL Execute(CString strSQL);

	
	//计算方位角、偏角
	void Calc_fwj_pj();
	//计算缓和参数、外失距、曲线总长
	void Calc_A_E_L();
	//计算HY、YH点坐标
	double* Calc_HY_YH_xy(double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2);
	//计算圆曲线上任一点的坐标
	double* Calc_Circle_xy(double dk, double dist, double dk_HY, double x_HY, double y_HY, double x_YH, double y_YH, double x_JD, double y_JD, double Rc);
	//计算直线上任一点的坐标
	double* Calc_Line_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1);
	//计算缓和曲线上任一点的坐标
	double* Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _T1, double _T2, double _Ls1, double _Ls2);
	//计算缓和曲线上任一点的坐标
	double* Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2);
	//坐标经纬度转换
	double* Trans_Curve_xy(double Xl, double Yn, int Tp, double L0, double H0);
	//计算主点里程
	void Calc_Point_dk(double dk_begin=0, double dk_end=0);
	//计算主点坐标
	void Calc_Point_xy(double dk_begin=0, double dk_end=0);
	//计算任一点里程
	double* Calc_Curve_xy(double dk, double dist=0, double dk_begin=0, double dk_end=0);
	vector<double*> Calc_Curve_xys(double dk_begin, double dk_end, double gap, double dist=0, double dk_begin_break=0, double dk_end_break=0);


	SQXELEMENT GetSqx(double dk);
	double SqxCalc(double dk, SQXELEMENT sqx);
	BOOL IsSqx(double dk, SQXELEMENT sqx);

	JDELEMENTLIST m_vecJDElement;
	SQXELEMENTLIST m_vecSQXElement;

	CString m_strConnect;
	CString	m_strSQL;
	XTPREPORTMSADODB::_ConnectionPtr m_pConnection;
	XTPREPORTMSADODB::_RecordsetPtr m_pRecordset;
};

#endif // ARXRLE_CRUVE_ELEMENT_H
