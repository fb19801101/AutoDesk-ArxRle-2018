// ArxRleCurveElement.h: interface for the ArxRleCurveElement class.
//

#ifndef ARXRLE_CRUVE_ELEMENT_H
#define ARXRLE_CRUVE_ELEMENT_H

typedef struct tagJDELEMENT
{
	CString JD;								 // ������
	double x, y;						     // ��������

	double R1, Ls1, A1;                      // ǰ�������߰뾶,���ȡ�����
	double R2, Ls2, A2;                      // �󻺺����߰뾶,���ȡ�����
	double T1, T2;                           // ǰ�����߳�
	double Rc, Lc;                           // Բ���߰뾶,����
	double L, E, Lz;					     // �����ܳ�����ʸ�ࡢ��ֱ�߳�

	double fwj, pj;	                         // ��λ�ǡ�ƫ��

	double DK, QD, ZD;                       // ������̡����յ����
	double ZH, HY, QZ, YH, HZ;               // �����������

	double QD_x, QD_y, ZD_x, ZD_y;			 // ���յ�����
	double ZH_x,ZH_y,HZ_x,HZ_y;				 // ֱ����ֱ������
	double HY_x,HY_y,YH_x,YH_y;				 // ��ԲԲ��������
	double QZ_x,QZ_y;                        // ��������

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

	//��ȡ�������λ�ڽ�����һ���� 1 ǰֱ��  2 ǰ��������  3 Բ����  4 �󻺺�����  5 ��ֱ��
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

	void InputJDData(CString inputfilename);//�ļ����뺯��
	void InputSQXData(CString inputfilename);//�ļ����뺯��
	void ReadMDBTable(CString mdbFname,CString TabFname);
	void OutputJDResult(CString outputfilename);//�ļ��������
	void WriteMDBTable(CString mdbFname, CString TabFname);
	BOOL Execute(CString strSQL);

	
	//���㷽λ�ǡ�ƫ��
	void Calc_fwj_pj();
	//���㻺�Ͳ�������ʧ�ࡢ�����ܳ�
	void Calc_A_E_L();
	//����HY��YH������
	double* Calc_HY_YH_xy(double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2);
	//����Բ��������һ�������
	double* Calc_Circle_xy(double dk, double dist, double dk_HY, double x_HY, double y_HY, double x_YH, double y_YH, double x_JD, double y_JD, double Rc);
	//����ֱ������һ�������
	double* Calc_Line_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1);
	//���㻺����������һ�������
	double* Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _T1, double _T2, double _Ls1, double _Ls2);
	//���㻺����������һ�������
	double* Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2);
	//���꾭γ��ת��
	double* Trans_Curve_xy(double Xl, double Yn, int Tp, double L0, double H0);
	//�����������
	void Calc_Point_dk(double dk_begin=0, double dk_end=0);
	//������������
	void Calc_Point_xy(double dk_begin=0, double dk_end=0);
	//������һ�����
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
