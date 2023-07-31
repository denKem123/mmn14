MAIN: add r3,LIST
LOOP: prn 48
inc r3
mov r3,K
sub r1,r4
bne END
dec W
;Comment0
.entry MAIN
add L3,L3
END: stop
;Comment1
LIST: .data 6,-9
.data -100
K: .data 31
.entry LIST
.extern W
.extern L3