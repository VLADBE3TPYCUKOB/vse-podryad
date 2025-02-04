; Запросить с клавиатуры два числа (m и n) и два символа (X и Y).
; Результатом работы становится файл result.txt, который состоит из n строк по m символов. 
; Четные строки состоят из введенного символа X, а нечетные из символа Y. 
; Например, введены числа 3 и 5 и символы % и №. Результат получится 

; №№№№№
; %%%%%
; №№№№№

;В моей лабороторной я считал строки с нулевой. четная-нечетная-четная-нечетная...

format PE console
include 'win32ax.inc'
entry _main

section '.code' executable
_main:
    ;файл
    invoke CreateFile, filename, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
    mov [file_variable], eax ; сохранить адрес файла

    invoke printf, input_m
    invoke scanf, out_decimal, m ; int m

    invoke printf, input_n
    invoke scanf, out_decimal, n ; int n
    
    invoke printf, input_x
    invoke scanf, out_char, x ; char x
    
    invoke printf, input_y
    invoke scanf, out_char, y ; char y
    
    invoke printf, datas_n_m, [m], [n]
    invoke printf, datas_x_y, [x], [y]
    
    mov esi, [m]
    mov edi, [x] ; хранить x char в edi
    write_line:
        mov ebx,[n]
        cmp [char_to_print], edi
        je mov_y
        
        mov_x:
            mov [char_to_print], edi
            jmp write_char
        mov_y:
            mov edi, [y]
            mov [char_to_print], edi
        
        write_char:
            invoke WriteFile, [file_variable], char_to_print, 1, 0, 0
            dec ebx
            jnz write_char
        
        invoke WriteFile, [file_variable], slash_n, 1, 0, 0
        dec esi
        mov edi, [x] ; хранить x char в edi
        jnz write_line
    
    invoke CloseHandle, [file_variable]
    
    invoke ExitProcess, 0
    
section '.data' data readable writeable
    m dd 0
    n dd 0
    x dd 0
    y dd 0
    filename db 'result.txt', 0
    file_variable dd 0
    char_to_print dd 0
    
    input_m db 'm >>> ', 0
    input_n db 'n >>> ', 0
    input_x db 'x >>> ', 0
    input_y db 'y >>> ', 0
    out_decimal db '%32d', 0
    out_char db '%32s', 0
    datas_n_m db 'm = %d; n = %d', 10, 0
    datas_x_y db 'x = %c; y = %c', 10, 0
    
    slash_n db 10, 0
    char db '%c', 0
    
section '.idata' import data readable writeable
 
    library kernel32, 'kernel32.dll', msvcrt, 'msvcrt.dll'
    
    import kernel32, ExitProcess, 'ExitProcess', CreateFile, 'CreateFileA', WriteFile, 'WriteFile', CloseHandle, 'CloseHandle'
    import msvcrt, printf, 'printf', scanf, 'scanf', getchar, 'getchar'