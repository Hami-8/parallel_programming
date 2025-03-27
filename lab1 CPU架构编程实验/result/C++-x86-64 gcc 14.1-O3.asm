sum_naive(std::vector<double, std::allocator<double>> const&, int):
        test    esi, esi
        jle     .L7
        mov     rcx, QWORD PTR [rdi]
        cmp     esi, 1
        je      .L8
        mov     edx, esi
        mov     rax, rcx
        pxor    xmm0, xmm0
        shr     edx
        sal     rdx, 4
        add     rdx, rcx
.L4:
        addsd   xmm0, QWORD PTR [rax]
        add     rax, 16
        addsd   xmm0, QWORD PTR [rax-8]
        cmp     rdx, rax
        jne     .L4
        mov     eax, esi
        and     eax, -2
        and     esi, 1
        je      .L11
.L3:
        cdqe
        addsd   xmm0, QWORD PTR [rcx+rax*8]
        ret
.L11:
        ret
.L7:
        pxor    xmm0, xmm0
        ret
.L8:
        xor     eax, eax
        pxor    xmm0, xmm0
        jmp     .L3
sum_2way(std::vector<double, std::allocator<double>> const&, int):
        test    esi, esi
        jle     .L16
        pxor    xmm0, xmm0
        mov     rcx, QWORD PTR [rdi]
        xor     eax, eax
        movapd  xmm1, xmm0
.L15:
        lea     edx, [rax+1]
        addsd   xmm1, QWORD PTR [rcx+rax*8]
        cmp     esi, edx
        jle     .L14
        addsd   xmm0, QWORD PTR [rcx+8+rax*8]
.L14:
        add     rax, 2
        cmp     esi, eax
        jg      .L15
        addsd   xmm0, xmm1
        ret
.L16:
        pxor    xmm0, xmm0
        ret