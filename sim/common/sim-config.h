/*  This file is part of the program psim.

    Copyright (C) 1994-1995, Andrew Cagney <cagney@highland.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
    */


#ifndef _PSIM_CONFIG_H_
#define _PSIM_CONFIG_H_

/* Host dependant:

   The CPP below defines information about the compilation host.  In
   particular it defines the macro's:

   	WITH_HOST_BYTE_ORDER	The byte order of the host. Could
				be any of LITTLE_ENDIAN, BIG_ENDIAN
				or 0 (unknown).  Those macro's also
				need to be defined.

 */


/* NetBSD:

   NetBSD is easy, everything you could ever want is in a header file
   (well almost :-) */

#if defined(__NetBSD__)
# include <machine/endian.h>
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BYTE_ORDER
# endif
# if (BYTE_ORDER != WITH_HOST_BYTE_ORDER)
#  error "host endian incorrectly configured, check config.h"
# endif
#endif

/* Linux is similarly easy.  */

#if defined(__linux__)
# include <endian.h>
# include <asm/byteorder.h>
# if defined(__LITTLE_ENDIAN) && !defined(LITTLE_ENDIAN)
#  define LITTLE_ENDIAN __LITTLE_ENDIAN
# endif
# if defined(__BIG_ENDIAN) && !defined(BIG_ENDIAN)
#  define BIG_ENDIAN __BIG_ENDIAN
# endif
# if defined(__BYTE_ORDER) && !defined(BYTE_ORDER)
#  define BYTE_ORDER __BYTE_ORDER
# endif
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BYTE_ORDER
# endif
# if (BYTE_ORDER != WITH_HOST_BYTE_ORDER)
#  error "host endian incorrectly configured, check config.h"
# endif
#endif

/* INSERT HERE - hosts that have available LITTLE_ENDIAN and
   BIG_ENDIAN macro's */


/* Some hosts don't define LITTLE_ENDIAN or BIG_ENDIAN, help them out */

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif


/* SunOS on SPARC:

   Big endian last time I looked */

#if defined(sparc) || defined(__sparc__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BIG_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != BIG_ENDIAN)
#  error "sun was big endian last time I looked ..."
# endif
#endif


/* Random x86

   Little endian last time I looked */

#if defined(i386) || defined(i486) || defined(i586) || defined (i686) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined (__i686__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER LITTLE_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != LITTLE_ENDIAN)
#  error "x86 was little endian last time I looked ..."
# endif
#endif

#if (defined (__i486__) || defined (__i586__) || defined (__i686__)) && defined(__GNUC__) && WITH_BSWAP
#undef  htonl
#undef  ntohl
#define htonl(IN) __extension__ ({ int _out; __asm__ ("bswap %0" : "=r" (_out) : "0" (IN)); _out; })
#define ntohl(IN) __extension__ ({ int _out; __asm__ ("bswap %0" : "=r" (_out) : "0" (IN)); _out; })
#endif

/* Power or PowerPC running AIX  */
#if defined(_POWER) && defined(_AIX)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BIG_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != BIG_ENDIAN)
#  error "Power/PowerPC AIX was big endian last time I looked ..."
# endif
#endif

/* Solaris running PowerPC */
#if defined(__PPC) && defined(__sun__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER LITTLE_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != LITTLE_ENDIAN)
#  error "Solaris on PowerPCs was little endian last time I looked ..."
# endif
#endif

/* HP/PA */
#if defined(__hppa__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BIG_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != BIG_ENDIAN)
#  error "HP/PA was big endian last time I looked ..."
# endif
#endif

/* Big endian MIPS */
#if defined(__MIPSEB__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER BIG_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != BIG_ENDIAN)
#  error "MIPSEB was big endian last time I looked ..."
# endif
#endif

/* Little endian MIPS */
#if defined(__MIPSEL__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER LITTLE_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != LITTLE_ENDIAN)
#  error "MIPSEL was little endian last time I looked ..."
# endif
#endif

/* Windows NT */
#if defined(__WIN32__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER LITTLE_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != LITTLE_ENDIAN)
#  error "Windows NT was little endian last time I looked ..."
# endif
#endif

/* Alpha running DEC unix */
#if defined(__osf__) && defined(__alpha__)
# if (WITH_HOST_BYTE_ORDER == 0)
#  undef WITH_HOST_BYTE_ORDER
#  define WITH_HOST_BYTE_ORDER LITTLE_ENDIAN
# endif
# if (WITH_HOST_BYTE_ORDER != LITTLE_ENDIAN)
#  error "AXP running DEC unix was little endian last time I looked ..."
# endif
#endif


