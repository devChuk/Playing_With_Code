.code16         # Use 16-bit assembly
.globl start    # This tells the linker where we want to start executing

start:
    movb $0x00,%ah      # 0x00 - set video mode
    movb $0x03,%al      # 0x03 - 80x25 text mode
    int $0x10           # call into the BIOS
    mov $0x00, %al      # interrupts to get system time
    out %al, $0x70      # writes reg to rtc
    in $0x71, %al       # read secs from rtc   
    mov $0x0a, %bl
    idiv %bl            # al/bl remainder 0-9
    mov %ah, %al        # remainder -> al
    mov $0x30, %bl      # 48 -> bl
    add %bl, %al        # converts int to ASCII value
    movb %al, %dl       # stores in dl
    
question:
    movw $message, %si  # load the offset of our message into %si
    jmp print_char      # print "what number am i thinking of"
guess:
    movb $0x00,%ah      # 0x00 - set video mode
    int $0x16           # call into the BIOS, read user input into al

    cmp %dl, %al
    jz ifright

ifwrong:
    movw $wrong, %si    # load the offset of our message into %si
    movb %al, 0(%si)    # print user inputted value
    movb $0x0a, 1(%si)
    movb $0x0d, 2(%si)  # add new line
    movb $0x0a, 18(%si)
    movb $0x0d, 19(%si) # add new line
    jmp print_wrong      # print "Wrong"

ifright:
    movw $right, %si    # load the offset of our message into %si
    movb %al, 0(%si)    # print user inputted value
    movb $0x0a, 1(%si)
    movb $0x0d, 2(%si)  # add new line
    movb $0x0a, 18(%si)
    movb $0x0d, 19(%si) # add new line
print_right: 
    lodsb           # loads a single byte from (%si) into %al and increments %si
    testb %al,%al   # checks to see if the byte is 0
    jz done        # if so, jump out (jz jumps if ZF in EFLAGS is set)
    movb $0x0E,%ah  # 0x0E is the BIOS code to print the single character
    int $0x10       # call into the BIOS using a software interrupt
    jmp print_right  # go back to the start of the loop

print_char: 
    lodsb           # loads a single byte from (%si) into %al and increments %si
    testb %al,%al   # checks to see if the byte is 0
    jz guess        # if so, jump out (jz jumps if ZF in EFLAGS is set)
    movb $0x0E,%ah  # 0x0E is the BIOS code to print the single character
    int $0x10       # call into the BIOS using a software interrupt
    jmp print_char  # go back to the start of the loop
print_wrong: 
    lodsb           # loads a single byte from (%si) into %al and increments %si
    testb %al,%al   # checks to see if the byte is 0
    jz question        # if so, jump out (jz jumps if ZF in EFLAGS is set)
    movb $0x0E,%ah  # 0x0E is the BIOS code to print the single character
    int $0x10       # call into the BIOS using a software interrupt
    jmp print_wrong # go back to the start of the loop

done: 
    jmp done        # loop forever

# The .string command inserts an ASCII string with a null terminator
message:
    .string    "What number am I thinking of (0-9): "
wrong:
    .string    "   -----Wrong-----  "
right:
    .string    "   ----Correct----  "

# This pads out the rest of the boot sector and then puts
# the magic 0x55AA that the BIOS expects at the end, making sure
# we end up with 512 bytes in total.
# 
# The somewhat cryptic "(. - start)" means "the current address
# minus the start of code", i.e. the size of the code we've written
# so far. So this will insert as many zeroes as are needed to make
# the boot sector 510 bytes log, and 

.fill 510 - (. - start), 1, 0
.byte 0x55
.byte 0xAA
