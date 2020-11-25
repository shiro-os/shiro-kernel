section .text
global setInterrupts:
setInterrupts:
  sti
  ret

global clearInterrupts:
clearInterrupts:
  cli
  ret