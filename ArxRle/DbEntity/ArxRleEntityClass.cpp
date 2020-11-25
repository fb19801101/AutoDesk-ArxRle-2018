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

/*3DDWFPREC     ������άDWF�����ľ��ȡ� 
3DCONVERSIONMODE     ���ڽ����ʺ͹�Դ����ת��Ϊ��ǰ��Ʒ�汾�� 
3DSELECTIONMODE     ����ʹ����ά�Ӿ���ʽʱ�Ӿ����ص��Ķ����ѡ�����ȼ���
ACADLSPASDOC     �����ǽ�acad.lsp�ļ����ص�ÿ��ͼ���У����ǽ����ص������д򿪵ĵ�һ��ͼ���С�
ACADPREFIX     �洢��ACAD��������ָ����Ŀ¼·����
ACADVER     �洢AutoCAD�İ汾�š�
ACISOUTVER     ����ʹ��ACISOUT�������SAT�ļ���ACIS�汾��
ADCSTATE     ָʾ������Ĵ��ڴ��ڴ򿪻��ǹر�״̬��
AFLAGS     ��������ѡ�
ANGBASE     ������ڵ�ǰUCS�Ļ�׼������Ϊ 0��
ANGDIR     �������Ƕȵķ��򡣴�����ڵ�ǰUCS����� 0 �ǶȲ����Ƕ�ֵ�� 
ANNOALLVISIBLE     ���ػ���ʾ��֧�ֵ�ǰannotation scale��annotative����
ANNOAUTOSCALE     ע�ͱ�������ʱ����annotative�����֧��annotation scale��
ANNOTATIVEDWG     ָ��ͼ�β��뵽����ͼ����ʱ���Ƿ��൱��annotative�顣
APBOX     �򿪻�ر��Զ���׽�п����ʾ��
APERTURE     ������Ϊ��λ���ö���׽�п����ʾ�ߴ硣 
APSTATE     ��༭���еġ����дѡ��塱���ڴ��ڴ򿪻��ǹر�״̬��
AREA     �洢��AREA������������һ������� 
ATTDIA     ����INSERT�����Ƿ�ʹ�öԻ�����������ֵ�����롣 
ATTIPE     �������ڴ����������Ե���λ�༭������ʾ��
ATTMODE     �������Ե���ʾ��
ATTMULTI     �����Ƿ�ɴ����������ԡ�
ATTREQ     �ڲ��������п���INSERT�Ƿ�ʹ��Ĭ���������á�
AUDITCTL     ����AUDIT�����Ƿ񴴽��˲鱨�� (ADT) �ļ���
AUNITS     ���ýǶȵ�λ��
AUPREC     ��������ֻ���Ƕȵ�λ�����пɱ༭�Ƕȵ�λ��С��λ����
AUTODWFPUBLISH     �����Զ��������ܵĿ���״̬��
AUTOSNAP     �����Զ���׽��ǡ���������ʾ�ʹ�������ʾ��Ҳ���Դ򿪼���׷�ٺͶ���׽׷�٣������Ƽ���׷�١�����׽׷�ٺ�����ģʽ��������ʾ����ʾ��
BACKGROUNDPLOT     �����Ƿ�򿪺�̨��ӡ�ͺ�̨������Ĭ������£��رպ�̨��ӡ���򿪺�̨������
BACKZ     �Ի�ͼ��λ�洢��ǰ�ӿں������ƽ�浽Ŀ��ƽ���ƫ��ֵ��
BACTIONCOLOR     �ڿ�༭�������ö�����������ɫ��
BDEPENDENCYHIGHLIGHT     �����ڿ�༭����ѡ��������������е�ʱ�Ƿ����������������� 
BGRIPOBJCOLOR     �ڿ�༭�������üе����ɫ��
BGRIPOBJSIZE     �ڿ�༭���������������Ļ��ʾ���Զ���е����ʾ�ߴ硣
BINDTYPE     ���ư󶨻���λ�༭�ⲿ����ʱ�ⲿ�������ƵĴ���ʽ��
BLIPMODE     ���Ƶ����Ƿ�ɼ�����ϵͳ������������������ͬ��
BLOCKEDITLOCK     ��ֹ�򿪿�༭���Լ��༭��̬�鶨�塣
BLOCKEDITOR     ��ӳ��༭���Ƿ��Ѵ򿪡� 
BPARAMETERCOLOR     ���ÿ�༭���еĲ�������ɫ��
BPARAMETERFONT     ���ÿ�༭���еĲ����Ͷ������õ����塣 
BPARAMETERSIZE     �ڿ�༭���������������Ļ��ʾ�Ĳ����ı��͹��ܵ���ʾ�ߴ硣
BTMARKDISPLAY     �����Ƿ���ʾ��̬����յ���ֵ����ǡ� 
BVMODE     ���Ƶ�ǰ�ɼ���״̬�¿ɼ��Ķ����ڿ�༭���е���ʾ��ʽ�� 
CALCINPUT     �����Ƿ�����ı����Լ����ںͶԻ��������������е���ѧ���ʽ��ȫ�ֳ�����
CAMERADISPLAY     �򿪻�ر�����������ʾ��
CAMERAHEIGHT     Ϊ���������ָ��Ĭ�ϸ߶ȡ� 
CANNOSCALE     ���õ�ǰ�ռ��еĵ�ǰannotation scale������
CANNOSCALEVALUE     ���ص�ǰannotation scale��ֵ
CDATE     ��С����ʽ�洢��ǰ�����ں�ʱ�䡣
CECOLOR     �����¶������ɫ��
CELTSCALE     ���õ�ǰ��������ͱ������ӡ�
CELTYPE     �����¶�������͡�
CELWEIGHT     �����¶�����߿�
CENTERMT     ���Ƽе��������ˮƽ���е����ֵķ�ʽ��
CHAMFERA     ��CHAMMODE����Ϊ 0 ʱ���õ�һ�����Ǿ��롣
CHAMFERB     ��CHAMMODE����Ϊ 0 ʱ���õڶ������Ǿ��롣
CHAMFERC     ��CHAMMODE����Ϊ 1 ʱ���õ��ǳ��ȡ�
CHAMFERD     ��CHAMMODE����Ϊ 1 ʱ���õ��ǽǶȡ�
CHAMMODE     ����CHAMFER�����뷽����
CIRCLERAD     ����Ĭ�ϵ�Բ�뾶��
CLAYER     ���õ�ǰͼ�㡣
CLEANSCREENSTATE     ȫ����ʾ״̬�Ŀ���״̬��
CLISTATE     ����ڴ��ڴ򿪻��ǹر�״̬��
CMATERIAL     �����¶���Ĳ��ʡ�
CMDACTIVE     ָʾ���������ͨ���͸������ű����ǶԻ���
CMDDIA     ����ִ��QLEADER����ʱ��λ���ֱ༭������ʾ�� 
CMDECHO     ������AutoLISP���������ʱ�Ƿ������ʾ�����롣
CMDINPUTHISTORYMAX     ���ô洢��������ʾ�е���ǰ����ֵ�����������
CMDNAMES     ��ʾ������͸����������ơ� 
CMLEADERSTYLE     ��ǰʹ�õĶ���������ʽ������
CMLJUST     ָ�����߶�����ʽ��
CMLSCALE     ָ�����߱�����
CMLSTYLE     ��ǰʹ�õĶ�����ʽ�����ơ�
COMPASS     ������άָ�����ڵ�ǰ�ӿ��еĿ���״̬��
COORDS     ����״̬��������ĸ�ʽ�͸���Ƶ�ʡ�
COPYMODE     �����Ƿ��Զ��ظ�COPY���
CPLOTSTYLE     �����¶���ĵ�ǰ��ӡ��ʽ��
CPROFILE     ��ʾ��ǰ���õ����ơ�
CROSSINGAREACOLOR     ���ƽ���ѡ��ʱѡ���������ɫ�� 
CSHADOW     ������ά�������Ӱ��ʾ���ԡ�
CTAB     ����ͼ���еĵ�ǰ��ģ�ͻ򲼾֣�ѡ����ơ�
CTABLESTYLE     ��ǰʹ�õı����ʽ������
CURSORSIZE     ����Ļ��С�İٷֱ�ȷ��ʮ�ֹ��Ĵ�С��
CVPORT     ��ʾ��ǰ�ӿڵı�ʶ�롣
DIMALTU     �������б�ע����ʽ���Ƕȱ�ע���⣩�Ļ��㵥λ�ĵ�λ��ʽ��
DIMALTZ     ���ƶԻ��㵥λ��עֵ�����㴦��DIMALTZ��ֵΪ 0 �� 3 ʱֻӰ��Ӣ��-Ӣ���ע��
DIMANNO     ָʾ��ǰ��ע��ʽ�Ƿ���annotative��
DIMAPOST     ָ���������б�ע���ͣ��Ƕȱ�ע���⣩�Ļ����ע����ֵ������ǰ׺���׺�������߶�ָ������
DIMARCSYM     ���ƻ�����ע��Բ�����ŵ���ʾ�� 
DIMASO     ��ʽ�ġ������ڲ�Ʒ���Ա��ֽű��������ԡ�
DIMASSOC     ���Ʊ�ע����Ĺ������Լ��Ƿ�ֽ��ע��
DIMASZ     ���Ƴߴ��ߺ����߼�ͷ�Ĵ�С�������ƻ��ߵĴ�С��
DIMATFIT     �ߴ�����ڵĿռ䲻����ͬʱ���±�ע���ֺͼ�ͷʱ����ϵͳ������ȷ�������ߵ����з�ʽ��
DIMAUNIT     ���ýǶȱ�ע�ĵ�λ��ʽ��
DIMAZIN     �ԽǶȱ�ע�������㴦��
DIMBLK     ���óߴ���ĩ����ʾ�ļ�ͷ�顣 
DIMBLK1     ���óߴ��ߵ�һ���˵�ļ�ͷ��
DIMBLK2     ���óߴ��ߵڶ����˵�ļ�ͷ��
DIMCEN     ������DIMCENTER��DIMDIAMETER��DIMRADIUS������Ƶ�Բ��Բ����Բ�ı�Ǻ������ߡ�
DIMCLRD     Ϊ�ߴ��ߡ���ͷ�ͱ�ע����ָ����ɫ��ͬʱ������LEADER����������ߵ���ɫ�� 
DIMCLRE     Ϊ�ߴ����ָ����ɫ��
DIMCLRT     Ϊ��ע����ָ����ɫ�� 
DIMDEC     ���ñ�ע����λ����ʾ��С��λ����
DIMDLE     ��ʹ��Сб�ߴ����ͷ���б�עʱ�����óߴ��߳����ߴ���ߵľ��롣
DIMDLI     ���ƻ��߱�ע�гߴ��ߵļ�ࡣ
DIMDSEP     ָ��������λ��ʽΪʮ���Ƶı�עʱҪʹ�õĵ��ַ�С���ָ�����
DIMEXE     ָ���ߴ��߳����ߴ���ߵľ��롣
DIMEXO     ָ���ߴ����ƫ��ԭ��ľ��롣���ڹ̶����ȵĳߴ���ߣ���ֵ��������Сƫ������
DIMFIT     �ѷ����������DIMATFIT��DIMTMOVE��
DIMfRadiusAC     ���÷�����ʽ����DIMLUNIT����Ϊ 4 [����] �� 5 [����] ʱ����
DIMFXL     ���óߴ���ߵ��ܳ��ȣ���ʼ�ڳߴ��ߣ�ֱ����עԭ�㡣��ͼ�ε�λ���ó��ȡ�
DIMFXLON     �����Ƿ񽫳ߴ��������Ϊ�̶����ȡ�DIMFXLON��ʱ���ߴ��������ΪDIMFXLָ���ĳ��ȡ�
DIMGAP     �ߴ��߷ֳ����δӶ�����ע���ַ���������֮��ʱ�����ñ�ע������Χ�ľ��롣ͬʱ������LEADER�������ע�ͺͻ���֮��ļ�ࡣ������븺 ֵ��DIMGAP���ڱ�ע������Χ����һ������
DIMJOGANG     ȷ������뾶��ע�У��ߴ��ߵĺ����߶εĽǶȡ�
DIMJUST     ���Ʊ�ע���ֵ�ˮƽλ�á�
DIMLDRBLK     ָ�����߼�ͷ�����͡�
DIMLFAC     �������Ա�ע����ֵ�ı������ӡ�
DIMLIM     ���ɱ�ע������ΪĬ�����֡���DIMLIM����Ϊ����������ر�DIMTOL��
DIMLTEX1     ���õ�һ���ߴ���ߵ����͡�ֵΪ��㡢�����������ơ�
DIMLTEX2     ���õڶ����ߴ���ߵ����͡�ֵΪ��㡢�����������ơ�
DIMLTYPE     ���óߴ��ߵ����͡�ֵΪ��㡢�����������ơ�
DIMLUNIT     �������б�ע���ͣ��Ƕȱ�ע���⣩�ĵ�λ��
DIMLWD     Ϊ�ߴ���ָ���߿���ֵ�Ǳ�׼�߿�
DIMLWE     Ϊ�ߴ����ָ���߿���ֵ�Ǳ�׼�߿�
DIMPOST     ָ����ע����ֵ������ǰ׺���׺�������߶�ָ������
DIMRND     �����б�ע�������뵽ָ��ֵ��
DIMSAH     ���Ƴߴ��߼�ͷ�����ʾ��
DIMSCALE     ����Ӧ���ڱ�ע��������ָ����С�������ƫ��������ȫ�ֱ������ӡ�
DIMSD1     �����Ƿ���ʾ��һ���ߴ��ߺͼ�ͷ��
DIMSD2     �����Ƿ���ʾ�ڶ����ߴ��ߺͼ�ͷ��
DIMSE1     �����Ƿ��ֹ��ʾ��һ���ߴ���ߡ�
DIMSE2     �����Ƿ��ֹ��ʾ�ڶ����ߴ���ߡ�
DIMSHO     ��ʽ�ġ������ڱ��ֽű�����������û���κ�Ӱ�졣
DIMSOXD     ����ߴ������û���㹻�Ŀռ䣬�����ؼ�ͷ��
DIMSTYLE     ��ǰʹ�õı�ע��ʽ�����ơ� 
DIMTAD     ������������ڳߴ��ߵĴ�ֱλ�á�
DIMTDEC     ���ñ�ע����λ�Ĺ���ֵ��Ҫ��ʾ��С��λ����
DIMTFAC     ��ͨ��DIMTXTϵͳ��������һ����ָ�������͹���ֵ�����ָ߶�����ڱ�ע���ָ߶ȵı������ӡ�
DIMTFILL     ���Ʊ�ע���ֵı�����
DIMTFILLCLR     ���ñ�ע�����ֱ�������ɫ��
DIMTIH     �������б�ע���ͣ������ע���⣩�ı�ע�����ڳߴ�����ڵ�λ�á�
DIMTIX     �ڳߴ����֮��������֡�
DIMTM     ���ñ�ע���ֵ���С���£�����ޣ���DIMTOL��DIMLIM����Ϊ��ʱ����
DIMTMOVE     ���ñ�ע���ֵ��ƶ�����
DIMTOFL     �����Ƿ��ڳߴ����֮����Ƴߴ��ߣ���ʹ��ע���ֱ������ڳߴ����֮�⣩��
DIMTOH     ���Ʊ�ע�����ڳߴ�������λ�á�
DIMTOL     ������ڱ�ע����֮�󡣽�DIMTOL����Ϊ������ر�DIMLIM��
DIMTOLJ     ���ù���ֵ����ڱ�ע���ֵĴ�ֱ������ʽ��
DIMTP     ���ñ�ע���ֵ�����ϣ�����ޣ���DIMTOL��DIMLIM����Ϊ��ʱ����
DIMTSZ     ָ�����Ա�ע���뾶��ע�Լ�ֱ����ע�����������ͷ��Сб�ߵĳߴ硣
DIMTVP     ���Ʊ�ע�����ڳߴ����Ϸ����·��Ĵ�ֱλ�á�
DIMTXSTY     ָ����ע��������ʽ��
DIMTXT     ָ����ע���ֵĸ߶ȣ����ǵ�ǰ������ʽ���й̶��ĸ߶ȣ���
DIMTZIN     ���ƶԹ���ֵ�����㴦��
DIMUNIT     ��ʽ�ġ������ڲ�Ʒ���Ա��ֽű��������ԡ�DIMUNIT���滻ΪDIMLUNIT��DIMfRadiusAC��
DIMUPT     �����û���λ����ѡ�
DIMZIN     ���ƶ�����λֵ�����㴦��
DISPSILH     ������άʵ������������ڶ�ά�߿����ά�߿��Ӿ���ʽ�е���ʾ�� 
DISTANCE     �洢DIST���������ľ��롣
DONUTID     ����Բ����Ĭ���ھ���
DONUTOD     ����Բ����Ĭ���⾶����ֵ����Ϊ�㡣
DRAGMODE     �����϶��������ʾ�� 
DRAGP1     �����������϶�ģʽ�µ���������ʡ�
DRAGP2     ���ÿ����϶�ģʽ�µ���������ʡ�
DRAGVS     ������άʵ��ͼԪ�Լ�����ʵ�����������ʱ�����Ӿ���ʽ��
DRAWORDERCTL     �����ص��������ʾ�����ܼ̳�Ӱ���������BREAK��FILLET��HATCH��HATCHEDIT��EXPLODE��TRIM��JOIN�� PEDIT��OFFSET��
DRSTATE     ȷ����ͼ���޸������������ڴ��ڴ򿪻��ǹر�״̬��
DTEXTED     ָ��Ϊ�༭�������ֶ���ʾ���û����档
DWFfRadiusAME     ȷ��DWF�ο���ͼ�߿��Ƿ�ɼ���
DWFOSNAP     ȷ���Ƿ�Ϊ������ͼ���е�DWF�ο���ͼ�еļ���ͼ�����ö���׽��
DWGCHECK     ��ͼ��ʱ���ͼ�����Ƿ����Ǳ�����⡣
DWGCODEPAGE     ��SYSCODEPAGEϵͳ�����洢��ͬ��ֵ�����ڼ�����ԭ�򣩡�
DWGNAME     �洢��ǰͼ�ε����ơ�
DWGPREFIX     �洢ͼ�ε����������ļ���ǰ׺��
DWGTITLED     ָʾ��ǰͼ���Ƿ���������
DXEVAL     ����������ȡ������ʱ������Դ�Ƚϣ�������ݲ��ǵ�ǰ���ݣ�����ʾ����֪ͨ
DYNDIGRIP     �����ڼе�����༭�ڼ���ʾ��Щ��̬��ע�����뽫DYNDIVISϵͳ��������Ϊ 2���⽫��ʾ���еĶ�̬��ע��
DYNDIVIS     �����ڼе�����༭�ڼ���ʾ�Ķ�̬��ע������DYNDIGRIP�����ڼе�����༭�ڼ���ʾ��Щ��̬��ע�� 
DYNMODE     �򿪻�رն�̬���빦�ܡ�ȫ�����ܶ���ʱ�������Ľ���������ʾ�����ݡ�
DYNPICOORDS     ����ָ��������ʹ����������ʽ������ʹ�þ��������ʽ�� 
DYNPIFORMAT     ����ָ��������ʹ�ü��������ʽ������ʹ�õѿ��������ʽ�������ý������ڵڶ������һ�㡣
DYNPIVIS     ���ƺ�ʱ��ʾָ�����롣
DYNPROMPT     ���ơ���̬���롱��������ʾ����ʾ����ʾ��
DYNTOOLTIPS     �����ܹ�������ʾ�������Ӱ��Ĺ�������ʾ��
EDGEMODE     ����TRIM��EXTEND����ȷ���߽�ıߺͼ��бߵķ�ʽ��
ELEVATION     �洢�¶�������ڵ�ǰUCS�ĵ�ǰ��ߡ�
ENTERPRISEMENU     ��ʾ��ҵCUI������Ѷ��壩���ļ����������ļ�����·����
ERRNO
AutoLISP�������õ���AutoCAD��⵽����ʱ����ʾ��Ӧ�Ĵ������ı�š�
ERSTATE     ȷ�����ⲿ���ա�ѡ��崦�ڴ򿪻��ǹر�״̬��
EXPERT     �����Ƿ���ʾĳЩ�ض���ʾ��
EXPLMODE     ����EXPLODE�����Ƿ�֧�ְ���ͳһ�������� (NUS) �Ŀ顣
EXTMAX     �洢ͼ�η�Χ���Ͻǵ��ֵ��
EXTMIN     �洢ͼ�η�Χ���½ǵ��ֵ��
EXTNAMES     Ϊ�洢�ڶ�����е������������ƣ��������ͺ�ͼ�㣩���ò�����
FACETRATIO     ����Բ����Բ׶ʵ����Ƕ��Ŀ�߱ȡ�����Ϊ 1 �����������ܶ��Ը�����Ⱦģ�ͺ���ɫģ�͵�������
FACETRES     ������ɫ�����ɾ���������ߵĶ����ƽ���ȡ���ЧֵΪ 0.01 �� 10.0��
FIELDDISPLAY     ������ʾ���ֶ��Ƿ���л�ɫ����������ӡ������
FIELDEVAL     �����ֶεĸ��·�ʽ��
FILEDIA     ��ֹ��ʾ�ļ������Ի���
FILLETRAD     �洢��ǰ��Բ�ǰ뾶��
FILLMODE     ָ���Ƿ����ͼ��������䡢��άʵ���Լ������ߡ�
FONTALT     ָ���Ҳ���ָ���������ļ�ʱҪʹ�õ��滻���塣 
FONTMAP     ָ��Ҫʹ�õ�����ӳ���ļ���
fRadiusONTZ     ��ͼ�ε�λ�洢��ǰ�ӿ��е�ǰ�����ƽ�����Ŀ��ƽ���ƫ������
FULLOPEN     ָʾ��ǰͼ���Ƿ�ֲ��򿪡�
FULLPLOTPATH     �����Ƿ�ͼ���ļ�������·�����͵���̨��ӡ��
GRIDDISPLAY     ����դ�����ʾ��Ϊ����ʾ���ޡ�
GRIDMAJOR     ������դ�������դ���߱Ƚϵ�Ƶ�ʡ���Чֵ��ΧΪ�� 1 �� 100��
GRIDMODE     ָ��դ��Ŀ���״̬��
GRIDUNIT     ָ����ǰ�ӿڵ�դ���ࣨX��Y���򣩡� 
GRIPBLOCK     ѡ���󣬿��ƿ���Ƕ�׶����ϵļе����ʾ��
GRIPCOLOR     ����δѡ�ме����ɫ����Чȡֵ��ΧΪ 1 �� 255��
GRIPDYNCOLOR     ���ƶ�̬����Զ���е����ɫ����Чȡֵ��ΧΪ 1 �� 255��
GRIPHOT     ����ѡ���е����ɫ����Чȡֵ��ΧΪ 1 �� 255��
GRIPHOVER     ���ƹ����ͣ��δѡ���е���ʱ�üе�������ɫ����Чȡֵ��ΧΪ 1 �� 255��
GRIPOBJLIMIT     ѡ�񼯰����Ķ������ָ������ʱ����ֹ��ʾ�е㡣
GRIPS     ����ѡ�񼯼е��ڡ����족�����ƶ���������ת�������������š��͡�����е㡱ģʽ�е�ʹ�á�
GRIPSIZE     ������Ϊ��λ���üе��Ĵ�С����Чȡֵ��ΧΪ 1 �� 255��
GRIPTIPS     ���Ƶ������ͣ��֧�ּе���ʾ�Ķ�̬����Զ������ļе���ʱ�е���ʾ����ʾ�� 
GTAUTO     ����������Ϊ��ά�Ӿ���ʽ���ӿ�����������֮ǰѡ�����ʱ���е㹤���Ƿ��Զ���ʾ��
GTDEFAULT     ��������ά��ͼ�зֱ�����MOVE��ROTATE����ʱ��3DMOVE�� 3DROTATE�����Ƿ��Զ�������
GTLOCATION     ���� 3DMOVE�� 3DROTATE����֮ǰѡ�����ʱ�����Ƽе㹤�ߵĳ�ʼλ�á�
HALOGAP     ָ��һ��������һ�������ڵ���Ҫ��ʾ�ļ�ࡣ����һӢ��İٷֱ�ָ����ֵ���������������ż����Ӱ�졣
HANDLES     ����Ӧ�ó����Ƿ���Է��ʶ�������
HIDEPRECISION     ������������ɫ�ľ��ȡ�
HIDETEXT     ָ��ִ��HIDE����ʱ�Ƿ�����TEXT��DTEXT��MTEXT����������ֶ���
HIGHLIGHT     ���ƶ�������ԣ���Ӱ��ʹ�üе�ѡ���Ķ���
HPANG     ָ�����ͼ���ĽǶȡ�
HPASSOC     �������ͼ���ͽ�������Ƿ������
HPBOUND     ������BHATCH��BOUNDARY������Ķ������͡�
HPDOUBLE     ָ���û�����ͼ����˫�����ͼ����˫��ָ����ԭʼֱ�߳� 90 �Ƚǻ��Ƶĵڶ���ֱ�ߡ� 
HPDRAWORDER     ����ͼ���������Ļ�ͼ���򡣴洢��ͼ��������䡱�Ի����еġ���ͼ�������á�
HPGAPTOL     ����ͼ�����߽�ʱ���Ժ��Ե�����϶��Ĭ��ֵΪ 0��
HPMAXLINES     ���ƽ����ɵ�����ߵ������Ŀ������100��10,000,000֮���ֵ�������á�
HPINHERIT     ������HATCH��HATCHEDIT������ʹ�á��̳����ԡ�ʱ���ͼ������ͼ�����ԭ�㡣
HPNAME     ����Ĭ�����ͼ���������� (.)��HPNAME����ΪĬ��ֵ�� 
HPOBJWARNING     ���ÿ���ѡ���ͼ�����߽������������������������ʾ������Ϣ����
HPORIGIN     ����ڵ�ǰ�û�����ϵΪ�µ�ͼ������������ͼ�����ԭ�㡣
HPORIGINMODE     ����HATCHȷ��Ĭ��ͼ�����ԭ��ķ�ʽ��
HPSCALE     ָ�����ͼ���ı������ӣ���ֵ��������㡣
HPSEPARATE     �����ڼ����պϱ߽��Ͻ��в���ʱ��HATCH�Ǵ�������ͼ�������󣬻��Ƿֱ𴴽�����ͼ��������
HPSPACE     ָ���û�����ļ�ͼ�������ͼ���߼�࣬��ֵ��������㡣
HYPERLINKBASE     ָ��ͼ��������������Գ����ӵ�·����
IMAGEHLT     ����������������դͼ���ǽ����Թ�դͼ��߿�
IMPLIEDFACE     ����������ļ�⡣
INDEXCTL     �����Ƿ񴴽�ͼ��Ϳռ����������䱣�浽ͼ���ļ��С�
INETLOCATION     �洢BROWSER����͡����Web���Ի�����ʹ�õ�Internet��ַ��
INPUTHISTORYMODE     �����û�������ʷ��¼����ʾ���ݺ�λ�á� 
INSBASE     �洢BASE�������õĲ�����㣬�õ�ǰ�ռ��UCS�����ʾ��
INSNAME     ΪINSERT��������Ĭ�Ͽ�����
INSUNITS     ָ��������ŵ�ͼ���еĿ顢ͼ����ⲿ���ս����Զ��������õ�ͼ�ε�λֵ�� 
INSUNITSDEFSOURCE     ��INSUNITS����Ϊ 0 ʱ������Դ���ݵ�λֵ��
INSUNITSDEFTARGET     ��INSUNITS����Ϊ 0 ʱ������Ŀ��ͼ�ε�λֵ��
INTELLIGENTUPDATE     ����ͼ�ε�ˢ���ʡ�Ĭ��ֵΪ 20 ֡ÿ�롣
INTERFERECOLOR     ���ø���������ɫ��
INTERFEREOBJVS     ���ø��������Ӿ���ʽ��
INTERFEREVPVS     ָ��������ʱ�ӿڵ��Ӿ���ʽ��
INTERSECTIONCOLOR     �����Ӿ���ʽ����Ϊ����ά�߿�ʱ��ά���潻�ߴ��Ķ���ߵ���ɫ�� 
INTERSECTIONDISPLAY     �����Ӿ���ʽ����Ϊ����ά�߿�ʱ��ά���潻�ߴ��Ķ���ߵ���ʾ�� 
ISAVEBAK     �Ƿ񴴽������ļ� (BAK)��
ISAVEPERCENT     ȷ��ͼ���ļ���������������������ռ���������������ֻ���±����ͼ���ļ����Ѹ��ĵĲ��֣��Ӷ����ٱ���ͼ���ļ������ʱ�䡣��� ISAVEPERCENT����Ϊ 0����ÿһ�ζ�������ȫ���档
ISOLINES     ָ��������ÿ�������������Ŀ����Ч����ֵΪ 0 �� 2047��
LASTANGLE     �洢����ڵ�ǰ�ռ�ĵ�ǰUCS��XYƽ���������һԲ���Ķ˵�Ƕȡ�
LASTPOINT     �洢��һ������ĵ㡣
LASTPROMPT     �洢���Ե������е���һ���ַ�����
LATITUDE     ��ʮ���Ƹ�ʽָ��ͼ��ģ�͵�γ�ȡ� 
LAYEREVAL     ���ƺ�ʱ����ͼ��������еġ�δЭ����ͼ�㡱�������б��е���ͼ�㡣 
LAYERFILTERALERT     �Ƿ�ɾ��ͼ���������������ܡ� 
LAYERNOTIFY     ָ����ʱ��ʾ��δЭ������ͼ��ľ��档
LAYLOCKFADECTL     ��������ͼ���ϵĶ������ɫ
LAYOUTREGENCTL     ָ����ģ�͡�ѡ��Ͳ���ѡ��е���ʾ�б�ĸ��·�ʽ��������ܡ�
LEGACYCTRLPICK     ָ������ѭ��ѡ��ļ���CTRL+�����Ĳ����� 
LENSLENGTH     �洢͸����ͼ��ʹ�õĽ��ࣨ�Ժ���Ϊ��λ����
LIGHTGLYPHDISPLAY     �����Ƿ���ʾ������������ϵͳ��������Ϊ���ء�ʱ������ʾ����ͼ���еĹ�Դ�������� 
LIGHTINGUNITS     ������ʹ�ó����Դ����ʹ�ù�ȿ��ƹ�Դ����ָʾ��ǰ�Ĺ�ѧ��λ
LIGHTLISTSTATE     ָʾ�Ƿ��Ѵ򿪡�ģ���еĹ�Դ�����ڡ� 
LIGHTSINBLOCKS     ������Ⱦʱ�Ƿ�ʹ�ÿ��а����Ĺ�Դ
LIMCHECK     �����Ƿ������դ�����֮�ⴴ������
LIMMAX     �洢��ǰ�ռ�����Ϸ�դ����ޡ�
LIMMIN     �洢��ǰ�ռ�����·�դ����ޡ�
LINEARBRIGHTNESS     ���Ʊ�׼��Դ������ͼ�ε�ȫ�����ȼ���
LINEARCONTRAST     ���Ʊ�׼��Դ������ͼ�ε�ȫ�ֶԱȶȼ���
LOCALE     ��ʾ����ָʾ��ǰ����Ĵ��롣
LOCALROOTPREFIX     �洢���ļ��е�����·�������ļ����а�װ�˱��ؿ��Զ����ļ���
LOCKUI     ָ�������������Ϳɹ̶����ڣ����硰������ġ��͡����ԡ�ѡ��壩��λ�úʹ�С��
LOFTANG1     ����ͨ�����������е�һ�������İ�ģб�ȡ�
LOFTANG2     ����ͨ���������������һ�������İ�ģб�ȡ�
LOFTMAG1     ����ͨ�����������е�һ�������İ�ģб�ȵķ�ֵ�� 
LOFTMAG2     ����ͨ���������������һ�������İ�ģб�ȵķ�ֵ��
LOFTNORMALS     ���Ʒ�������ͨ������洦�ķ��ߡ�ָ��·����������ʱ���Ը����á�
LOFTPARAM     ���Ʒ���ʵ����������״��
LOGEXPBRIGHTNESS     ����ʹ�ù�ȿ��ƹ�Դʱͼ�ε�ȫ�����ȼ���
LOGEXPCONTRAST     ����ʹ�ù�ȿ��ƹ�Դʱͼ�ε�ȫ�ֶԱȶȼ���
LOGEXPDAYLIGHT     ����ʹ�ù�ȿ��ƹ�Դʱ�Ƿ�ʹ�������չ�
LOGEXPMIDTONES     ����ʹ�ù�ȿ��ƹ�Դʱͼ�ε�ȫ����ɫ������
LOGFILEMODE     ָ���Ƿ��ı����ڵ�����д����־�ļ���
LOGFILENAME     ָ����ǰͼ�ε��ı�������־�ļ���·�������ơ�
LOGFILEPATH     ָ������������ͼ�ε��ı�������־�ļ���·����
LOGINNAME     ����ʾ��������ʱ���û�������û�����
LONGITUDE     ��ʮ���Ƹ�ʽָ��ͼ��ģ�͵ľ��ȡ� 
LTSCALE     ����ȫ�����ͱ������ӡ� 
LUNITS     �������Ե�λ��
LUPREC     ���ó��ȵ�λ��С��λ����
LWDEFAULT     ����Ĭ���߿�ֵ��
LWDISPLAY     �����Ƿ���ʾ�߿�
LWUNITS     �����߿�λ����Ӣ����ʾ�����Ժ�����ʾ��
MATSTATE     ָʾ�Ƿ��Ѵ򿪡����ʡ����ڡ� 
MAXACTVP     ���ò����п�ͬʱ����ĵ��ӿڵ������Ŀ��
MAXSORT     �������б������������ķ�����������������Ŀ��
MBUTTONPAN     ���ƶ����豸�ϵĵ�������ť���ֵĲ�����
MEASUREINIT     ���ƴ�ͷ������ͼ����ʹ��Ӣ�ƻ���ʹ�ù���Ĭ�����á�
MEASUREMENT     ���Ƶ�ǰͼ����ʹ��Ӣ�ƻ��ǹ������ͼ���������ļ���
MENUCTL     ������Ļ�˵��е�ҳ���л���
MENUECHO     ���ò˵����Ժ���ʾ����λ��
MENUNAME     �洢�Զ����ļ����������ļ�����·����
MIRRTEXT     ����MIRROR���ӳ���ֵķ�ʽ��
MODEMACRO     ��״̬����ʾ�ַ��������統ǰͼ�ε����ơ�ʱ��/���ڴ��ǻ�����ģʽ�� 
MSMSTATE     �洢һ��ֵ������ָʾ�򿪻�رձ�Ǽ���������
MSOLESCALE     ���ƾ���ճ����ģ�Ϳռ��е����ֵ�OLE����Ĵ�С��
MSLTSCALE     ������annotation scale��ʾ�ڡ�ģ�͡�ѡ��ϵ�����
MTEXTED     �������ڱ༭�������ֶ����Ӧ�ó���
MTEXTFIXED     ���ö������ֵ���ʾ��С��λ�á�
MTJIGSTRING     ��������MTEXT����ʱ��ʾ�ڹ��λ�õ������������ݡ�
MYDOCUMENTSPREFIX     �洢�û���ǰ��¼�ġ�My Documents���ļ��е�����·����
NOMUTT     ��ֹ��ʾͨ������²���ֹ��ʾ����Ϣ��
NORTHDIRECTION     ָ����������ĽǶȡ� 
OBSCUREDCOLOR     ָ������ֱ�ߵ���ɫ��
OBSCUREDLTYPE     ָ���ڵ��ߵ����͡�
OFFSETDIST     ����Ĭ�ϵ�ƫ�ƾ��롣
OFFSETGAPTYPE     ����ƫ�Ʊպ϶����ʱ�����߶�֮���Ǳ�ڼ�϶�ķ�ʽ��
OLEfRadiusAME     �����Ƿ���ʾ�ʹ�ӡͼ��������OLE����ı߿�
OLEHIDE     ����OLE�������ʾ�ʹ�ӡ��
OLEQUALITY     ����OLE�����Ĭ�ϴ�ӡ������
OLESTARTUP     ���ƴ�ӡʱ�Ƿ����Ƕ���OLE�����ԴӦ�ó���
OPMSTATE     �洢һ��ֵ������ָʾ�򿪡��رջ����ء����ԡ�ѡ��塣
ORTHOMODE     �޶���������������ƶ���
OSMODE     ����ִ�еĶ���׽ģʽ��
OSNAPCOORD     �����Ƿ���������ʾ���������������ִ�ж���׽�� 
OSNAPHATCH     ��ʽ�ġ�ʹ��OSoPointIONSϵͳ�������ƶ���׽�Ƿ����ͼ��������
OSNAPNODELEGACY     ���ơ��ڵ㡱����׽�Ƿ�����ڲ�׽���������ֶ���
OSNAPZ     ���ƶ���׽�Ƿ��Զ�ͶӰ���뵱ǰUCS��λ�ڵ�ǰ��ߵ�XYƽ��ƽ�е�ƽ���ϡ�
OSoPointIONS     ʹ�ö�̬UCSʱ�����Զ�����ͼ��������;��и�Zֵ�ļ������ϵĶ���׽��
PALETTEOPAQUE     �����Ƿ����ʹ����͸���� 
PAPERUPDATE     ��ͼ�Բ�ͬ��Ϊ��ͼ�������ļ�ָ����Ĭ��ֵ��ͼֽ�ߴ��ӡ����ʱ�����ƾ���Ի������ʾ�� 
PDMODE     ������ʾ�����ķ�ʽ���й�����ֵ����ϸ��Ϣ����μ�POINT���
PDSIZE     ���õ�������ʾ�ߴ硣
PEDITACCEPT     ��ֹ��PEDIT����ʾ��ѡ���Ķ����Ƕ���ߡ���ʾ����ѡ�������Զ�ת��Ϊ����ߡ�
PELLIPSE     ������ELLIPSE���������Բ���͡�
PERIMETER     �洢��AREA��LIST�����������һ���ܳ�ֵ�� 
PERSPECTIVE     ָ����ǰ�ӿ��Ƿ���ʾ͸����ͼ��
PERSPECTIVECLIP     ȷ���۵���õ�λ�á�
PFACEVMAX     ����ÿ�������󶥵�����
PICKADD     ���ƺ���ѡ�����滻��ǰѡ�񼯻�����ӵ����С�
PICKAUTO     ������ʾ��ѡ�����ʱ�Ƿ��Զ���ʾѡ�񴰿ڡ�
PICKBOX     ������Ϊ��λ���ö���ѡ��Ŀ��ĸ߶ȡ� 
PICKDRAG     ���ƻ���ѡ�񴰿ڵķ�����
PICKFIRST     �����ڷ�������֮ǰ����ѡ���ִ�У�����֮��ѡ�����
PICKSTYLE     ���Ʊ���ѡ��͹���ͼ�����ѡ���ʹ�á�
PLATFORM     ָʾ����ʹ�õ�ƽ̨��
PLINEGEN     ����Χ�ƶ�ά����ߵĶ�����������ͼ���ķ�ʽ��
PLINETYPE     ָ���Ƿ�ʹ���Ż��Ķ�ά����ߡ�
PLINEWID     �洢Ĭ�ϵĶ���߿�ȡ�
PLOTOFFSET     ���ƴ�ӡƫ��������ڿɴ�ӡ�����������ͼֽ�ߡ�
PLOTROTMODE     ���ƴ�ӡ����
PLQUIET     �����Ƿ���ʾ��ѡ����ش�ӡ�Ի���ͷ������ű����� 
POLARADDANG     �洢����׷�ٺͼ��Ჶ׽�������Ƕȡ� 
POLARANG     ���ü����������
POLARDIST
SNAPTYPEϵͳ��������Ϊ 1�����Ჶ׽��ʱ�����ò�׽������
POLARMODE     ���Ƽ���׷�ٺͶ���׽׷�ٵ����á�
POLYSIDES     ����POLYGON�����Ĭ�ϱ�����ȡֵ��ΧΪ 3 �� 1024��
POPUPS     ��ʾ��ǰ���õ���ʾ��������״̬��
PREVIEWEFFECT     ָ������Ԥ������ѡ����Ӿ�Ч���� 
PREVIEWFILTER     ��ѡ��Ԥ�����ų�ָ���Ķ������͡�
PRODUCT     ���ز�Ʒ���ơ�
PROGRAM     ���س������ơ�
PROJECTNAME     Ϊ��ǰͼ��ָ���������ơ�
PROJMODE     ���������޼�������ĵ�ǰͶӰģʽ��
PROXYGRAPHICS     ָ���Ƿ񽫴�������ͼ�񱣴���ͼ���С� 
PROXYNOTICE     �ڴ�������ʱ��ʾ֪ͨ��
PROXYSHOW     ���ƴ��������ͼ���е���ʾ��
PROXYWEBSEARCH     ָ����������󼤻����ķ�ʽ��
PSLTSCALE     ������ͼֽ�ռ��ӿ�����ʾ�Ķ�������ͱ�����
PSOLHEIGHT     ����POLYSOLID�����ɨ��ʵ�����ʱ���һ������ĸ߶�ֵ��
PSOLWIDTH     ����POLYSOLID�����ɨ��ʵ�����ʱ���һ������ĵĿ��ֵ��
PSTYLEMODE     ָʾ��ǰͼ�δ�����ɫ��ش�ӡ��ʽģʽ����������ӡ��ʽģʽ�� 
PSTYLEPOLICY     ���ƴ���AutoCAD2000 ֮ǰ�İ汾�д�����ͼ�λ�ʹ��ͼ��ģ���ͷ������ͼ��ʱ��ʹ�õĴ�ӡ��ʽģʽ��
PSVPSCALE     Ϊ�����´������ӿ�������ͼ�������ӡ�
PUBLISHALLSHEETS     ���Ʒ���PUBLISH����ʱ�����д���������Ի����б�
PUBLISHCOLLATE     �����Ƿ�ͼֽ��Ϊ������ҵ����
PUCSBASE     �洢��������UCS���ã�������ͼֽ�ռ䣩��ԭ��ͷ����UCS���ơ�
QCSTATE     ȷ�������ټ��㡱���������ڴ򿪻��ǹر�״̬��
QTEXTMODE     �������ֵ���ʾ��ʽ�� 
RASTERDPI     ���ƽ����׻�Ӣ��ת��Ϊ���أ���֮��ʱ��ͼֽ�ߴ�ʹ�ӡ��������
RASTERPREVIEW     �����Ƿ�BMPԤ��ͼ����ͼ��һ�𱣴档
RECOVERYMODE     ����ϵͳ���ֹ��Ϻ��Ƿ��¼ͼ���޸���Ϣ��
REFEDITNAME     ��ʾ���ڱ༭�Ĳ������ơ�
REGENMODE     ����ͼ�ε��Զ������ɡ�
RE-INIT     ���³�ʼ�����ֻ��ǡ����ֻ��Ƕ˿ں�acad.pgp�ļ���
REMEMBERFOLDERS     ������ʾ�ڱ�׼�ļ�ѡ��Ի����е�Ĭ��·����
RENDERPREFSSTATE     ����һ��ֵ������ָʾ�򿪻�رա���Ⱦ���á�ѡ��塣
RENDERUSERLIGHTS     ������Ⱦ�������Ƿ�ת���û���Դ
REPORTERROR     ���Ƴ����쳣�ر�ʱ�Ƿ������Autodesk���ʹ��󱨸档
ROAMABLEROOTPREFIX     �洢���ļ��е�����·����
RTDISPLAY     ����ִ��ʵZOOM��PAN����ʱ��դͼ���OLE�������ʾ��
SAVEFIDELITY     ���Ʊ���ͼ��ʱ�Ƿ񱣴����Ӿ������
SAVEFILE     �洢��ǰ�Զ�������ļ�����
SAVEFILEPATH     ָ����ǰ�����������Զ������ļ�Ŀ¼��·����
SAVENAME     ��ʾ��������ͼ�ε��ļ�����Ŀ¼·����
SAVETIME     �Է���Ϊ��λ�����Զ�����ʱ������
SCREENBOXES     �洢��ͼ�������Ļ�˵�����ʾ�Ŀ�����
SCREENMODE     ָʾ��ʾ��״̬��
SCREENSIZE     ������Ϊ��λ�洢��ǰ�ӿڴ�С��X��Y����
SELECTIONANNODISPLAY     ����ѡ��annotative����ʱ�����������ʾ���Ƿ���ʱ�Խϰ�״̬��ʾ
SELECTIONAREA     ����ѡ���������ʾЧ����
SELECTIONAREAOPACITY     ���ƽ��д���ѡ��ͽ���ѡ��ʱѡ�������͸���ȡ� 
SELECTIONPREVIEW     ���ƹ�����������ʱ�����Է�ʽ��
SETBYLAYERMODE     ����ΪSETBYLAYERѡ����Щ����
SHADEDGE     ������Ⱦʱ�ߵ���ɫ��
SHADEDIF     ������������뻷����ı��ʡ�
SHADOWPLANELOCATION     ����������ʾ��Ӱ�Ĳ��ɼ���ƽ���λ�á� 
SHORTCUTMENU     ���ơ�Ĭ�ϡ������༭���͡����ģʽ�Ŀ�ݲ˵��ڻ�ͼ�����Ƿ���á�
SHOWHIST     ����ͼ����ʵ��ġ���ʾ��ʷ��¼�����ԡ� 
SHOWLAYERUSAGE     ����ͼ�����Թ������С�ָʾ����ʹ�õ�ͼ�㡱ѡ���Ƿ�ѡ��
SHPNAME     ����Ĭ�ϵ������ơ�
SIGWARN     ���ƴ򿪴��и��ŵ�����ǩ�����ļ�ʱ�Ƿ񷢳����档
SKETCHINC     ��������SKETCH����ļ�¼������
SKPOLY     ȷ��SKETCH��������ֱ�߻������ɶ���ߡ�
SNAPANG     ���õ�ǰ�ӿڵĲ�׽��դ����ת�Ƕȡ���ת����Ե�ǰUCSָ����
SNAPBASE     ����ڵ�ǰUCS���õ�ǰ�ӿڵĲ�׽��դ��ԭ�㡣
SNAPISOPAIR     ���Ƶ�ǰ�ӿڵĵ����ƽ�档
SNAPMODE     �򿪻�رղ�׽ģʽ��
SNAPSTYL     ���õ�ǰ�ӿڵĲ�׽��ʽ��
SNAPTYPE     ���õ�ǰ�ӿڵĲ�׽���͡�
SNAPUNIT     ���õ�ǰ�ӿڵĲ�׽��ࡣ
SOLIDCHECK     Ϊ��ǰ����򿪻�ر�ʵ��У�顣
SOLIDHIST     ���Ƹ���ʵ���Ƿ��������ڸ���ʵ����ԭʼ����ġ���ʷ��¼����
SPLfRadiusAME     �����������ߺ�������϶���ߵ���ʾ��
SPLINESEGS     ����PEDIT����ġ��������ߡ�ѡ�����ɵ�������϶�����߶���Ŀ��
SPLINETYPE     ����PEDIT����ġ��������ߡ�ѡ�����ɵ��������͡�
SSFOUND     �������ͼֽ���ɹ�������ʾͼֽ��·�����ļ�����
SSLOCATE     ���ƴ�ͼ��ʱ�Ƿ�λ�ʹ����ͼ���������ͼֽ����
SSMAUTOOPEN     ���Ƶ�����ͼֽ�������ͼ��ʱͼֽ������������ʾ��Ϊ��
SSMPOLLTIME     ����ͼֽ����״̬���ݵ��Զ�ˢ��ʱ������
SSMSHEETSTATUS     ����ͼֽ����״̬���ݵ�ˢ�·�ʽ��
SSMSTATE     ȷ����ͼֽ�������������ڴ��ڴ򿪻��ǹر�״̬��
STANDARDSVIOLATION     ָ���������޸ķǱ�׼����ʱ���Ƿ�֪ͨ�û���ǰͼ���д��ڱ�׼��ͻ��
STARTUP     ����ʹ��NEW��QNEW�������ͼ��ʱ���Ƿ���ʾ��������ͼ�Ρ��Ի��򡣻����Ƶ�Ӧ�ó�������ʱ�Ƿ���ʾ���������Ի���
STEPSIZE     ָ�����λ����ģʽ��ÿһ���Ĵ�С��
STEPSPERSEC     ָ�����λ����ģʽ��ÿ��ִ�еĲ�����
SUNPROPERTIESSTATE     ָʾ���������ԡ����ڴ��ڴ򿪻��ǹر�״̬�� 
SUNSTATUS     ���������Ƿ��ڵ�ǰ�ӿ���Ͷ����ߡ� 
SURFTAB1     ΪRULESURF��TABSURF��������Ҫ���ɵ��б���Ŀ��ͬʱΪREVSURF��EDGESURF����������M����������ܶȡ�
SURFTAB2     ΪREVSURF��EDGESURF����������N����������ܶȡ�
SURFTYPE     ����PEDIT����ġ�ƽ����ѡ��Ҫִ�е�����������͡�
SURFU     ΪPEDIT����ġ�ƽ����ѡ��������M����������ܶ��Լ���������ϵ�U�����ܶȡ�
SURFV     ΪPEDIT����ġ�ƽ����ѡ��������N����������ܶ��Լ���������ϵ�V�����ܶȡ�
SYSCODEPAGE     ָʾ�ɲ���ϵͳ��������ϵͳ����ҳ��Ҫ���Ĵ���ҳ����μ�����ϵͳ�ġ���������
TABLEINDICATOR     ���Ƶ�����λ���ֱ༭���Ա༭���Ԫʱ������������ĸ����ʾ�� 
TABLETOOLBAR     ���Ʊ�񹤾�������ʾ��
TABMODE     �������ֻ��ǵ�ʹ�á�
TARGET     �洢��ǰ�ӿ���Ŀ����λ�ã���UCS�����ʾ����
TBCUSTOMIZE     �����Ƿ�����Զ��幤��ѡ����顣
TDCREATE     �洢����ͼ��ʱ�ı���ʱ������ڡ�
TDINDWG     �洢�ܵı༭ʱ�䣬�������α��浱ǰͼ��֮�仨�ѵ���ʱ�䡣
TDUCREATE     �洢����ͼ��ʱ��ͨ��ʱ������ڡ�
TDUPDATE     �洢�ϴθ���/����ʱ�ı���ʱ������ڡ�
TDUSRTIMER     �洢�û�����ʱ���ʱ����
TDUUPDATE     �洢�ϴθ���/����ʱ��ͨ��ʱ������ڡ�
TEMPOVERRIDES     �򿪻�ر�����ģʽ������׽����ģʽ��ʱ������� 
TEMPPREFIX     ����Ϊ������ʱ�ļ������õ�Ŀ¼��������еĻ���������·���ָ�����
TEXTEVAL     ��������ж���TEXT��ʹ��AutoLISP���� -TEXT����������ַ�����
TEXTFILL     ���ƴ�ӡ����ȾʱTrueType�������䷽ʽ��
TEXTOUTPUTFILEFORMAT     �ṩ��ӡ���ı�������־�ļ���Unicodeѡ� 
TEXTQLTY     �������������ķֱ�����Ƕ����
TEXTSIZE     �����õ�ǰ������ʽ���Ƶ������ֶ����Ĭ�ϸ߶ȡ�
TEXTSTYLE     ��ǰʹ�õ�������ʽ�����ơ�
THICKNESS     ���õ�ǰ����ά��ȡ�
TILEMODE     ����ģ�͡�ѡ�����һ������ѡ���Ϊ��ǰ��
TIMEZONE     ����ͼ���������ʱ���� 
TOOLTIPMERGE     ����ͼͼ��������ʾ�ϲ�Ϊ������������ʾ�� 
TOOLTIPS     ���ƹ������Ϲ�������ʾ����ʾ��
TPSTATE     ȷ��������ѡ��塱���ڴ��ڴ򿪻��ǹر�״̬��
TRACEWID     ���ÿ��ߵ�Ĭ�Ͽ�ȡ�
TRACKPATH     ���Ƽ���׷�ٺͶ���׽׷�ٶ���·������ʾ��
TRAYICONS     �����Ƿ���״̬����ʾ״̬���̡�
TRAYNOTIFY     �����Ƿ���״̬����������ʾ����֪ͨ��
TRAYTIMEOUT     ���Ʒ���֪ͨ����ʾʱ�䳤�ȣ�����Ϊ��λ����
TREEDEPTH     ָ�������ȣ�����״�ṹ�Ŀռ��������Էֳ���֧�Ĵ�����
TREEMAX     ͨ�����ƿռ��������˷������еĽڵ���Ŀ���Ӷ�����������ͼ��ʱռ�õ��ڴ档
TRIMMODE     �����Ƿ��޼����Ǻ�Բ��ѡ���ߡ�
TSPACEFAC     ���ƶ������ֵ��м�ࡣ
TSPACETYPE    ���ƶ���������ʹ�õ��м�����͡�
TSTACKALIGN     ���ƶѵ����ֵĴ�ֱ���뷽ʽ��
TSTACKSIZE     ���ƶѵ����ַ����߶������ѡ�����ֵĵ�ǰ�߶ȵİٷֱȡ�
UCSAXISANG     ʹ��UCS�����X��Y��Zѡ������һ������תUCSʱ���洢Ĭ�ϽǶȡ� 
UCSBASE     �洢��������UCS���õ�ԭ��ͷ����UCS���ơ�
UCSDETECT     �����Ƿ��Ѽ��̬UCS��ȡ��
UCSFOLLOW     ��һ��UCSת������һ��UCSʱ�Ƿ�����ƽ����ͼ�� 
UCSICON     ��ʾ��ǰ�ӿڻ򲼾ֵ�UCSͼ�ꡣ 
UCSNAME     �洢��ǰ�ռ䵱ǰ�ӿڵĵ�ǰ����ϵ���ơ�
UCSORG     �洢��ǰ�ռ��е�ǰ�ӿڵĵ�ǰ����ϵԭ�㡣
UCSORTHO     ȷ���ָ�������ͼʱ�Ƿ��Զ��ָ���ص�����UCS���á�
UCSVIEW     ȷ����ǰUCS�Ƿ���������ͼһ�𱣴档 
UCSVP     ȷ���ӿ��е�UCS�Ǳ��ֲ��仹�ǽ�����Ӧ�ı��Է�ӳ��ǰ�ӿڵ�UCS״̬��
UCSXDIR     �洢��ǰ�ռ��е�ǰ�ӿڵĵ�ǰUCS��X���� 
UCSYDIR     �洢��ǰ�ռ��е�ǰ�ӿڵĵ�ǰUCS��Y���� 
UNDOCTL     ָʾUNDO����ġ��Զ����������ơ��͡����顱ѡ���״̬��
UNDOMARKS     �洢����ǡ�ѡ�������UNDO�������еı����Ŀ��
UNITMODE     ���Ƶ�λ����ʾ��ʽ�� 
UPDATETHUMBNAIL     ����ͼֽ���������е���ͼԤ���ĸ��¡� 
USERI1-5     �ṩ����ֵ�洢�ͼ������ܡ��������ϵͳ������USERI1��USERI2��USERI3��USERI4 ��USERI5��
USERR1-5     �ṩʵ���Ĵ洢�ͼ������ܡ��������ϵͳ������USERR1��USERR2��USERR3��USERR4 ��USERR5��
USERS1-5     �ṩ�����ַ������ݵĴ洢�ͼ������ܡ��������ϵͳ������USERS1��USERS2��USERS3��USERS4 ��USERS5�� 
VIEWCTR     �洢��ǰ�ӿ�����ͼ�����ġ���ֵ��UCS�����ʾ��
VIEWDIR     �洢��ǰ�ӿ��еĹ۲췽����UCS�����ʾ����
VIEWMODE     �洢��ǰ�ӿڵĹ۲�ģʽ��
VIEWSIZE     �洢��ǰ�ӿ�����ʾ����ͼ�ĸ߶ȣ���ͼ�ε�λ�������� 
VIEWTWIST     �洢�����WCS�����ĵ�ǰ�ӿڵ���ͼ��ת�Ƕȡ�
VISRETAIN     ���������ⲿ���յ�ͼ������ԡ����ƿɼ��ԡ���ɫ�����͡��߿�ʹ�ӡ��ʽ��
VPLAYEROVERRIDES     ָʾ���ڵ�ǰͼ���ӿ��Ƿ�����κξ����ӿ� (VP) ���������ͼ�㡣
VPLAYEROVERRIDESMODE     �����Ƿ���ʾ�ʹ�ӡ�벼���ӿڹ�����ͼ�����������
VPMAXIMIZEDSTATE     �洢ָʾ�Ƿ��ӿ���󻯵�ֵ��
VSBACKGROUNDS     �����Ƿ���Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ����ʾ������
VSEDGECOLOR     ���õ�ǰ�ӿ��Ӿ���ʽ�бߵ���ɫ��
VSEDGEJITTER     ����ʹֱ����ʾ��Ǧ�ʹ��������ĳ̶ȡ� 
VSEDGEOVERHANG     ���������������佻�㣬�Դﵽ�ֻ��Ч����
VSEDGES     ������ʾ���ӿ��еıߵ����͡�
VSEDGESMOOTH     ָ����ʾ�ۺ۱ߵĽǶȡ�
VSFACECOLORMODE     ������μ��������ɫ��
VSFACEHIGHLIGHT     ���Ƶ�ǰ�ӿ��в����в��ʵ����Ͼ������Ե���ʾ��
VSFACEOPACITY     ���Ƶ�ǰ�ӿ������͸���ȡ� 
VSFACESTYLE     ��������ڵ�ǰ�ӿ�����ʾ�档
VSHALOGAP     ����Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ�еĹ��μ����
VSHIDEPRECISION     ����Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ�е����غ���ɫ�ľ��ȡ�
VSINTERSECTIONCOLOR     ָ��Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ���ཻ����ߵ���ɫ��
VSINTERSECTIONEDGES     ����Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ���ཻ�ߵ���ʾ��
VSINTERSECTIONLTYPE     ����Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ�еĽ������͡�
VSISOONTOP     ��ʾӦ���ڵ�ǰ�ӿڵ��Ӿ���ʽ����ɫ���󶥲������ߡ� 
VSLIGHTINGQUALITY     ���õ�ǰ�ӿ��еĹ�Դ������
VSMATERIALMODE     ���Ƶ�ǰ�ӿ��в��ʵ���ʾ��
VSMAX     �洢��ǰ�ӿ����������Ͻǡ�
VSMIN     �洢��ǰ�ӿ����������½ǡ�
VSMONOCOLOR     ΪӦ���ڵ�ǰ�ӿڵ��Ӿ���ʽ����ĵ�ɫ��Ⱦɫ��ʾ������ɫ��
VSOBSCUREDCOLOR     ָ��Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ���ڵ������أ��ߵ���ɫ��
VSOBSCUREDEDGES     �����Ƿ���ʾ�ڵ������أ��ߡ�
VSOBSCUREDLTYPE     ָ��Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ���ڵ������أ��ߵ����͡�
VSSHADOWS     �����Ӿ���ʽ�Ƿ���ʾ��Ӱ��
VSSILHEDGES     ����Ӧ���ڵ�ǰ�ӿڵ��Ӿ���ʽ�е�ʵ����������ߵ���ʾ��
VSSILHWIDTH     ������Ϊ��λָ����ǰ�ӿ��������ߵĿ�ȡ�
VSSTATE     �򿪻�رա��Ӿ���ʽ�����ڡ�
VTDURATION     �Ժ���Ϊ��λ����ƽ����ͼ���ɵ����ޡ�
VTENABLE     ���ƺ�ʱʹ��ƽ����ͼ���ɡ� 
VTFPS     ��֡/ÿ��Ϊ��λ����ƽ����ͼ���ɵ���С�ٶȡ�
WHIPARC     ����Բ��Բ���Ƿ�ƽ����ʾ��
WHIPTHREAD     �����Ƿ�ʹ�ø��Ӵ���������߲����ٶȣ�WHIPTHREAD�Ե��������������Ч��
WINDOWAREACOLOR     ���ƴ���ѡ��ʱ͸��ѡ���������ɫ�� 
WMFBKGND     ������WindowsͼԪ�ļ� (WMF) ��ʽ�������ʱ��������ʾ��
WMFFOREGND     ������WindowsͼԪ�ļ� (WMF) ��ʽ�������ʱǰ��ɫ��ָ����ʽ��
WORLDUCS     ָʾUCS�Ƿ���WCS��ͬ��
WORLDVIEW     ȷ����ӦDVIEW��VPOINT����������������WCS��Ĭ�ϣ���������ڵ�ǰUCS��
WRITESTAT     ָʾͼ���ļ���ֻ���Ļ��ǿ�д�ġ�
WSCURRENT     �������н����з��ص�ǰ�����ռ����Ʋ��������ռ���Ϊ��ǰ�����ռ䡣
XCLIPfRadiusAME     �����ⲿ���ռ��ñ߽�Ŀɼ��ԡ�
XEDIT     ���Ƶ�ǰͼ�α�����ͼ�β���ʱ�Ƿ������λ�༭��
XFADECTL     ����������λ�༭�Ĳ��յ���ɫ�Ȱٷֱȡ�
XLOADCTL     �򿪻�ر��ⲿ���յİ�����ع��ܣ��������Ǵ򿪲��յ�ͼ�λ��Ǵ򿪸����� 
XLOADPATH     �������ڴ洢������ص��ⲿ�����ļ���ʱ������·����
XREFCTL     �����Ƿ񴴽��ⲿ������־(XLG)�ļ���
XREFNOTIFY     ���Ƹ��»�ȱ���ⲿ����֪ͨ��
XREFTYPE     ���Ƹ��Ż򸲸��ⲿ����ʱ��Ĭ�ϲ������͡�
ZOOMFACTOR     ������ǰ����󻬶�������ʱ�����ı仯�̶ȡ�
ZOOMWHEEL     ��������м�Ļ���ʱ���л�͸�����Ų����ķ��� */

#include "ArxRleEntityClass.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"

static double sfLineWeight[] = {0.00, 0.05, 0.09, 0.13, 0.15, 0.18, 0.20, 0.25, 0.30, 0.35, 0.40, 0.50, 0.53, 0.60, 0.70, 0.80, 0.90, 1.00, 1.06, 1.20, 1.40, 1.58, 2.00, 2.11};
static AcDb::LineWeight ConvertLineWeight(double fWidth)
{
	if(EqualFloat(fWidth, -1))
		return AcDb::kLnWtByLayer;
	else if(EqualFloat(fWidth, -2))
		return AcDb::kLnWtByBlock;
	else
	{
		for(int i = 0; i < 23; i ++)
		{
			if(BetweenFloat(fWidth, sfLineWeight[i], sfLineWeight[i + 1]))
				return (AcDb::LineWeight)int(RoundFloat(fWidth, sfLineWeight[i], sfLineWeight[i + 1]) * 100);
		}
	}
	return AcDb::kLnWtByLwDefault;
}

// CPt3d 3D��ṹ

CPt3d::CPt3d()
{
	x = y = z = 0;
}

CPt3d::CPt3d(const double xx, const double yy, const double zz)
{
	x = xx;
	y = yy;
	z = zz;
}

CPt3d::CPt3d(const double* xyz)
{
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
}

CPt3d::CPt3d(const complex<double> xy)
{
	x = xy.real();
	y = xy.imag();
}

CPt3d::CPt3d(const CPt3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
}

CPt3d::CPt3d(const AcGePoint2d& pt)
{
	x = pt.x;
	y = pt.y;
	z = 0;
}

CPt3d::CPt3d(const AcGePoint3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
}

CPt3d::CPt3d(const AcGeVector3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
}

CPt3d::CPt3d(bool bValid)
{
	if(!bValid)
	{
		x = INVALIDCOOR;
		y = INVALIDCOOR;
		z = INVALIDCOOR;
	}
	else
		CPt3d();
}


bool CPt3d::operator == (const CPt3d& pt) const
{
	if(CompareFloat(x, pt.x) != 0 ||
		CompareFloat(y, pt.y) != 0 ||
		CompareFloat(z, pt.z) != 0)
		return false;
	return true;
}

bool CPt3d::operator != (const CPt3d& pt) const
{
	if(CompareFloat(x, pt.x) == 0 && CompareFloat(y, pt.y) == 0 && CompareFloat(z, pt.z) == 0)
		return false;
	return true;
}

bool CPt3d::operator > (const CPt3d& pt) const
{
	int nRet = CompareFloat(x, pt.x);
	if(nRet > 0)
		return true;
	else if(nRet < 0)
		return false;
	else if(CompareFloat(y, pt.y) < 0)
		return true;
	return false;
}

bool CPt3d::operator < (const CPt3d& pt) const
{
	int nRet = CompareFloat(x, pt.x);
	if(nRet < 0)
		return true;
	else if(nRet > 0)
		return false;
	else if(CompareFloat(y, pt.y) < 0)
		return true;
	return false;
}

CPt3d CPt3d::operator = (const double* xyz)
{
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
	return *this;
}

CPt3d CPt3d::operator = (const complex<double> xy)
{
	x = xy.real();
	y = xy.imag();
	return *this;
}

CPt3d CPt3d::operator = (const CPt3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
	return *this;
}

CPt3d CPt3d::operator = (const ads_point& pt)
{
	x = pt[X];
	y = pt[Y];
	z = pt[Z];
	return *this;
}

CPt3d CPt3d::operator = (const AcGePoint2d& pt)
{
	x = pt.x;
	y = pt.y;
	z = 0;
	return *this;
}

CPt3d CPt3d::operator = (const AcGePoint3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
	return *this;
}

CPt3d CPt3d::operator = (const AcGeVector3d& pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
	return *this;
}

CPt3d CPt3d::operator + (const double* xyz)
{
	CPt3d tmp;
	tmp.x = x + xyz[0];
	tmp.y = y + xyz[1];
	tmp.z = z + xyz[2];
	return tmp;
}

CPt3d CPt3d::operator + (const complex<double> xy)
{
	CPt3d tmp;
	tmp.x = x + xy.real();
	tmp.y = y + xy.imag();
	return tmp;
}

CPt3d CPt3d::operator + (const CPt3d& pt)
{
	CPt3d tmp;
	tmp.x = x + pt.x;
	tmp.y = y + pt.y;
	tmp.z = z + pt.z;
	return tmp;
}

CPt3d CPt3d::operator + (const AcGePoint2d& pt)
{
	CPt3d tmp;
	tmp.x = x + pt.x;
	tmp.y = y + pt.y;
	tmp.z = z;
	return tmp;
}

CPt3d CPt3d::operator + (const AcGePoint3d& pt)
{
	CPt3d tmp;
	tmp.x = x + pt.x;
	tmp.y = y + pt.y;
	tmp.z = z + pt.z;
	return tmp;
}

CPt3d CPt3d::operator + (const AcGeVector3d& pt)
{
	CPt3d tmp;
	tmp.x = x + pt.x;
	tmp.y = y + pt.y;
	tmp.z = z + pt.z;
	return tmp;
}

CPt3d CPt3d::operator - (const double* xyz)
{
	CPt3d tmp;
	tmp.x = x - xyz[0];
	tmp.y = y - xyz[1];
	tmp.z = z - xyz[2];
	return tmp;
}

CPt3d CPt3d::operator - (const complex<double> xy)
{
	CPt3d tmp;
	tmp.x = x - xy.real();
	tmp.y = y - xy.imag();
	return tmp;
}

CPt3d CPt3d::operator - (const CPt3d& pt)
{
	CPt3d tmp;
	tmp.x = x - pt.x;
	tmp.y = y - pt.y;
	tmp.z = z - pt.z;
	return tmp;
}

CPt3d CPt3d::operator - (const AcGePoint2d& pt)
{
	CPt3d tmp;
	tmp.x = x - pt.x;
	tmp.y = y - pt.y;
	tmp.z = z;
	return tmp;
}

CPt3d CPt3d::operator - (const AcGePoint3d& pt)
{
	CPt3d tmp;
	tmp.x = x - pt.x;
	tmp.y = y - pt.y;
	tmp.z = z - pt.z;
	return tmp;
}

CPt3d CPt3d::operator - (const AcGeVector3d& pt)
{
	CPt3d tmp;
	tmp.x = x - pt.x;
	tmp.y = y - pt.y;
	tmp.z = z - pt.z;
	return tmp;
}

CPt3d CPt3d::operator += (const double* xyz)
{
	x += xyz[0];
	y += xyz[1];
	z += xyz[2];
	return *this;
}

CPt3d CPt3d::operator += (const complex<double> xy)
{
	x += xy.real();
	y += xy.imag();
	return *this;
}

CPt3d CPt3d::operator += (const CPt3d& pt)
{
	x += pt.x;
	y += pt.y;
	z += pt.z;
	return *this;
}

CPt3d CPt3d::operator += (const AcGePoint2d& pt)
{
	x += pt.x;
	y += pt.y;
	z = 0;
	return *this;
}

CPt3d CPt3d::operator += (const AcGePoint3d& pt)
{
	x += pt.x;
	y += pt.y;
	z += pt.z;
	return *this;
}

CPt3d CPt3d::operator += (const AcGeVector3d& pt)
{
	x += pt.x;
	y += pt.y;
	z += pt.z;
	return *this;
}

CPt3d CPt3d::operator -= (const double* xyz)
{
	x -= xyz[0];
	y -= xyz[1];
	z -= xyz[2];
	return *this;
}

CPt3d CPt3d::operator -= (const complex<double> xy)
{
	x -= xy.real();
	y -= xy.imag();
	return *this;
}

CPt3d CPt3d::operator -= (const CPt3d& pt)
{
	x -= pt.x;
	y -= pt.y;
	z -= pt.z;
	return *this;
}

CPt3d CPt3d::operator -= (const AcGePoint2d& pt)
{
	x -= pt.x;
	y -= pt.y;
	z = 0;
	return *this;
}

CPt3d CPt3d::operator -= (const AcGePoint3d& pt)
{
	x -= pt.x;
	y -= pt.y;
	z -= pt.z;
	return *this;
}

CPt3d CPt3d::operator -= (const AcGeVector3d& pt)
{
	x -= pt.x;
	y -= pt.y;
	z -= pt.z;
	return *this;
}

CPt3d CPt3d::operator * (const CPt3d& scale)
{
	CPt3d temp;
	temp.x = x * scale.x;
	temp.y = y * scale.y;
	temp.z = z * scale.z;
	return temp;
}

CPt3d CPt3d::operator / (const CPt3d& scale)
{
	CPt3d temp(*this);
	if(CompareFloat(scale.x, 0) != 0)
		temp.x = x / scale.x;
	if(CompareFloat(scale.y, 0) != 0)
		temp.y = y / scale.y;
	if(CompareFloat(scale.z, 0) != 0)
		temp.z = z / scale.z;
	return temp;
}

CPt3d CPt3d::operator *= (const CPt3d& scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	return *this;
}

CPt3d CPt3d::operator /= (const CPt3d& scale)
{
	if(CompareFloat(scale.x, 0) != 0)
		x /= scale.x;
	if(CompareFloat(scale.y, 0) != 0)
		y /= scale.y;
	if(CompareFloat(scale.z, 0) != 0)
		z /= scale.z;
	return *this;
}

CPt3d CPt3d::operator * (const double fScale)
{
	CPt3d temp;
	temp.x = x * fScale;
	temp.y = y * fScale;
	temp.z = z * fScale;
	return temp;
}

CPt3d CPt3d::operator / (const double fScale)
{
	if(CompareFloat(fScale, 0) != 0)
	{
		CPt3d temp(*this);
		temp.x = x / fScale;
		temp.y = y / fScale;
		temp.z = z / fScale;
		return temp;
	}
	return *this;
}

CPt3d CPt3d::operator *= (const double fScale)
{
	x *= fScale;
	y *= fScale;
	z *= fScale;
	return *this;
}

CPt3d CPt3d::operator /= (const double fScale)
{
	if(CompareFloat(fScale, 0) != 0)
	{
		x /= fScale;
		y /= fScale;
		z /= fScale;
	}
	return *this;
}

CPt3d CPt3d::operator * (const double* scale)
{
	CPt3d temp;
	temp.x = x * scale[0];
	temp.y = y * scale[1];
	temp.z = z * scale[2];
	return temp;
}

CPt3d CPt3d::operator / (const double* scale)
{
	CPt3d temp(*this);
	if(CompareFloat(scale[0], 0) != 0)
		temp.x = x / scale[0];
	if(CompareFloat(scale[1], 0) != 0)
		temp.y = y / scale[1];
	if(CompareFloat(scale[2], 0) != 0)
		temp.z = z / scale[2];
	return temp;
}

CPt3d CPt3d::operator *= (const double* scale)
{
	x *= scale[0];
	y *= scale[1];
	z *= scale[2];
	return *this;
}

CPt3d CPt3d::operator /= (const double* scale)
{
	if(CompareFloat(scale[0], 0) != 0)
		x /= scale[0];
	if(CompareFloat(scale[1], 0) != 0)
		y /= scale[1];
	if(CompareFloat(scale[2], 0) != 0)
		z /= scale[2];
	return *this;
}

double CPt3d::operator [] (int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		return INVALIDCOOR;
	}
}

CPt3d::operator double*() const
{
	double* xyz = new double[3];
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
	return xyz;
}

CPt3d::operator complex<double>() const
{
	complex<double> xy(x,y);
	return xy;
}

CPt3d::operator AcGePoint2d() const
{
	return AcGePoint2d(x, y);
}

CPt3d::operator AcGePoint3d() const
{
	return AcGePoint3d(x, y, z);
}

CPt3d::operator AcGeVector3d() const
{
	return AcGeVector3d(x, y, z);
}

double* CPt3d::fPtr() const
{
	double* xyz = new double[3];
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
	return xyz;
}

complex<double> CPt3d::complexDbl() const
{
	complex<double> xy(x,y);
	return xy;
}

AcGePoint2d CPt3d::aPt2() const
{
	return AcGePoint2d(x, y);
}

AcGePoint3d CPt3d::aPt() const
{
	return AcGePoint3d(x, y, z);
}

AcGeVector3d CPt3d::vPt() const
{
	return AcGeVector3d(x, y, z);
}

CString CPt3d::sPt(int index, int prec) const
{
	CString str,prc;
	prc.Format(L"%d",prec);
	prec ? prc = L"%."+prc+L"f" : prc = L"%"+prc+L"d";

	switch (index)
	{
	case 0:
		str.Format(prc,x);
		break;
	case 1:
		str.Format(prc,y);
		break;
	case 2:
		str.Format(prc,z);
		break;
	default:
		CString prcs = L"X:"+prc;
		prcs += L" Y:"+prc;
		prcs += L" Z:"+prc;
		str.Format(prcs,x,y,z);
		break;
	}
	return str;
}

const char* CPt3d::cPt(int index, int prec)
{
	return ArxRleString(sPt(index,prec)).c_ptr();
}

double CPt3d::GetX() const
{
	return x;
}

double CPt3d::GetY() const
{
	return y;
}

double CPt3d::GetZ() const
{
	return z;
}

double* CPt3d::Get() const
{
	double* xyz = new double[3];
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
	return xyz;
}

void CPt3d::SetX(const double xx)
{
	x = xx;
}

void CPt3d::SetY(const double yy)
{
	y = yy;
}

void CPt3d::SetZ(const double zz)
{
	z = zz;
}

void CPt3d::Set(const double xx, const double yy, const double zz)
{
	x = xx;
	y = yy;
	z = zz;
}

bool CPt3d::IsValid()
{
	if(CompareFloat(x, INVALIDCOOR) == 0 &&
		CompareFloat(y, INVALIDCOOR) == 0 &&
		CompareFloat(z, INVALIDCOOR) == 0)
		return false;

	return true;
};

double CPt3d::GetDistance(const CPt3d& ptEnd)
{
	return sqrt((ptEnd.x - x) * (ptEnd.x - x) +
		(ptEnd.y - y) * (ptEnd.y - y) +
		(ptEnd.z - z) * (ptEnd.z - z));
}

double CPt3d::GetDistance(const CPt3d& ptStart, const CPt3d& ptEnd)
{
	return sqrt((ptStart.x - ptEnd.x) * (ptStart.x - ptEnd.x) +
		(ptStart.y - ptEnd.y) * (ptStart.y - ptEnd.y) +
		(ptStart.z - ptEnd.z) * (ptStart.z - ptEnd.z));
}

double CPt3d::GetAngle(const CPt3d& ptEnd)
{
	if(Equal(ptEnd.x, x))
	{
		if (ptEnd.y > y)
		{
			return PI * 0.5;
		}
		else 
		{
			return PI * 1.5;
		}
	}
	else if (Equal(ptEnd.y, y))
	{
		if (ptEnd.x > x)
		{
			return 0;
		}
		else
		{
			return PI;
		}
	}
	else
	{
		double fRadiusesult = atan((y - ptEnd.y) / (x - ptEnd.x));
		if ((ptEnd.x < x) && (ptEnd.y > y))
		{
			return fRadiusesult + PI;
		}
		else if ((ptEnd.x < x) && (ptEnd.y < y))
		{
			return fRadiusesult + PI;
		}
		else if ((ptEnd.x > x) && (ptEnd.y < y))
		{
			return fRadiusesult + 2 * PI;
		}
		else 
		{
			return fRadiusesult;
		}
	}
}

double CPt3d::GetAngle(const CPt3d& ptStart, const CPt3d& ptEnd)
{
	if(Equal(ptEnd.x, ptStart.x))
	{
		if (ptEnd.y > ptStart.y)
		{
			return PI * 0.5;
		}
		else 
		{
			return PI * 1.5;
		}
	}
	else if (Equal(ptEnd.y, ptStart.y))
	{
		if (ptEnd.x > ptStart.x)
		{
			return 0;
		}
		else
		{
			return PI;
		}
	}
	else
	{
		double fRadiusesult = atan((ptStart.y - ptEnd.y) / (ptStart.x - ptEnd.x));
		if ((ptEnd.x < ptStart.x) && (ptEnd.y > ptStart.y))
		{
			return fRadiusesult + PI;
		}
		else if ((ptEnd.x < ptStart.x) && (ptEnd.y < ptStart.y))
		{
			return fRadiusesult + PI;
		}
		else if ((ptEnd.x > ptStart.x) && (ptEnd.y < ptStart.y))
		{
			return fRadiusesult + 2 * PI;
		}
		else 
		{
			return fRadiusesult;
		}
	}
}

double CPt3d::GetVectorAzimuth(const CPt3d& ptEnd) //����-PI��PI
{
	return GetVectorAzimuth(*this, ptEnd);
}

double CPt3d::GetVectorAzimuth(const CPt3d& ptStart, const CPt3d& ptEnd) //����-PI��PI
{
	if(ptStart == ptEnd)
		return 0;

	double fAngle = 0;

	if(fabs(ptEnd.x - ptStart.x) < 0.001)
	{
		if(ptEnd.y < ptStart.y) fAngle = PI * -0.5;
		else fAngle = PI * 0.5;
	}
	else if(fabs(ptEnd.y - ptStart.y) < 0.001)
	{
		if(ptEnd.x < ptStart.x) fAngle = PI;
		else fAngle = 0;
	}
	else
		fAngle = atan2(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);

	return fAngle;
}

CPt3d CPt3d::GetLineEnd(const double fLength, const double fRotation)
{
	return GetLineEnd(*this, fLength, fRotation);
}

CPt3d CPt3d::GetLineEnd(const CPt3d& ptStart, double fLength, double fRotation)
{
	//     fLength = fabs(fLength);
	//     int nMult = GetIntMultiple(fRotation, 2 * PI, 0.00000001);
	//     fRotation += -nMult * 2 * PI;//������ڵ���2*PI��ת�Ƕ�
	//     if(fRotation < 0) //�����˳ʱ����ת��ת������ʱ��Ƕ�
	//         fRotation = 2 * PI + fRotation;
	return CPt3d(ptStart.x + fLength * cos(fRotation), ptStart.y + fLength * sin(fRotation));
}

// CLayer

CLayer::CLayer()
{
	m_pLayer = new AcDbLayerTableRecord;
}

CLayer::CLayer(AcDbObjectId& objectId)
{
	if(objectId.isValid())
		m_pLayer = (AcDbLayerTableRecord*)GetRecordPtr(objectId);
}

CLayer::CLayer(const CLayer& oLayer)
{
	CLayer* pLayer = const_cast<CLayer*>(&oLayer);
	if(pLayer->isValid())
		m_pLayer = (AcDbLayerTableRecord*)GetRecordPtr(pLayer->GetObjectId());
}

CLayer::~CLayer()
{
}

AcDbObjectId CLayer::GetObjectId()
{
	if(m_pLayer != NULL)
	{
		return m_pLayer->objectId();
	}

	return AcDbObjectId();
}

void CLayer::SetName(ArxRleString lpszName)
{
	if(m_pLayer != NULL)
	{
		m_pLayer->setName(lpszName);
	}
}

void CLayer::SetColor(COLORREF clr)
{
	try
	{
		if(m_pLayer != NULL)
		{
			AcCmColor clr1;
			clr1.setColorMethod(AcCmEntityColor::kByColor);
			clr1.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
			m_pLayer->setColor(clr1);
		}
	}
	catch(...)
	{
	}
}

void CLayer::SetDescription(ArxRleString lpszDescription)
{
	if(m_pLayer != NULL)
		m_pLayer->setDescription(lpszDescription);
}

void CLayer::SetLineWidth(double fWidth)
{
	if(m_pLayer != NULL)
		m_pLayer->setLineWeight(ConvertLineWeight(fWidth));
}

void CLayer::SetOff(bool bIsOff)
{
	if(m_pLayer != NULL)
		m_pLayer->setIsOff(bIsOff);
}

void CLayer::SetLocked(bool bIsLocked)
{
	if(m_pLayer != NULL)
		m_pLayer->setIsLocked(bIsLocked);
}

void CLayer::SetFrozen(bool bIsFrozen)
{
	if(m_pLayer != NULL)
		m_pLayer->setIsFrozen(bIsFrozen);
}

void CLayer::SetHidden(bool bIsHidden)
{
	if(m_pLayer != NULL)
		m_pLayer->setIsHidden(bIsHidden);
}

void CLayer::SetPrintable(bool bIsPrint)
{
	if(m_pLayer != NULL)
		m_pLayer->setIsPlottable(bIsPrint);
}

void CLayer::SetLineType(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		try
		{
			if(m_pLayer != NULL && objectId.isValid())
			{
				m_pLayer->setLinetypeObjectId(objectId);
				// 			AcDbDatabase* pDatabase = m_pLayer->database();
				//             if(!pDatabase.isNull()()())
				//             {
				// 			    AcDbObjectId LineTypeId;
				// 			    if(_stricmp(lpszLineType, "continuous") == 0)
				// 			    {
				// 				    LineTypeId = pDatabase->getLinetypeContinuousId();
				// 				    m_pLayer->setLinetypeObjectId(LineTypeId);
				// 			    }
				// 			    else
				// 			    {
				// 				    OdDbLinetypeTablePtr pLinetypeTable = pDatabase->getLinetypeTableId().safeOpenObject(AcDb::kForRead);
				// 				    AcString strLineType(lpszLineType);
				// 				    if(pLinetypeTable->has(strLineType))
				// 				    {
				// 					    LineTypeId = pLinetypeTable->getAt(strLineType);
				// 					    m_pLayer->setLinetypeObjectId(LineTypeId);
				// 				    }
				// 			    }
				//             }
			}
		}
		catch(...)
		{
		}
	}
}

bool CLayer::isValid()
{
	if(!m_pLayer->objectId().isNull())
	{
		return m_pLayer->objectId().isValid();
	}
	return false;
}

CLayer& CLayer::operator = (AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		m_pLayer = NULL;
		m_pLayer = (AcDbLayerTableRecord*)GetRecordPtr(objectId);
	}

	return *this;
}

CLayer& CLayer::operator = (CLayer& layer)
{
	m_pLayer = (AcDbLayerTableRecord*)GetRecordPtr(layer.GetObjectId());

	return *this;
}

bool CLayer::operator == (CLayer& layer)
{
	if(m_pLayer != NULL && !layer.m_pLayer != NULL)
		return m_pLayer->objectId() == layer.m_pLayer->objectId();
	else if(m_pLayer != NULL && layer.m_pLayer != NULL)
		return true;

	return false;
}

bool CLayer::operator != (CLayer& layer)
{
	if(m_pLayer != NULL && !layer.m_pLayer != NULL)
		return m_pLayer->objectId() != layer.m_pLayer->objectId();
	else if(m_pLayer != NULL && layer.m_pLayer != NULL)
		return false;

	return true;
}

char* CLayer::GetName()
{
	if(m_pLayer != NULL)
	{
		ACHAR* lpszName;
		m_pLayer->getName(lpszName);
		return (char*)lpszName;
	}

	return "";
}

COLORREF CLayer::GetColor()
{
	if(m_pLayer != NULL)
	{
		AcCmColor color = m_pLayer->color();
		if(color.isByACI())
		{
			return acdbGetRGB(color.colorIndex());
		}
		else if(color.isByColor())
		{
			return RGB(color.red(), color.green(), color.blue());
		}
	}

	return 0;
}

// ������ʽ

CTextStyle::CTextStyle()
{
	m_pTextStyleRecord = new AcDbTextStyleTableRecord;
}

CTextStyle::CTextStyle(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		m_pTextStyleRecord = (AcDbTextStyleTableRecord*)GetRecordPtr(objectId);
	}
}

CTextStyle::CTextStyle(CTextStyle& oTextStyle)
{
	if(oTextStyle.isValid())
		m_pTextStyleRecord = oTextStyle.m_pTextStyleRecord;
}

CTextStyle::~CTextStyle()
{
}

bool CTextStyle::isValid()
{
	if(m_pTextStyleRecord != NULL)
	{
		return m_pTextStyleRecord->objectId().isValid();
	}

	return false;
}

void CTextStyle::SetName(ArxRleString lpszName)
{
	if(m_pTextStyleRecord != NULL && lpszName.GetLength() > 0)
	{
		m_pTextStyleRecord->setName(lpszName);
	}
}

void CTextStyle::SetFont(ArxRleString lpszFontName, bool bold, bool italic)
{
	try
	{
		if(m_pTextStyleRecord != NULL && lpszFontName.GetLength() > 0)
		{
			try
			{
				Charset charset = Charset::kChineseSimpCharset;
				Autodesk::AutoCAD::PAL::FontUtils::FontPitch pitch = Autodesk::AutoCAD::PAL::FontUtils::FontPitch::kDefault;
				Autodesk::AutoCAD::PAL::FontUtils::FontFamily family = Autodesk::AutoCAD::PAL::FontUtils::FontFamily::kDoNotCare;
				m_pTextStyleRecord->setFont(lpszFontName, bold, italic, charset, pitch, family);
			}
			catch(...)
			{
			}
		}
	}
	catch(...)
	{

	}
}

void CTextStyle::SetFont(ArxRleString lpszFontName, ArxRleString lpszBigFontName, bool vertical/* = false*/)
{
	try
	{
		if(m_pTextStyleRecord != NULL && lpszFontName.GetLength() > 0)
		{
			try
			{
				m_pTextStyleRecord->setFileName(lpszFontName);
				if(lpszBigFontName.GetLength() > 0)
					m_pTextStyleRecord->setBigFontFileName(lpszBigFontName);
				m_pTextStyleRecord->setIsVertical(vertical);
			}
			catch(...)
			{
			}
		}
	}
	catch(...)
	{

	}
}

void CTextStyle::SetHeight(double fHeight)
{
	if(m_pTextStyleRecord != NULL)
	{
		m_pTextStyleRecord->setTextSize(fHeight);
	}
}

void CTextStyle::SetWidthFactor(double fXScale)
{
	if(m_pTextStyleRecord != NULL)
	{
		m_pTextStyleRecord->setXScale(fXScale);
	}
}

void CTextStyle::SetOblique(double fOblique)
{
	if(m_pTextStyleRecord != NULL)
	{
		m_pTextStyleRecord->setObliquingAngle(fOblique);
	}
}

void CTextStyle::SetUpsideDown(bool bUpsideDown)
{
	if(m_pTextStyleRecord != NULL)
	{
		//m_pTextStyleRecord->setIsUpsideDown(bUpsideDown);
	}
}

void CTextStyle::SetBackward(bool bBackward)
{
	if(m_pTextStyleRecord != NULL)
	{
		//m_pTextStyleRecord->setIsBackwards(bBackward);
	}
}

char* CTextStyle::GetName()
{
	if(m_pTextStyleRecord != NULL)
	{
		char* lpszName = NULL;
		m_pTextStyleRecord->getName(AcString(lpszName));
		return lpszName;
	}
	return "";
}

double CTextStyle::GetHeight()
{
	if(m_pTextStyleRecord != NULL)
	{
		return m_pTextStyleRecord->textSize();
	}

	return 0;
}

double CTextStyle::GetWidthFactor()
{
	if(m_pTextStyleRecord != NULL)
	{
		return m_pTextStyleRecord->xScale();
	}

	return 0;
}

double CTextStyle::GetOblique()
{
	if(m_pTextStyleRecord != NULL)
	{
		return m_pTextStyleRecord->obliquingAngle();
	}

	return 0;
}

bool CTextStyle::GetUpsideDown()
{
	if(m_pTextStyleRecord != NULL)
	{
		//return m_pTextStyleRecord->isUpsideDown();
	}

	return false;
}

bool CTextStyle::GetBackward()
{
	if(m_pTextStyleRecord != NULL)
	{
		//return m_pTextStyleRecord->isBackwards();
	}

	return false;
}

void CTextStyle::GetFont(char* strFontFace, bool& bBold, bool& bItalic)
{
	if(m_pTextStyleRecord != NULL)
	{
		ACHAR* oFace;
		Adesk::Boolean blnBold = bBold, blnItalic = bItalic;
		Charset charset = Charset::kChineseSimpCharset;
		Autodesk::AutoCAD::PAL::FontUtils::FontPitch pitch = Autodesk::AutoCAD::PAL::FontUtils::FontPitch::kDefault;
		Autodesk::AutoCAD::PAL::FontUtils::FontFamily family = Autodesk::AutoCAD::PAL::FontUtils::FontFamily::kDoNotCare;
		m_pTextStyleRecord->font(oFace, blnBold, blnItalic, charset, pitch, family);
		strFontFace = (char*)oFace;
	}
}

void CTextStyle::GetFont(char* strFontName, char* strBigFontName, bool& bVertical)
{
	if(m_pTextStyleRecord != NULL)
	{
		ACHAR* oFontName;
		ACHAR* oBigFontName;
		m_pTextStyleRecord->fileName(oFontName);
		m_pTextStyleRecord->bigFontFileName(oBigFontName);
		bVertical = m_pTextStyleRecord->isVertical();
		strFontName = (char*)oFontName;
		strBigFontName = (char*)oBigFontName;
	}
}

int CTextStyle::GetFontType() const
{
	if(m_pTextStyleRecord != NULL)
	{
		if(m_pTextStyleRecord->isShapeFile())
		{
			ACHAR* oBigFontName;
			m_pTextStyleRecord->bigFontFileName(oBigFontName);
			if(oBigFontName == NULL)
				return 2;
			return 3;
		}
		ACHAR* oFace;
		Adesk::Boolean bBold, bItacil;
		Charset charset = Charset::kChineseSimpCharset;
		Autodesk::AutoCAD::PAL::FontUtils::FontPitch pitch = Autodesk::AutoCAD::PAL::FontUtils::FontPitch::kDefault;
		Autodesk::AutoCAD::PAL::FontUtils::FontFamily family = Autodesk::AutoCAD::PAL::FontUtils::FontFamily::kDoNotCare;
		m_pTextStyleRecord->font(oFace, bBold, bItacil, charset, pitch, family);
		char* lpszName = (char*)oFace;
		int len = strlen(lpszName);
		for(int i = 0; i < len; i ++)
		{
			if(!__isascii(lpszName+i))
				return 1;
		}

		return 0;
	}
	return -1;
}

AcDbObjectId CTextStyle::GetObjectId()
{
	if(m_pTextStyleRecord != NULL)
	{
		return m_pTextStyleRecord->objectId();
	}

	return AcDbObjectId();
}

// �����ʽ
#include "DbTableStyle.h"
CTableStyle::CTableStyle()
{
	m_pTableStyle = new AcDbTableStyle;
}

CTableStyle::CTableStyle(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
		m_pTableStyle = (AcDbTableStyle*)obj;
	}
}

CTableStyle::CTableStyle(CTableStyle& oTableStyle)
{
	if(!oTableStyle.m_pTableStyle != NULL)
		m_pTableStyle = oTableStyle.m_pTableStyle;
}

CTableStyle::~CTableStyle()
{
}

bool CTableStyle::isValid()
{
	if(m_pTableStyle != NULL)
	{
		return m_pTableStyle != NULL;
	}

	return false;
}

void CTableStyle::SetName(ArxRleString lpszName)
{
	if(m_pTableStyle != NULL && lpszName.GetLength() > 0)
	{
		m_pTableStyle->setName(lpszName);
	}
}

void CTableStyle::SetFlowDirection(bool bFlow)
{
	if(m_pTableStyle != NULL)
	{
		m_pTableStyle->setFlowDirection((AcDb::FlowDirection)bFlow);
	}
}

void CTableStyle::SetTextStyle(CTableStyle* pTextStyle)
{
	if(m_pTableStyle != NULL && pTextStyle != NULL)
	{
		try
		{
			m_pTableStyle->setTextStyle(pTextStyle->GetObjectId());
		}
		catch(...)
		{
		}
	}
}

void CTableStyle::SetTextHeight(double fHeight)
{
	if(m_pTableStyle != NULL)
	{
		m_pTableStyle->setTextHeight(fHeight);
	}
}

void CTableStyle::CreateCellStyle(ArxRleString lpszName)
{
	if(m_pTableStyle != NULL)
	{
		m_pTableStyle->createCellStyle(lpszName);
	}
}

void CTableStyle::SetRotation(double fRotation, ArxRleString lpszCellType)
{
	if(m_pTableStyle != NULL)
	{
		if(lpszCellType.GetLength() > 0)
			m_pTableStyle->setRotation(fRotation, lpszCellType);
		else
		{
			AcStringArray AcStrArray;
			m_pTableStyle->getCellStyles(AcStrArray);
			for(int i = 0; i < AcStrArray.length(); i ++)
				m_pTableStyle->setRotation(fRotation, AcStrArray[i]);
		}
	}
}

void CTableStyle::SetMargin(ArxMargin eMargin, double fMargin, ArxRleString lpszCellStyle)
{
	if(m_pTableStyle != NULL)
	{
		if(lpszCellStyle.GetLength() > 0)
			m_pTableStyle->setMargin((AcDb::CellMargin)eMargin, fMargin, lpszCellStyle);
		else
		{
			AcStringArray AcStrArray;
			m_pTableStyle->getCellStyles(AcStrArray);
			for(int i = 0; i < AcStrArray.length(); i ++)
				m_pTableStyle->setMargin((AcDb::CellMargin)eMargin, fMargin, AcStrArray[i]);
		}
	}
}

char* CTableStyle::GetName()
{
	if(m_pTableStyle != NULL)
	{
		ACHAR* szName;
		m_pTableStyle->getName(szName);
		return (char*)szName;
	}
	return "";
}

CTextStyle CTableStyle::GetTextStyle()
{
	if(m_pTableStyle != NULL)
	{
		try
		{
			return AcDbObjectId(m_pTableStyle->textStyle());
		}
		catch(...)
		{
		}
	}
	return AcDbObjectId();
}

double CTableStyle::GetTextHeight()
{
	if(m_pTableStyle != NULL)
	{
		return m_pTableStyle->textHeight();
	}

	return 0;
}

double CTableStyle::GetRotation(ArxRleString lpszCellStyle)
{
	if(m_pTableStyle != NULL && lpszCellStyle.GetLength() > 0)
	{
		return m_pTableStyle->rotation(lpszCellStyle);
	}

	return 0;
}

bool CTableStyle::GetFlowDirection()
{
	if(m_pTableStyle != NULL)
	{
		return (m_pTableStyle->flowDirection() == AcDb::kBtoT);
	}

	return false;
}

AcDbObjectId CTableStyle::GetObjectId()
{
	if(m_pTableStyle != NULL)
	{
		return m_pTableStyle->objectId();
	}

	return AcDbObjectId();
}

// ���¼

CBlockRecord::CBlockRecord()
{
	m_pBlockRecord = new AcDbBlockTableRecord;
}

CBlockRecord::CBlockRecord(AcDbObjectId& objectId)
{
	if(!m_pBlockRecord->objectId().isNull())
		m_pBlockRecord = NULL;
	if(objectId.isValid())
		m_pBlockRecord = (AcDbBlockTableRecord*)GetRecordPtr(objectId);
}

CBlockRecord::CBlockRecord(CBlockRecord& oBlockRcd)
{
	if(!m_pBlockRecord->objectId().isNull())
		m_pBlockRecord = NULL;
	if(!oBlockRcd.m_pBlockRecord->objectId().isNull())

		m_pBlockRecord = oBlockRcd.m_pBlockRecord;
}

CBlockRecord::CBlockRecord(ArxRleString lpszName)
{

}

CBlockRecord::~CBlockRecord()
{
}

CBlockRecord& CBlockRecord::operator = (CBlockRecord& record)
{
	if(record.isValid())
	{
		if(!m_pBlockRecord->objectId().isNull())
			m_pBlockRecord = NULL;

		m_pBlockRecord = record.m_pBlockRecord;
	}
	return *this;
}

CBlockRecord& CBlockRecord::operator = (AcDbObjectId& objectId)
{
	if(objectId.isValid())
		m_pBlockRecord = (AcDbBlockTableRecord*)GetRecordPtr(objectId);
	return *this;
}

void CBlockRecord::SetName(ArxRleString lpszName)
{
	if(!m_pBlockRecord->objectId().isNull() && lpszName.GetLength() > 0)
		m_pBlockRecord->setName(lpszName);
}

void CBlockRecord::SetOrigin(CPt3d pt)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		m_pBlockRecord->setOrigin(AcGePoint3d(pt.x, pt.y, pt.z));
	}
}

bool CBlockRecord::LoadFile(ArxRleString lpszPathName)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		if(lpszPathName.GetLength() > 0)
		{
			m_pBlockRecord->setPathName(lpszPathName);
			return true;
		}
	}

	return false;
}

bool CBlockRecord::AppendEntity(CEntity* pEntity)
{
	try
	{
		if(!m_pBlockRecord->objectId().isNull() && !pEntity->isNull())
		{
			AcDbObjectId objectId = pEntity->getent()->objectId();
			m_pBlockRecord = (AcDbBlockTableRecord*)GetRecordPtr(objectId);
			return true;
		}
	}
	catch(...)
	{
	}

	return false;
}

void CBlockRecord::SetComments(ArxRleString lpszComment)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		m_pBlockRecord->setComments(lpszComment);
	}
}

void CBlockRecord::SetLayout(CLayout* pLayout)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		m_pBlockRecord->setLayoutId(pLayout->GetObjectId());
	}
}

void CBlockRecord::SetBlockScaling(bool bAny)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		m_pBlockRecord->setBlockScaling(AcDbBlockTableRecord::BlockScaling(bAny));
	}
}

void CBlockRecord::SetExplodable(bool bExplodable)
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		m_pBlockRecord->setExplodable(bExplodable);
	}
}

bool CBlockRecord::Explodable()
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		return m_pBlockRecord->explodable();
	}

	return false;
}

char* CBlockRecord::GetName()
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		ACHAR* szName;
		m_pBlockRecord->getName(szName);
		return (char*)szName;
	}

	return "";
}

AcDbObjectId CBlockRecord::GetObjectId()
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		return m_pBlockRecord->objectId();
	}
	return AcDbObjectId();
}

bool CBlockRecord::isValid()
{
	if(!m_pBlockRecord->objectId().isNull())
	{
		return m_pBlockRecord->objectId().isValid();
	}

	return false;
}

// ��ע

CDimensionStyle::CDimensionStyle()
{
	m_pDimensionStyle = new AcDbDimStyleTableRecord;
}

CDimensionStyle::CDimensionStyle(AcDbObjectId& objectId)
{
	if(objectId.isValid())
		m_pDimensionStyle = (AcDbDimStyleTableRecord*)GetRecordPtr(objectId);
}

CDimensionStyle::CDimensionStyle(CDimensionStyle& oDimStyle)
{
	if(!m_pDimensionStyle->objectId().isNull())
		m_pDimensionStyle = NULL;

	if(oDimStyle.isValid())
		m_pDimensionStyle = oDimStyle.m_pDimensionStyle;
}

CDimensionStyle::~CDimensionStyle()
{
}

CDimensionStyle& CDimensionStyle::operator = (AcDbObjectId& objectId)
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle = NULL;
	}
	if(objectId.isValid())
		m_pDimensionStyle = (AcDbDimStyleTableRecord*)GetRecordPtr(objectId);
	return *this;
}

CDimensionStyle& CDimensionStyle::operator = (CDimensionStyle& style)
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle = NULL;
	}
	if(style.isValid())
		m_pDimensionStyle = style.m_pDimensionStyle;
	return *this;
}

bool CDimensionStyle::operator == (CDimensionStyle& dim)
{
	if(!m_pDimensionStyle->objectId().isNull() && !dim.m_pDimensionStyle->objectId().isNull())
		return m_pDimensionStyle->objectId() == dim.m_pDimensionStyle->objectId();
	else if(m_pDimensionStyle->objectId().isNull() && dim.m_pDimensionStyle->objectId().isNull())
		return true;

	return false;
}

bool CDimensionStyle::operator != (CDimensionStyle& dim)
{
	if(!m_pDimensionStyle->objectId().isNull() && !dim.m_pDimensionStyle->objectId().isNull())
		return m_pDimensionStyle->objectId() != dim.m_pDimensionStyle->objectId();
	else if(m_pDimensionStyle->objectId().isNull() && dim.m_pDimensionStyle->objectId().isNull())
		return false;

	return true;
}

bool CDimensionStyle::isValid()
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		return m_pDimensionStyle->objectId().isValid();
	}
	return false;
}

void CDimensionStyle::SetName(ArxRleString lpszName)
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setName(lpszName);
	}
}

char* CDimensionStyle::GetName()
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		ACHAR* szName;
		m_pDimensionStyle->getName(szName);
		return (char*)szName;
	}

	return "";
}

void CDimensionStyle::SetArrow(ArxRleString lpszName)		//��ͷ��ʽ
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setDimsah(false);
		m_pDimensionStyle->setDimblk(lpszName);
	}
}

void CDimensionStyle::SetArrow(ArxRleString lpszName1, ArxRleString lpszName2)		//��ͷ1��ʽ,��ͷ2��ʽ
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setDimsah(true);
		if(lpszName1.GetLength() > 0)
			m_pDimensionStyle->setDimblk1(lpszName1);
		if(lpszName2.GetLength() > 0)
			m_pDimensionStyle->setDimblk2(lpszName2);
	}
}

void CDimensionStyle::SetDimasz(double fSize)
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setDimasz(fSize);
	}
}

void CDimensionStyle::SetDimzin(byte nBits)
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setDimzin(nBits);
	}
}

AcDbObjectId CDimensionStyle::GetObjectId()
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		return m_pDimensionStyle->objectId();
	}

	return AcDbObjectId();
}

// �û�����ϵ

CUcsRecord::CUcsRecord()
{
	m_pUcsRecord = new AcDbUCSTableRecord;
}

CUcsRecord::CUcsRecord(AcDbObjectId& objectId)
{
	if(objectId.isValid())
		m_pUcsRecord = (AcDbUCSTableRecord*)GetRecordPtr(objectId);
}

CUcsRecord::CUcsRecord(CUcsRecord& oUcsRcd)
{
	m_pUcsRecord = oUcsRcd.m_pUcsRecord;
}

CUcsRecord::~CUcsRecord()
{
}

bool CUcsRecord::isValid()
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		return m_pUcsRecord->objectId().isValid();
	}
	return false;
}

void CUcsRecord::SetName(ArxRleString lpszName)
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		m_pUcsRecord->setName(lpszName);
	}
}

char* CUcsRecord::GetName()
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		ACHAR* szName;
		m_pUcsRecord->getName(szName);
		return (char*)szName;
	}

	return "";
}

void CUcsRecord::SetOrigin(CPt3d ptPosition)
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		m_pUcsRecord->setOrigin(AcGePoint3d(ptPosition.x, ptPosition.y, ptPosition.z));
	}
}

void CUcsRecord::SetAxis(CPt3d xAxis, CPt3d yAxis)
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		m_pUcsRecord->setXAxis(AcGeVector3d(xAxis.x, xAxis.y, xAxis.z));
		m_pUcsRecord->setYAxis(AcGeVector3d(yAxis.x, yAxis.y, yAxis.z));
	}
}

void CUcsRecord::SetUcsBaseOrigin(CPt3d ptOrigin)
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		m_pUcsRecord->setUcsBaseOrigin(AcGePoint3d(ptOrigin.x, ptOrigin.y, ptOrigin.z), AcDb::kNonOrthoView);
	}
}

CPt3d CUcsRecord::GetUcsBaseOrigin()
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		return m_pUcsRecord->ucsBaseOrigin(AcDb::kNonOrthoView);
	}
	return CPt3d(false);
}

CPt3d CUcsRecord::GetOrigin()
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		return m_pUcsRecord->origin();
	}

	return CPt3d(false);
}

AcDbObjectId CUcsRecord::GetObjectId()
{
	if(!m_pUcsRecord->objectId().isNull())
	{
		return m_pUcsRecord->objectId();
	}

	return AcDbObjectId();
}

// ͼԪ����

CEntity::CEntity()
{
	m_pEntity = NULL;
}

CEntity::CEntity(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CEntity::CEntity(const CEntity& oEntity)
{
	m_pEntity = GetEntPtr(oEntity.m_pEntity->objectId());
}

CEntity::~CEntity()
{
}

bool CEntity::isNull() const
{
	if(m_pEntity == NULL)
		return true;

	return false;
}

AcDbEntity* CEntity::getent() const
{
	return m_pEntity;
}

void CEntity::setent(AcDbObject* pEnt)
{
	m_pEntity = (AcDbEntity*)pEnt;
}

void CEntity::addToSpace()
{
	if(!isNull())
	{
		AcDbEntity* ent = (AcDbEntity*)m_pEntity->clone();
		ent->setDatabaseDefaults();
		ArxRleUtils::transformToWcs(ent, ARXRLEDB);
		ArxRleUtils::addToCurrentSpace(ent, ARXRLEDB);
	}
}

void CEntity::addToSpaceAndClose()
{
	if(!isNull())
	{
		AcDbEntity* ent = (AcDbEntity*)m_pEntity->clone();
		ent->setLayer(GetCurLayer());
		ent->setDatabaseDefaults();
		ArxRleUtils::transformToWcs(ent, ARXRLEDB);
		ArxRleUtils::addToCurrentSpaceAndClose(ent, ARXRLEDB);
	}
}

COLORREF CEntity::getColor() const
{
	if(m_pEntity != NULL)
	{
		AcCmColor clr = m_pEntity->color();
		if(clr.isByColor())
			return RGB(clr.red(),clr.green(),clr.blue());
	}

	return 0;
}

void CEntity::setColor(COLORREF clr)
{
	if(m_pEntity != NULL)
	{
		AcCmColor color;
		color.setColorMethod(AcCmEntityColor::kByColor);
		color.setRGB(GetRValue(clr),GetGValue(clr),GetBValue(clr));
		m_pEntity->setColor(color);
	}
}

int CEntity::getColorIndex() const
{
	if(m_pEntity != NULL)
		return m_pEntity->colorIndex();

	return 0;
}

void CEntity::setColorIndex(int aci)
{
	if(m_pEntity != NULL)
		m_pEntity->setColorIndex(aci);
}

ArxRleString CEntity::getLayer() const
{
	if(m_pEntity != NULL)
		return m_pEntity->layer();

	return "";
}

void CEntity::setLayer(ArxRleString name)
{
	if(m_pEntity != NULL)
		m_pEntity->setLayer(name);
}

AcDbObjectId CEntity::getLayerId() const
{
	if(m_pEntity != NULL)
		return m_pEntity->layerId();

	return AcDbObjectId();
}

void CEntity::setLayerId(AcDbObjectId id)
{
	if(m_pEntity != NULL)
		m_pEntity->setLayer(id);
}

ArxRleString CEntity::getLineType() const
{
	if(m_pEntity != NULL)
		return m_pEntity->linetype();

	return "";
}

void CEntity::setLineType(ArxRleString lt)
{
	if(m_pEntity != NULL)
		m_pEntity->setLinetype(lt);
}

AcDbObjectId CEntity::getLineTypeId() const
{
	if(m_pEntity != NULL)
		return m_pEntity->linetypeId();

	return AcDbObjectId();
}

void CEntity::setLineTypeId(AcDbObjectId id)
{
	if(m_pEntity != NULL)
		m_pEntity->setLinetype(id);
}

double CEntity::getLineTypeScale() const
{
	if(m_pEntity != NULL)
		return m_pEntity->linetypeScale();

	return 1;
}

void CEntity::setLineTypeScale(double lts)
{
	if(m_pEntity != NULL)
		m_pEntity->setLinetypeScale(lts);
}

AcDb::LineWeight CEntity::getLineWeight() const
{
	if(m_pEntity != NULL)
		return m_pEntity->lineWeight();

	return AcDb::kLnWt000;
}

void CEntity::setLineWeight(AcDb::LineWeight lw)
{
	if(m_pEntity != NULL)
		m_pEntity->setLineWeight(lw);
}

// ��

CPointEnt::CPointEnt()
{
	m_pEntity = new AcDbPoint;
	x=y=z=0;
}

CPointEnt::CPointEnt(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		m_pEntity = GetEntPtr(objectId);
		AcDbPoint* pAcPt = (AcDbPoint*)m_pEntity;
		AcGePoint3d pt = pAcPt->position();
		x = pt.x; y = pt.y; z = pt.z;
	}
	else
		x=y=z=0;
}

CPointEnt::CPointEnt(CPointEnt& oPoint)
{
	if(!oPoint.isNull())
	{
		m_pEntity = oPoint.getent();
		AcDbPoint* pAcPt = (AcDbPoint*)m_pEntity;
		AcGePoint3d pt = pAcPt->position();
		x = pt.x; y = pt.y; z = pt.z;
	}
	else
		x=y=z=0;
}

CPointEnt::~CPointEnt()
{
	x=y=z=0;
}

void CPointEnt::SetPoint(CPt3d pt)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(pt.x, pt.y, pt.z));
		x = pt.x; y = pt.y; z = pt.z;
	}
}

void CPointEnt::SetPoint(AcGePoint3d pt)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(pt);
		x = pt.x; y = pt.y; z = pt.z;
	}
}

void CPointEnt::SetPoint(AcGePoint2d pt)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(pt.x, pt.y, 0));
		x = pt.x; y = pt.y; z = 0;
	}
}

void CPointEnt::SetPoint(double fX, double fY, double fZ)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(fX, fY, fZ));
		x = fX; y = fY; z = fZ;
	}
}

void CPointEnt::SetX(double fX)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(fX, y, z));
		x = fX;
	}
}

void CPointEnt::SetY(double fY)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(x, fY, z));
		y = fY;
	}
}

void CPointEnt::SetZ(double fZ)
{
	if(!isNull())
	{
		AcDbPoint* pEntity = (AcDbPoint*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(x, y, fZ));
		z = fZ;
	}
}

// ֱ��

CLine::CLine()
{
	m_pEntity = new AcDbLine;
}

CLine::CLine(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CLine::CLine(CLine& oLine)
{
	m_pEntity = GetEntPtr(oLine.m_pEntity->objectId());
}

CLine::~CLine()
{
}

void CLine::SetPoint(CPt3d ptStart, CPt3d ptEnd)
{
	if(!isNull())
	{
		AcDbLine* pEntity = (AcDbLine*)m_pEntity;
		pEntity->setStartPoint(AcGePoint3d(ptStart.x, ptStart.y, ptStart.z));
		pEntity->setEndPoint(AcGePoint3d(ptEnd.x, ptEnd.y, ptEnd.z));
	}
}

void CLine::Set(CPt3d ptStart, double fLength, double fRotation)
{
	if(!isNull())
	{
		AcDbLine* pEntity = (AcDbLine*)m_pEntity;
		pEntity->setStartPoint(AcGePoint3d(ptStart.x, ptStart.y, ptStart.z));
		CPt3d ptEnd = CPt3d::GetLineEnd(ptStart, fLength, fRotation);
		pEntity->setEndPoint(AcGePoint3d(ptEnd.x, ptEnd.y, ptEnd.z));
	}
}

void CLine::GetPoint(CPt3d& ptStart, CPt3d& ptEnd)
{
	if(!isNull())
	{
		AcDbLine* pEntity = (AcDbLine*)m_pEntity;
		AcGePoint3d pt;
		pEntity->getStartPoint(pt);
		ptStart = pt;
		pEntity->getEndPoint(pt);
		ptEnd = pt;
	}
}

// CPolyline  �����ͼԪ

CPolyline::CPolyline()
{
	m_pEntity = new AcDbPolyline;
}

CPolyline::CPolyline(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CPolyline::CPolyline(CPolyline& oPolyLine)
{
	m_pEntity = GetEntPtr(oPolyLine.m_pEntity->objectId());
}

CPolyline::~CPolyline()
{
}

void CPolyline::AddPoint(CPt3dArray arrPoint)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		if(arrPoint.size() < 2) return;
		int nPtCnt = arrPoint.size();

		for(int i=0;i<nPtCnt;i++)
			pPolyline->addVertexAt(i, AcGePoint2d(arrPoint[i].x, arrPoint[i].y));
	}
}

void CPolyline::AddPoint(AcGePoint3dArray arrPoint)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		if(arrPoint.length() < 2) return;
		int nPtCnt = arrPoint.length();

		for(int i=0;i<nPtCnt;i++)
			pPolyline->addVertexAt(i, AcGePoint2d(arrPoint[i].x, arrPoint[i].y));
	}
}

long CPolyline::AddPoint(CPt3d ptPosition)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		unsigned int nIndex = pPolyline->numVerts();
		pPolyline->addVertexAt(nIndex, AcGePoint2d(ptPosition.x, ptPosition.y));

		return nIndex;
	}

	return -1;
}

void CPolyline::InsertPoint(long nIndex, CPt3d ptPosition)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint2d pt;
		pt.set(ptPosition.x, ptPosition.y);
		pPolyline->addVertexAt(nIndex, pt);
	}
}

long CPolyline::AddLine(CPt3d ptStart, double fLength, double fRotation)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		unsigned int nIndex = pPolyline->numVerts();
		pPolyline->addVertexAt(nIndex++, AcGePoint2d(ptStart.x, ptStart.y));
		CPt3d ptEnd = CPt3d(ptStart.x + fLength * cos(fRotation), ptStart.y + fLength * sin(fRotation),ptStart.z);
		pPolyline->addVertexAt(nIndex, AcGePoint2d(ptEnd.x, ptEnd.y));

		return nIndex;
	}

	return -1;
}

long CPolyline::AddArc(CPt3d ptPosition, double fCentralAngle)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		unsigned int nIndex = pPolyline->numVerts();
		pPolyline->addVertexAt(nIndex, AcGePoint2d(ptPosition.x, ptPosition.y),tan(fCentralAngle / 4));

		return nIndex;
	}

	return -1;
}

void CPolyline::SetIsClosed(bool bIsClosed)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->setClosed(bIsClosed);
	}
}

bool CPolyline::IsClosed() const
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->isClosed();
		return true;
	}

	return false;
}

void CPolyline::SetLineWidth(double fWidth)
{
	if(!isNull())
	{
		if(CompareFloat(fWidth, -1) == 0)
			m_pEntity->setLineWeight(AcDb::kLnWtByLayer);
		else if(CompareFloat(fWidth, -2) == 0)
			m_pEntity->setLineWeight(AcDb::kLnWtByBlock);
		else if(CompareFloat(fWidth, 0) >= 0)
		{
			AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
			pPolyline->setConstantWidth(fWidth);
		}
		else
			m_pEntity->setLineWeight(AcDb::kLnWtByLwDefault);
	}
}

double CPolyline::GetLineWidth() const
{
	if(!isNull())
	{
		AcDb::LineWeight lw = m_pEntity->lineWeight();
		if(lw == AcDb::kLnWtByLayer)
			return -1;
		else if(lw == AcDb::kLnWtByBlock)
			return -2;
		else if(lw == AcDb::kLnWtByLwDefault)
			return -3;
		else
		{
			AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
			double fWidth = 0;
			pPolyline->getConstantWidth(fWidth);
			return fWidth;
		}
	}

	return 0.0f;
}

void CPolyline::SetWidthAt(long nIndex, double fStartWidth, double fEndWidth)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		if(nIndex < (long)pPolyline->numVerts())
			pPolyline->setWidthsAt(nIndex, fStartWidth, fEndWidth);
	}
}

int CPolyline::GetPointNum() const
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		return pPolyline->numVerts();
	}
	return -1;
}

CPt3dArray CPolyline::GetPoint()
{
	CPt3dArray arrPoint;
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		int nNum = pPolyline->numVerts();
		for(int i = 0; i < nNum; i ++)
		{
			AcGePoint3d pt;
			pPolyline->getPointAt(i, pt);
			arrPoint.push_back(CPt3d(pt.x,pt.y,pt.z));
		}
	}

	return arrPoint;
}

bool CPolyline::HasArc()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->hasBulges();
		return true;
	}

	return false;

}

void CPolyline::SetPointAt(long nIndex, CPt3d ptNew)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->setPointAt(nIndex, AcGePoint2d(ptNew.x, ptNew.y));
	}
}

void CPolyline::ClearPoint()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->reset(true,0);
	}
}

void CPolyline::RemovePointAt(long nIndex)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->removeVertexAt(nIndex);
	}
}

double CPolyline::GetArea()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		if(pPolyline->isClosed())
		{
			double fArea;
			pPolyline->getArea(fArea);
			return fArea;
		}
	}

	return -1;
}

CPt3d CPolyline::GetStartPoint()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint3d oPoint;
		pPolyline->getStartPoint(oPoint);
		return CPt3d(oPoint.x,oPoint.y,oPoint.z)/* - g_vectOffset*/;
	}
	return CPt3d(0,0,0);
}

CPt3d CPolyline::GetEndPoint()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint3d oPoint;
		pPolyline->getEndPoint(oPoint);
		return CPt3d(oPoint.x,oPoint.y,oPoint.z)/* - g_vectOffset*/;
	}
	return CPt3d(0,0,0);
}

double CPolyline::GetDistAtPoint(CPt3d ptOnCurve)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint3d oPoint(ptOnCurve.x, ptOnCurve.y, ptOnCurve.z);
		double fDist = 0;
		pPolyline->getDistAtPoint(oPoint, fDist);
		return fDist;
	}
	return -1;
}

CPt3d CPolyline::GetPointAtDist(double fDistance)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint3d oPoint;
		pPolyline->getPointAtDist(fDistance, oPoint);
		CPt3d ptOnCurve = CPt3d(oPoint.x,oPoint.y,oPoint.z);

		return ptOnCurve;
	}

	return CPt3d(0,0,0);
}

double CPolyline::GetLength()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		AcGePoint3d oPoint;
		pPolyline->getEndPoint(oPoint);
		double fDist = 0;
		pPolyline->getDistAtPoint(oPoint, fDist);
		return fDist;
	}
	return -1;
}

void CPolyline::SetElevation(double fElevation)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->setElevation(fElevation);
	}
}

double CPolyline::GetElevation()
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		return pPolyline->elevation();
	}

	return 0;
}

void CPolyline::AddRectangular(CPt3d& oBeginPt, CPt3d& oEndPt)
{
	if(!isNull())
	{
		AcDbPolyline* pPolyline = (AcDbPolyline*)m_pEntity;
		pPolyline->addVertexAt(0, AcGePoint2d(oBeginPt.x,oBeginPt.y));
		pPolyline->addVertexAt(1, AcGePoint2d(oBeginPt.x,oEndPt.y));
		pPolyline->addVertexAt(2, AcGePoint2d(oEndPt.x,oEndPt.y));
		pPolyline->addVertexAt(3, AcGePoint2d(oEndPt.x,oBeginPt.y));
		pPolyline->addVertexAt(4, AcGePoint2d(oBeginPt.x,oBeginPt.y));
	}
}

// Բ

#define S(a, b, c) (a.x- c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x)
static double Y_Coordinates(double x,double y,double k,double x0)
{
	return k * x0 - k * x + y;
}
//dRadius������ʾԲ�����ҵ��ǲ࣬������
static bool Circle_Center(CPt3d p1,CPt3d p2,double dRadius, CPt3d& center)
{
	if(CompareFloat(p2.x, p1.x) == 0)//x������ͬ
	{
		center.y = (p1.y + p2.y) * 0.5;
		if((CompareFloat(p2.y, p1.y) < 0 && dRadius > 0) ||//�뾶�����㣬ȡֱ�߷�����Ҳ�Բ��
			(CompareFloat(p2.y, p1.y) > 0 && dRadius < 0))//�뾶С���㣬ȡֱ�߷�������Բ��
			center.x = p1.x + sqrt(dRadius * dRadius -(p1.y - p2.y) * (p1.y - p2.y) / 4.0);
		else
			center.x = p1.x - sqrt(dRadius * dRadius -(p1.y - p2.y) * (p1.y - p2.y) / 4.0);
		return true;
	}
	else if(CompareFloat(p2.y, p1.y) == 0)//y������ͬ
	{
		center.x = (p1.x + p2.x) * 0.5;
		if((CompareFloat(p2.x, p1.x) < 0 && dRadius > 0) ||//�뾶�����㣬ȡֱ�߷�����Ҳ�Բ��
			(CompareFloat(p2.x, p1.x) > 0 && dRadius < 0))//�뾶С���㣬ȡֱ�߷�������Բ��
			center.y = p1.y + sqrt(dRadius * dRadius -(p1.x - p2.x) * (p1.x - p2.x) / 4.0);
		else
			center.y = p2.y - sqrt(dRadius * dRadius -(p1.x - p2.x) * (p1.x - p2.x) / 4.0);
		return true;
	}
	else
	{
		double k_verticle = 0.0;
		double mid_x = 0.0,mid_y = 0.0;
		double a = 1.0;
		double b = 1.0;
		double c = 1.0;
		k_verticle = (p1.x - p2.x) / (p2.y - p1.y);
		mid_x = (p1.x + p2.x) / 2.0;
		mid_y = (p1.y + p2.y) / 2.0;
		a = 1.0 + k_verticle * k_verticle;
		b = -2 * mid_x - k_verticle * k_verticle * (p1.x + p2.x);
		c = mid_x * mid_x + k_verticle * k_verticle * (p1.x + p2.x) * (p1.x + p2.x) / 4.0 - 
			(dRadius * dRadius - ((mid_x - p1.x) * (mid_x - p1.x) + (mid_y - p1.y) * (mid_y - p1.y)));

		CPt3d center1, center2;
		center1.x = (-1.0 * b + sqrt(b * b -4 * a * c)) / (2 * a);
		center2.x = (-1.0 * b - sqrt(b * b -4 * a * c)) / (2 * a);
		center1.y = Y_Coordinates(mid_x,mid_y,k_verticle,center1.x);
		center2.y = Y_Coordinates(mid_x,mid_y,k_verticle,center2.x);

		double x0 = (p1.y * p2.x - p2.y * p1.x) / (p1.y - p2.y); //��������ֱ��X�ؾ�
		double fAngle = atan4(p2.y - p1.y, p2.x - p1.x); //��������ֱ�ߵ�б��
		double fAngle1 = atan4(center1.y, center1.x - x0); //��������ֱ�ߵ�y=0���Բ��1���ӵ�ֱ�ߵ�б��
		double fAngle2 = atan4(center2.y, center2.x - x0); //��������ֱ�ߵ�y=0���Բ��2���ӵ�ֱ�ߵ�б��
		if(CompareFloat(fAngle1, fAngle2) == 0)
		{
			center.x = (center1.x + center2.x) * 0.5;
			center.y = (center1.y + center2.y) * 0.5;
			return true;
		}
		double fS1 = p1.y * p1.y + (p1.x - x0) * (p1.x - x0);//ptStart�㵽(x0,0)�ľ���ƽ��
		double fS2 = p2.y * p2.y + (p2.x - x0) * (p2.x - x0);//ptEnd�㵽(x0,0)�ľ���ƽ��
		if(CompareFloat(fS1, fS2) < 0)//�ж����㷽��
		{
			if((CompareFloat(fAngle1, fAngle) < 0 && dRadius > 0) ||
				(CompareFloat(fAngle1, fAngle) > 0 && dRadius < 0))
			{
				center.x = center1.x;
				center.y = center1.y;
				return true;
			}
			else if((CompareFloat(fAngle2, fAngle) < 0 && dRadius > 0) ||
				(CompareFloat(fAngle2, fAngle) > 0 && dRadius < 0))
			{
				center.x = center2.x;
				center.y = center2.y;
				return true;
			}
		}
		else
		{
			if((CompareFloat(fAngle1, fAngle) < 0 && dRadius < 0) ||
				(CompareFloat(fAngle1, fAngle) > 0 && dRadius > 0))
			{
				center.x = center1.x;
				center.y = center1.y;
				return true;
			}
			else if((CompareFloat(fAngle2, fAngle) < 0 && dRadius < 0) ||
				(CompareFloat(fAngle2, fAngle) > 0 && dRadius > 0))
			{
				center.x = center2.x;
				center.y = center2.y;
				return true;
			}
		}
	}
	return false;
}

CCircle::CCircle()
{
	m_pEntity = new AcDbCircle;
}

CCircle::CCircle(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CCircle::CCircle(CCircle& oCircle)
{
	m_pEntity = GetEntPtr(oCircle.m_pEntity->objectId());
}

CCircle::~CCircle()
{
}

void CCircle::Set(CPt3d ptCenter, double fRadius)
{
	if(!isNull())
	{
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		pEntity->setCenter(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
		pEntity->setRadius(fabs(fRadius));
	}
}

void CCircle::SetPoint(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd)
{
	if(!isNull())
	{
		AcGePoint3d ptCenter;
		ptCenter.x = S(CPt3d(ptStart.x * ptStart.x + ptStart.y * ptStart.y, ptStart.y),
			CPt3d(ptMiddle.x * ptMiddle.x + ptMiddle.y * ptMiddle.y, ptMiddle.y),
			CPt3d(ptEnd.x * ptEnd.x + ptEnd.y * ptEnd.y, ptEnd.y)) / (2 * S(ptStart, ptMiddle, ptEnd));
		ptCenter.y = S(CPt3d(ptStart.x, ptStart.x * ptStart.x + ptStart.y * ptStart.y),
			CPt3d(ptMiddle.x, ptMiddle.x * ptMiddle.x + ptMiddle.y * ptMiddle.y),
			CPt3d(ptEnd.x, ptEnd.x * ptEnd.x + ptEnd.y * ptEnd.y)) / (2 * S(ptStart, ptMiddle, ptEnd));
		ptCenter.z = 0;
		double fRadius = sqrt((ptStart.x - ptCenter.x) * (ptStart.x - ptCenter.x) + (ptStart.y - ptCenter.y) * (ptStart.y - ptCenter.y));
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		pEntity->setCenter(ptCenter);
		pEntity->setRadius(fRadius);
	}
}

bool CCircle::SetPointRadius(CPt3d ptStart, CPt3d ptEnd, double fRadius)
{
	double fDist = ptStart.GetDistance(ptEnd);
	if(ptStart == ptEnd)
		return false;

	if(CompareFloat(2*fabs(fRadius), fDist, 0.002) < 0)
		return false;

	if(!isNull())
	{
		AcGePoint3d ptCenter;
		if(CompareFloat(fDist, 2 * fabs(fRadius)) == 0)
		{
			ptCenter.x = (ptStart.x + ptEnd.x) / 2;
			ptCenter.y = (ptStart.y + ptEnd.y) / 2;
		}
		else
		{
			CPt3d pt;
			Circle_Center(ptStart, ptEnd, fRadius, pt);
			ptCenter.x = pt.x;
			ptCenter.y = pt.y;
		}
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		pEntity->setCenter(ptCenter);
		pEntity->setRadius(fRadius);
		return true;
	}
	return false;
}

bool CCircle::GetIsClosed()
{
	if(!isNull())
	{
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		pEntity->isClosed();
		return true;
	}

	return false;
}

CPt3d CCircle::GetCenter()
{
	if(!isNull())
	{
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		CPt3d ptCenter = pEntity->center();
		return ptCenter;
	}

	return CPt3d(false);
}

double CCircle::GetRadius()
{
	if(!isNull())
	{
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		return pEntity->radius();
	}

	return 0.0f;
}

double CCircle::GetArea()
{
	if(!isNull())
	{
		AcDbCircle* pEntity = (AcDbCircle*)m_pEntity;
		double fArea = 0.0f;
		pEntity->getArea(fArea);
		return fArea;
	}

	return 0;
}

bool CCircle::SelEntity(ArxRleString strPrompt)
{
	ads_name entres;
	ads_point ptres;
	while(acedEntSel(_T("\n")+strPrompt,entres,ptres) != RTCAN) //RTNORM �ɹ� RTERROR ʧ��  RTCAN ȡ��
	{
		AcDbObjectId objectId;
		if(Acad::eOk != acdbGetObjectId(objectId,entres))
			continue;

		if(Acad::eOk != acdbOpenAcDbEntity(m_pEntity, objectId, AcDb::kForRead, Adesk::kFalse))
			continue;

		if(m_pEntity->isKindOf(AcDbCircle::desc()))
			return true;
	}

	return false;
}

// Բ��

CArc::CArc()
{
	m_pEntity = new AcDbArc;
}

CArc::CArc(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CArc::CArc(CArc& oArc)
{
	m_pEntity = GetEntPtr(oArc.m_pEntity->objectId());
}

CArc::~CArc()
{
}

bool CArc::Set(CPt3d ptCenter, double fRadius, double fStartAngle, double fEndAngle)
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		pEntity->setCenter(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
		pEntity->setRadius(fabs(fRadius));
		pEntity->setStartAngle(fStartAngle);
		pEntity->setEndAngle(fEndAngle);
		return true;
	}

	return false;
}

bool CArc::Set(CPt3d ptStart, CPt3d ptMiddle, CPt3d ptEnd)
{
	if(CompareFloat(ptStart.x, ptEnd.x) == 0 &&
		CompareFloat(ptStart.x, ptMiddle.x) == 0)
		return false;
	if(CompareFloat(ptStart.y, ptEnd.y) == 0 &&
		CompareFloat(ptStart.y, ptMiddle.y) == 0)
		return false;
	if(CompareFloat((ptEnd.y - ptStart.y) / (ptEnd.x - ptStart.x),
		(ptMiddle.y - ptStart.y) / (ptMiddle.x - ptStart.x)) == 0)
		return false;

	if(!isNull())
	{
		AcGePoint3d ptCenter;
		ptCenter.x = S(CPt3d(ptStart.x * ptStart.x + ptStart.y * ptStart.y, ptStart.y),
			CPt3d(ptMiddle.x * ptMiddle.x + ptMiddle.y * ptMiddle.y, ptMiddle.y),
			CPt3d(ptEnd.x * ptEnd.x + ptEnd.y * ptEnd.y, ptEnd.y)) / (2 * S(ptStart, ptMiddle, ptEnd));
		ptCenter.y = S(CPt3d(ptStart.x, ptStart.x * ptStart.x + ptStart.y * ptStart.y),
			CPt3d(ptMiddle.x, ptMiddle.x * ptMiddle.x + ptMiddle.y * ptMiddle.y),
			CPt3d(ptEnd.x, ptEnd.x * ptEnd.x + ptEnd.y * ptEnd.y)) / (2 * S(ptStart, ptMiddle, ptEnd));
		ptCenter.z = 0;
		double fRadius = sqrt((ptStart.x - ptCenter.x) * (ptStart.x - ptCenter.x) + (ptStart.y - ptCenter.y) * (ptStart.y - ptCenter.y));
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		pEntity->setCenter(ptCenter);
		pEntity->setRadius(fRadius);
		double fStartAngle = 0, fEndAngle = 2 * PI, fMiddleAngle = 0;
		fStartAngle = atan4(ptStart.y - ptCenter.y, ptStart.x - ptCenter.x);
		fMiddleAngle = atan4(ptMiddle.y - ptCenter.y, ptMiddle.x - ptCenter.x);
		fEndAngle = atan4(ptEnd.y - ptCenter.y, ptEnd.x - ptCenter.x);
		if(CompareFloat(fStartAngle, fMiddleAngle) > 0 &&
			CompareFloat(fMiddleAngle, fEndAngle) > 0)
		{
			double fTemp = fStartAngle;
			fStartAngle = fEndAngle;
			fEndAngle = fTemp;
		}
		pEntity->setStartAngle(fStartAngle);
		pEntity->setEndAngle(fEndAngle);
		return true;
	}

	return false;
}

bool CArc::Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, double fStartTangle)
{
	double fAbsRadius = fabs(fRadius);
	double fDistance = ptEnd.GetDistance(ptStart);
	if(ptStart == ptEnd || CompareFloat(fAbsRadius * 2, fDistance) > 0)
	return false;

	if(CompareFloat(fAbsRadius * 2, fDistance) == 0 &&
		CompareFloat(fabs(AdjustAngle02(ptStart.GetVectorAzimuth(ptEnd)) - fStartTangle), PI * 0.5) != 0)
	return false;

	if(!isNull())
	{
		AcGePoint3d ptCenter;
		double fStartAngle = 0, fEndAngle = 0;
		if(CompareFloat(fAbsRadius * 2, fDistance) == 0)
		{
			ptCenter.x = (ptStart.x + ptEnd.x) / 2;
			ptCenter.y = (ptStart.y + ptEnd.y) / 2;
			double fAzimuth = CPt3d::GetVectorAzimuth(ptStart, ptEnd);
			if(CompareFloat(fRadius, 0) > 0)
			{
				fStartAngle = fAzimuth - PI;
				fEndAngle = fAzimuth;
			}
			else
			{
				fStartAngle = fAzimuth;
				fEndAngle = fAzimuth + PI;
			}
		}
		else
		{
			short nLocation = short(fRadius / fAbsRadius * 1.1);
			CPt3d ptCenter = ptStart.GetLineEnd(fAbsRadius, fStartAngle + nLocation * PI * 0.5);
			double fAngle12 = ptStart.GetVectorAzimuth(ptEnd);
			double fAngle10 = ptStart.GetVectorAzimuth(ptCenter);
			double fAngle1 = ptCenter.GetVectorAzimuth(ptStart);
			double fAngle2 = ptCenter.GetVectorAzimuth(ptEnd);
			if(nLocation == -1)
			{
				if(CompareFloat(fAngle10, fAngle12) < 0)
				{
					fStartAngle = fAngle2;
					fEndAngle = fStartAngle + acos(2 * fAbsRadius * fAbsRadius - fDistance * fDistance) / (2 * fAbsRadius * fAbsRadius);
				}
				else
				{
					fStartAngle = fAngle2;
					fEndAngle = fStartAngle + 2 * PI - acos(2 * fAbsRadius * fAbsRadius - fDistance * fDistance) / (2 * fAbsRadius * fAbsRadius);
				}
			}
			else
			{
				if(CompareFloat(fAngle10, fAngle12) < 0)
				{
					fStartAngle = fAngle1;
					fEndAngle = fStartAngle + 2 * PI - acos(2 * fAbsRadius * fAbsRadius - fDistance * fDistance) / (2 * fAbsRadius * fAbsRadius);
				}
				else
				{
					fStartAngle = fAngle1;
					fEndAngle = fStartAngle + acos(2 * fAbsRadius * fAbsRadius - fDistance * fDistance) / (2 * fAbsRadius * fAbsRadius);
				}
			}
		}
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		pEntity->setCenter(ptCenter);
		pEntity->setRadius(fabs(fRadius));
		pEntity->setStartAngle(fStartAngle);
		pEntity->setEndAngle(fEndAngle);
		return true;
	}

	return false;
}

bool CArc::Set(CPt3d ptStart, CPt3d ptEnd, double fRadius, bool bMinorArc)
{
	if(ptStart == ptEnd)
	return false;

	double fDistance = ptStart.GetDistance(ptEnd);
	if(CompareFloat(2 * fabs(fRadius), fDistance, 0.002) < 0)
		fRadius = fRadius / fabs(fRadius) * fDistance * 0.5;

	if(!isNull())
	{
		AcGePoint3d ptCenter;
		double fStartAngle = 0, fEndAngle = 0;
		if(CompareFloat(fDistance, 2 * fabs(fRadius), 0.001) == 0)
		{
			ptCenter.x = (ptStart.x + ptEnd.x) / 2;
			ptCenter.y = (ptStart.y + ptEnd.y) / 2;
			double fAzimuth = CPt3d::GetVectorAzimuth(ptStart, ptEnd);
			if(CompareFloat(fRadius, 0) > 0)
			{
				fStartAngle = fAzimuth - PI;
				fEndAngle = fAzimuth;
			}
			else
			{
				fStartAngle = fAzimuth;
				fEndAngle = fAzimuth + PI;
			}
		}
		else
		{
			CPt3d pt;
			double fRadius1 = fRadius;
			if(fRadius > 0 && bMinorArc)
				fRadius1 = -fRadius;
			else if(fRadius > 0 && !bMinorArc)
				fRadius1 = fRadius;
			else if(fRadius < 0 && bMinorArc)
				fRadius1 = -fRadius;
			else
				fRadius1 = fRadius;
			if(!Circle_Center(ptStart, ptEnd, fRadius1, pt))
				return false;
			ptCenter.x = pt.x;
			ptCenter.y = pt.y;
			double fAngle1, fAngle2;
			if(CompareFloat(pt.x, ptEnd.x) != 0)
				fAngle2 = atan4(ptEnd.y - pt.y, ptEnd.x - pt.x);
			else if(CompareFloat(pt.y, ptEnd.y) > 0)
				fAngle2 = 3 * PI / 2;
			else
				fAngle2 = PI / 2;
			if(CompareFloat(pt.x, ptStart.x) != 0)
				fAngle1 = atan4(ptStart.y - pt.y, ptStart.x - pt.x);
			else if(CompareFloat(pt.y, ptStart.y) < 0)
				fAngle1 = 3 * PI / 2;
			else
				fAngle1 = PI / 2;
			if(fRadius > 0 && bMinorArc)
			{
				if(CompareFloat(fAngle1, fAngle2) > 0)
					fAngle1 -= 2 * PI;
				fStartAngle = fAngle1;
				fEndAngle = fAngle2;
			}
			else if(fRadius > 0 && !bMinorArc)
			{
				if(CompareFloat(fAngle1, fAngle2) > 0)
					fAngle1 -= 2 * PI;
				fStartAngle = fAngle1;
				fEndAngle = fAngle2;
			}
			else if(fRadius < 0 && bMinorArc)
			{
				if(CompareFloat(fAngle1, fAngle2) < 0)
					fAngle2 -= 2 * PI;
				fStartAngle = fAngle2;
				fEndAngle = fAngle1;
			}
			else
			{
				if(CompareFloat(fAngle1, fAngle2) < 0)
					fAngle2 -= 2 * PI;
				fStartAngle = fAngle2;
				fEndAngle = fAngle1;
			}
		}
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		pEntity->setCenter(ptCenter);
		pEntity->setRadius(fabs(fRadius));
		pEntity->setStartAngle(fStartAngle);
		pEntity->setEndAngle(fEndAngle);
		return true;
	}

	return false;
}

bool CArc::GetIsClosed()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		pEntity->isClosed();
		return true;
	}

	return false;
}

CPt3d CArc::GetCenter()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		CPt3d ptCenter = pEntity->center();
		return ptCenter;
	}

	return CPt3d(false);
}

double CArc::GetRadius()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		return pEntity->radius();
	}

	return 0.0f;
}

double CArc::GetStartAngle()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		return pEntity->startAngle();
	}

	return 0;
}

double CArc::GetEndAngle()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		return pEntity->endAngle();
	}

	return 0;
}

double CArc::GetArea()
{
	if(!isNull())
	{
		AcDbArc* pEntity = (AcDbArc*)m_pEntity;
		double fArea = 0.0f;
		pEntity->getArea(fArea);
		return fArea;
	}

	return 0;
}

// ��Բ����

CEllipse::CEllipse()
{
	m_pEntity = new AcDbEllipse;
}

CEllipse::CEllipse(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CEllipse::CEllipse(CEllipse& oEllipse)
{
	m_pEntity = GetEntPtr(oEllipse.m_pEntity->objectId());
}

CEllipse::~CEllipse()
{
}

void CEllipse::Set(CPt3d ptCenter, CPt3d vtMajorAxis, double fRadiusRatio, double fStartAngle, double fEndAngle)
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		if(CompareFloat(fEndAngle - fStartAngle, 2 * PI) >= 0)
			fEndAngle = fStartAngle + 2 * PI - 0.01;
		pEntity->set(ptCenter, AcGeVector3d(0.0, 0.0, 1.0), vtMajorAxis, fRadiusRatio, fStartAngle, fEndAngle);
	}
}

void CEllipse::SetEx(CPt3d ptMajorStart, CPt3d ptMajorEnd, double fMinorRadius, double fStartAngle, double fEndAngle)
{
	if(!isNull())
	{
		double fRadiusRatio = fMinorRadius * 2 / sqrt((ptMajorEnd.x - ptMajorStart.x) * (ptMajorEnd.x - ptMajorStart.x) + (ptMajorEnd.y - ptMajorStart.y) * (ptMajorEnd.y - ptMajorStart.y) + (ptMajorEnd.z - ptMajorStart.z) * (ptMajorEnd.z - ptMajorStart.z));

		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		if(CompareFloat(fEndAngle - fStartAngle, 2 * PI) >= 0)
			fEndAngle = fStartAngle + 2 * PI - 0.01;
		pEntity->set(
			AcGePoint3d(ptMajorStart.x + (ptMajorEnd.x - ptMajorStart.x) / 2, ptMajorStart.y + (ptMajorEnd.y - ptMajorStart.y) / 2, ptMajorStart.z + (ptMajorEnd.z - ptMajorStart.z) / 2),
			AcGeVector3d(0.0, 0.0, 1.0),
			AcGeVector3d((ptMajorEnd.x - ptMajorStart.x) / 2, (ptMajorEnd.y - ptMajorStart.y) / 2, (ptMajorEnd.z - ptMajorStart.z) / 2),
			fRadiusRatio, fStartAngle, fEndAngle);
	}
}

bool CEllipse::GetIsClosed()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		pEntity->isClosed();
		return true;
	}

	return false;
}

CPt3d CEllipse::GetCenter()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		CPt3d ptCenter = pEntity->center();
		return ptCenter;
	}

	return CPt3d(false);
}

CPt3d CEllipse::GetMajorAxis()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		return pEntity->majorAxis();
	}

	return CPt3d(false);
}

double CEllipse::GetStartAngle()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		return pEntity->startAngle();
	}

	return 0;
}

double CEllipse::GetEndAngle()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		return pEntity->endAngle();
	}

	return 0;
}

double CEllipse::GetArea()
{
	if(!isNull())
	{
		AcDbEllipse* pEntity = (AcDbEllipse*)m_pEntity;
		double fArea = 0.0f;
		pEntity->getArea(fArea);
		return fArea;
	}

	return 0;
}

// �ı�

CText::CText()
{
	m_pEntity = new AcDbText;
}

CText::CText(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CText::CText(CText& oText)
{
	m_pEntity = GetEntPtr(oText.m_pEntity->objectId());
}

CText::~CText()
{
}

void CText::SetPosition(CPt3d ptPosition)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setPosition(AcGePoint3d(ptPosition.x, ptPosition.y, ptPosition.z));
		pEntity->setAlignmentPoint(AcGePoint3d(ptPosition.x, ptPosition.y, ptPosition.z));
	}
}

void CText::SetText(ArxRleString lpszText)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setTextString(lpszText);
	}
}

void CText::SetTextStyle(AcDbTextStyleTableRecord* pTextStyle)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setTextStyle(pTextStyle->objectId());
	}
}

void CText::SetTextStyle(AcDbObjectId& oTextStyleId)
{
	if(oTextStyleId.isValid())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setTextStyle(oTextStyleId);
	}
}

void CText::SetTextStyle(CTextStyle& ts)
{
	AcDbObjectId oTextStyleId = ts.GetObjectId();
	if(oTextStyleId.isValid())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setTextStyle(oTextStyleId);
	}
}

void CText::SetRotation(double fRotation)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setRotation(fRotation);
	}
}

void CText::SetTextHeight(double fHeight)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setHeight(fHeight);
	}
}

void CText::SetOblique(double fOblique)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setOblique(fOblique);
	}
}

void CText::SetAlignmentMode(ArxAlignment eAlign)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;

		switch(eAlign)
		{
		case ArxLeftTop:
			pEntity->setHorizontalMode(AcDb::kTextLeft);
			pEntity->setVerticalMode(AcDb::kTextTop);
			break;
		case ArxMiddleTop:
			pEntity->setVerticalMode(AcDb::kTextTop);
			pEntity->setHorizontalMode(AcDb::kTextCenter);
			break;
		case ArxRightTop:
			pEntity->setVerticalMode(AcDb::kTextTop);
			pEntity->setHorizontalMode(AcDb::kTextRight);
			break;
		case ArxLeftMiddle:
			pEntity->setHorizontalMode(AcDb::kTextLeft);
			pEntity->setVerticalMode(AcDb::kTextVertMid);
			break;
		case ArxCenter:
			pEntity->setVerticalMode(AcDb::kTextVertMid);
			pEntity->setHorizontalMode(AcDb::kTextCenter);
			break;
		case ArxRightMiddle:
			pEntity->setVerticalMode(AcDb::kTextVertMid);
			pEntity->setHorizontalMode(AcDb::kTextRight);
			break;
		case ArxLeftBottom:
			pEntity->setHorizontalMode(AcDb::kTextLeft);
			pEntity->setVerticalMode(AcDb::kTextBase);
			break;
		case ArxMiddleBottom:
			pEntity->setHorizontalMode(AcDb::kTextCenter);
			pEntity->setVerticalMode(AcDb::kTextBase);
			break;
		case ArxRightBottom:
			pEntity->setHorizontalMode(AcDb::kTextRight);
			pEntity->setVerticalMode(AcDb::kTextBase);
			break;
		default:
			pEntity->setHorizontalMode(AcDb::kTextLeft);
			pEntity->setVerticalMode(AcDb::kTextBase);
			break;
		}
		//         if(eAlign == zLeftBottom || eAlign < zLeftTop || eAlign > zRightBottom)
		//             pEntity->setPosition(ptPosition);
		//         else pEntity->setAlignmentPoint(ptPosition);
	}
}

void CText::SetWidthFactor(double fFactor)
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		pEntity->setWidthFactor(fFactor);
	}
}

CPt3d CText::GetPosition()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return CPt3d(pEntity->position());
	}

	return CPt3d(false);
}

char* CText::GetText()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return (char*)pEntity->textString();
	}

	return "";
}

double CText::GetHeight()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return pEntity->height();
	}

	return 0.0;
}

double CText::GetRotation()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return pEntity->rotation();
	}

	return 0.0;
}

double CText::GetOblique()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return pEntity->oblique();
	}

	return 0.0;
}

double CText::GetWidthFactor()
{
	if(!isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		return pEntity->widthFactor();
	}

	return 1.0;	
}

double CText::GetActualWidth()
{
	if(!isNull() && !m_pEntity->objectId().isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		double fFontWidth = pEntity->height() * pEntity->widthFactor();
		AcGePoint3dArray oPointArray;
		pEntity->getStretchPoints(oPointArray);//getBoundingPoints
		return CPt3d::GetDistance(oPointArray[0], oPointArray[1]) + fFontWidth + 0.2;
	}

	return 0;
}

void CText::GetBoundPoint(CPt3d& ptTopLeft, CPt3d& ptTopRight, CPt3d& ptBottomRight, CPt3d& ptBottomLeft)
{
	if(!isNull() && !m_pEntity->objectId().isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		AcGePoint3dArray oPointArray;
		pEntity->getStretchPoints(oPointArray);//getBoundingPoints
		double fRotation = pEntity->rotation();
		double fFontWidth = pEntity->height() * pEntity->widthFactor();
		ptTopLeft = CPt3d::GetLineEnd(oPointArray[0], -0.2, fRotation);
		ptTopRight = CPt3d::GetLineEnd(oPointArray[1], fFontWidth, fRotation);
		ptBottomRight = CPt3d::GetLineEnd(oPointArray[2], fFontWidth, fRotation);
		ptBottomLeft = CPt3d::GetLineEnd(oPointArray[3], -0.2, fRotation);
	}
}

void CText::GetGeomExtents(CPt3d& ptMin, CPt3d& ptMax)
{
	if(!isNull() && !m_pEntity->objectId().isNull())
	{
		AcDbText* pEntity = (AcDbText*)m_pEntity;
		AcDbExtents ext;
		pEntity->getGeomExtents(ext);
		ptMin = ext.minPoint();
		ptMax = ext.maxPoint();
	}
}

// ���ı�

CMText::CMText()
{
	m_pEntity = new AcDbMText;
	m_fWidthFactor = 1;
}

CMText::CMText(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CMText::CMText(CMText& oMText)
{
	m_pEntity = GetEntPtr(oMText.m_pEntity->objectId());
	m_fWidthFactor = oMText.m_fWidthFactor;
}

CMText::~CMText()
{
}

void CMText::SetPosition(CPt3d ptPosition)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setLocation(AcGePoint3d(ptPosition.x, ptPosition.y, ptPosition.z));
	}
}

void CMText::SetText(ArxRleString lpszText)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		if(CompareFloat(m_fWidthFactor, 1) != 0)
		{
			char szTemp[20];
			sprintf(szTemp, "{\\W%.2f;", m_fWidthFactor);
			AcString oText(szTemp);
			oText += lpszText.a_str();
			oText += "}";
			pEntity->setContents(oText);
		}
		else pEntity->setContents(lpszText);
	}
}

void CMText::SetTextStyle(AcDbTextStyleTableRecord* pTextStyle)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setTextStyle(pTextStyle->objectId());
	}
}

void CMText::SetTextStyle(AcDbObjectId& oTextStyleId)
{
	if(oTextStyleId.isValid())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setTextStyle(oTextStyleId);
	}
}

void CMText::SetTextStyle(CTextStyle& ts)
{
	AcDbObjectId oTextStyleId = ts.GetObjectId();
	if(oTextStyleId.isValid())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setTextStyle(oTextStyleId);
	}
}

void CMText::SetTextHeight(double fHeight)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setTextHeight(fHeight);
	}
}

void CMText::SetRotation(double fRotation)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setRotation(fRotation);
	}
}

void CMText::SetHeight(double fHeight)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setHeight(fHeight);
	}
}

void CMText::SetAlignmentMode(ArxAlignment eAlign)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setAttachment((AcDbMText::AttachmentPoint)eAlign);
	}
}

void CMText::SetBackgroundFill(bool bFill, double fScaleFactor, bool bUseBackground, COLORREF clr)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setBackgroundFill(bFill);
		if(bFill)
		{
			pEntity->setBackgroundScaleFactor(fScaleFactor);
			pEntity->setUseBackgroundColor(bUseBackground);
			if(!bUseBackground)
			{
				AcCmColor oColor;
				oColor.setColorMethod(AcCmEntityColor::kByColor);
				oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));

				pEntity->setBackgroundFillColor(oColor);
			}
		}
	}
}

void CMText::SetTextWidthFactor(double fWidthFactor)
{
	if(!isNull())
	{
		m_fWidthFactor = fWidthFactor;
	}
}

CPt3d CMText::GetPosition()
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		CPt3d ptPosition = pEntity->location();
		return ptPosition;
	}

	return CPt3d(false);
}

char* CMText::GetText()
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		return (char*)pEntity->contents();
	}

	return "";
}

double CMText::GetHeight()
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		return pEntity->height();
	}

	return 0.0f;
}

double CMText::GetWidth()
{
	try
	{
		if(!isNull())
		{
			try
			{
				AcDbMText* pEntity = (AcDbMText*)m_pEntity;
				if(pEntity->objectId().isValid())
				{
					AcGePoint3dArray oPointArray;
					pEntity->getBoundingPoints(oPointArray);
					return CPt3d::GetDistance(oPointArray[0], oPointArray[1]);
				}
				return pEntity->width();
			}
			catch(...)
			{
			}
		}
	}
	catch(...)
	{

	}

	return 0.0f;
}

double CMText::GetActualWidth()
{
	if(!isNull() && !m_pEntity->objectId().isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		return pEntity->actualWidth();
	}

	return 0;
}

double CMText::GetTextHeight()
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		return pEntity->textHeight();
	}

	return 0.0f;
}

double CMText::GetRotation()
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		return pEntity->rotation();
	}

	return 0.0;
}

void CMText::SetWidth(double fWidth)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setWidth(fWidth);
	}
}

void CMText::SetLineSpaceFactor(double fFactor)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setLineSpacingFactor(fFactor);
	}
}

void CMText::SetLineSpaceStyle(short nStyle)
{
	if(!isNull())
	{
		AcDbMText* pEntity = (AcDbMText*)m_pEntity;
		pEntity->setLineSpacingStyle((AcDb::LineSpacingStyle)nStyle);
	}
}

// ��

CBlock::CBlock()
{
	m_pEntity = new AcDbBlockReference;
}

CBlock::CBlock(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CBlock::CBlock(CBlock& oBlock)
{
	m_pEntity = GetEntPtr(oBlock.m_pEntity->objectId());
}

CBlock::~CBlock()
{
}

void CBlock::SetBlockRecord(AcDbBlockTableRecord *pRecord)
{
	if(!isNull() && !pRecord->objectId().isNull())
	{
		try
		{
			AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
			AcDbObjectId objectId = pEntity->blockTableRecord();
			if(objectId.isValid() && objectId == pRecord->objectId())
				return;

			pEntity->setBlockTableRecord(pRecord->objectId());
			AcDbBlockTableRecord* pBlockRecord = pRecord;
			AcDbBlockTableRecordIterator* pIterator;
			pBlockRecord->newIterator(pIterator);
			AcGePoint3d basePoint;
			AcGeVector3d posVector = pEntity->position().asVector();
			AcGeScale3d scaleFactor = pEntity->scaleFactors();
			AcGeMatrix3d xfm;
			xfm.setToRotation(pEntity->rotation(), AcGeVector3d(0, 0, 1), pEntity->position());
			AcDbAttributeDefinition *pAttdef;
			for(pIterator->start();pIterator->done();pIterator->step())//�����¼�����е�Attibute���б���
			{
				AcDbEntity* pEnt = NULL;
				pIterator->getEntity(pEnt,AcDb::kForRead);
				pAttdef = AcDbAttributeDefinition::cast(pEnt);
				if (pAttdef != NULL && !pAttdef->isConstant())
				{
					AcDbAttribute* pAtt = new AcDbAttribute;
					pAtt->setPropertiesFrom(pAttdef);
					pAtt->setLayer(pAttdef->layerId());
					pAtt->setInvisible(pAttdef->isInvisible());
					basePoint = pAttdef->position();
					basePoint.x *= scaleFactor.sx;
					basePoint.y *= scaleFactor.sy;
					basePoint.z *= scaleFactor.sz;
					basePoint += posVector; 
					pAtt->setPosition(basePoint);
					pAtt->setRotation(pAttdef->rotation());
					pAtt->setTag(pAttdef->tag());
					pAtt->setFieldLength(pAttdef->fieldLength());
					pAtt->setColor(pAttdef->color());
					pAtt->setLinetype(pAttdef->linetypeId());
					pAtt->setHeight(pAttdef->height() * scaleFactor.sy);
					pAtt->setTextString(pAttdef->textString());
					pAtt->setWidthFactor(pAttdef->widthFactor());
					pAtt->setTextStyle(pAttdef->textStyle());
					pAtt->setLineWeight(pAttdef->lineWeight());
					pAtt->setHorizontalMode(pAttdef->horizontalMode());
					pAtt->setVerticalMode(pAttdef->verticalMode());
					basePoint = pAttdef->alignmentPoint();
					basePoint.x *= scaleFactor.sx;
					basePoint.y *= scaleFactor.sy;
					basePoint.z *= scaleFactor.sz;
					basePoint += posVector; 
					pAtt->setAlignmentPoint(basePoint);
					pAtt->transformBy(xfm);

					pEntity->appendAttribute(pAtt);
				}
			}
		}
		catch(...)
		{
		}
	}
}

void CBlock::SetPosition(CPt3d ptPosition)
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		AcGePoint3d oPos(ptPosition.x, ptPosition.y, ptPosition.z);
		AcGeVector3d oVector = oPos - pEntity->position();
		pEntity->setPosition(oPos);
		AcDbObjectIterator* pIterator = pEntity->attributeIterator();
		AcGePoint3d basePoint;
		for(pIterator->start();!pIterator->done();pIterator->step())
		{
			AcDbAttribute *pAtt = AcDbAttribute::cast(pIterator->entity());
			if(pAtt != NULL && !pAtt->isConstant())
			{
				basePoint = pAtt->position();
				basePoint += oVector; 
				pAtt->setPosition(basePoint);
				basePoint = pAtt->alignmentPoint();
				basePoint += oVector; 
				pAtt->setAlignmentPoint(basePoint);
			}
		}
	}
}

void CBlock::SetRotation(double fRotation)
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		pEntity->setRotation(fRotation);
		AcGeMatrix3d xfm;
		AcGeVector3d axis(0, 0, 1);
		AcGePoint3d oPos = pEntity->position();
		xfm.setToRotation(fRotation, axis, oPos);
		//         pEntity->setBlockTransform(xfm);

		AcDbObjectIterator* pIterator = pEntity->attributeIterator();
		for(pIterator->start();!pIterator->done();pIterator->step())
		{
			AcDbEntity* pEnt = pIterator->entity();
			AcDbAttribute *pAtt = AcDbAttribute::cast(pEnt);
			if(pAtt != NULL && !pAtt->isConstant())
			{
				pAtt->transformBy(xfm);
			}
		}
	}
}

void CBlock::SetScaleFactors(CPt3d ptScale)
{
	if(CompareFloat(ptScale.x, 0) <= 0 ||
		CompareFloat(ptScale.y, 0) <= 0 ||
		CompareFloat(ptScale.z, 0) <= 0)
		return;

	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		pEntity->setScaleFactors(AcGeScale3d(ptScale.x, ptScale.y, ptScale.z));
		AcGePoint3d oPos = pEntity->position();
		AcDbObjectIterator* pIterator = pEntity->attributeIterator();
		AcGePoint3d basePoint;
		for(pIterator->start();!pIterator->done();pIterator->step())
		{
			AcDbEntity* pEnt = pIterator->entity();
			AcDbAttribute *pAtt = AcDbAttribute::cast(pEnt);
			if(pAtt != NULL && !pAtt->isConstant())
			{
				basePoint = pAtt->position();
				AcGeVector3d oVect = basePoint - oPos;
				oVect.x *= ptScale.x; 
				oVect.y *= ptScale.y;
				oVect.z *= ptScale.z;
				pAtt->setPosition(oPos + oVect);
				basePoint = pAtt->alignmentPoint();
				oVect = basePoint - oPos;
				oVect.x *= ptScale.x; 
				oVect.y *= ptScale.y;
				oVect.z *= ptScale.z;
				pAtt->setAlignmentPoint(oPos + oVect);
				pAtt->setHeight(pAtt->height() * ptScale.x);
			}
		}
	}
}

void CBlock::Explode(AcDbObjectIdArray& arrObjectId, AcDbBlockTableRecord* pBlockRecord)
{
	try
	{
		if(!isNull() && !pBlockRecord->objectId().isNull())
		{
			AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
			AcDbBlockTableRecord* pRecord = pBlockRecord;
			AcDbVoidPtrArray arr;
			pEntity->explode(arr);
			int length = arr.length();
			for(int i = 0; i < length; i ++)
			{
				AcRxObject* pObject = (AcRxObject*)arr.at(i);
				if(pObject->isKindOf(AcDbEntity::desc()))
				{
					AcDbEntity* pEntity1 = (AcDbEntity*)pObject;
					pRecord->appendAcDbEntity(pEntity1);
					arrObjectId.append(AcDbObjectId(pEntity1->objectId()));
				}
			}
		}
	}
	catch(...)
	{
	}
}

void CBlock::GetEntityArray(AcDbObjectIdArray& arrObjectId)
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		AcDbBlockTableRecord* pRecord = (AcDbBlockTableRecord*)GetRecordPtr(pEntity->blockTableRecord());
		AcDbBlockTableRecordIterator* pIterator;
		pRecord->newIterator(pIterator);
		for(pIterator->start(); !pIterator->done();pIterator->step())
		{
			AcDbObjectId entityId;
			pIterator->getEntityId(entityId);
			arrObjectId.append(entityId);
		}
		pRecord->close();
	}
}

CPt3d CBlock::GetPosition()
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		CPt3d ptPosition = pEntity->position();
		return ptPosition;
	}

	return CPt3d(false);
}

double CBlock::GetRotation()
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		return pEntity->rotation();
	}

	return 0.0f;
}

CPt3d CBlock::GetScaleFactors()
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		AcGeScale3d odScale = pEntity->scaleFactors();
		return CPt3d(odScale.sx, odScale.sy, odScale.sz);
	}

	return CPt3d(false);
}

void CBlock::SetAttribute(ArxRleString lpszName, ArxRleString lpszText)
{
	try
	{
		if(!isNull())
		{
			AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
			AcDbObjectIterator* pIterator = pEntity->attributeIterator();
			for(pIterator->start(); !pIterator->done(); pIterator->step())
			{
				AcDbEntity* pEnt = pIterator->entity();
				AcDbAttribute* pAtt = AcDbAttribute::cast(pEnt);
				if(pAtt != NULL && !pAtt->isConstant())
				{
					if(pAtt->tag() == lpszName)
					{
						pAtt->upgradeOpen();
						pAtt->setTextString(lpszText);
						pAtt->downgradeOpen();
					}
				}
			}
		}
	}
	catch(...)
	{
	}
}

char* CBlock::GetAttribute(ArxRleString lpszName)
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		AcDbObjectIterator* pIterator = pEntity->attributeIterator();
		for(pIterator->start(); !pIterator->done(); pIterator->step())
		{
			AcDbEntity* pEnt = pIterator->entity();
			AcDbAttribute* pAtt = AcDbAttribute::cast(pEnt);
			if(pAtt != NULL && !pAtt->isConstant())
			{
				if(pAtt->tag() == lpszName)
				{
					return (char*)pAtt->textString();
				}
			}
		}
	}

	return "";
}

void CBlock::AppendAttribute(ArxRleString lpszName, AcDbText* pText)
{
	if(!isNull())
	{
		AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
		AcGePoint3d oPosition = pEntity->position();
		AcGeScale3d oScale = pEntity->scaleFactors();
		AcDbAttributeDefinition *pAttdef = AcDbAttributeDefinition::cast(pText);
		AcDbAttribute* pAtt = new AcDbAttribute;
		pAtt->setPropertiesFrom(pAttdef);
		pAtt->setTag(lpszName);
		pAtt->setInvisible(pAttdef->isInvisible());
		AcGePoint3d basePoint = pAttdef->position();
		AcGeVector3d oVector = basePoint - oPosition;
		oVector.x *= oScale.sx;
		oVector.y *= oScale.sy;
		oVector.z *= oScale.sz;
		basePoint += oVector; 
		pAtt->setPosition(basePoint);
		pAtt->setRotation(pAttdef->rotation());
		pAtt->setFieldLength(pAttdef->fieldLength());
		pAtt->setColor(pAttdef->color());
		pAtt->setLinetype(pAttdef->linetypeId());
		pAtt->setHeight(pAttdef->height());
		pAtt->setTextString(pAttdef->textString());
		pAtt->setWidthFactor(pAttdef->widthFactor());
		pAtt->setTextStyle(pAttdef->textStyle());
		pAtt->setLineWeight(pAttdef->lineWeight());
		pAtt->setHorizontalMode(pAttdef->horizontalMode());
		pAtt->setVerticalMode(pAttdef->verticalMode());
		basePoint = pAttdef->alignmentPoint();
		oVector = basePoint - oPosition;
		oVector.x *= oScale.sx;
		oVector.y *= oScale.sy;
		oVector.z *= oScale.sz;
		basePoint += oVector;  
		pAtt->setAlignmentPoint(basePoint);
		AcGeMatrix3d xfm;
		AcGeVector3d axis(0, 0, 1);
		basePoint = pEntity->position();
		xfm.setToRotation(pEntity->rotation(), axis, basePoint);
		pAtt->transformBy(xfm);

		pEntity->appendAttribute(pAtt);
	}
}

void CBlock::SetAttributeFontHeight(ArxRleString lpszName, double fFontHeight)
{
	try
	{
		if(!isNull())
		{
			AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
			AcDbObjectIterator* pIterator = pEntity->attributeIterator();
			for(pIterator->start(); !pIterator->done(); pIterator->step())
			{
				AcDbEntity* pEnt = pIterator->entity();
				AcDbAttribute* pAtt = AcDbAttribute::cast(pEnt);
				if(pAtt != NULL && !pAtt->isConstant())
				{
					if(pAtt->tag() == lpszName == 0)
					{
						pAtt->upgradeOpen();
						pAtt->setHeight(fFontHeight);
						pAtt->downgradeOpen();
					}
				}
			}
		}
	}
	catch(...)
	{
	}
}

void CBlock::SetAttributeAlign(ArxRleString lpszName, ArxAlignment eAlign)
{
	try
	{
		if(!isNull())
		{
			AcDbBlockReference* pEntity = (AcDbBlockReference*)m_pEntity;
			AcDbObjectIterator* pIterator = pEntity->attributeIterator();
			for(pIterator->start(); !pIterator->done(); pIterator->step())
			{
				AcDbEntity* pEnt = pIterator->entity();
				AcDbAttribute* pAtt = AcDbAttribute::cast(pEnt);
				if(pAtt != NULL && !pAtt->isConstant())
				{
					if(pAtt->tag() == lpszName)
					{
						pAtt->upgradeOpen();
						switch(eAlign)
						{
						case ArxLeftTop:
							pAtt->setHorizontalMode(AcDb::kTextLeft);
							pAtt->setVerticalMode(AcDb::kTextTop);
							break;
						case ArxMiddleTop:
							pAtt->setVerticalMode(AcDb::kTextTop);
							pAtt->setHorizontalMode(AcDb::kTextCenter);
							break;
						case ArxRightTop:
							pAtt->setVerticalMode(AcDb::kTextTop);
							pAtt->setHorizontalMode(AcDb::kTextRight);
							break;
						case ArxLeftMiddle:
							pAtt->setHorizontalMode(AcDb::kTextLeft);
							pAtt->setVerticalMode(AcDb::kTextVertMid);
							break;
						case ArxCenter:
							pAtt->setVerticalMode(AcDb::kTextVertMid);
							pAtt->setHorizontalMode(AcDb::kTextCenter);
							break;
						case ArxRightMiddle:
							pAtt->setVerticalMode(AcDb::kTextVertMid);
							pAtt->setHorizontalMode(AcDb::kTextRight);
							break;
						case ArxLeftBottom:
							pAtt->setHorizontalMode(AcDb::kTextLeft);
							pAtt->setVerticalMode(AcDb::kTextBase);
							break;
						case ArxMiddleBottom:
							pAtt->setHorizontalMode(AcDb::kTextCenter);
							pAtt->setVerticalMode(AcDb::kTextBase);
							break;
						case ArxRightBottom:
							pAtt->setHorizontalMode(AcDb::kTextRight);
							pAtt->setVerticalMode(AcDb::kTextBase);
							break;
						default:
							pAtt->setVerticalMode(AcDb::kTextBase);
							pAtt->setHorizontalMode(AcDb::kTextLeft);
							break;
						}
						pAtt->downgradeOpen();
					}
				}
			}
		}
	}
	catch(...)
	{
	}
}

bool CBlock::SetBlockAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef)
{
	// open the block record and find all the ATTDEFS
	AcDbBlockTableRecord* blkTblRec = (AcDbBlockTableRecord*)GetRecordPtr(blockRecordId);
	if(blkTblRec == NULL)
		return false;

	AcDbBlockTableRecordIterator* blkIter;
	if(blkTblRec->newIterator(blkIter) != Acad::eOk)
		return false;

	AcDbEntity* ent;
	AcDbAttributeDefinition* attdef;
	AcGeMatrix3d xformMat = blkRef->blockTransform();

	for(; !blkIter->done(); blkIter->step()) {
		if(blkIter->getEntity(ent, AcDb::kForRead) == Acad::eOk) {
			// deal only with non-constant ATTDEFS
			if(((attdef = AcDbAttributeDefinition::cast(ent)) != NULL) &&
				(attdef->isConstant() == Adesk::kFalse)) {
					// create a new ATTRIBUTE entity
					AcDbAttribute* attrib = new AcDbAttribute;

					// set ENTITY common fields
					attrib->setPropertiesFrom(attdef);

					// set ATTDEF common fields
					attrib->setInvisible(attdef->isInvisible());
					attrib->setFieldLength(attdef->fieldLength());

					// set TEXT common fields
					attrib->setThickness(attdef->thickness());
					attrib->setOblique(attdef->oblique());
					attrib->setRotation(attdef->rotation());
					attrib->setHeight(attdef->height());
					attrib->setTextStyle(attdef->textStyle());
					attrib->mirrorInX(attdef->isMirroredInX());
					attrib->mirrorInY(attdef->isMirroredInY());
					attrib->setHorizontalMode(attdef->horizontalMode());
					attrib->setVerticalMode(attdef->verticalMode());
					attrib->setPosition(attdef->position());
					attrib->setAlignmentPoint(attdef->alignmentPoint());

					// put in default value for test
					acutPrintf(_T("\nUsing default ATTRIBUTE value..."));
					const TCHAR* tagStr = attdef->tagConst();
					attrib->setTag(tagStr);
					const TCHAR* valStr = attdef->textStringConst();
					attrib->setTextString(valStr);

					// add to this block reference
					if(blkRef->appendAttribute(attrib) == Acad::eOk) {
						attrib->transformBy(xformMat);
						attrib->setWidthFactor(attdef->widthFactor());    // has to be set after transform
						attrib->close();
					}
					else {
						acutPrintf(_T("\nERROR: Could not append ATTRIBUTE."));
						delete attrib;
					}
			}
			ent->close();
		}
	}

	delete blkIter;
	blkTblRec->close();
	return true;
}

// �ӿ�

CViewport::CViewport()
{
	m_pEntity = new AcDbViewport;
}

CViewport::CViewport(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CViewport::CViewport(const CViewport& oViewport)
{
	CViewport* pViewport = const_cast<CViewport*>(&oViewport);
	m_pEntity = pViewport->getent();
	m_pt1 = oViewport.m_pt1;
	m_pt2 = oViewport.m_pt2;
}

CViewport::~CViewport()
{
}

void CViewport::SetRect(CPt3d pt1, CPt3d pt2)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		AcGePoint3d Odpt1(pt1.x, pt1.y, pt1.z);
		AcGePoint3d Odpt2(pt2.x, pt2.y, pt2.z);
		AcGePoint3d ptCenter((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2, 0);

		double fWidth = fabs(pt1.x - pt2.x);
		double fHeight = fabs(pt1.y - pt2.y);
		pEntity->setCenterPoint(ptCenter);
		pEntity->setWidth(fWidth);
		pEntity->setHeight(fHeight);
		m_pt1 = pt1;
		m_pt2 = pt2;
	}
}

void CViewport::SetWidth(double fWidth)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setWidth(fWidth);
	}
}

void CViewport::SetHeight(double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setHeight(fHeight);
	}
}

void CViewport::GetPoint(CPt3d& pt1, CPt3d& pt2)
{
	pt1 = m_pt1;
	pt2 = m_pt2;
}

void CViewport::SetNonRectClipEntity(CPolyline* pLine)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setNonRectClipEntityId(pLine->getent()->objectId());
		pEntity->setNonRectClipOn();
		pEntity->setLocked();
	}
}

void CViewport::SetNonRectClipOff()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setNonRectClipOff();
	}
}

void CViewport::SetOn(bool bOn)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		if(bOn)
			pEntity->setOn();
		else
			pEntity->setOff();
	}
}

void CViewport::SetLocked(bool bLock)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		if(bLock)
			pEntity->setLocked();
		else
			pEntity->setUnlocked();
	}
}

void CViewport::SetUcs(CPt3d origin, CPt3d xAxis, CPt3d yAxis)
{
	try
	{
		if(!m_pEntity->objectId().isNull())
		{
			AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
			pEntity->setUcs(AcGePoint3d(origin.x, origin.y, origin.z),
				AcGeVector3d(xAxis.x, xAxis.y, xAxis.z),
				AcGeVector3d(yAxis.x, yAxis.y, yAxis.z));
			pEntity->setUcsPerViewport(true);
			pEntity->setUcsIconVisible();
		}
	}
	catch(...)
	{
	}
}

void CViewport::SetScale(double fScale)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		if(CompareFloat(fScale, 0.0) <= 0)
			pEntity->setStandardScale(AcDbViewport::kScaleToFit);
		else
			pEntity->setCustomScale(fScale);
	}
}

void CViewport::SetLensLength(double fLensLength)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setLensLength(fLensLength);
	}
}

void CViewport::SetViewDirection(CPt3d viewDirection)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setViewDirection(AcGeVector3d(viewDirection.x, viewDirection.y, viewDirection.z));
	}
}

void CViewport::SetTwistAngle(double fAngle)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setTwistAngle(fAngle);
	}
}

void CViewport::SetViewTarget(CPt3d ptCenter)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setViewTarget(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
	}
}

void CViewport::SetViewHeight(double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		pEntity->setViewHeight(fHeight);
	}
}

void CViewport::FreezeLayersInViewport(CLayerArray& arrLayer)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		AcDbObjectIdArray arrObjectId;
		long cnt = arrLayer.length();
		for(long i=0; i<cnt; i++)
		{
			CLayer& layer = arrLayer.at(i);
			arrObjectId.append(layer.GetRecord()->objectId());
		}
		pEntity->freezeLayersInViewport(arrObjectId);
	}
}

double CViewport::GetWidth()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->width();
	}

	return 0.0;
}

double CViewport::GetHeight()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->height();
	}

	return 0.0;
}

bool CViewport::IsOn()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->isOn();
	}

	return false;
}

bool CViewport::IsLocked()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->isLocked();
	}

	return false;
}

void CViewport::GetUcs(CPt3d& origin, CPt3d& xAxis, CPt3d& yAxis)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		AcGePoint3d georigin;
		AcGeVector3d gexAxis, geyAxis;
		pEntity->getUcs(georigin, gexAxis, geyAxis);
		origin = georigin;
		xAxis = gexAxis;
		yAxis = geyAxis;
	}
}

double CViewport::GetScale()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->height();
	}

	return 0.0;
}

CPt3d CViewport::GetViewCenter()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		AcGePoint2d pt = pEntity->viewCenter();
		return CPt3d(pt.x, pt.y);
	}

	return CPt3d(false);
}

CPt3d CViewport::GetViewDirection()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->viewDirection();
	}

	return CPt3d(false);
}

CPt3d CViewport::GetViewTarget()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->viewTarget();
	}

	return CPt3d(false);
}

double CViewport::GetTwistAngle()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->twistAngle();
	}

	return 0.0;
}

double CViewport::GetViewHeight()
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbViewport* pEntity = (AcDbViewport*)m_pEntity;
		return pEntity->viewHeight();
	}

	return 0.0;
}

// ��ע

CDimension::CDimension()
{
	m_pEntity = new AcDbRotatedDimension;
}

CDimension::CDimension(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CDimension::CDimension(CDimension& oDimension)
{
	m_pEntity = oDimension.m_pEntity;
}

CDimension::~CDimension()
{
}

void CDimension::SetDimensionStyle(CDimensionStyle *pRecord)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		AcDbObjectId objectId = pRecord->GetObjectId();
		pEntity->setDimensionStyle(objectId);
		pEntity->setDimstyleData(objectId);
	}
}

void CDimension::SetDimBlockRecord(CBlockRecord* pRecord)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimBlockId(pRecord->GetObjectId());
	}
}

void CDimension::SetText(ArxRleString lpszText)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimensionText(lpszText);
	}
}

void CDimension::SetTextPosition(CPt3d ptPosition)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setTextPosition(AcGePoint3d(ptPosition.x, ptPosition.y, ptPosition.z));
	}
}

void CDimension::SetTextRotation(double fRotation)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setTextRotation(fRotation);
	}
}

void CDimension::SetArrowFlipped(bool bFirst, bool bSecond)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setArrowFirstIsFlipped(bFirst);
		pEntity->setArrowSecondIsFlipped(bSecond);
	}
}

void CDimension::SetDynamicDimension(bool bDynamic)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDynamicDimension(bDynamic);
	}
}

void CDimension::SetArrow(ArxRleString lpszName)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		AcDbObjectId objectId = pEntity->dimensionStyle();
		AcDbDimStyleTableRecord* pDimRecord  = (AcDbDimStyleTableRecord*)GetRecordPtr(objectId,AcDb::kForWrite);
		pDimRecord->setDimblk1(lpszName);
		pDimRecord->setDimblk2(lpszName);
		pDimRecord->close();
	}
}

void CDimension::SetExtLineFixLenEnable(bool bEnable)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		//pEntity->setExtLineFixLenEnable(bEnable);
	}
}

void CDimension::SetExtLineFixLen(double fLength)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		//pEntity->setExtLineFixLen(fLength);
	}
}

void CDimension::SetDimExt1Linetype(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimExt1Linetype(objectId);
	}
}

void CDimension::SetDimExt2Linetype(AcDbObjectId& objectId)
{
	if(objectId.isValid())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimExt2Linetype(objectId);
	}
}

void CDimension::SetArrowSize(double fSize)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimasz(fSize);
	}
}

void CDimension::SetDimzin(byte nBits)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimzin(nBits);
	}
}

void CDimension::SetDimexe(double fDis)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimexe(fDis);
	}
}

void CDimension::SetDimexo(double fOffset)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimexo(fOffset);
	}
}

void CDimension::SetTextHeight(double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtxt(fHeight);
	}
}

void CDimension::SetTextHorz(ArxDimtad eTad)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtad(eTad);
	}
}

void CDimension::SetTextOffset(double fGap)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimgap(fGap);
	}
}

void CDimension::SetDimtih(bool bTih)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtih(bTih);
	}
}

void CDimension::SetDimtoh(bool bToh)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtoh(bToh);
	}
}

void CDimension::SetDimtix(bool bTix)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtix(bTix);
	}
}

void CDimension::SetDimtofl(bool bTofl)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimtofl(bTofl);
	}
}

void CDimension::SetLineColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		AcCmColor color;
		color.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		pEntity->setDimclrd(color);
	}
}

void CDimension::SetExtLineColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		AcCmColor color;
		color.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		pEntity->setDimclre(color);
	}
}

void CDimension::SetTextColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		AcCmColor color;
		color.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		pEntity->setDimclrt(color);
	}
}

void CDimension::SetDimLineType(AcDbObjectId oLineType)
{
	if(!m_pEntity->objectId().isNull() && oLineType.isValid())
	{
		AcDbRotatedDimension* pEntity = (AcDbRotatedDimension*)m_pEntity;
		pEntity->setDimLineLinetype(oLineType);
	}
}

void CDimension::SetAlignedDimPoint(CPt3d pt1, CPt3d pt2, double fDis)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbAlignedDimension* pEntity = (AcDbAlignedDimension*)m_pEntity;
		pEntity->setXLine1Point(AcGePoint3d(pt1.x, pt1.y, pt1.z));
		pEntity->setXLine2Point(AcGePoint3d(pt2.x, pt2.y, pt2.z));
		double fAngle = CPt3d::GetVectorAzimuth(pt1, pt2) + (fDis > 0 ? -PI / 2 : PI / 2); 
		AcGePoint3d pt;
		pt.x = pt1.x + fDis * cos(fAngle);
		pt.y = pt1.y + fDis * sin(fAngle);
		pt.z = pt1.z;
		pEntity->setDimLinePoint(pt);
	}
}

void CDimension::SetAlignedDimPoint(CPt3d pt)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbAlignedDimension* pEntity = (AcDbAlignedDimension*)m_pEntity;
		pEntity->setDimLinePoint(AcGePoint3d(pt.x, pt.y, pt.z));
	}
}

void CDimension::SetAlignedDimOblique(double fOblique)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbAlignedDimension* pEntity = (AcDbAlignedDimension*)m_pEntity;
		pEntity->setOblique(fOblique);
	}
}

void CDimension::SetPoint(CPt3d ptStart1, CPt3d ptStart2, CPt3d ptCenter)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDb3PointAngularDimension* pEntity = (AcDb3PointAngularDimension*)m_pEntity;
		pEntity->setXLine1Point(AcGePoint3d(ptStart1.x, ptStart1.y, ptStart1.z));
		pEntity->setXLine2Point(AcGePoint3d(ptStart2.x, ptStart2.y, ptStart2.z));
		pEntity->setCenterPoint(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
	}
}

void CDimension::SetArc(CPt3d ptArc)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDb3PointAngularDimension* pEntity = (AcDb3PointAngularDimension*)m_pEntity;
		pEntity->setArcPoint(AcGePoint3d(ptArc.x, ptArc.y, ptArc.z));
	}
}

void CDimension::SetArcDimPoint(CPt3d ptArc)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbArcDimension* pEntity = (AcDbArcDimension*)m_pEntity;
		pEntity->setArcPoint(AcGePoint3d(ptArc.x, ptArc.y, ptArc.z));
	}
}

void CDimension::SetArcDimCenterPoint(CPt3d ptCenter)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbArcDimension* pEntity = (AcDbArcDimension*)m_pEntity;
		pEntity->setCenterPoint(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
	}
}

void CDimension::SetArcDimLeaderPoint(CPt3d pt1, CPt3d pt2)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbArcDimension* pEntity = (AcDbArcDimension*)m_pEntity;
		pEntity->setLeader1Point(AcGePoint3d(pt1.x, pt1.y, pt1.z));
		pEntity->setLeader2Point(AcGePoint3d(pt2.x, pt2.y, pt2.z));
	}
}

void CDimension::SetGridDimDefiningPoint(CPt3d ptDefine)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbOrdinateDimension* pEntity = (AcDbOrdinateDimension*)m_pEntity;
		pEntity->setDefiningPoint(AcGePoint3d(ptDefine.x, ptDefine.y, ptDefine.z));
	}
}

void CDimension::SetGridDimLeaderEndPoint(CPt3d ptEnd)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbOrdinateDimension* pEntity = (AcDbOrdinateDimension*)m_pEntity;
		pEntity->setLeaderEndPoint(AcGePoint3d(ptEnd.x, ptEnd.y, ptEnd.z));
	}
}

void CDimension::SetRadiusDimCenter(CPt3d ptCenter)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRadialDimension* pEntity = (AcDbRadialDimension*)m_pEntity;
		pEntity->setCenter(AcGePoint3d(ptCenter.x, ptCenter.y, ptCenter.z));
	}
}

void CDimension::SetRadiusDimChordPoint(CPt3d ptChord, double fLeaderLength)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbRadialDimension* pEntity = (AcDbRadialDimension*)m_pEntity;
		pEntity->setChordPoint(AcGePoint3d(ptChord.x, ptChord.y, ptChord.z));
		pEntity->setLeaderLength(fLeaderLength);
	}
}

//���

CHatch::CHatch()
{
	m_pEntity = new AcDbHatch;
	AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
	pEntity->setNormal(AcGeVector3d(0, 0, 1.0));
}

CHatch::CHatch(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CHatch::CHatch(CHatch& oHatch)
{
    m_pEntity = oHatch.m_pEntity;
}

CHatch::~CHatch()
{
}

void CHatch::SetHatchObjectType(ArxHatchObjectType type)
{
    if(!m_pEntity->objectId().isNull())
    {
        AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
        pEntity->setHatchObjectType((AcDbHatch::HatchObjectType)type);
    }
}

void CHatch::SetGradiant(ArxRleString lpszName, bool bUser)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setGradient(bUser ? AcDbHatch::kUserDefinedGradient : AcDbHatch::kPreDefinedGradient, lpszName);
	}
}

void CHatch::SetOriginPoint(CPt3d pt)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setOriginPoint(AcGePoint2d(pt.x, pt.y));
	}
}

void CHatch::SetHatchStyle(ArxHatchStyle style)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setHatchStyle((AcDbHatch::HatchStyle)style);
	}
}

bool CHatch::SetPattern(ArxRleString lpszName, ArxHatchPatternType eType)
{
	try
	{
		if(!m_pEntity->objectId().isNull())
		{
			AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
			pEntity->setPattern((AcDbHatch::HatchPatternType)eType, lpszName);
			return true;
		}
	}
	catch(...)
	{
	}

	return false;
}

void CHatch::SetPatternAngle(double fAngle)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setPatternAngle(fAngle);
	}
}

void CHatch::SetPatternScale(double fScale)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setPatternScale(fScale);
	}
}

void CHatch::EvaluateHatch()
{
    if(!m_pEntity->objectId().isNull())
    {
        AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
        pEntity->evaluateHatch();
    }
}

void CHatch::SetAssociative(bool bAssociative)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
		pEntity->setAssociative(bAssociative);
	}
}

void CHatch::AppendAssocObjectIds(AcDbObjectIdArray& arrObjectId)
{
    try
    {
	    if(!m_pEntity->objectId().isNull())
	    {
            try
            {
		        AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
                pEntity->appendLoop(AcDbHatch::kExternal, arrObjectId);
            }
            catch(...)
            {
            }
	    }
    }
    catch(...)
    {

    }
}

void CHatch::AppendLoopPoint(CPt3d *pPoint, int nNum)
{
    try
    {
        if(!m_pEntity->objectId().isNull())
        {
            try
            {
                AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
                AcGePoint2dArray ptArray;
                ptArray.setPhysicalLength(0).setLogicalLength(nNum);
                AcGeDoubleArray bulgeArray;
                bulgeArray.setPhysicalLength(0).setLogicalLength(nNum);
                for(int i = 0; i < nNum; i ++)
                {
                    CPt3d ptTemp = pPoint[i];
                    ptArray[i].set(ptTemp.x, ptTemp.y);
                    bulgeArray[i] = 0;
                }
                pEntity->appendLoop(AcDbHatch::kExternal, ptArray, bulgeArray);
            }
            catch(...)
            {
            }
        }
    }
    catch(...)
    {
        
    }
}

void CHatch::SetPickPoint(CPt3d ptPick)
{
    try
    {
        if(!m_pEntity->objectId().isNull())
        {
            try
            {
                AcDbHatch* pEntity = (AcDbHatch*)m_pEntity;
                AcGePoint2dArray ptArray;
                ptArray.setPhysicalLength(0).setLogicalLength(1);
                AcGePoint2d pt(ptPick.x, ptPick.y);
                ptArray[0].set(ptPick.x, ptPick.y);
                pEntity->appendLoop(AcDbHatch::kDerived, ptArray, AcGeDoubleArray());
            }
            catch(...)
            {
            }
        }
    }
    catch(...)
    {
    
    }
}

//��
#include "DbTable.h"
CTable::CTable()
{
	m_pEntity = new AcDbTable;
}

CTable::CTable(AcDbObjectId& objectId)
{
	m_pEntity = GetEntPtr(objectId);
}

CTable::CTable(CTable& oTable)
{
	m_pEntity = oTable.m_pEntity;
}

CTable::~CTable()
{
}

void CTable::SetTableStyle(CTableStyle* pTableStyle)
{
	if(pTableStyle != NULL)
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setTableStyle(pTableStyle->GetObjectId());
	}
}

void CTable::SetRows(long nRows)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setNumRows(nRows);

		AcDbDatabase* pDatabase = pEntity->database();
		AcDbObjectId objectId = pDatabase->tablestyle();
	}
}

void CTable::SetCols(long nCols)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setNumColumns(nCols);
	}
}

void CTable::SetHeight(double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setHeight(fHeight);
	}
}

void CTable::SetWidth(double fWidth)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setWidth(fWidth);
	}
}

void CTable::SetTextHeight(double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		long nRows = pEntity->numRows();
		long nCols = pEntity->numColumns();
		for(long i = 0; i < nRows; i ++)
		{
			for(long j = 0; j < nCols; j ++)
				pEntity->setTextHeight(i, j, fHeight);
		}
	}
}

void CTable::SetTextHeight(long nRow, long nCol, double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setTextHeight(nRow, nCol, fHeight);
	}
}

void CTable::SetTextStyle(CTextStyle* pTextStyle)
{
	if(!m_pEntity->objectId().isNull() && pTextStyle != NULL)
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setTextStyle(pTextStyle->GetObjectId());
	}
}

void CTable::SetTextStyle(long nRow, long nCol, CTextStyle* pTextStyle)
{
    try
    {
        if(!m_pEntity->objectId().isNull() && pTextStyle->isValid())
        {
            AcDbTable* pEntity = (AcDbTable*)m_pEntity;
            pEntity->setTextStyle(nRow, nCol, pTextStyle->GetObjectId());
        }
    }
    catch(...)
    {
    }
}

void CTable::SetTextColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		AcCmColor oColor;
		oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		long nRows = pEntity->numRows();
		long nCols = pEntity->numColumns();
		for(long i = 0; i < nRows; i ++)
			for(long j = 0; j < nCols; j ++)
				pEntity->setContentColor(i, j, oColor);
	}
}

void CTable::SetTextColor(long nRow, long nCol, COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		AcCmColor oColor;
		oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		pEntity->setContentColor(nRow, nCol, oColor);
	}
}

void CTable::SetGridColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		AcCmColor oColor;
		oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		long nRows = pEntity->numRows();
		long nCols = pEntity->numColumns();
		for(long i = 0; i < nRows; i ++)
			for(long j = 0; j < nCols; j ++)
				pEntity->setGridColor(i, j, AcDb::kAllGridLines, oColor);
		pEntity->setColor(oColor);
	}
}

void CTable::SetGridWidth(long nRow, long nCol, double fWidth)
{
	try
	{
		if(!m_pEntity->objectId().isNull())
		{
			AcDbTable* pEntity = (AcDbTable*)m_pEntity;
			pEntity->setGridLineWeight(nRow, nCol, AcDb::kAllGridLines, ConvertLineWeight(fWidth));
		}
	}
	catch(...)
	{
	}
}

void CTable::SetRowHeight(long nRow, double fHeight)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setRowHeight(nRow, fHeight);
	}
}

void CTable::SetColName(long nCol, ArxRleString lpszName)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setColumnName(nCol, lpszName);
	}
}

void CTable::SetColWidth(long nCol, double fWidth)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setColumnWidth(nCol, fWidth);
	}
}

void CTable::SetCellValue(long nRow, long nCol, ArxRleString lpszText)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setCellType(nRow, nCol, AcDb::kTextCell);
		AcValue* pValue = new AcValue;
		pValue->set(lpszText);
		pEntity->setValue(nRow, nCol, *pValue);
	}
}

void CTable::SetCellValue(long nRow, long nCol, long nValue)
{
	try
	{
		if(!m_pEntity->objectId().isNull())
		{
			AcDbTable* pEntity = (AcDbTable*)m_pEntity;
			pEntity->setCellType(nRow, nCol, AcDb::kTextCell);
			AcValue* pValue = new AcValue;
			pValue->set(nValue);
			pEntity->setValue(nRow, nCol, *pValue);
		} 
	}
	catch(...)
	{
	}
}

void CTable::SetCellValue(long nRow, long nCol, double fValue)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setCellType(nRow, nCol, AcDb::kTextCell);
		AcValue* pValue = new AcValue;
		pValue->set(fValue);
		pEntity->setValue(nRow, nCol, *pValue);
	} 
}

void CTable::SetCellValue(long nRow, long nCol, __int64 nValue)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setCellType(nRow, nCol, AcDb::kTextCell);
		AcValue* pValue = new AcValue;
		pValue->set(nValue);
		pEntity->setValue(nRow, nCol, *pValue);
	} 
}

void CTable::SetAlignment(ArxAlignment align)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		long nRows = pEntity->numRows();
		long nCols = pEntity->numColumns();
		for(long i = 0; i < nRows; i ++)
		{
			for(long j = 0; j < nCols; j ++)
				pEntity->setAlignment(i, j, (AcDb::CellAlignment)align);
		}
	}
}

void CTable::SetAlignment(long nRow, long nCol, ArxAlignment align)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		pEntity->setAlignment(nRow, nCol, (AcDb::CellAlignment)align);
	}
}

void CTable::MergeCells(long nRow1, long nRow2, long nCol1, long nCol2)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		long nRowFirst = min(nRow1, nRow2);
		long nRowLast = max(nRow1, nRow2);
		long nColFirst = min(nCol1, nCol2);
		long nColLast = max(nCol1, nCol2);
		pEntity->mergeCells(nRowFirst, nRowLast, nColFirst, nColLast);
	} 
}

void CTable::UnmergeCells(long nRow1, long nRow2, long nCol1, long nCol2)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		long nRowFirst = min(nRow1, nRow2);
		long nRowLast = max(nRow1, nRow2);
		long nColFirst = min(nCol1, nCol2);
		long nColLast = max(nCol1, nCol2);
		pEntity->unmergeCells(nRowFirst, nRowLast, nColFirst, nColLast);
	} 
}

void CTable::InsertRows(long nRow, long nRows, double fHeight)
{
	if(!m_pEntity->objectId().isNull() && nRows > 0)
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		int nNum = pEntity->numRows();
		if(nRow > nNum) nRow = nNum - 1;
		if(CompareFloat(fHeight, 0) == 0)
		{
			fHeight = pEntity->rowHeight(nRow - 1);
		}
		pEntity->insertRows(nRow, fHeight, nRows);
	}
}

void CTable::SetBackgroundColor(COLORREF clr)
{
	if(!m_pEntity->objectId().isNull())
	{
		AcDbTable* pEntity = (AcDbTable*)m_pEntity;
		AcCmColor oColor;
		oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		long nRows = pEntity->numRows();
		long nCols = pEntity->numColumns();
		for(long i = 0; i < nRows; i ++)
		{
			for(long j = 0; j < nCols; j ++)
				pEntity->setBackgroundColor(i, j, oColor);
		}
	}
}

// ����
CLayout::CLayout()
{
	m_pLayout = new AcDbLayout;
}

CLayout::CLayout(AcDbObjectId objectId)
{
	if(objectId.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
		m_pLayout = AcDbLayout::cast(obj);
	}
}

CLayout::CLayout(CLayout& oLayout)
{
    m_pLayout = oLayout.m_pLayout;
}

CLayout::~CLayout()
{
}

void CLayout::AddViewport(CViewport* pViewport, CPt3d ptLeftBottom, double fWidth, double fHeight,
				CPt3d ptMapLeftBottom, double fScaleFactor, double fAngle, CPolyline* pLine)
{
	//����ptLeftBottom��ptMapLeftBottom��ʵ���������෴�ģ���д����ʱû��ע�⣬����Ҳ���ø��ˣ��е��ơ�
	if(!m_pLayout->objectId().isNull() && pViewport != NULL)
	{
		try
		{
			double fAzimuth1 = atan4(fHeight, fWidth);
			double fLength = sqrt(fWidth*fWidth + fHeight*fHeight) / fScaleFactor;
			CPt3d ptTopRight = CPt3d::GetLineEnd(ptLeftBottom, fLength, fAzimuth1 + fAngle);
			CPt3d ptCenter((ptLeftBottom.x + ptTopRight.x) / 2, (ptLeftBottom.y + ptTopRight.y) / 2, ptLeftBottom.z);
			CPt3d ptNewLeftBottom = CPt3d::GetLineEnd(ptCenter, fLength / 2, PI - fAzimuth1 - fAngle * 2);

			AcGePoint3d ptInsert(ptMapLeftBottom.x + fWidth / 2, ptMapLeftBottom.y + fHeight / 2, ptMapLeftBottom.z);
			AcDbViewport* pViewport1 = (AcDbViewport*)pViewport->getent();
			pViewport1->setWidth(fWidth);
			pViewport1->setHeight(fHeight);
			AcGePoint3d ptModelCenter(ptCenter.x, ptCenter.y, ptCenter.z);
			pViewport1->setCenterPoint(ptInsert);
			pViewport1->setViewTarget(ptModelCenter);
			pViewport1->setTwistAngle(-fAngle);
			pViewport1->setCustomScale(fScaleFactor);
			AcDbBlockTableRecord* pBlockRecord = (AcDbBlockTableRecord*)GetRecordPtr(m_pLayout->getBlockTableRecordId(),AcDb::kForWrite);
			pBlockRecord->appendAcDbEntity(pViewport1);
			pViewport1->setOn();
			pViewport1->setLineWeight(AcDb::kLnWt000);

			pViewport1->setUcsIconAtOrigin();
			pViewport1->setUcsIconVisible();
			pViewport1->setUcsPerViewport(true);
			pBlockRecord->close();
		}
		catch(...)
		{
		}
	}
}

void CLayout::SetPlotPaperSize(ArxRleString lpszName)
{
    if(!m_pLayout->objectId().isNull())
    {
	    try
	    {
			AcDbPlotSettingsValidator* pValidator = ARXRLEPSV;
		    pValidator->setCanonicalMediaName(m_pLayout, lpszName);
		    pValidator->setCurrentStyleSheet(m_pLayout, L"acad.ctb");
		    pValidator->setUseStandardScale(m_pLayout, true);
		    pValidator->setStdScaleType(m_pLayout, AcDbPlotSettings::k1_1);
		    pValidator->setPlotPaperUnits(m_pLayout, AcDbPlotSettings::kMillimeters);
            double fWidth, fHeight;
            m_pLayout->getPlotPaperSize(fWidth, fHeight);
            if(fWidth > fHeight)
		        pValidator->setPlotRotation(m_pLayout, AcDbPlotSettings::k0degrees);
            else
                pValidator->setPlotRotation(m_pLayout, AcDbPlotSettings::k90degrees);
            pValidator->setPlotType(m_pLayout, AcDbPlotSettings::kWindow);
 		    pValidator->setPlotOrigin(m_pLayout, 0, 0);
            pValidator->setPlotWindowArea(m_pLayout, 0, 0, fWidth, fHeight);
            pValidator->setPlotCentered(m_pLayout, true);
	    }
	    catch(...)
	    {
	    }
    }
}

void CLayout::SetPlotPaperSize(double fWidth, double fHeight, short nPaperUnits)
{
	try
	{
		AcDbPlotSettingsValidator* pValidator = ARXRLEPSV;
        AcDbPlotSettings::PlotPaperUnits eUnits = AcDbPlotSettings::kMillimeters;
        if(nPaperUnits == 0) eUnits = AcDbPlotSettings::kInches;
        else if(nPaperUnits == 2) eUnits = AcDbPlotSettings::kPixels;
		pValidator->setClosestMediaName(m_pLayout, fWidth, fHeight, eUnits, false);
		pValidator->setCurrentStyleSheet(m_pLayout, L"acad.ctb");
		pValidator->setUseStandardScale(m_pLayout, true);
		pValidator->setStdScaleType(m_pLayout, AcDbPlotSettings::k1_1);
        pValidator->setPlotPaperUnits(m_pLayout, AcDbPlotSettings::kMillimeters);
		pValidator->setPlotRotation(m_pLayout, AcDbPlotSettings::k90degrees);
        pValidator->setPlotType(m_pLayout, AcDbPlotSettings::kWindow);
		pValidator->setPlotOrigin(m_pLayout, 0, 0);
        pValidator->setPlotWindowArea(m_pLayout, 0, 0, fWidth, fHeight);
        pValidator->setPlotCentered(m_pLayout, true);
        pValidator->setZoomToPaperOnUpdate(m_pLayout, true);
	}
	catch(...)
	{
	}

}

void CLayout::GetPaperSize(double& fWidth, double fHeight)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout->getPlotPaperSize(fWidth, fHeight);
	}
}

void CLayout::GetMargin(double& fLeft, double& fTop, double& fRight, double& fBottom)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout->getPlotPaperMargins(fLeft, fBottom, fRight, fTop);
	}
}

char* CLayout::GetPlotDeviceName()
{
    if(!m_pLayout->objectId().isNull())
    {
        const ACHAR* szName;
		m_pLayout->getPlotCfgName(szName);
		return (char*)szName;
    }

    return "";
}

void CLayout::SetInsertBase(CPt3d& pt)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout->database()->setInsbase(AcGePoint3d(pt.x, pt.y, pt.z));
	}
}

void CLayout::GetViewportList(CViewportArray& arr)
{
	if(!m_pLayout->objectId().isNull())
	{
		AcDbObjectIdArray arrObjectId = m_pLayout->getViewportArray();
		int length = arrObjectId.length();
		for(int i = 0; i < length; i ++)
		{
			CViewport oViewport(arrObjectId.at(i));
			arr.append(oViewport);
		}
	}
}

bool CLayout::isValid()
{
	if(!m_pLayout->objectId().isNull())
	{
		return m_pLayout->objectId().isValid();
	}
	return false;
}

CLayout& CLayout::operator = (AcDbObjectId objectId)
{
	if(objectId.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
		m_pLayout = AcDbLayout::cast(obj);
	}

	return *this;
}

CLayout& CLayout::operator = (CLayout& layout)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout = NULL;
	}
	m_pLayout = layout.m_pLayout;

	return *this;
}

bool CLayout::operator == (CLayout& layout)
{
	if(!m_pLayout->objectId().isNull() && !layout.m_pLayout->objectId().isNull())
	{
		return m_pLayout->objectId() == layout.m_pLayout->objectId();
	}
	else if(m_pLayout->objectId().isNull() && layout.m_pLayout->objectId().isNull())
		return true;

	return false;
}

bool CLayout::operator != (CLayout& layout)
{
	if(!m_pLayout->objectId().isNull() && !layout.m_pLayout->objectId().isNull())
	{
		return m_pLayout->objectId() != layout.m_pLayout->objectId();
	}
	else if(m_pLayout->objectId().isNull() && layout.m_pLayout->objectId().isNull())
		return false;

	return true;
}

void CLayout::SetName(ArxRleString lpszName)
{
	if(!m_pLayout->objectId().isNull())
		m_pLayout->setLayoutName(lpszName);
}

char* CLayout::GetName() const
{
	if(!m_pLayout->objectId().isNull())
	{
		ACHAR* szName;
		m_pLayout->getLayoutName(szName);
		return (char*)szName;
	}

	return "";
}

void CLayout::SetLimits(CPt3d ptMin, CPt3d ptMax, bool bCheck)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout->database()->setLimmin(AcGePoint2d(ptMin.x, ptMin.y));
		m_pLayout->database()->setLimmax(AcGePoint2d(ptMax.x, ptMax.y));
		m_pLayout->database()->setLimcheck(bCheck);
	}
}

void CLayout::GetLimits(CPt3d& ptMin, CPt3d& ptMax, bool& bCheck)
{
	if(!m_pLayout->objectId().isNull())
	{
		AcGePoint2d oMin = m_pLayout->database()->limmin();
		ptMin = oMin;
		AcGePoint2d oMax = m_pLayout->database()->limmax();
		ptMax = oMax;
		bCheck = m_pLayout->database()->limcheck();
	}
}

void CLayout::SetExtents(CPt3d ptMin, CPt3d ptMax)
{
	if(!m_pLayout->objectId().isNull())
	{
		m_pLayout->database()->setExtmin(AcGePoint3d(ptMin.x, ptMin.y, ptMin.z));
		m_pLayout->database()->setExtmax(AcGePoint3d(ptMax.x, ptMax.y, ptMax.z));
	}
}

void CLayout::GetExtents(CPt3d& ptMin, CPt3d& ptMax)
{
	if(!m_pLayout->objectId().isNull())
	{
		AcGePoint3d oMin = m_pLayout->database()->extmin();
		ptMin = oMin;
		AcGePoint3d oMax = m_pLayout->database()->extmax();
		ptMax = oMax;
	}
}

AcDbObjectId CLayout::GetObjectId()
{
	if(!m_pLayout->objectId().isNull())
		return m_pLayout->objectId();

	return AcDbObjectId();
}

void CLayout::SetPlotViewportBorders(bool bPlot)
{
    if(!m_pLayout->objectId().isNull())
        m_pLayout->setPlotViewportBorders(bPlot);
}

// ������
CGroup::CGroup()
{
	m_pGroup = new AcDbGroup;
}

CGroup::CGroup(AcDbObjectId objectId)
{
	if(objectId.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
		m_pGroup = AcDbGroup::cast(obj);
	}
}

CGroup::CGroup(CGroup& oGroup)
{
	m_pGroup = oGroup.m_pGroup;
}

CGroup::~CGroup()
{
}

bool CGroup::IsNull() const
{
	if(m_pGroup != NULL)
	{
		if(!m_pGroup->objectId().isNull())
			return true;
		else
			return false;
	}

	return false;
}

char* CGroup::GetDescription() const
{
	if(IsNull())
	{
		USES_CONVERSION;
		return T2A(m_pGroup->description());
	}
	return "";
}

void CGroup::SetDescription(ArxRleString lpszName)
{
	if(IsNull())
	{
		m_pGroup->setDescription(lpszName);
	}
}

bool CGroup::IsSelectable() const
{
	if(IsNull())
		return m_pGroup->isSelectable();
	return false;
}

void CGroup::SetSelectable(bool bSelectable)
{
	if(IsNull())
		m_pGroup->setSelectable(bSelectable);
}

char* CGroup::GetName() const
{
	if(IsNull())
	{
		USES_CONVERSION;
		return T2A(m_pGroup->name());
	}
	return "";
}

void CGroup::SetName(ArxRleString lpszName)
{
	if(IsNull())
	{
		m_pGroup->setName(lpszName);
	}
}

bool CGroup::IsNotAccessible() const
{
	if(IsNull())
		return m_pGroup->isNotAccessible();
	return false;
}

bool CGroup::IsAnonymous() const
{
	if(IsNull())
		return m_pGroup->isAnonymous();
	return false;
}

void CGroup::SetAnonymous()
{
	if(IsNull())
		m_pGroup->setAnonymous();
}

void CGroup::Append(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->append(objectId);
}

void CGroup::Append(vector<AcDbObjectId> objectIds)
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		m_pGroup->append(objIds);
	}
}

void CGroup::Prepend(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->prepend(objectId);
}

void CGroup::Prepend(vector<AcDbObjectId> objectIds)
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		m_pGroup->prepend(objIds);
	}
}

void CGroup::InsertAt(long index, AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->insertAt(index, objectId);
}

void CGroup::InsertAt(long index, vector<AcDbObjectId> objectIds)
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		m_pGroup->insertAt(index, objIds);
	}
}

void CGroup::Remove(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->remove(objectId);
}

void CGroup::RemoveAt(long index)
{
	if(IsNull())
		m_pGroup->removeAt(index);
}

void CGroup::Remove(vector<AcDbObjectId> objectIds)
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		m_pGroup->remove(objIds);
	}
}

void CGroup::RemoveAt(long index, vector<AcDbObjectId> objectIds)
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		m_pGroup->removeAt(index, objIds);
	}
}

void CGroup::Replace(AcDbObjectId oldId, AcDbObjectId newId)
{
	if(IsNull())
		m_pGroup->replace(oldId, newId);
}

void CGroup::Transfer(long fromIndex, long toIndex, long numItems)
{
	if(IsNull())
		m_pGroup->transfer(fromIndex, toIndex, numItems);
}

void CGroup::Clear()
{
	if(IsNull())
		m_pGroup->clear();
}

long CGroup::GetEntities() const
{
	if(IsNull())
		m_pGroup->numEntities();
	return 0;
}

bool CGroup::Has(CEntity* pEntity) const
{
	if(IsNull())
		return m_pGroup->has(pEntity->getent());

	return false;
}

int CGroup::AllEntityIds(vector<AcDbObjectId> objectIds) const
{
	if(IsNull())
	{
		AcDbObjectIdArray objIds;
		for(int i= 0; i<objectIds.size(); i++)
			objIds.append(objectIds[i]);
		return m_pGroup->allEntityIds(objIds);
	}

	return 0;
}

long CGroup::GetIndex(AcDbObjectId objectId) const
{
	if(IsNull())
	{
		Adesk::UInt32 index;
		m_pGroup->getIndex(objectId,index);
		return index;
	}

	return 0;
}

void CGroup::Reverse()
{
	if(IsNull())
		m_pGroup->reverse();
}

void CGroup::SetColorIndex(long index)
{
	if(IsNull())
		m_pGroup->setColorIndex(index);
}

void CGroup::SetColor(COLORREF clr)
{
	if(IsNull())
	{
		AcCmColor oColor;
		oColor.setRGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
		m_pGroup->setColor(oColor);
	}
}

void CGroup::SetLayer(ArxRleString lpszName)
{
	if(IsNull())
	{
		m_pGroup->setLayer(lpszName);
	}
}

void CGroup::SetLayer(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->setLayer(objectId);
}

void CGroup::SetLinetype(ArxRleString lpszName)
{
	if(IsNull())
	{
		m_pGroup->setLinetype(lpszName);
	}
}

void CGroup::SetLinetype(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->setLinetype(objectId);
}

void CGroup::SetLinetypeScale(double fScale)
{
	if(IsNull())
		m_pGroup->setLinetypeScale(fScale);
}

void CGroup::SetVisibility(bool bVisibility)
{
	if(IsNull())
		m_pGroup->setVisibility((AcDb::Visibility)bVisibility);
}

void CGroup::SetHighlight(bool newVal)
{
	if(IsNull())
		m_pGroup->setHighlight(newVal);
}

void CGroup::SetMaterial(ArxRleString lpszName)
{
	if(IsNull())
	{
		m_pGroup->setMaterial(lpszName);
	}
}

void CGroup::SetMaterial(AcDbObjectId objectId)
{
	if(IsNull())
		m_pGroup->setMaterial(objectId);
}

AcDbObjectId CGroup::GetObjectId()
{
	if(IsNull())
		return m_pGroup->objectId();

	return AcDbObjectId();
}

AcDbGroup* CGroup::GetObject()
{
	if(IsNull())
		return m_pGroup;

	return new AcDbGroup;
}

CCreatEnt::CCreatEnt()
{
}

CCreatEnt::~CCreatEnt()
{
}

AcDbObjectId CCreatEnt::CreateLine(AcGePoint3d ptStart,AcGePoint3d ptEnd)
{
	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);
	// ��ʵ����ӵ�ͼ�����ݿ�
	AcDbObjectId lineId;
	lineId = CCreatEnt::PostToModelSpace(pLine);
	return lineId;
}

// ��ʵ����ӵ�ͼ�����ݿ��ģ�Ϳռ�
AcDbObjectId CCreatEnt::PostToModelSpace(AcDbEntity* pEnt)
{
	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
		AcDb::kForWrite);
	AcDbObjectId entId;
	pBlockTableRecord->appendAcDbEntity(entId, pEnt);
	pBlockTable->close();
	pBlockTableRecord->close();
	pEnt->close();
	return entId;
}

AcDbObjectId CCreatEnt::CreateCircle(AcGePoint3d ptCenter,
									 AcGeVector3d vec, double radius)
{
	AcDbCircle *pCircle = new AcDbCircle(ptCenter, vec, radius);
	// ��ʵ����ӵ�ͼ�����ݿ�
	AcDbObjectId circleId;
	circleId = CCreatEnt::PostToModelSpace(pCircle);
	return circleId;
}

AcDbObjectId CCreatEnt::CreateCircle(AcGePoint3d ptCenter, double radius)
{
	AcGeVector3d vec(0, 0, 1);
	return CCreatEnt::CreateCircle(ptCenter, vec, radius);
}

AcGePoint3d CCreatEnt::Pt2dTo3d(AcGePoint2d pt)
{
	AcGePoint3d ptTemp(pt.x, pt.y, 0);
	return ptTemp;
}

AcDbObjectId CCreatEnt::CreateArc(AcGePoint3d ptCenter, AcGeVector3d vec,
								  double radius, double startAngle, double endAngle)
{
	AcDbArc *pArc = new AcDbArc(ptCenter, vec, radius, startAngle, endAngle);
	AcDbObjectId arcId;
	arcId = CCreatEnt::PostToModelSpace(pArc);
	return arcId;
}

AcDbObjectId CCreatEnt::CreateArc(AcGePoint2d ptCenter, double radius,
								  double startAngle, double endAngle)
{
	AcGeVector3d vec(0, 0, 1);
	return CCreatEnt::CreateArc(CCreatEnt::Pt2dTo3d(ptCenter),
		vec, radius, startAngle, endAngle);
}

AcDbObjectId CCreatEnt::CreateArc(AcGePoint2d ptStart, AcGePoint2d ptOnArc,AcGePoint2d ptEnd)
{
	// ʹ�ü�������Բ�ġ��뾶
	AcGeCircArc2d geArc(ptStart, ptOnArc, ptEnd);
	AcGePoint2d ptCenter = geArc.center();
	double radius = geArc.radius();
	// ������ʼ����ֹ�Ƕ�
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();
	return CCreatEnt::CreateArc(ptCenter, radius, startAngle, endAngle);
}

// ��������ʵ�ֲ���
AcDbObjectId CCreatEnt::CreateText(const AcGePoint3d& ptInsert,
								   ArxRleString text, AcDbObjectId style,
								   double height, double rotation)
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height, rotation);
	return CCreatEnt::PostToModelSpace(pText);
}

// ������������ʵ�ֲ���
AcDbObjectId CCreatEnt::CreateMText(const AcGePoint3d& ptInsert,
									ArxRleString text, AcDbObjectId style,
									double height, double width)
{
	AcDbMText *pMText = new AcDbMText();
	// ���ö������ֵ�����
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(ptInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setAttachment(AcDbMText::kBottomLeft);
	return CCreatEnt::PostToModelSpace(pMText);
}

bool isUcs()
{
	struct resbuf ret;
	acedGetVar(_T("WORLDUCS"), &ret); 
	return !ret.resval.rint;
}

int PointTrans(TCHAR *mode, ads_point pt_from, ads_point pt_to, int disp, struct resbuf* ent_from, struct resbuf* ent_to)
{   
	struct resbuf *from=NULL, *to=NULL;
	int ret;
	if( !_tcsicmp( mode, _T("U2W")))    
	{
		from = ads_buildlist( RTSHORT, 1, RTNONE );
		to   = ads_buildlist( RTSHORT, 0, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("W2U") ) )            
	{
		from = ads_buildlist( RTSHORT, 0, RTNONE );
		to   = ads_buildlist( RTSHORT, 1, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("D2W")))    
	{
		from = ads_buildlist( RTSHORT, 2, RTNONE );
		to   = ads_buildlist( RTSHORT, 0, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("W2D") ) )            
	{
		from = ads_buildlist( RTSHORT, 0, RTNONE );
		to   = ads_buildlist( RTSHORT, 2, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("D2U")))    
	{
		from = ads_buildlist( RTSHORT, 2, RTNONE );
		to   = ads_buildlist( RTSHORT, 1, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("U2D") ) )            
	{
		from = ads_buildlist( RTSHORT, 1, RTNONE );
		to   = ads_buildlist( RTSHORT, 2, RTNONE );
		ret = ads_trans( pt_from, from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("E2E") ) )            
	{
		ret = ads_trans( pt_from, ent_from, ent_to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("E2U") ) )            
	{
		to   = ads_buildlist( RTSHORT, 1, RTNONE );
		ret = ads_trans( pt_from, ent_from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("E2W")))
	{
		to   = ads_buildlist( RTSHORT, 0, RTNONE );
		ret = ads_trans( pt_from, ent_from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("E2D")))
	{
		to   = ads_buildlist( RTSHORT, 2, RTNONE );
		ret = ads_trans( pt_from, ent_from, to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("U2E") ) )            
	{
		from = ads_buildlist( RTSHORT, 1, RTNONE );
		ret = ads_trans( pt_from, from, ent_to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("W2E") ) )            
	{
		from = ads_buildlist( RTSHORT, 0, RTNONE );
		ret = ads_trans( pt_from, from, ent_to, disp, pt_to );
	}
	else if( !_tcsicmp( mode, _T("D2E") ) )            
	{
		from = ads_buildlist( RTSHORT, 2, RTNONE );
		ret = ads_trans( pt_from, from, ent_to, disp, pt_to );
	}

	if (from) ads_relrb(from);
	if (to)   ads_relrb(to);
	return ret;
}

CPt3d U2W(CPt3d pt)
{
	ads_point pt_from, pt_to;
	pt_from[X] = pt.x;
	pt_from[Y] = pt.y;
	pt_from[Z] = pt.z;
	acdbUcs2Wcs(pt_from, pt_to, false);
	return CPt3d(pt_to);
}

CPt3d W2U(CPt3d pt)
{
	ads_point pt_from, pt_to;
	pt_from[X] = pt.x;
	pt_from[Y] = pt.y;
	pt_from[Z] = pt.z;
	acdbWcs2Ucs(pt_from, pt_to, false);
	return CPt3d(pt_to);
}

AcGePoint3d U2W(AcGePoint3d pt)
{
	ads_point pt_from, pt_to;
	pt_from[X] = pt.x;
	pt_from[Y] = pt.y;
	pt_from[Z] = pt.z;
	acdbUcs2Wcs(pt_from, pt_to, false);
	return AcGePoint3d(pt_to[X],pt_to[Y],pt_to[Z]);
}

AcGePoint3d W2U(AcGePoint3d pt)
{
	ads_point pt_from, pt_to;
	pt_from[X] = pt.x;
	pt_from[Y] = pt.y;
	pt_from[Z] = pt.z;
	acdbWcs2Ucs(pt_from, pt_to, false);
	return AcGePoint3d(pt_to[X],pt_to[Y],pt_to[Z]);
}

AcDbSymbolTableRecord* GetRecordPtr(AcDbObjectId id, AcDb::OpenMode mode)
{
	if(id.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, id, mode);
		return AcDbSymbolTableRecord::cast(obj);
	}

	return NULL;
}

AcDbEntity* GetEntPtr(AcDbObjectId id, AcDb::OpenMode mode)
{
	if(id.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, id, mode);
		return AcDbEntity::cast(obj);
	}

	return NULL;
}

bool UnLockEntity(AcDbEntity* ent, bool bLock)
{
	AcDbObjectId entId = ent->objectId();
	AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(ent->layerId(),AcDb::kForWrite);
	if(bLock)
		pRcd->setIsLocked(1);
	else
		pRcd->setIsLocked(0);
	pRcd->close();
	ent->close();

	Acad::ErrorStatus es = acdbOpenAcDbEntity(ent, entId, AcDb::kForWrite, true);
	if(es == Acad::eOk) return true;
	return false;
}

COLORREF AcCmColorToRefColor(AcCmColor clr, AcDbObjectId layerId)
{
	AcCmEntityColor::ColorMethod clrMethod = clr.colorMethod();
	switch (clrMethod)
	{
	case AcCmEntityColor::kByColor :
		return RGB(clr.red(), clr.green(), clr.blue());
	case AcCmEntityColor::kByACI :
		return GetRGBByACI(clr.colorIndex());
	case AcCmEntityColor::kByLayer :
		{
			AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(layerId, AcDb::kForRead);
			AcCmColor clrLayer = pRcd->color();
			pRcd->close();
			return RGB(GetRValue(clrLayer.color()),GetGValue(clrLayer.color()),GetBValue(clrLayer.color()));
		}
	default:
		return RGB(255,255,255);
	}
}

AcCmColor RefColorToAcCmColor(COLORREF clr, AcCmEntityColor::ColorMethod clrMethod, AcDbObjectId layerId)
{
	AcCmColor color;
	int r = GetRValue(clr), g = GetGValue(clr), b = GetBValue(clr);
	switch (clrMethod)
	{
	case AcCmEntityColor::kByColor :
		color.setColorMethod(AcCmEntityColor::kByColor);
		color.setRGB(r,g,b);
		break;
	case AcCmEntityColor::kByACI :
		color.setColorMethod(AcCmEntityColor::kByACI);
		color.setColorIndex(GetACIByRGB(r,g,b));
		break;
	case AcCmEntityColor::kByLayer :
		{
			AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(layerId, AcDb::kForWrite);
			AcCmColor clrLayer = pRcd->color();
			pRcd->close();
			clrLayer.setColorMethod(AcCmEntityColor::kByLayer);
			clrLayer.setColor(clr);
			color = clrLayer;
		}
	default:
		color.setColorMethod(AcCmEntityColor::kByColor);
		color.setRGB(r,g,b);
		break;
	}

	return color;
}

double MeasureTextLength(ArxRleString strText, double fFontWidth, int nFontType)
{
	vector<ArxRleString> strArray;
	strText.ParseSubStrByDelimiter(strArray, "\\P");
	double fMeasureLength = 0.0;
	for(int i = 0; i < strArray.size(); i ++)
	{
		double fTextMeasureLength = 0.0;
		int nAsciiCharSum, nSpaceCharSum, nAlphaSum, nDigitSum, nAsciiThinnerSum;
		int nStrLength = strArray[i].GetStringInfo(nAsciiCharSum, nSpaceCharSum, nDigitSum, nAlphaSum, nAsciiThinnerSum);
		switch(nFontType)
		{
		case 0:
			fTextMeasureLength = (nStrLength - nAsciiCharSum)*fFontWidth*1.16;
			fTextMeasureLength += (nAsciiCharSum - nAsciiThinnerSum) * fFontWidth*0.64;
			fTextMeasureLength += nAsciiThinnerSum * fFontWidth * 0.28;
			break;
		case 1:
			fTextMeasureLength = (nStrLength - nAsciiCharSum)*fFontWidth*1.2;
			fTextMeasureLength += (nAsciiCharSum - nAsciiThinnerSum) * fFontWidth*0.6;
			fTextMeasureLength += nAsciiThinnerSum * fFontWidth * 0.5;
			break;
		case 2:
			fTextMeasureLength = (nStrLength - nAsciiCharSum) * fFontWidth;
			fTextMeasureLength += nAsciiCharSum * fFontWidth * 0.93;
			//fTextMeasureLength += nAlphaSum * fFontWidth * 0.67;
			break;
		case 3:
			if(nStrLength != nAsciiCharSum)
			{
				fTextMeasureLength = (nStrLength - nAsciiThinnerSum) * fFontWidth;
				fTextMeasureLength += nAsciiThinnerSum * fFontWidth * 0.5;
			}
			else
			{
				fTextMeasureLength = (nAsciiCharSum - nAsciiThinnerSum) * fFontWidth*0.8;
				fTextMeasureLength += nAsciiThinnerSum * fFontWidth * 0.5;
			}
			break;
		default:
			fTextMeasureLength = nStrLength * fFontWidth;
		}
		fMeasureLength = max(fMeasureLength, fTextMeasureLength);
	}
	return fMeasureLength;
}

void EraseGroup()
{
	ads_name ent;
	AcDbObjectId objId;
	int rc;
	ads_point pt;
	rc = acedEntSel(L"\nPlease select an Group Entity: ", ent, pt);
	if (rc != RTNORM) return;

	acdbGetObjectId(objId, ent);
	AcDbObjectPointer<AcDbEntity>pEnt(objId, AcDb::kForRead);
	CString sGrpName;
	void    *pSomething;
	AcDbObjectId   persObjId;
	const AcDbVoidPtrArray* pReactors = pEnt->reactors();
	if (pReactors != NULL)
	{
		for (int i = 0; i < pReactors->length(); i++)
		{
			pSomething = pReactors->at(i);
			// Is it a persistent reactor?
			if (acdbIsPersistentReactor(pSomething)) {
				persObjId = acdbPersistentReactorObjectId( pSomething );
				acutPrintf(L"\n\nPersistent reactor found.");
				if(pEnt.openStatus() == Acad::eOk)
					pEnt->close();
				AcDbObjectPointer<AcDbGroup>pGroup(persObjId, AcDb::kForWrite);
				sGrpName = pGroup->name();
				acedAlert(sGrpName);
				pGroup->erase();
			}
		}
	}
}

void EraseGroup(ArxRleString groupName)
{
	AcDbDictionary *pGroupDict;
	AcDbObjectId pGroupId;
	ARXRLEDB->getGroupDictionary(pGroupDict, AcDb::kForWrite);
	if (pGroupDict->getAt(groupName,pGroupId)  == Acad::eOk)
	{
		AcDbObjectPointer <AcDbGroup> pGroup(pGroupId, AcDb::kForWrite);
		pGroup->erase();
		pGroupDict->remove(pGroupId);
		pGroupDict->close();
		pGroup->close();
	}
	pGroupDict->close();
}

AcDbObjectId AddLayer(ArxRleString lpszName)
{
	AcDbObjectId objectId;

	AcDbLayerTable* pLayerTable;
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
		return objectId;

	//�ж�ͼ������Ƿ��Ѿ��д�ͼ��
	if (pLayerTable->has(lpszName))
	{
		pLayerTable->getAt(lpszName,objectId);
	}
	else
	{
		AcDbLayerTableRecord* pLayerTblRcd = new AcDbLayerTableRecord;
		pLayerTblRcd->setName(lpszName);
		pLayerTable->add(objectId,pLayerTblRcd);
		pLayerTblRcd->close();
	}
	pLayerTable->close();

	return objectId;
}

AcDbObjectId AddLayer(ArxRleString lpszLayer,int iColorIndex, AcDb::LineWeight AcLineWeight, ArxRleString lpszLinetype)
{
	AcDbObjectId objectId;

	AcDbLayerTable *pLayerTable;  //������һ���յĲ��ָ��
	AcDbDatabase* db = ARXRLEDB;  //��ǰͼ�����ݿ�
	if(db->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
		return objectId;

	if(!pLayerTable->has(lpszLayer))
	{
		AcDbLayerTableRecord *pLayerTblRcd= new AcDbLayerTableRecord;//�²���¼
		pLayerTblRcd->setName(lpszLayer);   //�趨ͼ����
		pLayerTblRcd->setIsFrozen(0);   // ͼ��ⶳ
		pLayerTblRcd->setIsOff(0);      // ��ͼ��
		pLayerTblRcd->setVPDFLT(0);     // ʹ��Ĭ���ӿ�
		pLayerTblRcd->setIsLocked(0);   // ͼ�����
		AcCmColor color;                // AcCmColor��ACAD��ɫ������
		color.setColorIndex(iColorIndex);      
		pLayerTblRcd->setColor(color);  // ͼ����ɫΪ��ɫ
		pLayerTblRcd->setLineWeight(AcLineWeight); //�����߿�
		// Ϊ����ͼ���������ͣ�Ҫ�õ����ͱ��¼��ID�����µĴ�����ʾ��εõ���������¼ID
		AcDbLinetypeTable *pLinetypeTbl;
		AcDbObjectId ltId;
		db->getSymbolTable(pLinetypeTbl, AcDb::kForRead); //�����ͱ�Ϊд��״̬
		if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //��ȡlpszLinetype����ID
		{
			pLinetypeTbl->close();
			db->loadLineTypeFile(lpszLinetype,_T("acadiso.lin")); //�������ļ��л�ȡlpszLinetype����
			db->getLinetypeTable(pLinetypeTbl,AcDb::kForRead);
			if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //��ȡlpszLinetype����ID
				pLinetypeTbl->getAt(_T("Continuous"), ltId);
		}
		pLinetypeTbl->close();
		pLayerTblRcd->setLinetypeObjectId(ltId);

		
		pLayerTable->add(objectId,pLayerTblRcd); //pLayerTable->add(pLayerTblRcd);
		pLayerTblRcd->close();
	}
	else
	{
		AcDbLayerTableRecord *pLayerTblRcd;
		pLayerTable->getAt(lpszLayer,pLayerTblRcd,AcDb::kForWrite);
		
		pLayerTblRcd->setIsFrozen(0);   // ͼ��ⶳ
		pLayerTblRcd->setIsOff(0);      // ��ͼ��
		pLayerTblRcd->setVPDFLT(0);     // ʹ��Ĭ���ӿ�
		pLayerTblRcd->setIsLocked(0);   // ͼ�����
		AcCmColor color;                // AcCmColor��ACAD��ɫ������
		color.setColorIndex(iColorIndex);      
		pLayerTblRcd->setColor(color);  // ͼ����ɫΪ��ɫ
		pLayerTblRcd->setLineWeight(AcDb::kLnWt013); //�����߿�
		AcDbLinetypeTable *pLinetypeTbl;
		AcDbObjectId ltId;
		db->getSymbolTable(pLinetypeTbl, AcDb::kForRead);
		if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //��ȡlpszLinetype����ID
		{
			pLinetypeTbl->close();
			db->loadLineTypeFile(lpszLinetype,_T("acadiso.lin")); //�������ļ��л�ȡlpszLinetype����
			db->getLinetypeTable(pLinetypeTbl,AcDb::kForRead);
			if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //��ȡlpszLinetype����ID
				pLinetypeTbl->getAt(_T("Continuous"), ltId);
		}
		pLinetypeTbl->close();
		pLayerTblRcd->setLinetypeObjectId(ltId);

		objectId = pLayerTblRcd->objectId();
		pLayerTblRcd->close();
	}
	pLayerTable->close();
	
	return objectId;
}

AcDbObjectId SetCurLayer(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbLayerTable* pLayerTable;
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
		return objectId;

	//�ж�ͼ������Ƿ��Ѿ��д�ͼ��
	if (pLayerTable->has(lpszName))
	{
		pLayerTable->getAt(lpszName,objectId);
		ARXRLEDB->setClayer(objectId);

// 		struct resbuf result;
// 		acedGetVar(_T("CLAYER"),&result);
// 		result.resval.rstring = lpszName;
// 		acedSetVar(_T("CLAYER"), &result);
	}
	pLayerTable->close();

	return objectId;
}

AcDbObjectId GetCurLayer()
{
	return ARXRLEDB->clayer();
}

ArxRleString GetCurLayerName()
{
	AcDbLayerTableRecord* pLayerTblRcd = (AcDbLayerTableRecord*)GetRecordPtr(GetCurLayer());
	ACHAR* lpszName;
	pLayerTblRcd->getName(lpszName);
	pLayerTblRcd->close();
	return lpszName;
}

AcDbObjectId FindLayer(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbLayerTable* pLayerTable;
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
		return objectId;

	//�ж�ͼ������Ƿ��Ѿ��д�ͼ��
	if(pLayerTable->has(lpszName))
		pLayerTable->getAt(lpszName,objectId);
	pLayerTable->close();

	return objectId;
}

bool DelLayer(ArxRleString lpszName)
{
	try
	{
		AcDbLayerTable* pLayerTable;
		if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
			return false;

		//�ж�ͼ������Ƿ��Ѿ��д�ͼ��
		if (pLayerTable->has(lpszName))
		{
			AcDbLayerTableRecord* pLayer;
			pLayerTable->getAt(lpszName,pLayer,AcDb::kForWrite);
			AcDbLayerTableRecord* pCurLayer = (AcDbLayerTableRecord*)GetRecordPtr(ARXRLEDB->clayer());
			if(pLayer == pCurLayer)
			{
				ARXRLEDB->setClayer(ARXRLEDB->layerZero());
			}
			pLayer->erase(true);
			pCurLayer->close();
			pLayerTable->close();
			return true;
		}
		pLayerTable->close();
	}
	catch(...)
	{
	}
	return false;
}

AcDbObjectId AddLayout(ArxRleString lpszName)
{
	try
	{
		AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
		AcDbObjectId objectId = pLayMan->findLayoutNamed(lpszName);
		if(objectId.isValid())
			return objectId;

		pLayMan->createLayout(lpszName, objectId, ARXRLEDS->objectId(),NULL);
		if(objectId.isValid())
			return objectId;
	}
	catch(...)
	{
	}

	return AcDbObjectId();
}

bool DelLayout(ArxRleString lpszName)
{
	try
	{
		if(lpszName.GetLength() > 0)
		{
			AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
			if(pLayMan->findLayoutNamed(lpszName).isValid())
			{
				AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
				if(objectId.isValid())
				{
					AcDbObject* obj;
					acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
					AcDbLayout* pLayout = AcDbLayout::cast(obj);

					ACHAR* szName;
					pLayout->getLayoutName(szName);
					if(szName == lpszName)
						pLayMan->setCurrentLayout(L"Model");

					pLayout->close();
				}
				pLayMan->deleteLayout(lpszName);
				return true;
			}
		}
	}
	catch(...)
	{
	}

	return false;
}

void RenameLayout(ArxRleString lpszOldName, ArxRleString lpszNewName)
{
	try
	{
		if(lpszOldName.GetLength() > 0 && lpszNewName.GetLength() > 00)
		{
			AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
			if(pLayMan->findLayoutNamed(lpszOldName).isValid())
				pLayMan->renameLayout(lpszOldName, lpszNewName);
		}
	}
	catch(...)
	{
	}
}

AcDbObjectId FindLayout(ArxRleString lpszName)
{
	AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
	AcDbObjectId objectId = pLayMan->findLayoutNamed(lpszName);
	return objectId;
}

AcDbObjectId SetCurLayout(ArxRleString lpszName)
{
	try
	{
		if(lpszName.GetLength() > 0)
		{
			AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
			AcString AcName = pLayMan->findActiveLayout(TRUE);
			AcDbObjectId objectId = pLayMan->findLayoutNamed(AcName);
			if(objectId.isValid())
				return objectId;
		}
		else
		{
			AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
			AcDbObjectId objectId = pLayMan->findLayoutNamed(lpszName);
			if(objectId.isValid())
				return objectId;
		}
	}
	catch(...)
	{
	}

	return AcDbObjectId();
}

AcDbObjectId GetActiveLayout()
{
	try
	{
		AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
		AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
		return objectId;
	}
	catch(...)
	{
	}

	return AcDbObjectId();
}

bool AddViewportRecord(AcDbViewportTableRecord* pViewportRecord)
{
	try
	{
		AcDbViewportTable* pViewportTable;
		ARXRLEDB->getViewportTable(pViewportTable,AcDb::kForWrite);
		if(!pViewportTable->has(pViewportRecord->objectId()))
		{
			AcDbViewportTableRecord* pViewportTblRcd = (AcDbViewportTableRecord*)GetRecordPtr(pViewportRecord->objectId(),AcDb::kForWrite);
			pViewportTable->add(pViewportTblRcd);
			pViewportTblRcd->close();
			pViewportTable->close();
			return true;
		}
		pViewportTable->close();
	}
	catch(...)
	{
	}

	return false;
}

AcDbObjectId GetActiveViewport()
{
	AcDbObjectId objectId;
	try
	{
		AcDbViewportTable* pViewportTable;
		ARXRLEDB->getViewportTable(pViewportTable,AcDb::kForRead);
		AcDbViewportTableRecord *pViewportTblRcd; 
		if(pViewportTable->getAt(L"*ACTIVE", pViewportTblRcd, AcDb::kForRead) == Acad::eOk) 
		{ 
 			pViewportTblRcd->setCenterPoint(AcGePoint2d(0.5, 0.5)); 
 			pViewportTblRcd->setHeight(1.0); 
 			pViewportTblRcd->setWidth(1.0); 
			objectId = pViewportTblRcd->objectId();
			pViewportTblRcd->close();
		} 
		pViewportTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

void GetMediaNameList(CStringArray& arrName)//, bool bDependent)
{
	try
	{
		AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
		 
		AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
		if (objectId.isValid())
		{
			AcDbObject* obj;
			acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
			AcDbLayout *pLayout = AcDbLayout::cast(obj);

			AcDbPlotSettingsValidator *pValidator = ARXRLEPSV;
			pValidator->refreshLists(pLayout);
			AcArray<const ACHAR*> mMediaList;
			const ACHAR* pLocaleName;
			pValidator->canonicalMediaNameList(pLayout, mMediaList);

			int nLength = mMediaList.length();
			for (int nCtr = 0; nCtr < nLength; nCtr++)
			{
				pValidator->getLocaleMediaName(pLayout, mMediaList.at(nCtr), pLocaleName);
				arrName.Add(pLocaleName);
			}
			pLayout->close();
		}
	}
	catch(...)
	{
	}
}

AcDbObjectId GetLayoutOfModelSpace()
{
	if(!ARXRLEDS->objectId().isNull())
	{
		AcDbObjectId objId = ARXRLEDS->getLayoutId();
		AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
		AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
		if(!objectId.isNull())
		{
			AcDbObject* obj;
			acdbOpenAcDbObject(obj, objectId, AcDb::kForWrite);
			AcDbLayout *pLayout = AcDbLayout::cast(obj);

			pLayout->setBlockTableRecordId(objId);
			ACHAR* AcName;
			if(pLayout->getLayoutName(AcName) == Acad::eOk)
				pLayMan->setCurrentLayout(AcName);

			pLayout->close();
		}

		return objId;
	}
	return AcDbObjectId();
}

AcDbObjectId AddBlockRecord(ArxRleString lpszName)
{
	AcDbObjectId objectId;
    try
    {
		try
		{
			AcDbBlockTable* pBlockTable;
			ARXRLEDB->getBlockTable(pBlockTable,AcDb::kForWrite);
			
			if(!pBlockTable->has(lpszName))
				ARXRLEDB->insert(objectId, lpszName, lpszName,ARXRLEDB, false);
			else
				pBlockTable->getAt(lpszName,objectId);

			pBlockTable->close();
		}
		catch(...)
		{
		}
    }
    catch(...)
    {

    }

	return objectId;
}

AcDbObjectId GetBlockRecord(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	try
	{
		AcDbBlockTable* pBlockTable;
		ARXRLEDB->getBlockTable(pBlockTable,AcDb::kForWrite);
		if(pBlockTable->has(lpszName))
		{
			pBlockTable->getAt(lpszName,objectId);
		}
		pBlockTable->close();
	}
	catch(...)
	{
	}
	
	return objectId;
}

void InsertDwg(ArxRleString lpszFileName)
{
	try
	{
		if(lpszFileName.GetLength() > 0)
		{
			if(PathFileExists(lpszFileName))
			{
				AcDbDatabase* pDatabase = new AcDbDatabase(false,true);
				pDatabase->readDwgFile(lpszFileName);
				AcGePoint3d pt = pDatabase->insbase();
				pDatabase->setInsbase(pt);
				AcGeMatrix3d oMatrix;
				ARXRLEDB->insert(oMatrix, pDatabase);
			}
		}
	}
	catch(...)
	{
	}
}

void InsertRef(ArxRleString lpszFileName)
{
    try
    {
		if(lpszFileName.GetLength() > 0)
		{
			if(PathFileExists(lpszFileName))
			{
				ArxRleString szName;
				LPCWSTR lpszName = PathFindFileName(lpszFileName);
				StrNCpy(szName, lpszName, PathFindExtension(lpszFileName) - lpszName + 1);
				AcDbBlockTable* pBlockTable;
				ARXRLEDB->getBlockTable(pBlockTable,AcDb::kForRead);
				AcDbBlockTableRecord* pBlockTableRcd;
				if(!pBlockTable->has(szName))
				{
					AcDbObjectId xrefBlkId;
					acdbAttachXref(ARXRLEDB, lpszFileName,  szName, xrefBlkId);
					pBlockTableRcd = (AcDbBlockTableRecord*)GetRecordPtr(xrefBlkId);
				}
				else
				{
					AcDbObjectId objectId;	
					pBlockTable->getAt(szName,objectId);
					pBlockTableRcd = (AcDbBlockTableRecord*)GetRecordPtr(objectId);
				}

				AcDbBlockReference* pRef = new AcDbBlockReference;
				pRef->setBlockTableRecord(pBlockTableRcd->objectId());
				AcGePoint3d pt = ARXRLEDB->insbase();
				pRef->setPosition(pt);
				AcDbObjectId objectId = ARXRLEDB->currentSpaceId();
				AcDbBlockTableRecord* pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objectId);
				pSpace->appendAcDbEntity(pRef);
				pBlockTableRcd->close();
			}
		}
    }
    catch(...)
    {
    }
}

AcDbObjectId InsertBlockRecord(ArxRleString lpszFileName)
{
	AcDbObjectId objectId;
    try
    {
		if(PathFileExists(lpszFileName))
		{
			ArxRleString szName;
			StrCpy(szName, lpszFileName);
			PathStripPath(szName);
			PathRemoveExtension(szName);
			AcDbBlockTable* pBlockTable;
			ARXRLEDB->getBlockTable(pBlockTable,AcDb::kForRead);
			if(pBlockTable->has(lpszFileName))
			{
				pBlockTable->getAt(lpszFileName,objectId);
			}
			else
			{
				AcDbDatabase* pDatabase = new AcDbDatabase(false, true);
				pDatabase->readDwgFile(lpszFileName);
				ARXRLEDB->insert(objectId, szName, szName, pDatabase, false);
			}
			pBlockTable->close();
		}
    }
    catch(...)
    {
    }
    
    return objectId;
}

AcDbObjectId InsertBlockRecord(ArxRleString lpszFileName, ArxRleString lpszSource)
{
	AcDbObjectId objectId;
    try
    {
		if(PathFileExists(lpszFileName))
		{
			AcDbBlockTable* pBlockTable;
			ARXRLEDB->getBlockTable(pBlockTable, AcDb::kForRead);
			if(pBlockTable->has(lpszSource))
			{
				pBlockTable->getAt(lpszSource, objectId);
			}
			else
			{
				AcDbDatabase* pDatabase = new AcDbDatabase(false,true);
				pDatabase->readDwgFile(lpszFileName);
				pDatabase->getBlockTable(pBlockTable, AcDb::kForRead);
				if(pBlockTable->has(lpszSource))
				{
					ARXRLEDB->insert(objectId, lpszSource, lpszSource, pDatabase, false);
				}
			}
			pBlockTable->close();
		}
    }
    catch(...)
    {
    }
    
    return objectId;
}

AcDbObjectId InsertBlockRecord(ArxRleString lpszNewName, ArxRleString lpszFileName, ArxRleString lpszSource)
{
	AcDbObjectId objectId;
	try
	{
		AcDbBlockTable* pBlockTable;
		ARXRLEDB->getBlockTable(pBlockTable, AcDb::kForWrite);
		if(pBlockTable->has(lpszNewName))
		{
			pBlockTable->getAt(lpszNewName, objectId);
		}
		else
		{
			if(PathFileExists(lpszFileName))
			{
				AcDbDatabase* pDatabase = new AcDbDatabase(false,true);
				pDatabase->readDwgFile(lpszFileName);

				ARXRLEDB->insert(objectId, lpszSource, lpszNewName, pDatabase, false);
			}
		}
		pBlockTable->close();
	}
	catch(...)
	{
	}
	
	return objectId;
}

AcDbObjectId InsertBlockRecordByReference(ArxRleString lpszName, ArxRleString lpszFileName)
{
	AcDbObjectId objectId;	
	try
	{
		AcDbBlockTable* pBlockTable;
		ARXRLEDB->getBlockTable(pBlockTable,AcDb::kForRead);
		if(pBlockTable->has(lpszName))
		{
			pBlockTable->getAt(lpszName,objectId);
		}
		else
		{
			if(PathFileExists(lpszFileName))
			{
				acdbAttachXref(ARXRLEDB, lpszFileName,  lpszName, objectId);
			}
		}
		pBlockTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

bool GetBlockRecordName(ArxRleString lpszFileName, CStringArray& arrName)
{
	try
	{
		USES_CONVERSION;
		if(PathFileExists(A2T(lpszFileName)))
		{
			AcDbDatabase* pDatabase = new AcDbDatabase(false,true);
			pDatabase->readDwgFile(lpszFileName);
			AcDbBlockTable* pBlockTable;
			pDatabase->getBlockTable(pBlockTable, AcDb::kForRead);
			AcDbBlockTableIterator* pIterator;
			pBlockTable->newIterator(pIterator);
			for(pIterator->start(); !pIterator->done(); pIterator->step())
			{
				AcDbBlockTableRecord* pBlockTblRcd; 
				pIterator->getRecord(pBlockTblRcd, AcDb::kForRead);
				AcString AcName; 
				pBlockTblRcd->getName(AcName);
				if(AcName.find('*') == -1)
					arrName.Add(AcName);
			}
			return true;
		}
	}
	catch(...)
	{
	}
	return false;
}

long GetBlockRecordNameFromFile(ArxRleString lpszFilePath, ArxRleString lpszName, long nLength)
{
	CStringArray arrName;
	GetBlockRecordName(lpszFilePath, arrName);
	ZeroMemory(lpszName, nLength);
	long i = 0;
	for(long i = 0; i < arrName.GetCount(); i ++)
	{
		if(nLength - (long)strlen(lpszName) < arrName[i].GetLength() + 1)
			break;
		USES_CONVERSION;
		StrCat(lpszName, arrName[i]);
		StrCat(lpszName, L";");
	}

	return i;
}

void SetInsbase(CPt3d ptInsBase)
{
	ARXRLEDB->setInsbase(AcGePoint3d(ptInsBase.x, ptInsBase.y, ptInsBase.z));
}

CPt3d GetInsbase()
{
	return CPt3d(ARXRLEDB->insbase());
}

AcDbObjectId AddDimensionStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable,AcDb::kForWrite);
		AcDbDimStyleTableRecord* pDimStyleTblRcd = new AcDbDimStyleTableRecord;
		if(pDimStyleTable->has(lpszName))
			pDimStyleTable->getAt(lpszName,objectId);
		else
		{
			pDimStyleTable->add(pDimStyleTblRcd);
			pDimStyleTblRcd->setName(lpszName);
		}
		pDimStyleTblRcd->close();
		pDimStyleTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

void AddDimensionStyle(AcDbDimStyleTableRecord* pDimStyleRecord)
{
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable,AcDb::kForWrite);
		AcString AcName;
		pDimStyleRecord->getName(AcName);
		if(!pDimStyleTable->has(AcName))
			pDimStyleTable->add(pDimStyleRecord);
		pDimStyleTable->close();
	}
	catch(...)
	{
	}
}

AcDbObjectId GetDimensionStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable,AcDb::kForWrite);

		if(pDimStyleTable->has(lpszName))
		{
			pDimStyleTable->getAt(lpszName,objectId);
		}
		pDimStyleTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

AcDbObjectId GetStandardDimensionStyle()
{
	AcDbObjectId objectId;
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable,AcDb::kForRead);

		AcString AcName("Standard");
		if(pDimStyleTable->has(AcName))
		{
			pDimStyleTable->getAt(AcName,objectId);
		}
		pDimStyleTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

bool SetCurDimensionStyle(ArxRleString lpszName)
{
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable,AcDb::kForWrite);
		if(pDimStyleTable->has(lpszName))
		{
			AcDbObjectId objectId;
			pDimStyleTable->getAt(lpszName,objectId);
			ARXRLEDB->setDimstyleData(objectId);
			ARXRLEDB->setDimstyle(objectId);
			pDimStyleTable->close();
			return true;
		}
		pDimStyleTable->close();
	}
	catch(...)
	{
	}

	return false;
}

void LoadLineType(ArxRleString lpszFile, ArxRleString lpszName)
{
	try
	{
		try
		{
			if(strcmp(lpszName, "*") != 0)
				ARXRLEDB->loadLineTypeFile(lpszName, lpszFile);
			else
			{
				CStringArray arrName;
				GetLineTypeFromFile(lpszFile, arrName);
				for(int i = 0; i < arrName.GetCount(); i ++)
				{
					AcString AcName = arrName[i];
					int nLen = AcName.find(',');
					ARXRLEDB->loadLineTypeFile(AcName.mid(0,nLen), lpszFile);
				}
			}
		}
		catch(...)
		{
		}
	}
	catch(...)
	{

	}
}

bool SetCurLineType(ArxRleString lpszName)
{
	try
	{
		if(lpszName.GetLength() > 0)
		{
			AcDbLinetypeTable* pLinetypeTable;
			ARXRLEDB->getLinetypeTable(pLinetypeTable, AcDb::kForRead);
			if(pLinetypeTable->has(lpszName))
			{
				AcDbObjectId objectId;
				pLinetypeTable->getAt(lpszName, objectId);
				ARXRLEDB->setCeltype(objectId);
			}
			pLinetypeTable->close();
		}
	}
	catch(...)
	{
	}
	return false;
}

void SetLTScale(double fScalse)
{
	struct resbuf result;
	acedGetVar(_T("LTSCALE"),&result);
	result.resval.rreal = fScalse;
	acedSetVar(_T("LTSCALE"), &result);

	//AcDbLayerTable *pLayerTable;  //������һ���յĲ��ָ��
	//AcDbDatabase* db = ARXRLEDB;  //��ǰͼ�����ݿ�
	//if(db->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //�򿪲��Ϊд��״̬
	//{
	//	acutPrintf(_T("�޷���ȡ����ǰ���ͼ�����ݿ��ͼ��ָ��"));
	//	return;
	//}

	//db->setLtscale(fScalse);
	//db->setLineWeightDisplay(FALSE);
}

ArxRleString GetCurLineType()
{
	AcDbObjectId objectId = ARXRLEDB->celtype();
	AcDbLinetypeTableRecord* pLineTypeTblRcd = (AcDbLinetypeTableRecord*)GetRecordPtr(objectId);
	AcString lpszName;
	pLineTypeTblRcd->getName(lpszName);
	pLineTypeTblRcd->close();
	return lpszName;
}

AcDbObjectId GetLineType(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	try
	{
		try
		{
			AcDbLinetypeTable* pLinetypeTable;
			ARXRLEDB->getLinetypeTable(pLinetypeTable, AcDb::kForRead);

			if(pLinetypeTable->has(lpszName))
			{
				pLinetypeTable->getAt(lpszName, objectId);
			}
			pLinetypeTable->close();
		}
		catch(...)
		{
		}
	}
	catch(...)
	{
	}

	return objectId;
}

bool GetLineTypeFromFile(ArxRleString lpszFile, CStringArray& arrLine)
{
	if(lpszFile.GetLength() < 0 || !PathFileExists(lpszFile))
		return false;
	arrLine.RemoveAll();

	ifstream in;
	in.open(lpszFile.c_ptr(), ios::in);
	if(!in.fail())
	{
		char szLine[1024];
		while(1)
		{
			in.getline(szLine, _countof(szLine));
			if(in.fail())
				break;
			StrTrim(ArxRleString(szLine), L" ");
			if(szLine[0] == '*')
			{
				arrLine.Add(ArxRleString(szLine + 1).t_str());
			}
		}
		in.close();

		return true;
	}

	return false;
}

AcDbObjectId AddTextStyle(ArxRleString lpszName, ArxRleString lpszFontName, ArxRleString lpszBigFontName, double fWidthFactor)
{
	AcDbObjectId objectId;
	try
	{
		AcDbTextStyleTable* pTextStyleTable;
		ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForWrite);
		if(pTextStyleTable->has(lpszName))
		{
			pTextStyleTable->getAt(lpszName, objectId);
		}
		else
		{
			AcDbTextStyleTableRecord* pTextStyleTblRcd = new AcDbTextStyleTableRecord;
			pTextStyleTblRcd->setName(lpszName);
			pTextStyleTblRcd->setFileName(lpszFontName);
			if(lpszBigFontName.GetLength() > 0)
				pTextStyleTblRcd->setBigFontFileName(lpszBigFontName);
			pTextStyleTblRcd->setXScale(fWidthFactor);
			
			pTextStyleTable->add(objectId, pTextStyleTblRcd);
			pTextStyleTblRcd->close();
		}
		pTextStyleTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

AcDbObjectId FindTextStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbTextStyleTable* pTextStyleTable;
	ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForRead);
	if(lpszName.GetLength() > 0)
	{
		if(pTextStyleTable->has(lpszName))
		{
			pTextStyleTable->getAt(lpszName, objectId);
		}
	}
	else
	{
		pTextStyleTable->getAt(AcString("Standard"), objectId);
	}
	pTextStyleTable->close();

    return objectId;
}

AcDbObjectId GetStandardTextStyle()
{
	AcDbTextStyleTable* pTextStyleTable;
	ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForRead);
	AcDbObjectId objectId;
	pTextStyleTable->getAt(AcString("Standard"), objectId);
	pTextStyleTable->close();
	return objectId;
}

AcDbObjectId SetCurTextStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbTextStyleTable* pTextStyleTable;
	ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForRead);
	if(pTextStyleTable->has(lpszName))
	{
		pTextStyleTable->getAt(lpszName, objectId);
		ARXRLEDB->setTextstyle(objectId);

// 		struct resbuf result;
// 		acedGetVar(_T("TEXTSTYLE"),&result);
// 		result.resval.rstring = lpszName;
// 		acedSetVar(_T("TEXTSTYLE"), &result);
	}
	pTextStyleTable->close();

	return objectId;
}

AcDbObjectId GetCurTextStyle()
{
	AcDbObjectId objectId;
	struct resbuf result;
	acedGetVar(_T("TEXTSTYLE"),&result);
	AcString AcName(result.resval.rstring);
	AcDbTextStyleTable* pTextStyleTable;
	ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForRead);
	if(pTextStyleTable->has(AcName))
	{
		pTextStyleTable->getAt(AcName, objectId);
	}
	pTextStyleTable->close();
	return objectId;
}

AcDbObjectId GetCurTableStyle()
{
	return ARXRLEDB->tablestyle();
}

AcDbObjectId AddDimStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	try
	{
		AcDbDimStyleTable* pDimStyleTable;
		ARXRLEDB->getDimStyleTable(pDimStyleTable, AcDb::kForWrite);
		if(pDimStyleTable->has(lpszName))
		{
			pDimStyleTable->getAt(lpszName, objectId);
		}
		else
		{
			AcDbDimStyleTableRecord* pDimStyleTblRcd = new AcDbDimStyleTableRecord;
			pDimStyleTblRcd->setName(lpszName);
			pDimStyleTable->add(objectId, pDimStyleTblRcd);
			pDimStyleTblRcd->close();
		}
		pDimStyleTable->close();
	}
	catch(...)
	{
	}

	return objectId;
}

AcDbObjectId GetStandardDimStyle()
{
	AcDbDimStyleTable* pDimStyleTable;
	ARXRLEDB->getDimStyleTable(pDimStyleTable, AcDb::kForRead);
	AcDbObjectId objectId;
	pDimStyleTable->getAt(AcString("Standard"), objectId);
	pDimStyleTable->close();
	return objectId;
}

AcDbObjectId SetCurDimStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbDimStyleTable* pDimStyleTable;
	ARXRLEDB->getDimStyleTable(pDimStyleTable, AcDb::kForRead);
	if(pDimStyleTable->has(lpszName))
	{
		pDimStyleTable->getAt(lpszName, objectId);
		ARXRLEDB->setDimstyle(objectId);
	}
	pDimStyleTable->close();

	return objectId;
}

AcDbObjectId FindDimStyle(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbDimStyleTable* pDimStyleTable;
	ARXRLEDB->getDimStyleTable(pDimStyleTable, AcDb::kForRead);
	if(lpszName.GetLength() > 0)
	{
		if(pDimStyleTable->has(lpszName))
		{
			pDimStyleTable->getAt(lpszName, objectId);
		}
	}
	else
	{
		pDimStyleTable->getAt(AcString("Standard"), objectId);
	}
	pDimStyleTable->close();

	return objectId;
}

AcDbObjectId GetCurDimStyle()
{
	return ARXRLEDB->dimstyle();
}

void SetPointMode(POINTMODE mode)
{
	ARXRLEDB->setPdmode(mode);
}

POINTMODE GetPointMode()
{
	return POINTMODE(ARXRLEDB->pdmode());
}

void SetPointSize(double fSize)
{
	ARXRLEDB->setPdsize(fSize);
}

double GetPointSize()
{
	return ARXRLEDB->pdsize();
}

void SetLimits(const CPt3d ptMin, const CPt3d ptMax, bool bCheck)
{
	ARXRLEDB->setLimmin(AcGePoint2d(ptMin.x, ptMin.y));
	ARXRLEDB->setLimmax(AcGePoint2d(ptMax.x, ptMax.y));
	ARXRLEDB->setLimcheck(bCheck);
}

void GetLimits(CPt3d& ptMin, CPt3d& ptMax, bool& bCheck)
{
	AcGePoint2d odMin, odMax;
	odMin = ARXRLEDB->limmin();
	odMax = ARXRLEDB->limmax();
	ptMin = odMin;
	ptMax = odMax;
	bCheck = ARXRLEDB->limcheck();
}

AcDbObjectId AddUcs(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbUCSTable* pUcsTable;
	ARXRLEDB->getUCSTable(pUcsTable, AcDb::kForWrite);
	if(pUcsTable->has(lpszName))
	{
		pUcsTable->getAt(lpszName, objectId);
	}
	else
	{
		AcDbUCSTableRecord* pUcsTableRcd = new AcDbUCSTableRecord;
		pUcsTableRcd->setName(lpszName);
		pUcsTable->add(pUcsTableRcd);
		objectId = pUcsTableRcd->objectId();
		pUcsTableRcd->close();
	}
	pUcsTable->close();
	return objectId;
}

AcDbObjectId SetCurrentUcs(CPt3d ptOrigin, CPt3d xAxis, CPt3d yAxis)
{
	AcDbObjectId objectId;
	AcDbUCSTableRecord* pUcsTableRcd = new AcDbUCSTableRecord;
	pUcsTableRcd->setOrigin(ptOrigin);
	pUcsTableRcd->setXAxis(xAxis);
	pUcsTableRcd->setYAxis(yAxis);
	objectId= pUcsTableRcd->objectId();
	ARXRLEDB->setUcsBase(objectId);
	pUcsTableRcd->close();
	return objectId;
}

void SetCurrentUcs(AcDbUCSTableRecord* pUcsTableRcd)
{
	ARXRLEDB->setUcsBase(pUcsTableRcd->objectId());
}

AcDbObjectId SetCurrentUcs(ArxRleString lpszName)
{
	AcDbObjectId objectId;
	AcDbUCSTable* pUcsTable;
	ARXRLEDB->getUCSTable(pUcsTable, AcDb::kForWrite);
	if(pUcsTable->has(lpszName))
	{
		pUcsTable->getAt(lpszName, objectId);
		ARXRLEDB->setUcsBase(objectId);
	}
	pUcsTable->close();

	return objectId;
}

CPt3dArray ReadPtDataFile(ArxRleString strPointFile, bool bChange)
{
	CPt3dArray oPointArray;
	if(PathFileExists(strPointFile))
	{
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(strPointFile, CFile::modeRead))
		{
			int nPos = 0;
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				strLine.Replace(_T("��"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("��"), _T(";"));
				if(strLine.GetLength() == 0)
					continue;

 				CStringArray arrSubStr;
 				int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

				CPt3d pt;
				if(cnt == 2)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = 0;
				}
				if(cnt == 3)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = _tstof(arrSubStr[2]);
				}
				oPointArray.push_back(pt);
			}

			file.Close();
		}
	}

	return oPointArray;
}

bool WritePtDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile)
{
	setlocale(LC_ALL,"");

	CStdioFile file;
	if(file.Open(strPointFile, CFile::modeCreate | CFile::modeReadWrite))
	{
		file.Seek(CFile::begin,0);
		for(UINT i=0; i<oPointArray.size(); i++)
		{
			CPt3d& pt = oPointArray[i];
			CString strTemp;
			strTemp.Format(_T("%.3f;%.3f;%.3f\n"),pt.x,pt.y,pt.z);
			file.WriteString(strTemp);
		}

		file.Close();
		return TRUE;
	}

	return FALSE;
}

CPt3dArray ReadZdmDataFile(ArxRleString strPointFile, bool bChange)
{
	CPt3dArray oPointArray;
	if(PathFileExists(strPointFile))
	{
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(strPointFile, CFile::modeRead))
		{
			int nPos = 0;
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				strLine.Replace(_T("��"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("��"), _T(";"));
				if(strLine.GetLength() == 0)
					continue;

				CStringArray arrSubStr;
				int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

				CPt3d pt;
				if(cnt == 2)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = 0;
				}
				if(cnt == 3)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = _tstof(arrSubStr[2]);
				}
				oPointArray.push_back(pt);
			}

			file.Close();
		}
	}

	CPt3dArray oPointArrayZdm;
	CPt3d ptBase = oPointArray[0];
	for(int i=0; i<oPointArray.size(); i++)
	{
		CPt3d pt = oPointArray[i];
		oPointArrayZdm.push_back(CPt3d(sqrt((pt.x-ptBase.x)*(pt.x-ptBase.x)+(pt.y-ptBase.y)*(pt.y-ptBase.y)),pt.z-ptBase.z,pt.z));
	}

	return oPointArrayZdm;
}

bool WriteZdmDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile,double stat, double height)
{
	setlocale(LC_ALL,"");

	CStdioFile file;
	if(file.Open(strPointFile, CFile::modeCreate | CFile::modeReadWrite))
	{
		file.Seek(CFile::begin,0);
		CPt3d ptBegin = oPointArray[0];
		CString strTemp;
		strTemp.Format(_T("׮��;�߳�\n"));
		file.WriteString(strTemp);
		strTemp.Format(_T("%.3f;%.3f\n"),stat,height);
		file.WriteString(strTemp);
		for(UINT i=1; i<oPointArray.size(); i++)
		{
			CPt3d pt = oPointArray[i];
			double s = stat+pt.x-ptBegin.x;
			double h = height+pt.y-ptBegin.y;
			strTemp.Format(_T("%.3f;%.3f\n"),s,h);
			file.WriteString(strTemp);
		}

		file.Close();
		return TRUE;
	}

	return FALSE;
}

CPt3dArray ReadHdmDataFile(ArxRleString strPointFile, bool bChange)
{
	CPt3dArray oPointArray;
	if(PathFileExists(strPointFile))
	{
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(strPointFile, CFile::modeRead))
		{
			int nPos = 0;
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				strLine.Replace(_T("��"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("��"), _T(";"));
				if(strLine.GetLength() == 0)
					continue;

				CStringArray arrSubStr;
				int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

				CPt3d pt;
				if(cnt == 2)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = 0;
				}
				if(cnt == 3)
				{
					pt.x = !bChange ? _tstof(arrSubStr[0]):_tstof(arrSubStr[1]);
					pt.y = !bChange ? _tstof(arrSubStr[1]):_tstof(arrSubStr[0]);
					pt.z = _tstof(arrSubStr[2]);
				}
				oPointArray.push_back(pt);
			}

			file.Close();
		}
	}

	CPt3dArray oPointArrayHdm;
	CPt3d ptBase = oPointArray[0];
	for(int i=0; i<oPointArray.size(); i++)
	{
		CPt3d pt = oPointArray[i];

		oPointArrayHdm.push_back(CPt3d(sqrt((pt.x-ptBase.x)*(pt.x-ptBase.x)+(pt.y-ptBase.y)*(pt.y-ptBase.y)),pt.z-ptBase.z,pt.z));
	}

	return oPointArrayHdm;
}

bool WriteHdmDataFile(CPt3dArray& oPointArray, ArxRleString strPointFile, int id, double height)
{
	setlocale(LC_ALL,"");

	CStdioFile file;
	if(file.Open(strPointFile, CFile::modeCreate | CFile::modeReadWrite))
	{
		file.Seek(CFile::begin,0);
		CPt3d ptBegin = oPointArray[id];
		CString strTemp;
		strTemp.Format(_T("����;�߳�\n"));
		file.WriteString(strTemp);
		for(UINT i=0; i<oPointArray.size(); i++)
		{
			CPt3d pt = oPointArray[i];
			if(i == id)
			{
				strTemp.Format(_T("0.000;%.3f\n"),height);
				file.WriteString(strTemp);
			}
			else
			{
				double s = pt.x-ptBegin.x;
				double h = height+pt.y-ptBegin.y;
				strTemp.Format(_T("%.3f;%.3f\n"),s,h);
				file.WriteString(strTemp);
			}
		}

		file.Close();
		return TRUE;
	}

	return FALSE;
}

double AdjustAngle02(double fAngle) //���� �Ƕȵ�����0��2��֮��
{
	fAngle = AdjustAngleNP(fAngle);
	if(BetweenFloat(fAngle, -PI, PI))
		return fAngle;
	else if(CompareFloat(fAngle, PI) >= 0)
	{
		return fAngle - PI * 2;
	}
	else
	{
		return fAngle + PI * 2;
	}
}

double AdjustAngleNP(double fAngle) //���� �Ƕȵ�����-�е���֮��
{
	if(BetweenFloat(fAngle, 0, PI * 2))
		return fAngle;
	else if(CompareFloat(fAngle, PI * 2) >= 0)
	{
		short n = short(fAngle / (PI * 2));
		return fAngle - n * PI * 2;
	}
	else
	{
		short n = short(fAngle / (PI * 2)) - 1;
		return fAngle - n * PI * 2;
	}
}

int GetACIByRGB(byte r, byte g, byte b)
{
	return AcCmEntityColor::lookUpACI(r, g, b);
}

int GetACIByREF(COLORREF clr)
{
	int r = GetRValue(clr), g = GetGValue(clr), b = GetBValue(clr);
	return AcCmEntityColor::lookUpACI(r, g, b);
}

COLORREF GetRGBByACI(int aci)
{
	//return acdbGetRGB(aci);
	COLORREF clr = AcCmEntityColor::lookUpRGB(aci);
	return RGB(GetBValue(clr), GetGValue(clr), GetRValue(clr));
}

CPt3d GetNewPoint(CPt3d& oBeginPt, double fOffsetLength, double fRadiusotation)
{
	fOffsetLength = fabs(fOffsetLength);
	fRadiusotation -= 2 * PI;//������ڵ���2*PI��ת�Ƕ�
	if(fRadiusotation < 0) //�����˳ʱ����ת��ת������ʱ��Ƕ�
		fRadiusotation = 2 * PI + fRadiusotation;

	CPt3d srcNewPt(oBeginPt.x + fOffsetLength * cos(fRadiusotation), oBeginPt.y + fOffsetLength * sin(fRadiusotation), oBeginPt.z);

	return srcNewPt;
}

double GetDistOf2Pts(CPt3d& oBeginPt, CPt3d& oEndPt, bool bSpace)
{
	double fDistance = 0;
	if(bSpace)
		fDistance = sqrt(ex((oEndPt.x-oBeginPt.x),2)+ex((oEndPt.y-oBeginPt.y),2)+ex((oEndPt.z-oBeginPt.z),2));
	else
		fDistance = sqrt(ex((oEndPt.x-oBeginPt.x),2)+ex((oEndPt.y-oBeginPt.y),2));

	return fDistance;
}

double GetAngleOf2Pts(CPt3d& oBeginPt, CPt3d& oEndPt)
{
	if(Equal(oEndPt.x, oBeginPt.x))
	{
		if (oEndPt.y > oBeginPt.y)
		{
			return PI * 0.5;
		}
		else 
		{
			return PI * 1.5;
		}
	}
	else if (Equal(oEndPt.y, oBeginPt.y))
	{
		if (oEndPt.x > oBeginPt.x)
		{
			return 0;
		}
		else
		{
			return PI;
		}
	}
	else
	{
		double fRadiusesult = atan((oBeginPt.y - oEndPt.y) / (oBeginPt.x - oEndPt.x));
		if ((oEndPt.x < oBeginPt.x) && (oEndPt.y > oBeginPt.y))
		{
			return fRadiusesult + PI;
		}
		else if ((oEndPt.x < oBeginPt.x) && (oEndPt.y < oBeginPt.y))
		{
			return fRadiusesult + PI;
		}
		else if ((oEndPt.x > oBeginPt.x) && (oEndPt.y < oBeginPt.y))
		{
			return fRadiusesult + 2 * PI;
		}
		else 
		{
			return fRadiusesult;
		}
	}
}

int JudgePointOnLine(CPt3d& oPoint, CPt3d& oLineBeginPt, CPt3d& oLineEndPt)
{
	//����Ҫ�жϽ����Ƿ��������߶���
	double fLenOfCPtToBeginPt = GetDistOf2Pts(oPoint, oLineBeginPt);
	double fLenOfCPtToEndPt = GetDistOf2Pts(oPoint, oLineEndPt);
	double fLenOfBeginPtToEndPt = GetDistOf2Pts(oLineBeginPt, oLineEndPt);
	if(CompareBothDouble((fLenOfCPtToBeginPt+fLenOfCPtToEndPt), fLenOfBeginPtToEndPt, DISTANCE_PRECISION) <= 0)
		return true;

	return false;
}

int JudgePointOnCircle(CPt3d& oPoint, CPt3d& oCenterPt, double fRadius)
{
	double fDistance = GetDistOf2Pts(oPoint, oCenterPt);
	if (Equal(fDistance, fRadius))
	{
		return 0;
	}
	else if (fDistance > fRadius)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int JudgePointOnArc(CPt3d& oPoint, CPt3d& oCenterPt, CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius)
{
	double fDistance = GetDistOf2Pts(oCenterPt, oPoint);
	if (fDistance > fRadius)
		return -2;

	if (Equal(fDistance, fRadius, DISTANCE_PRECISION))
	{
		double fBeginAngle = GetAngleOf2Pts(oCenterPt, oBeginPt);
		double fEndAngle = GetAngleOf2Pts(oCenterPt, oEndPt);
		double fAngle = GetAngleOf2Pts(oCenterPt, oPoint);
		if ((CompareBothDouble(fAngle, fBeginAngle, ANGLE_PRECISION) >= 0 && CompareBothDouble(fAngle, fEndAngle, ANGLE_PRECISION) <= 0) ||
			(CompareBothDouble(fAngle, fBeginAngle, ANGLE_PRECISION) <= 0 && CompareBothDouble(fAngle, fEndAngle, ANGLE_PRECISION) >= 0))
			return 1;
		else
			return 0;
	}

	if(fDistance < fRadius)
		return -1;

	return -1;
}

AcDbDatabase* ArxRleDataBase()
{
	return acdbHostApplicationServices()->workingDatabase();
}

AcDbBlockTableRecord* ArxRleDrawSpace()
{
	AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
	AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
	if(!objectId.isNull())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
		AcDbLayout *pLayout = AcDbLayout::cast(obj);

		AcDbObjectId objId = pLayout->getBlockTableRecordId();
		ACHAR* AcName;
		if(pLayout->getLayoutName(AcName) == Acad::eOk)
			pLayMan->setCurrentLayout(AcName);

		pLayout->close();
		return (AcDbBlockTableRecord*)GetRecordPtr(objId);
	}
	else
	{
		AcDbObjectId objectId = ARXRLEDB->currentSpaceId();
		return (AcDbBlockTableRecord*)GetRecordPtr(objectId);
	}
}

AcDbPlotSettingsValidator* ArxRlePlotSettingsValidator()
{
	return acdbHostApplicationServices()->plotSettingsValidator();
}

AcDbDataLinkManager* ArxRleDataLinkManager()
{
	return acdbHostApplicationServices()->workingDatabase()->getDataLinkManager();
}

AcApDocument* ArxRleApDocument() //kWrite
{
	AcApDocument *pDoc=acDocManager->curDocument();
	acDocManager->lockDocument(pDoc,AcAp::kWrite);
	return pDoc;
}

void SendMsgToAcad(ArxRleString cmd)
{
	ACHAR* msg = cmd.w_ptr();
	COPYDATASTRUCT cmdMsg;
	cmdMsg.dwData = (DWORD)1;
	cmdMsg.cbData = (DWORD)(_tcslen(msg) + 1) * sizeof(ACHAR);
	cmdMsg.lpData = msg;
	SendMessage(adsw_acadMainWnd(), WM_COPYDATA, NULL, (LPARAM)&cmdMsg);
}

void SendCmdToAcad(ArxRleString cmd)
{
	TRY
	{
		CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));
		LPDISPATCH lpDisp = IAcad.get_ActiveDocument();
		if(lpDisp != NULL)
		{
			CAcadDocument IDoc(lpDisp);
			IDoc.SendCommand(cmd.t_str());
			lpDisp->Release();
		}
	}
	CATCH(COleDispatchException,e)
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void SendCmdToAcad(ArxRleString cmd, ArxRleString pram)
{
	acedCommandS(RTSTR, cmd.t_str(), RTSTR, pram.t_str(), RTNONE);
	//acDocManager->sendStringToExecute(curDoc(), _T("_POINT 2,2,0 "));
	//ads_queueexpr(L"command\"_POINT\" \"1,1,0\"");
}

ArxRleString GetCurDwgFilePath()
{
	AcApDocument *pDoc=acDocManager->curDocument();
	CString strCurFilePathName(pDoc->fileName());
	strCurFilePathName.Mid(0, strCurFilePathName.ReverseFind('\\'))+_T("\\");
	return strCurFilePathName;
}

Acad::ErrorStatus OpenEntity(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode, bool lockDocument, bool openErasedEntity)
{
	// �����޸�֮ǰ�������ĵ�
	if(lockDocument) acDocManager->lockDocument(acDocManager->curDocument(),mode ? AcAp::kWrite : AcAp::kRead);

	return acdbOpenAcDbEntity(pEnt, id, mode, openErasedEntity);
}

void CloseEntity(AcDbEntity* pEnt, bool unLockDocument, bool flushGraphics)
{
	pEnt->close();

	// �����޸���ɣ������ĵ�
	if(unLockDocument) acDocManager->unlockDocument(acDocManager->curDocument());

	// ˢ����ʾ
	if(flushGraphics) actrTransactionManager->flushGraphics();
}

AcDbBlockTableRecord* GetDrawSpace(ArxSpaceType SpaceType)
{
	AcDbBlockTableRecord* pSpace = new AcDbBlockTableRecord;
	AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
	switch(SpaceType)
	{
	case ArxModel:
		{
			AcDbObjectId objectId = pLayMan->findLayoutNamed(AcString("*Model_Space"));
			if (objectId.isValid())
			{
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	case ArxActive:
		{
			AcDbObjectId objectId = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE));
			if(!objectId.isNull())
			{
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	case ArxPaper:
		{
			AcDbObjectId objectId = pLayMan->findLayoutNamed(AcString("*Paper_Space"));
			if(!objectId.isNull())
			{
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	default:
		break;
	}

	return pSpace;
}

AcDbBlockTableRecord* SetDrawSpace(ArxSpaceType SpaceType)
{
	AcDbBlockTableRecord* pSpace = new AcDbBlockTableRecord;
	AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();
	switch(SpaceType)
	{
	case ArxModel:
		{
			AcDbObjectId objectId = pLayMan->findLayoutNamed(AcString("*Model_Space"));
			if(!objectId.isNull())
			{
				pLayMan->setCurrentLayout(L"*Model_Space");
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	case ArxActive:
		{
			const ACHAR* szName = pLayMan->findActiveLayout(TRUE);
			AcDbObjectId objectId = pLayMan->findLayoutNamed(szName);
			if(!objectId.isNull())
			{
				pLayMan->setCurrentLayout(szName);
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	case ArxPaper:
		{
			AcDbObjectId objectId = pLayMan->findLayoutNamed(AcString("*Paper_Space"));
			if(!objectId.isNull())
			{
				pLayMan->setCurrentLayout(AcString("*Paper_Space"));
				AcDbObject* obj;
				acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
				AcDbLayout* pLayout = AcDbLayout::cast(obj);
				AcDbObjectId objId = pLayout->getBlockTableRecordId();
				pSpace = (AcDbBlockTableRecord*)GetRecordPtr(objId);
				pLayout->close();
			}
		}
		break;
	default:
		break;
	}

	return pSpace;
}

bool ArxRleSave()
{
	Acad::ErrorStatus es = ARXRLEDB->save();
	if(es == Acad::eOk)
		return true;
	else
		return false;
}

void AddEntity(CEntity* pEntity)
{
	AcDbEntity* pEnt = (AcDbEntity*)pEntity->getent()->clone();
	pEnt->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pEnt, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pEnt, ARXRLEDB);
}

AcDbObjectId add_Entity(AcDbEntity *pEntity)
{
	AcDbBlockTable* pBlockTable;
	ARXRLEDB->getBlockTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord*  pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId objId; 
	pBlockTableRecord->appendAcDbEntity(objId,pEntity);

	pEntity->close();
	pBlockTableRecord->close();
	pBlockTable->close();
	return objId;
}

AcDbObjectId AddEntity(AcDbEntity *pEntity)
{
	pEntity->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pEntity, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pEntity, ARXRLEDB);
	return pEntity->objectId();
}

void add_Point(double fX, double fY, double fZ)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;

		SAFEARRAY* psaPoint = NULL;
		psaPoint = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPoint != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPoint, &index, &fX);
			index++;
			SafeArrayPutElement(psaPoint, &index, &fY);
			index++;
			SafeArrayPutElement(psaPoint, &index, &fZ);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPoint;
			IMSpace.AddPoint(pt);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPoint);
		}
		else
			acutPrintf(_T("\n---DWG����ӵ�ʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddPoint(double fX, double fY, double fZ)
{
	AcDbPoint* pPt = new AcDbPoint;
	pPt->setPosition(AcGePoint3d(fX,fY,fZ));
	AcGeVector3d ucsZAxis = ArxRleUtils::getUcsZAxis(ARXRLEDB);
	AcGeVector3d ucsXAxis = ArxRleUtils::getUcsXAxis(ARXRLEDB);
	AcGeVector3d entXAxis;
	ArxRleUtils::getEcsXAxis(ucsZAxis, entXAxis);   // get AutoCAD's arbitrary X-Axis
	pPt->setEcsRotation(ucsXAxis.angleTo(entXAxis, ucsZAxis));
	pPt->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pPt, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pPt);
}

void AddPoint(CPt3d& oPoint3D)
{
	AddPoint(oPoint3D.x,oPoint3D.y,oPoint3D.z);
}

void AddPoint(CPt3dArray& oPointArray)
{
	for(long i=0; i<(long)oPointArray.size(); i++)
	{
		CPt3d& srcPt = oPointArray[i];
		AddPoint(srcPt.x,srcPt.y,srcPt.z);
	}
}

void AddPoint()
{
	ArxRleUiPrPoint pt(_T("Insert point"), NULL);
	if(pt.go() != ArxRleUiPrBase::kOk)
		return;

	AddPoint(CPt3d(pt.value()));
}

void add_Line(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt1,sabPt2;//��ȫ���������ṹ
		sabPt1.lLbound = 0L;  //����
		sabPt1.cElements = 3; //Ԫ�ظ���
		sabPt2.lLbound = 0L;
		sabPt2.cElements = 3;

		SAFEARRAY *psaPt1 = NULL, *psaPt2 = NULL;  //��ȫ����
		psaPt1 = SafeArrayCreate(VT_R8, 1, &sabPt1); //����һ��һά��ȫ����
		psaPt2 = SafeArrayCreate(VT_R8, 1, &sabPt2);
		if(psaPt1 != NULL && psaPt2 != NULL)
		{
			long index = 0; // Ԫ��λ�������������У�����������1��1��;
			SafeArrayPutElement(psaPt1, &index, &fX1);//��ȫ���������Ԫ��
			index++;
			SafeArrayPutElement(psaPt1, &index, &fY1);
			index++;
			SafeArrayPutElement(psaPt1, &index, &fZ1);

			index = 0;
			SafeArrayPutElement(psaPt2, &index, &fX2);
			index++;
			SafeArrayPutElement(psaPt2, &index, &fY2);
			index++;
			SafeArrayPutElement(psaPt2, &index, &fZ2);

			VARIANT pt1,pt2;
			VariantInit(&pt1);
			V_VT(&pt1) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt1) = psaPt1;
			VariantInit(&pt2);
			V_VT(&pt2) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt2) = psaPt2;
			IMSpace.AddLine(pt1,pt2);

			VariantClear(&pt1);
			VariantClear(&pt2);
			//SafeArrayDestroy(psaPt1);
			//SafeArrayDestroy(psaPt2);
		}
		else
			acutPrintf(_T("\n---DWG�����ֱ��ʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddLine(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2)
{
	AcDbLine* pLine = new AcDbLine;
	pLine->setDatabaseDefaults();
	pLine->setStartPoint(AcGePoint3d(fX1,fY1,fZ1));
	pLine->setEndPoint(AcGePoint3d(fX2,fY2,fZ2));

	ArxRleUtils::transformToWcs(pLine, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pLine);
}

void AddLine(CPt3d& oBeginPt, CPt3d& oEndPt)
{
	AddLine(oBeginPt.x,oBeginPt.y,oBeginPt.z,oEndPt.x,oEndPt.y,oEndPt.z);
}

void add_Polyline(CPt3dArray& oPointArray)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);
		long nVertices = oPointArray.size();

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3*nVertices;

		SAFEARRAY* psaPts = NULL;
		psaPts = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPts != NULL)
		{
			long index = 0;
			for(long i=0; i<nVertices; i++)
			{
				CPt3d& srcPt = oPointArray[i];

				SafeArrayPutElement(psaPts, &index, &srcPt.x);
				index++;
				SafeArrayPutElement(psaPts, &index, &srcPt.y);
				index++;
				SafeArrayPutElement(psaPts, &index, &srcPt.z);
				index++;
			}

			VARIANT pts;
			VariantInit(&pts);
			V_VT(&pts) = VT_ARRAY | VT_R8;
			V_ARRAY(&pts) = psaPts;

			IMSpace.AddPolyline(pts);

			VariantClear(&pts);
			//SafeArrayDestroy(psaPts);
		}
		else
			acutPrintf(_T("\n---DWG����Ӷ����ʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;

	/*
	//ʹ��SAFEARRARʵ�ֶ�ά����
	{
		VARTYPE vt = VT_I4;    //����Ԫ�ص����ͣ�long
		SAFEARRAYBOUND sab[2]; //���ڶ��������ά�����±����ʼֵ
		sab[0].cElements = 2;
		sab[0].lLbound = 0;
		sab[1].cElements = 2;
		sab[1].lLbound = 0;

		//����һ��2*2������Ϊlong�Ķ�ά����
		SAFEARRAY* psa = SafeArrayCreate(vt, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);
		if(NULL == psa)
			throw;

		//ͨ��ָ�������ָ�����Զ�ά�����Ԫ�ؽ��м�Ӹ�ֵ
		long (*pArray)[2] = NULL;
		HRESULT hRet = SafeArrayAccessData(psa, (void **)&pArray);
		if(FAILED(hRet))
			throw;

		memset(pArray, 0, 2*2*sizeof(long));

		//�ͷ�ָ�������ָ��
		SafeArrayUnaccessData(psa);
		pArray = NULL;

		//�Զ�ά�����Ԫ�ؽ��������ֵ
		long index[2] = {0, 0};
		long lFirstLBound = 0;
		long lFirstUBound = 0;
		long lSecondLBound = 0;
		long lSecondUBound = 0;
		SafeArrayGetLBound(psa, 1, &lFirstLBound);
		SafeArrayGetUBound(psa, 1, &lFirstUBound);
		SafeArrayGetLBound(psa, 2, &lSecondLBound);
		SafeArrayGetUBound(psa, 2, &lSecondUBound);
		for(long i = lFirstLBound; i <= lFirstUBound; i++)
		{
			index[0] = i;
			for(long j = lSecondLBound; j <= lSecondUBound; j++)
			{
				index[1] = j;
				long lElement = i * sab[1].cElements + j; 
				HRESULT hRet = SafeArrayPutElement(psa, index, &lElement);
				if(FAILED(hRet))
					throw;
			}
		}

		//��SAFEARRAYת��ΪVARIANT
		VARIANT var;
		var.vt = VT_ARRAY | vt; //vt�����psa���������ͱ���һ��
		var.parray = psa;
		SafeArrayDestroy(psa);
		psa = NULL;
	}



	//ʹ��COleSafeArrayʵ�ֶ�ά����
	{
		VARTYPE vt = VT_I4; //����Ԫ�ص����ͣ�long
		SAFEARRAYBOUND sab[2]; //���ڶ��������ά�����±����ʼֵ   
		sab[0].cElements = 2;    
		sab[0].lLbound = 0;    
		sab[1].cElements = 2;    
		sab[1].lLbound = 0;    
		COleSafeArray olesa;    
		olesa.Create(vt, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);  
		//ͨ��ָ�������ָ�����Զ�ά�����Ԫ�ؽ��м�Ӹ�ֵ
		long (*pArray)[2] = NULL;
		olesa.AccessData((void **)&pArray);
		memset(pArray, 0, 2*2*sizeof(long));
		//�ͷ�ָ�������ָ��
		olesa.UnaccessData();
		pArray = NULL;

		//�Զ�ά�����Ԫ�ؽ��������ֵ
		long index[2] = {0, 0};
		long lFirstLBound = 0;
		long lFirstUBound = 0;
		long lSecondLBound = 0;
		long lSecondUBound = 0;
		olesa.GetLBound(1, &lFirstLBound);
		olesa.GetUBound(1, &lFirstUBound);
		olesa.GetLBound(2, &lSecondLBound);
		olesa.GetUBound(2, &lSecondUBound);
		for (long i = lFirstLBound; i <= lFirstUBound; i++)
		{
			index[0] = i;
			for (long j = lSecondLBound; j <= lSecondUBound; j++)
			{
				index[1] = j;
				long lElement = i * sab[1].cElements + j; 
				olesa.PutElement(index, &lElement);
			}
		}
		VARIANT var = (VARIANT)olesa; //��COleSafeArray����ת��ΪVARIANT
	}
	*/
}

void AddPolyline(CPt3dArray& oPointArray, double fConstantWidth)
{
	if(oPointArray.size() < 2) return;
	int nPtCnt = oPointArray.size();
	AcDbPolyline* pPolyline = new AcDbPolyline(nPtCnt);

	Acad::ErrorStatus es;
	AcGePoint2d pt;
	for(int i=0;i<nPtCnt;i++)
	{
		pt.set(oPointArray[i].x, oPointArray[i].y);
		es = pPolyline->addVertexAt(i, pt);
		if(es != Acad::eOk)
			ArxRleUtils::rxErrorMsg(es);
	}

	pPolyline->setElevation(oPointArray[0].z);
	pPolyline->setConstantWidth(fConstantWidth);

	pPolyline->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pPolyline, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pPolyline);
}

void AddPolyline(CPt3dArray& oPointArray, vector<unsigned int> index, vector<double> fBeginWidth, vector<double> fEndWidth)
{
	if(oPointArray.size() < 2) return;
	int nPtCnt = oPointArray.size();
	AcDbPolyline* pPolyline = new AcDbPolyline(nPtCnt);

	Acad::ErrorStatus es;
	AcGePoint2d pt;
	for(int i=0;i<nPtCnt;i++)
	{
		pt.set(oPointArray[i].x, oPointArray[i].y);
		es = pPolyline->addVertexAt(i, pt);
		if(es != Acad::eOk)
			ArxRleUtils::rxErrorMsg(es);
	}

	pPolyline->setElevation(oPointArray[0].z);
	int nIndexCnt = index.size();
	for(int i=0; i<nIndexCnt; i++)
		pPolyline->setWidthsAt(index[i],fBeginWidth[i],fEndWidth[i]);

	pPolyline->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pPolyline, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pPolyline);
}

void AddPolyline(CPt3dArray& oPointArray, unsigned int index, double fBeginWidth, double fEndWidth)
{
	if(oPointArray.size() < 2) return;
	int nPtCnt = oPointArray.size();
	AcDbPolyline* pPolyline = new AcDbPolyline(nPtCnt);

	Acad::ErrorStatus es;
	AcGePoint2d pt;
	for(int i=0;i<nPtCnt;i++)
	{
		pt.set(oPointArray[i].x, oPointArray[i].y);
		es = pPolyline->addVertexAt(i, pt);
		if(es != Acad::eOk)
			ArxRleUtils::rxErrorMsg(es);
	}

	pPolyline->setElevation(oPointArray[0].z);
	pPolyline->setWidthsAt(index,fBeginWidth,fEndWidth);

	pPolyline->setDatabaseDefaults();
	ArxRleUtils::transformToWcs(pPolyline, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pPolyline);
}

void AddRectangular(CPt3d& oBeginPt, CPt3d& oEndPt, double fConstantWidth)
{
	CPt3dArray oPointArray;
	CPt3d srcPt1(oBeginPt.x,oBeginPt.y,oBeginPt.z);
	oPointArray.push_back(srcPt1);
	CPt3d srcPt2(oBeginPt.x,oEndPt.y,oBeginPt.z);
	oPointArray.push_back(srcPt2);
	CPt3d srcPt3(oEndPt.x,oEndPt.y,oBeginPt.z);
	oPointArray.push_back(srcPt3);
	CPt3d srcPt4(oEndPt.x,oBeginPt.y,oBeginPt.z);
	oPointArray.push_back(srcPt4);
	CPt3d srcPt5(oBeginPt.x,oBeginPt.y,oBeginPt.z);
	oPointArray.push_back(srcPt5);

	AddPolyline(oPointArray,fConstantWidth);
}

void AddRectangular(double fX1, double fY1, double fZ1,double fX2, double fY2, double fZ2, double fConstantWidth)
{
	AddRectangular(CPt3d(fX1,fY1,fZ1),CPt3d(fX2,fY2,fZ2),fConstantWidth);
}

void add_Circle(CPt3d& oCenterPt, double fRadius)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;
		SAFEARRAY* psaPt = NULL;
		psaPt = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPt != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.x);
			index++;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.y);
			index++;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.z);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPt;
			IMSpace.AddCircle(pt, fRadius);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPt);
		}
		else
			acutPrintf(_T("\n---DWG�����Բʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddCircle(CPt3d& oCenterPt, double fRadius)
{
	AcDbCircle* circle = new AcDbCircle;
	circle->setDatabaseDefaults();
	circle->setCenter(AcGePoint3d(oCenterPt.x,oCenterPt.y,oCenterPt.z));
	circle->setRadius(fRadius);

	ArxRleUtils::transformToWcs(circle, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(circle);
}

void AddCircle(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius)
{
	double fDist = GetDistOf2Pts(oBeginPt, oEndPt);
	double fAngle = GetAngleOf2Pts(oBeginPt, oEndPt);
	CPt3d oCenterPt = GetNewPoint(oBeginPt,fDist/2,fAngle);
	fDist = sqrt(ex(fRadius,2)-ex(fDist/2,2));
	if(fRadius > 0)
		oCenterPt = GetNewPoint(oCenterPt,fDist,fAngle-PI/2);
	else
		oCenterPt = GetNewPoint(oCenterPt,fDist,fAngle+PI/2);

	AddCircle(oCenterPt,fRadius);
}

void AddCircle()
{
	ArxRleUiPrPoint prCenterPt(_T("Center point"), NULL);
	if(prCenterPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDist prRadius(_T("Radius"), NULL, ArxRleUiPrDist::kNoNegNoZero, prCenterPt.value());
	if(prRadius.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbCircle* circle = new AcDbCircle;
	circle->setDatabaseDefaults();
	circle->setCenter(prCenterPt.value());
	circle->setRadius(prRadius.value());
	ArxRleUtils::transformToWcs(circle, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(circle);
}

void add_Arc(CPt3d& oCenterPt, double fRadius, double fBeginAngle, double fEndAngle)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;
		SAFEARRAY* psaPt = NULL;
		psaPt = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPt != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.x);
			index++;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.y);
			index++;
			SafeArrayPutElement(psaPt, &index, &oCenterPt.z);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPt;
			IMSpace.AddArc(pt, fRadius, fBeginAngle, fEndAngle);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPt);
		}
		else
			acutPrintf(_T("\n---DWG�����Բ��ʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddArc(CPt3d& oCenterPt, double fRadius, double fBeginAngle, double fEndAngle)
{
	AcDbArc* arc = new AcDbArc;
	arc->setDatabaseDefaults();
	arc->setCenter(AcGePoint3d(oCenterPt.x,oCenterPt.y,oCenterPt.z));
	arc->setRadius(fRadius);
	arc->setStartAngle(fBeginAngle);
	arc->setEndAngle(fEndAngle);

	ArxRleUtils::transformToWcs(arc, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(arc);
}

void AddArc(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius, bool bMajorArc)
{
	double fDist = GetDistOf2Pts(oBeginPt, oEndPt);
	double fAngle = GetAngleOf2Pts(oBeginPt, oEndPt);
	CPt3d oCenterPt = GetNewPoint(oBeginPt,fDist/2,fAngle);
	if(oBeginPt > oEndPt)
	{
		fAngle = GetAngleOf2Pts(oEndPt, oBeginPt);
		oCenterPt = GetNewPoint(oEndPt,fDist/2,fAngle);
	}
	fDist = sqrt(ex(fRadius,2)-ex(fDist/2,2));
	if(fRadius > 0)
		oCenterPt = GetNewPoint(oCenterPt,fDist,fAngle-PI/2);
	else
		oCenterPt = GetNewPoint(oCenterPt,fDist,fAngle+PI/2);

	double fBeginAngle = GetAngleOf2Pts(oCenterPt,oEndPt);
	double fEndAngle = GetAngleOf2Pts(oCenterPt,oBeginPt);
	if(oBeginPt > oEndPt)
	{
		fBeginAngle = GetAngleOf2Pts(oCenterPt,oBeginPt);
		fEndAngle = GetAngleOf2Pts(oCenterPt,oEndPt);
	}

	if(bMajorArc)
	{
		double fAngle = fEndAngle;
		fEndAngle = fBeginAngle;
		fBeginAngle = fAngle;
	}

	AddArc(oCenterPt, fRadius, fBeginAngle, fEndAngle);
}

void AddArc(CPt3d& oBeginPt, CPt3d& oMidPt, CPt3d& oEndPt)
{
	AcGeCircArc2d geArc(oBeginPt, oMidPt, oEndPt);
	CPt3d ptCenter = geArc.center();
	double fRadius = geArc.radius();
	// ������ʼ����ֹ�Ƕ�
	AcGeVector2d vecStart(oBeginPt.x - ptCenter.x, oBeginPt.y - ptCenter.y);
	AcGeVector2d vecEnd(oEndPt.x - ptCenter.x, oEndPt.y - ptCenter.y);
	double fBeginAngle = vecStart.angle();
	double fEndAngle = vecEnd.angle();

	AddArc(ptCenter, fRadius, fBeginAngle, fEndAngle);
}

double GetArcBulge(CPt3d& oBeginPt, CPt3d& oMidPt, CPt3d& oEndPt)
{
	AcGeCircArc2d geArc(oBeginPt, oMidPt, oEndPt);
	CPt3d ptCenter = geArc.center();
	// ������ʼ����ֹ�Ƕ�
	AcGeVector2d vecStart(oBeginPt.x - ptCenter.x, oBeginPt.y - ptCenter.y);
	AcGeVector2d vecEnd(oEndPt.x - ptCenter.x, oEndPt.y - ptCenter.y);
	double fBeginAngle = vecStart.angle();
	double fEndAngle = vecEnd.angle();

	double fBulge = 0.0;
	double fAlfa = fEndAngle - fBeginAngle;
	if (fAlfa < 0.0)//����յ�Ƕ�С�����Ƕȣ�ȡ����
		fAlfa = 2 * PI + fAlfa;

	fBulge = tan(fAlfa/4);
	return fBulge;
}

double GetArcBulge(CPt3d& oBeginPt, CPt3d& oEndPt, double fRadius, bool bMajorArc)
{
	double fDist = oBeginPt.GetDistance(oEndPt);
	double fAngle = oBeginPt.GetAngle(oEndPt);
	CPt3d oCenterPt = oBeginPt.GetLineEnd(fDist/2,fAngle);
	if(oBeginPt > oEndPt)
	{
		fAngle = oEndPt.GetAngle(oBeginPt);
		oCenterPt = oEndPt.GetLineEnd(fDist/2,fAngle);
	}
	fDist = sqrt(ex(fRadius,2)-ex(fDist/2,2));
	if(fRadius > 0)
		oCenterPt = oCenterPt.GetLineEnd(fDist,fAngle-PI/2);
	else
		oCenterPt = oCenterPt.GetLineEnd(fDist,fAngle+PI/2);

	double fBeginAngle = oCenterPt.GetAngle(oEndPt);
	double fEndAngle = oCenterPt.GetAngle(oBeginPt);
	if(oBeginPt > oEndPt)
	{
		fBeginAngle = oCenterPt.GetAngle(oBeginPt);
		fEndAngle = oCenterPt.GetAngle(oEndPt);
	}

	if(bMajorArc)
	{
		double fAngle = fEndAngle;
		fEndAngle = fBeginAngle;
		fBeginAngle = fAngle;
	}

	double fBulge = 0.0;
	double fAlfa = fEndAngle - fBeginAngle;
	if (fAlfa < 0.0)//����յ�Ƕ�С�����Ƕȣ�ȡ����
		fAlfa = 2 * PI + fAlfa;

	fBulge = tan(fAlfa/4);
	return fBulge;
}

double GetArcBulge(AcDbArc*& pArc)
{
	double dStartAngle = pArc->startAngle();
	double dEndAngle = pArc->endAngle();

	double dAlfa = dEndAngle - dStartAngle;
	if (dAlfa < 0.0)//����յ�Ƕ�С�����Ƕȣ�ȡ����
	{
		dAlfa = 2 * PI + dAlfa;
	}

	double dBulge = 0.0;

	dBulge = tan((dAlfa) / 4.0);
	return dBulge;
}

void AddArc()
{
	ArxRleUiPrPoint prCenterPt(_T("Center point"), NULL);
	if(prCenterPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDist prRadius(_T("Radius"), NULL, ArxRleUiPrDist::kNoNegNoZero, prCenterPt.value());
	ArxRleUiPrAngle prStartAng(_T("Start angle"), NULL, ArxRleUiPrAngle::kAny, prCenterPt.value());
	ArxRleUiPrAngle prEndAng(_T("End angle"), NULL, ArxRleUiPrAngle::kAny, prCenterPt.value());

	if((prRadius.go() != ArxRleUiPrBase::kOk) ||
		(prStartAng.go() != ArxRleUiPrBase::kOk) ||
		(prEndAng.go() != ArxRleUiPrBase::kOk))
		return;

	AcDbArc* arc = new AcDbArc;
	arc->setDatabaseDefaults();
	arc->setCenter(prCenterPt.value());
	arc->setRadius(prRadius.value());
	arc->setStartAngle(prStartAng.value());
	arc->setEndAngle(prEndAng.value());
	ArxRleUtils::transformToWcs(arc, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(arc);
}

void add_Text(ArxRleString lpszText, CPt3d& oInsertPt, double fHeight)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;
		SAFEARRAY* psaPoint = NULL;
		psaPoint = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPoint != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.x);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.y);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.z);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPoint;

			IMSpace.AddText(lpszText,pt,fHeight);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPoint);
		}
		else
			acutPrintf(_T("\n---DWG�����Բʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddText(ArxRleString lpszText, CPt3d& oAlignmentPt, double fHeight, double fRotation, ArxAlignment eAlign)
{
	AcDbText* pText = new AcDbText;
	pText->setDatabaseDefaults();
	AcDbObjectId tsId = GetCurTextStyle();
	AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
	pText->setTextStyle(tsId);
	pText->setWidthFactor(ts->xScale());
	pText->setTextString(lpszText); //�ı�����
	pText->setHeight(fHeight); //�ı��߶�
	pText->setRotation(fRotation); //�ı���ת�Ƕ�
	//pText->setWidthFactor(GetCurTextStyle()->xScale());
	ts->close();

	switch(eAlign)
	{
	case ArxLeftTop:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxMiddleTop:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxRightTop:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxLeftMiddle:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxCenter:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxRightMiddle:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxLeftBottom:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	case ArxMiddleBottom:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	case ArxRightBottom:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	default:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	}
	pText->setPosition(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //�ı����������
	pText->setAlignmentPoint(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //�ı����������

	ArxRleUtils::transformToWcs(pText, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pText);
}

void AddText(AcDbTextStyleTableRecord* ts, ArxRleString lpszText, CPt3d& oAlignmentPt, double fHeight, double fRotation, ArxAlignment eAlign)
{
	AcDbText* pText = new AcDbText;
	pText->setDatabaseDefaults();
	if(ts != NULL) pText->setTextStyle(ts->objectId());
	pText->setTextString(lpszText); //�ı�����
	pText->setHeight(fHeight); //�ı��߶�
	pText->setRotation(fRotation); //�ı���ת�Ƕ�
	if(ts != NULL) pText->setWidthFactor(ts->xScale());

	switch(eAlign)
	{
	case ArxLeftTop:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxMiddleTop:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxRightTop:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextTop);
		break;
	case ArxLeftMiddle:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxCenter:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxRightMiddle:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextVertMid);
		break;
	case ArxLeftBottom:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	case ArxMiddleBottom:
		pText->setHorizontalMode(AcDb::kTextCenter);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	case ArxRightBottom:
		pText->setHorizontalMode(AcDb::kTextRight);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	default:
		pText->setHorizontalMode(AcDb::kTextLeft);
		pText->setVerticalMode(AcDb::kTextBase);
		break;
	}
	pText->setPosition(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //�ı����������
	pText->setAlignmentPoint(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //�ı����������

	ArxRleUtils::transformToWcs(pText, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pText);
}

void AddText()
{
	acutPrintf(_T("\nTesting make of AcDbText..."));

	ArxRleUiPrPoint prInsertPt(_T("Insertion point"), NULL);
	if(prInsertPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrString prText(_T("Text"), TRUE);
	if(prText.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbText* pText = new AcDbText;
	pText->setDatabaseDefaults();
	pText->setTextStyle(GetCurTextStyle());
	pText->setTextString(prText.value()); //�ı�����
	pText->setAlignmentPoint(AcGePoint3d(prInsertPt.value().x,prInsertPt.value().y,prInsertPt.value().z)); //�ı����������
	ArxRleUtils::transformToWcs(pText, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pText);
}

void add_MText(ArxRleString lpszText, CPt3d& oCenterPt, double fWidth)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;
		SAFEARRAY* psaPoint = NULL;
		psaPoint = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPoint != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPoint, &index, &oCenterPt.x);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oCenterPt.y);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oCenterPt.z);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPoint;
			IMSpace.AddMText(pt,fWidth,lpszText);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPoint);
		}
		else
			acutPrintf(_T("\n---DWG�����Բʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

void AddMText(ArxRleString lpszText, CPt3d& oInsertPt, double fWidth, double fHeight, double fRadiusotation, ArxAlignment eAlign)
{
	AcDbMText* pMText = new AcDbMText;
	pMText->setDatabaseDefaults();
	pMText->setTextStyle(GetCurTextStyle());
	pMText->setContents(lpszText); //�ı�����
	if(abs(fWidth) > 0)
		pMText->setWidth(fabs(fWidth)); //�ı���Χ���
	else
		pMText->setWidth(fabs(lpszText.GetLength()*1.0)); //�ı���Χ���
	pMText->setLocation(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z)); //�ı������
	pMText->setTextHeight(fHeight); //�ı��߶�
	pMText->setRotation(fRadiusotation); //�ı���ת�Ƕ�
	pMText->setAttachment((AcDbMText::AttachmentPoint)eAlign);

	ArxRleUtils::transformToWcs(pMText, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pMText);
}

void AddMText()
{
	acutPrintf(_T("\nTesting make of AcDbMText..."));

	ArxRleUiPrPoint prInsertPt(_T("Insertion point"), NULL);
	if(prInsertPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrCorner prCorner(_T("Other corner"), NULL, prInsertPt.value());
	ArxRleUiPrString prText(_T("Text"), TRUE);

	if((prCorner.go() != ArxRleUiPrBase::kOk) ||
		(prText.go() != ArxRleUiPrBase::kOk))
		return;

	AcDbMText* mtext = new AcDbMText;
	mtext->setLocation(prInsertPt.value());
	mtext->setWidth(fabs(prInsertPt.value().x - prCorner.value().x));
	mtext->setContents(prText.value());
	ArxRleUtils::transformToWcs(mtext, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(mtext);
}

void AddAttributeDefinition(ArxRleString lpszDefinition, ArxRleString lpszPrompt, ArxRleString lpszTag, CPt3d& oInsertPt, double fHeight, double fRadiusotation)
{
	AcDbAttributeDefinition* attdef = new AcDbAttributeDefinition;
	attdef->setDatabaseDefaults();
	attdef->setPosition(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z));
	attdef->setHeight(fHeight);
	attdef->setRotation(fRadiusotation);
	attdef->setTextString(lpszDefinition);
	attdef->setPrompt(lpszPrompt);
	attdef->setTag(lpszTag);
	ArxRleUtils::transformToWcs(attdef, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(attdef);
}

void AddBlock(CPt3d& oInsertPt, ArxRleString lpszBlkName, double fXscale, double fYscale, double fRadiusotation, double fZscale)
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND sabPt;
		sabPt.lLbound = 0L;
		sabPt.cElements = 3;
		SAFEARRAY* psaPoint = NULL;
		psaPoint = SafeArrayCreate(VT_R8, 1, &sabPt);

		if(psaPoint != NULL)
		{
			long index = 0;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.x);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.y);
			index++;
			SafeArrayPutElement(psaPoint, &index, &oInsertPt.z);

			VARIANT pt;
			VariantInit(&pt);
			V_VT(&pt) = VT_ARRAY | VT_R8;
			V_ARRAY(&pt) = psaPoint;
			IMSpace.InsertBlock(pt, lpszBlkName, fXscale, fYscale, fZscale, fRadiusotation, vtMissing);

			VariantClear(&pt);
			//SafeArrayDestroy(psaPoint);
		}
		else
			acutPrintf(_T("\n---DWG�����Բʧ�ܣ�---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

Acad::ErrorStatus SetBlockAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef)
{
	// open the block record and find all the ATTDEFS
	AcDbBlockTableRecord* blkTblRec = (AcDbBlockTableRecord*)GetRecordPtr(blockRecordId);
	if(blkTblRec == NULL)
		return(Acad::eInvalidInput);

	AcDbBlockTableRecordIterator* blkIter;
	if(blkTblRec->newIterator(blkIter) != Acad::eOk)
		return(Acad::eInvalidInput);

	AcDbEntity* ent;
	AcDbAttributeDefinition* attdef;
	AcGeMatrix3d xformMat = blkRef->blockTransform();

	for(; !blkIter->done(); blkIter->step()) {
		if(blkIter->getEntity(ent, AcDb::kForRead) == Acad::eOk) {
			// deal only with non-constant ATTDEFS
			if(((attdef = AcDbAttributeDefinition::cast(ent)) != NULL) &&
				(attdef->isConstant() == Adesk::kFalse)) {
					// create a new ATTRIBUTE entity
					AcDbAttribute* attrib = new AcDbAttribute;

					// set ENTITY common fields
					attrib->setPropertiesFrom(attdef);

					// set ATTDEF common fields
					attrib->setInvisible(attdef->isInvisible());
					attrib->setFieldLength(attdef->fieldLength());

					// set TEXT common fields
					attrib->setThickness(attdef->thickness());
					attrib->setOblique(attdef->oblique());
					attrib->setRotation(attdef->rotation());
					attrib->setHeight(attdef->height());
					attrib->setTextStyle(attdef->textStyle());
					attrib->mirrorInX(attdef->isMirroredInX());
					attrib->mirrorInY(attdef->isMirroredInY());
					attrib->setHorizontalMode(attdef->horizontalMode());
					attrib->setVerticalMode(attdef->verticalMode());
					attrib->setPosition(attdef->position());
					attrib->setAlignmentPoint(attdef->alignmentPoint());

					// put in default value for test
					acutPrintf(_T("\nUsing default ATTRIBUTE value..."));
					const TCHAR* tagStr = attdef->tagConst();
					attrib->setTag(tagStr);
					const TCHAR* valStr = attdef->textStringConst();
					attrib->setTextString(valStr);

					// add to this block reference
					if(blkRef->appendAttribute(attrib) == Acad::eOk) {
						attrib->transformBy(xformMat);
						attrib->setWidthFactor(attdef->widthFactor());    // has to be set after transform
						attrib->close();
					}
					else {
						acutPrintf(_T("\nERROR: Could not append ATTRIBUTE."));
						delete attrib;
					}
			}
			ent->close();
		}
	}

	delete blkIter;
	blkTblRec->close();
	return(Acad::eOk);
}

void AddBlock(ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt, double fRadiusotation)
{
	AcDbDatabase* db = ARXRLEDB;  //��ǰͼ�����ݿ�
	AcDbObjectId blkId;

	if(acdbSNValid(lpszBlkName, TRUE) != RTNORM ||
		ArxRleUtils::symbolExists(AcDbBlockTableRecord::desc(), lpszBlkName, db) == false ||
		ArxRleUtils::nameToSymbolId(AcDbBlockTableRecord::desc(), lpszBlkName, blkId, db) != Acad::eOk)
		return;

	AcDbBlockReference* blkRef = new AcDbBlockReference;
	if(blkRef->setBlockTableRecord(blkId) != Acad::eOk)
	{
		delete blkRef;
		return;
	}

	blkRef->setPosition(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z));
	blkRef->setRotation(fRadiusotation);
	blkRef->setScaleFactors(AcGeScale3d(oScalePt.x,oScalePt.y,oScalePt.z));

	if(ArxRleUtils::addToCurrentSpace(blkRef) == Acad::eOk)
	{
		SetBlockAttributes(blkId, blkRef);
		ArxRleUtils::transformToWcs(blkRef, db);
		blkRef->close();
	}
	else
		delete blkRef;
}

void AddBlock(ArxRleString lpszDwgFilePath, ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt, double fRadiusotation)
{
	if(!FileExist(lpszDwgFilePath.c_ptr()))
		return;

	CString blkName;//�ⲿ�ļ���Ϊ�����Ŀ���
	int len = lpszDwgFilePath.GetLength();
	int index1 = lpszDwgFilePath.ReverseFind('\\');
	int index2 = lpszDwgFilePath.ReverseFind('.');
	blkName = lpszDwgFilePath.Mid(index1+1,index2-1).t_str();

	if(!acdbSNValid(blkName, false))
		return;
	AcDbDatabase* db = ARXRLEDB;
	AcDbDatabase* srdb = new AcDbDatabase(false,true);
	srdb->readDwgFile(lpszDwgFilePath);
	ASSERT(srdb != db);

	AcDbObjectId blkId;
	db->insert(blkId, blkName, srdb, false);

	if(acdbSNValid(lpszBlkName, TRUE) != RTNORM ||
		ArxRleUtils::symbolExists(AcDbBlockTableRecord::desc(), lpszBlkName, db) == false ||
		ArxRleUtils::nameToSymbolId(AcDbBlockTableRecord::desc(), lpszBlkName, blkId, db) != Acad::eOk)
		return;

	AcDbBlockReference* blkRef = new AcDbBlockReference;
	if(blkRef->setBlockTableRecord(blkId) != Acad::eOk)
	{
		delete blkRef;
		return;
	}

	blkRef->setPosition(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z));
	blkRef->setRotation(fRadiusotation);
	blkRef->setScaleFactors(AcGeScale3d(oScalePt.x,oScalePt.y,oScalePt.z));

	if(ArxRleUtils::addToCurrentSpace(blkRef) == Acad::eOk)
	{
		SetBlockAttributes(blkId, blkRef);
		ArxRleUtils::transformToWcs(blkRef, db);
		blkRef->close();
	}
	else
		delete blkRef;
}

void AddMBlock(ArxRleString lpszBlkName, CPt3d& oInsertPt, CPt3d& oScalePt, double fRadiusotation, int nRows, int nColumns, double fRadiusowSpace, double fColSpace)
{
	AcDbDatabase* db = ARXRLEDB;  //��ǰͼ�����ݿ�
	AcDbObjectId blkId;

	if(acdbSNValid(lpszBlkName, TRUE) != RTNORM ||
		ArxRleUtils::symbolExists(AcDbBlockTableRecord::desc(), lpszBlkName, db) == false ||
		ArxRleUtils::nameToSymbolId(AcDbBlockTableRecord::desc(), lpszBlkName, blkId, db) != Acad::eOk)
		return;

	if(nRows > 256 || nColumns > 256)
		return;

	AcDbMInsertBlock* blkRef = new AcDbMInsertBlock;

	// set this block to point at the correct block ref
	if(blkRef->setBlockTableRecord(blkId) != Acad::eOk) {
		delete blkRef;
		return;
	}

	blkRef->setPosition(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z));
	blkRef->setRotation(fRadiusotation);
	blkRef->setScaleFactors(AcGeScale3d(oScalePt.x,oScalePt.y,oScalePt.z));

	blkRef->setColumns(nColumns);
	blkRef->setRows(nRows);
	blkRef->setColumnSpacing(fColSpace);
	blkRef->setRowSpacing(fRadiusowSpace);

	if(ArxRleUtils::addToCurrentSpace(blkRef) == Acad::eOk)
	{
		SetBlockAttributes(blkId, blkRef);
		ArxRleUtils::transformToWcs(blkRef, db);
		blkRef->close();
	}
	else
		delete blkRef;
}

void cmd_offset(AcDbObjectId id, CPt3d pt, double oft)
{
	//��CAD����ƫ��ʾ��
	ads_name e1;//��Ҫƫ�Ƶ�ʵ��
	ads_point p1;//ƫ�Ƶ���һ��
	p1[X] = pt.x;
	p1[Y] = pt.y;
	p1[Z] = pt.z;
	if(ArxRleUtils::objIdToEname(id, e1) == Acad::eOk)
		acedCommandS(RTSTR,_T("offset"),RTREAL,oft,RTENAME,e1,RTPOINT,p1,RTSTR,_T(""),RTNONE);
}

void cmd_fillet(AcDbObjectId id1, AcDbObjectId id2, CPt3d pt1, CPt3d pt2, double r)
{
	//ʹ��CAD����ǣ�
	ads_name e1,e2;//��Ҫƫ�Ƶ�ʵ��
	ads_point p1,p2;//ƫ�Ƶ���һ��
	p1[X] = pt1.x;
	p1[Y] = pt1.y;
	p1[Z] = pt1.z;
	p2[X] = pt2.x;
	p2[Y] = pt2.y;
	p2[Z] = pt2.z;
	if(ArxRleUtils::objIdToEname(id1, e1) == Acad::eOk && ArxRleUtils::objIdToEname(id2, e2) == Acad::eOk)
	{
		acedCommandS(RTSTR,_T("fillet"),RTSTR,_T("R"),RTREAL,r,RTNONE);
		acedCommandS(RTSTR,_T("fillet"),RTLB,RTENAME,e1,RTPOINT,p1,RTLE,RTLB,RTENAME,e2,RTPOINT,p2,RTLE,RTNONE);
	}
}

void To2dPolyline(AcDbObjectId objId, int flag)
{
	AcDbEntity *pEnt = NULL;
	double elev = 0.0;
	acdbOpenObject(pEnt, objId, AcDb::kForWrite);
	int i = 0;
	if (pEnt->isKindOf(AcDb3dPolyline::desc()))
	{
		AcDb2dPolyline *p2dPline = new AcDb2dPolyline();
		AcDb3dPolyline *p3dPline = AcDb3dPolyline::cast(pEnt);
		AcDbObjectIterator *pItr = p3dPline->vertexIterator();

		for (pItr->start(); !pItr->done(); pItr->step())
		{
			AcDb3dPolylineVertex *p3dVertex = NULL;
			AcDbObjectId vId = pItr->objectId();
			acdbOpenObject(p3dVertex, vId, AcDb::kForRead);
			AcDb::Vertex3dType verType = p3dVertex->vertexType();
			if (verType != AcDb::k3dControlVertex)
			{
				i++;
				AcDb2dVertex *p2dVertex = new AcDb2dVertex(p3dVertex->position());
				p2dVertex->setXData(p3dVertex->xData());
				p2dPline->appendVertex(p2dVertex);
				p2dVertex->close();
			}
			if (flag == 1)
			{
				elev += p3dVertex->position().z;
			}

			p3dVertex->close();
		}
		delete pItr;
		pItr = 0;
		double eleva = elev / i;

		p2dPline->setElevation(eleva);
		p2dPline->setPropertiesFrom(p3dPline);
		if (p3dPline->isClosed())
		{
			p2dPline->makeClosed();
		}
		p2dPline->setXData(p3dPline->xData());
		ArxRleUtils::addToCurrentSpaceAndClose(p2dPline);
		p3dPline->erase();
	}

	pEnt->close();
}

void To2dLine(AcDbObjectId objId)
{
	AcDbEntity *pEnt = NULL;
	acdbOpenObject(pEnt, objId, AcDb::kForWrite);
	if (pEnt->isKindOf(AcDbLine::desc()))
	{
		AcDbLine *pLine = AcDbLine::cast(pEnt);
		AcGePoint3d pt = pLine->startPoint();
		pt.z = 0;
		pLine->setStartPoint(pt); 
		pt = pLine->endPoint();
		pt.z = 0;
		pLine->setEndPoint(pt); 
	}

	pEnt->close();
}

void To2dArc(AcDbObjectId objId)
{
	AcDbEntity *pEnt = NULL;
	acdbOpenObject(pEnt, objId, AcDb::kForWrite);
	int i = 0;
	if (pEnt->isKindOf(AcDbArc::desc()))
	{
		AcDbArc *pArc = AcDbArc::cast(pEnt);
		AcGePoint3d pt = pArc->center();
		pt.z = 0;
		pArc->setCenter(pt); 
	}

	pEnt->close();
}