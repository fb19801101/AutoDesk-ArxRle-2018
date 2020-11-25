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

/*－－－－－－－－－－－－－程序设计思路－－－－－－－－－－－－－－－－－－-----------
//程序功能:          在CAD软件已打开的图中，用户自定义起点和终点，程序会自动
                     寻找一条丛起点到终点的路径，并自动算出路径长度（长度不是1:1的）
//结构体:            定义一个边信息结构体（包含数据：起始点，ID号，边长）。
//5个变量:           栈变量(EdgeNode)sEdgeNode和(AcGePoint3d)sPoint3d.数据类型为边结构体数组edge[],
//                   OBJECTARX中的系统类型AcGePoint3dArray变量edgePts和点常量const_pt。
//三个模块函数:      getAllEntity(),getPos(),findpath();
//主要技术:          利用计算机中常用的数据结构堆栈和回溯算法。
//                   其中自定义了堆栈类。它是丛自定义的单链表类继承过来的。
//运行过程:          在主程序中利用getallentity()将CAD图中所有的直线信息同步赋值给数组
//                   edge和edgePts。因为同步，所以表示同一个直线两个数组索引关系为
//                   i=(j-1)*2;调用findpath()寻径:通过起始点a(起始点是变化的)，按照规定的
//                   两种方式在edgePts找到下一个起始点c。将起始点a压栈sPoint3d(为了如果找不到路径，
//                   进行回退时，利用此栈中的元素进行再次寻径)。(如果找到根据这两个点(a,c)找到
//                   edge相应的边,并将此边进栈sEdgeNode，同时判断c点是否与终点b相同，如果相同，
//                   找到路径，将栈中元素赋值给相应的数组，并结束findpath(),否则，
//                   同时用常量const_pt修改在edgePts中此边的起始，终止点，将c重新赋值给a,继续循环)。
//                   (如果找不到c,将sEdgeNode弹栈，sPoint3d弹栈的元素重新寻径)。如果找不到路径，退出函数。
//                   在栈sEdgeNode中始终包含丛入口到当前位置的路径。
//作者:              邵 志 民
//时间:              2005.05.18
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－-----------*/

#define EDGESIZE 1000

struct EdgeNode //边节点结构
{
	AcGePoint3d ptStart; //起始点
	AcGePoint3d ptEnd;   //终止点
	AcDbObjectId ptId;   //边的ID号
	double edgeLen;      //权(边长)
};
ArxRleStack<EdgeNode> sEdgeNode;     //创建栈对象
ArxRleStack<AcGePoint3d> sPoint3d; //将每次的起始点进栈
AcGePoint3dArray edgePts;//存储边的起始、终止点
EdgeNode edge[EDGESIZE]; //存储边的全部信息
const AcGePoint3d const_pt(0.666666,0.666666,0); //修改信息常量

//在edge数组中找到相应的边索引
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

//搜索路径代码  实现思想:根据迷宫老鼠算法得出。 实现技术：利用堆栈技术和回溯算法
BOOL findPath(AcGePoint3d a, const AcGePoint3d b)
{
    AcGePoint3d tmp;
	AcGePoint3d c;
	EdgeNode tmpnode;
	int num=0,j;

	//清空堆栈
	if(sEdgeNode.m_nCount !=0)
	   sEdgeNode.RemoveAll();
    if(sPoint3d.m_nCount !=0)
	   sPoint3d.RemoveAll();

	while(true)
	{
		 BOOL flg=true;//控制两种找下一个点方式，同时只能选择一种
		 BOOL notfind=true;//找不到相对应的点
         for(int i=0;i<=edgePts.length()-1;i=i+2)
		 {//根据a在edgePts数组中找到相应的下一点(a与边的起始点相同)
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
			{//根据a在edgePts数组中找到相应的下一点(a与边的终止点相同)
               if(edgePts.at(i+1)==a)
			   {
			      c=edgePts.at(i);
				  notfind=false;
			      break;
			   }
			}
		 }
		 if(notfind)//如果找不到C
		 { 
			if(sPoint3d.m_nCount==0)
				return false;
			else
			{
			   sPoint3d.pop(&tmp);
               a=tmp;
			   num++;//判断没有路径
			   sEdgeNode.pop(&tmpnode);//弹栈
			}             
		 }
		 else
		 {            
             sPoint3d.push(a);
			 j=getPos(a,c);//在edge数组中找到相应的边索引
             sEdgeNode.push(edge[j]);//进栈
			 //检测所组合的点是否是用户选择的终点
			 if(c==b)//如果找到终止点
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
             //修改Point3dArray此边位置信息(利用两个数组的索引关系)
             edgePts[(j-1)*2]=const_pt;
             edgePts[(j-1)*2+1]=const_pt;
			 //将c赋值给a，重新循环
             a=c;
		 }
		 if(num==((edgePts.length())/2))
			 return false;
	}
}

