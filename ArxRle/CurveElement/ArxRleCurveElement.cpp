//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleCurveElement.h"
#include "DbEntity/ArxRleEntityClass.h"


ArxRleCurveElement::ArxRleCurveElement()
{
	m_vecJDElement.clear();
	m_vecSQXElement.clear();
}

ArxRleCurveElement::~ArxRleCurveElement(void)
{
}

void ArxRleCurveElement::InputJDData(CString inputfilename)
{
	if(PathFileExists(inputfilename))
	{
		m_vecJDElement.clear();
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(inputfilename, CFile::modeRead))
		{
			int nPos = 0;
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				strLine.Replace(_T("；"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("，"), _T(";"));
				if(strLine.GetLength() == 0 || strLine.Mid(0,1).Compare(_T("#")) == 0)
					continue;

				CStringArray arrSubStr;
				int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

				if(cnt == 13)
				{
					JDELEMENT jd;
					jd.JD = arrSubStr[0];
					jd.DK = _tstof(arrSubStr[1]);
					jd.x = _tstof(arrSubStr[2]);
					jd.y = _tstof(arrSubStr[3]);
					jd.T1 = _tstof(arrSubStr[4]);
					jd.T2 = _tstof(arrSubStr[5]);
					jd.R1 = _tstof(arrSubStr[6]);
					jd.R2 = _tstof(arrSubStr[7]);
					jd.Rc = _tstof(arrSubStr[8]);
					jd.Ls1 = _tstof(arrSubStr[9]);
					jd.Ls2 = _tstof(arrSubStr[10]);
					jd.Lc = _tstof(arrSubStr[11]);
					jd.Lz = _tstof(arrSubStr[12]);

					m_vecJDElement.push_back(jd);
				}
			}

			file.Close();
		}
	}
}

void ArxRleCurveElement::InputSQXData(CString filePath)
{
	if(PathFileExists(filePath))
	{
		m_vecSQXElement.clear();
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(filePath, CFile::modeRead))
		{
			CString str;
			int nPos = 0;
			while(file.ReadString(str))
			{
				str.Trim();
				if (str.GetLength() == 0 || str.Mid(0, 1).Compare(_T("#")) == 0)
					continue;

				SQXELEMENT sqx;
				if((nPos = str.Find(_T("DK"))) >= 0) sqx.DK = _tstof(str.Mid(nPos+2));
				if((nPos = str.Find(_T("H"))) >= 0) sqx.H = _tstof(str.Mid(nPos+2));
				if((nPos = str.Find(_T("R"))) >= 0) sqx.R = _tstof(str.Mid(nPos+2));
				if((nPos = str.Find(_T("I1"))) >= 0) sqx.I1 = _tstof(str.Mid(nPos+3))/1000;
				if((nPos = str.Find(_T("I2"))) >= 0) sqx.I2 = _tstof(str.Mid(nPos+3))/1000;
				sqx.L = fabs(sqx.R * (sqx.I1 - sqx.I2));
				sqx.T = sqx.L / 2;
				if(sqx.R != 0) sqx.E = sqx.T * sqx.T / 2 / sqx.R;

				m_vecSQXElement.push_back(sqx);
			}

			file.Close();
		}
	}
}

void ArxRleCurveElement::ReadMDBTable(CString mdbFname,CString TabFname)
{
	CoInitialize(NULL);

	m_pConnection.CreateInstance(__uuidof(XTPREPORTMSADODB::Connection));
	m_pRecordset.CreateInstance(__uuidof(XTPREPORTMSADODB::Recordset));

	m_strConnect.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s",mdbFname);
	//m_strSQL ="select * from 交点数据";
	m_strSQL.Format(L"select * from %s",TabFname);

	try
	{	
		m_pConnection->Open(_bstr_t(m_strConnect),"","",XTPREPORTMSADODB::adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}

	try
	{
		m_pRecordset->Open(_bstr_t(m_strSQL),
			m_pConnection.GetInterfacePtr(),
			XTPREPORTMSADODB::adOpenStatic,
			XTPREPORTMSADODB::adLockOptimistic,
			XTPREPORTMSADODB::adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());                     
	}

	try
	{
		for (int i=0; i<m_pRecordset->GetRecordCount(); i++)
		{				
			_variant_t v_JD = m_pRecordset->GetCollect("交点编号");
			_variant_t v_DK = m_pRecordset->GetCollect("交点里程");
			_variant_t v_x = m_pRecordset->GetCollect("交点坐标E/X");
			_variant_t v_y = m_pRecordset->GetCollect("交点坐标N/Y");
			_variant_t v_T1 = m_pRecordset->GetCollect("前切线长");
			_variant_t v_T2 = m_pRecordset->GetCollect("后切线长");
			_variant_t v_R1 = m_pRecordset->GetCollect("前缓和曲线半径");
			_variant_t v_R2 = m_pRecordset->GetCollect("后缓和曲线半径");
			_variant_t v_Rc = m_pRecordset->GetCollect("圆曲线半径");
			_variant_t v_Ls1 = m_pRecordset->GetCollect("前缓和曲线长");
			_variant_t v_Ls2 = m_pRecordset->GetCollect("后缓和曲线长");
			_variant_t v_Lc = m_pRecordset->GetCollect("圆曲线长");
			_variant_t v_Lz = m_pRecordset->GetCollect("夹直线长");
			_variant_t v_E = m_pRecordset->GetCollect("外失距");
			_variant_t v_pj = m_pRecordset->GetCollect("偏角");
			_variant_t v_fwj = m_pRecordset->GetCollect("方位角");

			JDELEMENT jd;
			jd.JD = _bstr_t(v_JD).GetBSTR();
			jd.DK = atof(_bstr_t(v_DK));
			jd.x = atof(_bstr_t(v_x));
			jd.y = atof(_bstr_t(v_y));
			jd.T1 = atof(_bstr_t(v_T1));
			jd.T2 = atof(_bstr_t(v_T2));
			jd.R1 = atof(_bstr_t(v_R1));
			jd.R2 = atof(_bstr_t(v_R2));
			jd.Rc = atof(_bstr_t(v_Rc));
			jd.Ls1 = atof(_bstr_t(v_Ls1));
			jd.Ls1 = atof(_bstr_t(v_Ls2));
			jd.Lc = atof(_bstr_t(v_Lc));
			jd.Lz = atof(_bstr_t(v_Lz));
			jd.E = atof(_bstr_t(v_E));
			jd.pj = atof(_bstr_t(v_pj));
			jd.fwj = atof(_bstr_t(v_fwj));
	
			m_vecJDElement.push_back(jd);

			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	m_pRecordset->Close();
	m_pConnection->Close();
}

void ArxRleCurveElement::OutputJDResult(CString outputfilename)
{
	setlocale(LC_ALL, "");

	CStdioFile file;
	if (file.Open(outputfilename, CFile::modeCreate | CFile::modeReadWrite))
	{
		file.Seek(CFile::begin, 0);
		CString strTemp;
		int nJDNum = m_vecJDElement.size();
		file.WriteString(L"交点编号,交点里程,交点坐标X,交点坐标Y, \
				前切线长,后切线长,前缓和曲线半径,后缓和曲线半径,圆曲线半径,前缓和曲线参数,后缓和曲线参数,前缓和曲线长,后缓和曲线长,圆曲线长,夹直线长, \
				曲线总长,外失距,偏角,方位角, \
				起点里程,直缓里程,缓圆里程,曲中里程,圆缓里程,缓直里程,终点里程, \
				起点坐标X,起点坐标Y,直缓坐标X,直缓坐标Y,缓圆坐标X,缓圆坐标Y,曲中坐标X,曲中坐标Y,圆缓坐标X,圆缓坐标Y,缓直坐标X,缓直坐标Y,终点坐标X,终点坐标Y\n");
		for (int i = 0; i<nJDNum; i++)
		{
			JDELEMENT jd = m_vecJDElement[i];
			strTemp.Format(_T("%s,%.3f,%.3f,%.3f, \
				%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f, \
				%.3f,%.3f,%s,%s, \
				%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f, \
				%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n"),
				jd.JD, jd.DK, jd.x, jd.y,
				jd.T1, jd.T2, jd.R1, jd.R2, jd.Rc, jd.A1, jd.A2, jd.Ls1, jd.Ls2, jd.Lc, jd.Lz, 
				jd.L, jd.E, FormatAngle(jd.pj), FormatAngle(jd.fwj),
				jd.QD, jd.ZH, jd.HY, jd.QZ, jd.YH, jd.HZ, jd.ZD,
				jd.QD_x, jd.QD_y, jd.ZH_x, jd.ZH_y, jd.HY_x, jd.HY_y, jd.QZ_x, jd.QZ_y, jd.YH_x, jd.YH_y, jd.HZ_x, jd.HZ_y, jd.ZD_x, jd.ZD_y);
			file.WriteString(strTemp);
		}

		file.Close();
	}
}

void ArxRleCurveElement::WriteMDBTable(CString mdbFname, CString TabFname)
{
	//// 	AfxOleInit();//VS2002和VC6.0用这个函数
	CoInitialize(NULL);//VS2005用这个函数
	m_pConnection.CreateInstance(__uuidof(XTPREPORTMSADODB::Connection));
	m_pRecordset.CreateInstance(__uuidof(XTPREPORTMSADODB::Recordset));
	////m_strConnect.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s",mdbFname);
	m_strConnect = L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + mdbFname;

	try
	{
		m_pConnection->Open(_bstr_t(m_strConnect), "", "", XTPREPORTMSADODB::adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}


	//// 	if(!FindTable(TabFname))//表不存在
	//// 	{
	CString m_strSQL;
	m_strSQL = "create table ";
	m_strSQL += TabFname;
	m_strSQL += "(";
	m_strSQL += "ID integer identity,转角 VARCHAR ,曲线长 VARCHAR, 切线长 VARCHAR, 直缓点里程 VARCHAR, 缓圆点里程 VARCHAR, 曲中点里程 VARCHAR, 圆缓点里程 VARCHAR, 缓直点里程 VARCHAR "; //建立新表       
																																						//,缓圆点x坐标 VARCHAR, 缓圆点y坐标 VARCHAR,圆缓点x坐标 VARCHAR, 圆缓点y坐标 VARCHAR,缓直点x坐标 VARCHAR, 缓直点y坐标 VARCHAR
	m_strSQL += ")";
	Execute(m_strSQL);
	////}
	m_strSQL.Format(L"delete from %s", TabFname);//删除全部
	Execute(m_strSQL);

	m_strSQL = L"select * from " + TabFname;
	try
	{
		m_pRecordset->Open(_bstr_t(m_strSQL),
			m_pConnection.GetInterfacePtr(),
			XTPREPORTMSADODB::adOpenStatic,
			XTPREPORTMSADODB::adLockOptimistic,
			XTPREPORTMSADODB::adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	try
	{
		CString strText;
		_variant_t str;
		int nJDNum = m_vecJDElement.size();
		for (int i = 0; i<nJDNum - 2; i++)
		{
			m_pRecordset->AddNew();
			strText.Format(L"%d", i+1);
			str = strText;
			m_pRecordset->PutCollect(L"ID", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].pj);
			str = strText;
			m_pRecordset->PutCollect(L"转角", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].L);
			str = strText;
			m_pRecordset->PutCollect(L"曲线长", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].T1);
			str = strText;
			m_pRecordset->PutCollect(L"切线长", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].DK);
			str = strText;
			m_pRecordset->PutCollect(L"交点里程", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].ZH);
			str = strText;
			m_pRecordset->PutCollect(L"直缓点里程", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].HY);
			str = strText;
			m_pRecordset->PutCollect(L"缓圆点里程", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].QZ);
			str = strText;
			m_pRecordset->PutCollect(L"曲中点里程", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].YH);
			str = strText;
			m_pRecordset->PutCollect(L"圆缓点里程", str);

			strText.Format(L"%.3lf", m_vecJDElement[i+1].HZ);
			str = strText;
			m_pRecordset->PutCollect(L"缓直点里程", str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].HY_x);
			str = strText;
			m_pRecordset->PutCollect(L"缓圆点x坐标",str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].HY_y);
			str = strText;
			m_pRecordset->PutCollect(L"缓圆点y坐标",str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].YH_x);
			str = strText;
			m_pRecordset->PutCollect(L"圆缓点x坐标",str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].YH_y);
			str = strText;
			m_pRecordset->PutCollect(L"圆缓点y坐标",str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].HZ_x);
			str = strText;
			m_pRecordset->PutCollect(L"缓直点x坐标",str);

			strText.Format(L"%.3lf",m_vecJDElement[i+1].HZ_y);
			str = strText;
			m_pRecordset->PutCollect(L"缓直点y坐标",str);

		}
		m_pRecordset->Update();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	m_pRecordset->Close();
	m_pConnection->Close();
}

