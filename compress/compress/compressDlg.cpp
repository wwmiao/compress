
// compressDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "compress.h"
#include "compressDlg.h"
#include "afxdialogex.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcompressDlg 对话框



CcompressDlg::CcompressDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPRESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcompressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcompressDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcompressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_un, &CcompressDlg::OnClickedButtonUn)
	ON_BN_CLICKED(IDCANCEL, &CcompressDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_cj, &CcompressDlg::OnClickedButtonCj)
	ON_BN_CLICKED(IDC_BUTTON_uncj, &CcompressDlg::OnClickedButtonUncj)
END_MESSAGE_MAP()


// CcompressDlg 消息处理程序

BOOL CcompressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcompressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcompressDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcompressDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//压缩文件
void CcompressDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CFileDialog fileDlg(TRUE);
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		string str;
		str = CW2A(path.GetString());
		Compress(str);
	}
}

//解压文件
void CcompressDlg::OnClickedButtonUn()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE);
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		string str;
		str = CW2A(path.GetString());
		Extract(str);
	}
}

//退出
void CcompressDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//压缩文件夹
void CcompressDlg::OnClickedButtonCj()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	TCHAR Buffer[MAX_PATH];//初始化入口参数bi开始
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if (pIDList!=NULL){
		SHGetPathFromIDList(pIDList, Buffer);//取得文件夹路径到Buffer里
		path = Buffer;//将路径保存在一个CString对象里
		//MessageBox(path);
		string str;
		str = CW2A(path.GetString());
		CompressFolder(str);

	}
	
}

//解压文件夹
void CcompressDlg::OnClickedButtonUncj()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE);
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		string str;
		str = CW2A(path.GetString());
		ExtractFolder(str);
	}
	
}
//压缩文件函数
void CcompressDlg::Compress(string path)
{
	string outfilename = ScanCharacter(path); //扫描源文件种字符的种类及个数，返回源文件的文件名并用string类型变量保存
	if (outfilename == "NULL") return;
	CreateHuffmanTree(); //构造哈夫曼树
	CreateHuffmanCode(); //生成哈夫曼编码
	//cout << "请输入被压缩后的文件的名字:";
	string filename;
	CString defaultDir = L"";
	CString defaultFilename = L"";
	CString filter = L"所有文件(*.*)|*.*||";
	CFileDialog fileDlg(FALSE,defaultDir,defaultFilename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,NULL);
	fileDlg.m_ofn.lpstrTitle = L"被压缩的文件保存对话框";
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		filename = CW2A(path.GetString());
	}
	//cin >> filename;
	/*filename = path ;
	int pos = filename.find_last_of(".");//找出最后一个.的字符串下标
	filename.erase(filename.begin()+pos, filename.end());//删去.之后（包括.）的字符串
	filename = filename + "c.txt";*/
	ofstream out(filename, ios::binary);
	//ofstream tc("text3.txt");
	if (!out)
	{
		//cout << "文件打开失败.." << endl;
		MessageBox(_T("文件打开失败"));
		return;
	}
	out.write((char*)&H_number, sizeof(int));//写入字符种类数
	//tc << H_number << endl;
	for (int i = 1; i <= H_number; ++i)//依次输入字符及字符的频度
	{
		out.write((char*)&(HuffmanTree[i].name), sizeof(char));
		//tc << HuffmanTree[i].name << endl;
		out.write((char*)&(HuffmanTree[i].weight), sizeof(int));
		//tc << HuffmanTree[i].weight << endl;
	}
	ifstream in(outfilename, ios::binary);//第二遍扫描源文件
	if (!in)
	{
		//cout << "打开源文件失败" << endl << endl;
		MessageBox(_T("打开源文件失败"));
		return;
	}
	unsigned char char_temp = '\0';//用8位的无符号变量作为读写字符的单元
	string unit;//存储哈夫曼编码，编码的个数大于等于八位就和char_temp进行|操作
	while (true)
	{
		char_temp = in.get();//在原文件中读取一个字符
		if (in.eof()) break;//判断是否到达文件的末尾
		for (int i = 1; i <= H_number; ++i)//在存取哈夫曼编码的数组中找到该字符对应的编码并将编码存储到unit中
		{
			if (Huffmancode[i].name == char_temp)
			{
				for (auto elem : Huffmancode[i].code)//向unit中输入编码
				{
					if (elem == 1)
						unit.push_back('1');
					else
						unit.push_back('0');
				}
				break;
			}
		}
		while (unit.length() >= 8)//如果unit中存储的哈夫曼编码的位数大于等于8，就将前八位通过位操作写入char_temp中
		{
			char_temp = '\0';
			for (int i = 0; i < 8; ++i)
			{
				char_temp = char_temp << 1;
				if (unit[i] == '1')
					char_temp = char_temp | 1;
			}
			auto p = unit.begin();
			unit.erase(p, p + 8);//清空unit中的前八位编码
			out.write((char*)&char_temp, sizeof(unsigned char));//将载有哈夫曼编码信息的字符写入到压缩文件中去
		}
	}
	if (unit.length() > 0)//处理最后不足八位的哈夫曼编码
	{
		char_temp = '\0';
		for (auto i = 0; i < unit.length(); ++i)
		{
			char_temp = char_temp << 1;
			if (unit[i] == '1')
				char_temp = char_temp | 1;
		}
		for (auto i = 0; i < (8 - unit.length()); ++i)//将编码移到到高位
			char_temp = char_temp << 1;
		out.write((char*)&char_temp, sizeof(unsigned char));
	}
	in.close();
	out.close();
	//压缩文件完成，将哈夫曼树的数组和存储哈夫曼编码的数组的内存释放掉，并将字符的种类数置为0
	HuffmanTree.resize(0);
	Huffmancode.resize(0);
	H_number = 0;
	MessageBox(_T("压缩完成"));
}