//遍历模型空间的所有直线实体
BOOL getAllEntity()
{
   //初始化变量
   AcDbLine *pLine=NULL;
   AcGePoint3d sPt,ePt;//直线的始终点
   double leng=0;

   AcDbBlockTable *pBlkTable=NULL;
   if((acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTable,AcDb::kForRead))!=Acad::eOk)//打开块表
   {
      acedAlert(L"打开块表失败!L");
      return false;
   }
   AcDbBlockTableRecord *pBlkTableRecord=NULL;
   if((pBlkTable->getAt(ACDB_MODEL_SPACE,pBlkTableRecord,AcDb::kForRead))!=Acad::eOk)//打开块表记录
   {
      acedAlert(L"打开块表记录失败L");
      pBlkTable->close();
      return false;
   }
   pBlkTable->close();//关闭块表

   //检测实体的个数
   int num=0;
   //定义遍历块表记录的浏览器，获得指向块表记录的浏览器指针
   AcDbBlockTableRecordIterator *pIterator=NULL; //创建叠代器
   if((pBlkTableRecord->newIterator(pIterator))!=Acad::eOk)
   {
	  acedAlert(L"创建浏览器失败!L");
      pBlkTableRecord->close();
      return false;
   }
   for(pIterator->start();!pIterator->done();pIterator->step())//遍历整个数据库
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
	      //检索直线实体的扩展数据－－－长度
		  pLine=AcDbLine::cast(obj);//得到指向ACDBLINE类的指针
          sPt=pLine->startPoint();
		  ePt=pLine->endPoint();
		  num++;
		  //赋值给边结构
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
   acutPrintf(L"图中实体检测完毕!\nL");
   return true;
}

//添加扩展属性模块(实体没有扩展属性)
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

//修改扩展属性模块(实体扩展属性)
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
	Obj->setXData(pRb);//保存链表数据	    

    acutRelRb(pRb);
}

//选择对象模块
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

//读取扩展属性模块(*OBJ没有关闭*)
void readXdata(AcDbObject* Obj, double& edgeLen)
{
     ASSERT(Obj!=NULL);
     //扩展属性数据链表
	 struct resbuf *pRb;
     pRb = Obj->xData(L"WIRE");
	 if(pRb!=NULL)
	 {
        for (;pRb != NULL;pRb = pRb->rbnext)
		{		          
           if (pRb->restype == 1040)	
		      edgeLen=pRb->resval.rreal;			
		}
        acutRelRb(pRb);//释放链表空间
	 }
	 else
		 edgeLen=88888;
}

//添加长度属性命令
void marxWire()
{
	ads_point pt1,pt2;
	AcGePoint3d st,et;

	//清空数组初始化
	if(!edgePts.isEmpty())
		edgePts.removeSubArray(0,edgePts.length()-1);	

	//遍历实体模块调用
	if(!getAllEntity())
	{
		acutPrintf(L"遍历实体操作错误\n");
		return;
	}

	int nErr = 0;
	acedInitGet(RSG_NONULL, NULL);
	nErr=acedGetPoint( NULL, L"\n请选取起始点:", pt1 );
	if (nErr==RTCAN)
	{
		acutPrintf(L"\nuser canceled!");
		return;
	}
	if (nErr==RTNORM)
	{
		st=asPnt3d(pt1);	   
	}

	nErr=acedGetPoint( NULL, L"\n请选取终止点:", pt2 );
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
	if(findPath(st,et))//开始寻径
	{
		double wirelen=0.0;
		AcDbObjectId wireid;
		for(int i=1;i<=sEdgeNode.m_nCount;i++)
		{
			wireid=edge[i].ptId;
			wirelen=edge[i].edgeLen;
			dis=dis+wirelen;
			//改变颜色       
			if ((acdbOpenObject(obj, wireid, AcDb::kForWrite)) != Acad::eOk)
			{
				acutPrintf(L"打开对象错误!\n");		      
				return;
			}
			pLine=AcDbLine::cast(obj);//得到指向ACDBLINE类的指针
			pLine->setColorIndex(3);//颜色		  
			obj->close();
		}
		acutPrintf(L"\n路径长度L = %f",dis);
	}
	else
		acutPrintf(L"\n对不起，没有找到相应路径!");
}

void marxAddLen()
{
	CAcModuleResourceOverride resOverride;
	double leng;
	AcDbObject *pObj;
	//选择对象
	if ((pObj = selectObject(AcDb::kForWrite)) == NULL)
		return;

	readXdata(pObj,leng);
	//当选择保存按钮时，将用户修改过的扩展属性保存到对象中去
	struct resbuf *pRb;
	pRb = pObj->xData(L"WIRE");

	if(leng==88888)   
		addXdata(pObj,leng);
	else
		mdXdata(pObj,leng);

	pObj->close();//关闭对象
}