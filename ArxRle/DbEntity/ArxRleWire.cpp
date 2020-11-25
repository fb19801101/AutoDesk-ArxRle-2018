//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleStack.h"

/*���������������������������������˼·������������������������������������-----------
//������:          ��CAD����Ѵ򿪵�ͼ�У��û��Զ��������յ㣬������Զ�
                     Ѱ��һ������㵽�յ��·�������Զ����·�����ȣ����Ȳ���1:1�ģ�
//�ṹ��:            ����һ������Ϣ�ṹ�壨�������ݣ���ʼ�㣬ID�ţ��߳�����
//5������:           ջ����(EdgeNode)sEdgeNode��(AcGePoint3d)sPoint3d.��������Ϊ�߽ṹ������edge[],
//                   OBJECTARX�е�ϵͳ����AcGePoint3dArray����edgePts�͵㳣��const_pt��
//����ģ�麯��:      getAllEntity(),getPos(),findpath();
//��Ҫ����:          ���ü�����г��õ����ݽṹ��ջ�ͻ����㷨��
//                   �����Զ����˶�ջ�ࡣ���Ǵ��Զ���ĵ�������̳й����ġ�
//���й���:          ��������������getallentity()��CADͼ�����е�ֱ����Ϣͬ����ֵ������
//                   edge��edgePts����Ϊͬ�������Ա�ʾͬһ��ֱ����������������ϵΪ
//                   i=(j-1)*2;����findpath()Ѱ��:ͨ����ʼ��a(��ʼ���Ǳ仯��)�����չ涨��
//                   ���ַ�ʽ��edgePts�ҵ���һ����ʼ��c������ʼ��aѹջsPoint3d(Ϊ������Ҳ���·����
//                   ���л���ʱ�����ô�ջ�е�Ԫ�ؽ����ٴ�Ѱ��)��(����ҵ�������������(a,c)�ҵ�
//                   edge��Ӧ�ı�,�����˱߽�ջsEdgeNode��ͬʱ�ж�c���Ƿ����յ�b��ͬ�������ͬ��
//                   �ҵ�·������ջ��Ԫ�ظ�ֵ����Ӧ�����飬������findpath(),����
//                   ͬʱ�ó���const_pt�޸���edgePts�д˱ߵ���ʼ����ֹ�㣬��c���¸�ֵ��a,����ѭ��)��
//                   (����Ҳ���c,��sEdgeNode��ջ��sPoint3d��ջ��Ԫ������Ѱ��)������Ҳ���·�����˳�������
//                   ��ջsEdgeNode��ʼ�հ�������ڵ���ǰλ�õ�·����
//����:              �� ־ ��
//ʱ��:              2005.05.18
����������������������������������������������������������������������������-----------*/

#define EDGESIZE 1000

struct EdgeNode //�߽ڵ�ṹ
{
	AcGePoint3d ptStart; //��ʼ��
	AcGePoint3d ptEnd;   //��ֹ��
	AcDbObjectId ptId;   //�ߵ�ID��
	double edgeLen;      //Ȩ(�߳�)
};
ArxRleStack<EdgeNode> sEdgeNode;     //����ջ����
ArxRleStack<AcGePoint3d> sPoint3d; //��ÿ�ε���ʼ���ջ
AcGePoint3dArray edgePts;//�洢�ߵ���ʼ����ֹ��
EdgeNode edge[EDGESIZE]; //�洢�ߵ�ȫ����Ϣ
const AcGePoint3d const_pt(0.666666,0.666666,0); //�޸���Ϣ����

//��edge�������ҵ���Ӧ�ı�����
int getPos(AcGePoint3d a, AcGePoint3d b)
{
	int i;
	for(i=1;i<=EDGESIZE;i++)
	{
		if((a==edge[i].ptStart) && (b==edge[i].ptEnd))
			break;

		if((b==edge[i].ptStart) && (a==edge[i].ptEnd))
			break;
	}
	return i;
}

