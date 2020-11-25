section .data
global IDT_Table:
IDT_Table:
times 256 db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

section .text
extern irq00_handler
extern irq01_handler
extern irq02_handler
extern irq03_handler
extern irq04_handler
extern irq05_handler
extern irq06_handler
extern irq07_handler
extern irq08_handler
extern irq09_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler


global irq0:
irq0:
  pusha
  call irq00_handler
  popa
  ret

global irq1:
irq1:
  pusha
  call irq01_handler
  popa
  ret

global irq2:
irq2:
  pusha
  call irq02_handler
  popa
  ret

global irq3:
irq3:
  pusha
  call irq03_handler
  popa
  ret

global irq4:
irq4:
  pusha
  call irq04_handler
  popa
  ret

global irq5:
irq5:
  pusha
  call irq05_handler
  popa
  ret

global irq6:
irq6:
  pusha
  call irq06_handler
  popa
  ret

global irq7:
irq7:
  pusha
  call irq07_handler
  popa
  ret

global irq8:
irq8:
  pusha
  call irq08_handler
  popa
  ret

global irq9:
irq9:
  pusha
  call irq09_handler
  popa
  ret

global irq10:
irq10:
  pusha
  call irq10_handler
  popa
  ret

global irq11:
irq11:
  pusha
  call irq11_handler
  popa
  ret

global irq12:
irq12:
  pusha
  call irq12_handler
  popa
  ret

global irq13:
irq13:
  pusha
  call irq13_handler
  popa
  ret

global irq14:
irq14:
  pusha
  call irq14_handler
  popa
  ret

global irq15:
irq15:
  pusha
  call irq15_handler
  popa
  ret

global idt_load:
idt_load:
  mov edx, [esp + 4]
  lidt [edx]
  sti
  ret

