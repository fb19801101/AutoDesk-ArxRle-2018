// ArxRleAttributeListItem.h : header file
//

#ifndef ARXRLE_ATTRIBUTELISTITEM_H
#define ARXRLE_ATTRIBUTELISTITEM_H

#define PIT_COMBO	      0	// PIT = property item type
#define PIT_EDIT	      1
#define PIT_LAYER	      2
#define PIT_TEXTSTYLE     3
#define PIT_DIMSTYLE      4
#define PIT_WORKSTYLE     5
#define PIT_COLOR	      6
#define PIT_LINETYPE      7
#define PIT_LINEWEIGHT    8
#define PIT_FONT	      9
#define PIT_FILE	      10
#define PIT_PATH          11
#define PIT_POINT         12
#define PIT_SEPARATOR     13
#define PIT_BLANK         14
#define PIT_NULL          15


/////////////////////////////////////////////////////////////////////////////
//ArxRleAttributeList Item
class ArxRleAttributeListItem
{
public:
	ArxRleAttributeListItem(CString curKey, CString curValue, int itemType, CString cmbItems,
		long ftWeight = 0, long ftHeight = 12, long ftWidth = 0, BOOL ftItalic = FALSE, CString ftName = L"宋体", COLORREF ftColor = RGB(0,0,0), int ftKeyVal = 0,
		BOOL isExpand = FALSE, int idxExpand = -1, CRect rcExpand = 0,
		COLORREF bkKeyColor = RGB(238,238,238), COLORREF bkValColor = RGB(255,255,255),
		COLORREF txtKeyColor = RGB(0,0,0), COLORREF txtValColor = RGB(0,0,0));

	ArxRleAttributeListItem(const ArxRleAttributeListItem &item);
	ArxRleAttributeListItem& operator=(const ArxRleAttributeListItem &item);

	bool operator<(const ArxRleAttributeListItem &item) const;
	bool operator==(const ArxRleAttributeListItem &item) const;
	static bool compare(const ArxRleAttributeListItem* first, const ArxRleAttributeListItem* second);

public:
	int      m_idxItem;      //项目索引
	CString  m_curKey;       //当前标题
	CString  m_curValue;     //当前数据
	int      m_itemType;     //数据类型
	CString  m_cmbItems;     //组合框数据
	CString  m_sufName;      //文件后缀名

	long     m_ftWeight;     //字体权重
	long     m_ftHeight;     //字体高度
	long     m_ftWidth;      //字体宽度
	BOOL     m_ftItalic;     //字体倾斜
	CString  m_ftName;       //字体名称
	COLORREF m_ftColor;      //字体颜色
	int      m_ftKeyVal;     //标题/文字字体 0标题文字 1标题 2文字

	BOOL     m_isExpand;     //是否展开
	int      m_idxExpand;    //分类索引(-1 -- 普通<不分类>，其它(>=0) -- 分类的索引号)
	CRect    m_rcExpand;     //分类位图矩形框

	COLORREF m_bkKeyColor;   //标题背景颜色
	COLORREF m_bkValColor;   //数据背景颜色
	COLORREF m_txtKeyColor;  //标题文字颜色
	COLORREF m_txtValColor;  //数据文字颜色

	AcDbObjectId m_objId;    //线型、图层、线宽实体ID
};

/////////////////////////////////////////////////////////////////////////////
//ArxRleAttributeList Itema
class ArxRleAttributeListItems
{
public:
	ArxRleAttributeListItems();
	virtual ~ArxRleAttributeListItems();

	ArxRleAttributeListItems(const ArxRleAttributeListItems &items);
	ArxRleAttributeListItems& operator=(const ArxRleAttributeListItems &items);
	ArxRleAttributeListItem* operator[](int index) const;

public:
	void AddComboValue(CString propName, CString curValue, CString cmbItems);
	void AddEditValue(CString propName, CString curValue);
	void AddLayerValue(CString propName, CString curValue);
	void AddTextStyleValue(CString propName, CString curValue);
	void AddDimStyleValue(CString propName, CString curValue);
	void AddWorkStyleValue(CString propName, CString curValue);
	void AddColorValue(CString propName, COLORREF txtValColor);
	void AddLineTypeValue(CString propName, CString curValue);
	void AddLineWeightValue(CString propName, int curValue);
	void AddFontValue(CString propName, CString curValue);
	void AddFileValue(CString propName, CString curValue, CString sufName);
	void AddPathValue(CString propName, CString curValue);
	void AddPointValue(CString propName, CString curValue);
	void AddSeparator(CString propName);

