# Hey Emacs, this is a -*- makefile -*-
#
# WinAVR Sample makefile written by Eric B. Weddington, Jörg Wunsch, et al.
# Released to the Public Domain
# Please read the make user manual!
#
# Additional material for this makefile was submitted by:
#  Tim Henigan
#  Peter Fleury
#  Reiner Patommel
#  Sander Pool
#  Frederik Rouleau
#  Markus Pfaff
#
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF (for use with AVR Studio 3.x or VMLAB).
#
# make extcoff = Convert ELF to AVR Extended COFF (for use with AVR Studio
#                4.07 or greater).
#
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
#
# make filename.s = Just compile filename.c into the assembler code only
#
# To rebuild project do "make clean" then "make all".
#

# Output Directory name
# Use OUTDIR= .
# for current directory
OUTDIR = output


# MCU name
MCU = attiny2313

# CPU clock
F_CPU = 8000000

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Target file name (without extension).
TARGET = AVR-HVSP

## A directory for common include files and the simple USART library.
## If you move either the current folder or the Library folder, you'll
##  need to change this path to match.
LIBDIR =


# List C source files here. (C dependencies are automatically generated.)
#SRC = $(TARGET).c
SRC=$(wildcard *.c $(LIBDIR)/*.c)



# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC =



# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS =


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)

# Place -I options here
CINCS =


CFLAGS = $(CDEFS)
CFLAGS += -O$(OPT)
CFLAGS += $(CSTANDARD)
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
# Put data and functions in separate sections - not linked if not used
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -Wall -Wstrict-prototypes
# Link time optimization - more straight instruction and not so many jumps.
CFLAGS += -flto


ASFLAGS = -DF_CPU=$(F_CPU)
ASFLAGS += -fdata-sections -ffunction-sections -flto

LDFLAGS = -Wl,-gc-sections # Do not link unused function sections
LDFLAGS += -Wl,--relax
LDFLAGS += -flto
#LDFLAGS += -nostartfiles



# Programming support using avrdude. Settings and variables.

# Programming hardware: alf avr910 avrisp bascom bsd
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = stk500

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = com1    # programmer connected to serial device

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep


# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)



# ---------------------------------------------------------------------------

# Define directories, if needed.
DIRAVR = c:/winavr
DIRAVRBIN = $(DIRAVR)/bin
DIRAVRUTILS = $(DIRAVR)/utils/bin
DIRINC = .
DIRLIB = $(DIRAVR)/avr/lib


# Define programs and commands.
SHELL = sh
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
COPY = cp




# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:




# Define all object files.
OBJ = $(SRC:%.c=$(OUTDIR)/%.o) $(ASRC:%.S=$(OUTDIR)/%.o)

# Define all listing files.
LST = $(ASRC:%.S=$(OUTDIR)/%.lst) $(SRC:%.c=$(OUTDIR)/%.lst)


# Compiler flags to generate dependency files.
GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d


# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)





# Default target.
all: begin gccversion createdir sizebefore build sizeafter finished end

build: elf hex eep lss sym

elf: $(OUTDIR)/$(TARGET).elf
hex: $(OUTDIR)/$(TARGET).hex
eep: $(OUTDIR)/$(TARGET).eep
lss: $(OUTDIR)/$(TARGET).lss
sym: $(OUTDIR)/$(TARGET).sym



# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
        @echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(OUTDIR)/$(TARGET).hex
ELFSIZE = $(SIZE) -C --mcu=$(MCU) $(OUTDIR)/$(TARGET).elf
sizebefore:
	@if [ -f $(OUTDIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(OUTDIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi



# Display compiler version information.
gccversion:
	@$(CC) --version

# Create output dir if not exist
createdir:
	mkdir -p $(OUTDIR)

# Program the device.
program: $(OUTDIR)/$(TARGET).hex $(OUTDIR)/$(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)
$(AVRDUDE_WRITE_EEPROM)




# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000


coff: $(OUTDIR)/$(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(OUTDIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(OUTDIR)/$(TARGET).cof


extcoff: $(OUTDIR)/$(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(OUTDIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(OUTDIR)/$(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
$(OUTDIR)/%.lss: $(OUTDIR)/%.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $(OUTDIR)/$@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
$(OUTDIR)/%.sym: $(OUTDIR)/%.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $(OUTDIR)/$@
	$(NM) -n $< > $@



# Link: create ELF output file from object files.
.SECONDARY : $(OUTDIR)/$(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)


# Compile: create object files from C source files.
$(OUTDIR)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
$(OUTDIR)/%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@



# Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OUTDIR)/$(TARGET).hex
	$(REMOVE) $(OUTDIR)/$(TARGET).eep
	$(REMOVE) $(OUTDIR)/$(TARGET).obj
	$(REMOVE) $(OUTDIR)/$(TARGET).cof
	$(REMOVE) $(OUTDIR)/$(TARGET).elf
	$(REMOVE) $(OUTDIR)/$(TARGET).map
	$(REMOVE) $(OUTDIR)/$(TARGET).obj
	$(REMOVE) $(OUTDIR)/$(TARGET).a90
	$(REMOVE) $(OUTDIR)/$(TARGET).sym
	$(REMOVE) $(OUTDIR)/$(TARGET).lnk
	$(REMOVE) $(OUTDIR)/$(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) .dep/*



# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff \
clean clean_list program
