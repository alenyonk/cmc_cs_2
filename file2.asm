extern printf


section .data
    x dq 8
    one dq 1
    two dd 2
    three dd 3
    five dq 5
    nineteen dd 19
    
    
    
section .rodata
    format db '%.3f', 0
    
section .text
;f1 = 3 (0.5 / (x + 1) + 1)
;f2 = 2.5x − 9.5 = (3x - 10)/2
;f3 = 5 / x

global f1
f1:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld qword[ebp + 8]; обратились к х по адресу, который лежал на стеке
    fld qword[ebp + 8]
    faddp
    fiadd dword[two]
    fst qword[ebp + 8]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    faddp
    faddp
    fiadd dword[three]
    fld qword[ebp + 8]
    fdivp
    leave
    ret

global f2
f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]; обратились к х по адресу, который лежал на стеке
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    faddp
    faddp
    faddp
    faddp; умножили на 5
    fisub dword[nineteen]
    fld1
    fld1
    faddp
    fdivp
    leave
    ret
    
global f3
f3:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld1
    fld1
    fld1
    fld1
    faddp
    faddp
    faddp
    faddp
    fld qword[ebp + 8]
    fdivp
    leave
    ret
    
    

    