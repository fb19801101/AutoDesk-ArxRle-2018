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

/*3DDWFPREC     控制三维DWF发布的精度。 
3DCONVERSIONMODE     用于将材质和光源定义转换为当前产品版本。 
3DSELECTIONMODE     控制使用三维视觉样式时视觉上重叠的对象的选择优先级。
ACADLSPASDOC     控制是将acad.lsp文件加载到每个图形中，还是仅加载到任务中打开的第一个图形中。
ACADPREFIX     存储由ACAD环境变量指定的目录路径。
ACADVER     存储AutoCAD的版本号。
ACISOUTVER     控制使用ACISOUT命令创建的SAT文件的ACIS版本。
ADCSTATE     指示设计中心窗口处于打开还是关闭状态。
AFLAGS     设置属性选项。
ANGBASE     将相对于当前UCS的基准角设置为 0。
ANGDIR     设置正角度的方向。从相对于当前UCS方向的 0 角度测量角度值。 
ANNOALLVISIBLE     隐藏或显示不支持当前annotation scale的annotative对象。
ANNOAUTOSCALE     注释比例更改时更新annotative对象可支持annotation scale。
ANNOTATIVEDWG     指定图形插入到其他图形中时，是否相当于annotative块。
APBOX     打开或关闭自动捕捉靶框的显示。
APERTURE     以像素为单位设置对象捕捉靶框的显示尺寸。 
APSTATE     块编辑器中的“块编写选项板”窗口处于打开还是关闭状态。
AREA     存储由AREA命令计算出的上一个面积。 
ATTDIA     控制INSERT命令是否使用对话框用于属性值的输入。 
ATTIPE     控制用于创建多行属性的在位编辑器的显示。
ATTMODE     控制属性的显示。
ATTMULTI     控制是否可创建多行属性。
ATTREQ     在插入块过程中控制INSERT是否使用默认属性设置。
AUDITCTL     控制AUDIT命令是否创建核查报告 (ADT) 文件。
AUNITS     设置角度单位。
AUPREC     设置所有只读角度单位和所有可编辑角度单位的小数位数。
AUTODWFPUBLISH     控制自动发布功能的开关状态。
AUTOSNAP     控制自动捕捉标记、工具栏提示和磁吸的显示。也可以打开极轴追踪和对象捕捉追踪，并控制极轴追踪、对象捕捉追踪和正交模式工具栏提示的显示。
BACKGROUNDPLOT     控制是否打开后台打印和后台发布。默认情况下，关闭后台打印，打开后台发布。
BACKZ     以绘图单位存储当前视口后向剪裁平面到目标平面的偏移值。
BACTIONCOLOR     在块编辑器中设置动作的文字颜色。
BDEPENDENCYHIGHLIGHT     控制在块编辑器中选定参数、动作或夹点时是否依赖亮显依赖对象。 
BGRIPOBJCOLOR     在块编辑器中设置夹点的颜色。
BGRIPOBJSIZE     在块编辑器中设置相对于屏幕显示的自定义夹点的显示尺寸。
BINDTYPE     控制绑定或在位编辑外部参照时外部参照名称的处理方式。
BLIPMODE     控制点标记是否可见。该系统变量的名称与命令相同。
BLOCKEDITLOCK     禁止打开块编辑器以及编辑动态块定义。
BLOCKEDITOR     反映块编辑器是否已打开。 
BPARAMETERCOLOR     设置块编辑器中的参数的颜色。
BPARAMETERFONT     设置块编辑器中的参数和动作所用的字体。 
BPARAMETERSIZE     在块编辑器中设置相对于屏幕显示的参数文本和功能的显示尺寸。
BTMARKDISPLAY     控制是否显示动态块参照的数值集标记。 
BVMODE     控制当前可见性状态下可见的对象在块编辑器中的显示方式。 
CALCINPUT     控制是否计算文本中以及窗口和对话框的数字输入框中的数学表达式和全局常量。
CAMERADISPLAY     打开或关闭相机对象的显示。
CAMERAHEIGHT     为新相机对象指定默认高度。 
CANNOSCALE     设置当前空间中的当前annotation scale的名称
CANNOSCALEVALUE     返回当前annotation scale的值
CDATE     以小数格式存储当前的日期和时间。
CECOLOR     设置新对象的颜色。
CELTSCALE     设置当前对象的线型比例因子。
CELTYPE     设置新对象的线型。
CELWEIGHT     设置新对象的线宽。
CENTERMT     控制夹点拉伸多行水平居中的文字的方式。
CHAMFERA     当CHAMMODE设置为 0 时设置第一个倒角距离。
CHAMFERB     当CHAMMODE设置为 0 时设置第二个倒角距离。
CHAMFERC     当CHAMMODE设置为 1 时设置倒角长度。
CHAMFERD     当CHAMMODE设置为 1 时设置倒角角度。
CHAMMODE     设置CHAMFER的输入方法。
CIRCLERAD     设置默认的圆半径。
CLAYER     设置当前图层。
CLEANSCREENSTATE     全屏显示状态的开关状态。
CLISTATE     命令窗口处于打开还是关闭状态。
CMATERIAL     设置新对象的材质。
CMDACTIVE     指示激活的是普通命令、透明命令、脚本还是对话框。
CMDDIA     控制执行QLEADER命令时在位文字编辑器的显示。 
CMDECHO     控制在AutoLISP命令函数运行时是否回显提示和输入。
CMDINPUTHISTORYMAX     设置存储在命令提示中的以前输入值的最大数量。
CMDNAMES     显示活动命令和透明命令的名称。 
CMLEADERSTYLE     当前使用的多重引线样式的名称
CMLJUST     指定多线对正方式。
CMLSCALE     指定多线比例。
CMLSTYLE     当前使用的多线样式的名称。
COMPASS     控制三维指南针在当前视口中的开关状态。
COORDS     控制状态行上坐标的格式和更新频率。
COPYMODE     控制是否自动重复COPY命令。
CPLOTSTYLE     控制新对象的当前打印样式。
CPROFILE     显示当前配置的名称。
CROSSINGAREACOLOR     控制交叉选择时选择区域的颜色。 
CSHADOW     设置三维对象的阴影显示特性。
CTAB     返回图形中的当前（模型或布局）选项卡名称。
CTABLESTYLE     当前使用的表格样式的名称
CURSORSIZE     按屏幕大小的百分比确定十字光标的大小。
CVPORT     显示当前视口的标识码。
DIMALTU     设置所有标注子样式（角度标注除外）的换算单位的单位格式。
DIMALTZ     控制对换算单位标注值的消零处理。DIMALTZ的值为 0 到 3 时只影响英尺-英寸标注。
DIMANNO     指示当前标注样式是否是annotative。
DIMAPOST     指定用于所有标注类型（角度标注除外）的换算标注测量值的文字前缀或后缀（或两者都指定）。
DIMARCSYM     控制弧长标注中圆弧符号的显示。 
DIMASO     旧式的。保留在产品中以保持脚本的完整性。
DIMASSOC     控制标注对象的关联性以及是否分解标注。
DIMASZ     控制尺寸线和引线箭头的大小。并控制基线的大小。
DIMATFIT     尺寸界线内的空间不足以同时放下标注文字和箭头时，此系统变量将确定这两者的排列方式。
DIMAUNIT     设置角度标注的单位格式。
DIMAZIN     对角度标注进行消零处理。
DIMBLK     设置尺寸线末端显示的箭头块。 
DIMBLK1     设置尺寸线第一个端点的箭头。
DIMBLK2     设置尺寸线第二个端点的箭头。
DIMCEN     控制由DIMCENTER、DIMDIAMETER和DIMRADIUS命令绘制的圆或圆弧的圆心标记和中心线。
DIMCLRD     为尺寸线、箭头和标注引线指定颜色。同时控制用LEADER命令创建的引线的颜色。 
DIMCLRE     为尺寸界线指定颜色。
DIMCLRT     为标注文字指定颜色。 
DIMDEC     设置标注主单位中显示的小数位数。
DIMDLE     当使用小斜线代替箭头进行标注时，设置尺寸线超出尺寸界线的距离。
DIMDLI     控制基线标注中尺寸线的间距。
DIMDSEP     指定创建单位格式为十进制的标注时要使用的单字符小数分隔符。
DIMEXE     指定尺寸线超出尺寸界线的距离。
DIMEXO     指定尺寸界线偏离原点的距离。对于固定长度的尺寸界线，此值将决定最小偏移量。
DIMFIT     已废弃，请改用DIMATFIT和DIMTMOVE。
DIMfRadiusAC     设置分数格式（当DIMLUNIT设置为 4 [建筑] 或 5 [分数] 时）。
DIMFXL     设置尺寸界线的总长度，起始于尺寸线，直到标注原点。以图形单位设置长度。
DIMFXLON     控制是否将尺寸界线设置为固定长度。DIMFXLON打开时，尺寸界线设置为DIMFXL指定的长度。
DIMGAP     尺寸线分成两段从而将标注文字放置在两段之间时，设置标注文字周围的距离。同时设置用LEADER命令创建的注释和基线之间的间距。如果输入负 值，DIMGAP将在标注文字周围放置一个方框。
DIMJOGANG     确定折弯半径标注中，尺寸线的横向线段的角度。
DIMJUST     控制标注文字的水平位置。
DIMLDRBLK     指定引线箭头的类型。
DIMLFAC     设置线性标注测量值的比例因子。
DIMLIM     生成标注界限作为默认文字。将DIMLIM设置为“开”将会关闭DIMTOL。
DIMLTEX1     设置第一条尺寸界线的线型。值为随层、随块或线型名称。
DIMLTEX2     设置第二条尺寸界线的线型。值为随层、随块或线型名称。
DIMLTYPE     设置尺寸线的线型。值为随层、随块或线型名称。
DIMLUNIT     设置所有标注类型（角度标注除外）的单位。
DIMLWD     为尺寸线指定线宽。其值是标准线宽。
DIMLWE     为尺寸界线指定线宽。其值是标准线宽。
DIMPOST     指定标注测量值的文字前缀或后缀（或两者都指定）。
DIMRND     将所有标注距离舍入到指定值。
DIMSAH     控制尺寸线箭头块的显示。
DIMSCALE     设置应用于标注变量（可指定大小、距离或偏移量）的全局比例因子。
DIMSD1     控制是否显示第一条尺寸线和箭头。
DIMSD2     控制是否显示第二条尺寸线和箭头。
DIMSE1     控制是否禁止显示第一条尺寸界线。
DIMSE2     控制是否禁止显示第二条尺寸界线。
DIMSHO     旧式的。除用于保持脚本的完整性外没有任何影响。
DIMSOXD     如果尺寸界线内没有足够的空间，则隐藏箭头。
DIMSTYLE     当前使用的标注样式的名称。 
DIMTAD     控制文字相对于尺寸线的垂直位置。
DIMTDEC     设置标注主单位的公差值中要显示的小数位数。
DIMTFAC     与通过DIMTXT系统变量设置一样，指定分数和公差值的文字高度相对于标注文字高度的比例因子。
DIMTFILL     控制标注文字的背景。
DIMTFILLCLR     设置标注中文字背景的颜色。
DIMTIH     控制所有标注类型（坐标标注除外）的标注文字在尺寸界线内的位置。
DIMTIX     在尺寸界线之间绘制文字。
DIMTM     设置标注文字的最小（下）公差极限（当DIMTOL或DIMLIM设置为开时）。
DIMTMOVE     设置标注文字的移动规则。
DIMTOFL     控制是否在尺寸界线之间绘制尺寸线（即使标注文字被放置在尺寸界线之外）。
DIMTOH     控制标注文字在尺寸界线外的位置。
DIMTOL     将公差附在标注文字之后。将DIMTOL设置为开将会关闭DIMLIM。
DIMTOLJ     设置公差值相对于标注文字的垂直对正方式。
DIMTP     设置标注文字的最大（上）公差极限（当DIMTOL或DIMLIM设置为开时）。
DIMTSZ     指定线性标注、半径标注以及直径标注中用于替代箭头的小斜线的尺寸。
DIMTVP     控制标注文字在尺寸线上方或下方的垂直位置。
DIMTXSTY     指定标注的文字样式。
DIMTXT     指定标注文字的高度（除非当前文字样式具有固定的高度）。
DIMTZIN     控制对公差值的消零处理。
DIMUNIT     旧式的。保留在产品中以保持脚本的完整性。DIMUNIT将替换为DIMLUNIT和DIMfRadiusAC。
DIMUPT     控制用户定位文字选项。
DIMZIN     控制对主单位值的消零处理。
DISPSILH     控制三维实体对象轮廓边在二维线框或三维线框视觉样式中的显示。 
DISTANCE     存储DIST命令计算出的距离。
DONUTID     设置圆环的默认内径。
DONUTOD     设置圆环的默认外径。此值不能为零。
DRAGMODE     控制拖动对象的显示。 
DRAGP1     设置重生成拖动模式下的输入采样率。
DRAGP2     设置快速拖动模式下的输入采样率。
DRAGVS     创建三维实体图元以及拉伸实体和拉伸曲面时设置视觉样式。
DRAWORDERCTL     控制重叠对象的显示次序。受继承影响的命令有BREAK、FILLET、HATCH、HATCHEDIT、EXPLODE、TRIM、JOIN、 PEDIT和OFFSET。
DRSTATE     确定“图形修复管理器”窗口处于打开还是关闭状态。
DTEXTED     指定为编辑单行文字而显示的用户界面。
DWFfRadiusAME     确定DWF参考底图边框是否可见。
DWFOSNAP     确定是否为附着在图形中的DWF参考底图中的几何图形启用对象捕捉。
DWGCHECK     打开图形时检查图形中是否存在潜在问题。
DWGCODEPAGE     与SYSCODEPAGE系统变量存储相同的值（由于兼容性原因）。
DWGNAME     存储当前图形的名称。
DWGPREFIX     存储图形的驱动器和文件夹前缀。
DWGTITLED     指示当前图形是否已命名。
DXEVAL     控制数据提取处理表何时与数据源比较，如果数据不是当前数据，则显示更新通知
DYNDIGRIP     控制在夹点拉伸编辑期间显示哪些动态标注。必须将DYNDIVIS系统变量设置为 2，这将显示所有的动态标注。
DYNDIVIS     控制在夹点拉伸编辑期间显示的动态标注数量。DYNDIGRIP控制在夹点拉伸编辑期间显示哪些动态标注。 
DYNMODE     打开或关闭动态输入功能。全部功能都打开时，上下文将控制所显示的内容。
DYNPICOORDS     控制指针输入是使用相对坐标格式，还是使用绝对坐标格式。 
DYNPIFORMAT     控制指针输入是使用极轴坐标格式，还是使用笛卡尔坐标格式。此设置仅适用于第二点或下一点。
DYNPIVIS     控制何时显示指针输入。
DYNPROMPT     控制“动态输入”工具栏提示中提示的显示。
DYNTOOLTIPS     控制受工具栏提示外观设置影响的工具栏提示。
EDGEMODE     控制TRIM和EXTEND命令确定边界的边和剪切边的方式。
ELEVATION     存储新对象相对于当前UCS的当前标高。
ENTERPRISEMENU     显示企业CUI（如果已定义）的文件名，包括文件名的路径。
ERRNO
AutoLISP函数调用导致AutoCAD检测到错误时，显示相应的错误代码的编号。
ERSTATE     确定“外部参照”选项板处于打开还是关闭状态。
EXPERT     控制是否显示某些特定提示。
EXPLMODE     控制EXPLODE命令是否支持按非统一比例缩放 (NUS) 的块。
EXTMAX     存储图形范围右上角点的值。
EXTMIN     存储图形范围左下角点的值。
EXTNAMES     为存储在定义表中的命名对象名称（例如线型和图层）设置参数。
FACETRATIO     控制圆柱和圆锥实体镶嵌面的宽高比。设置为 1 将增加网格密度以改善渲染模型和着色模型的质量。
FACETRES     调整着色对象和删除了隐藏线的对象的平滑度。有效值为 0.01 到 10.0。
FIELDDISPLAY     控制显示的字段是否带有灰色背景。不打印背景。
FIELDEVAL     控制字段的更新方式。
FILEDIA     禁止显示文件导航对话框。
FILLETRAD     存储当前的圆角半径。
FILLMODE     指定是否填充图案填充和填充、二维实体以及宽多段线。
FONTALT     指定找不到指定的字体文件时要使用的替换字体。 
FONTMAP     指定要使用的字体映射文件。
fRadiusONTZ     按图形单位存储当前视口中的前向剪裁平面距离目标平面的偏移量。
FULLOPEN     指示当前图形是否局部打开。
FULLPLOTPATH     控制是否将图形文件的完整路径发送到后台打印。
GRIDDISPLAY     控制栅格的显示行为和显示界限。
GRIDMAJOR     控制主栅格线与次栅格线比较的频率。有效值范围为从 1 到 100。
GRIDMODE     指定栅格的开关状态。
GRIDUNIT     指定当前视口的栅格间距（X和Y方向）。 
GRIPBLOCK     选定后，控制块中嵌套对象上的夹点的显示。
GRIPCOLOR     控制未选中夹点的颜色。有效取值范围为 1 到 255。
GRIPDYNCOLOR     控制动态块的自定义夹点的颜色。有效取值范围为 1 到 255。
GRIPHOT     控制选定夹点的颜色。有效取值范围为 1 到 255。
GRIPHOVER     控制光标暂停在未选定夹点上时该夹点的填充颜色。有效取值范围为 1 到 255。
GRIPOBJLIMIT     选择集包括的对象多于指定数量时，禁止显示夹点。
GRIPS     控制选择集夹点在“拉伸”、“移动”、“旋转”、“比例缩放”和“镜像夹点”模式中的使用。
GRIPSIZE     以像素为单位设置夹点框的大小。有效取值范围为 1 到 255。
GRIPTIPS     控制当光标悬停在支持夹点提示的动态块和自定义对象的夹点上时夹点提示的显示。 
GTAUTO     控制在设置为三维视觉样式的视口中启动命令之前选择对象时，夹点工具是否自动显示。
GTDEFAULT     控制在三维视图中分别启动MOVE和ROTATE命令时，3DMOVE和 3DROTATE命令是否自动启动。
GTLOCATION     运行 3DMOVE或 3DROTATE命令之前选择对象时，控制夹点工具的初始位置。
HALOGAP     指定一个对象被另一个对象遮挡处要显示的间距。按照一英寸的百分比指定该值，并且它不受缩放级别的影响。
HANDLES     报告应用程序是否可以访问对象句柄。
HIDEPRECISION     控制消隐和着色的精度。
HIDETEXT     指定执行HIDE命令时是否处理由TEXT、DTEXT或MTEXT命令创建的文字对象。
HIGHLIGHT     控制对象的亮显；不影响使用夹点选定的对象。
HPANG     指定填充图案的角度。
HPASSOC     控制填充图案和渐变填充是否关联。
HPBOUND     控制由BHATCH和BOUNDARY命令创建的对象类型。
HPDOUBLE     指定用户定义图案的双向填充图案。双向将指定与原始直线成 90 度角绘制的第二组直线。 
HPDRAWORDER     控制图案填充和填充的绘图次序。存储“图案填充和填充”对话框中的“绘图次序”设置。
HPGAPTOL     设置图案填充边界时可以忽略的最大间隙，默认值为 0。
HPMAXLINES     控制将生成的填充线的最大数目。可在100到10,000,000之间对值进行设置。
HPINHERIT     控制在HATCH和HATCHEDIT命令中使用“继承特性”时结果图案填充的图案填充原点。
HPNAME     设置默认填充图案，输入句点 (.)将HPNAME重置为默认值。 
HPOBJWARNING     设置可以选择的图案填充边界对象数量（超过此数量将显示警告信息）。
HPORIGIN     相对于当前用户坐标系为新的图案填充对象设置图案填充原点。
HPORIGINMODE     控制HATCH确定默认图案填充原点的方式。
HPSCALE     指定填充图案的比例因子，其值必须大于零。
HPSEPARATE     控制在几个闭合边界上进行操作时，HATCH是创建单个图案填充对象，还是分别创建各个图案填充对象。
HPSPACE     指定用户定义的简单图案的填充图案线间距，其值必须大于零。
HYPERLINKBASE     指定图形中用于所有相对超链接的路径。
IMAGEHLT     控制是亮显整个光栅图像还是仅亮显光栅图像边框。
IMPLIEDFACE     控制隐含面的检测。
INDEXCTL     控制是否创建图层和空间索引并将其保存到图形文件中。
INETLOCATION     存储BROWSER命令和“浏览Web”对话框所使用的Internet网址。
INPUTHISTORYMODE     控制用户输入历史记录的显示内容和位置。 
INSBASE     存储BASE命令设置的插入基点，用当前空间的UCS坐标表示。
INSNAME     为INSERT命令设置默认块名。
INSUNITS     指定插入或附着到图形中的块、图像或外部参照进行自动缩放所用的图形单位值。 
INSUNITSDEFSOURCE     当INSUNITS设置为 0 时，设置源内容单位值。
INSUNITSDEFTARGET     当INSUNITS设置为 0 时，设置目标图形单位值。
INTELLIGENTUPDATE     控制图形的刷新率。默认值为 20 帧每秒。
INTERFERECOLOR     设置干涉对象的颜色。
INTERFEREOBJVS     设置干涉对象的视觉样式。
INTERFEREVPVS     指定检查干涉时视口的视觉样式。
INTERSECTIONCOLOR     控制视觉样式设置为“二维线框”时三维曲面交线处的多段线的颜色。 
INTERSECTIONDISPLAY     控制视觉样式设置为“二维线框”时三维曲面交线处的多段线的显示。 
ISAVEBAK     是否创建备份文件 (BAK)。
ISAVEPERCENT     确定图形文件中所允许的增量保存耗损空间总量，增量保存只更新保存的图形文件中已更改的部分，从而减少保存图形文件所需的时间。如果 ISAVEPERCENT设置为 0，则每一次都进行完全保存。
ISOLINES     指定对象上每个面的轮廓线数目。有效整数值为 0 到 2047。
LASTANGLE     存储相对于当前空间的当前UCS的XY平面输入的上一圆弧的端点角度。
LASTPOINT     存储上一次输入的点。
LASTPROMPT     存储回显到命令行的上一个字符串。
LATITUDE     以十进制格式指定图形模型的纬度。 
LAYEREVAL     控制何时计算图层管理器中的“未协调新图层”过滤器列表中的新图层。 
LAYERFILTERALERT     是否删除图层过滤器以提高性能。 
LAYERNOTIFY     指定何时显示尚未协调的新图层的警告。
LAYLOCKFADECTL     控制锁定图层上的对象的褪色
LAYOUTREGENCTL     指定“模型”选项卡和布局选项卡中的显示列表的更新方式以提高性能。
LEGACYCTRLPICK     指定用于循环选择的键和CTRL+单击的操作。 
LENSLENGTH     存储透视视图中使用的焦距（以毫米为单位）。
LIGHTGLYPHDISPLAY     控制是否显示光线轮廓。此系统变量设置为“关”时，不显示代表图形中的光源的轮廓。 
LIGHTINGUNITS     控制是使用常规光源还是使用光度控制光源，并指示当前的光学单位
LIGHTLISTSTATE     指示是否已打开“模型中的光源”窗口。 
LIGHTSINBLOCKS     控制渲染时是否使用块中包含的光源
LIMCHECK     控制是否可以在栅格界限之外创建对象。
LIMMAX     存储当前空间的右上方栅格界限。
LIMMIN     存储当前空间的左下方栅格界限。
LINEARBRIGHTNESS     控制标准光源流程中图形的全局亮度级别。
LINEARCONTRAST     控制标准光源流程中图形的全局对比度级别。
LOCALE     显示用于指示当前区域的代码。
LOCALROOTPREFIX     存储根文件夹的完整路径，该文件夹中安装了本地可自定义文件。
LOCKUI     指定锁定工具栏和可固定窗口（例如“设计中心”和“特性”选项板）的位置和大小。
LOFTANG1     设置通过放样操作中第一个横截面的拔模斜度。
LOFTANG2     设置通过放样操作中最后一个横截面的拔模斜度。
LOFTMAG1     设置通过放样操作中第一个横截面的拔模斜度的幅值。 
LOFTMAG2     设置通过放样操作中最后一个横截面的拔模斜度的幅值。
LOFTNORMALS     控制放样对象通过横截面处的法线。指定路径或导向曲线时忽略该设置。
LOFTPARAM     控制放样实体和曲面的形状。
LOGEXPBRIGHTNESS     控制使用光度控制光源时图形的全局亮度级别
LOGEXPCONTRAST     控制使用光度控制光源时图形的全局对比度级别
LOGEXPDAYLIGHT     控制使用光度控制光源时是否使用室外日光
LOGEXPMIDTONES     控制使用光度控制光源时图形的全局中色调级别
LOGFILEMODE     指定是否将文本窗口的内容写入日志文件。
LOGFILENAME     指定当前图形的文本窗口日志文件的路径和名称。
LOGFILEPATH     指定任务中所有图形的文本窗口日志文件的路径。
LOGINNAME     将显示启动程序时配置或输入的用户名。
LONGITUDE     以十进制格式指定图形模型的经度。 
LTSCALE     设置全局线型比例因子。 
LUNITS     设置线性单位。
LUPREC     设置长度单位的小数位数。
LWDEFAULT     设置默认线宽值。
LWDISPLAY     控制是否显示线宽。
LWUNITS     控制线宽单位是以英寸显示还是以毫米显示。
MATSTATE     指示是否已打开“材质”窗口。 
MAXACTVP     设置布局中可同时激活的的视口的最大数目。
MAXSORT     设置由列表命令进行排序的符号名或块名的最大数目。
MBUTTONPAN     控制定点设备上的第三个按钮或滑轮的操作。
MEASUREINIT     控制从头创建的图形是使用英制还是使用公制默认设置。
MEASUREMENT     控制当前图形是使用英制还是公制填充图案和线型文件。
MENUCTL     控制屏幕菜单中的页面切换。
MENUECHO     设置菜单回显和提示控制位。
MENUNAME     存储自定义文件名，包括文件名的路径。
MIRRTEXT     控制MIRROR命令反映文字的方式。
MODEMACRO     在状态行显示字符串，例如当前图形的名称、时间/日期戳记或特殊模式。 
MSMSTATE     存储一个值，用以指示打开或关闭标记集管理器。
MSOLESCALE     控制具有粘贴到模型空间中的文字的OLE对象的大小。
MSLTSCALE     缩放由annotation scale显示在“模型”选项卡上的线型
MTEXTED     设置用于编辑多行文字对象的应用程序。
MTEXTFIXED     设置多行文字的显示大小和位置。
MTJIGSTRING     设置启动MTEXT命令时显示在光标位置的样例文字内容。
MYDOCUMENTSPREFIX     存储用户当前登录的“My Documents”文件夹的完整路径。
NOMUTT     禁止显示通常情况下不禁止显示的消息。
NORTHDIRECTION     指定北方阳光的角度。 
OBSCUREDCOLOR     指定暗显直线的颜色。
OBSCUREDLTYPE     指定遮挡线的线型。
OFFSETDIST     设置默认的偏移距离。
OFFSETGAPTYPE     控制偏移闭合多段线时处理线段之间的潜在间隙的方式。
OLEfRadiusAME     控制是否显示和打印图形中所有OLE对象的边框。
OLEHIDE     控制OLE对象的显示和打印。
OLEQUALITY     设置OLE对象的默认打印质量。
OLESTARTUP     控制打印时是否加载嵌入的OLE对象的源应用程序。
OPMSTATE     存储一个值，用以指示打开、关闭或隐藏“特性”选项板。
ORTHOMODE     限定光标在正交方向移动。
OSMODE     设置执行的对象捕捉模式。
OSNAPCOORD     控制是否在命令提示下输入坐标以替代执行对象捕捉。 
OSNAPHATCH     旧式的。使用OSoPointIONS系统变量控制对象捕捉是否忽略图案填充对象。
OSNAPNODELEGACY     控制“节点”对象捕捉是否可用于捕捉到多行文字对象。
OSNAPZ     控制对象捕捉是否自动投影到与当前UCS中位于当前标高的XY平面平行的平面上。
OSoPointIONS     使用动态UCS时，将自动隐藏图案填充对象和具有负Z值的几何体上的对象捕捉。
PALETTEOPAQUE     控制是否可以使窗口透明。 
PAPERUPDATE     试图以不同于为绘图仪配置文件指定的默认值的图纸尺寸打印布局时，控制警告对话框的显示。 
PDMODE     控制显示点对象的方式。有关输入值的详细信息，请参见POINT命令。
PDSIZE     设置点对象的显示尺寸。
PEDITACCEPT     禁止在PEDIT中显示“选定的对象不是多段线”提示，将选定对象自动转换为多段线。
PELLIPSE     控制由ELLIPSE命令创建的椭圆类型。
PERIMETER     存储由AREA或LIST命令计算的最后一个周长值。 
PERSPECTIVE     指定当前视口是否显示透视视图。
PERSPECTIVECLIP     确定眼点剪裁的位置。
PFACEVMAX     设置每个面的最大顶点数。
PICKADD     控制后续选择是替换当前选择集还是添加到其中。
PICKAUTO     控制提示“选择对象”时是否自动显示选择窗口。
PICKBOX     以像素为单位设置对象选择目标的高度。 
PICKDRAG     控制绘制选择窗口的方法。
PICKFIRST     控制在发出命令之前（先选择后执行）还是之后选择对象。
PICKSTYLE     控制编组选择和关联图案填充选择的使用。
PLATFORM     指示正在使用的平台。
PLINEGEN     设置围绕二维多段线的顶点生成线型图案的方式。
PLINETYPE     指定是否使用优化的二维多段线。
PLINEWID     存储默认的多段线宽度。
PLOTOFFSET     控制打印偏移是相对于可打印区域还是相对于图纸边。
PLOTROTMODE     控制打印方向。
PLQUIET     控制是否显示可选的相关打印对话框和非致命脚本错误。 
POLARADDANG     存储极轴追踪和极轴捕捉的其他角度。 
POLARANG     设置极轴角增量。
POLARDIST
SNAPTYPE系统变量设置为 1（极轴捕捉）时，设置捕捉增量。
POLARMODE     控制极轴追踪和对象捕捉追踪的设置。
POLYSIDES     设置POLYGON命令的默认边数。取值范围为 3 到 1024。
POPUPS     显示当前配置的显示驱动程序状态。
PREVIEWEFFECT     指定用于预览对象选择的视觉效果。 
PREVIEWFILTER     从选择预览中排除指定的对象类型。
PRODUCT     返回产品名称。
PROGRAM     返回程序名称。
PROJECTNAME     为当前图形指定工程名称。
PROJMODE     设置用于修剪或延伸的当前投影模式。
PROXYGRAPHICS     指定是否将代理对象的图像保存在图形中。 
PROXYNOTICE     在创建代理时显示通知。
PROXYSHOW     控制代理对象在图形中的显示。
PROXYWEBSEARCH     指定程序检查对象激活器的方式。
PSLTSCALE     控制在图纸空间视口中显示的对象的线型比例。
PSOLHEIGHT     保存POLYSOLID命令创建扫掠实体对象时最后一次输入的高度值。
PSOLWIDTH     保存POLYSOLID命令创建扫掠实体对象时最后一次输入的的宽度值。
PSTYLEMODE     指示当前图形处于颜色相关打印样式模式还是命名打印样式模式。 
PSTYLEPOLICY     控制打开在AutoCAD2000 之前的版本中创建的图形或不使用图形模板从头创建新图形时，使用的打印样式模式。
PSVPSCALE     为所有新创建的视口设置视图比例因子。
PUBLISHALLSHEETS     控制发出PUBLISH命令时如何填写“发布”对话框列表
PUBLISHCOLLATE     控制是否将图纸作为单个作业发布
PUCSBASE     存储定义正交UCS设置（仅用于图纸空间）的原点和方向的UCS名称。
QCSTATE     确定“快速计算”计算器处于打开还是关闭状态。
QTEXTMODE     控制文字的显示方式。 
RASTERDPI     控制将毫米或英寸转换为像素（或反之）时的图纸尺寸和打印比例。。
RASTERPREVIEW     控制是否将BMP预览图像与图形一起保存。
RECOVERYMODE     控制系统出现故障后是否记录图形修复信息。
REFEDITNAME     显示正在编辑的参照名称。
REGENMODE     控制图形的自动重生成。
RE-INIT     重新初始化数字化仪、数字化仪端口和acad.pgp文件。
REMEMBERFOLDERS     控制显示在标准文件选择对话框中的默认路径。
RENDERPREFSSTATE     储存一个值，用以指示打开或关闭“渲染设置”选项板。
RENDERUSERLIGHTS     控制渲染过程中是否转换用户光源
REPORTERROR     控制程序异常关闭时是否可以向Autodesk发送错误报告。
ROAMABLEROOTPREFIX     存储根文件夹的完整路径。
RTDISPLAY     控制执行实ZOOM或PAN命令时光栅图像和OLE对象的显示。
SAVEFIDELITY     控制保存图形时是否保存其视觉逼真度
SAVEFILE     存储当前自动保存的文件名。
SAVEFILEPATH     指定当前任务中所有自动保存文件目录的路径。
SAVENAME     显示最近保存的图形的文件名和目录路径。
SAVETIME     以分钟为单位设置自动保存时间间隔。
SCREENBOXES     存储绘图区域的屏幕菜单区显示的框数。
SCREENMODE     指示显示的状态。
SCREENSIZE     以像素为单位存储当前视口大小（X和Y）。
SELECTIONANNODISPLAY     控制选定annotative对象时，换算比例表示法是否暂时以较暗状态显示
SELECTIONAREA     控制选择区域的显示效果。
SELECTIONAREAOPACITY     控制进行窗口选择和交叉选择时选择区域的透明度。 
SELECTIONPREVIEW     控制光标滚动过对象时的亮显方式。
SETBYLAYERMODE     控制为SETBYLAYER选择哪些特性
SHADEDGE     控制渲染时边的着色。
SHADEDIF     设置漫反射光与环境光的比率。
SHADOWPLANELOCATION     控制用于显示阴影的不可见地平面的位置。 
SHORTCUTMENU     控制“默认”、“编辑”和“命令”模式的快捷菜单在绘图区域是否可用。
SHOWHIST     控制图形中实体的“显示历史记录”特性。 
SHOWLAYERUSAGE     控制图层特性管理器中“指示正在使用的图层”选项是否被选。
SHPNAME     设置默认的形名称。
SIGWARN     控制打开带有附着的数字签名的文件时是否发出警告。
SKETCHINC     设置用于SKETCH命令的记录增量。
SKPOLY     确定SKETCH命令生成直线还是生成多段线。
SNAPANG     设置当前视口的捕捉和栅格旋转角度。旋转角相对当前UCS指定。
SNAPBASE     相对于当前UCS设置当前视口的捕捉和栅格原点。
SNAPISOPAIR     控制当前视口的等轴测平面。
SNAPMODE     打开或关闭捕捉模式。
SNAPSTYL     设置当前视口的捕捉样式。
SNAPTYPE     设置当前视口的捕捉类型。
SNAPUNIT     设置当前视口的捕捉间距。
SOLIDCHECK     为当前任务打开或关闭实体校验。
SOLIDHIST     控制复合实体是否保留包含在复合实体中原始对象的“历史记录”。
SPLfRadiusAME     控制样条曲线和样条拟合多段线的显示。
SPLINESEGS     设置PEDIT命令的“样条曲线”选项生成的样条拟合多段线线段数目。
SPLINETYPE     设置PEDIT命令的“样条曲线”选项生成的曲线类型。
SSFOUND     如果搜索图纸集成功，则显示图纸集路径和文件名。
SSLOCATE     控制打开图形时是否定位和打开与该图形相关联的图纸集。
SSMAUTOOPEN     控制当打开与图纸相关联的图形时图纸集管理器的显示行为。
SSMPOLLTIME     控制图纸集中状态数据的自动刷新时间间隔。
SSMSHEETSTATUS     控制图纸集中状态数据的刷新方式。
SSMSTATE     确定“图纸集管理器”窗口处于打开还是关闭状态。
STANDARDSVIOLATION     指定创建或修改非标准对象时，是否通知用户当前图形中存在标准冲突。
STARTUP     控制使用NEW和QNEW命令创建新图形时，是否显示“创建新图形”对话框。还控制当应用程序启动时是否显示“启动”对话框。
STEPSIZE     指定漫游或飞行模式中每一步的大小。
STEPSPERSEC     指定漫游或飞行模式中每秒执行的步数。
SUNPROPERTIESSTATE     指示“阳光特性”窗口处于打开还是关闭状态。 
SUNSTATUS     控制阳光是否在当前视口中投射光线。 
SURFTAB1     为RULESURF和TABSURF命令设置要生成的列表数目。同时为REVSURF和EDGESURF命令设置在M方向的网格密度。
SURFTAB2     为REVSURF和EDGESURF命令设置在N方向的网格密度。
SURFTYPE     控制PEDIT命令的“平滑”选项要执行的曲面拟合类型。
SURFU     为PEDIT命令的“平滑”选项设置在M方向的曲面密度以及曲面对象上的U素线密度。
SURFV     为PEDIT命令的“平滑”选项设置在N方向的曲面密度以及曲面对象上的V素线密度。
SYSCODEPAGE     指示由操作系统所决定的系统代码页。要更改代码页，请参见操作系统的“帮助”。
TABLEINDICATOR     控制当打开在位文字编辑器以编辑表格单元时，行数和列字母的显示。 
TABLETOOLBAR     控制表格工具栏的显示。
TABMODE     控制数字化仪的使用。
TARGET     存储当前视口中目标点的位置（用UCS坐标表示）。
TBCUSTOMIZE     控制是否可以自定义工具选项板组。
TDCREATE     存储创建图形时的本地时间和日期。
TDINDWG     存储总的编辑时间，即在两次保存当前图形之间花费的总时间。
TDUCREATE     存储创建图形时的通用时间和日期。
TDUPDATE     存储上次更新/保存时的本地时间和日期。
TDUSRTIMER     存储用户花费时间计时器。
TDUUPDATE     存储上次更新/保存时的通用时间和日期。
TEMPOVERRIDES     打开或关闭正交模式、对象捕捉或极轴模式临时替代键。 
TEMPPREFIX     包含为放置临时文件而配置的目录名（如果有的话），附带路径分隔符。
TEXTEVAL     控制如何判定用TEXT（使用AutoLISP）或 -TEXT输入的文字字符串。
TEXTFILL     控制打印和渲染时TrueType字体的填充方式。
TEXTOUTPUTFILEFORMAT     提供打印和文本窗口日志文件的Unicode选项。 
TEXTQLTY     设置文字轮廓的分辨率镶嵌精度
TEXTSIZE     设置用当前文字样式绘制的新文字对象的默认高度。
TEXTSTYLE     当前使用的文字样式的名称。
THICKNESS     设置当前的三维厚度。
TILEMODE     将“模型”选项卡或上一个布局选项卡置为当前。
TIMEZONE     设置图形中阳光的时区。 
TOOLTIPMERGE     将绘图图工具栏提示合并为单个工具栏提示。 
TOOLTIPS     控制工具栏上工具栏提示的显示。
TPSTATE     确定“工具选项板”窗口处于打开还是关闭状态。
TRACEWID     设置宽线的默认宽度。
TRACKPATH     控制极轴追踪和对象捕捉追踪对齐路径的显示。
TRAYICONS     控制是否在状态栏显示状态托盘。
TRAYNOTIFY     控制是否在状态栏托盘中显示服务通知。
TRAYTIMEOUT     控制服务通知的显示时间长度（以秒为单位）。
TREEDEPTH     指定最大深度，即树状结构的空间索引可以分出分支的次数。
TREEMAX     通过限制空间索引（八分树）中的节点数目，从而限制重生成图形时占用的内存。
TRIMMODE     控制是否修剪倒角和圆角选定边。
TSPACEFAC     控制多行文字的行间距。
TSPACETYPE    控制多行文字中使用的行间距类型。
TSTACKALIGN     控制堆叠文字的垂直对齐方式。
TSTACKSIZE     控制堆叠文字分数高度相对于选定文字的当前高度的百分比。
UCSAXISANG     使用UCS命令的X、Y或Z选项绕其一个轴旋转UCS时，存储默认角度。 
UCSBASE     存储定义正交UCS设置的原点和方向的UCS名称。
UCSDETECT     控制是否已激活动态UCS获取。
UCSFOLLOW     从一个UCS转换到另一个UCS时是否生成平面视图。 
UCSICON     显示当前视口或布局的UCS图标。 
UCSNAME     存储当前空间当前视口的当前坐标系名称。
UCSORG     存储当前空间中当前视口的当前坐标系原点。
UCSORTHO     确定恢复正交视图时是否自动恢复相关的正交UCS设置。
UCSVIEW     确定当前UCS是否随命名视图一起保存。 
UCSVP     确定视口中的UCS是保持不变还是进行相应改变以反映当前视口的UCS状态。
UCSXDIR     存储当前空间中当前视口的当前UCS的X方向。 
UCSYDIR     存储当前空间中当前视口的当前UCS的Y方向。 
UNDOCTL     指示UNDO命令的“自动”、“控制”和“编组”选项的状态。
UNDOMARKS     存储“标记”选项放置在UNDO控制流中的标记数目。
UNITMODE     控制单位的显示格式。 
UPDATETHUMBNAIL     控制图纸集管理器中的略图预览的更新。 
USERI1-5     提供整数值存储和检索功能。共有五个系统变量：USERI1、USERI2、USERI3、USERI4 和USERI5。
USERR1-5     提供实数的存储和检索功能。共有五个系统变量：USERR1、USERR2、USERR3、USERR4 和USERR5。
USERS1-5     提供文字字符串数据的存储和检索功能。共有五个系统变量：USERS1、USERS2、USERS3、USERS4 和USERS5。 
VIEWCTR     存储当前视口中视图的中心。该值用UCS坐标表示。
VIEWDIR     存储当前视口中的观察方向（用UCS坐标表示）。
VIEWMODE     存储当前视口的观察模式。
VIEWSIZE     存储当前视口中显示的视图的高度（按图形单位测量）。 
VIEWTWIST     存储相对于WCS测量的当前视口的视图旋转角度。
VISRETAIN     控制依赖外部参照的图层的特性。控制可见性、颜色、线型、线宽和打印样式。
VPLAYEROVERRIDES     指示对于当前图层视口是否存在任何具有视口 (VP) 特性替代的图层。
VPLAYEROVERRIDESMODE     控制是否显示和打印与布局视口关联的图层特性替代。
VPMAXIMIZEDSTATE     存储指示是否将视口最大化的值。
VSBACKGROUNDS     控制是否在应用于当前视口的视觉样式中显示背景。
VSEDGECOLOR     设置当前视口视觉样式中边的颜色。
VSEDGEJITTER     控制使直线显示出铅笔勾画特征的程度。 
VSEDGEOVERHANG     将线延伸至超过其交点，以达到手绘的效果。
VSEDGES     控制显示在视口中的边的类型。
VSEDGESMOOTH     指定显示折痕边的角度。
VSFACECOLORMODE     控制如何计算面的颜色。
VSFACEHIGHLIGHT     控制当前视口中不具有材质的面上镜面亮显的显示。
VSFACEOPACITY     控制当前视口中面的透明度。 
VSFACESTYLE     控制如何在当前视口中显示面。
VSHALOGAP     设置应用于当前视口的视觉样式中的光晕间隔。
VSHIDEPRECISION     控制应用于当前视口的视觉样式中的隐藏和着色的精度。
VSINTERSECTIONCOLOR     指定应用于当前视口的视觉样式中相交多段线的颜色。
VSINTERSECTIONEDGES     控制应用于当前视口的视觉样式中相交边的显示。
VSINTERSECTIONLTYPE     设置应用于当前视口的视觉样式中的交线线型。
VSISOONTOP     显示应用于当前视口的视觉样式中着色对象顶部的素线。 
VSLIGHTINGQUALITY     设置当前视口中的光源质量。
VSMATERIALMODE     控制当前视口中材质的显示。
VSMAX     存储当前视口虚屏的右上角。
VSMIN     存储当前视口虚屏的左下角。
VSMONOCOLOR     为应用于当前视口的视觉样式中面的单色和染色显示设置颜色。
VSOBSCUREDCOLOR     指定应用于当前视口的视觉样式中遮挡（隐藏）线的颜色。
VSOBSCUREDEDGES     控制是否显示遮挡（隐藏）边。
VSOBSCUREDLTYPE     指定应用于当前视口的视觉样式中遮挡（隐藏）线的线型。
VSSHADOWS     控制视觉样式是否显示阴影。
VSSILHEDGES     控制应用于当前视口的视觉样式中的实体对象轮廓边的显示。
VSSILHWIDTH     以像素为单位指定当前视口中轮廓边的宽度。
VSSTATE     打开或关闭“视觉样式”窗口。
VTDURATION     以毫秒为单位设置平滑视图过渡的期限。
VTENABLE     控制何时使用平滑视图过渡。 
VTFPS     以帧/每秒为单位设置平滑视图过渡的最小速度。
WHIPARC     控制圆和圆弧是否平滑显示。
WHIPTHREAD     控制是否使用附加处理器来提高操作速度，WHIPTHREAD对单处理器计算机无效。
WINDOWAREACOLOR     控制窗口选择时透明选择区域的颜色。 
WMFBKGND     控制以Windows图元文件 (WMF) 格式插入对象时背景的显示。
WMFFOREGND     控制以Windows图元文件 (WMF) 格式插入对象时前景色的指定方式。
WORLDUCS     指示UCS是否与WCS相同。
WORLDVIEW     确定响应DVIEW和VPOINT命令的输入是相对于WCS（默认）还是相对于当前UCS。
WRITESTAT     指示图形文件是只读的还是可写的。
WSCURRENT     在命令行界面中返回当前工作空间名称并将工作空间置为当前工作空间。
XCLIPfRadiusAME     控制外部参照剪裁边界的可见性。
XEDIT     控制当前图形被其他图形参照时是否可以在位编辑。
XFADECTL     控制正被在位编辑的参照的褪色度百分比。
XLOADCTL     打开或关闭外部参照的按需加载功能，并控制是打开参照的图形还是打开副本。 
XLOADPATH     创建用于存储按需加载的外部参照文件临时副本的路径。
XREFCTL     控制是否创建外部参照日志(XLG)文件。
XREFNOTIFY     控制更新或缺少外部参照通知。
XREFTYPE     控制附着或覆盖外部参照时的默认参照类型。
ZOOMFACTOR     控制向前或向后滑动鼠标滚轮时比例的变化程度。
ZOOMWHEEL     滚动鼠标中间的滑轮时，切换透明缩放操作的方向。 */

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