//����·������  ʵ��˼��:�����Թ������㷨�ó��� ʵ�ּ��������ö�ջ�����ͻ����㷨
BOOL findPath(AcGePoint3d a, const AcGePoint3d b)
{
    AcGePoint3d tmp;
	AcGePoint3d c;
	EdgeNode tmpnode;
	int num=0,j;

	//��ն�ջ
	if(sEdgeNode.m_nCount !=0)
	   sEdgeNode.RemoveAll();
    if(sPoint3d.m_nCount !=0)
	   sPoint3d.RemoveAll();

	while(true)
	{
		 BOOL flg=true;//������������һ���㷽ʽ��ͬʱֻ��ѡ��һ��
		 BOOL notfind=true;//�Ҳ������Ӧ�ĵ�
         for(int i=0;i<=edgePts.length()-1;i=i+2)
		 {//����a��edgePts�������ҵ���Ӧ����һ��(a��ߵ���ʼ����ͬ)
            if(edgePts.at(i)==a)
			{
			    c=edgePts.at(i+1);
				flg=false;
				notfind=false;
			    break;
			}
		 }
		 if (flg)
		 {
            for(int i=0;i<=edgePts.length()-1;i=i+2)
			{//����a��edgePts�������ҵ���Ӧ����һ��(a��ߵ���ֹ����ͬ)
               if(edgePts.at(i+1)==a)
			   {
			      c=edgePts.at(i);
				  notfind=false;
			      break;
			   }
			}
		 }
		 if(notfind)//����Ҳ���C
		 { 
			if(sPoint3d.m_nCount==0)
				return false;
			else
			{
			   sPoint3d.pop(&tmp);
               a=tmp;
			   num++;//�ж�û��·��
			   sEdgeNode.pop(&tmpnode);//��ջ
			}             
		 }
		 else
		 {            
             sPoint3d.push(a);
			 j=getPos(a,c);//��edge�������ҵ���Ӧ�ı�����
             sEdgeNode.push(edge[j]);//��ջ
			 //�������ϵĵ��Ƿ����û�ѡ����յ�
			 if(c==b)//����ҵ���ֹ��
			 {
				for(int n=1;n<=sEdgeNode.m_nCount;n++)
				{
		           edge[n].ptEnd=sEdgeNode.GetAt(n).ptEnd;
		           edge[n].ptStart=sEdgeNode.GetAt(n).ptStart;
		           edge[n].edgeLen=sEdgeNode.GetAt(n).edgeLen;
                   edge[n].ptId=sEdgeNode.GetAt(n).ptId;
				}                
                return true;
			 }   
             //�޸�Point3dArray�˱�λ����Ϣ(�������������������ϵ)
             edgePts[(j-1)*2]=const_pt;
             edgePts[(j-1)*2+1]=const_pt;
			 //��c��ֵ��a������ѭ��
             a=c;
		 }
		 if(num==((edgePts.length())/2))
			 return false;
	}
}

