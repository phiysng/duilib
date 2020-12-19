#include <iostream>
#include <functional>
#include <Windows.h>

#include <UIlib.h>

#include <Utils/WinImplBase.h>

#include "wke.h"

using namespace DuiLib;
using namespace std;

// \note 2020/12/18 基本可用的基于miniblink的Webkit控件 不封装控件的消息

/// <summary>
/// MiniBlink控件名称
/// </summary>
const LPCTSTR kWebkitUI = L"WebkitUI";

/// <summary>
/// 关闭时的回调函数 返回false取消关闭操作
/// </summary>
/// <param name="webview">浏览器对象</param>
/// <param name="param">上下文数据</param>
/// <returns>false取消 true继续关闭此浏览器</returns>
bool onClose(wkeWebView webview, void* param)
{
	return true;
	//if (canContinue) {
	//	// return true to continue exit
	//	return true;
	//}
	//else {
	//	canContinue = true;
	//	return false;
	//}
}

/// <summary>
/// 返回前的回调函数 此时已经不可以取消
/// </summary>
/// <param name="webview"></param>
/// <param name="param"></param>
void onDestroy(wkeWebView webview, void* param)
{
	HWND hwnd = static_cast<HWND>(param);
	//cout << *s << endl;
	::PostMessage(hwnd, WM_CLOSE, 1010, 10);
}

/// <summary>
/// miniblink控件
/// </summary>
class WebkitUI : public CControlUI {
public:
	WebkitUI(HWND hwnd) :parentHWDN(hwnd) {}
	~WebkitUI() = default;

	void DoInit() override{
		window = wkeCreateWebWindow(WKE_WINDOW_TYPE_CONTROL, parentHWDN, 0, 0, 300, 300);
		hwnd = wkeGetHostHWND(window);
		wkeLoadURL(window, "https://cn.bing.com/");
		wkeOnWindowClosing(window, onClose, NULL);
		wkeOnWindowDestroy(window, onDestroy, parentHWDN);

		RECT rect{ 0 };
		::GetWindowRect(parentHWDN,&rect);


		//::SetWindowPos(hwnd,0, 0, 0, 300, 300,0);
		wkeShowWindow(window, TRUE);
		return;
	}

	void SetVisible(bool visible) {
		if (visible) {
			wkeShowWindow(window, TRUE);
		}
		else {
			wkeShowWindow(window, FALSE);
		}
	}

	void SetPos(RECT rc, bool bNeedInvalidate) {
		//RECT rect{ 0 };
		//::GetWindowRect(hwnd, &rect);

		::SetWindowPos(hwnd, 0, 0, 32, rc.right - rc.left, rc.bottom - rc.top, 0);

		wkeResize(window, rc.right - rc.left, rc.bottom - rc.top);


		//__super::SetPos(rc, bNeedInvalidate);
	}

	HWND parentHWDN;
	HWND hwnd;
	wkeWebView window;

};

class WizardWindow : public WindowImplBase
{
public:

	WizardWindow() = default;

	~WizardWindow(void) {}


	UILIB_RESOURCETYPE GetResourceType() const override {
		return UILIB_FILE;
	}

	CControlUI* WizardWindow::CreateControl(LPCTSTR pstrClass) override {
		/// trick impl , works only when we have only one control, fix later
		if (_tcsicmp(pstrClass, kWebkitUI) == 0)
			return	webkitUI  = new WebkitUI(GetHWND());

		return NULL;
	}

	CDuiString GetSkinFile() override {
		return L"wizardWnd.xml";
	}

	CDuiString GetSkinFolder() override {
		return L"";
	}

	LPCTSTR GetWindowClassName() const override {
		return _T("WizardWndBrowser");
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override {

		// WebkitUI 控件
		//webkitUI = (WebkitUI*)m_PaintManager.FindControl(_T("webkit"));

		return __super::OnCreate(uMsg, wParam, lParam, bHandled);
	}


	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override
	{
		if (wParam != 1010) {
			wkeDestroyWebWindow(webkitUI->window);
			bHandled = TRUE;
		}
		else {
			// begin to close
			bHandled = FALSE;
		}
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override
	{
		bHandled = FALSE;
		return 0;
	}

	//void SetPos(RECT rc, bool bNeedInvalidate) override  override{
	//	__super::SetPos()
	//}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override {

		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		RECT rect{ 0,0,width -5 , height + 25 };
		if (webkitUI) {
			webkitUI->SetPos(rect, false);
		}
		return __super::OnSize(uMsg, wParam, lParam, bHandled);
	}


	void OnFinalMessage(HWND hWnd) override {
		__super::OnFinalMessage(hWnd);
		
		::PostQuitMessage(0);

		delete this;
	}

	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)override {
	//	bHandled = FALSE;
	//	return 0;
	//}
	WebkitUI* webkitUI;
};


class PathRead0
{
public:
	PathRead0() = default;


	/*void Run()
	{
		std::bind
	}*/
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    

	wkeSetWkeDllPath(L"D:\\repos\\mb\\miniblink_x64.dll");

	wkeInitialize();

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\skin"));

	WizardWindow* pFrame = new WizardWindow();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("WizardWindowEx"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

    return 0;
}