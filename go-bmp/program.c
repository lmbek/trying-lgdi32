#include <windows.h>
#include <wingdi.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// IF YOU WANT TO RUN THIS WITH:
// gcc -o program9.exe program.c -lgdi32 -luser32 -lgdiplus
// ./program9.exe
// then use: ../assets/creepysmiley.bmp
// AND THEN YOU SHOULD UNCOMMENT BELOW:
//int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    start(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
//    return 0;
//}

int start(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Load the PNG image
    HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, "assets/creepysmiley.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        MessageBoxA(NULL, "Failed to load the image.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Register the window class
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TransparentWindowClass";
    RegisterClassA(&wc);  // Use RegisterClassA

    // Create a transparent window
    HWND hwnd = CreateWindowExA(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        "TransparentWindowClass", "", WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    // Set the transparency color (white in this example) as the transparent color
    SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

    // Set the window size and position
    BITMAP bm;
    GetObject(hBitmap, sizeof(bm), &bm);
    SetWindowPos(hwnd, HWND_TOPMOST, (1920/2)-(bm.bmWidth/2), (1080/2)-(bm.bmHeight/2), bm.bmWidth, bm.bmHeight, SWP_SHOWWINDOW);

    // Display the image in the window
    HDC hdc = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
    ReleaseDC(hwnd, hdc);
    DeleteDC(hdcMem);

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CLOSE) {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}