BOOL ArxRleCurveElement::Execute(CString m_strSQL)
{
	_variant_t RecordsAffected;
	try
	{
		if (m_pConnection != NULL && m_pConnection->State == XTPREPORTMSADODB::adStateOpen)
		{
			m_pConnection->Execute(_bstr_t(m_strSQL), &RecordsAffected, XTPREPORTMSADODB::adCmdText);
		}
	}
	catch (_com_error e)
	{
		// 		AfxMessageBox(e.Description());
	}
	return FALSE;
}

//计算方位角、偏角
void ArxRleCurveElement::Calc_fwj_pj()
{
	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum - 1; i++)
	{
		JDELEMENT& jd = m_vecJDElement[i];
		//两点之间的 X,Y 坐标的差值
		double dx = m_vecJDElement[i + 1].x - jd.x;
		double dy = m_vecJDElement[i + 1].y - jd.y;

		if (dx >= 0.0 && dy > 0.0)
			jd.fwj = atan(fabs(dx) / fabs(dy));
		else if (dx >= 0.0 && dy < 0.0)
			jd.fwj = PI - atan(fabs(dx) / fabs(dy));
		else if (dx < 0.0 && dy < 0.0)
			jd.fwj = PI + atan(fabs(dx) / fabs(dy));
		else if (dx <0.0 && dy >0.0)
			jd.fwj = 2.0*PI - atan(fabs(dx) / fabs(dy));
		else if (dx > 0.0 && dy == 0.0)
			jd.fwj = PI / 2.0;
		else if (dx < 0.0 && dy == 0.0)
			jd.fwj = PI*3.0 / 2.0;
	}

	for (int i = 0; i < nJDNum - 1; i++)
	{
		JDELEMENT& jd = m_vecJDElement[i+1];
		//计算交点偏角pj
		jd.pj = jd.fwj - m_vecJDElement[i].fwj;
		if (jd.pj > PI)//转角范围-180到+180
			jd.pj -= 2 * PI;
		else if (jd.pj < -PI)
			jd.pj += 2 * PI;
	}
}

//计算缓和参数、外失距
void ArxRleCurveElement::Calc_A_E_L()
{
	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum; i++)
	{
		JDELEMENT& jd = m_vecJDElement[i];
		jd.A1 = sqrt(jd.Rc * jd.Ls1);
		jd.A2 = sqrt(jd.Rc * jd.Ls2);
		jd.L = jd.Ls1 + jd.Lc + jd.Ls2;
		jd.E = sqrt(pow(jd.x - jd.QZ_x, 2) + pow(jd.y-jd.QZ_y,2));
	}
}

