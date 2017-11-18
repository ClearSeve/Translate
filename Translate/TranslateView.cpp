// TranslateView.cpp : 实现文件
//

#include "stdafx.h"
#include "Translate.h"
#include "TranslateView.h"
#include "TranslateDlg.h"
CEdit* g_pEdit;
// 需要翻译的字符串
CString CTranslateView::strText;
// 需要翻译字符串的语言
CString  CTranslateView::strPreLanguage;
// utf8 转 Unicode
CString UTF8ToUnicode(char* UTF8);
// 请求处理函数
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);


// CTranslateView

IMPLEMENT_DYNCREATE(CTranslateView, CFormView)
CTranslateView::CTranslateView() : CFormView(CTranslateView::IDD)
{

	// 显示的名称
	m_strTitle = _T("");
	// 需要翻译的语言
	m_strLanguage = _T("");
	// 是否可以输入内容
	m_bIsWrite = FALSE;

	// 需要翻译的字符串
	CTranslateView::strText = _T("");
	// 需要翻译字符串的语言
	CTranslateView::strPreLanguage = _T("");




}

CTranslateView::CTranslateView(CString Title, CString Language, BOOL IsWrite) : CFormView(CTranslateView::IDD)
{
	// 显示的名称
	m_strTitle = Title;
	// 需要翻译的语言
	m_strLanguage = Language;
	// 是否可以输入内容
	m_bIsWrite = IsWrite;

	// 需要翻译的字符串
	CTranslateView::strText = _T("");
	// 需要翻译字符串的语言
	CTranslateView::strPreLanguage = _T("");




}

CTranslateView::~CTranslateView()
{
}

void CTranslateView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTranslateView, CFormView)
END_MESSAGE_MAP()


// CTranslateView 诊断

#ifdef _DEBUG
void CTranslateView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTranslateView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTranslateView 消息处理程序

BOOL CTranslateView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CTranslateView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 设置标题
	GetDlgItem(IDC_TYPE)->SetWindowText(m_strTitle);
	// 将EDIT保存到全局变量中
	g_pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
	// 设置EDIT是否可以输入
	g_pEdit->SetReadOnly(!m_bIsWrite);
}
// 宽字节字符集转宽字节字符集(使用完内存后需要释放)
char* WToM(CString strWText)
{
	// 用于保存申请的地址
	char* strMText = NULL;
	// 获取转换后需要多少字节
	int len = WideCharToMultiByte(CP_ACP, 0, strWText, wcslen(strWText), NULL, 0, NULL, NULL);
	// 申请空间
	strMText = (char*)malloc(len + 1);
	// 清空内存
	memset(strMText, 0, len + 1);
	// 转换字符串
	len = WideCharToMultiByte(CP_ACP, 0, strWText, wcslen(strWText), strMText, len, NULL, NULL);
	// 设置字符串结尾
	strMText[len] = 0;
	return strMText;
}
size_t CTranslateView::g_f_wctou8(char * dest_str, const wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // 用于"位或"置标UTF-8编码0x80--->1000000
	wchar_t tmp_wchar = L'0'; // 用于宽字符位置析取和位移(右移位)
	unsigned char tmp_char = L'0';
	if (!src_wchar)//
		return (size_t)-1;
	for (;;) // 检测字节序列长度
	{
		if (src_wchar <= 0x7f){ // <=01111111
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同
			utf_one = 0x0;
			break;
		}
		if ((src_wchar > 0x7f) && (src_wchar <= 0x7ff)){ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](最多个位, 简写为*1)
			byte_one = 0x1f; // 00011111, 下类推(1位的数量递减)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ((src_wchar > 0x7ff) && (src_wchar <= 0xffff)){ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ((src_wchar > 0xffff) && (src_wchar <= 0x1fffff)){ //对UCS-4的支持..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ((src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff)){
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ((src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff)){
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; // 以上皆不满足则为非法序列
	}
	// 以下几行析取宽字节中的相应位, 并分组为UTF-8编码的各个字节
	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // 一个宽字符的多字节降序赋值
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///后位与byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// 在前面加----跟或
		tmp_wchar >>= 6;//右移位
	}
	//这个时候i=1
	//对UTF-8第一个字节位处理，
	//第一个字节的开头"1"的数目就是整个串中字节的数目
	tmp_char = (unsigned char)(tmp_wchar & byte_one);//根据上面附值得来，有效位个数
	dest_str[0] = (tmp_char | utf_one);//根据上面附值得来1的个数
	// 位值析取分组__End!
	return count_bytes;
}
int UniToUTF8(CString strUnicode, char *szUtf8)
{
	//MessageBox(strUnicode);
	int ilen = WideCharToMultiByte(CP_UTF8, 0, (LPCTSTR)strUnicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8Temp = new char[ilen + 1];
	memset(szUtf8Temp, 0, ilen + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPCTSTR)strUnicode, -1, szUtf8Temp, ilen, NULL, NULL);
	//size_t a = strlen(szUtf8Temp);
	sprintf(szUtf8, "%s", szUtf8Temp);// 
	delete[] szUtf8Temp;
	return ilen;
}