	void InsertComboValue(int index, CString propName, CString curValue, CString cmbItems);
	void InsertEditValue(int index, CString propName, CString curValue);
	void InsertLayerValue(int index, CString propName, CString curValue);
	void InsertTextStyleValue(int index, CString propName, CString curValue);
	void InsertDimStyleValue(int index, CString propName, CString curValue);
	void InsertWorkStyleValue(int index, CString propName, CString curValue);
	void InsertColorValue(int index, CString propName, COLORREF txtValColor);
	void InsertLineTypeValue(int index, CString propName, CString curValue);
	void InsertLineWeightValue(int index, CString propName, int curValue);
	void InsertFontValue(int index, CString propName, CString curValue);
	void InsertFileValue(int index, CString propName, CString curValue, CString sufName);
	void InsertPathValue(int index, CString propName, CString curValue);
	void InsertPointValue(int index, CString propName, CString curValue);
	void InsertSeparator(int index, CString propName);

	void SetComboValue(int index, CString curValue, CString cmbItems);
	void SetEditValue(int index, CString curValue);
	void SetLayerValue(int index, CString curValue);
	void SetTextStyleValue(int index, CString curValue);
	void SetDimStyleValue(int index, CString curValue);
	void SetWorkStyleValue(int index, CString curValue);
	void SetColorValue(int index, COLORREF txtValColor);
	void SetLineTypeValue(int index, CString curValue);
	void SetLineWeightValue(int index, int curValue);
	void SetFontValue(int index, CString curValue);
	void SetFileValue(int index, CString curValue, CString sufName);
	void SetPathValue(int index, CString curValue);
	void SetPointValue(int index, CString curValue);
	void SetKeyValue(int index, CString keyValue);

	void SetKeyColor(int index, COLORREF bkKeyColor, COLORREF txtKeyColor);
	void SetValColor(int index, COLORREF bkValColor, COLORREF txtValColor);
	void SetBkKeyColor(int index, COLORREF bkKeyColor);
	void SetBkValColor(int index, COLORREF bkValColor);
	void SetTxtKeyColor(int index, COLORREF txtKeyColor);
	void SetTxtValColor(int index, COLORREF txtValColor);

	void SetCommonItems(int nCitems);
	int GetCommonItems() const;

	int GetTrueIndex(int index) const;
	CString GetValue(int index) const;
	CString GetKeyValue(int index) const;
	CString GetValValue(int index) const;
	void GetKeyColor(int index, COLORREF &bkKeyColor, COLORREF &txtKeyColor);
	void GetValColor(int index, COLORREF &bkValColor, COLORREF &txtValColor);
	COLORREF GetBkKeyColor(int index) const;
	COLORREF GetBkValColor(int index) const;
	COLORREF GetTxtKeyColor(int index) const;
	COLORREF GetTxtValColor(int index) const;

	void Sort();

	void SetFont(int index, long ftWeight = 0, long ftHeight = 12, long ftWidth = 0, BOOL ftItalic = FALSE, CString ftName = L"宋体", COLORREF ftColor = RGB(0,0,0), int ftKeyVal = 0);
	void SetKeyFont(int index, long ftWeight = 0, long ftHeight = 12, long ftWidth = 0, BOOL ftItalic = FALSE, CString ftName = L"宋体", COLORREF ftColor = RGB(0,0,0));
	void SetValFont(int index, long ftWeight = 0, long ftHeight = 12, long ftWidth = 0, BOOL ftItalic = FALSE, CString ftName = L"宋体", COLORREF ftColor = RGB(0,0,0));

	int AddItem(CString propName, CString curValue, int nItemType, CString cmbItems = L"",
		COLORREF bkKeyColor = RGB(238,238,238), COLORREF bkValColor = RGB(255,255,255), COLORREF txtKeyColor = RGB(0,0,0), COLORREF txtValColor = RGB(0,0,0));
	int InsertItem(int index, CString propName, CString curValue, int nItemType, CString cmbItems = L"",
		COLORREF bkKeyColor = RGB(238,238,238), COLORREF bkValColor = RGB(255,255,255), COLORREF txtKeyColor = RGB(0,0,0), COLORREF txtValColor = RGB(0,0,0));
	void SetItem(int index, CString propName, CString curValue, int nItemType, CString cmbItems = L"",
		COLORREF bkKeyColor = RGB(238,238,238), COLORREF bkValColor = RGB(255,255,255), COLORREF txtKeyColor = RGB(0,0,0), COLORREF txtValColor = RGB(0,0,0));
	int AddItem(ArxRleAttributeListItem *&pItem);
	int InsertItem(int index, ArxRleAttributeListItem *&pItem);
	void SetItem(int index, ArxRleAttributeListItem *&pItem);
	ArxRleAttributeListItem* GetItem(int index) const;
	int GetItemCount() const;
	void DelItem(int index);
	void DelItems();

private:
	int m_itemCount;
	int m_nCItems;
	vector<ArxRleAttributeListItem*> m_vecItems;
};
#endif //ARXRLE_ATTRIBUTELISTITEM_H