//计算HY、YH点坐标
double* ArxRleCurveElement::Calc_HY_YH_xy(double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2)
{
	double fwj1 = atan2((_y - _y1), (_x - _x1));//第一方位角  atan2((_y - _y1), (_x - _x1)) * 180 / PI;
	if (fwj1 < 0) {
		fwj1 = 2.0*PI + fwj1;  //360 + fwj1;
	}
	double fwj2 = atan2((_y2 - _y), (_x2 - _x));//第二方位角  atan2((_y2 - _y), (_x2 - _x)) * 180 / PI;
	if (fwj2 < 0) {
		fwj2 = 2.0*PI + fwj2;  //360 + fwj2;
	}
	double pj = fwj1 - fwj2;//转角，左转为正，右转为负
	double ZH = _dk - _T1;
	double HZ = ZH + _Ls1 + _Ls2 + _Lc;

	double x1_1, y1_1, x1, y1, x1_2, y1_2;
	if (_Ls1 != 0) {
		double p1 = _Ls1 - pow(_Ls1, 5) / (40 * _Rc * _Rc * _Ls1 * _Ls1) + pow(_Ls1, 9) / (3456 * pow(_Rc, 4)*pow(_Ls1, 4));
		double q1 = pow(_Ls1, 3) / (6 * _Rc * _Ls1) - pow(_Ls1, 7) / (336 * pow(_Rc, 3) * pow(_Ls1, 3));
		if (pj < 0) {
			q1 = -q1;
		}
		double _p1 = sqrt(p1 * p1 + q1 * q1);
		double _w1 = fwj1 - atan2(q1, p1);  //fwj1 - atan2(q1, p1) * 180 / PI;
		x1_1 = _x + _T1 * cos(fwj1 - PI);  //_x + _T1 * cos(AngletoRadians(fwj1 - 180));
		y1_1 = _y + _T1 * sin(fwj1 - PI);  //_y + _T1 * sin(AngletoRadians(fwj1 - 180));
		x1_2 = _p1 * cos(_w1) + x1_1;  //_p1 * cos(AngletoRadians(_w1)) + x1_1;
		y1_2 = _p1 * sin(_w1) + y1_1;  //_p1 * sin(AngletoRadians(_w1)) + y1_1;

	}
	else {
		x1_1 = _x + _T1 * cos(fwj1 - PI);  //_x + _T1 * cos(AngletoRadians(fwj1 - 180));
		y1_1 = _y + _T1 * sin(fwj1 - PI);  //_y + _T1 * sin(AngletoRadians(fwj1 - 180));
		x1_2 = x1_1;
		y1_2 = y1_1;
	}

	double x2_1, y2_1, x2, y2, x2_2, y2_2;
	if (_Ls2 != 0) {
		double p2 = _Ls2 - pow(_Ls2, 5) / (40 * _Rc*_Rc*_Ls2*_Ls2);
		double q2 = pow(_Ls2, 3) / (6 * _Rc*_Ls2) - pow(_Ls2, 7) / (336 * pow(_Rc, 3)*pow(_Ls2, 3));
		q2 = -q2;
		if (pj < 0) {
			q2 = -q2;
		}
		double _p2 = sqrt(p2*p2 + q2*q2);
		double _w2 = fwj2 - atan2(q2, p2);  //fwj2 - atan2(q2, p2) * 180 / PI;
		x2_1 = _x + _T2*cos(fwj2);  //_x + _T2*cos(AngletoRadians(fwj2));
		y2_1 = _y + _T2*sin(fwj2);  //_y + _T2*sin(AngletoRadians(fwj2));
		x2_2 = _p2*cos(_w2 - PI) + x2_1;  //_p2*cos(AngletoRadians(_w2 - 180)) + x2_1;
		y2_2 = _p2*sin(_w2 - PI) + y2_1;  //_p2*sin(AngletoRadians(_w2 - 180)) + y2_1;
	}
	else {
		x2_1 = _x + _T2*cos(fwj2);  //_x + _T2*cos(AngletoRadians(fwj2));
		y2_1 = _y + _T2*sin(fwj2);  //_y + _T2*sin(AngletoRadians(fwj2));
		x2_2 = x2_1;
		y2_2 = y2_1;
	}

	double Ls1_1 = (_Rc*_Ls1) / (_R1 - _Rc);//交点下第一段卵形曲线剩余长度
	double Ls2_1 = (_Rc*_Ls2) / (_R2 - _Rc);//交点下第二段卵形曲线剩余长度
	double Ls1_2 = Ls1_1 + _Ls1;//交点下第一段卵形曲线还原后虚总长度
	double Ls2_2 = Ls2_1 + _Ls2;//交点下第二段卵形曲线还原后虚总长度
	double QD = ZH - Ls1_1;//交点下第一段卵形曲线还原后虚拟起点里程
	double ZD = HZ + Ls2_1;//交点下第二段卵形曲线还原后虚拟终点里程
	double NN1 = Ls1_1 - pow(Ls1_1, 5) / (40 * _Rc*_Rc*Ls1_2*Ls1_2) + pow(Ls1_1, 9) / (3456 * pow(_Rc, 4)*pow(Ls1_2, 4));//第一卵形曲线起点投射至上虚拟轴线Y值
	double SS1 = pow(Ls1_1, 3) / (6 * _Rc*Ls1_2) - pow(Ls1_1, 7) / (336 * pow(_Rc, 3)*pow(Ls1_2, 3));//第一卵形曲线起点投射至上虚拟轴线X值
	double NN2 = Ls2_1 - pow(Ls2_1, 5) / (40 * _Rc*_Rc*Ls2_2*Ls2_2) + pow(Ls2_1, 9) / (3456 * pow(_Rc, 4)*pow(Ls2_2, 4));//第二卵形曲线终点投射至上虚拟轴线Y值
	double SS2 = pow(Ls2_1, 3) / (6 * _Rc*Ls2_2) - pow(Ls2_1, 7) / (336 * pow(_Rc, 3)*pow(Ls2_2, 3));//第二卵形曲线终点投射至上虚拟轴线X值
	double x_Ls1 = _x + _T1*cos(fwj1 - PI);  //_x + _T1*cos(AngletoRadians(fwj1 - 180));
	double y_Ls1 = _y + _T1*sin(fwj1 - PI);//交点下第一段卵形曲线起点坐标  _y + _T1*sin(AngletoRadians(fwj1 - 180));
	double x_Ls2 = _x + _T2*cos(fwj2);  //_x + _T2*cos(AngletoRadians(fwj2));
	double y_Ls2 = _y + _T2*sin(fwj2);//交点下第二段卵形曲线终点坐标  _y + _T2*sin(AngletoRadians(fwj2));

	double p_Ls1 = sqrt(NN1*NN1 + SS1*SS1);//第一段卵形曲线起点至虚拟起点直线距离
	double w_Ls1 = pow(Ls1_1, 2) / (2 * _Rc*Ls1_2);//第一段卵形曲线起点偏角  (pow(Ls1_1, 2) / (2 * _Rc*Ls1_2))*(180 / PI);
	double _p_Ls1 = atan2(SS1, NN1);  //atan2(SS1, NN1) * 180 / PI;
	double _w_Ls1 = fwj1 + w_Ls1 - _p_Ls1 - PI;//第一卵形曲线起点至虚拟起点方位角  fwj1 + w_Ls1 - _p_Ls1 - 180;

	double p_Ls2 = sqrt(NN2*NN2 + SS2*SS2);
	double w_Ls2 = pow(Ls2_1, 2) / (2 * _Rc*Ls2_2);//第二段卵形曲线终点偏角  (pow(Ls2_1, 2) / (2 * _Rc*Ls2_2))*(180 / PI);
	double _p_Ls2 = atan2(SS2, NN2);  //atan2(SS2, NN2) * 180 / PI;
	double _w_Ls2 = fwj2 - w_Ls2 + _p_Ls2;

	if (pj < 0) {
		_w_Ls1 = fwj1 - w_Ls1 + _p_Ls1 - PI; //右偏时第一卵形曲线起点至虚拟起点方位角  fwj1 - w_Ls1 + _p_Ls1 - 180;
		_w_Ls2 = fwj2 + w_Ls2 - _p_Ls2;//右偏时虚拟终点至第二卵形曲线终点方位角
	}

	double _x_Ls1 = x_Ls1 + p_Ls1*cos(_w_Ls1);//交点下第一段卵形曲线还原后虚拟起点x坐标  x_Ls1 + p_Ls1*cos(AngletoRadians(_w_Ls1));
	double _y_Ls1 = y_Ls1 + p_Ls1*sin(_w_Ls1);//交点下第一段卵形曲线还原后虚拟起点y坐标  y_Ls1 + p_Ls1*sin(AngletoRadians(_w_Ls1));
	double _fwj_Ls1 = fwj1 + w_Ls1;//交点下第一段卵形曲线还原后虚拟轴线方位角
	double _x_Ls2 = x_Ls2 + p_Ls2*cos(_w_Ls2);//交点下第二段卵形曲线还原后虚拟起点x坐标  x_Ls2 + p_Ls2*cos(AngletoRadians(_w_Ls2));
	double _y_Ls2 = y_Ls2 + p_Ls2*sin(_w_Ls2);//交点下第二段卵形曲线还原后虚拟起点y坐标  y_Ls2 + p_Ls2*sin(AngletoRadians(_w_Ls2));
	double _fwj_Ls2 = fwj2 - w_Ls2;//交点下第二段卵形曲线还原后虚拟轴线方位角

	if (pj < 0) {
		_fwj_Ls1 = fwj1 - w_Ls1;
		_fwj_Ls2 = fwj2 + w_Ls2;
	}
	double p1 = Ls1_2 - pow(Ls1_2, 3) / (40 * _Rc*_Rc) + pow(Ls1_2, 5) / (3456 * pow(_Rc, 4));
	double q1 = pow(Ls1_2, 2) / (6 * _Rc) - pow(Ls1_2, 4) / (336 * pow(_Rc, 3));
	double w1 = pow(Ls1_2, 2) / (2 * _Rc*Ls1_2);  //(pow(Ls1_2, 2) / (2 * _Rc*Ls1_2))*(180 / PI);
	double fwj_Ls1 = _fwj_Ls1 - w1 - PI/2.0;  //_fwj_Ls1 - w1 - 90;

	double p2 = Ls2_2 - pow(Ls2_2, 3) / (40 * _Rc*_Rc) + pow(Ls2_2, 5) / (3456 * pow(_Rc, 4));
	double q2 = pow(Ls2_2, 2) / (6 * _Rc) - pow(Ls2_2, 4) / (336 * pow(_Rc, 3));
	double w2 = pow(Ls2_2, 2) / (2 * _Rc*Ls2_2);  //(pow(Ls2_2, 2) / (2 * _Rc*Ls2_2))*(180 / PI);
	double fwj_Ls2 = _fwj_Ls2 + w2 - PI / 2.0;  //_fwj_Ls2 + w2 - 90;

	if (pj < 0) {
		fwj_Ls1 = _fwj_Ls1 + w1 - PI / 2.0;  //_fwj_Ls1 + w1 - 90;
		fwj_Ls2 = _fwj_Ls2 - w2 - PI / 2.0;  //_fwj_Ls2 - w2 - 90;
	}

	double _p1 = sqrt(p1*p1 + q1*q1);//第一卵形曲线待求点至虚拟原点距离
	double _w1 = _fwj_Ls1 - atan2(q1, p1);//第一卵形曲线待求点至虚拟原点方位角  _fwj_Ls1 - atan2(q1, p1) * 180 / PI;
	double _p2 = sqrt(p2*p2 + q2*q2);
	double _w2 = _fwj_Ls2 - PI + atan2(q2, p2);  //_fwj_Ls2 - 180 + atan2(q2, p2) * 180 / PI;

	if (pj < 0) {
		_w1 = _fwj_Ls1 + atan2(q1, p1);  //_fwj_Ls1 + atan2(q1, p1) * 180 / PI;
		_w2 = _fwj_Ls2 - PI - atan2(q2, p2);  //_fwj_Ls2 - 180 - atan2(q2, p2) * 180 / PI;
	}

	double _x1_2 = _p1*cos(_w1) + _x_Ls1;  //_p1*cos(AngletoRadians(_w1)) + _x_Ls1;
	double _y1_2 = _p1*sin(_w1) + _y_Ls1; // 第一段卵形曲线待求点中心坐标  _p1*sin(AngletoRadians(_w1)) + _y_Ls1;

	double _x2_2 = _p2*cos(_w2) + _x_Ls2;  //_p2*cos(AngletoRadians(_w2)) + _x_Ls2;
	double _y2_2 = _p2*sin(_w2) + _y_Ls2;//第二段卵形曲线待求点中心坐标  _p2*sin(AngletoRadians(_w2)) + _y_Ls2;

	if (_R1 == 0) {
		x1 = x1_2;
		y1 = y1_2;
	} else {
		x1 = _x1_2;
		y1 = _y1_2;
	}
	if (_R2 == 0) {
		x2 = x2_2;
		y2 = y2_2;
	} else {
		x2 = _x2_2;
		y2 = _y2_2;
	}

	double* ret = new double[4];
	ret[0] = x1;
	ret[1] = y1;
	ret[2] = x2;
	ret[3] = y2;
	return ret;
}

