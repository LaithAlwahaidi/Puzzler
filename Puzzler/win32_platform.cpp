#include <windows.h>
#include <windowsx.h>
#include "win32_platform.h"
#include "Draw.h"
#include "Utilities.h"
#include "platform_common.h"
#include "app.h"
#include <iostream>
#include <algorithm>

#define process_button(b, vk)               \
    case vk:                                \
    {                                       \
        input.buttons[b].is_down = is_down; \
        input.buttons[b].changed = changed; \
    }                                       \
    break;

//static bool running = true;

static Render_State render_state;
HDC hdc;
Draw renderer(&render_state);
SudokuApp sAPP(renderer);

Input input = {};

static HCURSOR hCursorArrow;
static HCURSOR hCursorHand;

void resize(RECT rect)
{
    render_state.width = rect.right - rect.left;
    render_state.height = rect.bottom - rect.top;

    int buffer_size = render_state.width * render_state.height * sizeof(u32);

    // pixel memory
    if (render_state.memory)
        VirtualFree(render_state.memory, 0, MEM_RELEASE);
    render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    int data_size = render_state.width * render_state.height * sizeof(object_types);

    // pixel object data memory (buttons, cells, etc)
    if (render_state.data)
        VirtualFree(render_state.data, 0, MEM_RELEASE);
    render_state.data = (object_types*)VirtualAlloc(0, data_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
    render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
    render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
    render_state.bitmap_info.bmiHeader.biPlanes = 1;
    render_state.bitmap_info.bmiHeader.biBitCount = 32;
    render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
}

object_types* get_object_at_pos(int x, int y)
{
    return (object_types*)(render_state.data) + x + y * render_state.width;
}


LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (uMsg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
    {
        result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    break;
    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = 800;
        lpMMI->ptMinTrackSize.y = 800;
    }
    break;
    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        resize(rect);
    }
    break;
    //case WM_SIZING:
    //{
    //    RECT rect = *(RECT*)lParam;
    //    resize(rect);
    //    // redraw when resizing
    //    sAPP.simulate(&input);
    //    StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    //}
    //break;
    case WM_SETCURSOR:
    {
        WORD l = LOWORD(lParam);
        if (l == 0x001)
        {
            break;
        }
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    break;
    default:
    {
        result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    }
    return result;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // Create Window Class
    WNDCLASSW window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = L"Sudoku Window Class";
    window_class.lpfnWndProc = window_callback;

    hCursorArrow = LoadCursor(NULL, IDC_ARROW);
    hCursorHand = LoadCursor(NULL, IDC_HAND);

    window_class.hCursor = hCursorArrow;

    // Register Class
    RegisterClassW(&window_class);

    // Create Window
    HWND window = CreateWindowExW(0, window_class.lpszClassName, L"Sudoku Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        (HWND)NULL, (HMENU)NULL, hInstance, 0);

    hdc = GetDC(window);


    input.screen = SUDOKU_SCREEN;
    MSG message;


    while (GetMessageW(&message, window, 0, 0) > 0)
    {
        int toggle = 0;
        switch (message.message)
        {
        case WM_QUIT:
        {
            break;
        }
        break;
        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            u32 vk_code = (u32)message.wParam;
            bool is_down = ((message.lParam & (1 << 31)) == 0);
            bool changed = ((message.lParam & (1 << 30)) << 1) == (message.lParam & (1 << 31));

            switch (vk_code)
            {
                process_button(BUTTON_UP, VK_UP);
                process_button(BUTTON_DOWN, VK_DOWN);
                process_button(BUTTON_LEFT, VK_LEFT);
                process_button(BUTTON_RIGHT, VK_RIGHT);
            }
        }
        break;
        case WM_LBUTTONDOWN:
        {
            object_types* pixel_object = get_object_at_pos(GET_X_LPARAM(message.lParam), GET_Y_LPARAM(message.lParam));

            if (pixel_object->id == cell_id)
            {
                // If not pressing control or shift, reset previously highlighted cells
                if (!((message.wParam & MK_CONTROL) | (message.wParam & MK_SHIFT)))
                    std::fill(&input.is_higlighted[0][0], &input.is_higlighted[0][0] + sizeof(input.is_higlighted), false);

                cell c = pixel_object->object.cell;
                input.is_higlighted[c.p_y][c.p_x] = true;
                input.mouse_drag = true;
            }
        }
        break;
        case WM_MOUSEMOVE:
        {
            object_types* pixel_object = get_object_at_pos(GET_X_LPARAM(message.lParam), GET_Y_LPARAM(message.lParam));

            if (pixel_object->id == cell_id)
            {
                SetCursor(hCursorHand);
                if (input.mouse_drag)
                {
                    cell c = pixel_object->object.cell;
                    input.is_higlighted[c.p_y][c.p_x] = true;
                }
            }
            else
            {
                SetCursor(hCursorArrow);
            }

        }
        break;
        case WM_LBUTTONUP:
        {
            input.mouse_drag = false;
        }
        break;
        default:
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        }
        // Drawing
        sAPP.simulate(&input);


        // Render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

    }

    return 0;
}