inc %ra
movb %rc,`8
inc %rd
atoi_loop:
syscall
cltb *%rc,`48
brc atoi_done
cgtb *%rc,`57
brc atoi_done
subb *%rc,*%rc,`48
mul *%rb,*%rb,`10
add *%rb,*%rb,*%rc
bra atoi_loop
atoi_done:
mov %ra,*%rb
mov %rc,`0
loop:
ceq %ra,%rd
brc end
inc %rc
mod %rb,%ra,`2
cne %rb,%rd
brc even
mul %ra,%ra,`3
inc %ra
bra loop
even:
div %ra,%ra,`2
bra loop
end:
cne %rb,%ra
brc zero
dec %rb
zero:
mov %ra,`10
endl:
inc %rb
mul %rd,%rd,%ra
cgte %rc,%rd
brc endl
mov %rd,%rb
printl:
dec %rb
modb *%rb,%rc,%ra
addb *%rb,*%rb,`48
div %rc,%rc,%ra
cne %rb,`0
brc printl
mov %ra,`2
mov %rc,%rb
inc %rb
syscall