//生成哈夫曼编码的函数
void CcompressDlg::CreateHuffmanCode()
{
	Hcode_node elem;
	Huffmancode.push_back(elem);
	if (H_number == 1)
	{
		Huffmancode.push_back(elem);
		Huffmancode[1].name = HuffmanTree[1].name;
		Huffmancode[1].code.push_back(1);
	}
	for (int i = 1; i <= H_number; ++i)
	{
		Huffmancode.push_back(elem);
		Huffmancode[i].name = HuffmanTree[i].name;
		int temp_p = HuffmanTree[i].p;
		int temp_nodeindex = HuffmanTree[i].Hnodeindex;
		auto p = Huffmancode[i].code.end();
		while (temp_p != 0)
		{
			if (HuffmanTree[temp_p].lchild == temp_nodeindex)
			{
				p = Huffmancode[i].code.insert(p, 0);
			}
			else
			{
				p = Huffmancode[i].code.insert(p, 1);
			}
			temp_nodeindex = HuffmanTree[temp_p].Hnodeindex;
			temp_p = HuffmanTree[temp_p].p;
		}
	}
}

//构造哈夫曼树的函数
void CcompressDlg::CreateHuffmanTree()
{
	if (H_number == 1)
	{
		HuffmanTree[1].lchild = HuffmanTree[1].rchild = 1;
	}
	int mark = H_number + 1;
	int x = 0, y = 0;
	int min = 999999999, secmin = 0;
	while (mark < 2 * H_number)
	{
		for (int j = 1; j < mark; ++j)
		{
			if (HuffmanTree[j].p == 0 && HuffmanTree[j].weight < min)
			{
				y = x;
				secmin = min;
				min = HuffmanTree[j].weight;
				x = HuffmanTree[j].Hnodeindex;
			}
			else if (HuffmanTree[j].p == 0 && HuffmanTree[j].weight < secmin)
			{
				secmin = HuffmanTree[j].weight;
				y = HuffmanTree[j].Hnodeindex;
			}
			else;
		}
		HuffmanTree[mark].weight = HuffmanTree[x].weight + HuffmanTree[y].weight;
		HuffmanTree[mark].lchild = x;
		HuffmanTree[mark].rchild = y;
		HuffmanTree[x].p = mark;
		HuffmanTree[y].p = mark;
		mark++;
		x = y = 0;
		min = 99999999999, secmin = 0;
	}
	HuffmanTree[2 * H_number - 1].p = 0;
}

