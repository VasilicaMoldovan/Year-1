bits 32
global start

extern exit, fwrite, fopen, fclose, printf, scanf, fprintf
import fprintf msvcrt.dll 
import printf msvcrt.dll
import scanf msvcrt.dll  
import exit msvcrt.dll
import fwrite msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 

segment data use32 class=data public
    format db '%s', 0
    new_word dd 0
    

segment code use32 class=code public 
    start:
        read:
           mov dword[new_word], 0
           push dword new_word
           push dword format
           call [scanf]
           add esp, 4*2
           
           mov ecx, 0
           repeta:
               cmp dword[new_word + ecx], 0
               je skip
               inc ecx 
               jmp repeta
               
           skip:
             mov edi, 0
             reverse:
                 mov eax, dword[new_word + ecx]
                 stosd 
                 loop reverse
                 
            mov eax, [edi]
            push eax
            push dword format
            call [printf]
            add esp, 4*2
            
           cmp dword[new_word], 0Ah
           je finish
           
        finish:
    push    dword 0
    call    [exit]