// 翻译并显示在EDIT中
void CTranslateView::Translate()
{

	// 需要翻译的文本
	char* pstrTextstrM = WToM(CTranslateView::strText);

	char pstrTextM[4096] = { 0 };

	UniToUTF8(CTranslateView::strText, pstrTextM);


	// 待翻译的文本语言
	char* pstrPreLanguageM = WToM(CTranslateView::strPreLanguage);
	// 需要翻译成什么语言
	char* pstrLanguageM = WToM(m_strLanguage);

	// 用户信息字符串
	char szInfo[4096] = { 0 }; // 待加密的信息
	// 临时加密字符串
	unsigned  char  md[16] = { 0 };
	// 加密后的字符串
	char szkey[36] = { 0 }, tmp[3] = { 0 };
	int salt = rand() % 0xFFFF;
	// 构造加密
	sprintf(szInfo, "%s%s%d%s", "20160206000011344", pstrTextM, salt, "8I6r6BYVO4uH5GOnvR38");

	// 进行摘要

	md5_state_s md5data = { 0 };
	md5_init(&md5data);
	md5_append(&md5data, (md5_byte_t*)szInfo, strlen(szInfo));
	md5_finish(&md5data, md);
	//MD5((unsigned char*)szInfo, strlen (szInfo),md);
	// 进行加密转换
	for (int i = 0; i < 16; i++)
	{
		sprintf(tmp, "%2.2x", md[i]);
		strcat(szkey, tmp);
	}
	// 构造URL字符串
	CStringA strURL;
	strURL.Format("http://api.fanyi.baidu.com/api/trans/vip/translate?q=%s&from=%s&to=%s&appid=%s&salt=%d&sign=%s", pstrTextstrM, pstrPreLanguageM, pstrLanguageM, "20160206000011344", salt, szkey);
	// 追加到结尾
	// 构造字符串
	// 释放内存
	//free(pstrTextM);
	free(pstrPreLanguageM);
	free(pstrLanguageM);

	free(pstrTextstrM);

	HRESULT hRef = m_pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hRef))
	{
		AfxMessageBox(_T("信息交互接口创建失败!"));
		return;
	}

	hRef = m_pHttpReq->Open(_T("GET"), strURL.AllocSysString());
	if (FAILED(hRef))
		return;

	hRef = m_pHttpReq->Send();
	if (FAILED(hRef))
		return;

	// 拷贝字符串
	CString strRef = m_pHttpReq->ResponseText;

	
	USES_CONVERSION;
	char* pszRefData = W2A(strRef);

	write_data(pszRefData, 0, strlen(pszRefData),NULL);
}


// 请求处理函数
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{

	// 申请动态空间
	char* szBody = (char*)malloc(nmemb + 1);
	memset(szBody, 0, nmemb + 1);
	// 拷贝字符串
	strncpy(szBody, (char*)ptr, nmemb);
	// 给字符串结尾
	szBody[nmemb] = 0;

	// JSON解析出内容
	cJSON * pJson = cJSON_Parse(szBody);
	if (NULL == pJson)
	{
		// parse faild, return
		return 0;
	}
	// 获取一级信息
	cJSON * pSub = cJSON_GetObjectItem(pJson, "trans_result");
	if (NULL != pSub)
	{
		// 获取数组
		cJSON* pArray = cJSON_GetArrayItem(pSub, 0);
		if (NULL != pArray)
		{
			// 获取数组中的成员
			cJSON * pValue = cJSON_GetObjectItem(pArray, "dst");
			if (NULL != pValue)
			{
				CString str = UTF8ToUnicode(pValue->valuestring);
				// 添加到EDIT框中
				g_pEdit->SetWindowText(str);
			}
		}
	}

	// 释放内存Body
	free(szBody);
	return size;
}

// utf8 转 Unicode
CString UTF8ToUnicode(char* UTF8)
{

	DWORD dwUnicodeLen;        //转换后Unicode的长度
	TCHAR *pwText;            //保存Unicode的指针
	CString strUnicode;        //返回值
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//转为CString
	strUnicode.Format(_T("%s"), pwText);
	//清除内存
	delete[]pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}

