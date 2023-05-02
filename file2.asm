extern printf


section .data
    x dq 8
    one dq 1
    two dq 2
    three dq 3
    five dq 5
    ten dq 10
    
    
    
section .rodata
    format db '%.3f', 0
    
section .text
;f1 = 3 (0.5 / (x + 1) + 1)
;f2 = 2.5x − 9.5 = (3x - 10)/2
;f3 = 5 / x

global f1
global f2
global f3
f1:
    push ebp
    mov ebp, esp
    mov eax, dword[esp + 8]
    fld qword[one]
    fld qword[eax]; обратились к х по адресу, который лежал на стеке
    fld qword[eax]
    faddp
    fld qword[two]
    faddp
    fst qword[esp + 12]
    fld qword[esp + 12]
    fld qword[esp + 12]
    faddp
    faddp
    fld qword[three]
    faddp
    fld qword[esp + 12]
    fdivp
    leave
    ret

f2:
    push ebp
    mov ebp, esp
    mov eax, dword[esp + 8]
    fld qword[eax]; обратились к х по адресу, который лежал на стеке
    fld qword[eax]
    faddp
    fld qword[eax]
    faddp; умножили на три сложив три раза
    fld qword[ten]
    fsubp
    fld qword[two]
    fdivp
    leave
    ret
    

f3:
    push ebp
    mov ebp, esp
    fld qword[five]; положили делимое
    mov eax, dword[esp + 8]
    fld qword[eax]; обратились к х по адресу, который лежал на стеке
    fdivp; st1 =5/x, pop
    leave
    ret
    
    
