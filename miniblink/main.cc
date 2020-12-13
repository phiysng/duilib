#include <iostream>
#include <windows.h>

#include <UIlib.h>
// #include <Control/UIButton.h>
#include <Utils/WinImplBase.h>

using namespace DuiLib;

class WizardWindow : public WindowImplBase
{
public:

	WizardWindow() = default;

	~WizardWindow(void) {}


	UILIB_RESOURCETYPE GetResourceType() const {
		return UILIB_FILE;
	}

	CDuiString GetSkinFile() override {
		return L"wizardWnd.xml";
	}

	CDuiString GetSkinFolder() override {
		return L"";
	}

	LPCTSTR GetWindowClassName() const override {
		//static auto name = L("WizardWnd");
		return _T("WizardWndEx");
	}

	void OnFinalMessage(HWND hWnd) override {
		__super::OnFinalMessage(hWnd);

		delete this;
	}



};


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    

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