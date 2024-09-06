#include "UICore/UICore.h"

#include <Windows.h>

#include <iostream>
#include <string>

namespace UICore
{
    auto CreateDialogTemplate() -> DLGTEMPLATE
    {
        // Define the dialog template
        auto dlgTemplate = DLGTEMPLATE{};
        dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU;
        dlgTemplate.dwExtendedStyle = WS_EX_CONTROLPARENT;
        dlgTemplate.cdit = 2; // Number of controls in the dialog (Ok and Cancel buttons)
        dlgTemplate.x = 0;
        dlgTemplate.y = 0;
        dlgTemplate.cx = 200;
        dlgTemplate.cy = 200;

        // Add Ok button
        auto okButton = DLGITEMTEMPLATE{};
        okButton.style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
        okButton.dwExtendedStyle = 0;
        okButton.x = 70;
        okButton.y = 170;
        okButton.cx = 60;
        okButton.cy = 25;
        okButton.id = IDOK;
        dlgTemplate.addControl(okButton, L"BUTTON", L"OK");

        // Add Cancel button
        auto cancelButton = DLGITEMTEMPLATE{};
        cancelButton.style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
        cancelButton.dwExtendedStyle = 0;
        cancelButton.x = 135;
        cancelButton.y = 170;
        cancelButton.cx = 60;
        cancelButton.cy = 25;
        cancelButton.id = IDCANCEL;
        dlgTemplate.addControl(cancelButton, L"BUTTON", L"Cancel");

        return dlgTemplate;
    }

    INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    void ShowImageWindow(const std::filesystem::path imagePath)
    {
        // Convert the image path to a wide string
        auto imagePathWide = imagePath.wstring();

        auto dlgTemplate = CreateDialogTemplate();

        // Create the dialog box
        auto dialogHandle = CreateDialogIndirectParamW(nullptr, &dlgTemplate, nullptr, DialogProc, reinterpret_cast<LPARAM>(&imagePathWide));
        if (dialogHandle == nullptr)
        {
            // Dialog creation failed
            throw std::runtime_error("Failed to create dialog box");
        }

        // Show the dialog box
        ShowWindow(dialogHandle, SW_SHOW);

        // Message loop
        auto message = MSG();
        while (GetMessage(&message, nullptr, 0, 0))
        {
            if (!IsDialogMessage(dialogHandle, &message))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
    }

    INT_PTR CALLBACK DialogProc(HWND dialogHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_INITDIALOG:
        {
            // Get the image path from the LPARAM
            std::wstring* imagePathWide = reinterpret_cast<std::wstring*>(lParam);

            // Load the image
            auto hBitmap = (HBITMAP)LoadImageW(nullptr, imagePathWide->c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hBitmap == nullptr)
            {
                // Image loading failed
                EndDialog(dialogHandle, -1);
            }
            else
            {
                // Set the image as the dialog's background
                HWND hImage = GetDlgItem(dialogHandle, IDC_IMAGE);
                SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
            }

            return (INT_PTR)TRUE;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(dialogHandle, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }

        return (INT_PTR)FALSE;
    }
}
