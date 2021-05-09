
// compressDlg.h: 头文件
//

#pragma once
#include<vector>
#include"HTnode.h"
#include"Hcode_node.h"
#include<iostream>
#include<fstream>


// CcompressDlg 对话框
class CcompressDlg : public CDialogEx
{
// 构造
public:
	CcompressDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPRESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//压缩解压相关
	vector<HTnode> HuffmanTree;  //存储哈夫曼树的数组
	vector<Hcode_node>Huffmancode;  //存储哈夫曼编码的数组
	int H_number; //字符的种类数
	vector<string> filelist;//文件列表
	vector<unsigned long long> filelong;//文件对应大小
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedButtonUn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedButtonCj();
	afx_msg void OnClickedButtonUncj();
	//压缩解压相关函数
	void Compress(string path); //压缩文件的函数
	void Extract(string path);  //解压文件的函数
	string ScanCharacter(string filename);//扫描源文件中字符的种类及个数
	void CompressFolder(string path);//压缩文件夹的函数
	void ExtractFolder(string path);//解压文件夹的函数
	string ScanCharacterFolder(string filename);//扫描文件夹中字符种类及个数
	void CreateHuffmanTree();//建立哈夫曼树
	void CreateHuffmanCode();//生成哈夫曼编码
};