//计算圆曲线上任一点的坐标
double* ArxRleCurveElement::Calc_Circle_xy(double dk, double dist, double HY, double x_HY, double y_HY, double x_YH, double y_YH, double x_JD, double y_JD, double Rc)
{
	double m = (x_YH * x_YH + y_YH * y_YH - x_HY * x_HY - y_HY * y_HY) / (2 * (x_YH - x_HY));
	double n = ((y_YH - y_HY) / (x_YH - x_HY));
	double c = (Rc * Rc - m * m - x_HY * x_HY + 2 * m * x_HY - y_HY * y_HY) * (-1);
	double a = n * n + 1;
	double b = 2 * (n * x_HY - y_HY - m * n);
	double y1 = ((-1 * b) + sqrt(b * b - 4 * a * c)) / (2 * a);
	double y2 = ((-1 * b) - sqrt(b * b - 4 * a * c)) / (2 * a);
	double x1 = m - y1 * n;
	double x2 = m - y2 * n;
	double p1 = sqrt((x1 - x_JD) * (x1 - x_JD) + (y1 - y_JD) * (y1 - y_JD));
	double _x, _y, x, y; //_x,_y 为圆心坐标，x,y 为待求点坐标
	if (p1 > Rc) {
		_x = x1;
		_y = y1;
	}
	else {
		_x = x2;
		_y = y2;
	}

	double mm = dk - HY;
	double w1 = mm / Rc; //(mm * 360) / (2 * PI * Rc);
	double _w1 = atan2((y_HY - _y), (x_HY - _x)); //atan2((y_HY - _y), (x_HY - _x)) * 180 / PI
	if (_w1 < 0) {
		_w1 = _w1 + 2.0*PI; //_w1 + 360
	}

	double p2 = Rc + dist;
	double _w2 = atan2((y_JD - y_HY), (x_JD - x_HY)); //atan2((y_JD - y_HY), (x_JD - x_HY)) * 180 / PI;
	if (_w2 < 0) {
		_w2 = _w2 + 2.0*PI; //_w2 + 360;

	}

	double _w3 = atan2((y_YH - y_JD), (x_YH - x_JD)); //atan2((y_YH - y_JD), (x_YH - x_JD)) * 180 / PI;
	if (_w3 < 0) {
		_w3 = _w3 + 2.0*PI; //_w3 + 360;

	}
	if (_w2 > _w3) {
		w1 = -w1;
		p2 = Rc - dist;
		//System.out.println("顺时针，左偏");
	}
	else {
		//System.out.println("逆时针，右偏");
	}

	double w3 = atan2((y_JD - _y), (x_JD - _x));//交点到圆心方位角  atan2((y_JD - _y), (x_JD - _x)) * 180 / PI;
	if (w3 < 0) {
		w3 = w3 + 2.0*PI; //w3 + 360;
	}

	double w2 = _w1 + w1;

	x = _x + p2*cos(w2);  //_x + p2*cos(AngletoRadians(w2));
	y = _y + p2*sin(w2);  //_y + p2*sin(AngletoRadians(w2));

	double* ret = new double[2];
	ret[0] = x;
	ret[1] = y;
	return ret;
}

//计算直线上任一点的坐标
double* ArxRleCurveElement::Calc_Line_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1)
{
	double fwj = atan2((_y1 - _y), (_x1 - _x));  //atan2((_y1 - _y), (_x1 - _x)) * 180 / PI;
	double p = fabs(_dk - dk);
	double x1 = _x + p*cos(fwj);  //_x + p*cos(AngletoRadians(fwj));
	double y1 = _y + p*sin(fwj);  //_y + p*sin(AngletoRadians(fwj));
	double x = x1 + dist*cos(fwj + PI/2.0);  //x1 + dist*cos(AngletoRadians(fwj + 90));
	double y = y1 + dist*sin(fwj + PI/2.0);  //y1 + dist*sin(AngletoRadians(fwj + 90));

	double* ret = new double[2];
	ret[0] = x;
	ret[1] = y;
	return ret;
}

