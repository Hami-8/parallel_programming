sum_naive(std::vector<double, std::allocator<double>> const&, int):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        mov     QWORD PTR [rbp-24], rdi
        mov     DWORD PTR [rbp-28], esi
        pxor    xmm0, xmm0
        movsd   QWORD PTR [rbp-8], xmm0
        mov     DWORD PTR [rbp-12], 0
        jmp     .L2
.L3:
        mov     eax, DWORD PTR [rbp-12]
        movsx   rdx, eax
        mov     rax, QWORD PTR [rbp-24]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<double, std::allocator<double>>::operator[](unsigned long) const
        movsd   xmm0, QWORD PTR [rax]
        movsd   xmm1, QWORD PTR [rbp-8]
        addsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-8], xmm0
        add     DWORD PTR [rbp-12], 1
.L2:
        mov     eax, DWORD PTR [rbp-12]
        cmp     eax, DWORD PTR [rbp-28]
        jl      .L3
        movsd   xmm0, QWORD PTR [rbp-8]
        leave
        ret
sum_2way(std::vector<double, std::allocator<double>> const&, int):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 48
        mov     QWORD PTR [rbp-40], rdi
        mov     DWORD PTR [rbp-44], esi
        pxor    xmm0, xmm0
        movsd   QWORD PTR [rbp-8], xmm0
        pxor    xmm0, xmm0
        movsd   QWORD PTR [rbp-16], xmm0
        mov     DWORD PTR [rbp-20], 0
        jmp     .L6
.L8:
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        mov     rax, QWORD PTR [rbp-40]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<double, std::allocator<double>>::operator[](unsigned long) const
        movsd   xmm0, QWORD PTR [rax]
        movsd   xmm1, QWORD PTR [rbp-8]
        addsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-8], xmm0
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        cmp     DWORD PTR [rbp-44], eax
        jle     .L7
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        mov     rax, QWORD PTR [rbp-40]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<double, std::allocator<double>>::operator[](unsigned long) const
        movsd   xmm0, QWORD PTR [rax]
        movsd   xmm1, QWORD PTR [rbp-16]
        addsd   xmm0, xmm1
        movsd   QWORD PTR [rbp-16], xmm0
.L7:
        add     DWORD PTR [rbp-20], 2
.L6:
        mov     eax, DWORD PTR [rbp-20]
        cmp     eax, DWORD PTR [rbp-44]
        jl      .L8
        movsd   xmm0, QWORD PTR [rbp-8]
        addsd   xmm0, QWORD PTR [rbp-16]
        leave
        ret