/* INSERT HERE - additional hosts that do not have LITTLE_ENDIAN and
   BIG_ENDIAN definitions available.  */


/* endianness of the host/target:

   If the build process is aware (at compile time) of the endianness
   of the host/target it is able to eliminate slower generic endian
   handling code.

   Possible values are 0 (unknown), LITTLE_ENDIAN, BIG_ENDIAN */

#ifndef WITH_HOST_BYTE_ORDER
#define WITH_HOST_BYTE_ORDER		0 /*unknown*/
#endif

#ifndef WITH_TARGET_BYTE_ORDER
#define WITH_TARGET_BYTE_ORDER		0 /*unknown*/
#endif

extern int current_host_byte_order;
#define CURRENT_HOST_BYTE_ORDER (WITH_HOST_BYTE_ORDER \
				 ? WITH_HOST_BYTE_ORDER \
				 : current_host_byte_order)
extern int current_target_byte_order;
#define CURRENT_TARGET_BYTE_ORDER (WITH_TARGET_BYTE_ORDER \
				   ? WITH_TARGET_BYTE_ORDER \
				   : current_target_byte_order)



/* XOR endian.

   In addition to the above, the simulator can support the's horrible
   XOR endian mode (for instance implemented by the PowerPC).  This
   feature makes it possible to control the endian mode of a processor
   using the MSR. */

/* #define WITH_XOR_ENDIAN		8 */



/* Intel host BSWAP support:

   Whether to use bswap on the 486 and pentiums rather than the 386
   sequence that uses xchgb/rorl/xchgb */
#ifndef WITH_BSWAP
#define	WITH_BSWAP 0
#endif



/* SMP support:

   Sets a limit on the number of processors that can be simulated.  If
   WITH_SMP is set to zero (0), the simulator is restricted to
   suporting only on processor (and as a consequence leaves the SMP
   code out of the build process).

   The actual number of processors is taken from the device
   /options/smp@<nr-cpu> */

#if defined (WITH_SMP)

#if WITH_SMP
#define MAX_NR_PROCESSORS		WITH_SMP
#else
#define MAX_NR_PROCESSORS		1
#endif

#endif



/* Word size of host/target:

   Set these according to your host and target requirements.  At this
   point in time, I've only compiled (not run) for a 64bit and never
   built for a 64bit host.  This will always remain a compile time
   option */

#ifndef WITH_TARGET_WORD_BITSIZE
#define WITH_TARGET_WORD_BITSIZE        32 /* compiled only */
#endif

#ifndef WITH_HOST_WORD_BITSIZE
#define WITH_HOST_WORD_BITSIZE		32 /* 64bit ready? */
#endif



/* Most significant bit of target:

   Set this according to your target's bit numbering convention.  For
   the PowerPC it is zero, for many other targets it is 31 or 63.

   For targets that can both have either 32 or 64 bit words and number
   MSB as 31, 63.  Define this to be (WITH_TARGET_WORD_BITSIZE - 1) */

#ifndef WITH_TARGET_WORD_MSB
#define WITH_TARGET_WORD_MSB            0
#endif



/* Program environment:

   Three environments are available - UEA (user), VEA (virtual) and
   OEA (perating).  The former two are environment that users would
   expect to see (VEA includes things like coherency and the time
   base) while OEA is what an operating system expects to see.  By
   setting these to specific values, the build process is able to
   eliminate non relevent environment code

   CURRENT_ENVIRONMENT specifies which of vea or oea is required for
   the current runtime. */

#if defined (WITH_ENVIRONMENT)

#define USER_ENVIRONMENT		1
#define VIRTUAL_ENVIRONMENT		2
#define OPERATING_ENVIRONMENT		3

extern int current_environment;
#define CURRENT_ENVIRONMENT (WITH_ENVIRONMENT \
			     ? WITH_ENVIRONMENT \
			     : current_environment)

#endif



/* Callback/Default Memory.

   Core includes a builtin memory type (raw_memory) that is
   implemented using an array.  raw_memory does not require any
   additional functions etc.

   Callback memory is where the core calls a core device for the data
   it requires.

   Default memory is an extenstion of this where for addresses that do
   not map into either a callback or core memory range a default map
   can be used.

   The OEA model uses callback memory for devices and default memory
   for buses.

   The VEA model uses callback memory to capture `page faults'.

   While it may be possible to eliminate callback/default memory (and
   hence also eliminate an additional test per memory fetch) it
   probably is not worth the effort.

   BTW, while raw_memory could have been implemented as a callback,
   profiling has shown that there is a biger win (at least for the
   x86) in eliminating a function call for the most common
   (raw_memory) case. */

