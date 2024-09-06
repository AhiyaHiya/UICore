#include "UICore/UICore.h"

#include "resource.h"

#include <Windows.h>

#include <iostream>
#include <string>

namespace UICore
{
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
                auto imageHandle = GetDlgItem(dialogHandle, IDC_IMAGE);
                SendMessage(imageHandle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
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

    void ShowImageWindow(const std::filesystem::path imagePath)
    {
        // Convert the image path to a wide string
        auto imagePathWide = imagePath.wstring();

        // Create the dialog box
        auto dialogHandle = CreateDialogParamA(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DialogProc, reinterpret_cast<LPARAM>(&imagePathWide));
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
}
