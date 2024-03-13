from pwn import * 
import time
import ctypes 

context.log_level = 'debug'
fruits = [
    "Apple", 
    "Orange", 
    "Mango", 
    "Banana", 
    "Pineapple", 
    "Watermelon", 
    "Guava", 
    "Kiwi", 
    "Strawberry", 
    "Peach"
]

libc = ctypes.CDLL("/lib/x86_64-linux-gnu/libc.so.6")
p = process('./chal')
libc.srand(int(time.time())) 

for i in range(50):
    p.sendlineafter("guess : ", (fruits[libc.rand() % 10]).encode()) 

p.interactive() 

