#include <iostream>
#include <windows.h>

#include <UIlib.h>
// #include <Control/UIButton.h>
#include <Utils/WinImplBase.h>

using namespace DuiLib;

class WizardWindow : public CWindowWnd, public INotifyUI
{
public:
    LPCTSTR GetWindowClassName(void) const override{
        return L"MBControlWindow";
    }

    virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("btnHello"));
			{
				::MessageBox(NULL, _T("我是按钮"), _T("点击了按钮"), NULL);
			}
		}
    }

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		if (uMsg == WM_CREATE)
		{
			CControlUI* pWnd = new CButtonUI;
			pWnd->SetName(_T("btnHello"));//设置控件的名称，这个名称用于标识每一个控件，必须唯一，相当于MFC里面的控件ID
			pWnd->SetText(_T("Hello World"));//设置文字
			pWnd->SetBkColor(0xFF00FF00);//设置背景色
 
			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this);//添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
			return lRes;
		}
 
		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}
		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    
    CPaintManagerUI::SetInstance(hInstance);
 
	WizardWindow wizardWnd;
	wizardWnd.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	wizardWnd.ShowModal();

    return 0;
}