// CPt3d 3D点结构

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

double CPt3d::GetVectorAzimuth(const CPt3d& ptEnd) //返回-PI到PI
{
	return GetVectorAzimuth(*this, ptEnd);
}

double CPt3d::GetVectorAzimuth(const CPt3d& ptStart, const CPt3d& ptEnd) //返回-PI到PI
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
	//     fRotation += -nMult * 2 * PI;//处理大于等于2*PI旋转角度
	//     if(fRotation < 0) //如果是顺时针旋转，转换成逆时针角度
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

// 文字样式

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

// 表格样式
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

// 块记录

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

// 标注

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

void CDimensionStyle::SetArrow(ArxRleString lpszName)		//箭头样式
{
	if(!m_pDimensionStyle->objectId().isNull())
	{
		m_pDimensionStyle->setDimsah(false);
		m_pDimensionStyle->setDimblk(lpszName);
	}
}

void CDimensionStyle::SetArrow(ArxRleString lpszName1, ArxRleString lpszName2)		//箭头1样式,箭头2样式
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

// 用户坐标系

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

// 图元基类

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

// 点

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

// 直线

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

// CPolyline  多段线图元

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

// 圆

#define S(a, b, c) (a.x- c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x)
static double Y_Coordinates(double x,double y,double k,double x0)
{
	return k * x0 - k * x + y;
}
//dRadius正负表示圆心在弦的那侧，左负右正
static bool Circle_Center(CPt3d p1,CPt3d p2,double dRadius, CPt3d& center)
{
	if(CompareFloat(p2.x, p1.x) == 0)//x坐标相同
	{
		center.y = (p1.y + p2.y) * 0.5;
		if((CompareFloat(p2.y, p1.y) < 0 && dRadius > 0) ||//半径大于零，取直线方向的右侧圆心
			(CompareFloat(p2.y, p1.y) > 0 && dRadius < 0))//半径小于零，取直线方向的左侧圆心
			center.x = p1.x + sqrt(dRadius * dRadius -(p1.y - p2.y) * (p1.y - p2.y) / 4.0);
		else
			center.x = p1.x - sqrt(dRadius * dRadius -(p1.y - p2.y) * (p1.y - p2.y) / 4.0);
		return true;
	}
	else if(CompareFloat(p2.y, p1.y) == 0)//y坐标相同
	{
		center.x = (p1.x + p2.x) * 0.5;
		if((CompareFloat(p2.x, p1.x) < 0 && dRadius > 0) ||//半径大于零，取直线方向的右侧圆心
			(CompareFloat(p2.x, p1.x) > 0 && dRadius < 0))//半径小于零，取直线方向的左侧圆心
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

		double x0 = (p1.y * p2.x - p2.y * p1.x) / (p1.y - p2.y); //两点所在直线X截距
		double fAngle = atan4(p2.y - p1.y, p2.x - p1.x); //两点所在直线的斜角
		double fAngle1 = atan4(center1.y, center1.x - x0); //两点所在直线的y=0点和圆心1连接的直线的斜角
		double fAngle2 = atan4(center2.y, center2.x - x0); //两点所在直线的y=0点和圆心2连接的直线的斜角
		if(CompareFloat(fAngle1, fAngle2) == 0)
		{
			center.x = (center1.x + center2.x) * 0.5;
			center.y = (center1.y + center2.y) * 0.5;
			return true;
		}
		double fS1 = p1.y * p1.y + (p1.x - x0) * (p1.x - x0);//ptStart点到(x0,0)的距离平方
		double fS2 = p2.y * p2.y + (p2.x - x0) * (p2.x - x0);//ptEnd点到(x0,0)的距离平方
		if(CompareFloat(fS1, fS2) < 0)//判断两点方向
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
	while(acedEntSel(_T("\n")+strPrompt,entres,ptres) != RTCAN) //RTNORM 成功 RTERROR 失败  RTCAN 取消
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

// 圆弧

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

// 椭圆曲线

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

// 文本

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

// 多文本

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

// 块

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
			for(pIterator->start();pIterator->done();pIterator->step())//将块记录中所有的Attibute进行遍历
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

// 视口

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

// 标注

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

//填充

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

//表
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

// 布局
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
	//这里ptLeftBottom和ptMapLeftBottom的实际意义是相反的，编写程序时没有注意，后来也不好改了，有点绕。
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

// 对象组
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
	// 将实体添加到图形数据库
	AcDbObjectId lineId;
	lineId = CCreatEnt::PostToModelSpace(pLine);
	return lineId;
}

// 将实体添加到图形数据库的模型空间
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
	// 将实体添加到图形数据库
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
	// 使用几何类获得圆心、半径
	AcGeCircArc2d geArc(ptStart, ptOnArc, ptEnd);
	AcGePoint2d ptCenter = geArc.center();
	double radius = geArc.radius();
	// 计算起始和终止角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();
	return CCreatEnt::CreateArc(ptCenter, radius, startAngle, endAngle);
}

