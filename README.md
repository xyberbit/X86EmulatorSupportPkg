### PREFACE

> X86EmulatorPkg enables QEMU on UEFI and makes x64 option-ROMs executable on
Aarch64 platforms. Even though it's not a recent package, it still functions
well with late edk2.

### REQUIREMENT

> Additional prototypes and declarations are required to glue compilers, QEMU,
UEFI and CPU architectures together; however, they are not found as a part of
X86EmulatorPkg. Conventionally, a so-called support header does the job.
OpenSslSupport.h in edk2-archive and CrtLibSupport.h in edk2 are both good
examples to reference as templates of X86EmulatorPkg's support header.

### WORK

> The support header is the root include file of all headers as described in
itself, it contains everything required to build the module. The associated
standard headers declare nothing but include the support header only. To match
modern edk2, the support header is mostly in reference to the headers under
tianocore/edk2-libc/StdLib/Include.

### MORE

> It's not necessary to put required headers in X86EmulatorPkg, that makes the
source package messy. Instead, a support package is created that comes with all
headers for X86EmulatorPkg. Furthermore, the support package is easily
expandable to support other similar projects.

### GCC OPTIONS
  
  * "-nostdinc" strongly recommended, compiler default headers excluded.

  * "-w" all warnings disabled if harmless.

  * individual warning disabled if -w not preferrable.

    * "-D__noreturn__=" cpu_loop_exit() defined in assembly w/ ret instruction.

    * "-Wno-return-type" value returned functions terminated with tcg_abort().

### DEBUG MODE
  
> tianocore/edk2/MdePkg/Library/BaseIoLibIntrinsic/IoLibNoIo.c prohibits any I/O
  command for non-x86 architectures. Comment out all ASSERTs in Io functions to
  free the x86 emulator.

### QUICK START

> _\# switch to root of workspace or any preferrable directory in $PACKAGES_PATH_

    git clone https://github.com/ardbiesheuvel/X86EmulatorPkg.git
    git clone https://github.com/xyberbit/X86EmulatorSupportPkg.git

    x86emuinf="X86EmulatorPkg/X86Emulator.inf"

    echo "  GCC:*_*_*_CC_FLAGS = -nostdinc -D__noreturn__= -Wno-return-type" >> $x86emuinf
    echo "" >> $x86emuinf
    echo "[Packages]" >> $x86emuinf
    echo "  X86EmulatorSupportPkg/X86EmulatorSupportPkg.dec" >> $x86emuinf

> _\# append "  X86EmulatorPkg/X86Emulator.inf" to section [Components] in <your-project>.dsc_\
> _\# append "  INF X86EmulatorPkg/X86Emulator.inf" to section [FV.FvMain] in <your-project>.fdf_
