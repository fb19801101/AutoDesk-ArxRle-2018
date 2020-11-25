// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// =  oooo   oooo  
// = oooooo oooooo  
// = oo  oo oo  oo  
// = oo  oo oo  oo  
// = oooooo oooooo  
// =  oooo   oooo    Copyright ( c ) The Old Ones 1998
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// General information section.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// $Author::                                                               $ User who last changed the file
// $Date::                                                                 $ Date and time of last check in
// $Revision::                                                             $ Visual SourceSafe version number
// $Workfile::                                                             $ Filename
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// History section.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// $History::                                                              $
// End =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- 

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @doc
// @module OOExToolBar.hpp | 
//         This module include an improved tool bar.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Definition to avoid multiple include.
// ------------------------------------------------------------------------
#ifndef ARXRLE_COOLBAR_H
#define ARXRLE_COOLBAR_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Include file section.
// ------------------------------------------------------------------------
// Extended bitmap class.
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef TB_SETEXTENDEDSTYLE
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Class declaration.
// ------------------------------------------------------------------------
#define NB_POSSIBLE_MODE 6
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class: (FUNCTIONAL)
//       This class manage an extended toolbar.
// @base public | CToolBar
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class ArxRleCoolBar : public CToolBar
{
    // --------------------------------------------------------------------
    // @group Macro definition.
    // --------------------------------------------------------------------
	DECLARE_DYNAMIC( ArxRleCoolBar )
    
    // --------------------------------------------------------------------
    // @group Structure definition.
    // --------------------------------------------------------------------
    private:
    public:
        enum ImageMode_ { SmallHot, SmallStandard, SmallDisable,
                          LargeHot, LargeStandard, LargeDisable };
    protected:

    // --------------------------------------------------------------------
    // @group Data definition.
    // --------------------------------------------------------------------
    private:
        // @Access Other usefull needed flag.
        bool m_bOldFloating;                                                // @CMember To patch the drawing when vertical.<nl>

    public:
    protected:
        // @Access ToolBar attribute.
        UINT m_nShowIconMode;                                               // @CMember Small or large icon.
        bool m_bShowIconText;                                               // @CMember To enable or disable the icon text.<nl>

        // @Access Size data.
        int m_nDropButtonSize;                                              // @CMember The drop button width.
        int m_nTextHeight;                                                  // @CMember The text height.
        int m_nTextWidth;                                                   // @CMember The text width.
        CSize m_SmallIconSize;                                              // @CMember The size of the icon in small mode.
        CSize m_LargeIconSize;                                              // @CMember The size of the icon in large mode.<nl>

        // @Access The image list.
        CImageList m_ImageList[ NB_POSSIBLE_MODE ];                         // @CMember The list of image.

    // --------------------------------------------------------------------
    // @group Implementation Method definition.
    // --------------------------------------------------------------------
    private:
        // @Access Usefull private method.
        // @CMember Method to calculate the current size of the button.
        CSize CalcButtonSize();

    public:
        // @Access Class Initialization method.
        ArxRleCoolBar();                                               // @CMember Constructor.
        ~ArxRleCoolBar();                                              // @CMember Destructor.<nl>

    	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
	    void GetButton(int nIndex, TBBUTTON* pButton) const;
	    void SetButton(int nIndex, TBBUTTON* pButton);
    	
    	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
	    CSize CalcSize(TBBUTTON* pData, int nCount);
    	CSize CalcLayout(DWORD nMode, int nLength = -1);

    protected:
        // @Access Usefull protected method.
    	void DrawGripper( CDC& dc ) const;                                  // @CMember To draw the gripper.<nl>

        // @Access Protected method to set the image information.
        void SetDisableImageList( CImageList* pList );                      // @CMember To set the disable image list.
        void SetHotImageList( CImageList* pList );                          // @CMember To set the hoover image list.
    	void SetStandardImageList( CImageList* pList );                     // @CMember To set the normal image list.<nl>

        // @Access Image list initialization method.
        virtual void AssignImageList();                               // @CMember Set the correct image list in the control.
        
    // --------------------------------------------------------------------
    // @group Functionnal Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Loading information.
        void ResizeToolBar();                                         // @CMember To set the size of the toolbar.
        virtual BOOL LoadToolBar( UINT _ResourceId );                       // @CMember To load the toolbar information.
    
        // @Access To set the image information.
        void SetImageList( ImageMode_ _ImageMode, CImageList& _rList );     // @CMember To set the small disable image list.

        // @Access Image list initialization method.
        virtual void InitImageList();                                 // @CMember Set the correct image list in the control.

        // @Access Mode related method.
        void SetIconMode( UINT _nShowIconMode );                            // @CMember To view large or small icon.
        UINT GetIconMode() const;                                     // @CMember To get the large or small icon mode.
        void SetTextMode( bool _bShowIconText );                            // @CMember To set the text on or off.
        bool GetTextMode() const;                                     // @CMember To get the text on or off.<nl>

        // @Access Usefull button method.
        void SetButtonDropDown( int nID );                                  // @CMember To set a drop arrow for a given button.<nl>

    protected:
        
    // --------------------------------------------------------------------
    // @group MFC Definition.
    // --------------------------------------------------------------------
    // Overrides
    	// ClassWizard generated virtual function overrides
    	//{{AFX_VIRTUAL( ArxRleCoolBar )
    	public:
    	    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
        	virtual CSize GetButtonSize(TBBUTTON* pData, int iButton);
	        virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	    protected:
        	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );	
    	//}}AFX_VIRTUAL

    // --------------------------------------------------------------------
    // @group Generated message map functions.
    // --------------------------------------------------------------------
    protected:
	    //{{AFX_MSG( ArxRleCoolBar )
    	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
    	afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp );
    	afx_msg void OnNcPaint();
    	afx_msg void OnSysColorChange();
        afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
    	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()
};
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class: (FUNCTIONAL)
//       This class manage an extended command ui.
// @base public | CCmdUI
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class ArxRleCoolCmdUI : public CCmdUI // class private to this file !
{
    public: // re-implementations only
	    virtual void Enable( BOOL bOn );
    	virtual void SetCheck( int nCheck );
};

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Class declaration.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class: (FUNCTIONAL)
//       This class manage an extended toolbar based on bitmap.
// @base public | COOExToolbar
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class ArxRleCoolBmpBar : public ArxRleCoolBar
{
    // --------------------------------------------------------------------
    // @group Macro definition.
    // --------------------------------------------------------------------
	DECLARE_DYNAMIC( ArxRleCoolBmpBar )
    
    // --------------------------------------------------------------------
    // @group Structure definition.
    // --------------------------------------------------------------------
    private:
    public:
        class CExBitmap
        {
            public:
                UINT m_nResourceId;
                COLORREF m_clrTransparent;
        };

    protected:

    // --------------------------------------------------------------------
    // @group Data definition.
    // --------------------------------------------------------------------
    private:
        // @Access The bitmap image.
        CExBitmap m_256Image[ NB_POSSIBLE_MODE ];                           // @CMember The 256 color bitmap id list.
        CExBitmap m_16Image[ NB_POSSIBLE_MODE ];                            // @CMember The 16 color bitmap id list.

    public:
    protected:

    // --------------------------------------------------------------------
    // @group Implementation Method definition.
    // --------------------------------------------------------------------
    private:
        // @Access Usefull private method.
        // @CMember Generic method to build an image list.
        void BuildImageList( CImageList& _rImageList, const CExBitmap& _rBitmap );

    public:
        // @Access Class Initialization method.
        ArxRleCoolBmpBar();                                               // @CMember Constructor.
        ~ArxRleCoolBmpBar();                                              // @CMember Destructor.<nl>

    protected:

    // --------------------------------------------------------------------
    // @group Functionnal Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Bitmap adding method.
        // @CMember To set the small disable bitmap.
        void SetBitmap( UINT _nBmpId, ImageMode_ _ImageMode, COLORREF _clrBk, bool _b256 = true );     
        
        // @Access Image list initialization method.
        virtual void InitImageList();                                 // @CMember Set the correct image list in the control.
        
    protected:
        
    // --------------------------------------------------------------------
    // @group MFC Definition.
    // --------------------------------------------------------------------
    // Overrides
    	// ClassWizard generated virtual function overrides
    	//{{AFX_VIRTUAL( ArxRleCoolBmpBar )
    	public:
	    protected:
    	//}}AFX_VIRTUAL

    // --------------------------------------------------------------------
    // @group Generated message map functions.
    // --------------------------------------------------------------------
    protected:
	    //{{AFX_MSG( ArxRleCoolBmpBar )
    	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()
};
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Start =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Class declaration.
// ------------------------------------------------------------------------
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// @class: (FUNCTIONAL)
//       This class manage an extended toolbar based on bitmap.
// @base public | COOExToolbar
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class ArxRleCoolIconBar : public ArxRleCoolBar
{
    // --------------------------------------------------------------------
    // @group Macro definition.
    // --------------------------------------------------------------------
	DECLARE_DYNAMIC( ArxRleCoolIconBar )
    
    // --------------------------------------------------------------------
    // @group Structure definition.
    // --------------------------------------------------------------------
    private:
    public:
    protected:

    // --------------------------------------------------------------------
    // @group Data definition.
    // --------------------------------------------------------------------
    private:
    public:
    protected:

    // --------------------------------------------------------------------
    // @group Implementation Method definition.
    // --------------------------------------------------------------------
    private:
        // @Access Private usefull method.
        HICON ConvertIconToGrayScale( HICON _hIcon, CSize _sizeImage );     // @CMember To convert the given icon into a gray scale icon.

    public:
        // @Access Class Initialization method.
        ArxRleCoolIconBar();                                             // @CMember Constructor.
        ~ArxRleCoolIconBar();                                            // @CMember Destructor.<nl>

    protected:

    // --------------------------------------------------------------------
    // @group Functionnal Method definition.
    // --------------------------------------------------------------------
    private:
    public:
        // @Access Icon adding method.
        // @CMember To add icon.
        void SetIcon( UINT _nStandardIcon, UINT _nDisableIcon = 0, UINT _nHotIcon = 0 );
        
    protected:
        
    // --------------------------------------------------------------------
    // @group MFC Definition.
    // --------------------------------------------------------------------
    // Overrides
    	// ClassWizard generated virtual function overrides
    	//{{AFX_VIRTUAL( ArxRleCoolIconBar )
    	public:
	    protected:
    	//}}AFX_VIRTUAL

    // --------------------------------------------------------------------
    // @group Generated message map functions.
    // --------------------------------------------------------------------
    protected:
	    //{{AFX_MSG( ArxRleCoolIconBar )
    	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()
};
// @end =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#endif // #define _OOExToolBar_H_