//扫描原文件中字符的种类及频度的函数
string CcompressDlg::ScanCharacter(string filename)
{
	ifstream in(filename, ios::binary);//以二进制的格式打开源文件
	if (!in)                          //检查指定的源文件是否存在          
	{
		//cout << "没有发现该文件.." << endl << endl;
		MessageBox(_T("没有发现该文件"));
		return "NULL";
	}
	unsigned char temp = '\0';  //用一个8位的无符号变量来依次读取源文件的信息
	HTnode *temparry = new HTnode[256];  //创建一个临时数组，用于统计字符的种类及频度
	while (true)           //判断是否到达文件的末尾
	{
		temp = in.get();
		if (in.eof())break;
		temparry[temp].name = temp;
		temparry[temp].weight++;
	}
	in.close();  //关闭in与源文件的关联
	HTnode elem;
	HuffmanTree.push_back(elem);//使得哈夫曼有效的存储是从HuffmanTree[1]开始
	H_number = 0;
	for (int i = 0; i < 256; i++)//选择出频度大于0的字符存储到哈夫曼数组中
	{
		if (temparry[i].weight != 0)
		{
			H_number++;//统计字符的种类数
			HuffmanTree.push_back(elem);
			*(HuffmanTree.end() - 1) = temparry[i];
		}
	}
	if (HuffmanTree.size() == 1)
	{
		//cout << "您输入的文本为空文本.." << endl << endl;
		MessageBox(_T("您输入的文本为空文本"));
		return "NULL";
	}
	delete[]temparry;//统计完毕以后释放临时数组的内存
	for (int i = 1; i <= (H_number - 1); i++)//为叶节点的双亲节点开辟内存
	{
		HuffmanTree.push_back(elem);
	}
	for (int i = 0; i < 2 * H_number; i++)//为哈夫曼数组的所有元素建立索引
	{
		HuffmanTree[i].Hnodeindex = i;
	}
	return filename;
}
void CcompressDlg::Extract(string path)
{
	ifstream in(path, ios::binary);
	if (!in)
	{
		//cout << "文件打开失败.." << endl;
		MessageBox(_T("文件打开失败"));
		return;
	}
	in.read((char*)&H_number, sizeof(int));//读取字符种类数
	HTnode elem;
	HuffmanTree.push_back(elem);
	for (int i = 1; i <= H_number; ++i)//读取字符的种类及频度
	{
		HuffmanTree.push_back(elem);
		in.read((char*)&(HuffmanTree[i].name), sizeof(char));
		in.read((char*)&(HuffmanTree[i].weight), sizeof(int));
	}
	for (int i = 1; i <= H_number - 1; ++i)//建立完整的哈夫曼数组
		HuffmanTree.push_back(elem);
	for (int i = 0; i < 2 * H_number; i++)//为哈夫曼数组元素建立索引
	{
		HuffmanTree[i].Hnodeindex = i;
	}
	CreateHuffmanTree();//生成哈夫曼树
	unsigned  char temp_char = '\0';//用来读取哈夫曼编码的单位
	unsigned long long length = 0;
	for (int i = 1; i <= H_number; ++i)//计算原文件的字符的个数
		length = length + HuffmanTree[i].weight;
	int top = HuffmanTree[2 * H_number - 1].Hnodeindex;//top存储的是结点的索引，初始化时根节点的索引
	//cout << "请输入解压以后的文件的名字:";
	string extractedname;
	//cin >> extractedname;
	CString defaultDir = L"";
	CString defaultFilename = L"";
	CString filter = L"所有文件(*.*)|*.*||";
	CFileDialog fileDlg(FALSE, defaultDir, defaultFilename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	fileDlg.m_ofn.lpstrTitle = L"解压的文件保存对话框";
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		extractedname = CW2A(path.GetString());
	}
	/*extractedname = path;
	int pos = extractedname.find_last_of(".");//找出最后一个.的字符串下标
	extractedname.erase(extractedname.begin() + pos - 1, extractedname.end());//删去.之后的字符串
	extractedname = extractedname + "un.docx";*/
	ofstream out(extractedname, ios::binary);
	if (!out)
	{
		//cout << "该文件打开失败.." << endl << endl;
		MessageBox(_T("该文件打开失败"));
		return;
	}
	while (length)
	{
		temp_char = in.get();//
		for (int i = 0; i < 8; ++i)
		{
			if (temp_char & 128)//如果最高位为1
				top = HuffmanTree[top].rchild;//top存储结点的右孩子的索引
			else
				top = HuffmanTree[top].lchild;//如果最高位为0，top存储结点的左孩子的索引
			if (top <= H_number)//如果从根节点到达叶节点
			{
				out << HuffmanTree[top].name;//输出字符
				length--;//更新原文件中未输出的字符的个数
				if (length == 0)break;//如果原文件中未输出的个数为0，表明原文件的字符已经全部输出，循环不需要再继续
				top = HuffmanTree[2 * H_number - 1].Hnodeindex;//否则top复位为根节点的索引
			}
			temp_char = temp_char << 1;//如果没到达叶节点，那么temp_char左移一位，继续循环
		}
	}
	in.close();
	out.close();
	//解压文件完成，将哈夫曼树的数组和存储哈夫曼编码的数组的内存释放掉，并将字符的种类数置为0
	HuffmanTree.resize(0);
	Huffmancode.resize(0);
	H_number = 0;
	MessageBox(_T("解压完成"));
}
void CcompressDlg::CompressFolder(string path)
{
	//filelist.push_back(path);//保存最初文件夹路径名称
	//filelong.push_back(0);//将文件夹文件大小设为0
	string outfilename = ScanCharacterFolder(path);//扫描源文件夹中字符的种类及个数，返回源文件的文件名并用string类型变量保存
	if (outfilename == "NULL") return;
	CreateHuffmanTree(); //构造哈夫曼树
	CreateHuffmanCode(); //生成哈夫曼编码
	//cout << "请输入被压缩后的文件的名字:";
	string filename;
	CString defaultDir = L"";
	CString defaultFilename = L"";
	CString filter = L"所有文件(*.*)|*.*||";
	CFileDialog fileDlg(FALSE, defaultDir, defaultFilename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	fileDlg.m_ofn.lpstrTitle = L"被压缩的文件保存对话框";
	if (IDOK == fileDlg.DoModal()) {
		CString path = fileDlg.GetPathName();
		filename = CW2A(path.GetString());
	}
	ofstream out(filename, ios::binary);
	if (!out)
	{
		//cout << "文件打开失败.." << endl;
		MessageBox(_T("文件打开失败"));
		return;
	}
	out.write((char*)&H_number, sizeof(int));//写入字符种类数
	for (int i = 1; i <= H_number; ++i)//依次输入字符及字符的频度
	{
		out.write((char*)&(HuffmanTree[i].name), sizeof(char));
		out.write((char*)&(HuffmanTree[i].weight), sizeof(int));
	}
	//通过之前存储的数组第二次遍历文件夹
	//vector<string>::iterator i;
	for (int i = 0; i < filelist.size(); i++) {
		string temp = filelist[i];//取文件路径出来判断和填入压缩文件
		CString tempfilep;
		tempfilep = CString(temp.c_str());
		CFileFind ff;
		BOOL bworking = ff.FindFile(tempfilep);
		while (bworking) {
			bworking = ff.FindNextFile();
			if (ff.IsDots())
				continue;
			//如果是目录
			if (ff.IsDirectory()) {
				//这是目录
				CString name = ff.GetFileName();//文件夹名称
				string str;
				str = CW2A(name.GetString());
				int size = str.size();
				out.write((char*)&(size), sizeof(int));
				out.write((char*)(str.c_str()), str.size());
			}
			else {
				//这是文件
				//MessageBox(_T("这是文件"));
				CString name = ff.GetFileName();//文件名称
				string str;
				str = CW2A(name.GetString());
				int size = str.size();
				out.write((char*)&(size), sizeof(int));
				out.write((char*)(str.c_str()), str.size());
				out.write((char*)&(filelong[i]), sizeof(unsigned long long));//一个文件内字符的个数
				ifstream in(temp, ios::binary);//以二进制的格式打开源文件,第二遍扫描源文件
				if (!in)                          //检查指定的源文件是否存在          
				{
					//cout << "没有发现该文件.." << endl << endl;
					MessageBox(_T("打开源文件失败"));
					//return "NULL";
				}
				unsigned char char_temp = '\0';//用8位的无符号变量作为读写字符的单元
				string unit;//存储哈夫曼编码，编码的个数大于等于八位就和char_temp进行|操作
				while (true)
				{
					char_temp = in.get();//在原文件中读取一个字符
					if (in.eof()) break;//判断是否到达文件的末尾
					for (int i = 1; i <= H_number; ++i)//在存取哈夫曼编码的数组中找到该字符对应的编码并将编码存储到unit中
					{
						if (Huffmancode[i].name == char_temp)
						{
							for (auto elem : Huffmancode[i].code)//向unit中输入编码
							{
								if (elem == 1)
									unit.push_back('1');
								else
									unit.push_back('0');
							}
							break;
						}
					}
					while (unit.length() >= 8)//如果unit中存储的哈夫曼编码的位数大于等于8，就将前八位通过位操作写入char_temp中
					{
						char_temp = '\0';
						for (int i = 0; i < 8; ++i)
						{
							char_temp = char_temp << 1;
							if (unit[i] == '1')
								char_temp = char_temp | 1;
						}
						auto p = unit.begin();
						unit.erase(p, p + 8);//清空unit中的前八位编码
						out.write((char*)&char_temp, sizeof(unsigned char));//将载有哈夫曼编码信息的字符写入到压缩文件中去
					}
				}
				if (unit.length() > 0)//处理最后不足八位的哈夫曼编码
				{
					char_temp = '\0';
					for (auto i = 0; i < unit.length(); ++i)
					{
						char_temp = char_temp << 1;
						if (unit[i] == '1')
							char_temp = char_temp | 1;
					}
					for (auto i = 0; i < (8 - unit.length()); ++i)//将编码移到到高位
						char_temp = char_temp << 1;
					out.write((char*)&char_temp, sizeof(unsigned char));
				}
				in.close();
			}
		}
		ff.Close();
	}
	out.close();
	//压缩文件完成，将哈夫曼树的数组和存储哈夫曼编码的数组的内存释放掉，并将字符的种类数置为0
	HuffmanTree.resize(0);
	Huffmancode.resize(0);
	filelist.resize(0);
	filelong.resize(0);
	H_number = 0;
	MessageBox(_T("压缩完成"));
}
string CcompressDlg::ScanCharacterFolder(string filename)
{
	CFileFind ff;
	HTnode *temparry = new HTnode[256];  //创建一个临时数组，用于统计所有文件的字符的种类及频度
	CString filepath;
	filepath = CString(filename.c_str());
	filepath += "\\*.*";
	BOOL bworking = ff.FindFile(filepath);
	while (bworking) {
		bworking = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		//如果是目录
		if (ff.IsDirectory()) {
			//这是目录
			CString path = ff.GetFilePath();
			CString jname = ff.GetFileName();
			string pstr,nstr;
			pstr = CW2A(path.GetString());
			nstr = CW2A(jname.GetString());
			filelist.push_back(pstr);//保存文件夹路径
			filelong.push_back(0);//将文件夹文件大小设为0
			ScanCharacterFolder(pstr);
			//MessageBox(filepath);

		}
		else {
			//这是文件
			//cout << "请输入要压缩的文件的文件名:";
			CString n = ff.GetFilePath();//文件路径
			CString name = ff.GetFileName();//文件名称
			string str;
			str = CW2A(n.GetString());
			filelist.push_back(str);//保存文件路径
	//string filename;
	//cin >> filename;
			ifstream in(str, ios::binary);//以二进制的格式打开源文件
			if (!in)                          //检查指定的源文件是否存在          
			{
				//cout << "没有发现该文件.." << endl << endl;
				MessageBox(_T("没有发现该文件"));
				return "NULL";
			}
			unsigned char temp = '\0';  //用一个8位的无符号变量来依次读取源文件的信息
			unsigned long long length = 0;//记录文件的字符的总个数
			//HTnode *temparry = new HTnode[256];  //创建一个临时数组，用于统计字符的种类及频度
			while (true)           //判断是否到达文件的末尾
			{
				temp = in.get();
				if (in.eof())break;
				temparry[temp].name = temp;
				temparry[temp].weight++;
				length++;
			}
			filelong.push_back(length);//保存文件的字符个数大小
			in.close();  //关闭in与源文件的关联
		}
	}
	ff.Close();
	HTnode elem;
	HuffmanTree.push_back(elem);//使得哈夫曼有效的存储是从HuffmanTree[1]开始
	H_number = 0;
	for (int i = 0; i < 256; i++)//选择出频度大于0的字符存储到哈夫曼数组中
	{
		if (temparry[i].weight != 0)
		{
			H_number++;//统计字符的种类数
			HuffmanTree.push_back(elem);
			*(HuffmanTree.end() - 1) = temparry[i];
		}
	}
	if (HuffmanTree.size() == 1)
	{
		//cout << "您输入的文本为空文本.." << endl << endl;
		MessageBox(_T("您输入的文本为空文本"));
		return "NULL";
	}
	delete[]temparry;//统计完毕以后释放临时数组的内存
	for (int i = 1; i <= (H_number - 1); i++)//为叶节点的双亲节点开辟内存
	{
		HuffmanTree.push_back(elem);
	}
	for (int i = 0; i < 2 * H_number; i++)//为哈夫曼数组的所有元素建立索引
	{
		HuffmanTree[i].Hnodeindex = i;
	}
	return filename;
}
void CcompressDlg::ExtractFolder(string path)
{
	ifstream in(path, ios::binary);
	if (!in)
	{
		//cout << "文件打开失败.." << endl;
		MessageBox(_T("文件打开失败"));
		return;
	}
	in.read((char*)&H_number, sizeof(int));//读取字符种类数
	HTnode elem;
	HuffmanTree.push_back(elem);
	for (int i = 1; i <= H_number; ++i)//读取字符的种类及频度
	{
		HuffmanTree.push_back(elem);
		in.read((char*)&(HuffmanTree[i].name), sizeof(char));
		in.read((char*)&(HuffmanTree[i].weight), sizeof(int));
	}
	for (int i = 1; i <= H_number - 1; ++i)//建立完整的哈夫曼数组
		HuffmanTree.push_back(elem);
	for (int i = 0; i < 2 * H_number; i++)//为哈夫曼数组元素建立索引
	{
		HuffmanTree[i].Hnodeindex = i;
	}
	CreateHuffmanTree();//生成哈夫曼树

	unsigned  char temp_char = '\0';//用来读取哈夫曼编码的单位
	int top = HuffmanTree[2 * H_number - 1].Hnodeindex;//top存储的是结点的索引，初始化时根节点的索引

	//选择解压文件夹的位置
	CString Epath;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	TCHAR Buffer[MAX_PATH];//初始化入口参数bi开始
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if (pIDList != NULL) {
		SHGetPathFromIDList(pIDList, Buffer);//取得文件夹路径到Buffer里
		Epath = Buffer;//将路径保存在一个CString对象里
		//MessageBox(path);
		//string str;
		//str = CW2A(Epath.GetString());
	}

	string filename;
	filename = CW2A(Epath.GetString());
	string folderpath = filename + "\\unFolder";//解压文件夹路径
	CString Cfolderpath;
	Cfolderpath = CString(folderpath.c_str());
	bool flag = CreateDirectory(Cfolderpath, NULL);//创建文件夹
	string subpath;
	subpath = folderpath + "\\";//子文件路径


	while (true) {
		//if (in.eof()) break;
		int size;//取文件名长度
		string name;//取文件名
		unsigned long long flong;//取文件长度
		in.read((char*)&size, sizeof(int));//取文件名长度
		if (in.eof()) break;
		//in.read((char*)(name.c_str()), 6);//取文件名
		for (int i = 0; i < size; i++) {
			char c;
			in.get(c);
			name = name + c;
		}
		CString output;
		output.Format(_T("size=%d"), size);
		MessageBox(output);
		CString output1;
		output1 = CString(name.c_str());
		MessageBox(output1);
		in.read((char*)&flong, sizeof(unsigned long long));//取文件长度

		//filename = path;
		//int pos = filename.find_last_of("/");//找出最后一个/的字符串下标
		//filename.erase(filename.begin() + pos+1, filename.end());//删去/之后（不包括/）的字符串
		//filename = filename + "c.txt";

		string subname;
		subname = subpath + name;//文件路径
		CString Csubname;
		Csubname = CString(subname.c_str());
		//MessageBox(Csubname);

		ofstream out(subname, ios::binary);
		if (!out)
		{
			//cout << "该文件打开失败.." << endl << endl;
			MessageBox(_T("该文件打开失败"));
			return;
		}
		while (flong)
		{
			temp_char = in.get();//
			for (int i = 0; i < 8; ++i)
			{
				if (temp_char & 128)//如果最高位为1
					top = HuffmanTree[top].rchild;//top存储结点的右孩子的索引
				else
					top = HuffmanTree[top].lchild;//如果最高位为0，top存储结点的左孩子的索引
				if (top <= H_number)//如果从根节点到达叶节点
				{
					out << HuffmanTree[top].name;//输出字符
					flong--;//更新原文件中未输出的字符的个数
					if (flong == 0)break;//如果原文件中未输出的个数为0，表明原文件的字符已经全部输出，循环不需要再继续
					top = HuffmanTree[2 * H_number - 1].Hnodeindex;//否则top复位为根节点的索引
				}
				temp_char = temp_char << 1;//如果没到达叶节点，那么temp_char左移一位，继续循环
			}
		}
		out.close();
		top = HuffmanTree[2 * H_number - 1].Hnodeindex;//top复位为根节点的索引*/
	}

	in.close();
	//out.close();
	//解压文件完成，将哈夫曼树的数组和存储哈夫曼编码的数组的内存释放掉，并将字符的种类数置为0
	HuffmanTree.resize(0);
	Huffmancode.resize(0);
	H_number = 0;
	MessageBox(_T("解压完成"));
}