//����ģ�Ϳռ������ֱ��ʵ��
BOOL getAllEntity()
{
   //��ʼ������
   AcDbLine *pLine=NULL;
   AcGePoint3d sPt,ePt;//ֱ�ߵ�ʼ�յ�
   double leng=0;

   AcDbBlockTable *pBlkTable=NULL;
   if((acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTable,AcDb::kForRead))!=Acad::eOk)//�򿪿��
   {
      acedAlert(L"�򿪿��ʧ��!L");
      return false;
   }
   AcDbBlockTableRecord *pBlkTableRecord=NULL;
   if((pBlkTable->getAt(ACDB_MODEL_SPACE,pBlkTableRecord,AcDb::kForRead))!=Acad::eOk)//�򿪿���¼
   {
      acedAlert(L"�򿪿���¼ʧ��L");
      pBlkTable->close();
      return false;
   }
   pBlkTable->close();//�رտ��

   //���ʵ��ĸ���
   int num=0;
   //�����������¼������������ָ�����¼�������ָ��
   AcDbBlockTableRecordIterator *pIterator=NULL; //����������
   if((pBlkTableRecord->newIterator(pIterator))!=Acad::eOk)
   {
	  acedAlert(L"���������ʧ��!L");
      pBlkTableRecord->close();
      return false;
   }
   for(pIterator->start();!pIterator->done();pIterator->step())//�����������ݿ�
   {
       AcDbObjectId ptId;
	   AcDbObject* obj;
	   pIterator->getEntityId(ptId);       
       if ((acdbOpenObject(obj, ptId, AcDb::kForRead)) != Acad::eOk)
	   {
          acutPrintf(L"acdbOpenEntity failed!L");
		  delete pIterator;pIterator=NULL;
          pBlkTableRecord->close();
          return false;
	   }
	   if (obj->isKindOf(AcDbLine::desc()))
	   {  	   
	      //����ֱ��ʵ�����չ���ݣ���������
		  pLine=AcDbLine::cast(obj);//�õ�ָ��ACDBLINE���ָ��
          sPt=pLine->startPoint();
		  ePt=pLine->endPoint();
		  num++;
		  //��ֵ���߽ṹ
          edge[num].ptEnd=ePt;
		  edge[num].ptStart=sPt;
		  edge[num].edgeLen=leng;
          edge[num].ptId=ptId;

          edgePts.append(sPt);
		  edgePts.append(ePt);
	   }
	   obj->close();
   }   

   delete pIterator;pIterator=NULL;
   pBlkTableRecord->close();
   acutPrintf(L"ͼ��ʵ�������!\nL");
   return true;
}

//�����չ����ģ��(ʵ��û����չ����)
void addXdata(AcDbObject* Obj, double edgeLen) 
{
	ASSERT(Obj!=NULL);
    struct  resbuf  *pRb, *pTemp;    
    pRb = Obj->xData(L"WIRE");   
    acdbRegApp(L"WIRE");
    pRb = acutNewRb(AcDb::kDxfRegAppName);
    pTemp = pRb;
    pTemp->resval.rstring = L"WIRE";

	pTemp->rbnext=acutNewRb(AcDb::kDxfXdReal); 
    pTemp=pTemp->rbnext; 
    pTemp->resval.rreal=edgeLen; 

    Obj->upgradeOpen();
    Obj->setXData(pRb);

    acutRelRb(pRb);
}

//�޸���չ����ģ��(ʵ����չ����)
void mdXdata(AcDbObject* Obj, double edgeLen) 
{
	ASSERT(Obj!=NULL);
    struct  resbuf  *pRb, *pTemp;    
    pRb = Obj->xData(L"WIRE");   
    for (pTemp=pRb;pTemp!=NULL;pTemp = pTemp->rbnext)
	{          
	  if (pTemp->restype == 1040)
		  pTemp->resval.rreal=edgeLen;               
	}
	Obj->upgradeOpen();	       
	Obj->setXData(pRb);//������������	    

    acutRelRb(pRb);
}

//ѡ�����ģ��
AcDbObject* selectObject(AcDb::OpenMode openMode)
{
    int sPoint3d;
    ads_name en;
    ads_point pt;
    acedInitGet(RSG_OTHER, L"Handle _HandleL");
    sPoint3d = acedEntSel(L"\nSelect an Entity or enterL"
        L" 'H' to enter its handle:  L", en, pt);

    ACHAR* handleStr = L"";
    AcDbObjectId ptId;
    switch (sPoint3d) {
    case RTNORM:   // got it!
        break;
    case RTKWORD:
        if ((acedGetString(1, L"Enter Valid Object Handle: L", handleStr, MAX_PATH) == RTNORM)
            && (acdbHandEnt(handleStr, en) == RTNORM))
            break;
    default:
       acutPrintf(L"Nothing Selected, Return Code==%d\nL",sPoint3d);
       return NULL;
    }

    Acad::ErrorStatus retStat;
    retStat = acdbGetObjectId(ptId, en);
    if (retStat != Acad::eOk)
	{
        acutPrintf(L"\nacdbGetObjectId failedL");
        acutPrintf(L"\nen==(%lx,%lx), retStat==%d\nL", en[0], en[1], ptId);
        return NULL;
    }

    AcDbObject* obj;

    if ((retStat = acdbOpenObject(obj, ptId, openMode)) != Acad::eOk)
    {
		acutPrintf(L"acdbOpenEntity failed: ename:(%lx,%lx),L mode:%d retStat:%dL", en[0], en[1], openMode, retStat);
        return NULL;
    }
    return obj;
}