//计算缓和曲线上任一点的坐标
double* ArxRleCurveElement::Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _T1, double _T2, double _Ls1, double _Ls2)
{
	double fwj1 = atan2((_y - _y1), (_x - _x1));  //atan2((_y - _y1), (_x - _x1)) * 180 / PI;
	if (fwj1 < 0) {
		fwj1 = 2.0*PI + fwj1;  //360 + fwj1;
	}
	double fwj2 = atan2((_y2 - _y), (_x2 - _x));  //atan2((_y2 - _y), (_x2 - _x)) * 180 / PI;
	if (fwj2 < 0) {
		fwj2 = 2.0*PI + fwj2;  //360 + fwj2;
	}
	double pj = fwj1 - fwj2;//转角，左转为正，右转为负
	double ZH = _dk - _T1;
	double HZ = ZH + _Ls1 + _Ls2 + _Lc;

	double Ls1 = dk - ZH;
	double Ls2 = HZ - dk;
	double p1 = Ls1 - pow(Ls1, 5) / (40 * _Rc*_Rc*_Ls1*_Ls1) + pow(Ls1, 9) / (3456 * pow(_Rc, 4)*pow(Ls1, 4));
	double p2 = Ls2 - pow(Ls2, 5) / (40 * _Rc*_Rc*_Ls2*_Ls2) + pow(Ls2, 9) / (3456 * pow(_Rc, 4)*pow(Ls2, 4));
	double q1 = pow(Ls1, 3) / (6 * _Rc*_Ls1) - pow(Ls1, 7) / (336 * pow(_Rc, 3)*pow(_Ls1, 3));
	double q2 = pow(Ls2, 3) / (6 * _Rc*_Ls2) - pow(Ls2, 7) / (336 * pow(_Rc, 3)*pow(_Ls2, 3));

	double w1 = pow(Ls1, 2) / (2 * _Rc*_Ls1);  //(pow(Ls1, 2) / (2 * _Rc*_Ls1))*(180 / PI);
	double w2 = pow(Ls2, 2) / (2 * _Rc*_Ls2);  //(pow(Ls2, 2) / (2 * _Rc*_Ls2))*(180 / PI);

	double _fwj1 = fwj1 - w1 - PI/2.0;  //fwj1 - w1 - 90;
	double _fwj2 = fwj2 - PI / 2.0 + w2;  //fwj2 - 90 + w2;
	if (pj < 0) {
		q1 = -q1;
		q2 = -q2;
		//dist = -dist;
		_fwj2 = fwj2 - PI / 2.0 - w2;  //fwj2 - 90 - w2;
		_fwj1 = fwj1 + w1 - PI / 2.0;  //fwj1 + w1 - 90;
	}
	double _p1 = sqrt(p1*p1 + q1*q1);
	double _p2 = sqrt(p2*p2 + q2*q2);

	double x_Ls1 = _x + _T1*cos(fwj1 - PI);  //_x + _T1*cos(AngletoRadians(fwj1 - 180));
	double y_Ls1 = _y + _T1*sin(fwj1 - PI);  //_y + _T1*sin(AngletoRadians(fwj1 - 180));

	double x_Ls2 = _x + _T2*cos(fwj2);  //_x + _T2*cos(AngletoRadians(fwj2));
	double y_Ls2 = _y + _T2*sin(fwj2);  //_y + _T2*sin(AngletoRadians(fwj2));

	double w_Ls1 = fwj1 - atan2(q1, p1);  //fwj1 - atan2(q1, p1) * 180 / PI;
	double _x_Ls1 = _p1*cos(w_Ls1) + x_Ls1;  //_p1*cos(AngletoRadians(w_Ls1)) + x_Ls1;
	double _y_Ls1 = _p1*sin(w_Ls1) + y_Ls1;  //_p1*sin(AngletoRadians(w_Ls1)) + y_Ls1;

	double w_Ls2 = fwj2 - PI + atan2(q2, p2);  //fwj2 - 180 + atan2(q2, p2) * 180 / PI;
	double _x_Ls2 = _p2*cos(w_Ls2) + x_Ls2;  //_p2*cos(AngletoRadians(w_Ls2)) + x_Ls2;
	double _y_Ls2 = _p2*sin(w_Ls2) + y_Ls2;  //_p2*sin(AngletoRadians(w_Ls2)) + y_Ls2;

	double x1, y1, x2, y2, x, y;
	x1 = _x_Ls1 + dist*cos(_fwj1);  //_x_Ls1 + dist*cos(AngletoRadians(_fwj1));
	y1 = _y_Ls1 + dist*sin(_fwj1);  //_y_Ls1 + dist*sin(AngletoRadians(_fwj1));

	x2 = _x_Ls2 + dist*cos(_fwj2);  //_x_Ls2 + dist*cos(AngletoRadians(_fwj2));
	y2 = _y_Ls2 + dist*sin(_fwj2);  //_y_Ls2 + dist*sin(AngletoRadians(_fwj2));

	if (Ls1 < _Ls1 + 0.05) {
		x = x1;
		y = y1;
	}
	else {
		x = x2;
		y = y2;
	}

	double* ret = new double[2];
	ret[0] = x;
	ret[1] = y;
	return ret;
}