// 创建文字实现部分
AcDbObjectId CCreatEnt::CreateText(const AcGePoint3d& ptInsert,
								   ArxRleString text, AcDbObjectId style,
								   double height, double rotation)
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height, rotation);
	return CCreatEnt::PostToModelSpace(pText);
}

// 创建多行文字实现部分
AcDbObjectId CCreatEnt::CreateMText(const AcGePoint3d& ptInsert,
									ArxRleString text, AcDbObjectId style,
									double height, double width)
{
	AcDbMText *pMText = new AcDbMText();
	// 设置多行文字的特性
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
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
		return objectId;

	//判断图层表中是否已经有此图层
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

	AcDbLayerTable *pLayerTable;  //先声明一个空的层表指针
	AcDbDatabase* db = ARXRLEDB;  //当前图形数据库
	if(db->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
		return objectId;

	if(!pLayerTable->has(lpszLayer))
	{
		AcDbLayerTableRecord *pLayerTblRcd= new AcDbLayerTableRecord;//新层表记录
		pLayerTblRcd->setName(lpszLayer);   //设定图层名
		pLayerTblRcd->setIsFrozen(0);   // 图层解冻
		pLayerTblRcd->setIsOff(0);      // 打开图层
		pLayerTblRcd->setVPDFLT(0);     // 使用默认视口
		pLayerTblRcd->setIsLocked(0);   // 图层解锁
		AcCmColor color;                // AcCmColor是ACAD颜色管理类
		color.setColorIndex(iColorIndex);      
		pLayerTblRcd->setColor(color);  // 图层颜色为红色
		pLayerTblRcd->setLineWeight(AcLineWeight); //设置线宽
		// 为给新图层设置线型，要得到线型表记录的ID。以下的代码演示如何得到并操作记录ID
		AcDbLinetypeTable *pLinetypeTbl;
		AcDbObjectId ltId;
		db->getSymbolTable(pLinetypeTbl, AcDb::kForRead); //打开线型表为写入状态
		if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //获取lpszLinetype线型ID
		{
			pLinetypeTbl->close();
			db->loadLineTypeFile(lpszLinetype,_T("acadiso.lin")); //从线型文件中获取lpszLinetype线型
			db->getLinetypeTable(pLinetypeTbl,AcDb::kForRead);
			if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //获取lpszLinetype线型ID
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
		
		pLayerTblRcd->setIsFrozen(0);   // 图层解冻
		pLayerTblRcd->setIsOff(0);      // 打开图层
		pLayerTblRcd->setVPDFLT(0);     // 使用默认视口
		pLayerTblRcd->setIsLocked(0);   // 图层解锁
		AcCmColor color;                // AcCmColor是ACAD颜色管理类
		color.setColorIndex(iColorIndex);      
		pLayerTblRcd->setColor(color);  // 图层颜色为红色
		pLayerTblRcd->setLineWeight(AcDb::kLnWt013); //设置线宽
		AcDbLinetypeTable *pLinetypeTbl;
		AcDbObjectId ltId;
		db->getSymbolTable(pLinetypeTbl, AcDb::kForRead);
		if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //获取lpszLinetype线型ID
		{
			pLinetypeTbl->close();
			db->loadLineTypeFile(lpszLinetype,_T("acadiso.lin")); //从线型文件中获取lpszLinetype线型
			db->getLinetypeTable(pLinetypeTbl,AcDb::kForRead);
			if(pLinetypeTbl->getAt(lpszLinetype, ltId) != Acad::eOk) //获取lpszLinetype线型ID
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
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
		return objectId;

	//判断图层表中是否已经有此图层
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
	if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
		return objectId;

	//判断图层表中是否已经有此图层
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
		if(ARXRLEDB->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
			return false;

		//判断图层表中是否已经有此图层
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

	//AcDbLayerTable *pLayerTable;  //先声明一个空的层表指针
	//AcDbDatabase* db = ARXRLEDB;  //当前图形数据库
	//if(db->getSymbolTable(pLayerTable, AcDb::kForWrite) != Acad::eOk) //打开层表为写入状态
	//{
	//	acutPrintf(_T("无法获取到当前活动的图形数据库的图层指针"));
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
				strLine.Replace(_T("；"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("，"), _T(";"));
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
				strLine.Replace(_T("；"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("，"), _T(";"));
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
		strTemp.Format(_T("桩号;高程\n"));
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
				strLine.Replace(_T("；"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("，"), _T(";"));
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
		strTemp.Format(_T("距离;高程\n"));
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

double AdjustAngle02(double fAngle) //弧度 角度调整到0到2π之间
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

double AdjustAngleNP(double fAngle) //弧度 角度调整到-π到π之间
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
	fRadiusotation -= 2 * PI;//处理大于等于2*PI旋转角度
	if(fRadiusotation < 0) //如果是顺时针旋转，转换成逆时针角度
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
	//仍需要判断交点是否在两个线段上
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
	// 所有修改之前，锁定文档
	if(lockDocument) acDocManager->lockDocument(acDocManager->curDocument(),mode ? AcAp::kWrite : AcAp::kRead);

	return acdbOpenAcDbEntity(pEnt, id, mode, openErasedEntity);
}

void CloseEntity(AcDbEntity* pEnt, bool unLockDocument, bool flushGraphics)
{
	pEnt->close();

	// 所有修改完成，解锁文档
	if(unLockDocument) acDocManager->unlockDocument(acDocManager->curDocument());

	// 刷新显示
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
			acutPrintf(_T("\n---DWG中添加点失败！---"));
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

		SAFEARRAYBOUND sabPt1,sabPt2;//安全数组索引结构
		sabPt1.lLbound = 0L;  //下限
		sabPt1.cElements = 3; //元素个数
		sabPt2.lLbound = 0L;
		sabPt2.cElements = 3;

		SAFEARRAY *psaPt1 = NULL, *psaPt2 = NULL;  //安全数组
		psaPt1 = SafeArrayCreate(VT_R8, 1, &sabPt1); //创建一个一维安全数组
		psaPt2 = SafeArrayCreate(VT_R8, 1, &sabPt2);
		if(psaPt1 != NULL && psaPt2 != NULL)
		{
			long index = 0; // 元素位置由右向左排列，即先列再行1列1行;
			SafeArrayPutElement(psaPt1, &index, &fX1);//向安全数组中添加元素
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
			acutPrintf(_T("\n---DWG中添加直线失败！---"));
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
			acutPrintf(_T("\n---DWG中添加多段线失败！---"));
	}
	CATCH(COleDispatchException,e) 
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;

	/*
	//使用SAFEARRAR实现二维数组
	{
		VARTYPE vt = VT_I4;    //数组元素的类型，long
		SAFEARRAYBOUND sab[2]; //用于定义数组的维数和下标的起始值
		sab[0].cElements = 2;
		sab[0].lLbound = 0;
		sab[1].cElements = 2;
		sab[1].lLbound = 0;

		//创建一个2*2的类型为long的二维数组
		SAFEARRAY* psa = SafeArrayCreate(vt, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);
		if(NULL == psa)
			throw;

		//通过指向数组的指针来对二维数组的元素进行间接赋值
		long (*pArray)[2] = NULL;
		HRESULT hRet = SafeArrayAccessData(psa, (void **)&pArray);
		if(FAILED(hRet))
			throw;

		memset(pArray, 0, 2*2*sizeof(long));

		//释放指向数组的指针
		SafeArrayUnaccessData(psa);
		pArray = NULL;

		//对二维数组的元素进行逐个赋值
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

		//把SAFEARRAY转换为VARIANT
		VARIANT var;
		var.vt = VT_ARRAY | vt; //vt必须和psa的数据类型保持一致
		var.parray = psa;
		SafeArrayDestroy(psa);
		psa = NULL;
	}



	//使用COleSafeArray实现二维数组
	{
		VARTYPE vt = VT_I4; //数组元素的类型，long
		SAFEARRAYBOUND sab[2]; //用于定义数组的维数和下标的起始值   
		sab[0].cElements = 2;    
		sab[0].lLbound = 0;    
		sab[1].cElements = 2;    
		sab[1].lLbound = 0;    
		COleSafeArray olesa;    
		olesa.Create(vt, sizeof(sab)/sizeof(SAFEARRAYBOUND), sab);  
		//通过指向数组的指针来对二维数组的元素进行间接赋值
		long (*pArray)[2] = NULL;
		olesa.AccessData((void **)&pArray);
		memset(pArray, 0, 2*2*sizeof(long));
		//释放指向数组的指针
		olesa.UnaccessData();
		pArray = NULL;

		//对二维数组的元素进行逐个赋值
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
		VARIANT var = (VARIANT)olesa; //把COleSafeArray变量转换为VARIANT
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
			acutPrintf(_T("\n---DWG中添加圆失败！---"));
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
			acutPrintf(_T("\n---DWG中添加圆弧失败！---"));
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
	// 计算起始和终止角度
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
	// 计算起始和终止角度
	AcGeVector2d vecStart(oBeginPt.x - ptCenter.x, oBeginPt.y - ptCenter.y);
	AcGeVector2d vecEnd(oEndPt.x - ptCenter.x, oEndPt.y - ptCenter.y);
	double fBeginAngle = vecStart.angle();
	double fEndAngle = vecEnd.angle();

	double fBulge = 0.0;
	double fAlfa = fEndAngle - fBeginAngle;
	if (fAlfa < 0.0)//如果终点角度小于起点角度，取补角
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
	if (fAlfa < 0.0)//如果终点角度小于起点角度，取补角
		fAlfa = 2 * PI + fAlfa;

	fBulge = tan(fAlfa/4);
	return fBulge;
}

double GetArcBulge(AcDbArc*& pArc)
{
	double dStartAngle = pArc->startAngle();
	double dEndAngle = pArc->endAngle();

	double dAlfa = dEndAngle - dStartAngle;
	if (dAlfa < 0.0)//如果终点角度小于起点角度，取补角
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
			acutPrintf(_T("\n---DWG中添加圆失败！---"));
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
	pText->setTextString(lpszText); //文本内容
	pText->setHeight(fHeight); //文本高度
	pText->setRotation(fRotation); //文本旋转角度
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
	pText->setPosition(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //文本对齐点坐标
	pText->setAlignmentPoint(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //文本对齐点坐标

	ArxRleUtils::transformToWcs(pText, ARXRLEDB);
	ArxRleUtils::addToCurrentSpaceAndClose(pText);
}

void AddText(AcDbTextStyleTableRecord* ts, ArxRleString lpszText, CPt3d& oAlignmentPt, double fHeight, double fRotation, ArxAlignment eAlign)
{
	AcDbText* pText = new AcDbText;
	pText->setDatabaseDefaults();
	if(ts != NULL) pText->setTextStyle(ts->objectId());
	pText->setTextString(lpszText); //文本内容
	pText->setHeight(fHeight); //文本高度
	pText->setRotation(fRotation); //文本旋转角度
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
	pText->setPosition(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //文本对齐点坐标
	pText->setAlignmentPoint(AcGePoint3d(oAlignmentPt.x,oAlignmentPt.y,oAlignmentPt.z)); //文本对齐点坐标

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
	pText->setTextString(prText.value()); //文本内容
	pText->setAlignmentPoint(AcGePoint3d(prInsertPt.value().x,prInsertPt.value().y,prInsertPt.value().z)); //文本对齐点坐标
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
			acutPrintf(_T("\n---DWG中添加圆失败！---"));
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
	pMText->setContents(lpszText); //文本内容
	if(abs(fWidth) > 0)
		pMText->setWidth(fabs(fWidth)); //文本范围宽度
	else
		pMText->setWidth(fabs(lpszText.GetLength()*1.0)); //文本范围宽度
	pMText->setLocation(AcGePoint3d(oInsertPt.x,oInsertPt.y,oInsertPt.z)); //文本插入点
	pMText->setTextHeight(fHeight); //文本高度
	pMText->setRotation(fRadiusotation); //文本旋转角度
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
			acutPrintf(_T("\n---DWG中添加圆失败！---"));
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
	AcDbDatabase* db = ARXRLEDB;  //当前图形数据库
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

	CString blkName;//外部文件作为块插入的块名
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
	AcDbDatabase* db = ARXRLEDB;  //当前图形数据库
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
	//用CAD命令偏移示例
	ads_name e1;//需要偏移的实体
	ads_point p1;//偏移到那一边
	p1[X] = pt.x;
	p1[Y] = pt.y;
	p1[Z] = pt.z;
	if(ArxRleUtils::objIdToEname(id, e1) == Acad::eOk)
		acedCommandS(RTSTR,_T("offset"),RTREAL,oft,RTENAME,e1,RTPOINT,p1,RTSTR,_T(""),RTNONE);
}

void cmd_fillet(AcDbObjectId id1, AcDbObjectId id2, CPt3d pt1, CPt3d pt2, double r)
{
	//使用CAD命令倒角：
	ads_name e1,e2;//需要偏移的实体
	ads_point p1,p2;//偏移到那一边
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