//��ȡ��չ����ģ��(*OBJû�йر�*)
void readXdata(AcDbObject* Obj, double& edgeLen)
{
     ASSERT(Obj!=NULL);
     //��չ������������
	 struct resbuf *pRb;
     pRb = Obj->xData(L"WIRE");
	 if(pRb!=NULL)
	 {
        for (;pRb != NULL;pRb = pRb->rbnext)
		{		          
           if (pRb->restype == 1040)	
		      edgeLen=pRb->resval.rreal;			
		}
        acutRelRb(pRb);//�ͷ�����ռ�
	 }
	 else
		 edgeLen=88888;
}

//��ӳ�����������
void marxWire()
{
	ads_point pt1,pt2;
	AcGePoint3d st,et;

	//��������ʼ��
	if(!edgePts.isEmpty())
		edgePts.removeSubArray(0,edgePts.length()-1);	

	//����ʵ��ģ�����
	if(!getAllEntity())
	{
		acutPrintf(L"����ʵ���������\n");
		return;
	}

	int nErr = 0;
	acedInitGet(RSG_NONULL, NULL);
	nErr=acedGetPoint( NULL, L"\n��ѡȡ��ʼ��:", pt1 );
	if (nErr==RTCAN)
	{
		acutPrintf(L"\nuser canceled!");
		return;
	}
	if (nErr==RTNORM)
	{
		st=asPnt3d(pt1);	   
	}

	nErr=acedGetPoint( NULL, L"\n��ѡȡ��ֹ��:", pt2 );
	if (nErr==RTCAN)
	{
		acutPrintf(L"\nUser canceled!");
		return;
	}
	if (nErr==RTNORM)
	{
		et=asPnt3d(pt2);
	}

	AcDbObject *obj;
	AcDbLine *pLine=NULL;
	double dis=0;	
	if(findPath(st,et))//��ʼѰ��
	{
		double wirelen=0.0;
		AcDbObjectId wireid;
		for(int i=1;i<=sEdgeNode.m_nCount;i++)
		{
			wireid=edge[i].ptId;
			wirelen=edge[i].edgeLen;
			dis=dis+wirelen;
			//�ı���ɫ       
			if ((acdbOpenObject(obj, wireid, AcDb::kForWrite)) != Acad::eOk)
			{
				acutPrintf(L"�򿪶������!\n");		      
				return;
			}
			pLine=AcDbLine::cast(obj);//�õ�ָ��ACDBLINE���ָ��
			pLine->setColorIndex(3);//��ɫ		  
			obj->close();
		}
		acutPrintf(L"\n·������L = %f",dis);
	}
	else
		acutPrintf(L"\n�Բ���û���ҵ���Ӧ·��!");
}

void marxAddLen()
{
	CAcModuleResourceOverride resOverride;
	double leng;
	AcDbObject *pObj;
	//ѡ�����
	if ((pObj = selectObject(AcDb::kForWrite)) == NULL)
		return;

	readXdata(pObj,leng);
	//��ѡ�񱣴水ťʱ�����û��޸Ĺ�����չ���Ա��浽������ȥ
	struct resbuf *pRb;
	pRb = pObj->xData(L"WIRE");

	if(leng==88888)   
		addXdata(pObj,leng);
	else
		mdXdata(pObj,leng);

	pObj->close();//�رն���
}