//计算缓和曲线上任一点的坐标
double* ArxRleCurveElement::Calc_Eases_xy(double dk, double dist, double _dk, double _x, double _y, double _x1, double _y1, double _x2, double _y2, double _Rc, double _Lc, double _R1, double _R2, double _T1, double _T2, double _Ls1, double _Ls2)
{
	double Ls1_1 = (_Rc*_Ls1) / (_R1 - _Rc);//交点下第一段卵形曲线剩余长度
	double Ls2_1 = (_Rc*_Ls2) / (_R2 - _Rc);//交点下第二段卵形曲线剩余长度
	double Ls1 = Ls1_1 + _Ls1;//交点下第一段卵形曲线还原后虚总长度
	double Ls2 = Ls2_1 + _Ls2;//交点下第二段卵形曲线还原后虚总长度

	double fwj1 = atan2((_y - _y1), (_x - _x1));//第一方位角  atan2((_y - _y1), (_x - _x1)) * 180 / PI;
	if (fwj1 < 0) {
		fwj1 = 2.0*PI + fwj1;  //360 + fwj1;
	}
	double fwj2 = atan2((_y2 - _y), (_x2 - _x));//第二方位角  atan2((_y2 - _y), (_x2 - _x)) * 180 / PI;
	if (fwj2 < 0) {
		fwj2 = 2.0*PI + fwj2;  //360 + fwj2;
	}
	double pj = fwj1 - fwj2;//转角，左转为正，右转为负
	double ZH = _dk - _T1;//卵形曲线起点里程
	double HZ = ZH + _Ls1 + _Ls2 + _Lc;//卵形曲线终点里程

	double QD = ZH - Ls1_1;//交点下第一段卵形曲线还原后虚拟起点里程
	double ZD = HZ + Ls2_1;//交点下第二段卵形曲线还原后虚拟终点里程

	double NN1 = Ls1_1 - pow(Ls1_1, 5) / (40 * _Rc*_Rc*Ls1*Ls1) + pow(Ls1_1, 9) / (3456 * pow(_Rc, 4)*pow(Ls1, 4));//第一卵形曲线起点投射至上虚拟轴线Y值
	double SS1 = pow(Ls1_1, 3) / (6 * _Rc*Ls1) - pow(Ls1_1, 7) / (336 * pow(_Rc, 3)*pow(Ls1, 3));//第一卵形曲线起点投射至上虚拟轴线X值
	double NN2 = Ls2_1 - pow(Ls2_1, 5) / (40 * _Rc*_Rc*Ls2*Ls2) + pow(Ls2_1, 9) / (3456 * pow(_Rc, 4)*pow(Ls2, 4));//第二卵形曲线终点投射至上虚拟轴线Y值
	double SS2 = pow(Ls2_1, 3) / (6 * _Rc*Ls2) - pow(Ls2_1, 7) / (336 * pow(_Rc, 3)*pow(Ls2, 3));//第二卵形曲线终点投射至上虚拟轴线X值

	double x_Ls1 = _x + _T1*cos(fwj1 - PI);  //_x + _T1*cos(AngletoRadians(fwj1 - 180));
	double y_Ls1 = _y + _T1*sin(fwj1 - PI);//交点下第一段卵形曲线起点坐标  _y + _T1*sin(AngletoRadians(fwj1 - 180));
	double x_Ls2 = _x + _T2*cos(fwj2);  //_x + _T2*cos(AngletoRadians(fwj2));
	double y_Ls2 = _y + _T2*sin(fwj2);//交点下第二段卵形曲线终点坐标  _y + _T2*sin(AngletoRadians(fwj2));

	double p_Ls1 = sqrt(NN1*NN1 + SS1*SS1);//第一段卵形曲线起点至虚拟起点直线距离
	double w_Ls1_1 = pow(Ls1_1, 2) / (2 * _Rc*Ls1);//第一段卵形曲线起点偏角  (pow(Ls1_1, 2) / (2 * _Rc*Ls1))*(180 / PI);
	double w_Ls1_2 = atan2(SS1, NN1);  //atan2(SS1, NN1) * 180 / PI; 
	double w_Ls1_3 = fwj1 + w_Ls1_1 - w_Ls1_2 - PI;//第一卵形曲线起点至虚拟起点方位角  fwj1 + w_Ls1_1 - w_Ls1_2 - 180;

	double p_Ls2 = sqrt(NN2*NN2 + SS2*SS2);
	double w_Ls2_1 = pow(Ls2_1, 2) / (2 * _Rc*Ls2);//第二段卵形曲线终点偏角  (pow(Ls2_1, 2) / (2 * _Rc*Ls2))*(180 / PI);
	double w_Ls2_2 = atan2(SS2, NN2);  //atan2(SS2, NN2) * 180 / PI;
	double w_Ls2_3 = fwj2 - w_Ls2_1 + w_Ls2_2;

	if (pj < 0) {
		w_Ls1_3 = fwj1 - w_Ls1_1 + w_Ls1_2 - PI; //右偏时第一卵形曲线起点至虚拟起点方位角  fwj1 - w_Ls1_1 + w_Ls1_2 - 180;
		w_Ls2_3 = fwj2 + w_Ls2_1 - w_Ls2_2;//右偏时虚拟终点至第二卵形曲线终点方位角
	}

	double x_Ls1_1 = x_Ls1 + p_Ls1*cos(w_Ls1_3);//交点下第一段卵形曲线还原后虚拟起点x坐标  x_Ls1 + p_Ls1*cos(AngletoRadians(w_Ls1_3));
	double y_Ls1_1 = y_Ls1 + p_Ls1*sin(w_Ls1_3);//交点下第一段卵形曲线还原后虚拟起点y坐标  y_Ls1 + p_Ls1*sin(AngletoRadians(w_Ls1_3));
	double fwj_Ls1 = fwj1 + w_Ls1_1;//交点下第一段卵形曲线还原后虚拟轴线方位角
	double x_Ls2_1 = x_Ls2 + p_Ls2*cos(w_Ls2_3);//交点下第二段卵形曲线还原后虚拟起点x坐标  x_Ls2 + p_Ls2*cos(AngletoRadians(w_Ls2_3));
	double y_Ls2_1 = y_Ls2 + p_Ls2*sin(w_Ls2_3);//交点下第二段卵形曲线还原后虚拟起点y坐标  y_Ls2 + p_Ls2*sin(AngletoRadians(w_Ls2_3));
	double fwj_Ls2 = fwj2 - w_Ls2_1;//交点下第二段卵形曲线还原后虚拟轴线方位角

	if (pj < 0) {
		fwj_Ls1 = fwj1 - w_Ls1_1;
		fwj_Ls2 = fwj2 + w_Ls2_1;
	}
	double Ls1_2 = dk - QD;//第一段卵形曲线待求点至虚拟起点弧线距离
	double p1 = Ls1_2 - pow(Ls1_2, 5) / (40 * _Rc*_Rc*Ls1*Ls1) + pow(Ls1_2, 9) / (3456 * pow(_Rc, 4)*pow(Ls1_2, 4));
	double q1 = pow(Ls1_2, 3) / (6 * _Rc*Ls1) - pow(Ls1_2, 7) / (336 * pow(_Rc, 3)*pow(Ls1, 3));
	double w1 = pow(Ls1_2, 2) / (2 * _Rc*Ls1);  //(pow(Ls1_2, 2) / (2 * _Rc*Ls1))*(180 / PI);
	double _fwj1 = fwj_Ls1 - w1 - PI/2.0;  //fwj_Ls1 - w1 - 90;

	double Ls2_2 = ZD - dk;//第二段卵形曲线待求点至虚拟终点距离
	double p2 = Ls2_2 - pow(Ls2_2, 5) / (40 * _Rc*_Rc*Ls2*Ls2) + pow(Ls2_2, 9) / (3456 * pow(_Rc, 4)*pow(Ls2_2, 4));
	double q2 = pow(Ls2_2, 3) / (6 * _Rc*Ls2) - pow(Ls2_2, 7) / (336 * pow(_Rc, 3)*pow(Ls2, 3));
	double w2 = pow(Ls2_2, 2) / (2 * _Rc*Ls2);  //(pow(Ls2_2, 2) / (2 * _Rc*Ls2))*(180 / PI);
	double _fwj2 = fwj_Ls2 + w2 - PI / 2.0;  //fwj_Ls2 + w2 - 90;

	if (pj < 0) {
		_fwj1 = fwj_Ls1 + w1 - PI / 2.0;  //fwj_Ls1 + w1 - 90;
		_fwj2 = fwj_Ls2 - w2 - PI / 2.0;  //fwj_Ls2 - w2 - 90;
	}

	double _p1 = sqrt(p1*p1 + q1*q1);//第一卵形曲线待求点至虚拟原点距离
	double _w1 = fwj_Ls1 - atan2(q1, p1);//第一卵形曲线待求点至虚拟原点方位角  fwj_Ls1 - atan2(q1, p1) * 180 / PI;
	double _p2 = sqrt(p2*p2 + q2*q2);
	double _w2 = fwj_Ls2 - PI + atan2(q2, p2);  //fwj_Ls2 - 180 + atan2(q2, p2) * 180 / PI;

	if (pj < 0) {
		_w1 = fwj_Ls1 + atan2(q1, p1);  //fwj_Ls1 + atan2(q1, p1) * 180 / PI;
		_w2 = fwj_Ls2 - PI - atan2(q2, p2);  //fwj_Ls2 - 180 - atan2(q2, p2) * 180 / PI;
	}

	double x_Ls1_2 = _p1*cos(_w1) + x_Ls1_1;  //_p1*cos(AngletoRadians(_w1)) + x_Ls1_1;
	double y_Ls1_2 = _p1*sin(_w1) + y_Ls1_1; // 第一段卵形曲线待求点中心坐标  _p1*sin(AngletoRadians(_w1)) + y_Ls1_1;

	double x_Ls2_2 = _p2*cos(_w2) + x_Ls2_1;  //_p2*cos(AngletoRadians(_w2)) + x_Ls2_1;
	double y_Ls2_2 = _p2*sin(_w2) + y_Ls2_1;//第二段卵形曲线待求点中心坐标  _p2*sin(AngletoRadians(_w2)) + y_Ls2_1;

	double x1, y1, x2, y2, x, y;
	x1 = x_Ls1_2 + dist*cos(_fwj1);  //x_Ls1_2 + dist*cos(AngletoRadians(_fwj1));
	y1 = y_Ls1_2 + dist*sin(_fwj1);//第一段卵形曲线待求点偏中坐标  y_Ls1_2 + dist*sin(AngletoRadians(_fwj1));

	x2 = x_Ls2_2 + dist*cos(_fwj2);  //x_Ls2_2 + dist*cos(AngletoRadians(_fwj2));
	y2 = y_Ls2_2 + dist*sin(_fwj2);//第二段卵形曲线待求点偏中坐标  y_Ls2_2 + dist*sin(AngletoRadians(_fwj2));

	if (Ls1_2 < Ls1 + 0.05) {
		x = x1;
		y = y1;
	}
	else {
		x = x2;
		y = y2;
	}

	double* ret = new double[2];
	ret[0] = x;
	ret[1] = y;
	return ret;
}

//计算主点里程
void ArxRleCurveElement::Calc_Point_dk(double dk_begin, double dk_end)
{
	double len = dk_end - dk_begin;
	double dk = dk_end;

	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk && fabs(len) > 0) {
			jd.DK -= len;
		}
	}

	for (int i = 1; i < nJDNum - 1; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		JDELEMENT& jd1 = m_vecJDElement[i-1];
		JDELEMENT& jd2 = m_vecJDElement[i+1];
		jd.ZH = jd.DK - jd.T1;
		jd.HY = jd.ZH + jd.Ls1;
		jd.QZ = jd.HY + jd.Lc / 2;
		jd.YH = jd.HY + jd.Lc;
		jd.HZ = jd.YH + jd.Ls2;
		jd1.ZD = jd.ZH;
		jd2.QD = jd.HZ;

		if (i == 1) {
			JDELEMENT& _jd = m_vecJDElement[0];
			_jd.QD = _jd.DK;
			_jd.ZH = _jd.DK;
			_jd.HY = _jd.DK;
			_jd.QZ = _jd.DK;
			_jd.YH = _jd.DK;
			_jd.HZ = _jd.DK;
			jd.QD = _jd.HZ;
		}
		if (i == nJDNum - 2) {
			JDELEMENT& _jd = m_vecJDElement[nJDNum - 1];
			_jd.ZH = _jd.DK;
			_jd.HY = _jd.DK;
			_jd.QZ = _jd.DK;
			_jd.YH = _jd.DK;
			_jd.HZ = _jd.DK;
			_jd.ZD = _jd.DK;
			jd.ZD = _jd.ZH;
		}
	}

	dk = dk_begin;
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk && fabs(len) > 0) jd.DK += len;
		if (jd.QD > dk && fabs(len) > 0) jd.QD += len;
		if (jd.ZH > dk && fabs(len) > 0) jd.ZH += len;
		if (jd.HY > dk && fabs(len) > 0) jd.HY += len;
		if (jd.QZ > dk && fabs(len) > 0) jd.QZ += len;
		if (jd.YH > dk && fabs(len) > 0) jd.YH += len;
		if (jd.HZ > dk && fabs(len) > 0) jd.HZ += len;
		if (jd.ZD > dk && fabs(len) > 0) jd.ZD += len;
	}
}

