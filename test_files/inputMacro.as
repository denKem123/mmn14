; file inputMacro.as

mcro m1 
 bne LOOP
 sub @r1, @r4
endmcro

MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
prn -5
m1
bne END
L1: inc K
bne LOOP
END: stop
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 22