#ifndef WITH_CALLBACK_MEMORY
#define WITH_CALLBACK_MEMORY		1
#endif



/* Alignment:

   The PowerPC may or may not handle miss aligned transfers.  An
   implementation normally handles miss aligned transfers in big
   endian mode but generates an exception in little endian mode.

   This model.  Instead allows both little and big endian modes to
   either take exceptions or handle miss aligned transfers.

   If 0 is specified then for big-endian mode miss alligned accesses
   are permitted (NONSTRICT_ALIGNMENT) while in little-endian mode the
   processor will fault on them (STRICT_ALIGNMENT). */

#if defined (WITH_ALIGNMENT)

#define NONSTRICT_ALIGNMENT    		1
#define STRICT_ALIGNMENT	       	2

extern int current_alignment;
#define CURRENT_ALIGNMENT (WITH_ALIGNMENT \
			   ? WITH_ALIGNMENT \
			   : current_alignment)

#endif



/* Floating point suport:

   Should the processor trap for all floating point instructions (as
   if the hardware wasn't implemented) or implement the floating point
   instructions directly. */

#if defined (WITH_FLOATING_POINT)

#define SOFT_FLOATING_POINT		1
#define HARD_FLOATING_POINT		2

extern int current_floating_point;
#define CURRENT_FLOATING_POINT (WITH_FLOATING_POINT \
				? WITH_FLOATING_POINT \
				: current_floating_point)

#endif



/* Debugging:

   Control the inclusion of debugging code. */

/* Include the tracing code.  Disabling this eliminates all tracing
   code */

#ifndef WITH_TRACE
#define WITH_TRACE                      1
#endif


/* include code that checks assertions scattered through out the
   program */

#ifndef WITH_ASSERT
#define WITH_ASSERT			1
#endif


/* Whether to check instructions for reserved bits being set */

/* #define WITH_RESERVED_BITS		1 */



/* include monitoring code */

#define MONITOR_INSTRUCTION_ISSUE	1
#define MONITOR_LOAD_STORE_UNIT		2
/* do not define WITH_MON by default */
#define DEFAULT_WITH_MON		(MONITOR_LOAD_STORE_UNIT \
					 | MONITOR_INSTRUCTION_ISSUE)


/* Current CPU model (models are in the generated models.h include file)  */
#ifndef WITH_MODEL
#define WITH_MODEL			0
#endif

#define CURRENT_MODEL (WITH_MODEL	\
		       ? WITH_MODEL	\
		       : current_model)

#ifndef WITH_DEFAULT_MODEL
#define WITH_DEFAULT_MODEL		DEFAULT_MODEL
#endif

#define MODEL_ISSUE_IGNORE		(-1)
#define MODEL_ISSUE_PROCESS		1

#ifndef WITH_MODEL_ISSUE
#define WITH_MODEL_ISSUE		0
#endif

extern int current_model_issue;
#define CURRENT_MODEL_ISSUE (WITH_MODEL_ISSUE	\
			     ? WITH_MODEL_ISSUE	\
			     : current_model_issue)



/* Whether or not input/output just uses stdio, or uses printf_filtered for
   output, and polling input for input.  */

#define DONT_USE_STDIO			2
#define DO_USE_STDIO			1

#ifndef WITH_STDIO
#define WITH_STDIO			0
#endif

extern int current_stdio;
#define CURRENT_STDIO (WITH_STDIO	\
		       ? WITH_STDIO     \
		       : current_stdio)



/* Specify that configured calls pass parameters in registers when the
   convention is that they are placed on the stack */

#ifndef WITH_REGPARM
#define WITH_REGPARM                   0
#endif

/* Specify that configured calls use an alternative calling mechanism */

#ifndef WITH_STDCALL
#define WITH_STDCALL                   0
#endif


/* complete/verify/print the simulator configuration */


/* For prefered_target_byte_order arugment */

#if defined (bfd_little_endian)
#define PREFERED_TARGET_BYTE_ORDER(IMAGE) ((IMAGE) == NULL \
					   ? 0 \
					   : bfd_little_endian(IMAGE) \
					   ? LITTLE_ENDIAN \
					   : BIG_ENDIAN)
#else
#define PREFERED_TARGET_BYTE_ORDER(IMAGE) ((IMAGE) == NULL \
					   ? 0 \
					   : !(IMAGE)->xvec->byteorder_big_p \
					   ? LITTLE_ENDIAN \
					   : BIG_ENDIAN)
#endif


extern void sim_config (SIM_DESC sd,
			int prefered_target_byte_order);

extern void print_sim_config (SIM_DESC sd);


#endif /* _PSIM_CONFIG_H */