//计算主点坐标
void ArxRleCurveElement::Calc_Point_xy(double dk_begin, double dk_end)
{
	double len = dk_end - dk_begin;
	double dk = dk_end;

	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk && fabs(len) > 0) jd.DK -= len;
		if (jd.QD > dk && fabs(len) > 0) jd.QD -= len;
		if (jd.ZH > dk && fabs(len) > 0) jd.ZH -= len;
		if (jd.HY > dk && fabs(len) > 0) jd.HY -= len;
		if (jd.QZ > dk && fabs(len) > 0) jd.QZ -= len;
		if (jd.YH > dk && fabs(len) > 0) jd.YH -= len;
		if (jd.HZ > dk && fabs(len) > 0) jd.HZ -= len;
		if (jd.ZD > dk && fabs(len) > 0) jd.ZD -= len;
	}


	for (int i = 1; i < nJDNum - 1; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		JDELEMENT& jd1 = m_vecJDElement[i - 1];
		JDELEMENT& jd2 = m_vecJDElement[i + 1];

		double* xys = Calc_Line_xy(jd.ZH, 0, jd.DK, jd.x, jd.y, jd1.x, jd1.y);
		jd.ZH_x = xys[0];
		jd.ZH_y = xys[1];

		xys = Calc_Line_xy(jd.HZ, 0, jd.DK, jd.x, jd.y, jd2.x, jd2.y);
		jd.HZ_x = xys[0];
		jd.HZ_y = xys[1];

		double* _xys = Calc_HY_YH_xy(jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
		jd.HY_x = _xys[0];
		jd.HY_y = _xys[1];
		jd.YH_x = _xys[2];
		jd.YH_y = _xys[3];

		xys = Calc_Circle_xy(jd.QZ, 0, jd.HY, jd.HY_x, jd.HY_y, jd.YH_x, jd.YH_y, jd.x, jd.y, jd.Rc);
		jd.QZ_x = xys[0];
		jd.QZ_y = xys[1];

		jd1.ZD_x = jd.ZH_x;
		jd1.ZD_y = jd.ZH_y;
		jd2.QD_x = jd.HZ_x;
		jd2.QD_y = jd.HZ_y;

		if (i == 1) {
			JDELEMENT& _jd = m_vecJDElement[0];
			_jd.QD_x = _jd.x;
			_jd.QD_y = _jd.y;
			_jd.ZH_x = _jd.x;
			_jd.ZH_y = _jd.y;
			_jd.HY_x = _jd.x;
			_jd.HY_y = _jd.y;
			_jd.QZ_x = _jd.x;
			_jd.QZ_y = _jd.y;
			_jd.YH_x = _jd.x;
			_jd.YH_y = _jd.y;
			_jd.HZ_x = _jd.x;
			_jd.HZ_y = _jd.y;
			jd.QD_x = _jd.HZ_x;
			jd.QD_y = _jd.HZ_y;
		}
		if (i == nJDNum - 2) {
			JDELEMENT& _jd = m_vecJDElement[nJDNum - 1];
			_jd.ZH_x = _jd.x;
			_jd.ZH_y = _jd.y;
			_jd.HY_x = _jd.x;
			_jd.HY_y = _jd.y;
			_jd.QZ_x = _jd.x;
			_jd.QZ_y = _jd.y;
			_jd.YH_x = _jd.x;
			_jd.YH_y = _jd.y;
			_jd.HZ_x = _jd.x;
			_jd.HZ_y = _jd.y;
			_jd.ZD_x = _jd.x;
			_jd.ZD_y = _jd.y;
			jd.ZD_x = _jd.ZH_x;
			jd.ZD_y = _jd.ZH_y;
		}
	}

	dk = dk_begin;
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk && fabs(len) > 0) jd.DK += len;
		if (jd.QD > dk && fabs(len) > 0) jd.QD += len;
		if (jd.ZH > dk && fabs(len) > 0) jd.ZH += len;
		if (jd.HY > dk && fabs(len) > 0) jd.HY += len;
		if (jd.QZ > dk && fabs(len) > 0) jd.QZ += len;
		if (jd.YH > dk && fabs(len) > 0) jd.YH += len;
		if (jd.HZ > dk && fabs(len) > 0) jd.HZ += len;
		if (jd.ZD > dk && fabs(len) > 0) jd.ZD += len;
	}
}

//计算任一点里程
double* ArxRleCurveElement::Calc_Curve_xy(double dk, double dist, double dk_begin, double dk_end)
{
	double len = dk_end - dk_begin;
	double _dk = dk_end;

	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > _dk && fabs(len) > 0) jd.DK -= len;
		if (jd.QD > _dk && fabs(len) > 0) jd.QD -= len;
		if (jd.ZH > _dk && fabs(len) > 0) jd.ZH -= len;
		if (jd.HY > _dk && fabs(len) > 0) jd.HY -= len;
		if (jd.QZ > _dk && fabs(len) > 0) jd.QZ -= len;
		if (jd.YH > _dk && fabs(len) > 0) jd.YH -= len;
		if (jd.HZ > _dk && fabs(len) > 0) jd.HZ -= len;
		if (jd.ZD > _dk && fabs(len) > 0) jd.ZD -= len;
	}

	_dk = dk > _dk ? dk - len : dk;
	double* xys = new double[2];
	for (int i = 1; i < nJDNum - 1; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		JDELEMENT& jd1 = m_vecJDElement[i-1];
		JDELEMENT& jd2 = m_vecJDElement[i+1];

		if (CompareFloat(_dk, jd.QD) >= 0 && CompareFloat(_dk, jd.ZD) <= 0) {
			if (jd.in_dk_part(_dk) > -1) {
				switch (jd.in_dk_part(_dk)) {
				case 1:
					xys = Calc_Line_xy(_dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y);
					break;
				case 5:
					xys = Calc_Line_xy(_dk, dist, jd2.DK, jd2.x, jd2.y, jd.x, jd.y);
					break;
				case 2:
					if (jd.R1 > 0) {
						xys = Calc_Eases_xy(_dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
					}
					else {
						xys = Calc_Eases_xy(_dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
					}
					break;
				case 4:
					if (jd.R2 > 0) {
						xys = Calc_Eases_xy(_dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
					}
					else {
						xys = Calc_Eases_xy(_dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
					}
					break;
				case 3:
					double* _xys = Calc_HY_YH_xy(jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
					xys = Calc_Circle_xy(_dk, dist, jd.HY, _xys[0], _xys[1], _xys[2], _xys[3], jd.x, jd.y, jd.Rc);
					break;
				}
			}

			break;
		}
	}

	_dk = dk_begin;
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > _dk && fabs(len) > 0) jd.DK += len;
		if (jd.QD > _dk && fabs(len) > 0) jd.QD += len;
		if (jd.ZH > _dk && fabs(len) > 0) jd.ZH += len;
		if (jd.HY > _dk && fabs(len) > 0) jd.HY += len;
		if (jd.QZ > _dk && fabs(len) > 0) jd.QZ += len;
		if (jd.YH > _dk && fabs(len) > 0) jd.YH += len;
		if (jd.HZ > _dk && fabs(len) > 0) jd.HZ += len;
		if (jd.ZD > _dk && fabs(len) > 0) jd.ZD += len;
	}

	return xys;
}

vector<double*> ArxRleCurveElement::Calc_Curve_xys(double dk_begin, double dk_end, double gap, double dist, double dk_begin_break, double dk_end_break)
{
	double len = dk_end_break - dk_begin_break;
	double dk0 = dk_end_break;
	double dk1 = dk_begin;
	double dk2 = dk_end;

	int nJDNum = m_vecJDElement.size();
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk0 && fabs(len) > 0) jd.DK -= len;
		if (jd.QD > dk0 && fabs(len) > 0) jd.QD -= len;
		if (jd.ZH > dk0 && fabs(len) > 0) jd.ZH -= len;
		if (jd.HY > dk0 && fabs(len) > 0) jd.HY -= len;
		if (jd.QZ > dk0 && fabs(len) > 0) jd.QZ -= len;
		if (jd.YH > dk0 && fabs(len) > 0) jd.YH -= len;
		if (jd.HZ > dk0 && fabs(len) > 0) jd.HZ -= len;
		if (jd.ZD > dk0 && fabs(len) > 0) jd.ZD -= len;
	}

	double _dk = dk1;
	vector<double*> xys_list;
	while (_dk < dk2) {
		double dk = _dk > dk0 ? _dk - len : _dk;
		for (int i = 1; i < nJDNum-1; i++) {
			JDELEMENT& jd = m_vecJDElement[i];
			JDELEMENT& jd1 = m_vecJDElement[i-1];
			JDELEMENT& jd2 = m_vecJDElement[i+1];

			if (CompareFloat(dk, jd.QD) >= 0 && CompareFloat(dk, jd.ZD) <= 0) {
				double* xys = new double[2];
				if (jd.in_dk_part(dk) > -1) {
					switch (jd.in_dk_part(dk)) {
					case 1:
						xys = Calc_Line_xy(dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y);
						break;
					case 5:
						xys = Calc_Line_xy(dk, dist, jd2.DK, jd2.x, jd2.y, jd.x, jd.y);
						break;
					case 2:
						if (jd.R1 > 0) {
							xys = Calc_Eases_xy(dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
						}
						else {
							xys = Calc_Eases_xy(dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
						}
						break;
					case 4:
						if (jd.R2 > 0) {
							xys = Calc_Eases_xy(dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
						}
						else {
							xys = Calc_Eases_xy(dk, dist, jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
						}
						break;
					case 3:
						double* _xys = Calc_HY_YH_xy(jd.DK, jd.x, jd.y, jd1.x, jd1.y, jd2.x, jd2.y, jd.Rc, jd.Lc, jd.R1, jd.R2, jd.T1, jd.T2, jd.Ls1, jd.Ls2);
						xys = Calc_Circle_xy(dk, dist, jd.HY, _xys[0], _xys[1], _xys[2], _xys[3], jd.x, jd.y, jd.Rc);
						break;
					}
					
					double* ret = new double[3];
					ret[0] = _dk;
					ret[1] = xys[0];
					ret[2] = xys[1];
					xys_list.push_back(ret);
				}

				break;
			}
		}

		_dk = _dk + gap;
	}

	dk0 = dk_begin_break;
	for (int i = 0; i < nJDNum; i++) {
		JDELEMENT& jd = m_vecJDElement[i];
		if (jd.DK > dk0 && fabs(len) > 0) jd.DK += len;
		if (jd.QD > dk0 && fabs(len) > 0) jd.QD += len;
		if (jd.ZH > dk0 && fabs(len) > 0) jd.ZH += len;
		if (jd.HY > dk0 && fabs(len) > 0) jd.HY += len;
		if (jd.QZ > dk0 && fabs(len) > 0) jd.QZ += len;
		if (jd.YH > dk0 && fabs(len) > 0) jd.YH += len;
		if (jd.HZ > dk0 && fabs(len) > 0) jd.HZ += len;
		if (jd.ZD > dk0 && fabs(len) > 0) jd.ZD += len;
	}

	return xys_list;
}

//坐标经纬度转换
double* ArxRleCurveElement::Trans_Curve_xy(double Xl, double Yn, int Tp, double L0, double H0)
{
	double a = 0; //a为坐标系椭球参数中地球长轴半径
	double b = 0; //b为坐标系椭球参数中地球短轴半径

	if (Tp <= 1) { //1954北京坐标系椭球参数
		a = 6378254;
		b = 6356863.01877304;
	}
	else if (Tp <= 2) { //1980西安坐标系系椭球参数
		a = 6378140;
		b = 6356755.28815752;
	}
	else if (Tp <= 3) { //WGS-84坐标系椭球参数
		a = 6378137;
		b = 6356752.3142;
	}
	else { //2000中国大地坐标系椭球参数
		a = 6378137;
		b = 6356752.3141;
	}

	a = a + H0;
	b = b + H0;

	double e1 = sqrt(a*a - b*b) / a; //第一偏心率e
	double e2 = sqrt(a*a - b*b) / b; //第二偏心率e2
	double c = a*a / b; //常数c
	double ee = e1*e1;
	double m0 = a*(1 - ee);
	double m2 = (3 * ee*m0) / 2;
	double m4 = (5 * ee*m2) / 4;
	double m6 = (7 * ee*m4) / 6;
	double m8 = (9 * ee*m6) / 8;
	double m10 = (11 * ee*m8) / 10;

	double a0 = m0 + m2 / 2 + 3 * m4 / 8 + 5 * m6 / 16 + 35 * m8 / 128;
	double a2 = m2 / 2 + m4 / 2 + 15 * m6 / 32 + 7 * m8 / 16;
	double a4 = m4 / 8 + 3 * m6 / 16 + 7 * m8 / 32;
	double a6 = m6 / 32 + m8 / 16;
	double a8 = m8 / 128;

	double xa0 = a0*PI / 180;
	double Bf1 = Xl / a0;//初始化Bf
	double bf;

	//按子午线弧长公式迭代计算
	double Bfi0 = Bf1;
	double Bfi1;
	double FBfi0;
	while (true)
	{
		FBfi0 = -a2*sin(2 * Bfi0) / 2 + a4*sin(4 * Bfi0) / 4 - a6*sin(6 * Bfi0) / 6 + a8*sin(8 * Bfi0) / 8;
		Bfi1 = (Xl - FBfi0) / a0;
		if (abs(Bfi1 - Bfi0) < PI*pow(10, -8) / (36 * 18))
			break;
		Bfi0 = Bfi1;
	}
	bf = Bfi1;
	// double R1=2.518828476*0.001,R2=3.7009546*pow(10,-6),R3=7.465*pow(10,-9);//2000中国大地坐标系计算系数
	double Bf = bf;//底点纬度
	double tf = tan(Bf);
	double sinBf = sin(Bf);
	double cosBf = cos(Bf);
	double nn22 = e2*e2*cosBf*cosBf;//引入的符号
	double Wf = sqrt(1 - e1*e1*sinBf*sinBf);//引入的辅助函数
	double Vf = sqrt(1 + e2*e2*cosBf*cosBf);
	double Mf = a*(1 - e1*e1) / pow(Wf, 3);//底点纬度下子午圈半径
	double y = Yn - 500000;
	double Nf = a / Wf;//底点纬度下卯酉圈半径

					   //经度:L,纬度:N
	double N = (Bf - (tf*y*y) / (2 * Mf*Nf) + (tf*(5 + 3 * tf*tf + nn22*nn22 - 9 * nn22*nn22*tf*tf)*pow(y, 4)) / (24 * Mf*pow(Nf, 3))
		- (tf*(61 + 90 * tf*tf + 45 * pow(tf, 4))*pow(y, 6)) / (720 * Mf*pow(Nf, 5))) * 180 / PI;
	double l = y / (Nf*cosBf) - (1 + 2 * tf*tf + nn22*nn22)*pow(y, 3) / (6 * pow(Nf, 3))*cosBf + (5 + 28 * tf*tf + 24 * pow(tf, 4))
		*pow(y, 5) / (120 * pow(Nf, 5)*cosBf);
	double L = L0 + l * 180 / PI;


	int _d1 = (int)L;
	double _t1 = (L - _d1) * 60;
	int _m1 = (int)_t1;
	double _s1 = (_t1 - _m1) * 60;

	int _d2 = (int)N;
	double _t2 = (N - _d2) * 60;
	int _m2 = (int)_t2;
	double _s2 = (_t2 - _m2) * 60;
	CString str;
	str.Format(_T("经度L：%d度%d分%.3f秒  维度N：%d度%d分%.3f秒"), _d1, _m1, _s1, _d2, _m2, _s2);

	double* ret = new double[2];
	ret[0] = L;
	ret[1] = N;

	return ret;
}




double ArxRleCurveElement::SqxCalc(double dk, SQXELEMENT sqx)
{
	double h = -9999.9999;
	double DK = sqx.DK, H = sqx.H, R = sqx.R, I1 = sqx.I1, I2 = sqx.I2, T = sqx.T, E = sqx.E, L = sqx.L;

	if(dk < (DK - T) || dk > (DK + T))
	{
		if (dk < DK)
			h = H - (DK - dk) * I1;
		else
			h = H + (dk - DK) * I2;
	}
	else
	{
		if(dk < DK)
			h = H - (DK - dk) * I1 + (dk - DK + T) * (dk - DK + T) / 2 / R * ((I1 > I2) ? -1.0 : 1.0);
		else
			h = H + (dk - DK) * I2 + (DK + T - dk) * (DK + T - dk) / 2 / R * ((I1 > I2) ? -1.0 : 1.0);
	}

	return h;
}

BOOL ArxRleCurveElement::IsSqx(double dk, SQXELEMENT sqx)
{
	double DK = sqx.DK, T = sqx.T;

	if(dk < (DK - T) || dk > (DK + T))
		return FALSE;

	return TRUE;
}

SQXELEMENT ArxRleCurveElement::GetSqx(double dk)
{
	int nSQXNum = m_vecSQXElement.size();
	if (nSQXNum == 0) return SQXELEMENT();
	if (dk <= m_vecSQXElement[0].DK) return m_vecSQXElement[0];
	if (dk >= m_vecSQXElement[nSQXNum - 1].DK) return m_vecSQXElement[nSQXNum - 1];
	for (int i = 1; i < nSQXNum; i++ )
	{
		SQXELEMENT sqx1 = m_vecSQXElement[i-1], sqx2 = m_vecSQXElement[i];
		if (dk >= sqx1.DK - sqx1.T && dk <= sqx1.DK + sqx1.T)
			return sqx1;
		if (dk > sqx1.DK + sqx1.T && dk < sqx2.DK - sqx2.T)
			return sqx1;
	}

	return SQXELEMENT();
}